
/// \file JanisActionInitialization.cc
/// \brief Implementation of the JanisActionInitialization class

#include "JanisActionInitialization.hh"
#include "JanisDDGeneratorAction.hh"
#include "JanisSteppingAction.hh"
#include "JanisDetectorConstruction.hh"
#include "JanisTrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JanisActionInitialization::JanisActionInitialization
							(JanisDetectorConstruction* detConstruction, G4String s)
 : G4VUserActionInitialization(), fname(s),
 fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

JanisActionInitialization::~JanisActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JanisActionInitialization::BuildForMaster() const
{
  SetUserAction(new JanisRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void JanisActionInitialization::Build() const
{
  SetUserAction(new JanisDDGeneratorAction);

  //note that this method is const, so cannot do any assignment operation such as assigning newly allocated action classes to private pointer members.
  //runAction->setOutputFileName( fname );
  //SetUserAction(runAction);

  SetUserAction( new JanisRunAction);
  SetUserAction( new JanisEventAction(runAction));
  SetUserAction(new JanisTrackingAction(eventAction));
  SetUserAction(new JanisSteppingAction(fDetConstruction, eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
