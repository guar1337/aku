#define dE_File_clnr_cxx
// The class definition in dE_File_clnr.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("dE_File_clnr.C")
// root> T->Process("dE_File_clnr.C","some options")
// root> T->Process("dE_File_clnr.C+")
//


#include "dE_File_clnr.h"
#include <TH2.h>
#include <TStyle.h>

void dE_File_clnr::Begin(TTree *tree)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
   outF = new TFile("/home/zalewski/data/mar2018/dE/geos/shortF.root","RECREATE");
   outTree = new TTree("shortT","cropped_tree");

   outTree->Branch("tSQX_L",  &out_tSQX_L,    "tSQX_L/D");
   outTree->Branch("tSQX_R",  &out_tSQX_R,    "tSQX_R/D");

   outTree->Branch("SQX_L_e", &out_SQX_L_Edep,    "SQX_L_e/D");
   outTree->Branch("SQX_R_e", &out_SQX_R_Edep,    "SQX_R_e/D");
   outTree->Branch("CsI_L_e", &out_CsI_L_Edep,    "CsI_L_e/D");
   outTree->Branch("CsI_R_e", &out_CsI_R_Edep,    "CsI_R_e/D");

   outTree->Branch("SQX_L_s", &out_SQX_L_strip,   "SQX_L_s/S");
   outTree->Branch("SQX_R_s", &out_SQX_R_strip,   "SQX_R_s/S");
   outTree->Branch("SQY_L_s", &out_SQY_L_strip,   "SQY_L_s/S");
   outTree->Branch("SQY_R_s", &out_SQY_R_strip,   "SQY_R_s/S");
   outTree->Branch("CsI_L_s", &out_CsI_L_strip,   "CsI_L_s/S");
   outTree->Branch("CsI_R_s", &out_CsI_R_strip,   "CsI_R_s/S");

   outTree->Branch("evX",  &out_evX, "evX/F");
   outTree->Branch("evY",  &out_evY, "evY/F");
   outTree->Branch("evZ",  &out_evZ, "evZ/F");

   outTree->Branch("tof",  &out_tof,   "tof/D");
   outTree->Branch("aF5",  &out_aF5,   "aF5/D");

   outTree->Bronch("LV_beam.",   "TLorentzVector", &out_LV_beam);
   outTree->Branch("angAng1H",   &out_angAng1H,  "angAng1H/B");
   outTree->Branch("angAng2H",   &out_angAng2H,  "angAng2H/B");


   TString option = GetOption();
}

void dE_File_clnr::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   out_LV_beam = new TLorentzVector();
   TString option = GetOption();
   counter=0;
}

Bool_t dE_File_clnr::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   

   fReader.SetEntry(entry);


   if (*angAng1H || *angAng2H)
      {
         counter++;
         out_tSQX_L = tSQX_L[1];
         out_tSQX_R = tSQX_R[1];

         out_SQX_L_Edep = SQX_L_e[1];
         out_SQX_R_Edep = SQX_R_e[1];
         out_CsI_L_Edep = CsI_L_e[1];
         out_CsI_R_Edep = CsI_R_e[1];

         out_SQX_L_strip = SQX_L_s[1];
         out_SQX_R_strip = SQX_R_s[1];
         out_SQY_L_strip = SQY_L_s[1];
         out_SQY_R_strip = SQY_R_s[1];
         out_CsI_L_strip = CsI_L_s[1];
         out_CsI_R_strip = CsI_R_s[1];

         out_evX = *evX;
         out_evY = *evY;
         out_evZ = *evZ;

         out_tof = *tof;
         out_aF5 = *aF5;

         out_LV_beam->SetPxPyPzE(LV_beam->Px(), LV_beam->Py(), LV_beam->Pz(), LV_beam->E());
         //printf("%f\n",out_LV_beam->E()-out_LV_beam->M());
         out_angAng1H = *angAng1H;
         out_angAng2H = *angAng2H;

         outTree->Fill();
      }

   return kTRUE;
}

void dE_File_clnr::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   printf("%lli\n",counter);

}

void dE_File_clnr::Terminate()
{
   outTree->Write();
   outF->Close();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}