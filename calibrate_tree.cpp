#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TH2D.h"
#include "stdio.h"
#include "Riostream.h"
#include "calibrate_tree.h"
#include <iostream>
#include "interface.h"


// voron1392

void loader(TString fname, float *AConst, float *BConst)
{
   ifstream plik(fname.Data());
   string dummy;
   float CConst;
   if (!plik) 
   {
   printf ("#   Cannot open %s coefficient file\n",fname.Data());
   return;
   }
   else
   {
   		printf("Opening %s calibration file...\n",fname.Data() );
   }
    getline(plik, dummy);
    getline(plik, dummy);
   for (int iii=0; iii<16; iii++)
      {      
      plik>>AConst[iii]>>BConst[iii]>>CConst;
      //cout<<AConst[iii]<<"  "<<BConst[iii]<<endl;
      }
    plik.close();
    //cout<<endl;
}

void calibrate_tree() 
{
gSystem->cd(s::work_dir.Data());

TString inFname("he6_7");
TString outFname(inFname.Copy().Append("_cal").Data()); 

TFile *inF  = new TFile((inFname.Append(".root").Data()), "READ");
TFile *outF = new TFile(outFname.Append(".root").Data(),"recreate");
TTree *inTree = (TTree*)inF->Get("AnalysisxTree");
TTree *outTree= new TTree("calibrated","he6");

out_nx1=0;
out_nx2=0;
out_ny1=0;
out_ny2=0;
out_trigger=0;

in_nx1=0;
in_nx2=0;
in_ny1=0;
in_ny2=0;
in_trigger=0;


//inTree->Print();

//Creating addresses of BEAM holding branches
inTree->SetMakeClass(1);
inTree->SetBranchAddress("NeEvent.CsI_L[16]",	    in_CsI_L);
inTree->SetBranchAddress("NeEvent.CsI_R[16]",	    in_CsI_R);
inTree->SetBranchAddress("NeEvent.SQX_L[16]",	    in_SQX_L);
inTree->SetBranchAddress("NeEvent.SQX_R[16]",	    in_SQX_R);
inTree->SetBranchAddress("NeEvent.SQY_L[16]",	    in_SQY_L);
inTree->SetBranchAddress("NeEvent.SQY_R[16]",	    in_SQY_R);

inTree->SetBranchAddress("NeEvent.tSQX_L[16]",       in_tSQX_L);
inTree->SetBranchAddress("NeEvent.tSQX_R[16]",       in_tSQX_R);

inTree->SetBranchAddress("NeEvent.tF3[4]",         in_tdcF3);
inTree->SetBranchAddress("NeEvent.F3[4]",          in_aF3);
inTree->SetBranchAddress("NeEvent.tF5[4]",         in_tdcF5);
inTree->SetBranchAddress("NeEvent.F5[4]",          in_aF5);

inTree->SetBranchAddress("NeEvent.nx1",          &in_nx1);
inTree->SetBranchAddress("NeEvent.ny1",          &in_ny1);
inTree->SetBranchAddress("NeEvent.nx2",          &in_nx2);
inTree->SetBranchAddress("NeEvent.ny2",          &in_ny2);

inTree->SetBranchAddress("NeEvent.x1[32]",     in_x1);
inTree->SetBranchAddress("NeEvent.y1[32]",     in_y1);
inTree->SetBranchAddress("NeEvent.x2[32]",     in_x2);
inTree->SetBranchAddress("NeEvent.y2[32]",     in_y2);

inTree->SetBranchAddress("NeEvent.trigger",     &in_trigger);


//ReCo - detectors
outTree->SetMakeClass(1);
//    CALIBRATED DATA
outTree->Branch("SQX_L",       out_SQX_L,       "SQX_L[16]/D");
outTree->Branch("SQX_R",       out_SQX_R,       "SQX_R[16]/D");
outTree->Branch("tSQX_L",       out_tSQX_L,       "tSQX_L[16]/D");
outTree->Branch("tSQX_R",       out_tSQX_R,       "tSQX_R[16]/D");
outTree->Branch("SQY_L",	    out_SQY_L,       "SQY_L[16]/D");
outTree->Branch("SQY_R",	    out_SQY_R,       "SQY_R[16]/D");
outTree->Branch("CsI_L",	    out_CsI_L,       "CsI_L[16]/D");
outTree->Branch("CsI_R",        out_CsI_R,       "CsI_R[16]/D");

outTree->Branch("tF3",	    out_tF3,       "tF3[4]/D");
outTree->Branch("F3",	    out_F3,        "F3[4]/D");
outTree->Branch("tF5",	    out_tF5,       "tF5[4]/D");
outTree->Branch("F5",	    out_F5,        "F5[4]/D");

outTree->Branch("x1",    out_x1,      "x1[32]/s");
outTree->Branch("x2",    out_x2,      "x2[32]/s");
outTree->Branch("y1",    out_y1,      "y1[32]/s");
outTree->Branch("y2",    out_y2,      "y2[32]/s");

outTree->Branch("nx1",    &out_nx1,      "nx1/s");
outTree->Branch("nx2",    &out_nx2,      "nx2/s");
outTree->Branch("ny1",    &out_ny1,      "ny1/s");
outTree->Branch("ny2",    &out_ny2,      "ny2/s");

//    RAW DATA
outTree->Branch("r_SQX_L",       r_SQX_L,       "r_SQX_L[16]/D");
outTree->Branch("r_SQX_R",       r_SQX_R,       "r_SQX_R[16]/D");
outTree->Branch("r_SQY_L",       r_SQY_L,       "r_SQY_L[16]/D");
outTree->Branch("r_SQY_R",       r_SQY_R,       "r_SQY_R[16]/D");
outTree->Branch("r_CsI_L",       r_CsI_L,       "r_CsI_L[16]/D");
outTree->Branch("r_CsI_R",       r_CsI_R,       "r_CsI_R[16]/D");

outTree->Branch("trigger",	    &out_trigger,        "trigger/I");
outTree->Branch("tof",     &tof,        "tof/D");
outTree->Branch("T",     &T,        "T/D");

loader("/home/guar/Desktop/1217_data/coefs/sqx_l_ec.clb", a_SQX_L, b_SQX_L);
loader("/home/guar/Desktop/1217_data/coefs/sqx_r_ec.clb", a_SQX_R, b_SQX_R);
loader("/home/guar/Desktop/1217_data/coefs/sqx_l_ec.clb", a_tSQX_L, b_tSQX_L);
loader("/home/guar/Desktop/1217_data/coefs/sqx_r_ec.clb", a_tSQX_R, b_tSQX_R);
loader("/home/guar/Desktop/1217_data/coefs/sqy_l_ec.clb", a_SQY_L, b_SQY_L);
loader("/home/guar/Desktop/1217_data/coefs/sqy_r_ec.clb", a_SQY_R, b_SQY_R);
loader("/home/guar/Desktop/1217_data/coefs/csi_r_ec.clb", a_CsI_R, b_CsI_R);
loader("/home/guar/Desktop/1217_data/coefs/csi_l_ec.clb", a_CsI_L, b_CsI_L);
printf("\n");

double gamma, beta_squared;

Long64_t nEntries = inTree->GetEntries();
printf("##############################################################################\n");
printf("#    Loaded file %s has %lli entries. \n#    Processing...\n", inFname.Data(), nEntries);
for (Long64_t entry=1; entry<nEntries; entry++)
{

   inTree->GetEntry(entry);
   if( entry % ( nEntries / 20 ) == 0)
   {
      cout<<"#    Progress: "<<double(entry * 100)/ nEntries<<" %"<<endl;
   }
   
   out_nx1=in_nx1;
   out_nx2=in_nx2;
   out_ny1=in_ny1;
   out_ny2=in_ny2;
   out_trigger=in_trigger;

   tof=(-(in_tdcF3[0]+in_tdcF3[1]+in_tdcF3[2]+in_tdcF3[3])/4+(in_tdcF5[0]+in_tdcF5[1])/2)*0.125+94.44;

   beta_squared=((12348/tof)/299.792)*((12348/tof)/299.792);

   gamma=1/sqrt(1-beta_squared);
   
   T=6.0188891*931.494*(gamma-1.0);

   for (int iii=0; iii<32; iii++)
   { 
      out_x1[iii]=in_x1[iii];
      out_x2[iii]=in_x2[iii];
      out_y1[iii]=in_y1[iii];
      out_y2[iii]=in_y2[iii];
   }

   for (int iii=0; iii<4; iii++)
   { 
      out_tF3[iii]=in_tdcF3[iii];
      out_F3[iii]=in_aF3[iii];
      out_tF5[iii]=in_tdcF5[iii];
      out_F5[iii]=in_aF5[iii];
   }

   for (int iii=0; iii<16; iii++)
   {    
      out_SQX_L[iii]=(in_SQX_L[iii]+gRandom->Uniform())*b_SQX_L[iii]+a_SQX_L[iii];
      out_SQY_L[iii]=(in_SQY_L[iii]+gRandom->Uniform())*b_SQY_L[iii]+a_SQY_L[iii];
      out_SQX_R[iii]=(in_SQX_R[iii]+gRandom->Uniform())*b_SQX_R[iii]+a_SQX_R[iii];
      out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];

      out_tSQX_R[iii]=((in_tSQX_R[iii]+gRandom->Uniform())+a_tSQX_R[iii]-(in_tdcF5[0]+in_tdcF5[1])/2)*0.125;
      out_tSQX_L[iii]=((in_tSQX_L[iii]+gRandom->Uniform())+a_tSQX_L[iii]-(in_tdcF5[0]+in_tdcF5[1])/2)*0.125;
      
      out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];
      out_CsI_L[iii]=(in_CsI_L[iii]+gRandom->Uniform())*b_CsI_L[iii]+a_CsI_L[iii];

      r_SQX_L[iii]=in_SQX_L[iii];
      r_SQY_L[iii]=in_SQY_L[iii];
      r_SQX_R[iii]=in_SQX_R[iii];
      r_SQY_R[iii]=in_SQY_R[iii];
      r_CsI_R[iii]=in_CsI_R[iii];
      r_CsI_L[iii]=in_CsI_L[iii];
   }


   if(out_x1[1]<100 && out_x2[1]<100 && out_y1[1]<100 && out_y2[1]<100 &&
      out_nx1<100 && out_nx2<100 && out_ny1<100 && out_ny2<100 && in_trigger==2 && tof>110.0 && tof<160.0)
   {
   outTree->Fill();
   }
   fill(out_SQX_L,out_SQX_L+16,16);
   fill(out_SQY_L,out_SQY_L+16,16);
   fill(out_SQX_R,out_SQX_R+16,16);
   fill(out_SQY_R,out_SQY_R+16,16);
   fill(out_CsI_R,out_CsI_R+16,16);
   fill(out_CsI_L,out_CsI_L+16,16);

   fill(r_SQX_L,r_SQX_L+16,16);
   fill(r_SQY_L,r_SQY_L+16,16);
   fill(r_SQX_R,r_SQX_R+16,16);
   fill(r_SQY_R,r_SQY_R+16,16);
   fill(r_CsI_R,r_CsI_R+16,16);
   fill(r_CsI_L,r_CsI_L+16,16);

   fill(out_x1,out_x1+32,0.);
   fill(out_x2,out_x2+32,0.);
   fill(out_y1,out_y1+32,0.);
   fill(out_y2,out_y2+32,0.);

   fill(out_tF3,out_tF3,0);
   fill(out_F3,out_F3,0);
   fill(out_tF5,out_tF5,0);
   fill(out_F5,out_F5,0);

}

printf("#    Creating file: %s with tree named \"calibrated\"\n",outFname.Data());
printf("#    Goodbye ;)\n");
outTree->Write();
outF->Close();


}
/*
        double Tbeam=v2H->Energy();
    double invariant = (m2H+m6He)*(m2H+m6He)+2.*m2H*Tbeam;
    double shorty=(invariant-m2H*m2H-m6He*m6He)*(invariant-m2H*m2H-m6He*m6He);
    double CMmom = sqrt((shorty-4.*m2H*m2H*m6He*m6He)/(4.*invariant));
    double chi = log((CMmom+sqrt(m2H*m2H+CMmom*CMmom))/m2H);
*/
