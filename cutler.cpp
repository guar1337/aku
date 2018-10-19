#include <iostream>
#include <TSystemDirectory.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include "constants.h"
#include "dE_E_angle.h"
#include "muchobojca.h"
#include <TVectorT.h>

R__LOAD_LIBRARY(libPhysics.so); 
//IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** 
//instead of
R__LOAD_LIBRARY(libgsl.so); 
//**R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
R__LOAD_LIBRARY(/home/guar/aku/wrk/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);

float loop(Float_t left_det_shift, Float_t right_det_shift, std::vector<Float_t> &vChiSquare_1H, std::vector<Float_t> &vChiSquare_2H)
{
	muchobojca 		*MrMuscle = new muchobojca();
	calibrate_tree 	*Kali = new calibrate_tree();
	float container;

	std::vector<Float_t> stdV_Sqlang_1H;
	std::vector<Float_t> stdV_Sqrang_1H;
	std::vector<Float_t> stdV_Sqlang_2H;
	std::vector<Float_t> stdV_Sqrang_2H;
	TGraph *angAngGraph_1H_geo1;
	TGraph *angAngGraph_1H_geo2;
	TGraph *angAngGraph_1H_geo3;

	TGraph *angAngGraph_2H_geo1;
	TGraph *angAngGraph_2H_geo2;
	TGraph *angAngGraph_2H_geo3;

	TString sourceDir, destinationDir, s_fnamePrefix, s_outFName, outFname_tmp;
	TString s_outTreeName, s_inTreeName, str_name;
	TTree *inTree = new TTree;
	TTree *outTree = new TTree;

	if (cs::inDir.Contains("raw"))
	{
		s_inTreeName = "AnalysisxTree";
		s_fnamePrefix = "cln";
		s_outTreeName = "cleaned";
	}

	else if (cs::inDir.Contains("cln"))
	{
		s_inTreeName = "cleaned";
		s_fnamePrefix = "clb";
		s_outTreeName = "calibrated";
	}

	else if (cs::inDir.Contains("clb"))
	{
		s_inTreeName = "calibrated";
		s_fnamePrefix = "dE";
		s_outTreeName = "dE_angle";
	}

	else
	{
	return 0;
	}

	int geoNo;
	for (int counter_geoNo = 0; counter_geoNo < 3; ++counter_geoNo)
	{
	geoNo = counter_geoNo+1;

	switch (geoNo)
	{/*
	case 0:
	{
	sourceDir = (cs::dir_CsI.Copy()).Data();
	gSystem->cd(sourceDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("csi"))			
		{
			printf("%s%s%s\t%i%s%s\n", "\x1B[32m", "\e[1m", 
					str_name.Data(), str_name.Atoi(), "\x1b[0m", "\e[0m");
			//str_name.Atoi();
			s_outFName = str_name.Copy().ReplaceAll(cs::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (cs::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="de")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work();}
		}			
	}
	break;
	}
*/
	case 1:
	{
	sourceDir = (cs::dir_runs.Copy() + cs::inDir).Append("/geo1/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(cs::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run02sum"))
		{
			printf("%s%s%s\t%s%s\n", "\x1B[32m", "\e[1m", 
					str_name.Data(), "\x1b[0m", "\e[0m");
			outFname_tmp = str_name.Copy().ReplaceAll(cs::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			outFname_tmp.ReplaceAll(".root","");
			s_outFName.Form("%s.root", outFname_tmp.Data());
			TFile *outF = new TFile(s_outFName, "RECREATE");
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			//printf("%s\t%s\n", s_inTreeName.Data(), (sourceDir+str_name.Copy()).Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (cs::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="clb")
			{



			dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);

			container = Hermes->actual_work(geoNo, left_det_shift, right_det_shift,
													stdV_Sqlang_1H, stdV_Sqrang_1H,
													stdV_Sqlang_2H, stdV_Sqrang_2H);

			angAngGraph_1H_geo1 =  new TGraph(stdV_Sqlang_1H.size(), &stdV_Sqlang_1H[0], &stdV_Sqrang_1H[0]);
			angAngGraph_2H_geo1 =  new TGraph(stdV_Sqlang_2H.size(), &stdV_Sqlang_2H[0], &stdV_Sqrang_2H[0]);
			stdV_Sqlang_1H.clear(); stdV_Sqrang_1H.clear(); stdV_Sqlang_2H.clear(); stdV_Sqrang_2H.clear();
			}
			outF->Close();
			inF->Close();
		}
	}
	break;
	}

	case 2:
	{
	sourceDir = (cs::dir_runs.Copy() + cs::inDir).Append("/geo2/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(cs::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("geo"))			
		{
			printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
					str_name.Data(), "\x1b[0m", "\e[0m");
			s_outFName = str_name.Copy().ReplaceAll(cs::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (cs::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="clb")
			{



			dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);

			container = Hermes->actual_work(geoNo, left_det_shift, right_det_shift,
													stdV_Sqlang_1H, stdV_Sqrang_1H,
													stdV_Sqlang_2H, stdV_Sqrang_2H);

			angAngGraph_1H_geo2 =  new TGraph(stdV_Sqlang_1H.size(), &stdV_Sqlang_1H[0], &stdV_Sqrang_1H[0]);
			angAngGraph_2H_geo2 =  new TGraph(stdV_Sqlang_2H.size(), &stdV_Sqlang_2H[0], &stdV_Sqrang_2H[0]);
			stdV_Sqlang_1H.clear(); stdV_Sqrang_1H.clear(); stdV_Sqlang_2H.clear(); stdV_Sqrang_2H.clear();

			}
			outF->Close();
			inF->Close();
		}			
	}
	break;
	}


	case 3:
	{
	sourceDir = (cs::dir_runs.Copy() + cs::inDir).Append("/geo3/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(cs::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());
	printf("%s\n",destinationDir.Data() );
	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("geo"))
		{
			printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
					str_name.Data(), "\x1b[0m", "\e[0m");
			s_outFName = str_name.Copy().ReplaceAll(cs::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (cs::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="clb")
						{



			dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);

			container = Hermes->actual_work(geoNo, left_det_shift, right_det_shift,
													stdV_Sqlang_1H, stdV_Sqrang_1H,
													stdV_Sqlang_2H, stdV_Sqrang_2H);

			angAngGraph_1H_geo3 =  new TGraph(stdV_Sqlang_1H.size(), &stdV_Sqlang_1H[0], &stdV_Sqrang_1H[0]);
			angAngGraph_2H_geo3 =  new TGraph(stdV_Sqlang_2H.size(), &stdV_Sqlang_2H[0], &stdV_Sqrang_2H[0]);
			stdV_Sqlang_1H.clear(); stdV_Sqrang_1H.clear(); stdV_Sqlang_2H.clear(); stdV_Sqrang_2H.clear();

			}
			outF->Close();
			inF->Close();
		}			
	}
	break;
	}	
