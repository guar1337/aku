#include "muchobojca.h"


R__LOAD_LIBRARY(libgsl.so);
R__LOAD_LIBRARY(/home/guar/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);


// voron1392

ClassImp(muchobojca);
muchobojca::muchobojca()
{
}

bool muchobojca::wrk(TTree *inTree, TTree *outTree, TString fname) 
{
maynard = new TOOL();
//Creating addresses of BEAM holding branches
inTree->SetMakeClass(1);

inTree->SetBranchAddress("NeEvent.CsI_L[16]",	in_CsI_L);
inTree->SetBranchAddress("NeEvent.CsI_R[16]",	in_CsI_R);
inTree->SetBranchAddress("NeEvent.SQX_L[32]",	in_SQX_L);
inTree->SetBranchAddress("NeEvent.SQX_R[32]",	in_SQX_R);
inTree->SetBranchAddress("NeEvent.SQY_L[16]",	in_SQY_L);
inTree->SetBranchAddress("NeEvent.SQY_R[16]",	in_SQY_R);

inTree->SetBranchAddress("NeEvent.tSQX_L[32]",	in_tSQX_L);
inTree->SetBranchAddress("NeEvent.tSQX_R[32]",	in_tSQX_R);
inTree->SetBranchAddress("NeEvent.tCsI_L[16]",	in_tCsI_L);
inTree->SetBranchAddress("NeEvent.tCsI_R[16]",	in_tCsI_R);
inTree->SetBranchAddress("NeEvent.tSQY_L[16]",	in_tSQY_L);
inTree->SetBranchAddress("NeEvent.tSQY_R[16]",	in_tSQY_R);

inTree->SetBranchAddress("NeEvent.tF3[4]",	in_tdcF3);
inTree->SetBranchAddress("NeEvent.F3[4]",	in_aF3);
inTree->SetBranchAddress("NeEvent.tF5[4]",	in_tdcF5);
inTree->SetBranchAddress("NeEvent.F5[4]",	in_aF5);
inTree->SetBranchAddress("NeEvent.tF6[4]",	in_tdcF6);
inTree->SetBranchAddress("NeEvent.F6[4]",	in_aF6);

inTree->SetBranchAddress("NeEvent.nx1",	&in_nx1);
inTree->SetBranchAddress("NeEvent.ny1",	&in_ny1);
inTree->SetBranchAddress("NeEvent.nx2",	&in_nx2);
inTree->SetBranchAddress("NeEvent.ny2",	&in_ny2);

inTree->SetBranchAddress("NeEvent.x1[32]",	in_x1);
inTree->SetBranchAddress("NeEvent.y1[32]",	in_y1);
inTree->SetBranchAddress("NeEvent.x2[32]",	in_x2);
inTree->SetBranchAddress("NeEvent.y2[32]",	in_y2);
inTree->SetBranchAddress("NeEvent.tMWPC[4]",	in_tMWPC);

inTree->SetBranchAddress("NeEvent.trigger", &in_trig);


//ReCo - detectors
outTree->SetMakeClass(1);
//CALIBRATED DATA
outTree->Branch("SQX_L",	out_SQX_L,	"SQX_L[32]/s");
outTree->Branch("SQX_R",	out_SQX_R,	"SQX_R[32]/s");
outTree->Branch("SQY_L",	out_SQY_L,	"SQY_L[16]/s");
outTree->Branch("SQY_R",	out_SQY_R,	"SQY_R[16]/s");
outTree->Branch("CsI_L",	out_CsI_L,	"CsI_L[16]/s");
outTree->Branch("CsI_R",	out_CsI_R,	"CsI_R[16]/s");

outTree->Branch("tSQX_L",	out_tSQX_L,	"tSQX_L[32]/s");
outTree->Branch("tSQX_R",	out_tSQX_R,	"tSQX_R[32]/s");
outTree->Branch("tSQY_L",	out_tSQY_L,	"tSQY_L[16]/s");
outTree->Branch("tSQY_R",	out_tSQY_R,	"tSQY_R[16]/s");
outTree->Branch("tCsI_L",	out_tCsI_L,	"tCsI_L[16]/s");
outTree->Branch("tCsI_R",	out_tCsI_R,	"tCsI_R[16]/s");

outTree->Branch("x1",	out_x1,	"x1[32]/s");
outTree->Branch("x2",	out_x2,	"x2[32]/s");
outTree->Branch("y1",	out_y1,	"y1[32]/s");
outTree->Branch("y2",	out_y2,	"y2[32]/s");

outTree->Branch("nx1",	&out_nx1,	"nx1/s");
outTree->Branch("nx2",	&out_nx2,	"nx2/s");
outTree->Branch("ny1",	&out_ny1,	"ny1/s");
outTree->Branch("ny2",	&out_ny2,	"ny2/s");

outTree->Branch("tF3",	out_tF3,	"tF3[4]/s");
outTree->Branch("F3",	out_F3,		"F3[4]/s");
outTree->Branch("tF5",	out_tF5,	"tF5[4]/s");
outTree->Branch("F5",	out_F5,		"F5[4]/s");
outTree->Branch("tF6",	out_tF6,	"tF6[4]/s");
outTree->Branch("F6",	out_F6,		"F6[4]/s");

outTree->Branch("tMWPC",	out_tMWPC,	"tMWPC[4]/s");
outTree->Branch("tof",		&tof,		"tof/D");
outTree->Branch("sumF5",	&sumF5,		"aF5/D");
outTree->Branch("trig",		&out_trig,	"trig/I");

maynard->params_loader("SQX_L_tc.clb", a_tSQX_L, b_tSQX_L, 32);
Long64_t nEntries = inTree->GetEntries();
counter = 0;
Long64_t tac_count=0, mwpc_count=0, sql_count=0, tof_range_count=0, zero_mult=0;
printf("##############################################################################\n");
printf("#Loaded files have %lli entries. \n#Processing...\n", nEntries);
for (Long64_t entry=0; entry<nEntries; entry++)
{
	inTree->GetTree()->GetEntry(entry);
	if( entry % ( nEntries / 10 ) == 0)
	{
		printf("#Progress: %i%%\n",counter);
		counter+=10;
	}
	tac=false; mwpc=false; tof_range=false; amp=false, sql=false;
	if (in_nx1<100 && in_nx2<100 && in_ny1<100 && in_ny2<100)
	{

		tof=(-(in_tdcF3[0]+in_tdcF3[1]+in_tdcF3[2]+in_tdcF3[3])/4.0+(in_tdcF5[0]+in_tdcF5[1])/2)*0.125+s::tof_const;
		sumF5 = (in_aF5[0] + in_aF5[1] + in_aF5[2] + in_aF5[3])/4.0;

		out_nx1=in_nx1;
		out_nx2=in_nx2;
		out_ny1=in_ny1;
		out_ny2=in_ny2;
		in_trig=out_trig;

		for (int iii=0; iii<4; iii++)
		{ 
			out_tF3[iii]=in_tdcF3[iii];
			out_F3[iii]=in_aF3[iii];
			out_tF5[iii]=in_tdcF5[iii];
			out_F5[iii]=in_aF5[iii];
			out_tF6[iii]=in_tdcF6[iii];
			out_F6[iii]=in_aF6[iii];
			out_tMWPC[iii] = in_tMWPC[iii];
		}
		for (int iii=0; iii<16; iii++)
		{

			out_SQY_L[iii]=in_SQY_L[iii];
			out_SQY_R[iii]=in_SQY_R[iii];
			out_CsI_R[iii]=in_CsI_R[iii];
			out_CsI_L[iii]=in_CsI_L[iii];

			out_tSQY_L[iii]=in_tSQY_L[iii];
			out_tSQY_R[iii]=in_tSQY_R[iii];
			out_tCsI_R[iii]=in_tCsI_R[iii];
			out_tCsI_L[iii]=in_tCsI_L[iii];

		}

			for (int iii=0; iii<32; iii++)
		{ 
			out_x1[iii]=in_x1[iii];
			out_x2[iii]=in_x2[iii];
			out_y1[iii]=in_y1[iii];
			out_y2[iii]=in_y2[iii];

			out_SQX_L[iii]=in_SQX_L[iii];
			out_SQX_R[iii]=in_SQX_R[iii];
			out_tSQX_R[iii]=in_tSQX_R[iii];
			out_tSQX_L[iii]=in_tSQX_L[iii];

			if (in_tSQX_L[iii]>500)
			{
				sql=true;
				sql_count++;
			}

		}


		if(	(in_tdcF3[0]-in_tdcF3[1]) > -50.0 && (in_tdcF3[0]-in_tdcF3[1]) < 50.0 &&
			(in_tdcF5[0]-in_tdcF5[1]) > -50.0 && (in_tdcF5[0]-in_tdcF5[1]) < 50.0	)
		{
			tac=true;
			tac_count++;
		}

		if (maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, s::MWPC_1_X_id)*
			maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, s::MWPC_1_Y_id)*
			maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, s::MWPC_2_X_id)*
			maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, s::MWPC_2_Y_id)	&&
			in_tMWPC[0]>3000 && in_tMWPC[1]>3000 && in_tMWPC[2]>3000 && in_tMWPC[3]>3000)
		{

			mwpc=true;
			mwpc_count++;
		}
		
