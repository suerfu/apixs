// $Id: GeneratorMessenger.cc $
//
/// \file GeneratorMessenger.cc
/// \brief Definition of the GeneratorMessenger class

#include "GeneratorMessenger.hh"

#include "GeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"

GeneratorMessenger::GeneratorMessenger( GeneratorAction* generator )
  : G4UImessenger(),
    primaryGenerator(generator),
    primaryGeneratorDir(0)
{
/*
	primaryGeneratorDir = new G4UIdirectory("/generator/");
	primaryGeneratorDir->SetGuidance("Generator position control.");

	generatorDistanceCmd = new G4UIcmdWithADouble("/generator/setDistance", this);
	generatorDistanceCmd->SetGuidance("Set distance between the target helium and  generator in unit of cm");
	generatorDistanceCmd->SetParameterName("distance", false);
	generatorDistanceCmd->SetDefaultValue(60);
	generatorDistanceCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  generatorAngleCmd = new G4UIcmdWithADouble("/generator/setAngle", this);
  generatorAngleCmd->SetGuidance("Set azimuth angle of the generator");
	generatorAngleCmd->SetParameterName("pmt_angle", false);
	generatorAngleCmd->SetDefaultValue(45);
	generatorAngleCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  generatorModeCmd = new G4UIcmdWithAString("/generator/setMode", this);
  generatorModeCmd->SetGuidance("Select gammas or neutrons");
  generatorModeCmd->SetParameterName("mode", true);
  generatorModeCmd->SetDefaultValue("neutrons");
  generatorModeCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GeneratorMessenger::~GeneratorMessenger(){
/*
    delete generatorDistanceCmd;
    delete generatorModeCmd;
    delete primaryGeneratorDir;
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue){
/*
	if( command == generatorDistanceCmd )
	{
		G4cout << "Setting generator distance to " << newValue << G4endl;
		primaryGenerator->setGeneratorDistance(generatorDistanceCmd->GetNewDoubleValue(newValue));
	}

  if( command == generatorAngleCmd )
  {
    G4cout << "Setting generator azimuth angle to " << newValue << G4endl;
    primaryGenerator->setGeneratorAngle(generatorAngleCmd->GetNewDoubleValue(newValue));
  }

  if( command == generatorModeCmd )
  {
    if(newValue != "gammas" && newValue != "neutrons")
    {
      G4cout << "\n ERROR! Bad generator mode definition: " << newValue << G4endl;
      return;
    }
    G4cout << "Setting generator mode to " << newValue << G4endl;
    primaryGenerator->SetGeneratorMode(newValue);
  }
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
