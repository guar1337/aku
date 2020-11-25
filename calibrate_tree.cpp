#include "calibrate_tree.h"


R__LOAD_LIBRARY(libgsl.so);
R__LOAD_LIBRARY(/home/zalewski/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/libMr_Blue_Sky.so);


ClassImp(calibrate_tree);
calibrate_tree::calibrate_tree()
{
	maynard = new TOOL();
	//tof_shift_A = -400;
	tof_shift_B = 1.0;
	counter = 0;

}

bool calibrate_tree::wrk(TTree *inTree, TTree *outTree) 
{

//Creating addresses of BEAM holding branches
inTree->SetMakeClass(1);
//inTree->Print();
inTree->SetBranchAddress("CsI_L",	in_CsI_L);
inTree->SetBranchAddress("CsI_R",	in_CsI_R);
inTree->SetBranchAddress("SQX_L",	in_SQX_L);
inTree->SetBranchAddress("SQX_R",	in_SQX_R);
inTree->SetBranchAddress("SQY_L",	in_SQY_L);
inTree->SetBranchAddress("SQY_R",	in_SQY_R);

inTree->SetBranchAddress("tSQX_L",	in_tSQX_L);
inTree->SetBranchAddress("tSQX_R",	in_tSQX_R);
inTree->SetBranchAddress("tCsI_L",	in_tCsI_L);
inTree->SetBranchAddress("tCsI_R",	in_tCsI_R);
inTree->SetBranchAddress("tSQY_L",	in_tSQY_L);
inTree->SetBranchAddress("tSQY_R",	in_tSQY_R);
if (cs::runNo == 3)
{
	inTree->SetBranchAddress("SQ300",	in_SQ300);
	inTree->SetBranchAddress("tSQ300",	in_tSQ300);
}



inTree->SetBranchAddress("tF3",	in_tdcF3);
inTree->SetBranchAddress("F3",	in_aF3);
inTree->SetBranchAddress("tF5",	in_tdcF5);
inTree->SetBranchAddress("F5",	in_aF5);
inTree->SetBranchAddress("tF6",	in_tdcF6);
inTree->SetBranchAddress("F6",	in_aF6);

inTree->SetBranchAddress("nx1",	&in_nx1);
inTree->SetBranchAddress("ny1",	&in_ny1);
inTree->SetBranchAddress("nx2",	&in_nx2);
inTree->SetBranchAddress("ny2",	&in_ny2);

inTree->SetBranchAddress("x1",		in_x1);
inTree->SetBranchAddress("y1",		in_y1);
inTree->SetBranchAddress("x2",		in_x2);
inTree->SetBranchAddress("y2",		in_y2);
inTree->SetBranchAddress("tMWPC",	in_tMWPC);
inTree->SetBranchAddress("trig",	&in_trig);
inTree->SetBranchAddress("tof",		&in_tof);
inTree->SetBranchAddress("sumF5",	&sumF5);


//ReCo - detectors
outTree->SetMakeClass(1);
//CALIBRATED DATA
outTree->Branch("SQX_L",	out_SQX_L,	"SQX_L[32]/D");
outTree->Branch("SQX_Ln",	out_SQX_Lnew,	"SQX_Ln[32]/D");
outTree->Branch("SQX_R",	out_SQX_R,	"SQX_R[32]/D");	
outTree->Branch("SQY_L",	out_SQY_L,	"SQY_L[16]/D");
outTree->Branch("SQY_R",	out_SQY_R,	"SQY_R[16]/D");
outTree->Branch("CsI_L",	out_CsI_L,	"CsI_L[16]/D");
outTree->Branch("CsI_0L",	out_CsI_0L,	"CsI_0L[16]/D");
outTree->Branch("CsI_R",	out_CsI_R,	"CsI_R[16]/D");
outTree->Branch("SQ300",	out_SQ300,	"SQ300[16]/D");
outTree->Branch("sqretot",	&sqretot,	"sqretot/D");

outTree->Branch("tSQX_L",	out_tSQX_L,	"tSQX_L[32]/D");
outTree->Branch("tSQX_R",	out_tSQX_R,	"tSQX_R[32]/D");
outTree->Branch("tSQY_L",	out_tSQY_L,	"tSQY_L[16]/D");
outTree->Branch("tSQY_R",	out_tSQY_R,	"tSQY_R[16]/D");
outTree->Branch("tCsI_L",	out_tCsI_L,	"tCsI_L[16]/D");
outTree->Branch("tCsI_R",	out_tCsI_R,	"tCsI_R[16]/D");
outTree->Branch("tSQ300",	out_tSQ300,	"tSQ300[16]/D");	

outTree->Branch("tF3",	out_tF3,	"tF3[4]/D");
outTree->Branch("F3",	out_F3,		"F3[4]/D");
outTree->Branch("tF5",	out_tF5,	"tF5[4]/D");
outTree->Branch("F5",	out_F5,		"F5[4]/D");
outTree->Branch("tF6",	out_tF6,	"tF6[4]/D");
outTree->Branch("F6",	out_F6,		"F6[4]/D");

outTree->Branch("x1",	out_x1,	"x1[32]/s");
outTree->Branch("x2",	out_x2,	"x2[32]/s");
outTree->Branch("y1",	out_y1,	"y1[32]/s");
outTree->Branch("y2",	out_y2,	"y2[32]/s");
	
outTree->Branch("nx1",		&out_nx1,	"nx1/s");
outTree->Branch("nx2",		&out_nx2,	"nx2/s");
outTree->Branch("ny1",		&out_ny1,	"ny1/s");
outTree->Branch("ny2",		&out_ny2,	"ny2/s");
outTree->Branch("tMWPC",	out_tMWPC,	"tMWPC[4]/f");

//RAW DATA
outTree->Branch("r_SQX_L",	r_SQX_L,	"r_SQX_L[32]/D");
outTree->Branch("r_SQX_R",	r_SQX_R,	"r_SQX_R[32]/D");
outTree->Branch("r_SQY_L",	r_SQY_L,	"r_SQY_L[16]/D");
outTree->Branch("r_SQY_R",	r_SQY_R,	"r_SQY_R[16]/D");
outTree->Branch("r_CsI_L",	r_CsI_L,	"r_CsI_L[16]/D");
outTree->Branch("r_CsI_R",	r_CsI_R,	"r_CsI_R[16]/D");

outTree->Branch("trig",		&out_trig,	"trig/I");
outTree->Branch("tof",		&out_tof,	"tof/D");
outTree->Branch("kinE",		&kinE,	"kinE/D");
outTree->Branch("aF5",		&aF5,	"aF5/D");
outTree->Branch("az",	&AZ,		 "az/D");
outTree->Branch("run",	&Run_ID,	"run/S");



if (maynard->params_loader("sqx_l_ec.clb", a_SQX_L, b_SQX_L, 32)	&&
	maynard->params_loader("sqx_r_ec.clb", a_SQX_R, b_SQX_R, 32)	&&

	maynard->params_loader("sqy_l_ec.clb", a_SQY_L, b_SQY_L, 16)	&&
	maynard->params_loader("sqy_r_ec.clb", a_SQY_R, b_SQY_R, 16)	&&

	maynard->params_loader("csi_r_ec.clb", a_CsI_R, b_CsI_R, 16)	&&
	maynard->params_loader("csi_l_ec.clb", a_CsI_L, b_CsI_L, 16)	&&

	maynard->params_loader("SQ300.clb", a_SQ300, b_SQ300, 16)	)
{
	printf("#\tSuccesfully loaded all the parameters for calibration\n");
}

else
{
	return 0;
}

TString fileName = inTree->GetCurrentFile()->GetName();
fileName.ReplaceAll(".root", "");
fileName.Remove(0,38);
fileName.Remove(2,2);

Run_ID = fileName.Atoi();
printf("%d\n",fileName.Atoi());

Long64_t nEntries = inTree->GetEntries();
printf("##############################################################################\n");
printf("#\tLoaded files have %lli entries. \n#\tProcessing...\n", nEntries);

for (Long64_t entry=0; entry<nEntries; entry++)
{
	inTree->GetTree()->GetEntry(entry);
	if( entry % ( nEntries / 10 ) == 0)
	{
		printf("#\tProgress: %i%%\n",counter);
		counter+=10;
	}
	out_nx1=in_nx1;
	out_nx2=in_nx2;
	out_ny1=in_ny1;
	out_ny2=in_ny2;
	out_trig=in_trig;
	aF5 = (in_aF5[0] + in_aF5[1] + in_aF5[2] + in_aF5[3])/4.0;
	Run_ID=0;
	if (Run_ID == 0)
	{
		for (int iii=0; iii<4; iii++)
		{
			out_tF3[iii]	=	(in_tdcF3[iii]+tof_shift_A)*0.125*tof_shift_B;
			out_F3[iii]		=	in_aF3[iii];
			out_tF5[iii]	=	(in_tdcF5[iii]+tof_shift_A)*0.125*tof_shift_B;
			out_F5[iii]		=	in_aF5[iii];
			out_tF6[iii]	=	(in_tdcF6[iii]+tof_shift_A)*0.125*tof_shift_B;
			out_F6[iii]		=	in_aF6[iii];
			out_tMWPC[iii]	=	((in_tMWPC[iii]-tof_shift_A)/3.4133)*tof_shift_B;
		}

		for (int iii=0; iii<16; iii++)
		{
			out_SQY_L[iii]=(in_SQY_L[iii]+gRandom->Uniform())*b_SQY_L[iii]+a_SQY_L[iii];
			out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];
			out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];
			out_CsI_L[iii]=(in_CsI_L[iii]+gRandom->Uniform())*b_CsI_L[iii]+a_CsI_L[iii];
			
			if (cs::runNo == 3)
			{
				out_SQ300[iii]=(in_SQ300[iii]+gRandom->Uniform())*b_SQ300[iii]+a_SQ300[iii];
				out_tSQ300[iii]=in_tSQ300[iii];
			}

			out_tSQY_L[iii]=in_tSQY_L[iii];
			out_tSQY_R[iii]=in_tSQY_R[iii];
			out_tCsI_R[iii]=in_tCsI_R[iii];
			out_tCsI_L[iii]=in_tCsI_L[iii];

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
			out_tSQX_R[iii]=in_tSQX_R[iii];
			out_tSQX_L[iii]=in_tSQX_L[iii];

			r_SQX_L[iii]=in_SQX_L[iii];
			r_SQX_R[iii]=in_SQX_R[iii];
		}
	}

	else if (Run_ID > 40)
	{
		for (int iii=0; iii<4; iii++)
		{
			out_tF3[iii]=in_tdcF3[iii]*0.0625;
			out_F3[iii]=in_aF3[iii];
			out_tF5[iii]=in_tdcF5[iii]*0.0625;
			out_F5[iii]=in_aF5[iii];
			out_tF6[iii]=in_tdcF6[iii]*0.0625;
			out_F6[iii]=in_aF6[iii];
			out_tMWPC[iii] = in_tMWPC[iii]/3.4133;
		}

		for (int iii=0; iii<16; iii++)
		{
			out_SQY_L[iii]=(in_SQY_L[iii]+gRandom->Uniform())*b_DSDY_L_5[iii]+a_DSDY_L_5[iii];
			out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_DSDY_R_5[iii]+a_DSDY_R_5[iii];
			out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R_5[iii]+a_CsI_R_5[iii];
			out_CsI_L[iii]=(in_CsI_L[iii]+gRandom->Uniform())*b_SSD_L_5[iii]+a_SSD_L_5[iii];

			out_tSQY_L[iii]=in_tSQY_L[iii];
			out_tSQY_R[iii]=in_tSQY_R[iii];
			out_tCsI_R[iii]=in_tCsI_R[iii];
			out_tCsI_L[iii]=in_tCsI_L[iii];

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

			out_SQX_L[iii]=(in_SQX_L[iii]+gRandom->Uniform())*b_DSDX_L_5[iii]+a_DSDX_L_5[iii];
			out_SQX_R[iii]=(in_SQX_R[iii]+gRandom->Uniform())*b_DSDX_R_5[iii]+a_DSDX_R_5[iii];
			out_tSQX_R[iii]=in_tSQX_R[iii];
			out_tSQX_L[iii]=in_tSQX_L[iii];

			r_SQX_L[iii]=in_SQX_L[iii];
			r_SQX_R[iii]=in_SQX_R[iii];
		}
	}
	
	else if ( (Run_ID > 0) && (Run_ID<40))
	{
		for (int iii=0; iii<4; iii++)
		{
			out_tF3[iii]	=	(in_tdcF3[iii])*0.125;
			out_F3[iii]		=	in_aF3[iii];
			out_tF5[iii]	=	(in_tdcF5[iii])*0.125;
			out_F5[iii]		=	in_aF5[iii];
			out_tF6[iii]	=	(in_tdcF6[iii])*0.125;
			out_F6[iii]		=	in_aF6[iii];
			out_tMWPC[iii]	=	((in_tMWPC[iii])/3.4133);
		}

		for (int iii=0; iii<16; iii++)
		{
			out_SQY_L[iii]=(in_SQY_L[iii]+gRandom->Uniform())*b_SQY_L[iii]+a_SQY_L[iii];
			out_SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];
			out_CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];
			out_CsI_L[iii]=(in_CsI_L[iii]+gRandom->Uniform())*b_CsI_L[iii]+a_CsI_L[iii];

			out_tSQY_L[iii]=in_tSQY_L[iii];
			out_tSQY_R[iii]=in_tSQY_R[iii];
			out_tCsI_R[iii]=in_tCsI_R[iii];
			out_tCsI_L[iii]=in_tCsI_L[iii];

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
			out_tSQX_R[iii]=in_tSQX_R[iii];
			out_tSQX_L[iii]=in_tSQX_L[iii];

			r_SQX_L[iii]=in_SQX_L[iii];
			r_SQX_R[iii]=in_SQX_R[iii];
		}
	}

	else
	{
		return 0;
	}

	if (Run_ID > 40)
	{
		out_tof=(-(out_tF3[0]+out_tF3[1]+out_tF3[2]+out_tF3[3])/4.0+(out_tF5[0]+out_tF5[1]+out_tF5[2]+out_tF5[3])/4)+cs::tof_const_5;
	}

	else
	{
		out_tof=(-(out_tF3[0]+out_tF3[1]+out_tF3[2]+out_tF3[3])/4.0+(out_tF5[0]+out_tF5[1]+out_tF5[2]+out_tF5[3])/4)+cs::tof_const;
	}

	Double_t beta_squared= pow((cs::tofBase/out_tof)/cs::c, 2.0);
	Double_t gamma=1.0/sqrt(1.0-beta_squared);
	kinE = cs::mass6He*(gamma-1.0);
	outTree->Fill();
	
	
}
outTree->Write();
return 1;
}

calibrate_tree::~calibrate_tree()
{
}
