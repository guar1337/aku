#include <iostream>
#include <TSystemDirectory.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include "constants.h"
#include "dE_E_angle.h"
#include "muchobojca.h"


R__LOAD_LIBRARY(libPhysics.so); 
// !! IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** 
//instead of
R__LOAD_LIBRARY(libgsl.so); 
//**R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
R__LOAD_LIBRARY(/home/guar/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);

void butler()
{
	muchobojca 		*MrMuscle = new muchobojca();
	calibrate_tree 	*Kali = new calibrate_tree();
	

	TString sourceDir, destinationDir, s_inTreeName, s_fnamePrefix, s_outFName;
	TString s_outTreeName, inFname, str_name;
	TTree *inTree = new TTree;
	TTree *outTree = new TTree;

	if (s::inDir.Contains("raw"))
	{
		s_inTreeName = "AnalysisxTree";
		s_fnamePrefix = "cln";
		s_outTreeName = "cleaned";
	}

	else if (s::inDir.Contains("cln"))
	{
		s_inTreeName = "cleaned";
		s_fnamePrefix = "clb";
		s_outTreeName = "calibrated";
	}

	else if (s::inDir.Contains("clb"))
	{
		s_inTreeName = "calibrated";
		s_fnamePrefix = "dE";
		s_outTreeName = "dE_angle";
	}

	else
	{
	return 0;
	}

	switch (s::runNo)
	{
	case 0:
	{
	sourceDir = (s::dir_CsI.Copy()).Data();
	gSystem->cd(sourceDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		inFname = obj->GetName();
		if (inFname.Contains("csi"))
			{
				printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
						inFname.Data(), "\x1b[0m", "\e[0m");
			}

		else if (inFname.Contains("csi"))
			{
				printf("%s\n",inFname.Data());
			}
	}

	TIter next = dir_data->GetListOfFiles();
	while (TObject *obj = next())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("csi"))			
		{
			s_outFName = str_name.Copy().ReplaceAll(s::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (s::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="de")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, inFname);
			Hermes->actual_work();}
		}			
	}
	break;
	}

	case 10:
	{
	sourceDir = (s::dir_runs.Copy() + s::inDir).Append("/geo1/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(s::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		inFname = obj->GetName();
		if (inFname.Contains("run00"))
			{
				printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
						inFname.Data(), "\x1b[0m", "\e[0m");
			}

		else if (inFname.Contains("run"))
			{
				printf("%s\n",inFname.Data());
			}
	}

	TIter next = dir_data->GetListOfFiles();
	while (TObject *obj = next())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run00"))
		{
			s_outFName = str_name.Copy().ReplaceAll(s::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			//printf("%s\t%s\n", s_inTreeName.Data(), (sourceDir+str_name.Copy()).Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (s::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="clb")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work();} outF->Close();}
	}
	break;
	}

	case 12:
	{
	sourceDir = (s::dir_runs.Copy() + s::inDir).Append("/geo1/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(s::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		inFname = obj->GetName();
		if (inFname.Contains("run02"))
			{
				printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
						inFname.Data(), "\x1b[0m", "\e[0m");
			}

		else if (inFname.Contains("run"))
			{
				printf("%s\n",inFname.Data());
			}
	}

	TIter next = dir_data->GetListOfFiles();
	while (TObject *obj = next())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run02"))			
		{
			s_outFName = str_name.Copy().ReplaceAll(s::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (s::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="clb")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work(); outF->Close();}
		}			
	}
	break;
	}

	case 2:
	{
	sourceDir = (s::dir_runs.Copy() + s::inDir).Append("/geo2/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(s::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		inFname = obj->GetName();
		if (inFname.Contains("run"))
			{
				printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
						inFname.Data(), "\x1b[0m", "\e[0m");
			}

		else if (inFname.Contains("run"))
			{
				printf("%s\n",inFname.Data());
			}
	}

	TIter next = dir_data->GetListOfFiles();
	while (TObject *obj = next())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run"))			
		{
			s_outFName = str_name.Copy().ReplaceAll(s::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (s::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="dE")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work(); outF->Close();}
		}			
	}
	break;
	}


	case 3:
	{
	sourceDir = (s::dir_runs.Copy() + s::inDir).Append("/geo3/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(s::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		inFname = obj->GetName();
		if (inFname.Contains("run"))
			{
				printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
						inFname.Data(), "\x1b[0m", "\e[0m");
			}

		else if (inFname.Contains("run"))
			{
				printf("%s\n",inFname.Data());
			}
	}

	TIter next = dir_data->GetListOfFiles();
	while (TObject *obj = next())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run"))			
		{
			s_outFName = str_name.Copy().ReplaceAll(s::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (s::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="clb")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work(); outF->Close();}
		}			
	}
	break;
	}		

	case 4:
	{
	sourceDir = (s::dir_runs.Copy() + s::inDir).Append("/geo4/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(s::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		inFname = obj->GetName();
		if (inFname.Contains("run"))
			{
				printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
						inFname.Data(), "\x1b[0m", "\e[0m");
			}

		else if (inFname.Contains("run"))
			{
				printf("%s\n",inFname.Data());
			}
	}

	TIter next = dir_data->GetListOfFiles();
	while (TObject *obj = next())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run"))			
		{
			s_outFName = str_name.Copy().ReplaceAll(s::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (s::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(s::inDir=="clb")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work(); outF->Close();}
		}			
	}
	break;
	}

	default:
	{
	printf("\nError: WTF amigo\n");
	return 0;
	break;
	}
	}

	
return 1;

}
