#include <iostream>
  R__LOAD_LIBRARY(libPhysics.so); // !! IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** instead of
  R__LOAD_LIBRARY(libgsl.so);     //                        **R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
  R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);
  
void
butler()
{
  //TFile* in =new TFile(ifilename);
  //inTree= (TTree*) in->Get("simevents");
  //tree_in->Print();
  //TFile * out=new TFile(ofilename,"recreate");
  //outTree = new TTree("Reconstructed","output tree");

  AL *b  = new trial(/*inTree,outTree*/);
  b->Reconstruction();
  //in->Close();
  //out->cd();
  //outTree->Write();
  //out->Close();

}
