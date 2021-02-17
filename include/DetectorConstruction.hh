/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include "G4NistManager.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;
class G4Event;
class DetectorConstructionMessenger;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction{

public:
    // constructor and destructor
    DetectorConstruction();
    virtual ~DetectorConstruction();

public:
    virtual G4VPhysicalVolume* Construct();
        // This method calls DefineMaterials and DefineVolumes successively.

    G4Material* FindMaterial(G4String);

private:
    
    void DefineMaterials();

    G4VPhysicalVolume* DefineVolumes();



    DetectorConstructionMessenger* fDetectorMessenger;

    bool fCheckOverlaps;

    // Variables related to the dimensions of the setup.

    G4NistManager* mat_man;

    // World
    G4double world_x;
    G4double world_y;
    G4double world_z;

    G4LogicalVolume* world_lv;

    // Source wheel
    G4LogicalVolume* wheel_lv;

    void CreateSourceWheel( );

    G4double wheel_dia;
    G4double wheel_thickness;
    G4ThreeVector wheel_position;
    
    // Source container
    //void CreateSourceContainer();

    friend DetectorConstructionMessenger;

    G4ThreeVector farside_position;
    G4RotationMatrix* farside_rot;

    G4ThreeVector filter_position;
    G4RotationMatrix* filter_rot;

    G4double target_circ_dia;
    G4double target_dia;
    G4double target_thickness;

    G4double target_angle;
    G4String target_mat_name;

    void AddTarget( G4double angle, G4String material);

    void AddTarget(){
        AddTarget( target_angle, target_mat_name);
    }

    void SetTargetAngle( G4double s){ target_angle = s;}

    void SetTargetMaterial( G4String s){ target_mat_name = s;}

    // Detector
    G4double detector_dia;
    G4double detector_thickness;
    void AddDetector( G4ThreeVector );

    void SetFarSidePosition( G4ThreeVector x){
        farside_position = x;
    }

    void FarSideRotateX( G4double a){
        farside_rot->rotateX(a);
    }

    void FarSideRotateY( G4double a){
        farside_rot->rotateY(a);
    }

    void FarSideRotateZ( G4double a){
        farside_rot->rotateZ(a);
    }

    void PlaceFarSideDetector();
    
    void SetFilterPosition( G4ThreeVector x){
        filter_position = x;
    }

    void FilterRotateX( G4double a){
        filter_rot->rotateX(a);
    }

    void FilterRotateY( G4double a){
        filter_rot->rotateY(a);
    }

    void FilterRotateZ( G4double a){
        filter_rot->rotateZ(a);
    }

    void PlaceFilter( G4ThreeVector a );

    G4int fs_count;
        // used to keep track of number of farside detectors.

    G4int filter_count;
};


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
