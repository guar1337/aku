#include <iostream>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include "constants.h"
#include "dE_E_angle.h"


R__LOAD_LIBRARY(libPhysics.so); // !! IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** instead of
R__LOAD_LIBRARY(libgsl.so); //**R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
R__LOAD_LIBRARY(/home/guar/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);

void doorman()
{
	gSystem->cd(s::CsI_dir.Data()); 
	TString inFname(s::inFname.Copy().Append(".root").Data());
	TString outFname(inFname.Copy().ReplaceAll("cal_","dE_").Data());
	TFile *inF= new TFile((inFname.Data()), "READ");
	TFile *outF = new TFile(outFname.Data(),"recreate");
	if (!inF->IsZombie())
	{
		printf("Succesfully opened file %s\n",inFname.Data());
	}
	else {return 0;}
TTree *inTree = (TTree*)inF->Get("calibrated");
TTree *outTree= new TTree("dE_E","he6");





//	He'd be happy to get just the run number LATER
//as for now I have dE_E_angle class inside Mr_Blue_Sky, but we need to set our ways apart
dE_E_angle *Hermes= new dE_E_angle(inTree,outTree);

Hermes->actual_work();

inF->Close();
outF->cd();
outTree->Write();
outF->Close();
}