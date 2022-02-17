///////////////////////////////////////////////////////////////////
// MaterialStepRecorder.cxx, (c) ATLAS Detector software
///////////////////////////////////////////////////////////////////

#include "SimpleMaterialStepRecorder/MaterialStepRecorder.h"
#include "TrkGeometry/MaterialStep.h"
#include <iostream>
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/INTupleSvc.h" 
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/SmartDataPtr.h"
#include "GaudiKernel/MsgStream.h"
#include "SimHelpers/ServiceAccessor.h"
#include "StoreGate/StoreGateSvc.h"
#include "G4Step.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4StepPoint.hh"
#include "G4TouchableHistory.hh"
#include "G4LogicalVolume.hh"
#include <climits>
#include <cmath>


MaterialStepRecorder::MaterialStepRecorder()
:  AthMessaging(Gaudi::svcLocator()->service< IMessageSvc >( "MessageSvc" ),"MaterialStepRecorder"),
   m_evtStore("StoreGateSvc/StoreGateSvc","MaterialStepRecorder"), //FIXME name should be passed in via a Config struct rather than hardcoded.
   m_detStore("StoreGateSvc/DetectorStore","MaterialStepRecorder") //FIXME name should be passed in via a Config struct rather than hardcoded.
{}


void MaterialStepRecorder::BeginOfEventAction(const G4Event*)
{

  ATH_MSG_DEBUG(" BeginOfEventAction");
  m_Step_Length.clear();
  m_Step_X0.clear();
  m_Step_L0.clear();
  m_Step_Rho.clear();
  m_Step_PosX.clear();
  m_Step_PosY.clear();
  m_Step_PosZ.clear();

}


void MaterialStepRecorder::EndOfEventAction(const G4Event*)
{

  ATH_MSG_DEBUG(" EndOfEventAction");

  MaterialTree->Fill();

}


void MaterialStepRecorder::BeginOfRunAction(const G4Run*)
{

  ATH_MSG_DEBUG(" BeginOfRunAction");

  OutputFile = new TFile("GeantinoNtuple.root","recreate");

  MaterialTree = new TTree("MaterialTree","");

  MaterialTree->Branch("Step_Length",&m_Step_Length);
  MaterialTree->Branch("Step_X0",&m_Step_X0);
  MaterialTree->Branch("Step_L0",&m_Step_L0);
  MaterialTree->Branch("Step_Rho",&m_Step_Rho);
  MaterialTree->Branch("Step_PosX",&m_Step_PosX);
  MaterialTree->Branch("Step_PosY",&m_Step_PosY);
  MaterialTree->Branch("Step_PosZ",&m_Step_PosZ);

}


void MaterialStepRecorder::EndOfRunAction(const G4Run*)
{

  ATH_MSG_DEBUG(" BeginOfRunAction");

  OutputFile->cd();
  MaterialTree->Write();
  OutputFile->Close();


}


void MaterialStepRecorder::UserSteppingAction(const G4Step* aStep)
{

  // kill secondaries
  if (aStep->GetTrack()->GetParentID()) {
      aStep->GetTrack()->SetTrackStatus(fStopAndKill);
      return;
  }

  // the material information
  G4TouchableHistory* touchHist = (G4TouchableHistory*)aStep->GetPreStepPoint()->GetTouchable();
  // G4LogicalVolume
  G4LogicalVolume *lv= touchHist ? touchHist->GetVolume()->GetLogicalVolume() : 0;
  G4Material *mat    = lv ? lv->GetMaterial() : 0;

  // log the information // cut off air
  if (mat && mat->GetRadlen() < 200000) {

    // the step information
    double steplength     = aStep->GetStepLength();

    // the position information
    G4ThreeVector pos     = aStep->GetPreStepPoint()->GetPosition();

    double X0             = mat->GetRadlen();
    double L0             = mat->GetNuclearInterLength();
    double rho            = mat->GetDensity()*CLHEP::mm3/CLHEP::gram;

    // Only store before Magnet
    if(pos.perp() < 1100.0) {

      m_Step_Length.push_back(steplength);
      m_Step_X0.push_back(X0);
      m_Step_L0.push_back(L0);
      m_Step_Rho.push_back(rho);
      m_Step_PosX.push_back(pos.x());
      m_Step_PosY.push_back(pos.y());
      m_Step_PosZ.push_back(pos.z());
    }
  }
}
