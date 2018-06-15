#include "calibrate_tree.h"


R__LOAD_LIBRARY(libgsl.so);
R__LOAD_LIBRARY(/home/guar/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);


// voron1392


void wrk(TString fname, TString dir_current) 
{
//TTree *inTree;

gSystem->cd(dir_current.Data());
if (!fname.Contains(".root"))
{
	fname.Append(".root");

}
TFile *inF = new TFile(fname.Copy());
if (inF->IsZombie())
{
	printf("\n#Cannot open file: %s\n", fname.Copy().Prepend("inF: ").Data());
	return 0;
}

printf("\n*Succesfully opened file %s\n",inF->GetName());
TFile *outF = new TFile(fname.Copy().Prepend("cal_"),"RECREATE");
if (outF->IsZombie())
{
	printf("#Cannot open file: %s\n", fname.Copy().Prepend("outF: ").Data());
	return 0;
}
printf("*Succesfully opened file %s\n\n",outF->GetName());


TTree *inTree = (TTree*)inF->Get("AnalysisxTree");
TTree *outTree= new TTree("calibrated","he6");


if (inTree->IsZombie())
{
	printf("#Cannot open tree: %s\n", fname.Copy().Prepend("inTree: ").Data());
	return 0;
}
else {printf("*Succesfully opened tree %s\n",inTree->GetName());}

if (outTree->IsZombie())
{
	printf("#Cannot open tree: %s\n", fname.Copy().Prepend("outTree: ").Data());
	return 0;
}
else {printf("*Succesfully opened tree %s\n\n",outTree->GetName());}

//inFiles

TOOL *maynard = new TOOL();
	int s_Nel=1;
	si_A[0]=28;
	si_Z[0]=14;
	si_W[0]=1;

	Si_Ecalc = new ELC(6,2,s_Nel,2.35,
					 si_A, si_Z, si_W,
					 1000.,1500);

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

if (maynard->params_loader("SQX_L_ec.clb", a_SQX_L, b_SQX_L, 32)!=1){return 0;}
if (maynard->params_loader("SQX_R_ec.clb", a_SQX_R, b_SQX_R, 32)!=1){return 0;}
if (maynard->params_loader("SQX_L_tc.clb", a_tSQX_L, b_tSQX_L, 32)!=1){return 0;}
if (maynard->params_loader("SQX_R_tc.clb", a_tSQX_R, b_tSQX_R, 32)!=1){return 0;}

if (maynard->params_loader("SQY_L_ec.clb", a_SQY_L, b_SQY_L, 16)!=1){return 0;}
if (maynard->params_loader("SQY_R_ec.clb", a_SQY_R, b_SQY_R, 16)!=1){return 0;}
if (maynard->params_loader("SQY_L_tc.clb", a_tSQY_L, b_tSQY_L, 16)!=1){return 0;}
if (maynard->params_loader("SQY_R_tc.clb", a_tSQY_R, b_tSQY_R, 16)!=1){return 0;}

if (maynard->params_loader("csi_r_tc.clb", a_tCsI_R, b_tCsI_R, 16)!=1){return 0;}
if (maynard->params_loader("csi_l_tc.clb", a_tCsI_L, b_tCsI_L, 16)!=1){return 0;}

if (s::runNo==0)
{
	if (maynard->params_loader("csi_r_0ec.clb", a_CsI_R, b_CsI_R, 16)!=1){return 0;}
	if (maynard->params_loader("csi_l_0ec.clb", a_CsI_L, b_CsI_L, 16)!=1){return 0;}

}

if (maynard->params_loader("csi_r_ec.clb", a_CsI_R, b_CsI_R, 16)!=1){return 0;}
if (maynard->params_loader("csi_l_ec.clb", a_CsI_L, b_CsI_L, 16)!=1){return 0;}

Long64_t nEntries = inTree->GetEntries();
counter = 0;
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

	tof=(-(in_tdcF3[0]+in_tdcF3[1]+in_tdcF3[2]+in_tdcF3[3])/4+(in_tdcF5[0]+in_tdcF5[1])/2)*0.125+s::tof_const;

	for (int iii=0; iii<4; iii++)
	{ 
		out_tF3[iii]=in_tdcF3[iii]*0.125;
		out_F3[iii]=in_aF3[iii];
		out_tF5[iii]=in_tdcF5[iii]*0.125;
		out_F5[iii]=in_aF5[iii];
		out_tF6[iii]=in_tdcF6[iii]*0.125;
		out_F6[iii]=in_aF6[iii];
		out_tMWPC[iii] = in_tMWPC[iii]/3.4133;
	}

	for (int iii=0; iii<16; iii++)
	{    

		out_SQY_L[iii]=(in_SQY_L[iii]+gRandom->Uniform())*b_SQY_L[iii]+a_SQY_L[iii];
		out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];
		out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];
		out_CsI_L[iii]=(in_CsI_L[iii]+gRandom->Uniform())*b_CsI_L[iii]+a_CsI_L[iii];

		out_tSQY_L[iii]=(in_tSQY_L[iii]+gRandom->Uniform())*b_tSQY_L[iii]+a_tSQY_L[iii];
		out_tSQY_R[iii]=(in_tSQY_R[iii]+gRandom->Uniform())*b_tSQY_R[iii]+a_tSQY_R[iii];
		out_tCsI_R[iii]=(in_tCsI_R[iii]+gRandom->Uniform())*b_tCsI_R[iii]+a_tCsI_R[iii];
		out_tCsI_L[iii]=(in_tCsI_L[iii]+gRandom->Uniform())*b_tCsI_L[iii]+a_tCsI_L[iii];

		r_SQY_L[iii]=in_SQY_L[iii];
		r_SQY_R[iii]=in_SQY_R[iii];
		r_CsI_R[iii]=in_CsI_R[iii];
		r_CsI_L[iii]=in_CsI_L[iii];
	}

		for (int iii=0; iii<32; iii++)
	{ 
		out_x1[iii]=in_x1[iii];
		out_x2[iii]=in_x2[iii];
		out_y1[iii]=in_y1[iii];
		out_y2[iii]=in_y2[iii];
		out_SQX_L[iii]=(in_SQX_L[iii]+gRandom->Uniform())*b_SQX_L[iii]+a_SQX_L[iii];
		out_SQX_R[iii]=(in_SQX_R[iii]+gRandom->Uniform())*b_SQX_R[iii]+a_SQX_R[iii];
		out_tSQX_R[iii]=(in_tSQX_R[iii]+gRandom->Uniform())*b_tSQX_R[iii]+a_tSQX_R[iii];
		out_tSQX_L[iii]=(in_tSQX_L[iii]+gRandom->Uniform())*b_tSQX_L[iii]+a_tSQX_L[iii];
		r_SQX_L[iii]=in_SQX_L[iii];
		r_SQX_R[iii]=in_SQX_R[iii];
	}

