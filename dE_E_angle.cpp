#include "dE_E_angle.h"

ClassImp(dE_E_angle);
using namespace std;

dE_E_angle::dE_E_angle()
{
	create_input_tree(NULL);
	create_output_tree(NULL);
}

dE_E_angle::dE_E_angle(TTree *inT, TTree *outT, TString inFile)
{
	create_input_tree(inT);
	create_output_tree(outT);
	maynard = new TOOL();
	s_curFile = inFile;

	int s_Nel=1;
	si_A[0]=28;
	si_Z[0]=14;
	si_W[0]=1;

h2_Si_Eloss 	= new ELC(2, 1, s_Nel, 2.35, si_A, si_Z, si_W, 300.,1500);
h3_Si_Eloss 	= new ELC(3, 1, s_Nel, 2.35, si_A, si_Z, si_W, 200.,1500);
he4_Si_Eloss 	= new ELC(4, 2, s_Nel, 2.35, si_A, si_Z, si_W, 500.,1500);
he6_Si_Eloss 	= new ELC(6, 2, s_Nel, 2.35, si_A, si_Z, si_W, 300.,1500);
li7_Si_Eloss 	= new ELC(7, 3, s_Nel, 2.35, si_A, si_Z, si_W, 700.,1500);
li8_Si_Eloss 	= new ELC(8, 3, s_Nel, 2.35, si_A, si_Z, si_W, 600.,1500);
li9_Si_Eloss 	= new ELC(9, 3, s_Nel, 2.35, si_A, si_Z, si_W, 600.,1500);
be9_Si_Eloss 	= new ELC(9, 4, s_Nel, 2.35, si_A, si_Z, si_W, 1000.,1500);


gcut_h2 = new TCutG("H2",maynard->gcut_noPoints(s_curFile,"h2.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_h2, "h2.dat");

gcut_h3 = new TCutG("H3",maynard->gcut_noPoints(s_curFile, "h3.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_h3, "h3.dat");

gcut_he4 = new TCutG("He4",maynard->gcut_noPoints(s_curFile, "he4.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_he4, "he4.dat");

gcut_he6 = new TCutG("He6",maynard->gcut_noPoints(s_curFile, "he6.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_he6, "he6.dat");

gcut_li7 = new TCutG("Li7",maynard->gcut_noPoints(s_curFile, "li7.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_li7, "li7.dat");

gcut_li8 = new TCutG("Li8",maynard->gcut_noPoints(s_curFile, "li8.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_li8, "li8.dat");

gcut_li9 = new TCutG("Li9",maynard->gcut_noPoints(s_curFile, "li9.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_li9, "li9.dat");

gcut_be9 = new TCutG("Be9",maynard->gcut_noPoints(s_curFile, "be9.dat"),&in_AZ,&in_aF5);
maynard->gcuts_loader(s_curFile, gcut_be9, "be9.dat");



TRotation beam_setting_array;
}

dE_E_angle::~dE_E_angle()
{
	delete h2_Si_Eloss;
	delete h3_Si_Eloss;
	delete he4_Si_Eloss;
	delete he6_Si_Eloss;
	delete li7_Si_Eloss;
	delete li8_Si_Eloss;
	delete li9_Si_Eloss;
	delete be9_Si_Eloss;
	delete maynard;
}

bool dE_E_angle::create_input_tree(TTree *in)
{
	inTree=in;
	inTree->SetMakeClass(1);
	//CALIBRATED DATA
	inTree->SetBranchAddress("CsI_L",	CsI_L);
	inTree->SetBranchAddress("CsI_R",	CsI_R);
	inTree->SetBranchAddress("SQX_L",	SQX_L);
	inTree->SetBranchAddress("SQX_R",	SQX_R);
	inTree->SetBranchAddress("SQY_L",	SQY_L);
	inTree->SetBranchAddress("SQY_R",	SQY_R);
	//RAW DATA
	inTree->SetBranchAddress("r_CsI_L",	r_CsI_L);
	inTree->SetBranchAddress("r_CsI_R",	r_CsI_R);
	inTree->SetBranchAddress("r_SQX_L",	r_SQX_L);
	inTree->SetBranchAddress("r_SQX_R",	r_SQX_R);
	inTree->SetBranchAddress("r_SQY_L",	r_SQY_L);
	inTree->SetBranchAddress("r_SQY_R",	r_SQY_R);

	//TIME
	inTree->SetBranchAddress("tSQX_L",	in_tSQX_L);
	inTree->SetBranchAddress("tSQX_R",	in_tSQX_R);
	inTree->SetBranchAddress("tCsI_L",	in_tCsI_L);
	inTree->SetBranchAddress("tCsI_R",	in_tCsI_R);
	inTree->SetBranchAddress("tSQY_L",	in_tSQY_L);
	inTree->SetBranchAddress("tSQY_R",	in_tSQY_R);

	inTree->SetBranchAddress("tF3",		 in_tF3);
	inTree->SetBranchAddress("F3",		in_F3);
	inTree->SetBranchAddress("tF5",		 in_tF5);
	inTree->SetBranchAddress("F5",		in_F5);
	inTree->SetBranchAddress("tF6",		 in_tF6);
	inTree->SetBranchAddress("F6",		in_F6);

	inTree->SetBranchAddress("nx1",		&in_nx1);
	inTree->SetBranchAddress("ny1",		&in_ny1);
	inTree->SetBranchAddress("nx2",		&in_nx2);
	inTree->SetBranchAddress("ny2",		&in_ny2);

	inTree->SetBranchAddress("tMWPC",	in_tMWPC);

	inTree->SetBranchAddress("x1",	 in_x1);
	inTree->SetBranchAddress("y1",	 in_y1);
	inTree->SetBranchAddress("x2",	 in_x2);
	inTree->SetBranchAddress("y2",	 in_y2);

	inTree->SetBranchAddress("trig",	 &in_trig);
	inTree->SetBranchAddress("tof",	 &in_tof);
	inTree->SetBranchAddress("az",	 &in_AZ);
	inTree->SetBranchAddress("aF5",	 &in_aF5);


 	return true;
}

bool dE_E_angle::create_output_tree(TTree *out)
{
	outTree=out;
	
	LV_6He = new TLorentzVector();
	LV_2H = new TLorentzVector();
	LV_tar_1H = new TLorentzVector();
	LV_tar_2H = new TLorentzVector();
	LV_beam = new TLorentzVector();

	
	outTree->SetMakeClass(1);
	outTree->Branch("SQX_L_m",	 &SQX_L_mult,	"SQX_L_m/S");
	outTree->Branch("SQX_R_m",	 &SQX_R_mult,	"SQX_R_m/S");
	outTree->Branch("SQY_L_m",	 &SQY_L_mult,	"SQY_L_m/S");
	outTree->Branch("SQY_R_m",	 &SQY_R_mult,	"SQY_R_m/S");
	outTree->Branch("CsI_L_m",	 &CsI_L_mult,	"CsI_L_m/S");
	outTree->Branch("CsI_R_m",	 &CsI_R_mult,	"CsI_R_m/S");

	outTree->Branch("tSQX_L",	 out_tSQX_L,	 "tSQX_L[32]/D");
	outTree->Branch("tSQX_R",	 out_tSQX_R,	 "tSQX_R[32]/D");
	outTree->Branch("tSQY_L",	 out_tSQY_L,	 "tSQY_L[16]/D");
	outTree->Branch("tSQY_R",	 out_tSQY_R,	 "tSQY_R[16]/D");
	outTree->Branch("tCsI_L",	 out_tCsI_L,	 "tCsI_L[16]/D");
	outTree->Branch("tCsI_R",	 out_tCsI_R,	 "tCsI_R[16]/D");

	outTree->Branch("SQY_L_e",	SQY_L_Edep,	 "SQY_L_e[16]/D");
	outTree->Branch("SQY_R_e",	SQY_R_Edep,	 "SQY_R_e[16]/D");
	outTree->Branch("SQX_L_e",	SQX_L_Edep,	 "SQX_L_e[32]/D");
	outTree->Branch("SQX_R_e",	SQX_R_Edep,	 "SQX_R_e[32]/D");
	outTree->Branch("CsI_L_e",	CsI_L_Edep,	 "CsI_L_e[16]/D");
	outTree->Branch("CsI_R_e",	CsI_R_Edep,	 "CsI_R_e[16]/D");

	outTree->Branch("SQX_L_s",	SQX_L_strip,	"SQX_L_s[32]/S");
	outTree->Branch("SQX_R_s",	SQX_R_strip,	"SQX_R_s[32]/S");
	outTree->Branch("SQY_L_s",	SQY_L_strip,	"SQY_L_s[16]/S");
	outTree->Branch("SQY_R_s",	SQY_R_strip,	"SQY_R_s[16]/S");
	outTree->Branch("CsI_L_s",	CsI_L_strip,	"CsI_L_s[16]/S");
	outTree->Branch("CsI_R_s",	CsI_R_strip,	"CsI_R_s[16]/S");

	outTree->Branch("sqlphi",	 &sqlphi,		"sqlphi/D");
	outTree->Branch("sqltheta",	 &sqltheta,	"sqltheta/D");
	outTree->Branch("sqltheta1H",	 &sqltheta1H,	"sqltheta1H/D");
	outTree->Branch("sqltheta2H",	 &sqltheta2H,	"sqltheta2H/D");
	outTree->Branch("sqlde",		&sqlde,		 "sqlde/D");

	outTree->Branch("sqde1",		&fsqde1,		 "sqde1/D");
	outTree->Branch("sqde2",		&fsqde2,		 "sqde2/D");

	outTree->Branch("sqlde1H",		&sqlde1H,		 "sqlde1H/D");
	outTree->Branch("sqlde2H",		&sqlde2H,		 "sqlde2H/D");
	outTree->Branch("sqletot",	&sqletot,	 "sqletot/D");
	outTree->Branch("sqlang",	&sqlang,	 "sqlang/D");
	outTree->Branch("sqlxtime",	&sqlxtime,	 "sqlxtime/D");
	outTree->Branch("sqlytime",	&sqlytime,	 "sqlytime/D");


	outTree->Branch("sqrtheta",	 &sqrtheta,	"sqrtheta/D");
	outTree->Branch("sqrphi",	 &sqrphi,		"sqrphi/D");
	outTree->Branch("sqrde",		&sqrde,		 "sqrde/D");
	outTree->Branch("fsqrde",		&fsqrde,		 "fsqrde/D");
	outTree->Branch("sqretot",	&sqretot,	 "sqretot/D");
	outTree->Branch("sqrang",	&sqrang,	 "sqrang/D");
	outTree->Branch("sqrxtime",	&sqrxtime,	 "sqrxtime/D");
	outTree->Branch("sqrytime",	&sqrytime,	 "sqrytime/D");

	outTree->Branch("s_csir",	 &memS_CsI_R,	"s_csir/S");
	outTree->Branch("s_csil",	 &memS_CsI_L,	"s_csil/S");

	outTree->Branch("X2H",	&X2H,	 "X2H/F");
	outTree->Branch("Y2H",	&Y2H,	 "Y2H/F");
	outTree->Branch("Z2H",	&Z2H,	 "Z2H/F");

	outTree->Branch("X6He",	&X6He,	 "X6He/F");
	outTree->Branch("Y6He",	&Y6He,	 "Y6He/F");
	outTree->Branch("Z6He",	&Z6He,	 "Z6He/F");

	outTree->Branch("evX",	&evX,	 "evX/F");
	outTree->Branch("evY",	&evY,	 "evY/F");
	outTree->Branch("evZ",	&evZ,	 "evZ/F");

	outTree->Branch("dist_tar_det",	&dist_tar_det,	 "dist_tar_det/F");

	outTree->Branch("tF3",	out_tF3,	 "tF3[4]/D");
	outTree->Branch("F3",	 out_F3,		"F3[4]/D");
	outTree->Branch("tF5",	out_tF5,	 "tF5[4]/D");
	outTree->Branch("F5",	 out_F5,		"F5[4]/D");
	outTree->Branch("tF6",	out_tF6,	 "tF6[4]/D");
	outTree->Branch("F6",	 out_F6,		"F6[4]/D");


	outTree->Branch("tof",	&out_tof,		 "tof/D");
	outTree->Branch("aF5",	&out_aF5,		 "aF5/D");
	outTree->Branch("az",	&out_AZ,		 "az/D");
	outTree->Branch("T",	&out_T1,		 "T/D");
	outTree->Branch("id",	&Ion_ID,	"id/S");

	outTree->Branch("x1",	out_x1,	"x1[32]/s");
	outTree->Branch("x2",	out_x2,	"x2[32]/s");
	outTree->Branch("y1",	out_y1,	"y1[32]/s");
	outTree->Branch("y2",	out_y2,	"y2[32]/s");

	outTree->Branch("tMWPC",	out_tMWPC,	 "tMWPC[4]/F");	

	outTree->Branch("nx1",	&out_nx1,	"nx1/s");
	outTree->Branch("nx2",	&out_nx2,	"nx2/s");
	outTree->Branch("ny1",	&out_ny1,	"ny1/s");
	outTree->Branch("ny2",	&out_ny2,	"ny2/s");

	outTree->Branch("trigger",	&out_trig,	"trigger/S");
	outTree->Branch("missMass",	 &missMass,	"missMass/D");

	outTree->Branch("c_SQX_L",	 c_SQX_L,	 "c_SQX_L[32]/D");
	outTree->Branch("c_SQX_R",	 c_SQX_R,	 "c_SQX_R[32]/D");
	outTree->Branch("c_SQY_L",	 c_SQY_L,	 "c_SQY_L[16]/D");
	outTree->Branch("c_SQY_R",	 c_SQY_R,	 "c_SQY_R[16]/D");
	outTree->Branch("c_CsI_L",	 c_CsI_L,	 "c_CsI_L[16]/D");
	outTree->Branch("c_CsI_R",	 c_CsI_R,	 "c_CsI_R[16]/D");

	outTree->Branch("r_SQX_L",	 raw_SQX_L,	 "r_SQX_L[32]/D");
	outTree->Branch("r_SQX_R",	 raw_SQX_R,	 "r_SQX_R[32]/D");
	outTree->Branch("r_SQY_L",	 raw_SQY_L,	 "r_SQY_L[16]/D");
	outTree->Branch("r_SQY_R",	 raw_SQY_R,	 "r_SQY_R[16]/D");
	outTree->Branch("r_CsI_L",	 raw_CsI_L,	 "r_CsI_L[16]/D");
	outTree->Branch("r_CsI_R",	 raw_CsI_R,	 "r_CsI_R[16]/D");

	outTree->Bronch("LV_6He.",		"TLorentzVector",	&LV_6He);
	outTree->Bronch("LV_2H.",		"TLorentzVector",	&LV_2H);
	outTree->Bronch("LV_beam.",	"TLorentzVector",	&LV_beam);

	outTree->Branch("mwpc",	&mwpc,	 "mwpc/B");
	outTree->Branch("ms",	&ms,	 "ms/B");
	outTree->Branch("tar",	&tar,	 "tar/B");
	outTree->Branch("the6",	&the6,	 "the6/B");

	outTree->Branch("cln1",	&cln1,	 "cln1/B");
	outTree->Branch("cln2",	&cln2,	 "cln2/B");
	outTree->Branch("cln3",	&cln3,	 "cln3/B");
	return true;
}

bool dE_E_angle::actual_work()
{

	Long64_t nEntries = inTree->GetEntries();
	TVector3 zx(0.0,1.0,0.0), v_beam(0.0,0.0,1.0), v_tar(0.0, 0.0, 0.0);
	TRandom3 *rnd = new TRandom3();
	counter = 0;
	maynard->initializeGeometry(&SQR_ang, &SQL_ang, &SQR_dist, &SQL_dist, &tar_angle);
	maynard->getTarCuts(&tar_cut_lo_X, &tar_cut_hi_X, &tar_cut_lo_Y, &tar_cut_hi_Y);
	maynard->getTimeCorrectionForDets(	&tcor_sqLX_I, &tcor_sqLX_II, &tcor_sqRX_I,
										&tcor_sqRX_II, &tcor_sqLY, &tcor_sqRY);

	printf("##############################################################################\n");
	printf("#	Loaded file %s has %lli entries. \n#	Processing...\n", s_curFile.Data(), nEntries);

Long64_t st=0, nd=0, rd=0, th=0;
for (Long64_t entry=0; entry<nEntries; entry++)
	{
	inTree->GetEntry(entry);

	if( entry % ( nEntries / 10 ) == 0)
		{
			printf("# Progress: %i %%\n", counter);
			counter+=10;
		}
	//NULLing everything
		LV_tar_2H->SetVectM(v_tar,s::mass_2H);
		LV_tar_1H->SetVectM(v_tar,s::mass_1H);
		memE_CsI_R=0.0; memE_CsI_L=0.0; memS_CsI_R=20; memS_CsI_L=20;
		dist_tar_det = 0.0, kine_2H=0.0, kine_1H=0.0;
		Ion_ID = 0, out_T1 = 0.0, out_T2 = 0.0, fsqde1=0.0, fsqde2=0.0;
		evX=0.0;evY=0.0;evZ=0.0;
		cln1=false, cln2=false, cln3=false;
		mwpc=false; ms=false; tar=false, the6=false;

		X6He=0.0; Y6He=0.0; Z6He=0.0; X2H=0.0; Y2H=0.0; Z2H=0.0;

		sqrphi=0.0; sqrtheta=0.0; sqrang=0.0; sqrde=0.0; sqretot=0.0;
		sqlphi=0.0; sqltheta=0.0; sqlang=0.0; sqlde=0.0; sqletot=0.0;		

		SQX_L_mult=0; SQY_L_mult=0; CsI_L_mult=0;
		SQX_R_mult=0; SQY_R_mult=0; CsI_R_mult=0;

		maynard->null_energy(	SQX_L_Edep,SQY_L_Edep,CsI_L_Edep,
								SQX_R_Edep,SQY_R_Edep,CsI_R_Edep);

		maynard->null_strips(	SQX_L_strip, SQY_L_strip, CsI_L_strip,
								SQX_R_strip, SQY_R_strip, CsI_R_strip);



	out_aF5 = in_aF5;
	out_nx1=in_nx1;
	out_nx2=in_nx2;
	out_ny1=in_ny1;
	out_ny2=in_ny2;
	out_trig=in_trig;
	out_tof = in_tof;
	out_AZ = in_AZ;

	//4 channels loop
	for (int iii=0; iii<4; iii++)
	{
		out_tF3[iii]=in_tF3[iii];
		out_F3[iii]=in_F3[iii];
		out_tF5[iii]=in_tF5[iii];
		out_F5[iii]=in_F5[iii];
		out_tF6[iii]=in_tF6[iii];
		out_F6[iii]=in_F6[iii];
		out_tMWPC[iii] = in_tMWPC[iii];
	}

	//16 channels loop
	for (int iii=0; iii<16; iii++)
	{
		if (in_tSQY_L[iii]>s::tc_SQY_L)
		{
			SQY_L_mult++;
			SQY_L_Edep[SQY_L_mult]=SQY_L[iii];
			SQY_L_strip[SQY_L_mult]=iii;
		}

		if (in_tSQY_R[iii]>s::tc_SQY_R)
		{
			SQY_R_mult++;
			SQY_R_Edep[SQY_R_mult]=SQY_R[iii];
			SQY_R_strip[SQY_R_mult]=iii;
		}

		if (in_tCsI_R[iii]>s::tc_CsI_R)
		{
			if (memE_CsI_R<CsI_R[iii])
			{
				memE_CsI_R = CsI_R[iii];
				memS_CsI_R = iii;
			}

			CsI_R_mult++;
			CsI_R_Edep[CsI_R_mult]=CsI_R[iii];
			CsI_R_strip[CsI_R_mult]=iii;
		}

		if (in_tCsI_L[iii]>s::tc_CsI_L)
		{
			if (memE_CsI_L<CsI_L[iii])
			{
				memE_CsI_L = CsI_L[iii];
				memS_CsI_L = iii;
			}
			CsI_L_mult++;
			CsI_L_Edep[CsI_L_mult]=CsI_L[iii];
			CsI_L_strip[CsI_L_mult]=iii;
		}

		c_SQX_L[iii]=SQX_L[iii];
		c_SQX_R[iii]=SQX_R[iii];
		c_SQY_L[iii]=SQY_L[iii];
		c_SQY_R[iii]=SQY_R[iii];
		c_CsI_L[iii]=CsI_L[iii];
		c_CsI_R[iii]=CsI_R[iii];

		raw_SQX_L[iii]=r_SQX_L[iii];
		raw_SQX_R[iii]=r_SQX_R[iii];
		raw_SQY_L[iii]=r_SQY_L[iii];
		raw_SQY_R[iii]=r_SQY_R[iii];
		raw_CsI_L[iii]=r_CsI_L[iii];
		raw_CsI_R[iii]=r_CsI_R[iii];


		out_tCsI_L[iii]=in_tCsI_L[iii];
		out_tCsI_R[iii]=in_tCsI_R[iii];
		out_tSQY_L[iii]=in_tSQY_L[iii];
		out_tSQY_R[iii]=in_tSQY_R[iii];
	}

	//32 channels loop
	for (int iii=0; iii<32; iii++)
	{
		out_x1[iii]=in_x1[iii];
		out_x2[iii]=in_x2[iii];
		out_y1[iii]=in_y1[iii];
		out_y2[iii]=in_y2[iii];

		if (in_tSQX_L[iii]>s::tc_SQX_L)
		{
			SQX_L_mult++;
			SQX_L_Edep[SQX_L_mult]=SQX_L[iii];
			SQX_L_strip[SQX_L_mult]=iii;
		}

		if (in_tSQX_R[iii]>s::tc_SQX_R)
		{
			SQX_R_mult++;
			SQX_R_Edep[SQX_R_mult]=SQX_R[iii];
			SQX_R_strip[SQX_R_mult]=iii;
		}

			out_tSQX_L[iii]=in_tSQX_L[iii];
			out_tSQX_R[iii]=in_tSQX_R[iii];
	}
	//MWPC
	if(	maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, s::MWPC_1_X_id)*
		maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, s::MWPC_1_Y_id)*
		maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, s::MWPC_2_X_id)*
		maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, s::MWPC_2_Y_id))
	{
		//displacement + go to corner of MWPC + follow wire order - get event point
		mwpc=true;
		MWPC_1_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Z = -816.0;

		MWPC_2_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Z = -270.0;

		dX=MWPC_2_X-MWPC_1_X;
		dY=MWPC_2_Y-MWPC_1_Y;
		dZ=MWPC_2_Z-MWPC_1_Z;
		
		v_beam.SetXYZ(dX,dY,dZ);
		Float_t det_effctv_thcknss = 347.1/(cos(v_beam.Theta()));
		Float_t det_thcknss = 1000.0/(cos(v_beam.Theta()));
			// choose correct Eloss method
		if (in_AZ<2.2)
		{
			if (gcut_h2->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_2H);
				out_T1 = h2_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = h2_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - h2_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - h2_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 21;
				//printf("Co ja robie tuuu %i\n",Ion_ID );
			}

			else if (gcut_he4->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_4He);
				out_T1 = he4_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = he4_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - he4_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - he4_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 42;
			}
		}

		else if (in_AZ>2.2 && in_AZ<2.6)
		{
			if (gcut_be9->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_9Be);
				out_T1 = be9_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = be9_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - be9_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - be9_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 94;
			}

			else if (gcut_li7->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_7Li);
				out_T1 = li7_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = li7_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - li7_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - li7_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 73;
			}

		}

		else if (in_AZ>2.6 && in_AZ<2.85)
		{
			if (gcut_li8->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_8Li);
				out_T1 = li8_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = li8_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - li8_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - li8_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 83;
			}
		}

		else if (in_AZ>2.85 && in_AZ<3.2)
		{
			if (gcut_he6->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_6He);
				out_T1 = he6_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = he6_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - he6_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - he6_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 62;
			}

			else if (gcut_h3->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_3H);
				out_T1 = h3_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = h3_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - h3_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - h3_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 31;
			}

			else if (gcut_li9->IsInside(in_AZ,in_aF5))
			{
				tempT = maynard->getT(in_tof,s::mass_9Li);
				out_T1 = li9_Si_Eloss->GetE(tempT, 347.1);
				out_T2 = li9_Si_Eloss->GetE(tempT, det_effctv_thcknss);
				fsqde1 = out_T1 - li9_Si_Eloss->GetE(out_T1, 1000.0);
				fsqde2 = out_T2 - li9_Si_Eloss->GetE(out_T2, det_thcknss);
				Ion_ID = 93;
			}
		}

		//rotation matrix that will convert 2H or 6He particle so that they will see beam as Z axis
		beam_setting_array.SetZAxis(v_beam.Unit(),zx);
		beam_setting_array.Invert();

		//v_beam.Transform(beam_setting_array);
		ene_beam = s::mass_6He + out_T2;
		mom_beam = sqrt(ene_beam*ene_beam - s::mass_6He*s::mass_6He);

		v_beam.SetMag(mom_beam);
		//printf("Wat wat wat%f\n",v_beam.Mag());	
		
		LV_beam->SetVectM(v_beam, s::mass_6He);
		Tcoef=(cos(tar_angle)*s::tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);
		XZsum= - sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z;

		evX = MWPC_1_X + dX*Tcoef;
		evY = MWPC_1_Y + dY*Tcoef;
		evZ = MWPC_1_Z + dZ*Tcoef;
		if (evX > tar_cut_lo_X && evX < tar_cut_hi_X	&&
			evY > tar_cut_lo_Y && evY < tar_cut_lo_Y	)
		{
			tar=true;
		}
	}




	//SQL energy - deuterium
	if (SQX_L_mult*SQY_L_mult==1 && mwpc)
	{
		sqlde=SQX_L_Edep[1];
		sqletot=memE_CsI_L;
		th++;
		if ((((memS_CsI_L/4)*4 <= SQY_L_strip[1]) 	&&
			((memS_CsI_L/4)*4+3 >= SQY_L_strip[1])	&&
			((memS_CsI_L%4)*8 <= SQX_L_strip[1])	&&
			((memS_CsI_L%4)*8+7 >= SQX_L_strip[1])	))
		{
			st++;
			cln1=true;
		}

		else if (((memS_CsI_L/4)*4-1 <= SQY_L_strip[1]) 	&&
			((memS_CsI_L/4)*4+4 >= SQY_L_strip[1])	&&
			((memS_CsI_L%4)*8-1 <= SQX_L_strip[1])	&&
			((memS_CsI_L%4)*8+8 >= SQX_L_strip[1])	)
		{
			nd++;
			cln2=true;
		}

		else if ((((memS_CsI_L/4)*4-2 <= SQY_L_strip[1]) 	&&
			((memS_CsI_L/4)*4+5 >= SQY_L_strip[1])	&&
			((memS_CsI_L%4)*8-2 <= SQX_L_strip[1])	&&
			((memS_CsI_L%4)*8+9 >= SQX_L_strip[1])	))
		{
			rd++;
			cln3=true;
		}

		//printf("CsI: %i, Y_L:, %i, X_L: %i\n",memS_CsI_L, SQY_L_strip[1], SQX_L_strip[1]);





		if (SQX_L_strip[1]<16)
		{
			sqlxtime=out_tSQX_L[SQX_L_strip[1]]-tcor_sqLX_I/sqlde;
		}
		else if (SQX_L_strip[1]>15)
		{
			sqlxtime=out_tSQX_L[SQX_L_strip[1]]-tcor_sqLX_II/sqlde;
		}
		else
		return 0;
		sqlytime=out_tSQY_L[SQY_L_strip[1]]-tcor_sqLY/sqlde;

		// coordinates of hit in LAB system
		X2H_lab = SQL_dist*sin(SQL_ang) + s::SQL_start_X * cos(SQL_ang);
		Y2H_lab = s::SQL_start_Y;
		Z2H_lab = SQL_dist*cos(SQL_ang) - s::SQL_start_X * sin(SQL_ang);		

		X2H_det=-2. *	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQL_ang);
		Y2H_det=4.	* 	(SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
		Z2H_det=2.	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQL_ang);

		X2H = X2H_lab + X2H_det;
		Y2H = Y2H_lab + Y2H_det;
		Z2H = Z2H_lab + Z2H_det;


		//setting deuterium vector
		TVector3 vect2H(X2H-evX, Y2H-evY, Z2H-evZ);
		ene_2H = sqlde + sqletot + s::mass_2H;
		mom_2H = sqrt(ene_2H*ene_2H-s::mass_2H*s::mass_2H);
		vect2H.SetMag(mom_2H);


		LV_2H->SetVectM(vect2H, s::mass_2H);
	

		missMass = LV_6He->M() - s::mass_6He;

		sqlphi=vect2H.Phi()*s::rad_to_deg;
		sqltheta=vect2H.Theta()*s::rad_to_deg;
		sqlang = vect2H.Angle(v_beam)*s::rad_to_deg;

		
		TLorentzVector LV_beamCopy(*LV_beam);
		//proton kinematics
		/*
		TVector3 vectBoost_1H((LV_beamCopy + *LV_tar_1H).BoostVector());
		LV_tar_1H->Boost(-vectBoost_1H);

		LV_tar_1H->SetTheta(rnd->Uniform(s::PI));
		LV_tar_1H->Boost(vectBoost_1H);

		sqlde1H = LV_tar_1H->E() - s::mass_1H;
		sqltheta1H = LV_tar_1H->Theta()*s::rad_to_deg;
		
		//deuterium kinematics
		Double_t kinThetaCM, kinThetaLab, kinELAB, pCM, lvInvariantBefore, lvInvariantAfter;
		Double_t kinInv, kinXsi, kinEcm, kinMomCM;

		kinThetaCM = rnd->Uniform(s::PI);
		kinInv = pow((s::mass_6He + s::mass_2H), 2) + 2*s::mass_2H*out_T;
		kinMomCM = sqrt((pow(kinInv-(s::mass_2H*s::mass_2H+s::mass_6He*s::mass_6He),2.0)-4*s::mass_2H*s::mass_2H*s::mass_6He*s::mass_6He)/(4*kinInv));
		kinXsi = log((kinMomCM+sqrt(s::mass_2H*s::mass_2H+kinMomCM*kinMomCM))/s::mass_2H);

		TVector3 vectBoost_2H((LV_beamCopy + *LV_tar_2H).BoostVector());
		LV_tar_2H->Boost(-vectBoost_2H);
		kinEcm = LV_tar_2H->E();
		LV_tar_2H->SetTheta(kinThetaCM);
		
//		LV_tar_2H->Boost(vectBoost_2H);
//		sqlde2H = LV_tar_2H->E() - s::mass_2H;
//		sqltheta2H = LV_tar_2H->Theta()*s::rad_to_deg;
		kinThetaLab = atan((kinMomCM*sin(kinThetaCM))/(kinMomCM*cos(kinThetaCM)*cosh(kinXsi)+kinEcm*sinh(kinXsi)));
		kinELAB = sqrt(kinMomCM*kinMomCM+s::mass_2H*s::mass_2H)*cosh(kinXsi)+kinMomCM*cos(kinThetaCM)*sinh(kinXsi)-s::mass_2H;
fsqlde=kinELAB;
sqltheta2H=kinThetaLab;
//		if (out_T>0)
//		{
//			printf("Energy lv: %f\tvs kin: %f and diff:\t%f\n",sqlde2H,kinThetaLab,kinELAB);
//
//		}



*/
	}

	//SQR energy - helium
	if(SQX_R_mult*SQY_R_mult==1 && mwpc)
	{		
		sqrde=SQY_R_Edep[1];
		sqretot=memE_CsI_R;

		if (SQX_R_strip[1]<16)
		{
			sqrxtime=out_tSQX_R[SQX_R_strip[1]]-tcor_sqRX_I/sqrde;
		}
		else if (SQX_R_strip[1]>15)
		{
			sqrxtime=out_tSQX_R[SQX_R_strip[1]]-tcor_sqRX_II/sqrde;
		}
		else
		return 0;
		sqrytime=out_tSQY_R[SQY_R_strip[1]]-tcor_sqRY/sqrde;

		// coordinates of hit in LAB system
		X6He_lab = SQR_dist*(-sin(SQR_ang)) + s::SQR_start_X * cos(SQR_ang);
		Y6He_lab = s::SQR_start_Y;
		Z6He_lab = SQR_dist*cos(SQR_ang) + s::SQR_start_X * sin(SQR_ang);		

		X6He_det= 2.*(SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQR_ang);
		Y6He_det= 4.* (SQY_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
		Z6He_det= 2.*(SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQR_ang);

		X6He = X6He_lab + X6He_det;
		Y6He = Y6He_lab + Y6He_det;
		Z6He = Z6He_lab + Z6He_det;

		//setting deuterium vector
		TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
		ene_6He = sqrde + sqretot + s::mass_6He;
		mom_6He = sqrt(ene_6He*ene_6He-s::mass_6He*s::mass_6He);
		vect6He.SetMag(mom_6He);


		LV_6He->SetVectM(vect6He, s::mass_6He);


		*LV_2H = *LV_tar_2H + *LV_beam - *LV_6He;
		//setting LAB angles of scattered 6 He - reference is beam vector
		//vect6He=beam_setting_array*vect6He;
		sqrtheta=vect6He.Theta()*s::rad_to_deg;
		sqrphi=vect6He.Phi()*s::rad_to_deg;
		sqrang = vect6He.Angle(v_beam)*s::rad_to_deg;
	}
	outTree->Fill();


}
printf("1st filter: %lli, 2nd filter: %lli, 3rd filter: %lli from: %lli\n",st, nd, rd, th);
TString outFname(s_curFile.Copy().ReplaceAll("cal_","dE_").Data());
printf("#	Creating file: %s with tree named \"dE_E\" \n",outFname.Data());
return 1;
}

