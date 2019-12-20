//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Dec 20 13:09:52 2019 by ROOT version 6.18/04
// from TChain /
//////////////////////////////////////////////////////////

#ifndef pfff_h
#define pfff_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class pfff : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderArray<unsigned short> NeEvent_CsI_L = {fReader, "NeEvent.CsI_L[16]"};
   TTreeReaderArray<unsigned short> NeEvent_tCsI_L = {fReader, "NeEvent.tCsI_L[16]"};
   TTreeReaderArray<unsigned short> NeEvent_CsI_R = {fReader, "NeEvent.CsI_R[16]"};
   TTreeReaderArray<unsigned short> NeEvent_tCsI_R = {fReader, "NeEvent.tCsI_R[16]"};
   TTreeReaderArray<unsigned short> NeEvent_SQX_L = {fReader, "NeEvent.SQX_L[32]"};
   TTreeReaderArray<unsigned short> NeEvent_tSQX_L = {fReader, "NeEvent.tSQX_L[32]"};
   TTreeReaderArray<unsigned short> NeEvent_SQY_L = {fReader, "NeEvent.SQY_L[16]"};
   TTreeReaderArray<unsigned short> NeEvent_tSQY_L = {fReader, "NeEvent.tSQY_L[16]"};
   TTreeReaderArray<unsigned short> NeEvent_SQX_R = {fReader, "NeEvent.SQX_R[32]"};
   TTreeReaderArray<unsigned short> NeEvent_tSQX_R = {fReader, "NeEvent.tSQX_R[32]"};
   TTreeReaderArray<unsigned short> NeEvent_SQY_R = {fReader, "NeEvent.SQY_R[16]"};
   TTreeReaderArray<unsigned short> NeEvent_SQ300 = {fReader, "NeEvent.SQ300[16]"};
   TTreeReaderArray<unsigned short> NeEvent_tSQ300 = {fReader, "NeEvent.tSQ300[16]"};
   TTreeReaderArray<unsigned short> NeEvent_tSQY_R = {fReader, "NeEvent.tSQY_R[16]"};
   TTreeReaderArray<unsigned short> NeEvent_ANR = {fReader, "NeEvent.ANR[16]"};
   TTreeReaderArray<unsigned short> NeEvent_ANS = {fReader, "NeEvent.ANS[16]"};
   TTreeReaderArray<unsigned short> NeEvent_neutAmp = {fReader, "NeEvent.neutAmp[32]"};
   TTreeReaderArray<unsigned short> NeEvent_neutTAC = {fReader, "NeEvent.neutTAC[32]"};
   TTreeReaderArray<unsigned short> NeEvent_neutTDC = {fReader, "NeEvent.neutTDC[32]"};
   TTreeReaderArray<unsigned short> NeEvent_F3 = {fReader, "NeEvent.F3[4]"};
   TTreeReaderArray<unsigned short> NeEvent_tF3 = {fReader, "NeEvent.tF3[4]"};
   TTreeReaderArray<unsigned short> NeEvent_F5 = {fReader, "NeEvent.F5[4]"};
   TTreeReaderArray<unsigned short> NeEvent_tF5 = {fReader, "NeEvent.tF5[4]"};
   TTreeReaderArray<unsigned short> NeEvent_F6 = {fReader, "NeEvent.F6[4]"};
   TTreeReaderArray<unsigned short> NeEvent_tF6 = {fReader, "NeEvent.tF6[4]"};
   TTreeReaderArray<unsigned short> NeEvent_tMWPC = {fReader, "NeEvent.tMWPC[4]"};
   TTreeReaderArray<unsigned int> NeEvent_scaler = {fReader, "NeEvent.scaler[16]"};
   TTreeReaderValue<ULong_t> NeEvent_mtime = {fReader, "NeEvent.mtime"};
   TTreeReaderValue<unsigned short> NeEvent_nx1 = {fReader, "NeEvent.nx1"};
   TTreeReaderValue<unsigned short> NeEvent_ny1 = {fReader, "NeEvent.ny1"};
   TTreeReaderValue<unsigned short> NeEvent_nx2 = {fReader, "NeEvent.nx2"};
   TTreeReaderValue<unsigned short> NeEvent_ny2 = {fReader, "NeEvent.ny2"};
   TTreeReaderArray<unsigned short> NeEvent_x1 = {fReader, "NeEvent.x1[32]"};
   TTreeReaderArray<unsigned short> NeEvent_y1 = {fReader, "NeEvent.y1[32]"};
   TTreeReaderArray<unsigned short> NeEvent_x2 = {fReader, "NeEvent.x2[32]"};
   TTreeReaderArray<unsigned short> NeEvent_y2 = {fReader, "NeEvent.y2[32]"};
   TTreeReaderValue<unsigned int> NeEvent_rx1 = {fReader, "NeEvent.rx1"};
   TTreeReaderValue<unsigned int> NeEvent_rx2 = {fReader, "NeEvent.rx2"};
   TTreeReaderValue<unsigned int> NeEvent_ry1 = {fReader, "NeEvent.ry1"};
   TTreeReaderValue<unsigned int> NeEvent_ry2 = {fReader, "NeEvent.ry2"};
   TTreeReaderValue<Int_t> NeEvent_nevent = {fReader, "NeEvent.nevent"};
   TTreeReaderValue<Int_t> NeEvent_trigger = {fReader, "NeEvent.trigger"};
   TTreeReaderValue<Int_t> NeEvent_subevents = {fReader, "NeEvent.subevents"};
   TTreeReaderValue<Int_t> NeEvent_evsize = {fReader, "NeEvent.evsize"};


   pfff(TTree * /*tree*/ =0) { }
   virtual ~pfff() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(pfff,0);

};

#endif

#ifdef pfff_cxx
void pfff::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t pfff::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef pfff_cxx