//no aF5 cut
	if(
		(in_tdcF5[0]-in_tdcF3[0])>100.0 && (in_tdcF5[0]-in_tdcF3[0])<800.0 &&
		(in_tdcF3[0]-in_tdcF3[1]) > -50.0 &&  (in_tdcF3[0]-in_tdcF3[1]) < 50.0 &&
		(in_tdcF5[0]-in_tdcF5[1]) > -50.0 &&  (in_tdcF5[0]-in_tdcF5[1]) < 50.0 &&
		(maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, s::MWPC_1_X_id)*
		maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, s::MWPC_1_Y_id)*
		maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, s::MWPC_2_X_id)*
		maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, s::MWPC_2_Y_id))
		&& in_aF5[0]>0/* &&


		(in_tdcF5[0]-in_tdcF3[0])>630 && (in_tdcF5[0]-in_tdcF3[0])<740 &&
		tof>150 && tof<200 && in_aF5[0]>600 && in_aF5[0]<1800		*/	)
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

printf("#    Creating file: %s with tree named \"calibrated\"\n",fname.Copy().Append("_cal.root").Data());
printf("#    We got from %lli entries to %lli entries with trigger cut\n",inTree->GetEntries(), outTree->GetEntries());
printf("#    That gives %i%% efficiency\n", static_cast<int>(100*outTree->GetEntries()/inTree->GetEntries()));
printf("#    Goodbye ;)\n");
outF->Write();
//outF
//inF->Close();
}

void calibrate_tree()
{
	TString dir_current;
	switch (s::runNo)
	{
		case 0:
			dir_current = s::dir_CsI;
			wrk(s::s_inFname.Data(), dir_current);
			return 1;
			break;

		case 1:
			dir_current = s::dir_runs.Copy().Append("/geo1").Data();
			break;

		case 2:
			dir_current = s::dir_runs.Copy().Append("/geo2").Data();
			break;

		case 3:
			dir_current = s::dir_runs.Copy().Append("/geo3").Data();
			break;

		case 4:
			dir_current = s::dir_runs.Copy().Append("/geo4").Data();
			break;

		default:
			printf("\nError: WTF amigo\n");
			return 0;
			break;
	}

	gSystem->cd(dir_current.Data());
	TSystemDirectory *dir_data = new TSystemDirectory("data", dir_current.Data());

	TIter bluster(dir_data->GetListOfFiles());
	while (TObject *obj = bluster())
	{
		TString inFname = obj->GetName();
		//if (inFname.Contains("run00")/* && !inFname.Contains("cal_")*/)
		//{
			printf("%s\n",inFname.Data());
		//}
	}
	TIter next(dir_data->GetListOfFiles());
	while (TObject *obj = next())
	{
		TString str_name = obj->GetName();
		if (str_name.Contains("run19") && !str_name.Contains("_"))
		{
			wrk(obj->GetName(), dir_current);
		}

		
	}
	
}

//}
/*
		  double Tbeam=v2H->Energy();
	 double invariant = (m2H+m6He)*(m2H+m6He)+2.*m2H*Tbeam;
	 double shorty=(invariant-m2H*m2H-m6He*m6He)*(invariant-m2H*m2H-m6He*m6He);
	 double CMmom = sqrt((shorty-4.*m2H*m2H*m6He*m6He)/(4.*invariant));
	 double chi = log((CMmom+sqrt(m2H*m2H+CMmom*CMmom))/m2H);
*/
