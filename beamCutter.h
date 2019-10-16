//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 10 14:48:28 2019 by ROOT version 6.12/06
// from TChain /
//////////////////////////////////////////////////////////

#ifndef beamCutter_h
#define beamCutter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include "constants.h"
#include <sys/ioctl.h> // For ioctl, TIOCGWINSZ
#include <unistd.h> // For STDOUT_FILENO

// Headers needed by this particular selector


class beamCutter : public TSelector {
public :
	TTreeReader	  fReader;  //!the tree reader
	TTree			 *fChain = 0;	//!pointer to the analyzed TTree or TChain
	TFile *outF;
	TTree *outTree;
	Long64_t nEntries;

	// Readers to access the data (delete the ones you do not need).
	TTreeReaderArray<unsigned short> F3 = {fReader, "NeEvent.F3[4]"};	
	TTreeReaderArray<unsigned short> tF3 = {fReader, "NeEvent.tF3[4]"};
	TTreeReaderArray<unsigned short> F5 = {fReader, "NeEvent.F5[4]"};
	TTreeReaderArray<unsigned short> tF5 = {fReader, "NeEvent.tF5[4]"};
	TTreeReaderArray<unsigned short> F6 = {fReader, "NeEvent.F6[4]"};
	TTreeReaderArray<unsigned short> tF6 = {fReader, "NeEvent.tF6[4]"};
	TTreeReaderValue<unsigned short> nx1 = {fReader, "NeEvent.nx1"};
	TTreeReaderValue<unsigned short> ny1 = {fReader, "NeEvent.ny1"};
	TTreeReaderValue<unsigned short> nx2 = {fReader, "NeEvent.nx2"};
	TTreeReaderValue<unsigned short> ny2 = {fReader, "NeEvent.ny2"};
	TTreeReaderArray<unsigned short> x1 = {fReader, "NeEvent.x1[32]"};
	TTreeReaderArray<unsigned short> y1 = {fReader, "NeEvent.y1[32]"};
	TTreeReaderArray<unsigned short> x2 = {fReader, "NeEvent.x2[32]"};
	TTreeReaderArray<unsigned short> y2 = {fReader, "NeEvent.y2[32]"};
	TTreeReaderValue<int> trigger = {fReader, "NeEvent.trigger"};

	beamCutter(TTree * /*tree*/ =0) { }
	virtual ~beamCutter() { }
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

	ClassDef(beamCutter,0);
	Float_t displacement, zero_position, tof, beta_squared, mass, gamma, kinE;
	Float_t MWPC_1_X, MWPC_2_X, MWPC_1_Y, MWPC_2_Y, MWPC_1_Z, MWPC_2_Z;
	Float_t dX, dY, dZ, mom_beam, ene_beam;
	unsigned short temp_x1[32], temp_x2[32], temp_y1[32], temp_y2[32];
	bool Get_MWPC_pos(UShort_t multi, unsigned short *wireNo, Float_t *MWPC_pos, Short_t MWPC_id);
	bool tac, range;
	TVector3 *vBeam;
	TLorentzVector *lvBeam;
	TRandom3 *rnd;
	float progress = 0.0;
	int consoleWidth;

};

#endif

#ifdef beamCutter_cxx
void beamCutter::Init(TTree *tree)
{
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the reader is initialized.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	fReader.SetTree(tree);
}

Bool_t beamCutter::Notify()
{
	// The Notify() function is called when a new file is opened. This
	// can be either for a new TTree in a TChain or when when a new TTree
	// is started when using PROOF. It is normally not necessary to make changes
	// to the generated code, but the routine can be extended by the
	// user if needed. The return value is currently not used.

	return kTRUE;
}


#endif // #ifdef beamCutter_cxx
