#include "TFile.h"
#include "stdio.h"
#include "Riostream.h"
#include "dE_E_angle.h"
#include <iostream>
#include "interface.h"
#include "TRandom3.h"

ClassImp(dE_E_angle);

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

	si_elo = new ELC(6,2,s_Nel,2.35,
					 si_A, si_Z, si_W,
					 500.,1000);
}

dE_E_angle::~dE_E_angle()
{
	delete si_elo;
}

bool dE_E_angle::create_input_tree(TTree *in)
{
	inTree=in;
	inTree->SetMakeClass(1);
	inTree->SetBranchAddress("CsI_L",	CsI_L);
	inTree->SetBranchAddress("CsI_R",	CsI_R);
	inTree->SetBranchAddress("SQX_L",	SQX_L);
	inTree->SetBranchAddress("SQX_R",	SQX_R);
	inTree->SetBranchAddress("tSQX_L",	in_tSQX_L);
	inTree->SetBranchAddress("tSQX_R",	in_tSQX_R);
	inTree->SetBranchAddress("SQY_L",	SQY_L);
	inTree->SetBranchAddress("SQY_R",	SQY_R);

	inTree->SetBranchAddress("tF3",		 in_tF3);
	inTree->SetBranchAddress("F3",		in_F3);
	inTree->SetBranchAddress("tF5",		 in_tF5);
	inTree->SetBranchAddress("F5",		in_F5);

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
	lv6he = new TLorentzVector();
	lv2h = new TLorentzVector();
	lvTar = new TLorentzVector();
	lvbeam = new TLorentzVector();
	outTree->SetMakeClass(1);
	outTree->Branch("SQX_L_m",	 &SQX_L_mult,	"SQX_L_m/S");
	outTree->Branch("SQX_R_m",	 &SQX_R_mult,	"SQX_R_m/S");
	outTree->Branch("SQY_L_m",	 &SQY_L_mult,	"SQY_L_m/S");
	outTree->Branch("SQY_R_m",	 &SQY_R_mult,	"SQY_R_m/S");
	outTree->Branch("CsI_L_m",	 &CsI_L_mult,	"CsI_L_m/S");
	outTree->Branch("CsI_R_m",	 &CsI_R_mult,	"CsI_R_m/S");

	outTree->Branch("SQX_L_e",	 SQX_L_Edep,	 "SQX_L_e[16]/D");
	outTree->Branch("SQX_R_e",	 SQX_R_Edep,	 "SQX_R_e[16]/D");

	//outTree->Branch("tSQX_L",	 out_tSQX_L,	 "tSQX_L[16]/D");
	//outTree->Branch("tSQX_R",	 out_tSQX_R,	 "tSQX_R[16]/D");

	outTree->Branch("SQY_L_e",	SQY_L_Edep,	 "SQY_L_e[16]/D");
	outTree->Branch("SQY_R_e",	SQY_R_Edep,	 "SQY_R_e[16]/D");
	outTree->Branch("CsI_L_e",	CsI_L_Edep,	 "CsI_L_e[16]/D");
	outTree->Branch("CsI_R_e",	CsI_R_Edep,	 "CsI_R_e[16]/D");

	outTree->Branch("SQX_L_s",	SQX_L_strip,	"SQX_L_s[16]/S");
	outTree->Branch("SQX_R_s",	SQX_R_strip,	"SQX_R_s[16]/S");
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

	outTree->Branch("sqrtheta",	 &sqrtheta,	"sqrtheta/D");
	outTree->Branch("sqrphi",	 &sqrphi,		"sqrphi/D");
	outTree->Branch("sqrde",		&sqrde,		 "sqrde/D");
	outTree->Branch("sqretot",	&sqretot,	 "sqretot/D");
	outTree->Branch("sqrang",	&sqrang,	 "sqrang/D");
	outTree->Branch("sqrtime",	&sqrtime,	 "sqrtime/D");

	outTree->Branch("tF3",	in_tF3,	 "tF3[4]/D");
	outTree->Branch("F3",	 in_F3,		"F3[4]/D");
	outTree->Branch("tF5",	in_tF5,	 "tF5[4]/D");
	outTree->Branch("F5",	 in_F5,		"F5[4]/D");
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

	outTree->Branch("c_SQX_L",	 c_SQX_L,	 "c_SQX_L[16]/D");
	outTree->Branch("c_SQX_R",	 c_SQX_R,	 "c_SQX_R[16]/D");
	outTree->Branch("c_SQY_L",	 c_SQY_L,	 "c_SQY_L[16]/D");
	outTree->Branch("c_SQY_R",	 c_SQY_R,	 "c_SQY_R[16]/D");
	outTree->Branch("c_CsI_L",	 c_CsI_L,	 "c_CsI_L[16]/D");
	outTree->Branch("c_CsI_R",	 c_CsI_R,	 "c_CsI_R[16]/D");

	outTree->Bronch("lv6he.",		"TLorentzVector",	&lv6he);
	outTree->Bronch("lv2h.",		"TLorentzVector",	&lv2h);
	outTree->Bronch("lvTar.",	"TLorentzVector",	&lvTar);
	outTree->Bronch("lvbeam.",	"TLorentzVector",	&lvbeam);
	return true;
}

