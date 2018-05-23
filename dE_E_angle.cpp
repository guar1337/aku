#include "dE_E_angle.h"

ClassImp(dE_E_angle);
using namespace std;

dE_E_angle::dE_E_angle()
{
	create_input_tree(NULL);
	create_output_tree(NULL);
}

dE_E_angle::dE_E_angle(TTree *inT, TTree *outT)
{
	create_input_tree(inT);
	create_output_tree(outT);

	int s_Nel=1;
	si_A[0]=28;
	si_Z[0]=14;
	si_W[0]=1;

	Si_Ecalc = new ELC(6,2,s_Nel,2.35,
					 si_A, si_Z, si_W,
					 1000.,1500);
	maynard = new TOOL();

	TRotation beam_setting_array;
}

dE_E_angle::~dE_E_angle()
{
	delete Si_Ecalc;
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

	inTree->SetBranchAddress("x1",	 in_x1);
	inTree->SetBranchAddress("y1",	 in_y1);
	inTree->SetBranchAddress("x2",	 in_x2);
	inTree->SetBranchAddress("y2",	 in_y2);

	inTree->SetBranchAddress("trigger",	 &in_trigger);
	inTree->SetBranchAddress("T",	 &in_T);
	inTree->SetBranchAddress("tof",	 &in_tof);

 	return true;
}

bool dE_E_angle::create_output_tree(TTree *out)
{
	outTree=out;
	
	LV_6He = new TLorentzVector();
	LV_2H = new TLorentzVector();
	LV_Tar = new TLorentzVector();
	LV_beam = new TLorentzVector();
	LV_ghost = new TLorentzVector();
	
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
	outTree->Branch("sqlde",		&sqlde,		 "sqlde/D");
	outTree->Branch("sqletot",	&sqletot,	 "sqletot/D");
	outTree->Branch("sqlang",	&sqlang,	 "sqlang/D");
	outTree->Branch("sqltime",	&sqltime,	 "sqltime/D");

	outTree->Branch("rx",	&rx,	 "rx/F");
	outTree->Branch("ry",	&ry,	 "ry/F");
	outTree->Branch("ry",	&ry,	 "ry/F");
	outTree->Branch("ene_2Hth", &ene_2Hth, "ene_2Hth/F");

	outTree->Branch("lx",	&lx,	 "lx/F");
	outTree->Branch("ly",	&ly,	 "ly/F");
	outTree->Branch("lz",	&lz,	 "lz/F");

	outTree->Branch("X2H",	&X2H,	 "X2H/F");
	outTree->Branch("Y2H",	&Y2H,	 "Y2H/F");
	outTree->Branch("Z2H",	&Z2H,	 "Z2H/F");

	outTree->Branch("X6He",	&X6He,	 "X6He/F");
	outTree->Branch("Y6He",	&Y6He,	 "Y6He/F");
	outTree->Branch("Z6He",	&Z6He,	 "Z6He/F");

	outTree->Branch("evX",	&evX,	 "evX/F");
	outTree->Branch("evY",	&evY,	 "evY/F");
	outTree->Branch("evZ",	&evZ,	 "evZ/F");
	outTree->Branch("mwpc",	&mwpc,	 "mwpc/B");
	outTree->Branch("ms",	&ms,	 "ms/B");
	outTree->Branch("tar",	&tar,	 "tar/B");

	outTree->Branch("sqrtheta",	 &sqrtheta,	"sqrtheta/D");
	outTree->Branch("sqrtheta2",	 &sqrtheta2,	"sqrtheta2/D");
	outTree->Branch("sqrphi",	 &sqrphi,		"sqrphi/D");
	outTree->Branch("sqrde",		&sqrde,		 "sqrde/D");
	outTree->Branch("sqretot",	&sqretot,	 "sqretot/D");
	outTree->Branch("sqrang",	&sqrang,	 "sqrang/D");
	outTree->Branch("sqrtime",	&sqrtime,	 "sqrtime/D");

	outTree->Branch("sqrtheo",	&sqrtheo,	 "sqrtheo/D");
	outTree->Branch("sqltheo",	&sqltheo,	 "sqltheo/D");

	outTree->Branch("tF3",	out_tF3,	 "tF3[4]/D");
	outTree->Branch("F3",	 out_F3,		"F3[4]/D");
	outTree->Branch("tF5",	out_tF5,	 "tF5[4]/D");
	outTree->Branch("F5",	 out_F5,		"F5[4]/D");
	outTree->Branch("tF6",	out_tF6,	 "tF6[4]/D");
	outTree->Branch("F6",	 out_F6,		"F6[4]/D");


	outTree->Branch("tof",	&out_tof,		 "tof/D");
	outTree->Branch("T",	&out_T,		 "T/D");

	outTree->Branch("x1",	out_x1,	"x1[32]/s");
	outTree->Branch("x2",	out_x2,	"x2[32]/s");
	outTree->Branch("y1",	out_y1,	"y1[32]/s");
	outTree->Branch("y2",	out_y2,	"y2[32]/s");

	outTree->Branch("nx1",	&out_nx1,	"nx1/s");
	outTree->Branch("nx2",	&out_nx2,	"nx2/s");
	outTree->Branch("ny1",	&out_ny1,	"ny1/s");
	outTree->Branch("ny2",	&out_ny2,	"ny2/s");
	outTree->Branch("trigger",	&out_trigger,	"trigger/S");
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
	outTree->Bronch("LV_Tar.",	"TLorentzVector",	&LV_Tar);
	outTree->Bronch("LV_beam.",	"TLorentzVector",	&LV_beam);
	return true;
}

