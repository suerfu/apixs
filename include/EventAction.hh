/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "StepInfo.hh"
#include "RunAction.hh"

class EventAction : public G4UserEventAction{

public:

    EventAction( RunAction* input_run_action );
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    vector<StepInfo>& GetStepCollection();

private:
     
    RunAction* run_action;
    
    TTree* data_tree;
    
    // methods
    void PrintEventStatistics() const;

    bool if_center;
    bool if_farside;


    int eventID;
    int trackID;
    int stepID;
    int parentID;

    G4String tmp_particle_name;
    G4String tmp_volume_name;
    G4String tmp_process_name;
    //int volume_copy_number;

    G4ThreeVector position;
    G4ThreeVector momentum;

    double x;
    double y;
    double z;
    double theta;
    double phi;

    double px;
    double py;
    double pz;

    double global_time;

    double Eki;
    double Ekf;
    double edep;

    int max_char_len;
    char particle_name[16];
    char volume_name[16];
    char process_name[16];


    vector<StepInfo> stepCollection;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
