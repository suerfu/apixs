
// $Id: DetectorConstructionMessenger.cc $
//
/// \file DetectorConstructionMessenger.cc
/// \brief Definition of the DetectorConstructionMessenger class

#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"

DetectorConstructionMessenger::DetectorConstructionMessenger( DetectorConstruction* placement) : G4UImessenger(), detector( placement ){

    directory = new G4UIdirectory( "/placement/" );
    directory->SetGuidance( "Far-side detector/filter placement." );

    posCmd = new G4UIcmdWith3VectorAndUnit( "/placement/pos", this);
    posCmd->SetGuidance( "Set the position of the farside detector to be placed.\nUnit is in cm by default.");
    posCmd->SetParameterName( "x", "y", "z", false );
    posCmd->AvailableForStates( G4State_Idle );
    posCmd->SetDefaultValue( G4ThreeVector(0,100*CLHEP::cm,0) );
    posCmd->SetDefaultUnit( "cm" );

    polarCmd = new G4UIcmdWith3Vector( "/placement/polar", this);
    polarCmd->SetGuidance( "Set the position of the farside detector to be placed by cylindrical coordinate.\nThis command does not accept user input unit and the internal unit for distance is cm and that for angle is degree.\n");
    polarCmd->SetParameterName( "r", "phi", "z", false );
    polarCmd->AvailableForStates( G4State_Idle );
    polarCmd->SetDefaultValue( G4ThreeVector(100,0,0) );

    angCmd_x = new G4UIcmdWithADoubleAndUnit( "/placement/rotateX", this );
    angCmd_y = new G4UIcmdWithADoubleAndUnit( "/placement/rotateY", this );
    angCmd_z = new G4UIcmdWithADoubleAndUnit( "/placement/rotateZ", this );

    angCmd_x->SetGuidance( "Set the angle of rotation about X-axis of the farside detector to be placed.\nUnit is in degree by default." );
    angCmd_y->SetGuidance( "Set the angle of rotation about Y-axis of the farside detector to be placed.\nUnit is in degree by default." );
    angCmd_z->SetGuidance( "Set the angle of rotation about Z-axis of the farside detector to be placed.\nUnit is in degree by default." );

    angCmd_x->AvailableForStates( G4State_Idle );
    angCmd_y->AvailableForStates( G4State_Idle );
    angCmd_z->AvailableForStates( G4State_Idle );

    angCmd_x->SetParameterName( "Xangle", false );
    angCmd_y->SetParameterName( "Yangle", false );
    angCmd_z->SetParameterName( "Zangle", false );

    angCmd_x->SetDefaultValue( 0. );
    angCmd_y->SetDefaultValue( 0. );
    angCmd_z->SetDefaultValue( 0. );

    angCmd_x->SetDefaultUnit( "deg" );
    angCmd_y->SetDefaultUnit( "deg" );
    angCmd_z->SetDefaultUnit( "deg" );

    place_detector = new G4UIcommand( "/placement/placeDetector", this );
    place_detector->SetGuidance( "Place a far-side detector based on the previously specified positions and angles." );
    place_detector->AvailableForStates( G4State_Idle );


    filterPosCmd = new G4UIcmdWith3VectorAndUnit( "/placement/filter_pos", this );
    filterPosCmd->SetGuidance( "Set the position of the filter.\nUnit is in cm by default.");
    filterPosCmd->SetParameterName( "x", "y", "z", false );
    filterPosCmd->AvailableForStates( G4State_Idle );
    filterPosCmd->SetDefaultValue( G4ThreeVector( 0, 100*CLHEP::cm, 0) );
    filterPosCmd->SetDefaultUnit( "cm" );

    filterPolarCmd = new G4UIcmdWith3Vector( "/placement/filter_polar", this);
    filterPolarCmd->SetGuidance( "Set the position of the filter by cylindrical coordinate.\nThis command does not accept user input unit and the internal unit for distance is cm and that for angle is degree.\n");
    filterPolarCmd->SetParameterName( "r", "phi", "z", false );
    filterPolarCmd->AvailableForStates( G4State_Idle );
    filterPolarCmd->SetDefaultValue( G4ThreeVector(100,0,0) );

    filterAngCmd_x = new G4UIcmdWithADoubleAndUnit( "/placement/filter_rotateX", this );
    filterAngCmd_y = new G4UIcmdWithADoubleAndUnit( "/placement/filter_rotateY", this );
    filterAngCmd_z = new G4UIcmdWithADoubleAndUnit( "/placement/filter_rotateZ", this );

    filterAngCmd_x->SetGuidance( "Set the angle of rotation about X-axis of the filter.\nUnit is in degree by default." );
    filterAngCmd_y->SetGuidance( "Set the angle of rotation about Y-axis of the filter.\nUnit is in degree by default." );
    filterAngCmd_z->SetGuidance( "Set the angle of rotation about Z-axis of the filter.\nUnit is in degree by default." );

    filterAngCmd_x->AvailableForStates( G4State_Idle );
    filterAngCmd_y->AvailableForStates( G4State_Idle );
    filterAngCmd_z->AvailableForStates( G4State_Idle );

    filterAngCmd_x->SetParameterName( "Xangle", false );
    filterAngCmd_y->SetParameterName( "Yangle", false );
    filterAngCmd_z->SetParameterName( "Zangle", false );

    filterAngCmd_x->SetDefaultValue( 0. );
    filterAngCmd_y->SetDefaultValue( 0. );
    filterAngCmd_z->SetDefaultValue( 0. );

    filterAngCmd_x->SetDefaultUnit( "deg" );
    filterAngCmd_y->SetDefaultUnit( "deg" );
    filterAngCmd_z->SetDefaultUnit( "deg" );

    place_filter = new G4UIcmdWith3VectorAndUnit( "/placement/placeFilter", this );
    place_filter->SetGuidance( "Place a filter based on the previously specified positions and angles." );
    place_filter->SetParameterName( "ID", "OD", "Height", false );
    place_filter->AvailableForStates( G4State_Idle );
    place_filter->SetDefaultValue( G4ThreeVector( 0.635*CLHEP::cm, 10*CLHEP::cm, 0) );
    place_filter->SetDefaultUnit( "cm" );
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

DetectorConstructionMessenger::~DetectorConstructionMessenger(){
//    delete FSDistanceCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void DetectorConstructionMessenger::SetNewValue( G4UIcommand* command, G4String newValue) {

    if( command==posCmd ){
        detector->SetFarSidePosition( posCmd->GetNew3VectorValue( newValue ) );
    }
    else if( command==polarCmd ){
        G4ThreeVector p = polarCmd->GetNew3VectorValue( newValue );
        G4double r = p.x()*CLHEP::cm;
        G4double z = p.z()*CLHEP::cm;
        G4double phi = p.y()*CLHEP::deg;
        detector->SetFarSidePosition( G4ThreeVector(r*cos(phi), r*sin(phi), z) );
    }
    else if( command==angCmd_x ){
        detector->FarSideRotateX( angCmd_x->GetNewDoubleValue( newValue) );
    }
    else if( command==angCmd_y ){
        detector->FarSideRotateY( angCmd_y->GetNewDoubleValue( newValue) );
    }
    else if( command==angCmd_z ){
        detector->FarSideRotateZ( angCmd_z->GetNewDoubleValue( newValue) );
    }
    else if( command==place_detector ){
        detector->PlaceFarSideDetector();
    }
    else if( command==filterPosCmd ){
        detector->SetFilterPosition( filterPosCmd->GetNew3VectorValue( newValue ) );
    }
    else if( command==filterPolarCmd ){
        G4ThreeVector p = filterPolarCmd->GetNew3VectorValue( newValue );
        G4double r = p.x()*CLHEP::cm;
        G4double z = p.z()*CLHEP::cm;
        G4double phi = p.y()*CLHEP::deg;
        detector->SetFilterPosition( G4ThreeVector(r*cos(phi), r*sin(phi), z) );
    }
    else if( command==filterAngCmd_x ){
        detector->FilterRotateX( filterAngCmd_x->GetNewDoubleValue( newValue) );
    }
    else if( command==filterAngCmd_y ){
        detector->FilterRotateY( filterAngCmd_y->GetNewDoubleValue( newValue) );
    }
    else if( command==filterAngCmd_z ){
        detector->FilterRotateZ( filterAngCmd_z->GetNewDoubleValue( newValue) );
    }
    else if( command==place_filter ){
        detector->PlaceFilter( place_filter->GetNew3VectorValue( newValue) );
    }
    return;
}
