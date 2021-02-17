
/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Neutron.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "StepInfo.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction( const DetectorConstruction* detectorConstruction, EventAction* eventAction)
      : G4UserSteppingAction(),
        fDetConstruction(detectorConstruction),
        fEventAction(eventAction){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step){

    // Collect energy and number of scatters step by step
    // Don't save the out of world step
    if(!step->GetPostStepPoint()->GetPhysicalVolume()) return;

//    if( step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()!="Transportation" )
        fEventAction->GetStepCollection().push_back(StepInfo(step));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
