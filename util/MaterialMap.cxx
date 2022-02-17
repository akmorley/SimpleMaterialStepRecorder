#include "MaterialMap.h"

/*
const int nBinsR = 5000;
const double MaxR = 500.0;

const int nBinsZ = 3000;
const double MaxZ = 1500.0;
*/

//const int nBinsR = 800;
//const double MaxR = 400.0;

const int nBinsR = 1600;
const double MaxR = 400.0;

const int nBinsZ = 3000;
const double MaxZ = 1500.0;

int main(int argc, char* argv[]) {

	std::cout << "Starting MaterialMap!" << std::endl;

  if( argc !=3 ){
    std::cout << "Incorrect number of arguments passed" <<std::endl;
    std::cout << "First argument  -- path to folder containing input ntuple" <<  std::endl;
    std::cout << "Second argument  -- name of output file" <<  std::endl;
  } else {
    std::cout << "Reading in files from " <<  argv[1] <<std::endl;
    std::cout << "Outputing in histograms " <<  argv[2] <<std::endl;
  }

  MakeChain( TString( argv[1] ) );
  
	mR = new Reader(MatChain);
	OutFile = new TFile( TString( argv[2] ) ,"recreate");

	Init();

	Process();

	Write();


	std::cout << "Tidy..." << std::endl;

	delete mR;

	OutFile->Close();
	

	std::cout << "Done!" << std::endl;

}

void MakeChain(TString inputDir) {

  std::cout << "Read files from: " << inputDir << std::endl;
  std::cout << "Making Chains..." << std::endl;

	MatChain = new TChain("MaterialTree","");

	std::vector<TString> fileNames = getFileNames(inputDir);
	std::vector<TString>::iterator fileNameItr;
  
  std::cout << "Processing files: ";
	for (fileNameItr=fileNames.begin(); fileNameItr!=fileNames.end(); ++fileNameItr) {

		std::cout << *fileNameItr << std::endl;
		MatChain->Add(*fileNameItr);

	}

}

void Init() {

	h_MatMap_ZR = new TH2D("h_MatMap_ZR","; z [mm]; r [mm]",nBinsZ,-MaxZ,MaxZ,nBinsR,0.0,MaxR);
	h_MatMap_ZR_Norm = (TH2D*) h_MatMap_ZR->Clone("h_MatMap_ZR_Norm");
	h_MatMap_ZR_Had = (TH2D*) h_MatMap_ZR->Clone("h_MatMap_ZR_Had");
	h_MatMap_ZR_Had_Norm = (TH2D*) h_MatMap_ZR->Clone("h_MatMap_ZR_Had_Norm");

	h_MatMap_XY = new TH2D("h_MatMap_XY","; x [mm]; y [mm]",2000,-50.0,50.0,2000,-50.0,50.0);

	h_Eta_R0_Rad = new TH1D("h_Eta_R0_Rad","; #eta; x/X_{0}",100,-2.5,2.5);

	h_Eta_R0_Had 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R0_Had");
	h_Eta_R0_Rad_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R0_Rad_Norm");
	h_Eta_R0_Had_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R0_Had_Norm");
	h_Eta_R1_Rad 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R1_Rad");
	h_Eta_R1_Had 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R1_Had");
	h_Eta_R1_Rad_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R1_Rad_Norm");
	h_Eta_R1_Had_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R1_Had_Norm");
	h_Eta_R2_Rad 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R2_Rad");
	h_Eta_R2_Had 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R2_Had");
	h_Eta_R2_Rad_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R2_Rad_Norm");
	h_Eta_R2_Had_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_R2_Had_Norm");

	h_Eta_IBL_Rad 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_IBL_Rad");
	h_Eta_IBL_Had 		= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_IBL_Had");
	h_Eta_IBL_Rad_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_IBL_Rad_Norm");
	h_Eta_IBL_Had_Norm 	= (TH1D*) h_Eta_R0_Rad->Clone("h_Eta_IBL_Had_Norm");



}

void Write() {

	OutFile->cd();

	h_MatMap_ZR->Write();
	h_MatMap_ZR_Had->Write();

	h_MatMap_XY->Write();

	h_Eta_R0_Rad->Write();
	h_Eta_R0_Had->Write();
	h_Eta_R1_Rad->Write();
	h_Eta_R1_Had->Write();
	h_Eta_R2_Rad->Write();
	h_Eta_R2_Had->Write();
	h_Eta_IBL_Rad->Write();
	h_Eta_IBL_Had->Write();
	
}