void dE_E_angle::null_strips(	UShort_t *SQX_L,UShort_t *SQY_L,UShort_t *CsI_L,
				 				UShort_t *SQX_R,UShort_t *SQY_R,UShort_t *CsI_R)
{
	fill(SQX_L,SQX_L+16,16);
	fill(SQY_L,SQY_L+16,16);
	fill(CsI_L,CsI_L+16,16);
	fill(SQX_R,SQX_R+16,16);
	fill(SQY_R,SQY_R+16,16);
	fill(CsI_R,CsI_R+16,16);
}

void dE_E_angle::null_calib_data(Double_t*SQX_L, Double_t*SQY_L, Double_t*CsI_L,
								 Double_t*SQX_R, Double_t*SQY_R, Double_t*CsI_R)
{
	fill(SQX_L,SQX_L+16,0.0);
	fill(SQY_L,SQY_L+16,0.0);
	fill(CsI_L,CsI_L+16,0.0);
	fill(SQX_R,SQX_R+16,0.0);
	fill(SQY_R,SQY_R+16,0.0);
	fill(CsI_R,CsI_R+16,0.0);
}

void dE_E_angle::null_energy( Double_t*SQX_L, Double_t*SQY_L, Double_t*CsI_L,
				Double_t*SQX_R, Double_t*SQY_R, Double_t*CsI_R)
{
	fill(SQX_L,SQX_L+16,0.);
	fill(SQY_L,SQY_L+16,0.);
	fill(CsI_L,CsI_L+16,0.);
	fill(SQX_R,SQX_R+16,0.);
	fill(SQY_R,SQY_R+16,0.);
	fill(CsI_R,CsI_R+16,0.); 
}

void dE_E_angle::null_MWPC(UShort_t *x1, UShort_t *x2, UShort_t *y1, UShort_t *y2 )
{
	fill(x1,x1+32,0);
	fill(x2,x2+32,0);
	fill(y1,y1+32,0);
	fill(y2,y2+32,0);
}

Double_t dE_E_angle::getT(Double_t tof, Double_t mass)
{
	beta_squared= pow((s::tofBase/tof)/s::c, 2.0);
	gamma=1.0/sqrt(1.0-beta_squared);
	return mass*s::u_to_MeV*(gamma-1.0);
}

