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

void butler()
{

	TString dir_cur;
	switch (s::runNo)
	{
		case 0:
			dir_cur = s::dir_CsI;
			//wrk(s::inFname.Data(), dir_cur);
			return 1;
			break;

		case 1:
			dir_cur = s::dir_runs.Copy().Append("/geo1").Data();
			break;

		case 2:
			dir_cur = s::dir_runs.Copy().Append("/geo2").Data();
			break;

		case 3:
			dir_cur = s::dir_runs.Copy().Append("/geo3").Data();
			break;

		case 4:
			dir_cur = s::dir_runs.Copy().Append("/geo4").Data();
			break;

		default:
			printf("\nError: WTF amigo\n");
			return 0;
			break;
	}

gSystem->cd(dir_cur.Data());
TSystemDirectory *dir_data = new TSystemDirectory("data", dir_cur.Data());
printf("Entering directory: %s\nLooping over following files:\n",dir_cur.Data());
TIter bluster(dir_data->GetListOfFiles());
while (TObject *obj = bluster())
{
	TString inFname = obj->GetName();
	if (inFname.Contains("cal_")) 
	{
		printf("%s\n",inFname.Data());
	}
}
TIter next(dir_data->GetListOfFiles());
while (TObject *obj = next())
{
	TString inFname = obj->GetName();
	TString outFname = inFname.Copy().ReplaceAll("cal_", "").Prepend("dE_");

	if (inFname.Contains("cal_")) 
	{
		TFile *inF= new TFile((inFname.Data()), "READ");
		TFile *outF = new TFile(outFname.Data(),"recreate");
		if (!inF->IsZombie())
		{
			printf("Succesfully opened file %s\n",inFname.Data());
		}
		else {return 0;}
		TTree *inTree = (TTree*)inF->Get("calibrated");
		TTree *outTree= new TTree("dE_E","he6");
		dE_E_angle *Hermes= new dE_E_angle(inTree,outTree, inFname);
		Hermes->actual_work();
		inF->Close();
		outF->cd();
		outTree->Write();
		outF->Close();
	}
}//file list iterator



//	He'd be happy to get just the run number LATER
//as for now I have dE_E_angle class inside Mr_Blue_Sky, but we need to set our ways apart
//dE_E_angle *Hermes= new dE_E_angle(inTree,outTree);
}
