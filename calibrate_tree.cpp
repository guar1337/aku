#include "calibrate_tree.h"


R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);

// voron1392

bool loader(TString fname, float *AConst, float *BConst, short chNo)
{
   ifstream plik(fname.Copy().Prepend("/home/guar/data/mar2018/calib/params/").Data());
   string dummy;
   float CConst;
   if (!plik) 
   {
   printf ("#   Cannot open %s coefficient file\n",fname.Data());
   return 0;
   }
   else
   {
   		printf("Opening %s calibration file...\n",fname.Data() );
   }
    getline(plik, dummy);
    getline(plik, dummy);
   for (int iii=0; iii<chNo; iii++)
      {      
      plik>>AConst[iii]>>BConst[iii]>>CConst;
      //cout<<AConst[iii]<<"  "<<BConst[iii]<<endl;
      }
    plik.close();
    //cout<<endl;
    printf("Finishing %s\n\n",fname.Data() );
    return 1;
}

void calibrate_tree() 
{
gSystem->cd(s::rootF_dir.Data());
TString outFname("run02_cal.root");
TFile *outF = new TFile(outFname.Data(),"RECREATE");
TTree *outTree= new TTree("calibrated","he6");
TFile *inF = new TFile("run02.root");
printf("Succesfully opened file %s\n",outF->GetName());
if (inF->IsZombie())
{
   printf("Cannot open file \n");
   return 0;
}
TTree *inTree = (TTree*)inF->Get("AnalysisxTree");

/*
vector<string> fNames{"he6_9_0.root" ,"he6_9_1.root", "he6_9_2.root"};
for (vector<string>::iterator iii = fNames.begin(); iii != fNames.end(); ++iii)
{
   cout << inFiles->Add(iii->c_str());
   printf("Adding file %s to my p00l \n", iii->c_str());
}
*/


//TObjArray *fileList= new TObjArray(*inFiles->GetListOfFiles());
//printf("ooo %s\n",fileList[0].GetName());


//inFiles

TOOL *maynard = new TOOL();

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
inTree->SetBranchAddress("NeEvent.SQX_L[32]",	    in_SQX_L);
inTree->SetBranchAddress("NeEvent.SQX_R[32]",	    in_SQX_R);
inTree->SetBranchAddress("NeEvent.SQY_L[16]",	    in_SQY_L);
inTree->SetBranchAddress("NeEvent.SQY_R[16]",	    in_SQY_R);

inTree->SetBranchAddress("NeEvent.tSQX_L[32]",       in_tSQX_L);
inTree->SetBranchAddress("NeEvent.tSQX_R[32]",       in_tSQX_R);
inTree->SetBranchAddress("NeEvent.tCsI_L[16]",       in_tCsI_L);
inTree->SetBranchAddress("NeEvent.tCsI_R[16]",       in_tCsI_R);
inTree->SetBranchAddress("NeEvent.tSQY_L[16]",       in_tSQY_L);
inTree->SetBranchAddress("NeEvent.tSQY_R[16]",       in_tSQY_R);

inTree->SetBranchAddress("NeEvent.tF3[4]",         in_tdcF3);
inTree->SetBranchAddress("NeEvent.F3[4]",          in_aF3);
inTree->SetBranchAddress("NeEvent.tF5[4]",         in_tdcF5);
inTree->SetBranchAddress("NeEvent.F5[4]",          in_aF5);
inTree->SetBranchAddress("NeEvent.tF6[4]",         in_tdcF6);
inTree->SetBranchAddress("NeEvent.F6[4]",          in_aF6);

inTree->SetBranchAddress("NeEvent.nx1",          &in_nx1);
inTree->SetBranchAddress("NeEvent.ny1",          &in_ny1);
inTree->SetBranchAddress("NeEvent.nx2",          &in_nx2);
inTree->SetBranchAddress("NeEvent.ny2",          &in_ny2);

inTree->SetBranchAddress("NeEvent.x1[32]",     in_x1);
inTree->SetBranchAddress("NeEvent.y1[32]",     in_y1);
inTree->SetBranchAddress("NeEvent.x2[32]",     in_x2);
inTree->SetBranchAddress("NeEvent.y2[32]",     in_y2);
inTree->SetBranchAddress("NeEvent.tMWPC[4]",     in_tMWPC);

inTree->SetBranchAddress("NeEvent.trigger",     &in_trigger);


//ReCo - detectors
outTree->SetMakeClass(1);
//    CALIBRATED DATA
outTree->Branch("SQX_L",       out_SQX_L,       "SQX_L[32]/D");
outTree->Branch("SQX_R",       out_SQX_R,       "SQX_R[32]/D");
outTree->Branch("SQY_L",       out_SQY_L,       "SQY_L[16]/D");
outTree->Branch("SQY_R",       out_SQY_R,       "SQY_R[16]/D");
outTree->Branch("CsI_L",       out_CsI_L,       "CsI_L[16]/D");
outTree->Branch("CsI_R",       out_CsI_R,       "CsI_R[16]/D");

outTree->Branch("tSQX_L",      out_tSQX_L,      "tSQX_L[32]/D");
outTree->Branch("tSQX_R",      out_tSQX_R,      "tSQX_R[32]/D");
outTree->Branch("tSQY_L",      out_tSQY_L,      "tSQY_L[16]/D");
outTree->Branch("tSQY_R",      out_tSQY_R,      "tSQY_R[16]/D");
outTree->Branch("tCsI_L",      out_tCsI_L,      "tCsI_L[16]/D");
outTree->Branch("tCsI_R",      out_tCsI_R,      "tCsI_R[16]/D");

outTree->Branch("tF3",	    out_tF3,       "tF3[4]/D");
outTree->Branch("F3",	    out_F3,        "F3[4]/D");
outTree->Branch("tF5",      out_tF5,       "tF5[4]/D");
outTree->Branch("F5",       out_F5,        "F5[4]/D");
outTree->Branch("tF6",      out_tF6,       "tF6[4]/D");
outTree->Branch("F6",       out_F6,        "F6[4]/D");

outTree->Branch("x1",    out_x1,      "x1[32]/s");
outTree->Branch("x2",    out_x2,      "x2[32]/s");
outTree->Branch("y1",    out_y1,      "y1[32]/s");
outTree->Branch("y2",    out_y2,      "y2[32]/s");

outTree->Branch("nx1",    &out_nx1,      "nx1/s");
outTree->Branch("nx2",    &out_nx2,      "nx2/s");
outTree->Branch("ny1",    &out_ny1,      "ny1/s");
outTree->Branch("ny2",    &out_ny2,      "ny2/s");
outTree->Branch("tMWPC",    out_tMWPC,      "tMWPC[4]/f");

//    RAW DATA
outTree->Branch("r_SQX_L",       r_SQX_L,       "r_SQX_L[32]/D");
outTree->Branch("r_SQX_R",       r_SQX_R,       "r_SQX_R[32]/D");
outTree->Branch("r_SQY_L",       r_SQY_L,       "r_SQY_L[16]/D");
outTree->Branch("r_SQY_R",       r_SQY_R,       "r_SQY_R[16]/D");
outTree->Branch("r_CsI_L",       r_CsI_L,       "r_CsI_L[16]/D");
outTree->Branch("r_CsI_R",       r_CsI_R,       "r_CsI_R[16]/D");

outTree->Branch("trigger",	    &out_trigger,        "trigger/I");
outTree->Branch("tof",     &tof,        "tof/D");
outTree->Branch("T",     &T,        "T/D");

if (loader("SQX_L_ec.clb", a_SQX_L, b_SQX_L, 32)!=1){return 0;}
if (loader("SQX_R_ec.clb", a_SQX_R, b_SQX_R, 32)!=1){return 0;}
//loader("sqx_l_tc.clb", a_tSQX_L, b_tSQX_L, 32);
//loader("sqx_r_tc.clb", a_tSQX_R, b_tSQX_R, 32);
if (loader("SQY_L_ec.clb", a_SQY_L, b_SQY_L, 16)!=1){return 0;}
if (loader("SQY_R_ec.clb", a_SQY_R, b_SQY_R, 16)!=1){return 0;}

if (loader("csi_r_ec.clb", a_CsI_R, b_CsI_R, 16)!=1){return 0;}
if (loader("csi_l_ec.clb", a_CsI_L, b_CsI_L, 16)!=1){return 0;}

Long64_t nEntries = inTree->GetEntries();
printf("##############################################################################\n");
printf("#    Loaded files have %lli entries. \n#    Processing...\n", nEntries);
for (Long64_t entry=0; entry<nEntries; entry++)
{

   inTree->GetTree()->GetEntry(entry);
   if( entry % ( nEntries / 100 ) == 0)
   {
      printf("#    Progress: %i%%\n",counter);
      counter++;
   }
   
   out_nx1=in_nx1;
   out_nx2=in_nx2;
   out_ny1=in_ny1;
   out_ny2=in_ny2;
   out_trigger=in_trigger;

   tof=(-(in_tdcF3[0]+in_tdcF3[1]+in_tdcF3[2]+in_tdcF3[3])/4+(in_tdcF5[0]+in_tdcF5[1])/2)*0.125+89.165;

   for (int iii=0; iii<32; iii++)
   { 
      out_x1[iii]=in_x1[iii];
      out_x2[iii]=in_x2[iii];
      out_y1[iii]=in_y1[iii];
      out_y2[iii]=in_y2[iii];
      out_SQX_L[iii]=(in_SQX_L[iii]+gRandom->Uniform())*b_SQX_L[iii]+a_SQX_L[iii];
      out_SQX_R[iii]=(in_SQX_R[iii]+gRandom->Uniform())*b_SQX_R[iii]+a_SQX_R[iii];
      out_tSQX_R[iii]=in_tSQX_R[iii]+gRandom->Uniform();
      out_tSQX_L[iii]=in_tSQX_L[iii]+gRandom->Uniform();
      r_SQX_L[iii]=in_SQX_L[iii];
      r_SQX_R[iii]=in_SQX_R[iii];
   }


   for (int iii=0; iii<4; iii++)
   { 
      out_tF3[iii]=in_tdcF3[iii]*0.125;
      out_F3[iii]=in_aF3[iii]*0.125;
      out_tF5[iii]=in_tdcF5[iii]*0.125;
      out_F5[iii]=in_aF5[iii]*0.125;
      out_tF6[iii]=in_tdcF6[iii]*0.125;
      out_F6[iii]=in_aF6[iii]*0.125;
      out_tMWPC[iii] = in_tMWPC[iii]/3.4133;
   }

   for (int iii=0; iii<16; iii++)
   {    

      out_SQY_L[iii]=(in_SQY_L[iii]+gRandom->Uniform())*b_SQY_L[iii]+a_SQY_L[iii];
      out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];
      out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];
      out_CsI_L[iii]=(in_CsI_L[iii]+gRandom->Uniform())*b_CsI_L[iii]+a_CsI_L[iii];

      out_tSQY_L[iii]=in_tSQY_L[iii]+gRandom->Uniform();
      out_tSQY_R[iii]=in_tSQY_R[iii]+gRandom->Uniform();
      out_tCsI_R[iii]=in_tCsI_R[iii]+gRandom->Uniform();
      out_tCsI_L[iii]=in_tCsI_L[iii]+gRandom->Uniform();

      r_SQY_L[iii]=in_SQY_L[iii];
      r_SQY_R[iii]=in_SQY_R[iii];
      r_CsI_R[iii]=in_CsI_R[iii];
      r_CsI_L[iii]=in_CsI_L[iii];
   }

