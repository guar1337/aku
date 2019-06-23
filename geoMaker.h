//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 13 15:13:01 2019 by ROOT version 6.12/06
// from TChain /
//////////////////////////////////////////////////////////

#ifndef geoMaker_h
#define geoMaker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <iterator>

// Headers needed by this particular selector


class geoMaker : public TSelector {
public :
	TTreeReader	  fReader;  //!the tree reader
	TTree			 *fChain = 0;	//!pointer to the analyzed TTree or TChain

	// Readers to access the data (delete the ones you do not need).
	TTreeReaderArray<unsigned short> CsI_L = {fReader, "NeEvent.CsI_L[16]"};
	TTreeReaderArray<unsigned short> tCsI_L = {fReader, "NeEvent.tCsI_L[16]"};
	TTreeReaderArray<unsigned short> CsI_R = {fReader, "NeEvent.CsI_R[16]"};
	TTreeReaderArray<unsigned short> tCsI_R = {fReader, "NeEvent.tCsI_R[16]"};
	TTreeReaderArray<unsigned short> SQX_L = {fReader, "NeEvent.SQX_L[32]"};
	TTreeReaderArray<unsigned short> tSQX_L = {fReader, "NeEvent.tSQX_L[32]"};
	TTreeReaderArray<unsigned short> SQY_L = {fReader, "NeEvent.SQY_L[16]"};
	TTreeReaderArray<unsigned short> tSQY_L = {fReader, "NeEvent.tSQY_L[16]"};
	TTreeReaderArray<unsigned short> SQX_R = {fReader, "NeEvent.SQX_R[32]"};
	TTreeReaderArray<unsigned short> tSQX_R = {fReader, "NeEvent.tSQX_R[32]"};
	TTreeReaderArray<unsigned short> SQY_R = {fReader, "NeEvent.SQY_R[16]"};
	TTreeReaderArray<unsigned short> tSQY_R = {fReader, "NeEvent.tSQY_R[16]"};
	TTreeReaderArray<unsigned short> ANR = {fReader, "NeEvent.ANR[16]"};
	TTreeReaderArray<unsigned short> ANS = {fReader, "NeEvent.ANS[16]"};
	TTreeReaderArray<unsigned short> neutAmp = {fReader, "NeEvent.neutAmp[32]"};
	TTreeReaderArray<unsigned short> neutTAC = {fReader, "NeEvent.neutTAC[32]"};
	TTreeReaderArray<unsigned short> neutTDC = {fReader, "NeEvent.neutTDC[32]"};
	TTreeReaderArray<unsigned short> F3 = {fReader, "NeEvent.F3[4]"};
	TTreeReaderArray<unsigned short> tF3 = {fReader, "NeEvent.tF3[4]"};
	TTreeReaderArray<unsigned short> F5 = {fReader, "NeEvent.F5[4]"};
	TTreeReaderArray<unsigned short> tF5 = {fReader, "NeEvent.tF5[4]"};
	TTreeReaderArray<unsigned short> F6 = {fReader, "NeEvent.F6[4]"};
	TTreeReaderArray<unsigned short> tF6 = {fReader, "NeEvent.tF6[4]"};
	TTreeReaderArray<unsigned short> tMWPC = {fReader, "NeEvent.tMWPC[4]"};
	TTreeReaderValue<unsigned short> nx1 = {fReader, "NeEvent.nx1"};
	TTreeReaderValue<unsigned short> ny1 = {fReader, "NeEvent.ny1"};
	TTreeReaderValue<unsigned short> nx2 = {fReader, "NeEvent.nx2"};
	TTreeReaderValue<unsigned short> ny2 = {fReader, "NeEvent.ny2"};
	TTreeReaderArray<unsigned short> x1 = {fReader, "NeEvent.x1[32]"};
	TTreeReaderArray<unsigned short> y1 = {fReader, "NeEvent.y1[32]"};
	TTreeReaderArray<unsigned short> x2 = {fReader, "NeEvent.x2[32]"};
	TTreeReaderArray<unsigned short> y2 = {fReader, "NeEvent.y2[32]"};
	TTreeReaderValue<Int_t> nevent = {fReader, "NeEvent.nevent"};
	TTreeReaderValue<Int_t> trigger = {fReader, "NeEvent.trigger"};
	TTreeReaderValue<Int_t> subevents = {fReader, "NeEvent.subevents"};
	TTreeReaderValue<Int_t> evsize = {fReader, "NeEvent.evsize"};

	Float_t	MWPC_1_X, MWPC_1_Y, MWPC_1_Z;
	Float_t MWPC_2_X, MWPC_2_Y, MWPC_2_Z;
	Double_t dX, dY, dZ, tar_angle, tar_pos_Z;
	Double_t detX, detY, detZ;
	Int_t SQX_R_mult, SQY_R_mult, SQX_R_strip, SQY_R_strip;
	Int_t SQX_L_mult, SQY_L_mult, SQX_L_strip, SQY_L_strip;

	Double_t	X6He_lab, Y6He_lab, Z6He_lab, SQR_dist, SQR_ang;
	Double_t X6He_det, Y6He_det, Z6He_det;
	Double_t	X2H_lab, Y2H_lab, Z2H_lab, SQL_dist, SQL_ang;
	Double_t X2H_det, Y2H_det, Z2H_det;
	Float_t displacement, zero_position, evX, evY, evZ, Tcoef;
	unsigned short temp_x1[32], temp_x2[32], temp_y1[32], temp_y2[32];
	TRandom3 *rnd;
	TH1F *diffX, *diffY, *diffZ;
	TString option;


	bool Get_MWPC_pos(UShort_t multi, unsigned short *wireNo, Float_t *MWPC_pos, Short_t MWPC_id);

	geoMaker(TTree * /*tree*/ =0) { }
	virtual ~geoMaker() { }
	virtual Int_t	Version() const { return 2; }
	virtual void	 Begin(TTree *tree);
	virtual void	 SlaveBegin(TTree *tree);
	virtual void	 Init(TTree *tree);
	virtual Bool_t  Notify();
	virtual Bool_t  Process(Long64_t entry);
	virtual Int_t	GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
	virtual void	 SetOption(const char *option) { fOption = option; }
	virtual void	 SetObject(TObject *obj) { fObject = obj; }
	virtual void	 SetInputList(TList *input) { fInput = input; }
	virtual TList  *GetOutputList() const { return fOutput; }
	virtual void	 SlaveTerminate();
	virtual void	 Terminate();

	ClassDef(geoMaker,0);

};

#endif

#ifdef geoMaker_cxx
void geoMaker::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	fReader.SetTree(tree);
}

Bool_t geoMaker::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef geoMaker_cxx