/*
	case 4:
	{
	sourceDir = (cs::dir_runs.Copy() + cs::inDir).Append("/geo4/").Data();
	destinationDir = sourceDir.Copy().ReplaceAll(cs::inDir.Data(), s_fnamePrefix.Data());
	gSystem->cd(destinationDir.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", sourceDir.Data());

	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{			
		str_name = obj->GetName();
		if (str_name.Contains("run"))			
		{
			printf("%s%s%s%s%s\n", "\x1B[32m", "\e[1m", 
					str_name.Data(), "\x1b[0m", "\e[0m");
			s_outFName = str_name.Copy().ReplaceAll(cs::inDir.Data(),s_fnamePrefix.Data());
			TFile *inF = new TFile(sourceDir+str_name.Copy(), "READ");
			TFile *outF = new TFile(s_outFName, "RECREATE");				
			inTree = (TTree*)inF->Get(s_inTreeName.Data());
			outTree= new TTree(s_outTreeName.Data(),s_outTreeName.Data());
			if (cs::inDir=="raw")	{MrMuscle->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="cln"){Kali->wrk(inTree, outTree, str_name);}
			else if(cs::inDir=="clb")
			{dE_E_angle *Hermes = new dE_E_angle(inTree,outTree, str_name);
			Hermes->actual_work();}
			outF->Close();
		}
	}
	break;
	}//case
*/
	default:
	{
	printf("\nError: WTF amigo?\n");
	return 0;
	break;
	}
	}//switch
}//for loop on geometry

