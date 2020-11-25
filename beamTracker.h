//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 16 10:52:51 2020 by ROOT version 6.18/04
// from TChain /
//////////////////////////////////////////////////////////

#ifndef beamTracker_h
#define beamTracker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <sys/ioctl.h> // For ioctl, TIOCGWINSZ
#include <unistd.h> // For STDOUT_FILENO

// Headers needed by this particular selector


class beamTracker : public TSelector {
public :
	TTreeReader	  fReader;  //!the tree reader
	TTree			 *fChain = 0;	//!pointer to the analyzed TTree or TChain

	TTreeReaderArray<unsigned short> in_CsI_R = {fReader, "NeEvent.CsI_R[16]"};
	TTreeReaderArray<unsigned short> in_tCsI_R = {fReader, "NeEvent.tCsI_R[16]"};
	TTreeReaderArray<unsigned short> in_SQX_R = {fReader, "NeEvent.SQX_R[32]"};
	TTreeReaderArray<unsigned short> in_tSQX_R = {fReader, "NeEvent.tSQX_R[32]"};
	TTreeReaderArray<unsigned short> in_SQY_R = {fReader, "NeEvent.SQY_R[16]"};
	TTreeReaderArray<unsigned short> in_tSQY_R = {fReader, "NeEvent.tSQY_R[16]"};

	TTreeReaderArray<unsigned short> F3 = {fReader, "NeEvent.F3[4]"};
	TTreeReaderArray<unsigned short> tF3 = {fReader, "NeEvent.tF3[4]"};
	TTreeReaderArray<unsigned short> F5 = {fReader, "NeEvent.F5[4]"};
	TTreeReaderArray<unsigned short> tF5 = {fReader, "NeEvent.tF5[4]"};
	TTreeReaderArray<unsigned short> inF6 = {fReader, "NeEvent.F6[4]"};
	TTreeReaderArray<unsigned short> intF6 = {fReader, "NeEvent.tF6[4]"};
	TTreeReaderArray<unsigned short> tMWPC = {fReader, "NeEvent.tMWPC[4]"};

	TTreeReaderValue<unsigned short> nx1 = {fReader, "NeEvent.nx1"};
	TTreeReaderValue<unsigned short> ny1 = {fReader, "NeEvent.ny1"};
	TTreeReaderValue<unsigned short> nx2 = {fReader, "NeEvent.nx2"};
	TTreeReaderValue<unsigned short> ny2 = {fReader, "NeEvent.ny2"};

	TTreeReaderArray<unsigned short> x1 = {fReader, "NeEvent.x1[32]"};
	TTreeReaderArray<unsigned short> y1 = {fReader, "NeEvent.y1[32]"};
	TTreeReaderArray<unsigned short> x2 = {fReader, "NeEvent.x2[32]"};
	TTreeReaderArray<unsigned short> y2 = {fReader, "NeEvent.y2[32]"};


	TCutG *deHe;
	TCutG *deLi;
	TCutG *yCut, *xCut, *dehe;
	TOOL *maynard;
	TFile *outF;
	TTree *outTree;
	Long64_t nEntries;
	Bool_t fMWPC, fTDC, fMulti, fdehe, fxfit, fyfit;
	Int_t geo, run;

	double dX; double dY; double dZ;
	double fMWPC_1_X;
	double fMWPC_1_Y;
	double fMWPC_2_X;
	double fMWPC_2_Y;
	double fMWPC_1_Z;
	double fMWPC_2_Z;

	double F6[4], tF6[4];

	double evX;
	double evY;
	double evZ;

	double X6He; double X6Helab; double X6Hedet;
	double Y6He; double Y6Helab; double Y6Hedet;
	double Z6He; double Z6Helab; double Z6Hedet;

	double sqrde, fsqrde, sqretot, kinE, tof;

	Int_t SQX_R_strip, SQY_R_strip, CsI_R_strip;

	Float_t a_SQX_R[32];
	Float_t b_SQX_R[32];
	Float_t a_SQY_R[16];
	Float_t b_SQY_R[16];
	Float_t a_CsI_R[16];
	Float_t b_CsI_R[16];
	Double_t SQX_R[32];
	Double_t SQY_R[16];
	Double_t CsI_R[16];
	Float_t MWPC_1_X, MWPC_2_X, MWPC_1_Y, MWPC_2_Y, MWPC_1_Z, MWPC_2_Z;

	beamTracker(TTree * /*tree*/ =0) { }
	virtual ~beamTracker() { }
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
	unsigned short temp_x1[32], temp_x2[32], temp_y1[32], temp_y2[32];
	bool Get_MWPC_pos(UShort_t multi, unsigned short *wireNo, Float_t *MWPC_pos, Short_t MWPC_id);
	TRandom3 *rnd;
	float progress = 0.0;
	int consoleWidth;

	ClassDef(beamTracker,0);

};

#endif

#ifdef beamTracker_cxx
void beamTracker::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	fReader.SetTree(tree);
}

Bool_t beamTracker::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef beamTracker_cxx