void Process() {

	const int nEvents = mR->fChain->GetEntries();

	std::cout << nEvents << " geantinos to process" << std::endl;

	double nFill = 0;

	// Loop over paths
	for(int n = 0; n < nEvents; ++n) {

		//if(n == 100000) break;

		if(n%10000 == 0) std::cout << n << " " << (double)100.*n/(double)nEvents << "% complete" << std::endl;

		mR->GetEntry(n);

		const int nSteps = mR->Step_X0->size();

		const double ZPath = (*mR->Step_PosZ)[0];

		if(fabs(ZPath) > MaxZ) continue;

		TVector3 Direction1((*mR->Step_PosX)[0],(*mR->Step_PosY)[0],(*mR->Step_PosZ)[0]);

		TVector3 Direction2((*mR->Step_PosX)[4],(*mR->Step_PosY)[4],(*mR->Step_PosZ)[4]);

		TVector3 Geantino = Direction2 - Direction1;

		double Sum_Rad_R0(0);
		double Sum_Had_R0(0);

		double Sum_Rad_R1(0);
		double Sum_Had_R1(0);

		double Sum_Rad_R2(0);
		double Sum_Had_R2(0);

    double Sum_Rad_IBL(0);
		double Sum_Had_IBL(0);


		for(int s = 0; s < nSteps; s++) {

			double X0 = (*mR->Step_X0)[s]; 
			double L0 = (*mR->Step_L0)[s]; 

			//double rho = (*mR->Step_Rho)[s]; // g/mm^3
			double len = (*mR->Step_Length)[s];

			double x = (*mR->Step_PosX)[s];
			double y = (*mR->Step_PosY)[s];
			double z = (*mR->Step_PosZ)[s];

			double r = sqrt(x*x + y*y);


			h_MatMap_XY->Fill(x,y,len/X0);

			int rBinStart = h_MatMap_ZR->GetYaxis()->FindBin(r);
			int rBinEnd = h_MatMap_ZR->GetYaxis()->FindBin(r+len);
			double nrBins = 1.0 + rBinEnd - rBinStart;


			for(int binr = rBinStart; binr <= rBinEnd; ++binr) {

				double rcen = h_MatMap_ZR->GetYaxis()->GetBinCenter(binr);

				h_MatMap_ZR->Fill(z,rcen,len/(X0*nrBins));
				h_MatMap_ZR_Had->Fill(z,rcen,len/(L0*nrBins));

			}
      
      if(r < 45.0){
        Sum_Rad_IBL += len/X0;
        Sum_Had_IBL += len/L0;
      }


			if(r < 250.0){
				Sum_Rad_R0 += len/X0;
				Sum_Had_R0 += len/L0;
			}

			if(r < 560.0){
				Sum_Rad_R1 += len/X0;
				Sum_Had_R1 += len/L0;
			}

			if(r < 1066.0){
				Sum_Rad_R2 += len/X0;
				Sum_Had_R2 += len/L0;
			}

/*
			int nStepsShare = 20;
			double ShareLen = len/nStepsShare;
			for(int l = 1; l <= nStepsShare; ++l) {

				double rpos = r + l*ShareLen;

				h_MatMap_ZR_Had->Fill(z,rpos,ShareLen/(L0));
				h_MatMap_ZR->Fill(z,rpos,ShareLen/(X0));

			}
*/

		} // Steps

		h_Eta_R0_Rad->Fill(Geantino.Eta(),Sum_Rad_R0);
		h_Eta_R0_Had->Fill(Geantino.Eta(),Sum_Had_R0);

		h_Eta_R1_Rad->Fill(Geantino.Eta(),Sum_Rad_R1);
		h_Eta_R1_Had->Fill(Geantino.Eta(),Sum_Had_R1);

		h_Eta_R2_Rad->Fill(Geantino.Eta(),Sum_Rad_R2);
		h_Eta_R2_Had->Fill(Geantino.Eta(),Sum_Had_R2);

		h_Eta_R0_Rad_Norm->Fill(Geantino.Eta());
		h_Eta_R0_Had_Norm->Fill(Geantino.Eta());

		h_Eta_R1_Rad_Norm->Fill(Geantino.Eta());
		h_Eta_R1_Had_Norm->Fill(Geantino.Eta());

		h_Eta_R2_Rad_Norm->Fill(Geantino.Eta());
		h_Eta_R2_Had_Norm->Fill(Geantino.Eta());

		h_Eta_IBL_Rad->Fill(Geantino.Eta(),Sum_Rad_IBL);
		h_Eta_IBL_Had->Fill(Geantino.Eta(),Sum_Had_IBL);

		h_Eta_IBL_Rad_Norm->Fill(Geantino.Eta());
		h_Eta_IBL_Had_Norm->Fill(Geantino.Eta());


		for(int r = 1; r <= h_MatMap_ZR->GetNbinsY(); ++r) {

			double rBin = h_MatMap_ZR->GetYaxis()->GetBinCenter(r);	
			h_MatMap_ZR_Norm->Fill(ZPath,rBin);
			h_MatMap_ZR_Had_Norm->Fill(ZPath,rBin);

		}

		nFill++;

	}	// Loop over paths

	// Re-normalise
	h_MatMap_ZR->Divide(h_MatMap_ZR_Norm);
	h_MatMap_ZR_Had->Divide(h_MatMap_ZR_Had_Norm);

	h_Eta_R0_Rad->Divide(h_Eta_R0_Rad_Norm);
	h_Eta_R0_Had->Divide(h_Eta_R0_Had_Norm);

	h_Eta_R1_Rad->Divide(h_Eta_R1_Rad_Norm);
	h_Eta_R1_Had->Divide(h_Eta_R1_Had_Norm);

	h_Eta_R2_Rad->Divide(h_Eta_R2_Rad_Norm);
	h_Eta_R2_Had->Divide(h_Eta_R2_Had_Norm);

	h_Eta_IBL_Rad->Divide(h_Eta_IBL_Rad_Norm);
	h_Eta_IBL_Had->Divide(h_Eta_IBL_Had_Norm);



}

std::vector<TString> getFileNames(TString dirName) {

	TSystemDirectory dir("*root*",dirName);
	TList *files = dir.GetListOfFiles();
	TString fileName;
	std::vector<TString> theNames;
	if(files) {
		TIter next(files);
		TSystemFile *file;
		while ((file=(TSystemFile*)next())) {
			fileName = file->GetName();
			if (fileName!="." && fileName!="..") theNames.push_back(dirName+fileName);
		}
	}
	return theNames;
}

