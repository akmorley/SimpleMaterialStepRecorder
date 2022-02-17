//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb  6 09:02:47 2015 by ROOT version 5.34/21
// from TTree MaterialTree/
// found on file: GeantinoNtuple.root
//////////////////////////////////////////////////////////

#ifndef Reader_h
#define Reader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.
using namespace std;

class Reader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   vector<double>  *Step_Length;
   vector<double>  *Step_X0;
   vector<double>  *Step_L0;
   vector<double>  *Step_Rho;
   vector<double>  *Step_PosX;
   vector<double>  *Step_PosY;
   vector<double>  *Step_PosZ;

   // List of branches
   TBranch        *b_Step_Length;   //!
   TBranch        *b_Step_X0;   //!
   TBranch        *b_Step_L0;   //!
   TBranch        *b_Step_Rho;   //!
   TBranch        *b_Step_PosX;   //!
   TBranch        *b_Step_PosY;   //!
   TBranch        *b_Step_PosZ;   //!

   Reader(TTree *tree=0);
   virtual ~Reader();
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Reader_cxx
Reader::Reader(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f =0;// (TFile*)gROOT->GetListOfFiles()->FindObject("GeantinoNtuple.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("GeantinoNtuple.root");
      }
      f->GetObject("MaterialTree",tree);

   }
   Init(tree);
}

Reader::~Reader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Reader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Reader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Reader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Step_Length = 0;
   Step_X0 = 0;
   Step_L0 = 0;
   Step_Rho = 0;
   Step_PosX = 0;
   Step_PosY = 0;
   Step_PosZ = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Step_Length", &Step_Length, &b_Step_Length);
   fChain->SetBranchAddress("Step_X0", &Step_X0, &b_Step_X0);
   fChain->SetBranchAddress("Step_L0", &Step_L0, &b_Step_L0);
   fChain->SetBranchAddress("Step_Rho", &Step_Rho, &b_Step_Rho);
   fChain->SetBranchAddress("Step_PosX", &Step_PosX, &b_Step_PosX);
   fChain->SetBranchAddress("Step_PosY", &Step_PosY, &b_Step_PosY);
   fChain->SetBranchAddress("Step_PosZ", &Step_PosZ, &b_Step_PosZ);
   Notify();
}

Bool_t Reader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Reader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

#endif // #ifdef Reader_cxx
