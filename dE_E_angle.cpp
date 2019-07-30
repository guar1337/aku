#include "dE_E_angle.h"

ClassImp(dE_E_angle);
using namespace std;

dE_E_angle::dE_E_angle()
{
	create_input_tree(NULL);
	create_output_tree(NULL);
}

dE_E_angle::dE_E_angle(TTree *inT, TTree *outT, TString inFile, int geoNo)
{
	create_input_tree(inT);
	create_output_tree(outT);
/*	
	outTree=outT;
	
	LV_6He = new TLorentzVector();
	LV_1H = new TLorentzVector();
	LV_2H = new TLorentzVector();

	LV_tar_1H = new TLorentzVector();
	LV_tar_2H = new TLorentzVector();
	LV_beam = new TLorentzVector();
*/	maynard = new TOOL();
	s_curFile = inFile;


	vBeam = new TVector3(0.0,0.0,1.0);
	vTarget = new TVector3(0.0, 0.0, 0.0);

	int si_Nel=1;
	si_A[0]=28;
	si_Z[0]=14;
	si_W[0]=1;

	int csi_Nel=2;
	csi_A[0]=126.90447;
	csi_Z[0]=53;
	csi_W[0]=1;

	csi_A[1]=132.905452;
	csi_Z[1]=55;
	csi_W[1]=1;

	int CD2_Nel=2;
	CD2_A[0]=2;
	CD2_Z[0]=1;
	CD2_W[0]=2;

	CD2_A[1]=12;
	CD2_Z[1]=6;
	CD2_W[1]=1;

	int BoPET_Nel=3;
	BoPET_A[0]=1;
	BoPET_Z[0]=1;
	BoPET_W[0]=8;

	BoPET_A[1]=12;
	BoPET_Z[1]=6;
	BoPET_W[1]=10;

	BoPET_A[2]=16;
	BoPET_Z[2]=8;
	BoPET_W[2]=4;

	h2_Si 		= new ELC(2, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
	h2_CsI 		= new ELC(2, 1, csi_Nel, 4.51, si_A, si_Z, csi_W, 100.,1500);
	h2_BoPET	= new ELC(2, 1, BoPET_Nel, 1.4, BoPET_A, BoPET_Z, BoPET_W, 100.,1500);
	h2_CD2		= new ELC(2, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);

	h1_Si 		= new ELC(1, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
	h1_CsI 		= new ELC(1, 1, csi_Nel, 4.51, si_A, si_Z, csi_W, 100.,1500);
	h1_BoPET	= new ELC(1, 1, BoPET_Nel, 1.4, BoPET_A, BoPET_Z, BoPET_W, 100.,1500);
	h1_CD2		= new ELC(1, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);

	he6_Si 		= new ELC(6, 2, si_Nel, 2.35, si_A, si_Z, si_W, 300.,1500);
	he6_CD2		= new ELC(6, 2, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 200.,1500);
	he6_BoPET	= new ELC(6, 2, BoPET_Nel, 1.4, BoPET_A, BoPET_Z, BoPET_W, 200.,1500);
	he6_CsI 	= new ELC(6, 2, csi_Nel, 4.51, csi_A, csi_Z, csi_W, 300.,1500);


	//Change all the graphical cuts geometry from number to variable 
	gcut_he6 = new TCutG("He6",maynard->gcut_noPoints(s_curFile, "he6.dat", cs::runNo), &in_tof, &in_aF5);
	maynard->gcuts_loader(s_curFile, gcut_he6, "he6.dat", geoNo);

	gcut_dehe6 = new TCutG("dehe6", maynard->gcut_noPoints(s_curFile, "dehe6.dat", cs::runNo),
							&sqretot, &sqrde);
	maynard->gcuts_loader(s_curFile, gcut_dehe6, "dehe6.dat", geoNo);

	gcut_AngAng1H_w6He = new TCutG("gcut_AngAng1H_w6He", maynard->gcut_noPoints(s_curFile,
									 "AngAng1H_w6He.dat", cs::runNo), &sqrang, &sqlang);
	maynard->gcuts_loader(s_curFile, gcut_AngAng1H_w6He, "AngAng1H_w6He.dat", geoNo);

	gcut_AngAng2H_w6He = new TCutG("gcut_AngAng2H_w6He", maynard->gcut_noPoints(s_curFile,
									 "AngAng2H_w6He.dat", cs::runNo), &sqrang, &sqlang);
	maynard->gcuts_loader(s_curFile, gcut_AngAng2H_w6He, "AngAng2H_w6He.dat", geoNo);


	deut_geo5 = new TCutG("deut_geo5",maynard->gcut_noPoints(s_curFile, "deut_geo5.dat", cs::runNo), &in_tof, &in_aF5);
	maynard->gcuts_loader(s_curFile, deut_geo5, "deut_geo5.dat", geoNo);

	rnd = new TRandom3();

	ToFMWPC = 644.0;
	gasTargetSi = 21.0;

}

dE_E_angle::~dE_E_angle()
{
	delete h2_Si;
	delete h2_CsI;
	delete h2_BoPET;
	delete h2_CD2;

	delete he6_Si;
	delete he6_CsI;
	delete he6_BoPET;
	delete he6_CD2;

	delete maynard;

	delete rnd;
}

bool dE_E_angle::create_input_tree(TTree *in)
{
	inTree=in;
	inTree->SetMakeClass(1);
	//CALIBRATED DATA
	inTree->SetBranchAddress("CsI_L",	CsI_L);
	inTree->SetBranchAddress("CsI_0L",	CsI_0L);
	inTree->SetBranchAddress("CsI_R",	CsI_R);
	inTree->SetBranchAddress("SQX_L",	SQX_L);
	inTree->SetBranchAddress("SQX_Ln",	SQX_Ln);
	inTree->SetBranchAddress("SQX_R",	SQX_R);
	inTree->SetBranchAddress("SQY_L",	SQY_L);
	inTree->SetBranchAddress("SQY_R",	SQY_R);
	
	//RAW DATA
	inTree->SetBranchAddress("r_CsI_L",	r_CsI_L);
	inTree->SetBranchAddress("r_CsI_R",	r_CsI_R);
	inTree->SetBranchAddress("r_SQX_L",	r_SQX_L);
	inTree->SetBranchAddress("r_SQX_R",	r_SQX_R);
	inTree->SetBranchAddress("r_SQY_L",	r_SQY_L);


	//inTree->SetBranchAddress("SQ300",	SQ300);
	//inTree->SetBranchAddress("r_SQY_R",	r_SQY_R);
	//inTree->SetBranchAddress("r_SQ300",	r_SQ300);
	//inTree->SetBranchAddress("tSQ300",	in_tSQ300);

	//TIME
	inTree->SetBranchAddress("tSQX_L",	in_tSQX_L);
	inTree->SetBranchAddress("tSQX_R",	in_tSQX_R);
	inTree->SetBranchAddress("tCsI_L",	in_tCsI_L);
	inTree->SetBranchAddress("tCsI_R",	in_tCsI_R);
	inTree->SetBranchAddress("tSQY_L",	in_tSQY_L);
	inTree->SetBranchAddress("tSQY_R",	in_tSQY_R);
	

	inTree->SetBranchAddress("tF3",		in_tF3);
	inTree->SetBranchAddress("F3",		in_F3);
	inTree->SetBranchAddress("tF5",		in_tF5);
	inTree->SetBranchAddress("F5",		in_F5);
	inTree->SetBranchAddress("tF6",		in_tF6);
	inTree->SetBranchAddress("F6",		in_F6);

	inTree->SetBranchAddress("nx1",		&in_nx1);
	inTree->SetBranchAddress("ny1",		&in_ny1);
	inTree->SetBranchAddress("nx2",		&in_nx2);
	inTree->SetBranchAddress("ny2",		&in_ny2);

	inTree->SetBranchAddress("tMWPC",	in_tMWPC);

	inTree->SetBranchAddress("x1",		in_x1);
	inTree->SetBranchAddress("y1",		in_y1);
	inTree->SetBranchAddress("x2",		in_x2);
	inTree->SetBranchAddress("y2",		in_y2);

	inTree->SetBranchAddress("trig",	&in_trig);
	inTree->SetBranchAddress("tof",		&in_tof);
	inTree->SetBranchAddress("az",		&in_AZ);
	inTree->SetBranchAddress("aF5",		&in_aF5);
	inTree->SetBranchAddress("run",		&run);


 	return true;
}

bool dE_E_angle::create_output_tree(TTree *out)
{
	outTree=out;
	
	LV_6He = new TLorentzVector();
	LV_1H = new TLorentzVector();
	LV_2H = new TLorentzVector();

	LV_tar_1H = new TLorentzVector();
	LV_tar_2H = new TLorentzVector();
	LV_beam = new TLorentzVector();

	
	outTree->SetMakeClass(1);
	/*
	outTree->Branch("SQX_L_m",	&SQX_L_mult,	"SQX_L_m/S");
	outTree->Branch("SQX_R_m",	&SQX_R_mult,	"SQX_R_m/S");
	outTree->Branch("SQY_L_m",	&SQY_L_mult,	"SQY_L_m/S");
	outTree->Branch("SQY_R_m",	&SQY_R_mult,	"SQY_R_m/S");
	outTree->Branch("CsI_L_m",	&CsI_L_mult,	"CsI_L_m/S");
	outTree->Branch("CsI_R_m",	&CsI_R_mult,	"CsI_R_m/S");

	outTree->Branch("tSQX_L",	out_tSQX_L,		"tSQX_L[32]/D");
	outTree->Branch("tSQX_R",	out_tSQX_R,		"tSQX_R[32]/D");
	outTree->Branch("tSQY_L",	out_tSQY_L,		"tSQY_L[16]/D");
	outTree->Branch("tSQY_R",	out_tSQY_R,		"tSQY_R[16]/D");
	outTree->Branch("tCsI_L",	out_tCsI_L,		"tCsI_L[16]/D");
	outTree->Branch("tCsI_R",	out_tCsI_R,		"tCsI_R[16]/D");

	outTree->Branch("SQY_L_e",	SQY_L_Edep,		"SQY_L_e[16]/D");
	outTree->Branch("SQY_R_e",	SQY_R_Edep,		"SQY_R_e[16]/D");
	outTree->Branch("SQX_L_e",	SQX_L_Edep,		"SQX_L_e[32]/D");
	outTree->Branch("SQX_R_e",	SQX_R_Edep,		"SQX_R_e[32]/D");
	outTree->Branch("CsI_L_e",	CsI_L_Edep,		"CsI_L_e[16]/D");
	outTree->Branch("CsI_R_e",	CsI_R_Edep,		"CsI_R_e[16]/D");

	outTree->Branch("SQX_L_s",	SQX_L_strip,	"SQX_L_s[32]/S");
	outTree->Branch("SQX_R_s",	SQX_R_strip,	"SQX_R_s[32]/S");
	outTree->Branch("SQY_L_s",	SQY_L_strip,	"SQY_L_s[16]/S");
	outTree->Branch("SQY_R_s",	SQY_R_strip,	"SQY_R_s[16]/S");
	outTree->Branch("CsI_L_s",	CsI_L_strip,	"CsI_L_s[16]/S");
	outTree->Branch("CsI_R_s",	CsI_R_strip,	"CsI_R_s[16]/S");
*/
	outTree->Branch("SQX_L_sNo",	&SQX_L_stripNo,	"SQX_L_sNo/F");
	outTree->Branch("SQX_R_sNo",	&SQX_R_stripNo,	"SQX_R_sNo/F");
	outTree->Branch("SQY_L_sNo",	&SQY_L_stripNo,	"SQY_L_sNo/F");
	outTree->Branch("SQY_R_sNo",	&SQY_R_stripNo,	"SQY_R_sNo/F");

	//LEFT
	outTree->Branch("sqlde",		&sqlde,		"sqlde/D");
	outTree->Branch("sqletot",		&sqletot,	"sqletot/D");

	outTree->Branch("sqlphi",		&sqlphi,	"sqlphi/D");
	outTree->Branch("sqltheta",		&sqltheta,	"sqltheta/D");
	
	outTree->Branch("sqlang",		&sqlang,	"sqlang/D");
	outTree->Branch("sqlang1",		&sqlang1,	"sqlang1/D");
	outTree->Branch("sqlang2",		&sqlang2,	"sqlang2/D");
	outTree->Branch("sqlxtime",		&sqlxtime,	"sqlxtime/D");
	outTree->Branch("sqlytime",		&sqlytime,	"sqlytime/D");
	outTree->Branch("fsqltheta_1H",	&fsqltheta_1H,"fsqltheta_1H/D");
	outTree->Branch("fsqltheta_2H",	&fsqltheta_2H,"fsqltheta_2H/D");
	outTree->Branch("kinsqle_1H",	&kinsqle_1H,"kinsqle_1H/D");
	outTree->Branch("kinsqle_2H",	&kinsqle_2H,"kinsqle_2H/D");


	outTree->Branch("sqrde",		&sqrde,		"sqrde/D");
	outTree->Branch("sqretot",		&sqretot,	"sqretot/D");

	outTree->Branch("sqrtheta",		&sqrtheta,	"sqrtheta/D");
	outTree->Branch("sqrphi",		&sqrphi,	"sqrphi/D");
	outTree->Branch("sqrang",		&sqrang,	"sqrang/D");
	outTree->Branch("sqrang1",		&sqrang1,	"sqrang1/D");
	outTree->Branch("sqrang2",		&sqrang2,	"sqrang2/D");
	outTree->Branch("sqrxtime",		&sqrxtime,	"sqrxtime/D");
	outTree->Branch("sqrytime",		&sqrytime,	"sqrytime/D");
	outTree->Branch("fsqrtheta1",	&fsqrtheta1,	"fsqrtheta1/D");
	outTree->Branch("fsqrtheta2",	&fsqrtheta2,	"fsqrtheta2/D");

	outTree->Branch("s_csir",		&memS_CsI_R,	"s_csir/S");
	outTree->Branch("s_csil",		&memS_CsI_L,	"s_csil/S");

	outTree->Branch("X2H",	&X2H,	"X2H/F");
	outTree->Branch("Y2H",	&Y2H,	"Y2H/F");
	outTree->Branch("Z2H",	&Z2H,	"Z2H/F");

	outTree->Branch("X6He",	&X6He,	"X6He/F");
	outTree->Branch("Y6He",	&Y6He,	"Y6He/F");
	outTree->Branch("Z6He",	&Z6He,	"Z6He/F");

	outTree->Branch("evX",	&evX,	"evX/F");
	outTree->Branch("evY",	&evY,	"evY/F");
	outTree->Branch("evZ",	&evZ,	"evZ/F");

	outTree->Branch("dX",	&dX,	"dX/F");
	outTree->Branch("dY",	&dY,	"dY/F");
	outTree->Branch("dZ",	&dZ,	"dZ/F");
/*
	outTree->Branch("f6X",	&f6X,	"f6X/F");
	outTree->Branch("f6Y",	&f6Y,	"f6Y/F");
	outTree->Branch("f6Z",	&f6Z,	"f6Z/F");

	outTree->Branch("f5X",	&f5X,	"f5X/F");
	outTree->Branch("f5Y",	&f5Y,	"f5Y/F");
	outTree->Branch("f5Z",	&f5Z,	"f5Z/F");


	outTree->Branch("tF3",	out_tF3,	"tF3[4]/D");
	outTree->Branch("F3",	out_F3,		"F3[4]/D");
	outTree->Branch("tF5",	out_tF5,	"tF5[4]/D");
	outTree->Branch("F5",	out_F5,		"F5[4]/D");
	outTree->Branch("tF6",	out_tF6,	"tF6[4]/D");
	outTree->Branch("F6",	out_F6,		"F6[4]/D");
*/
	outTree->Branch("tof",	&out_tof,	"tof/D");
	outTree->Branch("aF5",	&out_aF5,	"aF5/D");
	outTree->Branch("az",	&out_AZ,	"az/D");
/*

	outTree->Branch("ion",	&Ion_ID,	"ion/S");
	outTree->Branch("geo",	&Geo_ID,	"geo/S");
	outTree->Branch("run",	&Run_ID,	"run/S");

	outTree->Branch("x1",	out_x1,		"x1[32]/s");
	outTree->Branch("x2",	out_x2,		"x2[32]/s");
	outTree->Branch("y1",	out_y1,		"y1[32]/s");
	outTree->Branch("y2",	out_y2,		"y2[32]/s");

	outTree->Branch("nx1",	&out_nx1,	"nx1/s");
	outTree->Branch("nx2",	&out_nx2,	"nx2/s");
	outTree->Branch("ny1",	&out_ny1,	"ny1/s");
	outTree->Branch("ny2",	&out_ny2,	"ny2/s");

	outTree->Branch("tMWPC",	out_tMWPC,	"tMWPC[4]/F");	
	outTree->Branch("trigger",	&out_trig,	"trigger/S");
	outTree->Branch("mml",	&mml,	"mml/D");

	outTree->Branch("c_SQX_L",	c_SQX_L,	"c_SQX_L[32]/D");
	outTree->Branch("c_SQX_R",	c_SQX_R,	"c_SQX_R[32]/D");
	outTree->Branch("c_SQY_L",	c_SQY_L,	"c_SQY_L[16]/D");
	outTree->Branch("c_SQY_R",	c_SQY_R,	"c_SQY_R[16]/D");
	outTree->Branch("c_CsI_L",	c_CsI_L,	"c_CsI_L[16]/D");
	outTree->Branch("c_CsI_R",	c_CsI_R,	"c_CsI_R[16]/D");

	outTree->Branch("r_SQX_L",	raw_SQX_L,	"r_SQX_L[32]/D");
	outTree->Branch("r_SQX_R",	raw_SQX_R,	"r_SQX_R[32]/D");
	outTree->Branch("r_SQY_L",	raw_SQY_L,	"r_SQY_L[16]/D");
	outTree->Branch("r_SQY_R",	raw_SQY_R,	"r_SQY_R[16]/D");
	outTree->Branch("r_CsI_L",	raw_CsI_L,	"r_CsI_L[16]/D");
	outTree->Branch("r_CsI_R",	raw_CsI_R,	"r_CsI_R[16]/D");
*/
	outTree->Branch("he6",	&he6,	"he6/O");

	outTree->Branch("deu",	&angAng2H,	"deu/O");
	outTree->Branch("pro",	&angAng1H,	"pro/O");
/*
	outTree->Bronch("LV_6He.",	"TLorentzVector",	&LV_6He);
	outTree->Bronch("LV_2H.",	"TLorentzVector",	&LV_2H);
*/
	outTree->Branch("kinE",	&kinE,	"kinE/D");
	outTree->Bronch("LV_beam.",	"TLorentzVector",	&LV_beam);

	return true;
}

Float_t dE_E_angle::actual_work_1H(Double_t inputPars[4], Double_t qualityControl[4])
{
	Int_t geoNo = cs::runNo;

	hist_mml = new TH1F("hist_mml", "blabla", 200, -10.0, 10.0);
	hist_ene_diff = new TH1F("hist_ene_diff", "tit", 200, -15.0, 15.0);

	std::vector<Float_t> vec_lang;
	std::vector<Float_t> vec_rang;
	TF1 *fit;
	Long64_t nEntries = inTree->GetEntries();
	maynard->initializeGeometry(geoNo, &SQR_ang, &SQL_ang, &SQR_dist, &SQL_dist, &tar_angle, &tar_thcknss);

	counter=0;

	for (Long64_t entry=0; entry<nEntries; entry++)
		{

		inTree->GetEntry(entry);
	/*	
		if( entry % ( nEntries / 10 ) == 0)
		{
			printf("# Progress: %i %%\n", counter);
			counter+=10;
		}

	*/		
	SQL_dist += inputPars[1];
		if (run==3)
		{
			tar_pos_Z = cs::tar_pos_Z + 2.0;
			tar_angle = 6.0 * cs::deg_to_rad;
			SQL_ang = (50.0 + inputPars[0]) * cs::deg_to_rad;
			SQR_ang = (15.0 ) * cs::deg_to_rad;
		}

		else
		{
			tar_pos_Z = cs::tar_pos_Z;
			tar_angle = 45.0 * cs::deg_to_rad;
			SQL_ang = (65.0 + inputPars[0]) * cs::deg_to_rad;
			SQR_ang = (15.0) * cs::deg_to_rad;
		}

		//NULLing everything
		LV_tar_1H->SetVectM(*vTarget,cs::mass_1H);
		memE_CsI_R=0.0; memE_CsI_L=0.0; memE_CsI_0L=0.0; memS_CsI_R=20; memS_CsI_L=20;
		kine_2H=0.0, kine_1H=0.0, rest_of_events = 0;
		Ion_ID = 0, Geo_ID = cs::runNo, kinE = 0.0;
		evX=0.0; evY=0.0; evZ=0.0; Run_ID = run;

		he6=false, angAng1H=false, angAng2H=false;

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
		out_nx1 = in_nx1;
		out_nx2 = in_nx2;
		out_ny1 = in_ny1;
		out_ny2 = in_ny2;
		out_trig = in_trig;
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
			if (in_tSQY_L[iii]>cs::tc_SQY_L)
			{
				SQY_L_mult++;
				SQY_L_Edep[SQY_L_mult]=SQY_L[iii];
				SQY_L_strip[SQY_L_mult]=iii;
			}
	
			if (in_tSQY_R[iii]>cs::tc_SQY_R)
			{
				SQY_R_mult++;
				SQY_R_Edep[SQY_R_mult]=SQY_R[iii];
				SQY_R_strip[SQY_R_mult]=iii;
			}

			if (in_tCsI_R[iii]>cs::tc_CsI_R)
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

			if (in_tCsI_L[iii]>cs::tc_CsI_L)
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

			if (in_tSQX_L[iii]>cs::tc_SQX_L)
			{
				SQX_L_mult++;
				SQX_L_Edep[SQX_L_mult]=SQX_L[iii];
				SQX_L_strip[SQX_L_mult]=iii;
			}

			if (SQX_R[iii]>5.0)
			{
				SQX_R_mult++;
				SQX_R_Edep[SQX_R_mult]=SQX_R[iii];
				SQX_R_strip[SQX_R_mult]=iii;
			}

			out_tSQX_L[iii]=in_tSQX_L[iii];
			out_tSQX_R[iii]=in_tSQX_R[iii];
		}

		//MWPC
		maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, cs::MWPC_1_X_id);
		maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, cs::MWPC_1_Y_id);
		maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, cs::MWPC_2_X_id);
		maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, cs::MWPC_2_Y_id);

		//displacement + go to corner of MWPC + follow wire order - get event point
		MWPC_1_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Z = -816.0;
		MWPC_2_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Z = -270.0;

		dX=MWPC_2_X-MWPC_1_X;
		dY=MWPC_2_Y-MWPC_1_Y;
		dZ=MWPC_2_Z-MWPC_1_Z;
		
		vBeam->SetXYZ(dX,dY,dZ);

		if ((in_aF5>600 && in_aF5<1200 && in_tof>162 && in_tof<182) || (in_aF5==0 && in_tof>162 && in_tof<182))
		{
			kinE = maynard->getT(in_tof,cs::mass_6He);
			tempE = he6_Si->GetE(kinE, ToFMWPC);
			Ion_ID = 62;
			kinE = he6_CD2->GetE(tempE,  tar_thcknss/(2*cos(tar_angle)));
		}

		else
		{
			Ion_ID = 0;
		}

		ene_beam = cs::mass_6He + kinE;
		mom_beam = sqrt(ene_beam*ene_beam - cs::mass_6He*cs::mass_6He);

		vBeam->SetMag(mom_beam);
	
		LV_beam->SetVectM(*vBeam, cs::mass_6He);
		Tcoef=(cos(tar_angle)*tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);

		evX = MWPC_1_X + dX*Tcoef;
		evY = MWPC_1_Y + dY*Tcoef;
		evZ = MWPC_1_Z + dZ*Tcoef;


		TLorentzVector lv6He_EL(*LV_beam);
		TLorentzVector lv1H_EL(0,0,0,cs::mass_1H);
		TLorentzVector lvCM_EL = lv6He_EL+lv1H_EL;
		TVector3 boostVect_EL = lvCM_EL.BoostVector();

		lv6He_EL.Boost(-boostVect_EL);
		lv1H_EL.Boost(-boostVect_EL);

		double theta_CM = rnd->Uniform(0.0,TMath::Pi());

		lv6He_EL.SetTheta(TMath::Pi()-theta_CM);
		lv1H_EL.SetTheta(theta_CM);

		lv6He_EL.Boost(boostVect_EL);
		lv1H_EL.Boost(boostVect_EL);
		sqlang1 = 180.0 * (LV_beam->Angle(lv1H_EL.Vect()))/double(TMath::Pi());
		sqrang1 = 180.0 * (LV_beam->Angle(lv6He_EL.Vect()))/double(TMath::Pi());


		lv6He_EL = *LV_beam;
		TLorentzVector lv2H_EL(0,0,0,cs::mass_2H);
		lvCM_EL = lv6He_EL+lv2H_EL;
		boostVect_EL = lvCM_EL.BoostVector();

		lv6He_EL.Boost(-boostVect_EL);
		lv2H_EL.Boost(-boostVect_EL);

		lv6He_EL.SetTheta(TMath::Pi()-theta_CM);
		lv2H_EL.SetTheta(theta_CM);

		lv6He_EL.Boost(boostVect_EL);
		lv2H_EL.Boost(boostVect_EL);
		sqlang2 = 180.0 * (LV_beam->Angle(lv2H_EL.Vect()))/double(TMath::Pi());
		sqrang2 = 180.0 * (LV_beam->Angle(lv6He_EL.Vect()))/double(TMath::Pi());


		//SQL energy - deuterium
		if (SQX_L_mult*SQY_L_mult==1 && SQX_L_Edep[1]>0 && (Ion_ID==62 || Ion_ID==61))
		{
			SQX_L_stripNo = SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5;
			SQY_L_stripNo = SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5;
			// coordinates of hit in LAB system
			X2H_lab = SQL_dist*sin(SQL_ang) + cs::SQL_start_X * cos(SQL_ang);
			Y2H_lab = cs::SQL_start_Y;
			Z2H_lab = SQL_dist*cos(SQL_ang) - cs::SQL_start_X * sin(SQL_ang);

			X2H_det	=	-cs::width_strip_X	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQL_ang);
			Y2H_det	=	cs::width_strip_Y	* 	(SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
			Z2H_det	=	cs::width_strip_X	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQL_ang);

			X2H = X2H_lab + X2H_det;
			Y2H = Y2H_lab + Y2H_det;
			Z2H = Z2H_lab + Z2H_det;
