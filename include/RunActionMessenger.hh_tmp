
/// \file JanisRunActionMessenger.hh
/// \brief Definition of the JanisRunActionMessenger class

#ifndef JanisRunActionMessenger_h
#define JanisRunActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class JanisRunAction;
class G4UIdirectory;
class G4UIcmdWithAString;

class JanisRunActionMessenger: public G4UImessenger
{
    public:
        JanisRunActionMessenger(JanisRunAction* );
        virtual ~JanisRunActionMessenger();

        virtual void SetNewValue(G4UIcommand*, G4String);

      private:
        JanisRunAction* SetFileName;

        G4UIdirectory* SetFileNameDir;
        G4UIcmdWithAString* FileNameCmd;

};

#endif
