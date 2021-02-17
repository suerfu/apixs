
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4tgbVolumeMgr.hh"

#include "G4RunManager.hh"
#include "G4Material.hh"

#include "DetectorConstructionMessenger.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4ExtrudedSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4VisExtent.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"

#include "G4UserLimits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include<sstream>
using std::stringstream;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() {
    fCheckOverlaps = true;
    fDetectorMessenger = new DetectorConstructionMessenger(this);
    
    mat_man = G4NistManager::Instance(); //material mananger

    // World
    world_x = 0.5*m;
    world_y = 0.5*m;
    world_z = 0.5*m;

    wheel_dia = 5*cm;
    wheel_thickness = 3*mm;
    wheel_position = G4ThreeVector(0,0,0);

    target_circ_dia = 3.5*cm;
    target_dia = 1*cm;
    target_thickness = wheel_thickness; //1*mm;

    target_angle = 0;
    target_mat_name = "G4_Galactic";

    detector_dia = 3*2.54*cm;
    detector_thickness = 3*mm;

    farside_rot = new G4RotationMatrix();
    fs_count = 0;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


DetectorConstruction::~DetectorConstruction(){
    delete fDetectorMessenger;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* DetectorConstruction::Construct(){
    DefineMaterials();
    return DefineVolumes();
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* DetectorConstruction::DefineVolumes(){
    
    /*
    // Clean old geometry, if any
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
    */

    //===============  Materials ===============//

    G4Material* world_material = mat_man->FindOrBuildMaterial("G4_Galactic");
    G4Material* vacuum_material = mat_man->FindOrBuildMaterial("G4_Galactic");
    //G4Material* NaI_material = mat_man->FindOrBuildMaterial("NaI");
    //G4Material* SS_material = mat_man->FindOrBuildMaterial("G4_STAINLESS-STEEL");
    G4Material* Cu_material = mat_man->FindOrBuildMaterial("G4_Cu");
    G4Material* Si_material = mat_man->FindOrBuildMaterial("G4_Si");


    //===============  Build Geometry ===============//

    // World
    G4Box* world_solid = new G4Box( "world_solid", world_x/2.0, world_y/2.0, world_z/2.0);
    world_lv = new G4LogicalVolume( world_solid, world_material, "world_lv");
    G4VPhysicalVolume* world_pv = new G4PVPlacement( 0, G4ThreeVector(0,0,0), world_lv, "world_pv", 0, false, 0,fCheckOverlaps);

    // Source Wheel
    CreateSourceWheel();

    // Target foils
    AddTarget( 0  *degree, "G4_Li");
    AddTarget( 45 *degree, "G4_Be");
    AddTarget( 90 *degree, "G4_B");
    AddTarget( 135*degree, "G4_N");
    AddTarget( 180*degree, "G4_F");
    AddTarget( 225*degree, "G4_Ti");
    AddTarget( 270*degree, "G4_Al");
    AddTarget( 315*degree, "G4_Galactic");

    //Detector
    AddDetector( G4ThreeVector(0/*target_circ_dia/2*/,0,5*cm));

    G4double hex_height = 9*cm;
    G4double hex_dia = 5*2.54*cm;
    G4double hex_wall_thickness = 2*mm;
    G4double hex_cap_thickness = 1*cm;

    G4Tubs* hex_solid1 = new G4Tubs( "hex_solid1", 0, hex_dia/2, hex_height/2, 0, CLHEP::twopi);
    G4Tubs* hex_solid2 = new G4Tubs( "hex_solid2", 0, hex_dia/2-hex_wall_thickness,hex_height/2-hex_cap_thickness, 0, CLHEP::twopi);
    G4VSolid* hex_solid = new G4SubtractionSolid( "hex_solid", hex_solid1, hex_solid2);
    G4LogicalVolume* hex_lv = new G4LogicalVolume( hex_solid, Cu_material, "hex_lv");
    new G4PVPlacement( 0, G4ThreeVector(0,0,-hex_height/2+hex_cap_thickness+5*cm+detector_thickness), hex_lv, "hex", world_lv, false, 0, fCheckOverlaps);
/*
    // 4PI detector
    G4double detector_ID = 10*cm;
    G4double detector_OD = 11*cm;
    G4Sphere* detector_solid = new G4Sphere( "detector_solid", detector_ID/2, detector_OD/2, 0, CLHEP::twopi, 0, CLHEP::pi);
    G4LogicalVolume* detector_lv = new G4LogicalVolume( detector_solid, vacuum_material, "detector_lv" );
    new G4PVPlacement( 0, G4ThreeVector(0,0,0),detector_lv, "detector", world_lv, false, 0, fCheckOverlaps);
*/

    //===============  Visualization ===============//

    world_lv->SetVisAttributes( G4VisAttributes::Invisible );
    world_lv->SetVisAttributes( G4VisAttributes(G4Colour(.5,.5,.5,0.1)) );
    //center_lv->SetVisAttributes( G4VisAttributes(G4Colour( 1., 0, 1., 0.5)) );

    return world_pv;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void DetectorConstruction::DefineMaterials(){

    G4double a;  // mass of a mole;
    G4double z;  // z=mean number of protons;
    G4double density; //, fractionMass;
    G4String symbol, name;
    G4int ncomponents, natoms;

    G4Element* elNa = new G4Element( name="Sodium", symbol="Na", z = 11, a = 22.990 *g/mole );
    G4Element* elI  = new G4Element( name="Iodine", symbol="I" , z = 53, a = 253.81*g/mole );
    G4Material* NaI = new G4Material( "NaI", density= 3.67*g/cm3, ncomponents = 2);
    NaI->AddElement( elNa, natoms=1 );
    NaI->AddElement( elI,  natoms=1 );

    new G4Material("LHe",   z=2., a= 4.00*g/mole,  density= 0.141*g/cm3, kStateLiquid, 3.*kelvin);

    /*
    G4NistManager* nistManager =  G4NistManager::Instance();

    G4Element* elH  = new G4Element(name = "Hydrogen"   , symbol = "H"  , z = 1.  , a =   1.008*g/mole);
    G4Element* elC  = new G4Element(name = "Carbon"     , symbol = "C"  , z = 6.  , a =  12.011*g/mole);
    */

    // Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}


void DetectorConstruction::PlaceFarSideDetector(){

    // Use stringstream to parameterize the farside detector name with count number
    stringstream ss;
    ss << "farside_" << fs_count;

    G4Material* NaI_material = mat_man->FindOrBuildMaterial("NaI");
    G4Material* Al_material = mat_man->FindOrBuildMaterial("G4_Al");

    // Place the far-side detector.

    G4double NaI_thickness = 2*2.54*cm;
    G4double NaI_dia = 2*2.54*cm;
    G4double Al_thickness = 1*mm;

    G4Tubs* case_solid = new G4Tubs( "case_solid", 0, NaI_dia/2+Al_thickness, (2*Al_thickness+NaI_thickness)/2, 0, CLHEP::twopi);
    G4LogicalVolume* case_lv = new G4LogicalVolume( case_solid, Al_material, "case_lv");

    G4RotationMatrix* rot = new G4RotationMatrix( *farside_rot );
    new G4PVPlacement( rot, farside_position, case_lv, "case", world_lv, false, 0, fCheckOverlaps);


    G4Tubs* farside_solid = new G4Tubs( "fs_solid", 0, NaI_dia/2, NaI_thickness/2, 0, CLHEP::twopi);
    G4LogicalVolume* farside_lv = new G4LogicalVolume( farside_solid, NaI_material, "fs_lv");

    new G4PVPlacement( 0, G4ThreeVector(0,0,0), farside_lv, ss.str(), case_lv, false, 0, fCheckOverlaps);

    // Inform run manager about geometry change.
    G4RunManager::GetRunManager()->GeometryHasBeenModified();

    // After the placement, increment the counter and reset the rotation matrix for the next farside detector.
    fs_count++;
    *farside_rot = G4RotationMatrix();
}


void DetectorConstruction::PlaceFilter( G4ThreeVector a ){

    G4double filter_id = a.x();
    G4double filter_od = a.y();
    G4double filter_thickness = a.z();

    // Use stringstream to parameterize the farside detector name with count number
    stringstream ss;
    ss << "filter_" << filter_count;

    G4Material* filter_material = mat_man->FindOrBuildMaterial("G4_Pb");

    // Place the far-side detector.
    G4Tubs* filter_solid = new G4Tubs( "filter_solid", filter_id/2, filter_od/2, filter_thickness/2, 0, CLHEP::twopi);
    G4LogicalVolume* filter_lv = new G4LogicalVolume( filter_solid, filter_material, "filter_lv");

    G4RotationMatrix* rot = new G4RotationMatrix( *filter_rot );
    new G4PVPlacement( rot, filter_position, filter_lv, ss.str(), world_lv, false, 0, fCheckOverlaps);

    // Inform run manager about geometry change.
    G4RunManager::GetRunManager()->GeometryHasBeenModified();

    // After the placement, increment the counter and reset the rotation matrix for the next farside detector.
    filter_count++;
    *filter_rot = G4RotationMatrix();
}


void DetectorConstruction::CreateSourceWheel(){

    G4Material* wheel_material = mat_man->FindOrBuildMaterial("G4_Al");
    
    G4Tubs* wheel_solid = new G4Tubs( "wheel_solid", 0, wheel_dia/2, wheel_thickness/2, 0, CLHEP::twopi);
    wheel_lv = new G4LogicalVolume( wheel_solid, wheel_material, "wheel_lv");
    new G4PVPlacement( 0, wheel_position, wheel_lv, "wheel", world_lv, false, 0, fCheckOverlaps);
}


void DetectorConstruction::AddTarget( G4double angle, G4String material){

    G4ThreeVector pos = wheel_position + G4ThreeVector( target_circ_dia/2*cos(angle), target_circ_dia/2*sin(angle), wheel_thickness/2-target_thickness/2);

    G4Material* target_material = mat_man->FindOrBuildMaterial(material);
    
    G4Tubs* target_solid = new G4Tubs( "target_solid", 0, target_dia/2, target_thickness/2, 0, CLHEP::twopi);
    G4LogicalVolume* target_lv = new G4LogicalVolume( target_solid, target_material, "target_lv");
    new G4PVPlacement( 0, pos, target_lv, G4String("target_")+material, wheel_lv, false, 0, fCheckOverlaps);
}

void DetectorConstruction::AddDetector( G4ThreeVector v){

    G4Material* det_material = mat_man->FindOrBuildMaterial("G4_Si");
    G4Tubs* det_solid = new G4Tubs( "det_solid", 0, detector_dia/2, detector_thickness/2, 0, CLHEP::twopi);
    G4LogicalVolume* det_lv = new G4LogicalVolume( det_solid, det_material, "det_lv");
    new G4PVPlacement( 0, v, det_lv, "detector", world_lv, false, 0, fCheckOverlaps);
}
