//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 28 08:59:18 2019 by ROOT version 6.12/06
// from TTree cropped/cropped file
// found on file: /home/guar/data/mar2018/dE/geo1/fastAna.root
//////////////////////////////////////////////////////////

#ifndef newDawn_h
#define newDawn_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector


class newDawn : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> tSQX_L = {fReader, "tSQX_L"};
   TTreeReaderValue<Double_t> tSQX_R = {fReader, "tSQX_R"};
   TTreeReaderValue<Double_t> SQY_L_e = {fReader, "SQY_L_e"};
   TTreeReaderValue<Double_t> SQY_R_e = {fReader, "SQY_R_e"};
   TTreeReaderValue<Double_t> SQX_L_e = {fReader, "SQX_L_e"};
   TTreeReaderValue<Double_t> SQX_R_e = {fReader, "SQX_R_e"};
   TTreeReaderValue<Double_t> CsI_L_e = {fReader, "CsI_L_e"};
   TTreeReaderValue<Double_t> CsI_R_e = {fReader, "CsI_R_e"};
   TTreeReaderValue<Short_t> SQX_L_s = {fReader, "SQX_L_s"};
   TTreeReaderValue<Short_t> SQX_R_s = {fReader, "SQX_R_s"};
   TTreeReaderValue<Short_t> SQY_L_s = {fReader, "SQY_L_s"};
   TTreeReaderValue<Short_t> SQY_R_s = {fReader, "SQY_R_s"};
   TTreeReaderValue<Short_t> CsI_L_s = {fReader, "CsI_L_s"};
   TTreeReaderValue<Short_t> CsI_R_s = {fReader, "CsI_R_s"};
   TTreeReaderValue<Float_t> evX = {fReader, "evX"};
   TTreeReaderValue<Float_t> evY = {fReader, "evY"};
   TTreeReaderValue<Float_t> evZ = {fReader, "evZ"};
   TTreeReaderValue<Double_t> tof = {fReader, "tof"};
   TTreeReaderValue<Double_t> aF5 = {fReader, "aF5"};


   newDawn(TTree * /*tree*/ =0) { }
   virtual ~newDawn() { }
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

   ClassDef(newDawn,0);

};

#endif

#ifdef newDawn_cxx
void newDawn::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t newDawn::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef newDawn_cxx
