#include "ELC/AELC.h"
#include "ELC/ELC.h"
#include "dE_E_angle.h"

#include "constants.h"
R__LOAD_LIBRARY(libgsl.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/ELC/libEloss.so);


#include <sys/time.h>

bool MakeSelector_handler();
bool tree_extractor();
bool daisy_chain_files(bool printout);
bool kniggit();


void werter ()
{
	ofstream outStreamQ("/home/guar/Desktop/qualityControl_2.dat", ios::trunc);
	Double_t qualityControl[4];
	TStopwatch *stopwatch = new TStopwatch();
	printf("We should definitely do something, aight?\n");
	//daisy_chain_files(false);
	//MakeSelector_handler();
	/*
	TFile *inF = new TFile{"/home/guar/data/he6_d/cal/geo5/cal_run_09.root", "READ"};
	TTree *inT = (TTree*)inF->Get("calibrated");
	TFile *outF = new TFile{"/home/guar/data/he6_d/dE/geo5/tmp.root", "RECREATE"};
	TTree *outT= new TTree{"tmptree", "ha"};
	*/
	TString str_name = "cal_run_09.root";

	

	Double_t MWPC_X_1_shift = -5.0, MWPC_X_2_shift = -5.0;
	outStreamQ<<"MWPC_X_1_shift"<<"\t"<<"MWPC_X_2_shift"<<"\t"<<"sqlde+sqletot-kinsqle_2H"<<"\t"<<"sqlde+sqletot-kinsqle_2H sigma"<<"\t"<<"mml"<<"\t"<<"paramA"<<endl;

	for (int iii = 0; iii < 20; iii++)
	{
		for (int jjj = 0; jjj < 20; jjj++)
		{
			TFile *inF = new TFile{"/home/guar/data/he6_d/cal/geo5/cal_run_09.root", "READ"};
			TTree *inT = (TTree*)inF->Get("calibrated");
			TFile *outF = new TFile{"/home/guar/data/he6_d/dE/geo5/tmp.root", "RECREATE"};
			TTree *outT= new TTree{"tmptree", "ha"};
			dE_E_angle *Hermes = new dE_E_angle(inT,outT, str_name, cs::runNo);
			Hermes->actual_work_gas(MWPC_X_1_shift, MWPC_X_2_shift, qualityControl);
			//printf("%f\t%f\t%f\t\n", qualityControl[0], qualityControl[1], qualityControl[2]);
			outStreamQ<<MWPC_X_1_shift<<" "<<MWPC_X_2_shift<<" "<<qualityControl[0]<<" "<<qualityControl[1]<<" "<<qualityControl[2]<<" "<<qualityControl[3]<<endl;
			outStreamQ.flush();
			outT->Write();
			delete inT;
			delete inF;
			delete outT;
			delete outF;			
			delete Hermes;
			//outStreamQ<<MWPC_X_1_shift<<" "<<MWPC_X_2_shift<<"\t\t";		
			MWPC_X_2_shift+=0.5;

		}
		//outStreamQ<<endl;
		MWPC_X_1_shift+=0.5;
		MWPC_X_2_shift = -5.0;
	}

	
	stopwatch->Print();
	
}
bool MakeSelector_handler()
{
	TString fpath = "/home/guar/aku/geant4/build/gurney.root";
	TString treeName = "simevents";
	TFile *inFile = new TFile(fpath.Data());

	if (inFile->IsZombie())
	{
		return 0;
	}

	TTree *inChain;

	inChain = (TTree*)inFile->Get(treeName.Data());

	if (inChain == nullptr || inChain->IsZombie())
	{
		printf("Could not open Tree %s from TFile %s\n", treeName.Data(), fpath.Data());
		return 0;
	}

	//inChain->MakeSelector("jasper");



	inChain->Process("jasperNo5.C");
	inFile->Close();
	delete inFile;
	return 1;
}

bool MakeSelector_handler(TChain *inChain)
{
	//inChain->MakeSelector("beamCutter");
	inChain->Process("beamCutter.C");
	return 1;
}

bool tree_extractor()
{
	TString fpath = "/home/guar/data/mar2018/dE/geo.root";
	TString treeName = "dE_angle";
	TFile *inFile = new TFile(fpath.Data());

	if (inFile->IsZombie())
	{
		return 0;
	}

	TTree *inChain;
	inChain = (TTree*)inFile->Get(treeName.Data());

	if (inChain == nullptr || inChain->IsZombie())
	{
		printf("Could not open Tree %s from TFile %s\n", treeName.Data(), fpath.Data());
		return 0;
	}
	//Deactivate all
	inChain->SetBranchStatus("*", 0);
	// Activate only four of them
	for (auto activeBranchName : {"LV_beam.", "evX", "evY", "evZ"})
		inChain->SetBranchStatus(activeBranchName, 1);

	TFile newfile("beamSauce.root", "recreate");
	auto newtree = inChain->CloneTree();
	newtree->SetName("beam_src");
	newtree->Print();
	newfile.Write();
	return 1;
}

bool tree_extractor(TChain *inChain)
{
	//Deactivate all
	inChain->SetBranchStatus("*", 0);
	// Activate only four of them
	for (auto activeBranchName : {"LV_beam.", "evX", "evY", "evZ"})
		inChain->SetBranchStatus(activeBranchName, 1);

	TFile newfile("beamSauce.root", "recreate");
	auto newtree = inChain->CloneTree();
	newtree->SetName("beam_src");
	newtree->Print();
	newfile.Write();
	return 1;
}

bool daisy_chain_files(bool printout)
{
	//	remove this line to use multi-file processing

	TString raw_data_path{"/home/guar/data/mar2018/raw/geo1/"};
	TString fileName, TreePath;
	TString treeName{"/AnalysisxTree"};
	TChain *inChain = new TChain();
	TSystemDirectory *dir_data = new TSystemDirectory("data",raw_data_path.Data());
	short fcounter = 0;
	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		fileName = obj->GetName();
		if (	fileName.Contains("root") &&  //if we want to ommit some phrase (np.li9_3_21_0)
				!fileName.Contains("li9_3_21_0") //  "!"  sign is important
					)
		{
		TreePath.Form("%s%s%s",raw_data_path.Data(),fileName.Data(),treeName.Data());
		TFile *inF = new TFile((raw_data_path+fileName).Data(), "READ");
		if (!inChain->Add(TreePath.Data(),0)) {return 0;}
		fcounter++;
		//printf("fName:\t%s\n",TreePath.Data());
		}
	}

	printf("\n#\n##\n###\n##\n#\n\n");
	printf("\n\tWe have %lld entries from %d files\n",inChain->GetEntriesFast(), fcounter);
	printf("\n#\n##\n###\n##\n#\n\n");

	if (printout)
	{
		TObjArray *fileElements=inChain->GetListOfFiles();
		TIter next(fileElements);
		TChainElement *chEl=0;
		while (( chEl=(TChainElement*)next() ))
		{
			TFile f(chEl->GetTitle());
		 	printf("I opened:\t%s\t\tfile\n",chEl->GetTitle());
		}
		printf("\n#\n##\n###\n##\n#\n\n");
	}
	MakeSelector_handler(inChain);
	return 1;
}

bool kniggit()
{
	for (int iii = 0; iii < 10; iii++)
	{
		printf("%d\n",iii);
	}
	return true;
}