void dE_E_angle::actual_work()
{
	Long64_t nEntries = inTree->GetEntries();
	maynard->initializeGeometry(&SQR_ang, &SQL_ang, &SQR_dist, &SQL_dist, &tar_angle);

	printf("##############################################################################\n");
	printf("#	Loaded file %s has %lli entries. \n#	Processing...\n", s::inFname.Data(), nEntries);

	TVector3 zx(0.0,1.0,0.0);
	TVector3 v_beam(0.0,0.0,1.0);
	TVector3 v_tar(0.0, 0.0, 0.0);
	TRandom3 *rnd = new TRandom3();
	LV_Tar->SetVectM(v_tar,s::mass_2H);
	LV_ghost->SetVectM(v_beam,s::mass_2H);

for (Long64_t entry=0; entry<nEntries; entry++)
	{
	inTree->GetEntry(entry);

	if( entry % ( nEntries / 100 ) == 0)
		{
			printf("# Progress: %i %%\n", counter);
			counter++;
		}
	//NULLing everything
		evX=0.0;evY=0.0;evZ=0.0;
		mwpc=false;
		ms=false;
		tar=false;

		X6He=0.0;
		Y6He=0.0;
		Z6He=0.0;

		X2H=0.0;
		Y2H=0.0;
		Z2H=0.0;

		sqrphi=0.0;
		sqlphi=0.0;		
		sqrtheta=0.0;
		sqltheta=0.0;
		sqrang=0.0;
		sqlang=0.0;
		sqrde=0.0;
		sqlde=0.0;
		sqretot=0.0;		
		sqletot=0.0;

		SQX_L_mult=0;
		SQY_L_mult=0;
		CsI_L_mult=0;

		SQX_R_mult=0;
		SQY_R_mult=0;
		CsI_R_mult=0;

		maynard->null_energy(	SQX_L_Edep,SQY_L_Edep,CsI_L_Edep,
								SQX_R_Edep,SQY_R_Edep,CsI_R_Edep);

		maynard->null_strips(	SQX_L_strip, SQY_L_strip, CsI_L_strip,
								SQX_R_strip,SQY_R_strip,CsI_R_strip);
	
	//1 channel loop
	out_nx1=in_nx1;
	out_nx2=in_nx2;
	out_ny1=in_ny1;
	out_ny2=in_ny2;
	out_trigger=in_trigger;
	out_tof = in_tof;
	//MWPC, ToF total energy loss is equal to 347.15 mkm of Si
	in_tof>0.0 ? T = maynard->getT(in_tof, s::mass_6He) : T=0.0; 
	out_T = Si_Ecalc->GetE(T, 347.15);

	//4 channels loop
	for (int iii=0; iii<4; iii++)
	{
		out_tF3[iii]=in_tF3[iii];
		out_F3[iii]=in_F3[iii];
		out_tF5[iii]=in_tF5[iii];
		out_F5[iii]=in_F5[iii];
		out_tF6[iii]=in_tF6[iii];
		out_F6[iii]=in_F6[iii];
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

		if (in_tCsI_L[iii]>s::tc_CsI_L)
		{
			CsI_L_mult++;
			CsI_L_Edep[CsI_L_mult]=CsI_L[iii];
			CsI_L_strip[CsI_L_mult]=iii;
		}


		if (in_tSQY_R[iii]>s::tc_SQY_R)
		{
			SQY_R_mult++;
			SQY_R_Edep[SQY_R_mult]=SQY_R[iii];
			SQY_R_strip[SQY_R_mult]=iii;
		}

		if (in_tCsI_R[iii]>s::tc_CsI_R)
		{
			CsI_R_mult++;
			CsI_R_Edep[CsI_R_mult]=CsI_R[iii];
			CsI_R_strip[CsI_R_mult]=iii;
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
		MWPC_1_X += rnd->Uniform(0.0,1.0)-0.5;
		MWPC_1_Y += rnd->Uniform(0.0,1.0)-0.5;
		MWPC_1_Z = -816.0;

		MWPC_2_X += rnd->Uniform(0.0,1.0)-0.5;
		MWPC_2_Y += rnd->Uniform(0.0,1.0)-0.5;
		MWPC_2_Z = -270.0;

		dX=MWPC_2_X-MWPC_1_X;
		dY=MWPC_2_Y-MWPC_1_Y;
		dZ=MWPC_2_Z-MWPC_1_Z;
		
		v_beam.SetXYZ(dX,dY,dZ);
		//rotation matrix that will convert 2H or 6He particle so that they will see beam as Z axis
		beam_setting_array.SetZAxis(v_beam.Unit(),zx);
		beam_setting_array.Invert();

		v_beam.Transform(beam_setting_array);
		ene_beam = s::mass_6He + out_T;
		mom_beam = sqrt(ene_beam*ene_beam - s::mass_6He*s::mass_6He);
		v_beam.SetMag(mom_beam);
		
		LV_beam->SetVectM(v_beam, s::mass_6He);
		Tcoef=(cos(tar_angle)*s::tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);
		XZsum= - sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z;

		evX = MWPC_1_X + dX*Tcoef;
		evY = MWPC_1_Y + dY*Tcoef;
		evZ = MWPC_1_Z + dZ*Tcoef;
		if (evZ>-12.0 && evZ<10 && evX>-12.0 && evX<20)
		{
			tar=true;
		}
	}

	//SQL energy - deuterium
	if (SQX_L_mult*SQY_L_mult==1 && mwpc)
	{
		//printf("\n\n# Entry No: %i %%\n", entry);
		sqlde=SQX_L_Edep[1];
		sqletot=CsI_L[  (SQY_L_strip[1]/4)*4  +  (3-SQX_L_strip[1]/8)];
		sqltime=out_tSQX_L[1];

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
		vect2H.Transform(beam_setting_array);
		ene_2H = sqlde + s::mass_2H;
		mom_2H = sqrt(ene_2H*ene_2H-s::mass_2H*s::mass_2H);
		vect2H.SetMag(mom_2H);

		LV_2H->SetVectM(vect2H, s::mass_2H);
		*LV_6He = *LV_Tar + *LV_beam - *LV_2H;
		missMass = LV_6He->M() - s::mass_6He;

		//setting LAB angles of scattered deuterium - reference is beam vector
		sqlphi=vect2H.Phi()*s::rad_to_deg;
		sqltheta=vect2H.Theta()*s::rad_to_deg;


		TVector3 vectBoost((*LV_beam + *LV_ghost).BoostVector());
		LV_ghost->Boost(-vectBoost);
		LV_ghost->SetTheta((TMath::Pi()-vect2H.Theta())*2.0);
		LV_ghost->Boost(vectBoost);
		ene_2Hth = LV_ghost->E() - s::mass_2H;
		*LV_ghost = *LV_Tar;
	}

	//SQR energy - helium
	if(SQX_R_mult*SQY_R_mult==1 && mwpc)
	{		
		sqrde=SQY_R_Edep[1];
		sqretot=CsI_R[    4*(SQY_R_strip[1]/4)+   ((SQX_R_strip[1]/8))    ];
		sqrtime=out_tCsI_R[    4*(3-SQY_R_strip[1]/4)+   (SQX_R_strip[1]/4)    ];
		

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

		//setting LAB angles of scattered 6 He - reference is beam vector
		vect6He=beam_setting_array*vect6He;
		sqrtheta=vect6He.Theta()*s::rad_to_deg;
		sqrphi=vect6He.Phi()*s::rad_to_deg;
	}

	outTree->Fill();


}
TString outFname(s::inFname.Copy().ReplaceAll("_cal.root","").Append("_dE_work.root").Data());
printf("#	Creating file: %s with tree named \"dE_E\" \n",outFname.Data());
printf("#	Goodbye ;)\n");
}

