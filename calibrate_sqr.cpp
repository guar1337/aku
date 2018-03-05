#include "TFile.h"
#include "TObjArray.h"
#include "TString.h"
#include "TTree.h"
#include "TH2D.h"
#include "stdio.h"
#include "Riostream.h"
#include "calibrate_sqr.h"
#include <iostream>
#include "interface.h"
#include <vector>

// voron1392

void loader(TString fname, float *AConst, float *BConst)
{
   ifstream plik(fname.Copy().Prepend("/home/guar/Desktop/1217_data/coefs/").Data());
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
      cout<<AConst[iii]<<"  "<<BConst[iii]<<endl;
      }
    plik.close();
    //cout<<endl;
    printf("Finishing %s\n\n",fname.Data() );
}

void calibrate_sqr() 
{
gSystem->cd(s::work_dir.Data());
TString outFname("sqr.root");
TFile *outF = new TFile(outFname.Data(),"RECREATE");
TTree *outTree= new TTree("calibrated","he6");
TFile *inF = new TFile("he6_9.root");
TTree *inTree = (TTree*)inF->Get("AnalysisxTree");
printf(".\n..\n...\n");
/*
vector<string> fNames{"he6_9_0.root" ,"he6_9_1.root", "he6_9_2.root"};
for (vector<string>::iterator iii = fNames.begin(); iii != fNames.end(); ++iii)
{
   cout << inFiles->Add(iii->c_str());
   printf("Adding file %s to my p00l \n", iii->c_str());
}
*/
printf(".\n..\n...\n");

//TObjArray *fileList= new TObjArray(*inFiles->GetListOfFiles());
//printf("ooo %s\n",fileList[0].GetName());


//inFiles

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

outTree->Branch("SQX_R",       out_SQX_R,       "SQX_R[16]/D");

outTree->Branch("tSQX_R",       out_tSQX_R,       "tSQX_R[16]/D");

outTree->Branch("SQY_R",	    out_SQY_R,       "SQY_R[16]/D");

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

outTree->Branch("r_SQX_R",       r_SQX_R,       "r_SQX_R[16]/D");
outTree->Branch("r_SQY_R",       r_SQY_R,       "r_SQY_R[16]/D");
outTree->Branch("r_CsI_R",       r_CsI_R,       "r_CsI_R[16]/D");

outTree->Branch("trigger",	    &out_trigger,        "trigger/I");
outTree->Branch("tof",     &tof,        "tof/D");


loader("sqx_r_ec.clb", a_SQX_R, b_SQX_R);
loader("sqx_r_tc.clb", a_tSQX_R, b_tSQX_R);
loader("sqy_r_ec.clb", a_SQY_R, b_SQY_R);
loader("csi_r_ec.clb", a_CsI_R, b_CsI_R);

printf(".\n..\n...\n");

double gamma, beta_squared;
Long64_t nEntries = inTree->GetEntries();
printf("##############################################################################\n");
printf("#    Loaded files have %lli entries. \n#    Processing...\n", nEntries);
for (Long64_t entry=0; entry<nEntries; entry++)
{

   inTree->GetTree()->GetEntry(entry);
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


      out_SQX_R[iii]=(in_SQX_R[iii]+gRandom->Uniform())*b_SQX_R[iii]+a_SQX_R[iii];
      out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];

      out_tSQX_R[iii]=((in_tSQX_R[iii]+gRandom->Uniform())+a_tSQX_R[iii]-(in_tdcF5[0]+in_tdcF5[1])/2)*0.125;

      
      out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];



      r_SQX_R[iii]=in_SQX_R[iii];
      r_SQY_R[iii]=in_SQY_R[iii];
      r_CsI_R[iii]=in_CsI_R[iii];
   }


   if(out_x1[1]<100 && out_x2[1]<100 && out_y1[1]<100 && out_y2[1]<100 &&
      out_nx1<100 && out_nx2<100 && out_ny1<100 && out_ny2<100 && tof>146 && tof<154 && in_aF5[0]>400 && in_aF5[0]<1100)
   {
   outTree->Fill();
   }

   fill(out_SQX_R,out_SQX_R+16,16);
   fill(out_SQY_R,out_SQY_R+16,16);
   fill(out_CsI_R,out_CsI_R+16,16);


   fill(r_SQX_R,r_SQX_R+16,0);
   fill(r_SQY_R,r_SQY_R+16,0);
   fill(r_CsI_R,r_CsI_R+16,0);

   fill(out_x1,out_x1+32,0);
   fill(out_x2,out_x2+32,0);
   fill(out_y1,out_y1+32,0);
   fill(out_y2,out_y2+32,0);

   fill(out_tF3,out_tF3,0);
   fill(out_F3,out_F3,0);
   fill(out_tF5,out_tF5,0);
   fill(out_F5,out_F5,0);

}

printf("#    Creating file: %s with tree named \"calibrated\"\n",outFname.Data());
printf("#    We got from %lli entries to %lli entries with trigger cut\n",inTree->GetEntries(), outTree->GetEntries());
printf("#    Goodbye ;)\n");
outTree->Write();
//outF
//inF->Close();
}

//}
/*
        double Tbeam=v2H->Energy();
    double invariant = (m2H+m6He)*(m2H+m6He)+2.*m2H*Tbeam;
    double shorty=(invariant-m2H*m2H-m6He*m6He)*(invariant-m2H*m2H-m6He*m6He);
    double CMmom = sqrt((shorty-4.*m2H*m2H*m6He*m6He)/(4.*invariant));
    double chi = log((CMmom+sqrt(m2H*m2H+CMmom*CMmom))/m2H);
*/
