//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr	9 11:42:44 2019 by ROOT version 6.12/06
// from TTree simevents/MC events
// found on file: /home/zalewski/aku/geant4/build/gurney.root
//////////////////////////////////////////////////////////

#ifndef jasper_h
#define jasper_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <sys/ioctl.h> // For ioctl, TIOCGWINSZ
#include <unistd.h> // For STDOUT_FILENO
#include <TH2.h>
#include <TStyle.h>

// Headers needed by this particular selector
#include "TLorentzVector.h"



class jasper : public TSelector {
public :
	TTreeReader		fReader;	//!the tree reader
	TTree			 *fChain = 0;	//!pointer to the analyzed TTree or TChain
	TFile *outF;
	TTree *outTree;

	// Readers to access the data (delete the ones you do not need).
	TTreeReaderValue<TLorentzVector> inlvBeam = {fReader, "lvBeam."};
	TTreeReaderValue<TLorentzVector> inlv2H = {fReader, "lv2H."};
	TTreeReaderValue<TLorentzVector> inlv6He = {fReader, "lv6He."};
	TTreeReaderValue<TLorentzVector> inlv2Hcm = {fReader, "lv2H_CM."};
	TTreeReaderValue<TLorentzVector> inlv6Hecm = {fReader, "lv6He_CM."};

	TTreeReaderArray<Double_t> CsIdeut = {fReader, "CsIdeut"};
	TTreeReaderArray<Double_t> SideutX = {fReader, "SideutX"};
	TTreeReaderArray<Double_t> SideutY = {fReader, "SideutY"};

	TTreeReaderValue<Double_t> fInsqlang = {fReader, "fsqlang"};
	TTreeReaderValue<Double_t> fInsqlde = {fReader, "fsqlde"};
	TTreeReaderValue<Double_t> fInsqletot = {fReader, "fsqletot"};

	TTreeReaderArray<Double_t> CsIhe = {fReader, "CsIhe"};
	TTreeReaderArray<Double_t> SiheY = {fReader, "SiheY"};
	TTreeReaderArray<Double_t> SiheX = {fReader, "SiheX"};

	TTreeReaderValue<Double_t> fInsqrang = {fReader, "fsqrang"};
	TTreeReaderValue<Double_t> fInsqrde = {fReader, "fsqrde"};
	TTreeReaderValue<Double_t> fInsqretot = {fReader, "fsqretot"};

	TTreeReaderValue<Double_t> beamT = {fReader, "fbeamT"};

	TTreeReaderValue<Double_t> fInevx = {fReader, "fevx"};
	TTreeReaderValue<Double_t> fInevy = {fReader, "fevy"};
	TTreeReaderValue<Double_t> fInevz = {fReader, "fevz"};
	TTreeReaderValue<Double_t> fInX6He = {fReader, "fX6He"};
	TTreeReaderValue<Double_t> fInY6He = {fReader, "fY6He"};
	TTreeReaderValue<Double_t> fInZ6He = {fReader, "fZ6He"};
	TTreeReaderValue<Double_t> fInX2H = {fReader, "fX2H"};
	TTreeReaderValue<Double_t> fInY2H = {fReader, "fY2H"};
	TTreeReaderValue<Double_t> fInZ2H = {fReader, "fZ2H"};
	TTreeReaderValue<Char_t> fEve2H = {fReader, "fEve2H"};

	TTreeReaderValue<Float_t> fMWPC_1_X = {fReader, "MWPC_1_X"};
	TTreeReaderValue<Float_t> fMWPC_2_X = {fReader, "MWPC_2_X"};
	TTreeReaderValue<Float_t> fMWPC_1_Y = {fReader, "MWPC_1_Y"};
	TTreeReaderValue<Float_t> fMWPC_2_Y = {fReader, "MWPC_2_Y"};


	Int_t Sideut_multY;
	Int_t Sideut_multX;
	Int_t Sihe_multX;
	Int_t Sihe_multY;

	Double_t SQLang, SQRang, SQLdist, SQRdist, tarAngle, tarPos;
	Double_t MWPC_1_Z, MWPC_2_Z;
	Double_t fsqrde, fsqlde, fsqretot, fsqletot, resqlde;
	Double_t sqrde, sqlde, sqretot, sqletot;
	Double_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
	Double_t fdX, fdY, fdZ, fhX, fhY, fhZ;
	Double_t X2Hlab, Y2Hlab, Z2Hlab, X6Helab, Y6Helab, Z6Helab;
	Double_t X2Hdet, Y2Hdet, Z2Hdet, X6Hedet, Y6Hedet, Z6Hedet;
	Double_t evX, evY, evZ;
	Double_t fevX, fevY, fevZ;
	Double_t dX, dY, dZ;
	Double_t sqlang, sqrang, fsqlang, fsqrang;
	Double_t out_fsqlangg, out_fsqrangg;
	Double_t mm, thetacm, phicm;
	Double_t fmm, fthetacm, fphicm;
	Double_t MWPC_1_X, MWPC_2_X, MWPC_1_Y, MWPC_2_Y;
	Int_t SQX_L_sNo, SQY_L_sNo, SQX_R_sNo, SQY_R_sNo;
	const Double_t width_strip_X{58.0/32.0};
	const Double_t width_strip_Y{58.0/16.0};
	TRandom3 *rnd;
	TVector3 *v2H, *v6He, *vf2H, *vf6He, *vBeam;
	//Double_t reco_sqlang, reco_sqrang;

	TLorentzVector *flv6He;
	TLorentzVector *flv2H;
	TLorentzVector *flvbeam;
	TLorentzVector *flv6Hecm;
	TLorentzVector *flv2Hcm;
	TLorentzVector *lv6He;
	TLorentzVector *lv2H;
	TLorentzVector *lvBeam;

	int CD2_Nel=2;
	double CD2_A[2]{2, 12};
	double CD2_Z[2]{1, 6};
	double CD2_W[2]{2, 1};
	AELC *h2_CD2;
	double tarThcknss{100.0};

	float progress = 0.0;
	Long64_t nEntries;
	int consoleWidth;

	jasper(TTree * /*tree*/ =0) { }
	virtual ~jasper() { }
	virtual Int_t	Version() const { return 2; }
	virtual void	Begin(TTree *tree);
	virtual void	SlaveBegin(TTree *tree);
	virtual void	Init(TTree *tree);
	virtual Bool_t	Notify();
	virtual Bool_t	Process(Long64_t entry);
	virtual Int_t	GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
	virtual void	SetOption(const char *option) { fOption = option; }
	virtual void	SetObject(TObject *obj) { fObject = obj; }
	virtual void	SetInputList(TList *input) { fInput = input; }
	virtual TList	*GetOutputList() const { return fOutput; }
	virtual void	SlaveTerminate();
	virtual void	Terminate();

	ClassDef(jasper,0);

};

#endif

#ifdef jasper_cxx
void jasper::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	fReader.SetTree(tree);
}

Bool_t jasper::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef jasper_cxx
