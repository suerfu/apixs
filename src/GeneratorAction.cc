//
/// \file GeneratorAction.cc
/// \brief Implementation of the GeneratorAction class

#include "GeneratorAction.hh"
#include "GeneratorMessenger.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
#include "G4IonTable.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


GeneratorAction::GeneratorAction() : G4VUserPrimaryGeneratorAction() {
    //fParticleSource = new G4ParticleGun();
    fgps = new G4GeneralParticleSource();
        // GPS must be initialized here.

    primaryGeneratorMessenger = new GeneratorMessenger(this);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


GeneratorAction::~GeneratorAction(){
    //delete fParticleSource;
    delete primaryGeneratorMessenger;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void GeneratorAction::GeneratePrimaries(G4Event* anEvent){
    fgps->GeneratePrimaryVertex(anEvent);
}
