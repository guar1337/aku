#include <iostream>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include "constants.h"
#include "dE_E_angle.h"
#include "muchobojca.h"


R__LOAD_LIBRARY(libPhysics.so); // !! IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** instead of
R__LOAD_LIBRARY(libgsl.so); //**R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
R__LOAD_LIBRARY(/home/guar/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);

bool doorman()
{
	/*
	TString cur_dir;
	switch (s::runNo)
	{
		case 0:
			cur_dir = s::dir_CsI;
			//wrk(s::s_inFname.Data(), cur_dir);
			//return 1;
			break;

		case 10:
			cur_dir = s::dir_runs.Copy().Append("/geo1").Data();
			break;

		case 12:
			cur_dir = s::dir_runs.Copy().Append("/geo1").Data();
			break;

		case 2:
			cur_dir = s::dir_runs.Copy().Append("/geo2").Data();
			break;

		case 3:
			cur_dir = s::dir_runs.Copy().Append("/geo3").Data();
			break;

		case 4:
			cur_dir = s::dir_runs.Copy().Append("/geo4").Data();
			break;

		default:
			printf("\ndoorman->Error: Wrong run number\n");
			return 0;
			break;
	}//switch


	gSystem->cd(cur_dir.Data());
	TString inFname(s::s_inFname.Copy().Append(".root").Prepend("cal_").Data());
	TString outFname(inFname.Copy().ReplaceAll("cal_","dE_").Data());
	TFile *inF= new TFile((inFname.Data()), "READ");
	TFile *outF = new TFile(outFname.Data(),"recreate");
	if (!inF->IsZombie())
	{
		printf("%sSuccesfully opened file %s%s\n", "\x1B[32m", inFname.Data(),"\x1b[0m");
	}
	else {return 0;}
TTree *inTree = (TTree*)inF->Get("calibrated");
TTree *outTree= new TTree("dE_E","he6");



*/

//	He'd be happy to get just the run number LATER
//as for now I have dE_E_angle class inside Mr_Blue_Sky, but we need to set our ways apart
//dE_E_angle *Hermes= new dE_E_angle(inTree,outTree, inFname);
maynard = new TOOL();
maynard->sigHandler("raw");
/*
Hermes->actual_work();

inF->Close();
outF->cd();
outTree->Write();
outF->Close();
*/
return 1;
}