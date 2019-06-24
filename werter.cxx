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
void Xerox();
void madLooper();
const TString MWPCID = "2";

void werter ()
{
	TProof::Open("");
	TStopwatch *stopwatch = new TStopwatch();
	printf("\n**We should definitely do something, aight?\n");
	//daisy_chain_files(false);
	//MakeSelector_handler();
	madLooper();
	//Xerox();
	stopwatch->Print();
}

void Xerox()
{
	Double_t qualityControl[4];
	Double_t inputPars[]{0.0,0.0,0.0,0.0};
	TString str_name = "cal_geo1.root";
	TFile *inF = new TFile{"/home/guar/data/he6_d/cal/geo1/cal_geo1.root", "READ"};
	TTree *inT = (TTree*)inF->Get("calibrated");
	TFile *outF = new TFile{"/home/guar/data/he6_d/cal/geo1/cal_pro1.root", "RECREATE"};
	TTree *outT = inT->CloneTree(0);
	outT->SetName("calibrated");
	dE_E_angle *Hermes = new dE_E_angle(inT, outT, str_name, cs::runNo);
	Hermes->actual_work_1H(inputPars, qualityControl);
	outT->Write();
	delete inT;
	delete inF;
	delete outT;
	delete outF;			
	delete Hermes;	
}

void madLooper()
{

	ofstream outStreamQ("/home/guar/Desktop/findingX.dat", ios::trunc);
	Double_t qualityControl_1H[4];
	Double_t qualityControl_2H[4];
	TString str_name = "cal_geo1.root";
	/*
	TFile *inF = new TFile{"/home/guar/data/he6_d/cal/geo1/cal_geo1.root", "READ"};
	TTree *inT = (TTree*)inF->Get("calibrated");
	TFile *outF = new TFile{"/home/guar/data/he6_d/dE/geo1/tmp.root", "RECREATE"};
	TTree *outT= new TTree{"tmptree", "ha"};
	*/
	

	
	//38.0 - best shift of left detector
	Double_t inputPars[]{-20.0,-20.0,-20.0,-16.0};
	outStreamQ<<"xL"<<"\t"<<"zL"<<"\t"<<"xR"<<"\t"<<"zR"<<"\t"<<"mm1H"<<"\t"<<"angang_1H"<<"\t"<<"mm2H"<<"\t"<<"angang_2H"<<"\t"<<endl;
	int counter{0};
	for (int iii = 0; iii < 20; iii++)
	{
		for (int jjj = 0; jjj < 20; jjj++)
		{
			for (int kkk = 0; kkk < 20; kkk++)
			{
				TFile *inF = new TFile{"/home/guar/data/he6_d/cal/geo1/cal_pro1.root", "READ"};
				TTree *inT = (TTree*)inF->Get("calibrated");
				TFile *outF = new TFile{"/home/guar/data/he6_d/dE/geo1/dE_pro1.root", "RECREATE"};
				TTree *outT= new TTree{"tmptree", "ha"};
				dE_E_angle *Hermes = new dE_E_angle(inT,outT, str_name, cs::runNo);
				Hermes->actual_work_1H(inputPars, qualityControl_1H);
				outT->Write();
				delete inT;
				delete inF;
				delete outT;
				delete outF;			
				delete Hermes;	

				inF = new TFile{"/home/guar/data/he6_d/cal/geo1/cal_deu1.root", "READ"};
				inT = (TTree*)inF->Get("calibrated");
				outF = new TFile{"/home/guar/data/he6_d/dE/geo1/dE_deu1.root", "RECREATE"};
				outT= new TTree{"tmptree", "ha"};
				Hermes = new dE_E_angle(inT,outT, str_name, cs::runNo);
				Hermes->actual_work_2H(inputPars, qualityControl_2H);
				outStreamQ<<inputPars[0]<<" "<<inputPars[1]<<" "<<inputPars[2]<<" "<<inputPars[3]<<" "<<qualityControl_1H[0]<<" "<<qualityControl_1H[2]<<" "<<qualityControl_2H[0]<<" "<<qualityControl_2H[2]<<endl;
																		
				outStreamQ.flush();
				outT->Write();

				delete inT;
				delete inF;
				delete outT;
				delete outF;			
				delete Hermes;
				inputPars[0] += 2;
			}
			inputPars[0] = -20.0;
			inputPars[1] += 2;
		}
		inputPars[1] = -20.0;
		inputPars[2] += 2;
		printf("## We have like, I don't know? Eeee %d%% or what\n",counter+=5);
	}	
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
	//inChain->MakeSelector("geoMaker");
	inChain->Process("geoMaker.C", MWPCID.Data());
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

	TString raw_data_path{"/home/guar/data/he6_d/calib_utilities/"};
	TString fileName, TreePath;
	TString treeName{"/AnalysisxTree"};
	TChain *inChain = new TChain();
	TSystemDirectory *dir_data = new TSystemDirectory("data",raw_data_path.Data());
	short fcounter = 0;
	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		fileName = obj->GetName();
		if (	fileName.Contains("MWPC")	&&  
				fileName.Contains(MWPCID)	&&//if we want to ommit some phrase (np.li9_3_21_0)
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