TF1 *angAngFit_1H = new TF1("angAngFit_1H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
angAngFit_1H->FixParameter(0, 2*cs::deg_to_rad);
angAngFit_1H->FixParameter(1, cs::mass_6He/cs::mass_1H);
angAngFit_1H->FixParameter(2, cs::rad_to_deg);

TF1 *angAngFit_2H = new TF1("angAngFit_2H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
angAngFit_2H->FixParameter(0, 2*cs::deg_to_rad);
angAngFit_2H->FixParameter(1, cs::mass_6He/cs::mass_2H);
angAngFit_2H->FixParameter(2, cs::rad_to_deg);

TMultiGraph *angAngMultiGraph_1H = new TMultiGraph();
TMultiGraph *angAngMultiGraph_2H = new TMultiGraph();

angAngMultiGraph_1H->Add(angAngGraph_1H_geo1);
angAngMultiGraph_1H->Add(angAngGraph_1H_geo2);
angAngMultiGraph_1H->Add(angAngGraph_1H_geo3);

angAngMultiGraph_2H->Add(angAngGraph_2H_geo1);
angAngMultiGraph_2H->Add(angAngGraph_2H_geo2);
angAngMultiGraph_2H->Add(angAngGraph_2H_geo3);




angAngGraph_1H_geo1->SetMarkerStyle(kFullDotMedium);
angAngGraph_1H_geo1->SetMarkerColor(kRed);
angAngGraph_1H_geo2->SetMarkerStyle(kFullDotMedium);
angAngGraph_1H_geo2->SetMarkerColor(kBlue);
//angAngGraph_1H_geo3->SetMarkerStyle(kFullDotMedium);
//angAngGraph_1H_geo3->SetMarkerColor();


angAngGraph_2H_geo1->SetMarkerStyle(kFullDotMedium);
angAngGraph_2H_geo1->SetMarkerColor(kRed);
angAngGraph_2H_geo2->SetMarkerStyle(kFullDotMedium);
angAngGraph_2H_geo2->SetMarkerColor(kBlue);
//angAngGraph_2H_geo3->SetMarkerStyle(kFullDotMedium);
//angAngGraph_2H_geo3->SetMarkerColor();

angAngMultiGraph_1H->Fit(angAngFit_1H, "Q");
angAngMultiGraph_2H->Fit(angAngFit_2H, "Q");
vChiSquare_1H.push_back(angAngFit_1H->GetChisquare());
vChiSquare_2H.push_back(angAngFit_2H->GetChisquare());

//angAngMultiGraph_1H->Draw("AP");



return container;

}

void cutler()
{
	std::vector<Float_t> vChiSquare_1H;
	std::vector<Float_t> vChiSquare_2H;
	TString dir_out("/home/guar/Desktop/");
	ofstream outStream_1H(dir_out.Append("fitQuality_1H.dat").Data(), ios::trunc);
	ofstream outStream_2H(dir_out.ReplaceAll("1H","2H").Data(), ios::trunc);
	Float_t right_det_shift = -2.0;
	Float_t left_det_shift = -4.0;
/*
	loop(left_det_shift, right_det_shift, vChiSquare_1H, vChiSquare_2H);
	outStream_1H<<vChiSquare_1H.back()<<" ";
	outStream_2H<<vChiSquare_2H.back()<<" ";
*/

	for (int iii = 0; iii < 40; ++iii)
	{
		for (int jjj = 0; jjj < 40; ++jjj)
		{
			loop(left_det_shift, right_det_shift, vChiSquare_1H, vChiSquare_2H);
			outStream_1H<<vChiSquare_1H.back()<<" ";
			outStream_2H<<vChiSquare_2H.back()<<" ";
			outStream_1H.flush();
			outStream_2H.flush();
			right_det_shift+=0.1;
		}
		outStream_1H<<endl;
		outStream_2H<<endl;
		left_det_shift+=0.2;
		right_det_shift=-2.0;
		printf("\n****************************************\n");
	}
	
}