void dE_E_angle::actual_work() 
{

	TVector3 zx(0.0,1.0,0.0);
	TVector3 v_beam(0.0,0.0,1.0);
	TRotation beam_setting_array;
	TRandom3 *rnd = new TRandom3();
	lvTar->SetPxPyPzE(0.0,0.0,0.0,s::H2_mass);
	int runNo = s::runNo;

	//Read detectors geometry parameters depending on run
	switch (runNo)
	{
		case 7:
		printf("Loaded exprimental setup parameters for run 7\n");
		sqr_ang=s::sqr_ang7;
		sql_ang=s::sql_ang7;

		sqr_dist=s::sqr_dist;
		sql_dist=s::sql_dist;
		break;

		case 9:
		printf("Loaded exprimental setup parameters for run 9\n");
		sqr_ang=s::sqr_ang9;
		sql_ang=s::sql_ang9;
		
		sqr_dist=s::sqr_dist;
		sql_dist=s::sql_dist;
		break;

		default:
		printf("Error: NO EXPERIMENTAL SETUP PARAMETERS\n");
		break;
	}


Long64_t nEntries = inTree->GetEntries();
printf("##############################################################################\n");
printf("#	Loaded file %s has %lli entries. \n#	Processing...\n", s::inFname.Data(), nEntries);

for (Long64_t entry=0; entry<nEntries; entry++)
{
	inTree->GetEntry(entry);
	
	if( entry % ( nEntries / 20 ) == 0)
	{
		cout<<"#	Progress: "<<static_cast<int>(ceil((entry * 100)/ nEntries))<<" %"<<endl;
	}

	//NULLing everything
	
		dX=0.0;dY=0.0;dZ=0.0;
		evX=0.0;evY=0.0;evZ=0.0;
		mwpc=false;

		SQX_L_mult=0;
		SQY_L_mult=0;
		CsI_L_mult=0;

		SQX_R_mult=0;
		SQY_R_mult=0;
		CsI_R_mult=0;

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
		sqlang=0.0;

		sqlde=0.0;
		sqletot=0.0;
		sqrde=0.0;
		sqretot=0.0;
		sqrang=0.0;
	

	null_strips(SQX_L_strip,SQY_L_strip,CsI_L_strip,
				SQX_R_strip,SQY_R_strip,CsI_R_strip);

	null_calib_data(c_SQX_L,c_SQY_L,c_CsI_L,
						c_SQX_R,c_SQY_R,c_CsI_R);

	null_energy(SQX_L_Edep,SQY_L_Edep,CsI_L_Edep,
				SQX_R_Edep,SQY_R_Edep,CsI_R_Edep);

	null_MWPC(out_x1, out_x2, out_y1, out_y2);
	
	//1 channel loop
	out_nx1=in_nx1;
	out_nx2=in_nx2;
	out_ny1=in_ny1;
	out_ny2=in_ny2;
	out_trigger=in_trigger;
	out_tof = in_tof;

	T = getT(in_tof, s::He6_mass);
	T = si_elo->GetE(T, 252.48);




	//4 channels loop
	for (int iii=0; iii<4; iii++)
	{
		out_tF3[iii]=in_tF3[iii];
		out_F3[iii]=in_F3[iii];
		out_tF5[iii]=in_tF5[iii];
		out_F5[iii]=in_F5[iii];
	}

	//16 channels loop
	for (int iii=0; iii<16; iii++)
	{
		if (SQX_L[iii]>3.5)
		{
			SQX_L_mult++;
			SQX_L_Edep[SQX_L_mult]=SQX_L[iii];
			SQX_L_strip[SQX_L_mult]=iii;
			out_tSQX_L[SQX_L_mult]=in_tSQX_L[iii];
		}

		if (SQY_L[iii]>3.5)
		{
			SQY_L_mult++;
			SQY_L_Edep[SQY_L_mult]=SQY_L[iii];
			SQY_L_strip[SQY_L_mult]=iii;
		}

		if (CsI_L[iii]>4.5)
		{
			CsI_L_mult++;
			CsI_L_Edep[CsI_L_mult]=CsI_L[iii];
			CsI_L_strip[CsI_L_mult]=iii;
		}

		if (SQX_R[iii]>5.0)
		{
			SQX_R_mult++;
			SQX_R_Edep[SQX_R_mult]=SQX_R[iii];
			SQX_R_strip[SQX_R_mult]=iii;
			out_tSQX_R[SQX_R_mult]=in_tSQX_R[iii];
		}

		if (SQY_R[iii]>5.0)
		{
			SQY_R_mult++;
			SQY_R_Edep[SQY_R_mult]=SQY_R[iii];
			SQY_R_strip[SQY_R_mult]=iii;
		}

		if (CsI_R[iii]>15.0)
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
	}

	//32 channels loop
	for (int iii=0; iii<32; iii++)
	{
		out_x1[iii]=in_x1[iii];
		out_x2[iii]=in_x2[iii];
		out_y1[iii]=in_y1[iii];
		out_y2[iii]=in_y2[iii];
	}

	//MWPC
	if(out_nx1*out_ny1*out_nx2*out_ny2!=0)
	{
		//displacement + go to corner of MWPC + follow wire order - get event point
		mwpc=true;
		MWPC_1_X=(-1.0) + (15.5*1.25)-(out_x1[0]+rnd->Uniform(0.0,1.0)-0.5)*1.25;
		MWPC_1_Y=(-2.5) + (-15.5*1.25)+(out_y1[0]+rnd->Uniform(0.0,1.0)-0.5)*1.25;
		MWPC_1_Z=-816.0;

		MWPC_2_X=(-1.5) + (15.5*1.25)-(out_x2[0]+rnd->Uniform(0.0,1.0)-0.5)*1.25;
		MWPC_2_Y=(-1.0) + (-15.5*1.25)+(out_y2[0]+rnd->Uniform(0.0,1.0)-0.5)*1.25;
		MWPC_2_Z=-270.0;


		dX=MWPC_2_X-MWPC_1_X;
		dY=MWPC_2_Y-MWPC_1_Y;
		dZ=MWPC_2_Z-MWPC_1_Z;

		v_beam.SetXYZ(dX,dY,dZ);
		He6_E = s::He6_mass + out_T;
		He6_Mom = sqrt(He6_E*He6_E-s::He6_mass*s::He6_mass);
		v_beam.SetMag(He6_Mom);
		lvbeam->SetVectM(v_beam,s::He6_mass);

		switch (runNo)
		{
			case 7:
			//for target at 45 deg
			XZsum=-MWPC_1_X-MWPC_1_Z;
			evX=MWPC_1_X+(XZsum*dX)/(dX+dZ);
			evY=MWPC_1_Y+(XZsum*dY)/(dX+dZ);
			evZ=MWPC_1_Z+(XZsum*dZ)/(dX+dZ);
			break;

			case 9:
			//for target at 0 deg
			XZsum=-MWPC_1_Z;
			evX=MWPC_1_X+(XZsum*dX)/(dZ);
			evY=MWPC_1_Y+(XZsum*dY)/(dZ);
			evZ=MWPC_1_Z+(XZsum*dZ)/(dZ);
			break;
		}


		//rotation matrix that will convert 2H or 6He particle so that they will see beam as Z axis
		beam_setting_array.SetZAxis(v_beam.Unit(),zx);
		beam_setting_array.Invert();
	}
	
	//SQL energy - deuterium
	if (SQX_L_mult*SQY_L_mult*mwpc==1)
	{
		sqlde=SQX_L_Edep[1];
		sqletot=CsI_L[  (SQY_L_strip[1]/4)*4  +  (3-SQX_L_strip[1]%4)];
		sqltime=out_tSQX_L[1];

		X2H=sql_dist*sin(sql_ang) + (30.0-4.*(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5)) * cos(sql_ang);
		Y2H=-30.+4.* (SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
		Z2H=sql_dist*cos(sql_ang) - (30.-4.*(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5)) * sin(sql_ang);

		TVector3 vect2H(X2H-evX, Y2H-evY, Z2H-evZ);
		H2_E = s::H2_mass+sqlde+sqletot;
		H2_Mom = sqrt(H2_E*H2_E-s::H2_mass*s::H2_mass);
		vect2H.SetMag(H2_Mom);
		lv2h->SetVectM(vect2H,s::H2_mass);
		vect2H=beam_setting_array*vect2H; 

		sqlphi=vect2H.Phi()*s::rad_to_deg;
		sqltheta=vect2H.Theta()*s::rad_to_deg;		

	}

	//SQR energy - helium
	if(SQX_R_mult*SQY_R_mult*mwpc==1)
	{
		sqrde=SQX_R_Edep[1];
		sqretot=CsI_R[    4*(3-SQY_R_strip[1]/4)+   (3-(SQX_R_strip[1]/4))    ];
		sqrtime=out_tSQX_R[1];


		X6He=-sqr_dist*sin(sqr_ang)+(30.-4.*(SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5))*cos(sqr_ang);
		Y6He=30.-4.*(SQY_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
		Z6He=sqr_dist*cos(sqr_ang)+(30.-4.*(SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5))*sin(sqr_ang);

		TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
		lv6he->SetVectMag(vect6He,s::He6_mass);
		vect6He=beam_setting_array*vect6He;

		sqrtheta=vect6He.Theta()*s::rad_to_deg;
		sqrphi=vect6He.Phi()*s::rad_to_deg;

	}

	*lv6he=(*lvTar+*lvbeam)-*lv2h;
	missMass=lv6he->M()- s::He6_mass;


	outTree->Fill();
}

printf("#	Creating file: %s with tree named \"dE_E\" \n",s::inFname.Copy().ReplaceAll("_cal","").Data());
printf("#	Goodbye ;)");
}