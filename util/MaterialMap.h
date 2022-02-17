#include "TFile.h"
#include "TH2.h"
#include "TF1.h"
#include "TF2.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TMath.h"
#include "TColor.h"
#include "TStyle.h"
#include "TVector.h"
#include "TError.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"
#include "TVector3.h"
#include "TTree.h"
#include "TChain.h"

#include <vector>
#include <cmath>
#include <iostream>

#include "Reader.h"

TFile * InputFile;
TFile * OutFile;

TTree * tree;
TChain * MatChain;
Reader * mR;

TH2D * h_MatMap_ZR;
TH2D * h_MatMap_ZR_Norm;

TH2D * h_MatMap_ZR_Had;
TH2D * h_MatMap_ZR_Had_Norm;

TH2D * h_MatMap_XY;

TH1D * h_Eta_R0_Rad;
TH1D * h_Eta_R0_Had;
TH1D * h_Eta_R0_Rad_Norm;
TH1D * h_Eta_R0_Had_Norm;

TH1D * h_Eta_R1_Rad;
TH1D * h_Eta_R1_Had;
TH1D * h_Eta_R1_Rad_Norm;
TH1D * h_Eta_R1_Had_Norm;

TH1D * h_Eta_R2_Rad;
TH1D * h_Eta_R2_Had;
TH1D * h_Eta_R2_Rad_Norm;
TH1D * h_Eta_R2_Had_Norm;

TH1D * h_Eta_IBL_Rad;
TH1D * h_Eta_IBL_Had;
TH1D * h_Eta_IBL_Rad_Norm;
TH1D * h_Eta_IBL_Had_Norm;



int main(int argc, char* argv[]);

void Init();
void Write();
void Process();

void MakeChain(TString inputDir);
std::vector<TString> getFileNames(TString dirName);