//no aF5 cut
   if(
      (in_tdcF5[0]-in_tdcF3[0])>100.0 && (in_tdcF5[0]-in_tdcF3[0])<800.0 &&
      (in_tdcF3[0]-in_tdcF3[1]) > -50.0 &&  (in_tdcF3[0]-in_tdcF3[1]) < 50.0 &&
      (in_tdcF5[0]-in_tdcF5[1]) > -50.0 &&  (in_tdcF5[0]-in_tdcF5[1]) < 50.0 &&
      (maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, s::MWPC_1_X_id)*
      maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, s::MWPC_1_Y_id)*
      maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, s::MWPC_2_X_id)*
      maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, s::MWPC_2_Y_id)) &&


      (in_tdcF5[0]-in_tdcF3[0])>630 && (in_tdcF5[0]-in_tdcF3[0])<740 &&
      tof>150 && tof<200 && in_aF5[0]>600 && in_aF5[0]<1800
      )
   {
   outTree->Fill();
   }
   fill(out_SQX_L,out_SQX_L+32,0);
   fill(out_SQY_L,out_SQY_L+16,0);
   fill(out_SQX_R,out_SQX_R+32,0);
   fill(out_SQY_R,out_SQY_R+16,0);
   fill(out_CsI_R,out_CsI_R+16,0);
   fill(out_CsI_L,out_CsI_L+16,0);

   fill(r_SQX_L,r_SQX_L+32,0);
   fill(r_SQY_L,r_SQY_L+16,0);
   fill(r_SQX_R,r_SQX_R+32,0);
   fill(r_SQY_R,r_SQY_R+16,0);
   fill(r_CsI_R,r_CsI_R+16,0);
   fill(r_CsI_L,r_CsI_L+16,0);

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
outF->Write();
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