/*
			X2H = 1.8125 * (-15.5 + (SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5)) * cos(SQL_ang) + SQL_dist*sin(SQL_ang) + inputPars[0];
			Y2H = 3.625 * ((SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) - 7.5);
			Z2H = 1.8125 * (-15.5 + (SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5)) * sin(SQL_ang) + SQL_dist*cos(SQL_ang) + inputPars[1];
*/
			TVector3 vect1H(X2H-evX, Y2H-evY, Z2H-evZ);
			sqlphi=vect1H.Phi()*cs::rad_to_deg;
			sqltheta=vect1H.Theta()*cs::rad_to_deg;
			sqlang = vect1H.Angle(*vBeam)*cs::rad_to_deg;

			sqlde	=	h1_Si->GetE(SQX_L_Edep[1], -3.5);
			sqlde	=	h1_CD2->GetE(sqlde, -tar_thcknss/2);
			sqletot = memE_CsI_L;
			s_csil = memS_CsI_L;
			ene_1H = sqlde + cs::mass_1H;
			mom_1H = sqrt(ene_1H*ene_1H-cs::mass_1H*cs::mass_1H);
			vect1H.SetMag(mom_1H);
			LV_1H->SetVectM(vect1H, cs::mass_1H);
			*LV_6He = *LV_tar_1H + *LV_beam - *LV_1H;
			mml = LV_6He->M() - cs::mass_6He;

			if (sqlang>0 && sqlde>0)
			{
				//Deuterium energy after reaction
				kinsqle_1H = maynard->kin_GetERecoil(vect1H.Angle(*vBeam), kinE, cs::mass_1H/cs::mass_6He);
				kinsqle_2H = maynard->kin_GetERecoil(vect1H.Angle(*vBeam), kinE, cs::mass_2H/cs::mass_6He);
			

				fsqltheta_1H = 180.0*atan(sin(2*vBeam->Angle(vect1H))/(-cos(2*vBeam->Angle(vect1H))+cs::mass_6He/cs::mass_1H))/cs::PI;
				fsqltheta_2H = 180.0*atan(sin(2*vBeam->Angle(vect1H))/(-cos(2*vBeam->Angle(vect1H))+cs::mass_6He/cs::mass_2H))/cs::PI;
		
				fsqrtheta1 = maynard->kin_GetAngProjectile(kinsqle_1H, kinE, cs::mass_1H/cs::mass_6He);
				fsqrtheta2 = maynard->kin_GetAngProjectile(kinsqle_2H, kinE, cs::mass_2H/cs::mass_6He);
			}
		}

		//SQR energy - helium
		if(SQX_R_mult*SQY_R_mult==1)
		{
			SQX_R_stripNo = SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5;
			SQY_R_stripNo = SQY_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5;
			sqrde=SQY_R_Edep[1];
			sqretot=memE_CsI_R;
			s_csir = memS_CsI_R;

			// coordinates of hit in LAB system
			X6He_lab = SQR_dist*(sin(-SQR_ang)) - cs::SQR_start_X * cos(SQR_ang);
			Y6He_lab = cs::SQR_start_Y;
			Z6He_lab = SQR_dist*cos(SQR_ang) - cs::SQR_start_X * sin(SQR_ang);		

			X6He_det = cs::width_strip_X * SQX_R_stripNo * cos(SQR_ang);
			Y6He_det = cs::width_strip_Y * SQY_R_stripNo;
			Z6He_det = cs::width_strip_X * SQX_R_stripNo * sin(SQR_ang);

			X6He = X6He_lab + X6He_det;
			Y6He = Y6He_lab + Y6He_det;
			Z6He = Z6He_lab + Z6He_det;

			//setting deuterium vector
			TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
			ene_6He = sqrde + sqretot + cs::mass_6He;
			mom_6He = sqrt(ene_6He*ene_6He-cs::mass_6He*cs::mass_6He);
			vect6He.SetMag(mom_6He);

			sqrtheta=vect6He.Theta()*cs::rad_to_deg;
			sqrphi=vect6He.Phi()*cs::rad_to_deg;
			sqrang = vect6He.Angle(*vBeam)*cs::rad_to_deg;

		}


		if (gcut_dehe6->IsInside(sqretot,sqrde) && sqlde>0 && kinE>0)
		{
			he6=true;
			
			if (gcut_AngAng1H_w6He->IsInside(sqrang, sqlang))
			{
				angAng1H=true;
				//printf("ZONK\n");
				
			}
			
		}

		if (sqletot==0 && sqlde>7)
		{
			
		}
