TTree * inTree =NULL;
TTree * outTree=NULL;
#include "interface.h"
#include <iostream>
#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
  R__LOAD_LIBRARY(libPhysics.so); // !! IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** instead of
  R__LOAD_LIBRARY(libgsl.so);     //                        **R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
  R__LOAD_LIBRARY(/home/guar/aku/libEloss.so);
  
void butler()
{
  gSystem->cd(s::work_dir.Data()); 
  TString inFname("he6_7_cal");
  TString outFname(inFname.Copy().ReplaceAll("_cal","").Data()); 

  TFile *inF  = new TFile((inFname.Append(".root").Data()), "READ");
  TFile *outF = new TFile(outFname.Append("_dE_work.root").Data(),"recreate");
  TTree *inTree = (TTree*)inF->Get("calibrated");
  TTree *outTree= new TTree("dE_E","he6");

  AL *b  = new dE_E_angle(inTree,outTree);

  b->actual_work();
  inF->Close();
  outF->cd();
  outTree->Write();
  outF->Close();

}




