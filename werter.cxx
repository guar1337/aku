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
void functionDrawer();

void werter ()
{
	TStopwatch *stopwatch = new TStopwatch();
	printf("\n**We should definitely do something, aight?\n");
	//daisy_chain_files(true);
	MakeSelector_handler();
	//Xerox();
	//functionDrawer();
	//kniggit();
	//tree_extractor();
	stopwatch->Print();
}

void Xerox()
{
	Double_t qualityControl[4];
	Double_t inputPars[]{0.0,0.0,0.0,0.0};
	TString str_name = "cal_geo2.root";
	TFile *inF = new TFile{"/home/guar/data/he6_d/cal/geo3/cal_geo3.root", "READ"};
	TTree *inT = (TTree*)inF->Get("calibrated");
	TFile *outF = new TFile{"/home/guar/data/he6_d/cal/geo3/cal_deu3.root", "RECREATE"};
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
	TString fName("deuPoly");
	TString fullName = "/home/guar/data/he6_d/simulation/" + fName + ".root";
	TFile *inF = new TFile(fullName.Data(),"READ");
	TTree *inTree;
	inTree = (TTree*)inF->Get("simevents");
	inTree->Process("jasper.C",fName.Data());
	inF->Close();
	return 1;
}

bool MakeSelector_handler(TChain *inChain)
{
	inChain->MakeSelector("pfff");
	TString entriesNo = TString::LLtoa(inChain->GetEntriesFast(),10);
	inChain->Process("beamCutter.C", entriesNo);
	return 1;
}

void functionDrawer()
{
	TRandom3 *rndGen = new TRandom3();
	Double_t theta4 = rndGen->Uniform(0.0, TMath::Pi());
	TF1 *function1 = new TF1("function1","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))", 0.0, 90.0);
	function1->FixParameter(0, 2*cs::deg_to_rad);
	function1->FixParameter(1, cs::mass_6He/cs::mass_2H);
	function1->FixParameter(2, cs::rad_to_deg);
	function1->Draw();
	TF1 *function2 = new TF1("function2","[1]*atan((2*tan([0]*(90.0-x))/(1-(tan([0]*(90.0-x))*tan([0]*(90.0-x))/0.97)+2.948803*(1+(tan([0]*(90.0-x))*tan([0]*(90.0-x))/0.97)))))", 0.0, 90.0);
	function2->FixParameter(1, cs::rad_to_deg);
	function2->FixParameter(0, cs::deg_to_rad);
	function2->Draw("same");

	Double_t ene_beam, mom_beam;
	TVector3 *vBeam = new TVector3(0.0, 0.0, 1.0);
	TLorentzVector *lvBeam, lvTarget;
	lvTarget = TLorentzVector(0.0, 0.0, 1.0, cs::mass_1H);
	ene_beam = cs::mass_6He + 160.0;
	mom_beam = sqrt(ene_beam*ene_beam - cs::mass_6He*cs::mass_6He);
	vBeam->SetMag(mom_beam);	
	lvBeam->SetVectM(*vBeam, cs::mass_6He);

	TLorentzVector lv6He_IN = *lvBeam;
	TLorentzVector lv2H_IN = lvTarget;
	TLorentzVector lvCM_IN = lv6He_IN+lv2H_IN;
	/*
	TVector3 boostVect_IN = lvCM_IN.boostVector();
	lv6He_IN.boost(-boostVect_IN);
	lv2H_IN.boost(-boostVect_IN);
	//Let's go inelastic now!
	Double_t newEcm	= lv2H_IN.e() + lv6He_IN.e() - excitedStateEnergy_6He;
	Double_t newE2H	= (1/(2*newEcm))*(newEcm*newEcm-mass6He*mass6He+mass2H*mass2H);
	Double_t newE6He	= (1/(2*newEcm))*(newEcm*newEcm+mass6He*mass6He-mass2H*mass2H)+excitedStateEnergy_6He;
	Double_t newMom2H	= sqrt(newE2H*newE2H-mass2H*mass2H);
	Double_t newMom6He = sqrt(newE6He*newE6He-mass6He*mass6He);

	lv2H_IN.setE(newE2H);
	lv6He_IN.setE(newE6He+excitedStateEnergy_6He);
	
	lv2H_IN.setRho(newMom2H);
	lv6He_IN.setRho(newMom6He);

	//CM PART
	lv6He_IN.rotate(0,	theta_CM,	0);
	lv6He_IN.rotate(0,	0,				phi_CM	);
	lv2H_IN.rotate(0,		-theta_CM,	0	);
	lv2H_IN.rotate(0,		0,				-phi_CM	);
		
	TLorentzVector lv2H_CM_IN(lv2H_IN);
	TLorentzVector lv6He_CM_IN(lv6He_IN);

	lv6He_IN.boost(boostVect_IN);
	lv2H_IN.boost(boostVect_IN);
	*/
}

bool tree_extractor()
{
	TString fpath = "/home/guar/data/he6_d/dE/PG_geo1.root";
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

	TString raw_data_path{"/home/guar/data/he6_d/raw/geo1/"};
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
return 0;
}