outTree->Fill();
		if (sqlang>0)
		{
			vec_lang.push_back(sqlang);
			vec_rang.push_back(sqrang);
		}
		
		
	}
	/*
	TF1 *angAngFit_1H = new TF1("angAngFit_1H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit_1H->FixParameter(0, 2*cs::deg_to_rad);
	angAngFit_1H->FixParameter(1, cs::mass_6He/cs::mass_1H);
	angAngFit_1H->FixParameter(2, cs::rad_to_deg);

	lang_vs_rang =  new TGraph(vec_lang.size(), &vec_lang[0], &vec_rang[0]);

	outTree->Draw("mml>>hist_mml", "");

	lang_vs_rang->Draw("AP");
	
	hist_mml->Fit("gaus", "Q");

	fit = hist_mml->GetFunction("gaus");

	qualityControl[0] = fit->GetParameter(1);
	qualityControl[1] = fit->GetParameter(2);

	lang_vs_rang->Fit(angAngFit_1H, "Q");
	qualityControl[2] = angAngFit_1H->GetChisquare();

	delete fit;
	delete hist_mml;
	delete lang_vs_rang;
	*/
	return 3.3;
}

Float_t dE_E_angle::actual_work_2H(Double_t inputPars[4], Double_t qualityControl[4])
{
	Int_t geoNo = cs::runNo;

	std::vector<Float_t> vec_lang;
	std::vector<Float_t> vec_rang;
	
	Long64_t nEntries = inTree->GetEntries();
	maynard->initializeGeometry(geoNo, &SQR_ang, &SQL_ang, &SQR_dist, &SQL_dist, &tar_angle, &tar_thcknss);


	counter=0;

	for (Long64_t entry=0; entry<nEntries; entry++)
		{

		inTree->GetEntry(entry);
	/*	
		if( entry % ( nEntries / 10 ) == 0)
		{
			printf("# Progress: %i %%\n", counter);
			counter+=10;
		}
	*/
	SQL_dist += inputPars[1];
		if (run==3)
		{
			tar_pos_Z = cs::tar_pos_Z + 2.0;
			tar_angle = 6.0 * cs::deg_to_rad;
			SQL_ang = (50.0 + inputPars[0]) * cs::deg_to_rad;
			SQR_ang = (15.0 ) * cs::deg_to_rad;
		}

		else
		{
			tar_pos_Z = cs::tar_pos_Z;
			tar_angle = 45.0 * cs::deg_to_rad;
			SQL_ang = (65.0 + inputPars[0]) * cs::deg_to_rad;
			SQR_ang = (15.0) * cs::deg_to_rad;
		}

		//NULLing everything
		LV_tar_2H->SetVectM(*vTarget,cs::mass_2H);
		memE_CsI_R=0.0; memE_CsI_L=0.0; memE_CsI_0L=0.0; memS_CsI_R=20; memS_CsI_L=20;
		kine_2H=0.0, kine_1H=0.0, rest_of_events = 0;
		Ion_ID = 0, Geo_ID = cs::runNo, kinE = 0.0;
		evX=0.0;evY=0.0;evZ=0.0; Run_ID = run;

		he6=false, angAng1H=false, angAng2H=false;

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
		out_nx1 = in_nx1;
		out_nx2 = in_nx2;
		out_ny1 = in_ny1;
		out_ny2 = in_ny2;
		out_trig = in_trig;
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
			if (SQY_L[iii]>3.0)
			{
				SQY_L_mult++;
				SQY_L_Edep[SQY_L_mult]=SQY_L[iii];
				SQY_L_strip[SQY_L_mult]=iii;
			}
	
			if (in_tSQY_R[iii]>cs::tc_SQY_R)
			{
				SQY_R_mult++;
				SQY_R_Edep[SQY_R_mult]=SQY_R[iii];
				SQY_R_strip[SQY_R_mult]=iii;
			}

			if (in_tCsI_R[iii]>cs::tc_CsI_R)
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

			if (in_tCsI_L[iii]>cs::tc_CsI_L)
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

			if (SQX_L[iii]>3.0)
			{
				SQX_L_mult++;
				SQX_L_Edep[SQX_L_mult]=SQX_L[iii];
				SQX_L_strip[SQX_L_mult]=iii;
			}

			if (SQX_R[iii]>5.0)
			{
				SQX_R_mult++;
				SQX_R_Edep[SQX_R_mult]=SQX_R[iii];
				SQX_R_strip[SQX_R_mult]=iii;
			}

			out_tSQX_L[iii]=in_tSQX_L[iii];
			out_tSQX_R[iii]=in_tSQX_R[iii];
		}

		//MWPC
		maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, cs::MWPC_1_X_id);
		maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, cs::MWPC_1_Y_id);
		maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, cs::MWPC_2_X_id);
		maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, cs::MWPC_2_Y_id);		
	
		//displacement + go to corner of MWPC + follow wire order - get event point
		MWPC_1_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Z = -816.0;
		MWPC_2_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Z = -270.0;

		dX=MWPC_2_X-MWPC_1_X;
		dY=MWPC_2_Y-MWPC_1_Y;
		dZ=MWPC_2_Z-MWPC_1_Z;
		
		vBeam->SetXYZ(dX,dY,dZ);

		if ((in_aF5>600 && in_aF5<1200 && in_tof>162 && in_tof<182) || (in_aF5==0 && in_tof>162 && in_tof<182))
		{
			kinE = maynard->getT(in_tof,cs::mass_6He);
			tempE = he6_Si->GetE(kinE, ToFMWPC);
			Ion_ID = 62;
			kinE = he6_CD2->GetE(tempE,  tar_thcknss/(2*cos(tar_angle)));
		}

		else
		{
			Ion_ID = 0;
		}

		ene_beam = cs::mass_6He + kinE;
		mom_beam = sqrt(ene_beam*ene_beam - cs::mass_6He*cs::mass_6He);

		vBeam->SetMag(mom_beam);
	
		LV_beam->SetVectM(*vBeam, cs::mass_6He);
		Tcoef=(cos(tar_angle)*tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);

		evX = MWPC_1_X + dX*Tcoef;
		evY = MWPC_1_Y + dY*Tcoef;
		evZ = MWPC_1_Z + dZ*Tcoef;


		TLorentzVector lv6He_EL(*LV_beam);
		TLorentzVector lv1H_EL(0,0,0,cs::mass_1H);
		TLorentzVector lvCM_EL = lv6He_EL+lv1H_EL;
		TVector3 boostVect_EL = lvCM_EL.BoostVector();

		lv6He_EL.Boost(-boostVect_EL);
		lv1H_EL.Boost(-boostVect_EL);

		double theta_CM = rnd->Uniform(0.0,TMath::Pi());

		lv6He_EL.SetTheta(TMath::Pi()-theta_CM);
		lv1H_EL.SetTheta(theta_CM);

		lv6He_EL.Boost(boostVect_EL);
		lv1H_EL.Boost(boostVect_EL);
		sqlang1 = 180.0 * (LV_beam->Angle(lv1H_EL.Vect()))/double(TMath::Pi());
		sqrang1 = 180.0 * (LV_beam->Angle(lv6He_EL.Vect()))/double(TMath::Pi());


		lv6He_EL = *LV_beam;
		TLorentzVector lv2H_EL(0,0,0,cs::mass_2H);
		lvCM_EL = lv6He_EL+lv2H_EL;
		boostVect_EL = lvCM_EL.BoostVector();

		lv6He_EL.Boost(-boostVect_EL);
		lv2H_EL.Boost(-boostVect_EL);

		lv6He_EL.SetTheta(TMath::Pi()-theta_CM);
		lv2H_EL.SetTheta(theta_CM);

		lv6He_EL.Boost(boostVect_EL);
		lv2H_EL.Boost(boostVect_EL);
		sqlang2 = 180.0 * (LV_beam->Angle(lv2H_EL.Vect()))/double(TMath::Pi());
		sqrang2 = 180.0 * (LV_beam->Angle(lv6He_EL.Vect()))/double(TMath::Pi());


		//SQL energy - deuterium
		if (SQX_L_mult*SQY_L_mult==1 && SQX_L_Edep[1]>0 && (Ion_ID==62 || Ion_ID==61))
		{
			// coordinates of hit in LAB system
			SQX_L_stripNo = SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5;
			SQY_L_stripNo = SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5;

			X2H_lab = SQL_dist*sin(SQL_ang) + cs::SQL_start_X * cos(SQL_ang);
			Y2H_lab = cs::SQL_start_Y;
			Z2H_lab = SQL_dist*cos(SQL_ang) - cs::SQL_start_X * sin(SQL_ang);		

			X2H_det	=	-cs::width_strip_X	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQL_ang);
			Y2H_det	=	cs::width_strip_Y	* 	(SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
			Z2H_det	=	cs::width_strip_X	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQL_ang);

			X2H = X2H_lab + X2H_det;
			Y2H = Y2H_lab + Y2H_det;
			Z2H = Z2H_lab + Z2H_det;

			TVector3 vect2H(X2H-evX, Y2H-evY, Z2H-evZ);
			sqlphi=vect2H.Phi()*cs::rad_to_deg;
			sqltheta=vect2H.Theta()*cs::rad_to_deg;
			sqlang = vect2H.Angle(*vBeam)*cs::rad_to_deg;

			sqlde	=	h2_Si->GetE(SQX_L_Edep[1], -3.5);
			sqlde	=	h2_CD2->GetE(sqlde, -tar_thcknss/2);
			sqletot = memE_CsI_L;
			s_csil = memS_CsI_L;
			ene_2H = sqlde + cs::mass_2H;
			mom_2H = sqrt(ene_2H*ene_2H-cs::mass_2H*cs::mass_2H);
			vect2H.SetMag(mom_2H);
			LV_2H->SetVectM(vect2H, cs::mass_2H);
			*LV_6He = *LV_tar_2H + *LV_beam - *LV_2H;
			mml = LV_6He->M() - cs::mass_6He;

			if (sqlang>0 && sqlde>0)
			{
				//Deuterium energy after reaction
				kinsqle_1H = maynard->kin_GetERecoil(vect2H.Angle(*vBeam), kinE, cs::mass_1H/cs::mass_6He);
				kinsqle_2H = maynard->kin_GetERecoil(vect2H.Angle(*vBeam), kinE, cs::mass_2H/cs::mass_6He);
			

				fsqltheta_1H = 180.0*atan(sin(2*vBeam->Angle(vect2H))/(-cos(2*vBeam->Angle(vect2H))+cs::mass_6He/cs::mass_1H))/cs::PI;
				fsqltheta_2H = 180.0*atan(sin(2*vBeam->Angle(vect2H))/(-cos(2*vBeam->Angle(vect2H))+cs::mass_6He/cs::mass_2H))/cs::PI;
		
				fsqrtheta1 = maynard->kin_GetAngProjectile(kinsqle_1H, kinE, cs::mass_1H/cs::mass_6He);
				fsqrtheta2 = maynard->kin_GetAngProjectile(kinsqle_2H, kinE, cs::mass_2H/cs::mass_6He);
			}
		}

		//SQR energy - helium
		if(SQX_R_mult*SQY_R_mult==1)
		{
			SQX_R_stripNo = SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5;
			SQY_R_stripNo = SQY_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5;

			sqrde=SQY_R_Edep[1];
			sqretot=memE_CsI_R;
			s_csir = memS_CsI_R;

			// coordinates of hit in LAB system
			X6He_lab = SQR_dist*(sin(-SQR_ang)) - cs::SQR_start_X * cos(SQR_ang);
			Y6He_lab = cs::SQR_start_Y;
			Z6He_lab = SQR_dist*cos(SQR_ang) - cs::SQR_start_X * sin(SQR_ang);		

			X6He_det = cs::width_strip_X * (SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQR_ang);
			Y6He_det = cs::width_strip_Y * (SQY_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
			Z6He_det = cs::width_strip_X * (SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQR_ang);

			X6He = X6He_lab + X6He_det;
			Y6He = Y6He_lab + Y6He_det;
			Z6He = Z6He_lab + Z6He_det;

			//setting deuterium vector
			TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
			ene_6He = sqrde + sqretot + cs::mass_6He;
			mom_6He = sqrt(ene_6He*ene_6He-cs::mass_6He*cs::mass_6He);
			vect6He.SetMag(mom_6He);

			sqrtheta=vect6He.Theta()*cs::rad_to_deg;
			sqrphi=vect6He.Phi()*cs::rad_to_deg;
			sqrang = vect6He.Angle(*vBeam)*cs::rad_to_deg;

		}

		if (gcut_dehe6->IsInside(sqretot,sqrde) && sqlde>0 && kinE>0)
		{
			he6=true;
			
			if (gcut_AngAng2H_w6He->IsInside(sqrang, sqlang)/* && sqletot==0*/)
			{
				angAng2H=true;
				outTree->Fill();
			}
		}

		if (sqletot==0 && sqlde>7)
		{
			
		}
		if (sqlang>0)
		{
			vec_lang.push_back(sqlang);
			vec_rang.push_back(sqrang);
		}

		
		
	}
	/*
	hist_mml = new TH1F("hist_mml", "blabla", 200, -10.0, 10.0);
	TF1 *fit;
	TF1 *angAngFit_2H = new TF1("angAngFit_2H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit_2H->FixParameter(0, 2*cs::deg_to_rad);
	angAngFit_2H->FixParameter(1, cs::mass_6He/cs::mass_2H);
	angAngFit_2H->FixParameter(2, cs::rad_to_deg);
	lang_vs_rang =  new TGraph(vec_lang.size(), &vec_lang[0], &vec_rang[0]);

	outTree->Draw("mml>>hist_mml", "");
	
	lang_vs_rang->Draw("AP");
	lang_vs_rang->Fit(angAngFit_2H, "Q");
	hist_mml->Fit("gaus", "Q");

	fit = hist_mml->GetFunction("gaus");

	qualityControl[0] = fit->GetParameter(1);
	qualityControl[1] = fit->GetParameter(2);
	qualityControl[2] = angAngFit_2H->GetChisquare();

	delete fit;
	delete hist_mml;
	delete lang_vs_rang;
	*/
	return 3.3;
}

