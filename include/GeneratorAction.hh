
// $Id: GeneratorAction.hh $
//
/// \file GeneratorAction.hh
/// \brief Definition of the GeneratorAction class

#ifndef GeneratorAction_h
#define GeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4VPhysicalVolume.hh"

class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;
class GeneratorMessenger;

class GeneratorAction : public G4VUserPrimaryGeneratorAction {

public:
    GeneratorAction();
    virtual ~GeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

    //void setGeneratorDistance(G4double);
    //void setGeneratorAngle(G4double);

private:
    GeneratorMessenger* primaryGeneratorMessenger;

    //G4double generator_distance;
    //G4double generator_angle;
    //G4String generator_mode;

    //G4ParticleGun*  fParticleSource;
    G4GeneralParticleSource*  fgps;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
