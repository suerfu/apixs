
/// \file JanisActionInitialization.hh
/// \brief Definition of the JanisActionInitialization class

#ifndef JanisActionInitialization_h
#define JanisActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"

#include "JanisRunAction.hh"
#include "JanisEventAction.hh"

#include <sstream>

class JanisDetectorConstruction;

class JanisActionInitialization : public G4VUserActionInitialization
{
  public:

    JanisActionInitialization(JanisDetectorConstruction*, G4String fname);
    virtual ~JanisActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

    void AddMacro( G4String s){
        if( runAction!=0 )
            runAction->AddMacro( s );
    }
    void AddRandomSeeds( long seeds[], int len){
        if( runAction!=0 )
            runAction->AddRandomSeeds( seeds, len );
    }

  private:

    G4String fname;
  	JanisDetectorConstruction* fDetConstruction;

    JanisRunAction* runAction;
    JanisEventAction* eventAction;

};

#endif
