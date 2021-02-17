/// \file DetectorConstructionMessenger.hh
/// \brief Definition of the DetectorConstructionMessenger class

#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

#include "globals.hh"
#include "CLHEP/Units/PhysicalConstants.h"
#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;

class DetectorConstructionMessenger: public G4UImessenger{

public:

    DetectorConstructionMessenger( DetectorConstruction* );
    virtual ~DetectorConstructionMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

private:

    DetectorConstruction* detector;

    G4UIdirectory* directory;

    // Far-side detector-related commands.

    G4UIcmdWith3VectorAndUnit* posCmd;
        // Command to specify position of the farside detector
    G4UIcmdWith3Vector* polarCmd;
        // Command to specify position of the farside detector by polar/cylindrical coordinate.
        // The unit is cm. Order is r (in X-Y plane, phi, z).
    G4UIcmdWithADoubleAndUnit* angCmd_x;
    G4UIcmdWithADoubleAndUnit* angCmd_y;
    G4UIcmdWithADoubleAndUnit* angCmd_z;
        // Command to specify angle of rotation the farside detector
    G4UIcommand* place_detector;

    // Filter/collimator related commands.

    G4UIcmdWith3VectorAndUnit* filterPosCmd;
        // Command to specify position of the farside detector
    G4UIcmdWith3Vector* filterPolarCmd;
        // Command to specify position of the farside detector by polar/cylindrical coordinate.
        // The unit is cm. Order is r (in X-Y plane, phi, z).
    G4UIcmdWithADoubleAndUnit* filterAngCmd_x;
    G4UIcmdWithADoubleAndUnit* filterAngCmd_y;
    G4UIcmdWithADoubleAndUnit* filterAngCmd_z;
        // Command to specify angle of rotation the farside detector
    G4UIcmdWith3VectorAndUnit* place_filter;
};

#endif
