///////////////////////////////////////////////////////////////////
// MaterialStepRecorder.h, (c) ATLAS Detector software
///////////////////////////////////////////////////////////////////

#ifndef MaterialStepRecorder_H
#define MaterialStepRecorder_H

#include <string>
#include <vector>


#include "StoreGate/StoreGateSvc.h"
#include "GaudiKernel/ServiceHandle.h"

#include "AthenaBaseComps/AthMessaging.h"

#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserSteppingAction.hh"

#include "TTree.h"
#include "TFile.h"

/** @class MaterialStepRecorder

*/


class MaterialStepRecorder: public AthMessaging, public G4UserEventAction,
                            public G4UserRunAction, public G4UserSteppingAction {

  public:
    MaterialStepRecorder();

    /** All G4 interface methods */
    void BeginOfEventAction(const G4Event*);
    void EndOfEventAction(const G4Event*);
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    void UserSteppingAction(const G4Step*);

  private:

    typedef ServiceHandle<StoreGateSvc> StoreGateSvc_t;
     /// Pointer to StoreGate (event store by default)
     mutable StoreGateSvc_t m_evtStore;
     /// Pointer to StoreGate (detector store by default)
     mutable StoreGateSvc_t m_detStore;


    TFile * OutputFile;
    TTree * MaterialTree;

    std::vector<double> m_Step_Length;
    std::vector<double> m_Step_X0;
    std::vector<double> m_Step_L0;
    std::vector<double> m_Step_Rho;
    std::vector<double> m_Step_PosX;
    std::vector<double> m_Step_PosY;
    std::vector<double> m_Step_PosZ;

};

#endif

