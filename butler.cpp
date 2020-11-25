#include <iostream>
#include <TSystemDirectory.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include <TStopwatch.h>
#include <TCutG.h>

#include "constants.h"
#include "dE_E_angle.h"
#include "muchobojca.h"
#include "calibrate_tree.h"

// !! IF NOT WORKING, TRY **gSystem->Load("/home/zalewski/Desktop/Eloss/trial/libelo.so");** 
//instead of
R__LOAD_LIBRARY(libgsl.so);
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/libMr_Blue_Sky.so);
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC/build/libEloss.so);

bool butler()
{
	Double_t qualityControl[4];
	Double_t inputPars[]{6.33544,7.7553,6.7597,0.0};
	TStopwatch time{};
	TString sourceDir, destinationDir, s_fnamePrefix, s_outFName;
	TString s_outTreeName, s_inTreeName, str_name;
	TTree *inT, *outT;
	TFile *inF, *outF;

	//Don't remove it, it has to be here, but I don't know why
	//some linking problem 
	TCutG *blaha = new TCutG();
	if (cs::inDir.Contains("raw"))
	{
		s_inTreeName = "AnalysisxTree";
		s_fnamePrefix = "cln";
		s_outTreeName = "cleaned";
	}

	else if (cs::inDir.Contains("cln"))
	{
		s_inTreeName = "cleaned";
		s_fnamePrefix = "cal";
		s_outTreeName = "calibrated";
	}

	else if (cs::inDir.Contains("cal"))
	{
		s_inTreeName = "calibrated";
		s_fnamePrefix = "dE";
		s_outTreeName = "dE_angle";
	}

	else
	{
		printf("Incorrect destination file: %s\n", cs::inDir.Data());
		return 0;
	}

	sourceDir = cs::dir_runs + cs::inDir + "/geo" + std::to_string(cs::runNo) + "/";	
	destinationDir = sourceDir.Copy().ReplaceAll(cs::inDir,s_fnamePrefix);
	TSystemDirectory source_dir_data{"data", sourceDir.Data()};
	TIter bluster = source_dir_data.GetListOfFiles();
	while (TObject *obj = bluster())
	{			
		str_name = obj->GetName();
		s_outFName = str_name.Copy().ReplaceAll(cs::inDir.Data(),s_fnamePrefix.Data());
		//printf("%s\n", s_outFName.Data());
		
		if (str_name.Contains(".root") && str_name.Contains(cs::inDir.Data()))
		{
			printf("%s%s%s\t%i%s%s\n", "\x1B[32m", "\e[1m", str_name.Data(), str_name.Atoi(), "\x1b[0m", "\e[0m");
			inF = new TFile{(sourceDir+str_name).Data(), "READ"};
			inT = (TTree*)inF->Get(s_inTreeName.Data());
			outF = new TFile{destinationDir+s_outFName, "RECREATE"};
			//printf("%s\n", (destinationDir+s_outFName).Data());
			outT= new TTree{s_outTreeName.Data(),s_outTreeName.Data()};

			if (cs::inDir=="raw")
			{
				muchobojca *MrMuscle = new muchobojca();
				MrMuscle->wrk(inT, outT);
			}

			else if(cs::inDir=="cln")
			{
				calibrate_tree 	*Kali = new calibrate_tree();
				Kali->wrk(inT, outT);
			}
			
			else if(cs::inDir=="cal")
			{
				dE_E_angle *Hermes = new dE_E_angle(inT,outT, str_name, cs::runNo);
				(cs::runNo == 5) ? Hermes->actual_work_gas() : Hermes->actual_work(inputPars, qualityControl, cs::runNo);
			}

			outT->Write();
			delete outF, inF;
		}
	}
	printf("I was working for %.2f seconds\n", time.RealTime());
	return 1;
}
