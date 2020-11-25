#include "ELC/AELC.h"
#include "ELC/ELC.h"
#include "dE_E_angle.h"

#include "constants.h"
#include "muchobojca.h"
#include "calibrate_tree.h"

R__LOAD_LIBRARY(libgsl.so);
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/libMr_Blue_Sky.so);
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC/build/libEloss.so);


#include <sys/time.h>

bool MakeSelector_handler();
bool tree_extractor();
bool daisy_chain_files(bool printout);
bool kniggit();
void Xerox();
void madLooper();
const TString MWPCID = "2";
void privateFileCaller();

void werter()
{
	TStopwatch *stopwatch = new TStopwatch();
	printf("\n**We should definitely do something, aight?\n");
	//daisy_chain_files(true);
	MakeSelector_handler();
	//Xerox();
	//kniggit();
	//tree_extractor();
	//privateFileCaller();
	stopwatch->Print();
}

void privateFileCaller()
{/*
	TString inTreeName,fnamePrefix, outTreeName;
	Double_t inputPars, qualityControl;

	if (cs::inDir.Contains("raw"))
	{
		inTreeName = "AnalysisxTree";
		fnamePrefix = "cln";
		outTreeName = "cleaned";
	}

	else if (cs::inDir.Contains("cln"))
	{
		inTreeName = "cleaned";
		fnamePrefix = "cal";
		outTreeName = "calibrated";
	}

	else if (cs::inDir.Contains("cal"))
	{
		inTreeName = "calibrated";
		fnamePrefix = "dE";
		outTreeName = "dE_angle";
	}

	TTree *inT, *outT;
	TFile *inF, *outF;
	TString infName = "/home/zalewski/data/he6_d/miscroot/CsI/cal_csiR.root";
	TString outFName = "/home/zalewski/data/he6_d/miscroot/CsI/dE_csiR.root";

	inF = new TFile{infName.Data(), "READ"};
	if (inF->IsZombie())
	{
		return 0;
	}

	inT = (TTree*)inF->Get(inTreeName.Data());
	outF = new TFile{outFName.Data(), "RECREATE"};
	outT= new TTree{outTreeName.Data(),outTreeName.Data()};

	if (cs::inDir=="raw")
	{
		muchobojca *MrMuscle = new muchobojca();
		MrMuscle->wrk(inT, outT);
	}

	else if(cs::inDir=="cln")
	{
		calibrate_tree *Kali = new calibrate_tree();
		Kali->wrk(inT, outT);
	}

	else if(cs::inDir=="cal")
	{
		dE_E_angle *Hermes = new dE_E_angle(inT,outT, infName, cs::runNo);
		(cs::runNo == 5) ? Hermes->actual_work_gas() : Hermes->actual_work(&inputPars, &qualityControl, cs::runNo);
	}

	outT->Write();
	delete outF, inF;*/
}

void Xerox()
{
	Double_t qualityControl[4];
	Double_t inputPars[]{0.0,0.0,0.0,0.0};
	TString str_name = "cal_geo2.root";
	TFile *inF = new TFile{"/home/zalewski/data/he6_d/cal/geo3/cal_geo3.root", "READ"};
	TTree *inT = (TTree*)inF->Get("calibrated");
	TFile *outF = new TFile{"/home/zalewski/data/he6_d/cal/geo3/cal_deu3.root", "RECREATE"};
	TTree *outT = inT->CloneTree(0);
	outT->SetName("calibrated");
	dE_E_angle *Hermes = new dE_E_angle(inT, outT, str_name, cs::runNo);
	Hermes->actual_work(inputPars, qualityControl);
	outT->Write();
	delete inT;
	delete inF;
	delete outT;
	delete outF;			
	delete Hermes;	
}

bool MakeSelector_handler()
{
	TString fName("gurney_bis");
	TString fullName = "/home/zalewski/Desktop/6He/analysis/20Fev/" + fName + ".root";
	TFile *inF = new TFile(fullName.Data(),"READ");
	TTree *inTree;
	inTree = (TTree*)inF->Get("simevents");
	printf("%lld\n",inTree->GetEntries() );
	//inTree->MakeSelector("expr");
	inTree->Process("jasper.C",fName.Data());
	inF->Close();
	return 1;
}

bool MakeSelector_handler(TChain *inChain)
{
	//inChain->MakeSelector("pfff");
	TString entriesNo = TString::LLtoa(inChain->GetEntriesFast(),10);
	inChain->Process("beamCutter.C", entriesNo);
	return 1;
}

bool tree_extractor()
{
	TString fpath = "/home/zalewski/data/he6_d/dE/PG_geo1.root";
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

	TFile *outF = new TFile((fpath + "_ladida").Data(), "recreate");
	auto outT = inChain->CloneTree();

	//Deactivate all
	//MakeSelector_handler(inChain);
	/*
	inChain->SetBranchStatus("*", 0);
	// Activate only four of them
	for (auto activeBranchName : {"LV_beam.", "evX", "evY", "evZ"})
		inChain->SetBranchStatus(activeBranchName, 1);
	*/
	Short_t Geo_ID = 0;
	TBranch *bpt = outT->Branch("geo",	&Geo_ID,	"geo/S");

	Long64_t nentries = outT->GetEntries();

	for (Long64_t i=0; i<nentries; i++)
	{
		outT->GetEntry(i);
		Geo_ID = 1;
		bpt->Fill();
	}

	outT->Print();
	outT->Write();
	delete inFile;
	delete outF;
/*
	newtree->SetName("working_copy");
	newtree->Print();
	newfile.Write();
*/
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

	TString raw_data_path{"/home/zalewski/data/he6_d/raw/geo1/"};
	TString fileName, TreePath;
	TString treeName{"/AnalysisxTree"};
	TChain *inChain = new TChain();
	TSystemDirectory *dir_data = new TSystemDirectory("data",raw_data_path.Data());
	short fcounter = 0;
	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		fileName = obj->GetName();
		if (	fileName.Contains("run")	&&  
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

	TString fName("gurney_bis");
	TString fullName = "/home/zalewski/aku/geant4/build/" + fName + ".root";
	TFile *inF = new TFile(fullName.Data(),"READ");
	TTree *inTree;
	inTree = (TTree*)inF->Get("simevents");
	inTree->MakeSelector("jasper_tmp.C");
	//inTree->Process("jasper_tmp.C",fName.Data());
	inF->Close();
	return 1;

}
