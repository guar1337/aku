//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr	9 11:42:44 2019 by ROOT version 6.12/06
// from TTree simevents/MC events
// found on file: /home/zalewski/aku/geant4/build/gurney.root
//////////////////////////////////////////////////////////

#ifndef jasperNo5_h
#define jasperNo5_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include "TLorentzVector.h"



class jasperNo5 : public TSelector {
public :
	TTreeReader		fReader;	//!the tree reader
	TTree			 *fChain = 0;	//!pointer to the analyzed TTree or TChain
	TFile *outF;
	TTree *outTree;

	// Readers to access the data (delete the ones you do not need).
	TTreeReaderValue<TLorentzVector> lvBeam = {fReader, "lvBeam."};
	TTreeReaderValue<TLorentzVector> lv2H = {fReader, "lv2H."};
	TTreeReaderValue<TLorentzVector> lv6He = {fReader, "lv6He."};
	TTreeReaderValue<TLorentzVector> lv2H_CM = {fReader, "lv2H_CM."};
	TTreeReaderValue<TLorentzVector> lv6He_CM = {fReader, "lv6He_CM."};
	TTreeReaderArray<Double_t> CsIdeut = {fReader, "CsIdeut"};
	TTreeReaderArray<Double_t> SideutX = {fReader, "SideutX"};
	TTreeReaderArray<Double_t> SideutY = {fReader, "SideutY"};
	TTreeReaderValue<Double_t> sqlang = {fReader, "sqlang"};
	TTreeReaderValue<Double_t> fsqlang = {fReader, "fsqlang"};
	TTreeReaderValue<Double_t> sqlde = {fReader, "sqlde"};
	TTreeReaderValue<Double_t> sqletot = {fReader, "sqletot"};
	TTreeReaderValue<Double_t> sqlphi = {fReader, "sqlphi"};
	TTreeReaderValue<Double_t> sqltheta = {fReader, "sqltheta"};
	TTreeReaderArray<Double_t> CsIhe = {fReader, "CsIhe"};
	TTreeReaderArray<Double_t> SiheY = {fReader, "SiheY"};
	TTreeReaderArray<Double_t> SiheX = {fReader, "SiheX"};
	TTreeReaderValue<Double_t> sqrang = {fReader, "sqrang"};
	TTreeReaderValue<Double_t> sqrde = {fReader, "sqrde"};
	TTreeReaderValue<Double_t> sqretot = {fReader, "sqretot"};
	TTreeReaderValue<Double_t> sqrphi = {fReader, "sqrphi"};
	TTreeReaderValue<Double_t> sqrtheta = {fReader, "sqrtheta"};
	TTreeReaderValue<Double_t> fsqrang = {fReader, "fsqrang"};
	TTreeReaderValue<Double_t> beamT = {fReader, "beamT"};
	TTreeReaderValue<Double_t> thetaCM = {fReader, "thetaCM"};
	TTreeReaderValue<Double_t> phiCM = {fReader, "phiCM"};
	TTreeReaderValue<Double_t> evx = {fReader, "evx"};
	TTreeReaderValue<Double_t> evy = {fReader, "evy"};
	TTreeReaderValue<Double_t> evz = {fReader, "evz"};
	TTreeReaderValue<Double_t> X6He = {fReader, "X6He"};
	TTreeReaderValue<Double_t> Y6He = {fReader, "Y6He"};
	TTreeReaderValue<Double_t> Z6He = {fReader, "Z6He"};
	TTreeReaderValue<Double_t> X2H = {fReader, "X2H"};
	TTreeReaderValue<Double_t> Y2H = {fReader, "Y2H"};
	TTreeReaderValue<Double_t> Z2H = {fReader, "Z2H"};
	TTreeReaderValue<Char_t> fEve2H = {fReader, "fEve2H"};


	Int_t Sideut_multY;
	Int_t Sideut_multX;
	Int_t Sihe_multX;
	Int_t Sihe_multY;
	//int mult_0_count, mult_1_count, mult_2_count, mult_3_count;
	Double_t m_sqlang, m_sqrang, m_sqldist, m_sqrdist;
	Double_t m_sqrDetAng;
	Double_t hX1, hY1, hZ1;
	Double_t dX, dY, dZ, hX, hY, hZ;
	Double_t fdX, fdY, fdZ, fhX, fhY, fhZ;
	Double_t dX0, dY0, dZ0, hX0, hY0, hZ0;
	Double_t out_evX, out_evY, out_evZ;
	Double_t out_sqlang, out_sqrang, out_fsqlang, out_fsqrang;
	Double_t out_fsqlangg, out_fsqrangg;
	Int_t SQX_L_s, SQY_L_s, SQX_R_s, SQY_R_s;
	const Double_t width_strip_X{58.0/32.0};
	const Double_t width_strip_Y{58.0/16.0};
	TRandom3 *rnd;
	TVector3 *v2H, *v6He, *vf2H, *vf6He;
	//Double_t reco_sqlang, reco_sqrang;
	std::vector<float> reco_sqlang;
	std::vector<float> reco_sqrang;



	jasperNo5(TTree * /*tree*/ =0) { }
	virtual ~jasperNo5() { }
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

	ClassDef(jasperNo5,0);

};

#endif

#ifdef jasperNo5_cxx
void jasperNo5::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	fReader.SetTree(tree);
}

Bool_t jasperNo5::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef jasperNo5_cxx