Float_t dE_E_angle::actual_work_gas(Float_t MWPC_X_1_shift, Float_t MWPC_X_2_shift, Double_t qualityControl[4])
{
	// By definition, geoNo = 5
	printf("%f\t%f\n", MWPC_X_1_shift, MWPC_X_2_shift);
	int geoNo=5;
	hist_mml = new TH1F("hist_mml", "blabla", 200, -10.0, 10.0);
	hist_ene_diff = new TH1F("hist_ene_diff", "tit", 200, -15.0, 15.0);

	std::vector<Float_t> vec_lang;
	std::vector<Float_t> vec_rang;
	TF1 *fit;

	Long64_t nEntries = inTree->GetEntries();
	maynard->initializeGeometry(geoNo, &SQR_ang, &SQL_ang, &SQR_dist, &SQL_dist, &tar_angle, &tar_thcknss);


	counter=0;

	for (Long64_t entry=0; entry<nEntries; entry++)
		{

		inTree->GetEntry(entry);
	
		if( entry % ( nEntries / 10 ) == 0)
		{
			printf("# Progress: %i %%\n", counter);
			counter+=10;
		}
		//NULLing everything
		LV_tar_2H->SetVectM(*vTarget,cs::mass_2H);
		memE_CsI_R=0.0; memE_CsI_L=0.0; memE_CsI_0L=0.0; memS_CsI_R=20; memS_CsI_L=20;
		kine_2H=0.0, kine_1H=0.0, rest_of_events = 0;
		Ion_ID = 0, Geo_ID = cs::runNo, kinE = 0.0;
		evX=0.0;evY=0.0;evZ=0.0; Run_ID = run;

		he6=false, angAng1H=false, angAng2H=false;

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
			if (SQY_L[iii]>cs::SQY_L_5)
			{
				SQY_L_mult++;
				SQY_L_Edep[SQY_L_mult]=SQY_L[iii];
				SQY_L_strip[SQY_L_mult]=iii;
			}
	
			if (SQY_R[iii]>cs::SQY_R_5)
			{
				SQY_R_mult++;
				SQY_R_Edep[SQY_R_mult]=SQY_R[iii];
				SQY_R_strip[SQY_R_mult]=iii;
			}

			/*
			if (in_tSQ300[iii]>2.0)
			{
				SQ300_mult++;
				SQ300_Edep[SQ300_mult]=SQ300[iii];
				SQ300_strip[SQ300_mult]=iii;
			}
			*/

			if (r_CsI_R[iii]>cs::CsI_R_5)
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

			if (CsI_L[iii]>cs::CsI_L_5)
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

			c_SQY_L[iii]=SQY_L[iii];
			c_SQY_R[iii]=SQY_R[iii];
			c_CsI_L[iii]=CsI_L[iii];
			c_CsI_R[iii]=CsI_R[iii];

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

			
			if (SQX_L[iii]>cs::SQX_L_5)
			{

				SQX_L_mult++;
				//if (SQX_L_mult>1) {printf("SQX_L[%d] = %f\n",iii, SQX_L[iii])};
				SQX_L_Edep[SQX_L_mult]=SQX_L[iii];
				SQX_L_strip[SQX_L_mult]=iii;
			}

			if (SQX_R[iii]>cs::SQX_R_5)
			{
				SQX_R_mult++;
				SQX_R_Edep[SQX_R_mult]=SQX_R[iii];
				SQX_R_strip[SQX_R_mult]=iii;
			}

			c_SQX_L[iii]=SQX_L[iii];
			c_SQX_R[iii]=SQX_R[iii];
			raw_SQX_L[iii]=r_SQX_L[iii];
			raw_SQX_R[iii]=r_SQX_R[iii];
			out_tSQX_L[iii]=in_tSQX_L[iii];
			out_tSQX_R[iii]=in_tSQX_R[iii];
		}
		

		//MWPC
		maynard->Get_MWPC_pos(in_nx1, in_x1, &MWPC_1_X, cs::MWPC_1_X_id);
		maynard->Get_MWPC_pos(in_ny1, in_y1, &MWPC_1_Y, cs::MWPC_1_Y_id);
		maynard->Get_MWPC_pos(in_nx2, in_x2, &MWPC_2_X, cs::MWPC_2_X_id);
		maynard->Get_MWPC_pos(in_ny2, in_y2, &MWPC_2_Y, cs::MWPC_2_Y_id);	

	
		//displacement + go to corner of MWPC + follow wire order - get event point
		MWPC_1_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_1_Z = -816.0;
		MWPC_2_X += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Y += rnd->Uniform(0.0,1.25)-0.6125;
		MWPC_2_Z = -270.0;

		dX = MWPC_2_X-MWPC_1_X;
		dY = MWPC_2_Y-MWPC_1_Y;
		dZ = MWPC_2_Z-MWPC_1_Z;
		
		vBeam->SetXYZ(dX,dY,dZ);
		Float_t ToFMWPC{644.0};
		// choose correct Eloss method

		//in_tof+=20.0;
		if ((in_aF5>450 && in_aF5<700 && in_tof>175 && in_tof<181) || (in_aF5==0 && in_tof>175 && in_tof<181))
		{	
			kinE = maynard->getT(in_tof, cs::mass_6He);
			tempE = he6_Si->GetE(kinE, ToFMWPC+gasTargetSi);
			Ion_ID = 62;
			kinE = tempE;
		}

		else
		{
			Ion_ID = 0;
		}

		ene_beam = cs::mass_6He + kinE;
		mom_beam = sqrt(ene_beam*ene_beam - cs::mass_6He*cs::mass_6He);

		vBeam->SetMag(mom_beam);
	
		LV_beam->SetVectM(*vBeam, cs::mass_6He);
		Tcoef=(cos(tar_angle)*cs::tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);

		evX = MWPC_1_X + dX*Tcoef;
		evY = MWPC_1_Y + dY*Tcoef;
		evZ = MWPC_1_Z + dZ*Tcoef;

		//SQL energy - deuterium
		if (SQX_L_mult*SQY_L_mult==1 && SQX_L_Edep[1]>0 && (Ion_ID==62 || Ion_ID==61))
		{
			// coordinates of hit in LAB system
			X2H_lab = SQL_dist*sin(SQL_ang) - cs::SQL_start_X * cos(SQL_ang);
			Y2H_lab = cs::SQL_start_Y;
			Z2H_lab = SQL_dist*cos(SQL_ang) + cs::SQL_start_X * sin(SQL_ang);

			X2H_det	=	cs::width_strip_X	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQL_ang);
			Y2H_det	=	cs::width_strip_Y	* 	(SQY_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
			Z2H_det	=	cs::width_strip_X	*	(SQX_L_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQL_ang);

			X2H = X2H_lab + X2H_det;
			Y2H = Y2H_lab + Y2H_det;
			Z2H = Z2H_lab - Z2H_det;

			//printf("Z2H_lab= %f\tZ2H_det= %f\t\n", Z2H_lab, Z2H_det);

			TVector3 vect2H(X2H-evX, Y2H-evY, Z2H-evZ);
			sqlphi=vect2H.Phi()*cs::rad_to_deg;
			sqltheta=vect2H.Theta()*cs::rad_to_deg;
			sqlang = vect2H.Angle(*vBeam)*cs::rad_to_deg;

			//Energy deposited in Si detector corrected for dead layer
			dummy1	=	h2_Si->GetE(SQX_L_Edep[1], -2.5);
			sqlde 	=	h2_Si->GetE(dummy1, -gasTargetSi/(2*cos(vect2H.Theta()-tar_angle)));
			Si_L_bank = SQX_L_Edep[1];
			sqletot = memE_CsI_L;
			cr = memS_CsI_L;
			//sqlde=SQX_L_Edep[1];
			ene_2H = sqlde + sqletot + cs::mass_2H;
		
			mom_2H = sqrt(ene_2H*ene_2H - cs::mass_2H*cs::mass_2H);
			vect2H.SetMag(mom_2H);
			LV_2H->SetVectM(vect2H, cs::mass_2H);
			*LV_6He = *LV_tar_2H + *LV_beam - *LV_2H;
			mml = LV_6He->M() - cs::mass_6He;

			if (sqlang>0 && sqlde>0)
			{
				//Deuterium energy after reaction based on angle
				kinsqle_1H = maynard->kin_GetERecoil(vect2H.Angle(*vBeam), kinE, cs::mass_1H/cs::mass_6He);
				kinsqle_2H = maynard->kin_GetERecoil(vect2H.Angle(*vBeam), kinE, cs::mass_2H/cs::mass_6He);
			
				//Helium angle based on dueterium angle
				fsqltheta_1H = 180.0*atan(sin(2*vBeam->Angle(vect2H))/(-cos(2*vBeam->Angle(vect2H))+cs::mass_6He/cs::mass_1H))/cs::PI;
				fsqltheta_2H = 180.0*atan(sin(2*vBeam->Angle(vect2H))/(-cos(2*vBeam->Angle(vect2H))+cs::mass_6He/cs::mass_2H))/cs::PI;
		
				//Helium angle based on Deuterium angle(based on deut energy)
				fsqrtheta1 = maynard->kin_GetAngProjectile(kinsqle_1H,kinE, cs::mass_1H/cs::mass_6He);
				fsqrtheta2 = maynard->kin_GetAngProjectile(kinsqle_2H,kinE, cs::mass_2H/cs::mass_6He);
			}
		}

		//SQR energy - helium
		if(SQX_R_mult*SQY_R_mult==1)
		{
			sqrde=SQX_R_Edep[1];
			sqretot=memE_CsI_R;

			// coordinates of hit in LAB system
			Double_t m_sqrDetAng = SQR_ang + 1.65;

			X6He_lab = -1 * SQR_dist * sin(SQR_ang*TMath::DegToRad()) + cs::width_strip_X * 15.5 * cos(m_sqrDetAng*TMath::DegToRad());
			Y6He_lab = -7.5 * cs::width_strip_Y;
			Z6He_lab = SQR_dist * cos(SQR_ang*TMath::DegToRad()) + cs::width_strip_X * 15.5 * sin(m_sqrDetAng*TMath::DegToRad());

			X6He_det = cs::width_strip_X	* (SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * cos(SQR_ang);
			Y6He_det = cs::width_strip_Y	* (SQY_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5);
			Z6He_det = cs::width_strip_X	* (SQX_R_strip[1]+rnd->Uniform(0.0,1.0)-0.5) * sin(SQR_ang);

			X6He = X6He_lab + X6He_det;
			Y6He = Y6He_lab + Y6He_det;
			Z6He = Z6He_lab + Z6He_det;

			//setting deuterium vector
			TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
			ene_6He = sqrde + sqretot + cs::mass_6He;
			mom_6He = sqrt(ene_6He*ene_6He-cs::mass_6He*cs::mass_6He);
			vect6He.SetMag(mom_6He);

			//setting LAB angles of scattered 6 He - reference is beam vector
			//vect6He=beam_setting_array*vect6He;
			sqrtheta=vect6He.Theta()*cs::rad_to_deg;
			sqrphi=vect6He.Phi()*cs::rad_to_deg;
			sqrang = vect6He.Angle(*vBeam)*cs::rad_to_deg;
		}

		if (gcut_dehe6->IsInside(sqretot,sqrde) && sqlde>0 && Ion_ID>60)
		{			
			if (deut_geo5->IsInside(sqrang,sqlang) && (sqlde+sqletot)>6.0)
			{
				he6=true;
				vec_lang.push_back(evX);
				vec_rang.push_back(mml);
				outTree->Fill();
			}
		}


		
		
		
	}

	TF1 *evX_vs_mml_fit = new TF1("evX_vs_mml_fit","[0]*x + [1]");
	lang_vs_rang =  new TGraph(vec_lang.size(), &vec_lang[0], &vec_rang[0]);



	
	//outTree->Draw("sqlde+sqletot-kinsqle_2H>>hist_ene_diff", "");
	outTree->Draw("mml>>hist_mml", "");
	//hist_ene_diff->Fit("gaus", "Q");
	/*hist_mml->Fit("gaus", "Q");


	fit = hist_ene_diff->GetFunction("gaus");
	qualityControl[0] = fit->GetParameter(1);
	qualityControl[1] = fit->GetParameter(2);
	qualityControl[2] = fit->GetChisquare();
	fit = hist_mml->GetFunction("gaus");
	qualityControl[3] = fit->GetParameter(1);*/
	
		//lang_vs_rang->Draw("AP");
	//lang_vs_rang->Fit(evX_vs_mml_fit, "Q");
	//qualityControl[3] = evX_vs_mml_fit->GetParameter(0);

	delete fit;
	delete hist_mml;
	delete hist_ene_diff;
	delete evX_vs_mml_fit;
	delete lang_vs_rang;

	return 3.3;
}