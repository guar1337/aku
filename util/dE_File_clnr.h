//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jan 28 15:55:12 2019 by ROOT version 6.12/06
// from TTree dE_angle/dE_angle
// found on file: /home/guar/data/mar2018/dE/geo1/dE_geo1.root
//////////////////////////////////////////////////////////

#ifndef dE_File_clnr_h
#define dE_File_clnr_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include "TLorentzVector.h"



class dE_File_clnr : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
   TFile *outF;
   TTree *outTree;

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Short_t> SQX_L_m = {fReader, "SQX_L_m"};
   TTreeReaderValue<Short_t> SQX_R_m = {fReader, "SQX_R_m"};
   TTreeReaderValue<Short_t> SQY_L_m = {fReader, "SQY_L_m"};
   TTreeReaderValue<Short_t> SQY_R_m = {fReader, "SQY_R_m"};
   TTreeReaderValue<Short_t> CsI_L_m = {fReader, "CsI_L_m"};
   TTreeReaderValue<Short_t> CsI_R_m = {fReader, "CsI_R_m"};
   TTreeReaderArray<Double_t> tSQX_L = {fReader, "tSQX_L"};
   TTreeReaderArray<Double_t> tSQX_R = {fReader, "tSQX_R"};
   TTreeReaderArray<Double_t> tSQY_L = {fReader, "tSQY_L"};
   TTreeReaderArray<Double_t> tSQY_R = {fReader, "tSQY_R"};
   TTreeReaderArray<Double_t> tCsI_L = {fReader, "tCsI_L"};
   TTreeReaderArray<Double_t> tCsI_R = {fReader, "tCsI_R"};
   TTreeReaderArray<Double_t> SQY_L_e = {fReader, "SQY_L_e"};
   TTreeReaderArray<Double_t> SQY_R_e = {fReader, "SQY_R_e"};
   TTreeReaderArray<Double_t> SQX_L_e = {fReader, "SQX_L_e"};
   TTreeReaderArray<Double_t> SQX_R_e = {fReader, "SQX_R_e"};
   TTreeReaderArray<Double_t> CsI_L_e = {fReader, "CsI_L_e"};
   TTreeReaderArray<Double_t> CsI_R_e = {fReader, "CsI_R_e"};
   TTreeReaderArray<Short_t> SQX_L_s = {fReader, "SQX_L_s"};
   TTreeReaderArray<Short_t> SQX_R_s = {fReader, "SQX_R_s"};
   TTreeReaderArray<Short_t> SQY_L_s = {fReader, "SQY_L_s"};
   TTreeReaderArray<Short_t> SQY_R_s = {fReader, "SQY_R_s"};
   TTreeReaderArray<Short_t> CsI_L_s = {fReader, "CsI_L_s"};
   TTreeReaderArray<Short_t> CsI_R_s = {fReader, "CsI_R_s"};
   TTreeReaderValue<Double_t> sqlde = {fReader, "sqlde"};
   TTreeReaderValue<Double_t> sqletot = {fReader, "sqletot"};
   TTreeReaderValue<Double_t> sqlphi = {fReader, "sqlphi"};
   TTreeReaderValue<Double_t> sqltheta = {fReader, "sqltheta"};
   TTreeReaderValue<Double_t> sqlang = {fReader, "sqlang"};
   TTreeReaderValue<Double_t> sqlxtime = {fReader, "sqlxtime"};
   TTreeReaderValue<Double_t> sqlytime = {fReader, "sqlytime"};
   TTreeReaderValue<Double_t> fsqltheta_1H = {fReader, "fsqltheta_1H"};
   TTreeReaderValue<Double_t> fsqltheta_2H = {fReader, "fsqltheta_2H"};
   TTreeReaderValue<Double_t> kinsqle_1H = {fReader, "kinsqle_1H"};
   TTreeReaderValue<Double_t> kinsqle_2H = {fReader, "kinsqle_2H"};
   TTreeReaderValue<Double_t> sqrde = {fReader, "sqrde"};
   TTreeReaderValue<Double_t> sqretot = {fReader, "sqretot"};
   TTreeReaderValue<Double_t> sqrtheta = {fReader, "sqrtheta"};
   TTreeReaderValue<Double_t> sqrphi = {fReader, "sqrphi"};
   TTreeReaderValue<Double_t> sqrang = {fReader, "sqrang"};
   TTreeReaderValue<Double_t> sqrxtime = {fReader, "sqrxtime"};
   TTreeReaderValue<Double_t> sqrytime = {fReader, "sqrytime"};
   TTreeReaderValue<Double_t> fsqrtheta1 = {fReader, "fsqrtheta1"};
   TTreeReaderValue<Double_t> fsqrtheta2 = {fReader, "fsqrtheta2"};
   TTreeReaderValue<Short_t> s_csir = {fReader, "s_csir"};
   TTreeReaderValue<Short_t> s_csil = {fReader, "s_csil"};
   TTreeReaderValue<Float_t> X2H = {fReader, "X2H"};
   TTreeReaderValue<Float_t> Y2H = {fReader, "Y2H"};
   TTreeReaderValue<Float_t> Z2H = {fReader, "Z2H"};
   TTreeReaderValue<Float_t> X6He = {fReader, "X6He"};
   TTreeReaderValue<Float_t> Y6He = {fReader, "Y6He"};
   TTreeReaderValue<Float_t> Z6He = {fReader, "Z6He"};
   TTreeReaderValue<Float_t> evX = {fReader, "evX"};
   TTreeReaderValue<Float_t> evY = {fReader, "evY"};
   TTreeReaderValue<Float_t> evZ = {fReader, "evZ"};
   TTreeReaderValue<Float_t> f6X = {fReader, "f6X"};
   TTreeReaderValue<Float_t> f6Y = {fReader, "f6Y"};
   TTreeReaderValue<Float_t> f6Z = {fReader, "f6Z"};
   TTreeReaderValue<Float_t> f5X = {fReader, "f5X"};
   TTreeReaderValue<Float_t> f5Y = {fReader, "f5Y"};
   TTreeReaderValue<Float_t> f5Z = {fReader, "f5Z"};
   TTreeReaderArray<Double_t> tF3 = {fReader, "tF3"};
   TTreeReaderArray<Double_t> F3 = {fReader, "F3"};
   TTreeReaderArray<Double_t> tF5 = {fReader, "tF5"};
   TTreeReaderArray<Double_t> F5 = {fReader, "F5"};
   TTreeReaderArray<Double_t> tF6 = {fReader, "tF6"};
   TTreeReaderArray<Double_t> F6 = {fReader, "F6"};
   TTreeReaderValue<Double_t> tof = {fReader, "tof"};
   TTreeReaderValue<Double_t> aF5 = {fReader, "aF5"};
   TTreeReaderValue<Double_t> az = {fReader, "az"};
   TTreeReaderValue<Double_t> T1 = {fReader, "T1"};
   TTreeReaderValue<Double_t> T2 = {fReader, "T2"};
   TTreeReaderValue<Short_t> ion = {fReader, "ion"};
   TTreeReaderValue<Short_t> geo = {fReader, "geo"};
   TTreeReaderValue<Short_t> run = {fReader, "run"};
   TTreeReaderArray<UShort_t> x1 = {fReader, "x1"};
   TTreeReaderArray<UShort_t> x2 = {fReader, "x2"};
   TTreeReaderArray<UShort_t> y1 = {fReader, "y1"};
   TTreeReaderArray<UShort_t> y2 = {fReader, "y2"};
   TTreeReaderValue<UShort_t> nx1 = {fReader, "nx1"};
   TTreeReaderValue<UShort_t> nx2 = {fReader, "nx2"};
   TTreeReaderValue<UShort_t> ny1 = {fReader, "ny1"};
   TTreeReaderValue<UShort_t> ny2 = {fReader, "ny2"};
   TTreeReaderArray<Float_t> tMWPC = {fReader, "tMWPC"};
   TTreeReaderValue<Short_t> trigger = {fReader, "trigger"};
   TTreeReaderValue<Double_t> mml = {fReader, "mml"};
   TTreeReaderArray<Double_t> c_SQX_L = {fReader, "c_SQX_L"};
   TTreeReaderArray<Double_t> c_SQX_R = {fReader, "c_SQX_R"};
   TTreeReaderArray<Double_t> c_SQY_L = {fReader, "c_SQY_L"};
   TTreeReaderArray<Double_t> c_SQY_R = {fReader, "c_SQY_R"};
   TTreeReaderArray<Double_t> c_CsI_L = {fReader, "c_CsI_L"};
   TTreeReaderArray<Double_t> c_CsI_R = {fReader, "c_CsI_R"};

   TTreeReaderValue<Bool_t> he6 = {fReader, "he6"};
   TTreeReaderValue<Bool_t> angAng1H = {fReader, "angAng1H"};
   TTreeReaderValue<Bool_t> angAng2H = {fReader, "angAng2H"};
   TTreeReaderValue<TLorentzVector> LV_6He = {fReader, "LV_6He."};
   TTreeReaderValue<TLorentzVector> LV_2H = {fReader, "LV_2H."};
   TTreeReaderValue<TLorentzVector> LV_beam = {fReader, "LV_beam."};

   Double_t  out_tSQX_L;
   Double_t  out_tSQX_R;

   Double_t out_SQX_L_Edep;
   Double_t out_SQX_R_Edep;
   Double_t out_CsI_L_Edep;
   Double_t out_CsI_R_Edep;

   Short_t out_SQX_L_strip;
   Short_t out_SQX_R_strip;
   Short_t out_SQY_L_strip;
   Short_t out_SQY_R_strip;
   Short_t out_CsI_L_strip;
   Short_t out_CsI_R_strip;

   Float_t out_evX;
   Float_t out_evY;
   Float_t out_evZ;

   Double_t  out_tof;
   Double_t  out_aF5;

   TLorentzVector *out_LV_beam;
   Bool_t out_angAng1H;
   Bool_t out_angAng2H;
   Long64_t counter;

   dE_File_clnr(TTree * /*tree*/ =0) { }
   virtual ~dE_File_clnr() { }
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

   ClassDef(dE_File_clnr,0);

};

#endif

#ifdef dE_File_clnr_cxx
void dE_File_clnr::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t dE_File_clnr::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef dE_File_clnr_cxx
