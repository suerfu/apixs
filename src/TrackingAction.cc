//
/// \file /src/TrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "TrackingAction.hh"
#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"

#include "StepInfo.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackingAction::TrackingAction(EventAction* eventAction)
  : G4UserTrackingAction(),
    fEventAction(eventAction){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackingAction::PreUserTrackingAction(const G4Track* track){

  // We have to set up the initStep by hand
  StepInfo stepInfo;

  stepInfo.SetEventID(G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID());
  stepInfo.SetTrackID(track->GetTrackID());
  stepInfo.SetStepID( /*0*/ track->GetCurrentStepNumber() );
  stepInfo.SetParentID(track->GetParentID());
  stepInfo.SetParticleName(track->GetParticleDefinition()->GetParticleName());
  stepInfo.SetVolumeName(track->GetVolume()->GetName());
  stepInfo.SetVolumeCopyNumber(track->GetVolume()->GetCopyNo());
  stepInfo.SetEki(track->GetKineticEnergy());
  stepInfo.SetEkf(track->GetKineticEnergy());
  stepInfo.SetPosition(track->GetPosition());
  stepInfo.SetMomentumDirection(track->GetMomentumDirection());
  stepInfo.SetGlobalTime(track->GetGlobalTime());
  stepInfo.SetProcessName("initStep");

  fEventAction->GetStepCollection().push_back(stepInfo);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