//		if (sumF5>0)
//		{
			amp=true;
//			amp_count++;
//
//		}

		if (tof>100 && tof<200)
		{
			tof_range=true;
			tof_range_count++;
		}

		if (in_nx1*in_nx2*in_ny1*in_ny2)
		{
			zero_mult++;
		}

		if (tac*mwpc*amp*tof_range*sql)		
		{
			outTree->Fill();
		}

	}

	
}
outTree->Write();
//printf("\n\n#\tCreating file: %s with tree named \"cleaned\"\n",fname.Copy().Prepend("cal_").Data());
printf("#\tWe got from %lli entries to %lli entries with trigger cut\n",inTree->GetEntries(), outTree->GetEntries()	);
printf("#\tThat gives %i%% total efficiency\n", static_cast<int>(100*outTree->GetEntries()/inTree->GetEntries())	);
printf("#\tTDC signals out of phase: %i%%\n", static_cast<int>(100*(nEntries-tac_count)/nEntries)	);
printf("#\tSQL amplitude at 0: %i%%\n", static_cast<int>(100*(nEntries-sql_count)/nEntries)		);
printf("#\tWrong tracking: %i%%\twhile there is %i%% of 0_mult events\n", static_cast<int>	(100*(nEntries-mwpc_count)/nEntries),static_cast<int>(100*(nEntries-zero_mult)/nEntries));
printf("#\tToF out of range: %i%%\n", static_cast<int>(100*(nEntries-tof_range_count)/nEntries)	);
printf("#\tGoodbye\n");
return 1;
}

muchobojca::~muchobojca()
{
}