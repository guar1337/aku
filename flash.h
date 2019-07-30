//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 16 13:46:16 2019 by ROOT version 6.12/06
// from TTree dE_angle/dE_angle
// found on file: /home/guar/data/he6_d/dE/geo1/PG_deu1.root
//////////////////////////////////////////////////////////

#ifndef flash_h
#define flash_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include "constants.h"

// Headers needed by this particular selector
#include "TLorentzVector.h"



class flash : public TSelector {
public :
	TTreeReader	fReader;  //!the tree reader
	TTree	*fChain = 0;	//!pointer to the analyzed TTree or TChain

	TTreeReaderValue<Float_t> SQX_L_sNo = {fReader, "SQX_L_sNo"};
	TTreeReaderValue<Float_t> SQX_R_sNo = {fReader, "SQX_R_sNo"};
	TTreeReaderValue<Float_t> SQY_L_sNo = {fReader, "SQY_L_sNo"};
	TTreeReaderValue<Float_t> SQY_R_sNo = {fReader, "SQY_R_sNo"};
	TTreeReaderValue<Double_t> sqlde = {fReader, "sqlde"};
	TTreeReaderValue<Double_t> sqletot = {fReader, "sqletot"};
	//TTreeReaderValue<Double_t> sqlang = {fReader, "sqlang"};
	TTreeReaderValue<Double_t> sqrde = {fReader, "sqrde"};
	TTreeReaderValue<Double_t> sqretot = {fReader, "sqretot"};
	//TTreeReaderValue<Double_t> sqrang = {fReader, "sqrang"};
	TTreeReaderValue<Float_t> evX = {fReader, "evX"};
	TTreeReaderValue<Float_t> evY = {fReader, "evY"};
	TTreeReaderValue<Float_t> evZ = {fReader, "evZ"};
	TTreeReaderValue<Float_t> dX = {fReader, "dX"};
	TTreeReaderValue<Float_t> dY = {fReader, "dY"};
	TTreeReaderValue<Float_t> dZ = {fReader, "dZ"};
	TTreeReaderValue<Short_t> geo = {fReader, "geo"};
	TTreeReaderValue<Bool_t> deu = {fReader, "deu"};
	TTreeReaderValue<Bool_t> pro = {fReader, "pro"};
	TTreeReaderValue<Double_t> kinE = {fReader, "kinE"};
	TTreeReaderValue<TLorentzVector> lvBeam = {fReader, "LV_beam."};


	flash(TTree * /*tree*/ =0) { }
	virtual ~flash() { }
	Float_t getVelo(Float_t T, Float_t mass);
	virtual Int_t	Version() const { return 2; }
	virtual void	Begin(TTree *tree);
	virtual void	SlaveBegin(TTree *tree);
	virtual void	Init(TTree *tree);
	virtual Bool_t  Notify();
	virtual Bool_t  Process(Long64_t entry);
	virtual Int_t	GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
	virtual void	SetOption(const char *option) { fOption = option; }
	virtual void	SetObject(TObject *obj) { fObject = obj; }
	virtual void	SetInputList(TList *input) { fInput = input; }
	virtual TList  *GetOutputList() const { return fOutput; }
	virtual void	SlaveTerminate();
	virtual void	Terminate();

private:

	Float_t tar_pos_Z, tar_thcknss, tar_angle, SQL_ang, SQR_ang, SQL_dist, SQR_dist, lvsqlang, lvsqrang, tar;
	Float_t X2H_lab, Y2H_lab, Z2H_lab, X6He_lab, Y6He_lab, Z6He_lab;
	Float_t X2H_det, Y2H_det, Z2H_det, X6He_det, Y6He_det, Z6He_det;
	Float_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
	Float_t sqlphi, sqltheta, sqrphi, sqrtheta, mml, sqlang, sqrang;
	Float_t ene_1H, ene_2H, mom_1H, mom_2H;
	Float_t fEproFromLang, fEdeuFromLang, fsqltheta_1H, fsqltheta_2H, fsqrang1H, fsqrang2H;
	Float_t inputPars[4];
	TRandom3 *rnd;
	TH1 *hist_mml1, *hist_mml2;
	TGraph *lang_vs_rang_1H, *lang_vs_rang_2H;
	Float_t velo_hel, velo_beam, vel_R, beta_squared, gamma, gamma_squared, beta;

	Double_t si_A[1], si_Z[1], si_W[1];
	Double_t CD2_A[2], CD2_Z[2], CD2_W[2];

	AELC *h2_Si, *h2_CD2, *h1_Si, *h1_CD2;

	TVector3 *vBeam, v6He;
	TLorentzVector *lvH1, *lvH2, *lvHe6, *lvTar1H, *lvTar2H;
	TF1 *fit1, *fit2;

	std::vector<Float_t> vec_lang_1H;
	std::vector<Float_t> vec_rang_1H;
	std::vector<Float_t> vec_lang_2H;
	std::vector<Float_t> vec_rang_2H;

	ClassDef(flash,0);	

};

#endif

#ifdef flash_cxx
void flash::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	fReader.SetTree(tree);
}

Bool_t flash::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef flash_cxx
