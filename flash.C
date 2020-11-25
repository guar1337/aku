#define flash_cxx

#include "flash.h"
#include <TH2.h>
#include <TStyle.h>

Float_t flash::getVelo(Float_t T, Float_t mass)
{
	Float_t gamma_squared = pow(T/(mass)+1,2.0);
	Float_t beta = sqrt(1-1/gamma_squared);
	return beta*cs::c;
}

void flash::Begin(TTree * /*tree*/)
{
	rnd = new TRandom3();
	int si_Nel=1;
	si_A[0]=28;
	si_Z[0]=14;
	si_W[0]=1;

	int CD2_Nel=2;
	CD2_A[0]=2;
	CD2_Z[0]=1;
	CD2_W[0]=2;

	CD2_A[1]=12;
	CD2_Z[1]=6;
	CD2_W[1]=1;

	h2_Si 		= new ELC(2, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
	h2_CD2		= new ELC(2, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);

	h1_Si 		= new ELC(1, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
	h1_CD2		= new ELC(1, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);

	TString option = GetOption();
	//lvBeam = new TLorentzVector();
	lvHe6 = new TLorentzVector();
	lvH1 = new TLorentzVector();
	lvH2 = new TLorentzVector();
	TVector3 vTarget(0.0, 0.0, 0.0);
	lvTar1H = new TLorentzVector();
	lvTar2H = new TLorentzVector();
	lvTar1H->SetVectM(vTarget, cs::mass_1H);
	lvTar2H->SetVectM(vTarget, cs::mass_2H);
	
}

void flash::SlaveBegin(TTree * /*tree*/)
{
	string option = GetOption();
	stringstream ss(option);
	ss>>inputPars[0];
	ss>>inputPars[1];
	ss>>inputPars[2];
	ss>>inputPars[3];

	
	hist_mml1 = new TH1F("hist_mml1", "hist_mml1", 200, -10.0, 10.0);
	hist_mml2 = new TH1F("hist_mml2", "hist_mml2", 200, -10.0, 10.0);
}

Bool_t flash::Process(Long64_t entry)
{
	fReader.SetEntry(entry);
	TLorentzVector *flvBeam = new TLorentzVector((*lvBeam).Px(), (*lvBeam).Py(), (*lvBeam).Pz(), (*lvBeam).E());

	
	if (*geo==2)
	{
		tar_pos_Z = cs::tar_pos_Z + 2.0;
		tar_angle = 6.0 * cs::deg_to_rad;
		SQL_ang = (50.0) * cs::deg_to_rad;
		SQR_ang = (15.0) * cs::deg_to_rad;
		SQL_dist = cs::sql_dist_s2;
		SQR_dist = cs::sqr_dist_s2;
	}

	else
	{
		tar_pos_Z = cs::tar_pos_Z;	
		tar_angle = 45.0 * cs::deg_to_rad;
		SQL_ang = (65.0) * cs::deg_to_rad;
		SQR_ang = (15.0) * cs::deg_to_rad;
		SQL_dist = cs::sql_dist_s1;
		SQR_dist = cs::sqr_dist_s1;
	}
/*
	TLorentzVector lv6He(*flvBeam);
	TLorentzVector lv1H(0,0,0,cs::mass_1H);
	TLorentzVector lvCM = lv6He+lv1H;
	TVector3 boostVect = lvCM.BoostVector();

	lv6He.Boost(-boostVect);
	lv1H.Boost(-boostVect);

	double theta_CM = rnd->Uniform(0.0,TMath::Pi());

	lv6He.SetTheta(TMath::Pi()-theta_CM);
	lv1H.SetTheta(theta_CM);

	lv6He.Boost(boostVect);
	lv1H.Boost(boostVect);

	lvsqlang = 180.0 * (lvBeam->Angle(lv1H.Vect()))/double(TMath::Pi());
	lvsqrang = 180.0 * (lvBeam->Angle(lv6He.Vect()))/double(TMath::Pi());

*/
	X2H_lab = SQL_dist*sin(SQL_ang) + cs::SQL_start_X * cos(SQL_ang);
	Y2H_lab = cs::SQL_start_Y;
	Z2H_lab = SQL_dist*cos(SQL_ang) - cs::SQL_start_X * sin(SQL_ang);

	X2H_det = -cs::width_strip_X * (*SQX_L_sNo) * cos(SQL_ang);
	Y2H_det = cs::width_strip_Y * (*SQY_L_sNo);
	Z2H_det = cs::width_strip_X * (*SQX_L_sNo) * sin(SQL_ang);

	X2H = X2H_lab + X2H_det;
	Y2H = Y2H_lab + Y2H_det;
	Z2H = Z2H_lab + Z2H_det;

/*	
	X2H = 1.8125 * (-15.5 + *SQX_L_sNo) * cos(SQL_ang) + SQL_dist*sin(SQL_ang) + inputPars[0];
	Y2H = 3.625 * (*SQY_L_sNo - 7.5);
	Z2H = 1.8125 * (-15.5 + *SQX_L_sNo) * sin(SQL_ang) + SQL_dist*cos(SQL_ang) + inputPars[1];
*/
	TVector3 vectH(X2H-*evX, Y2H-*evY, Z2H-*evZ);
	sqlphi=vectH.Phi()*cs::rad_to_deg;
	sqltheta=vectH.Theta()*cs::rad_to_deg;
	sqlang = vectH.Angle(flvBeam->Vect())*cs::rad_to_deg;

	//*sqlde = h1_CD2->GetE(*sqlde, -tar_thcknss/2);


	if (*pro==1)
	{

		vec_lang_1H.push_back(sqlang);
		vec_lang_1H.push_back(sqlang);

		if (*sqletot==0 && *sqlde>7.0)
		{
			ene_1H = h1_CD2->GetE(*sqlde, tar) + cs::mass_1H;
			mom_1H = sqrt(ene_1H*ene_1H-cs::mass_1H*cs::mass_1H);
			vectH.SetMag(mom_1H);
			lvH1->SetVectM(vectH, cs::mass_1H);
			*lvHe6 = *lvTar1H + *flvBeam - *lvH1;
			hist_mml1->Fill(lvHe6->M() - cs::mass_6He);
		}

	}

	if (*deu==1)
	{
		vec_lang_2H.push_back(sqlang);
		vec_lang_2H.push_back(sqlang);

		if (*sqletot==0 && *sqlde>7.0)
		{
			
			ene_2H = h2_CD2->GetE(*sqlde, tar) + cs::mass_2H;
			mom_2H = sqrt(ene_2H*ene_2H-cs::mass_2H*cs::mass_2H);
			vectH.SetMag(mom_2H);
			lvH2->SetVectM(vectH, cs::mass_2H);
			*lvHe6 = *lvTar2H + *flvBeam - *lvH2;
			hist_mml2->Fill(lvHe6->M() - cs::mass_6He);	
			printf("%f\t%f\t%f\n",*sqlde, sqlang, lvHe6->M() - cs::mass_6He);
		}

	}

	
/*
	Float_t velo_beam = getVelo(*kinE, cs::mass_6He);

	//kin_GetERecoil(vectH.Angle(*vBeam), kinE, cs::mass_1H/cs::mass_6He);
	Float_t velo_pro = ((2 * cos(sqlang)) / (1+cs::mass_1H/cs::mass_6He)) * velo_beam;
	velo_hel = getVelo(*kinE - *sqlde, cs::mass_6He);
	vel_R = velo_hel/velo_beam;
	beta_squared= pow(velo_pro/cs::c, 2.0);
	gamma=1.0/sqrt(1.0-beta_squared);
	fEproFromLang = cs::mass_1H/cs::mass_6He*(gamma-1.0)*cs::mass_6He;	//energy from angle
	fsqltheta_1H = 180.0*atan(sin(2*flvBeam->Vect().Angle(vectH))/(-cos(2*flvBeam->Vect().Angle(vectH))+cs::mass_6He/cs::mass_1H))/cs::PI;

	fsqrang1H = cs::rad_to_deg*atan(sin(2*cs::deg_to_rad*sqlang)/(cs::mass_6He/cs::mass_1H-cos(2*cs::deg_to_rad*sqlang)));	//R angle from L angle
	fsqrang2H = cs::rad_to_deg*atan(sin(2*cs::deg_to_rad*sqlang)/(cs::mass_6He/cs::mass_2H-cos(2*cs::deg_to_rad*sqlang)));	//R angle from L angle


	//kin_GetERecoil(vect2H.Angle(*flvBeam->Vect()), kinE, cs::mass_2H/cs::mass_6He);
	Float_t velo_deu = ((2 * cos(sqlang)) / (1+cs::mass_2H/cs::mass_6He)) * velo_beam;
	velo_hel = getVelo(*kinE - *sqlde, cs::mass_6He);
	vel_R = velo_hel/velo_beam;
	beta_squared= pow(velo_deu/cs::c, 2.0);
	gamma=1.0/sqrt(1.0-beta_squared);
	fEdeuFromLang = cs::mass_2H/cs::mass_6He*(gamma-1.0)*cs::mass_6He;	//energy from angle
	fsqltheta_2H = 180.0*atan(sin(2*flvBeam->Vect().Angle(vectH))/(-cos(2*flvBeam->Vect().Angle(vectH))+cs::mass_6He/cs::mass_2H))/cs::PI;
*/
	X6He_lab = SQR_dist*(sin(-SQR_ang)) - cs::SQR_start_X * cos(SQR_ang);
	Y6He_lab = cs::SQR_start_Y;
	Z6He_lab = SQR_dist*cos(SQR_ang) - cs::SQR_start_X * sin(SQR_ang);		

	X6He_det = cs::width_strip_X * (*SQX_R_sNo) * cos(SQR_ang);
	Y6He_det = cs::width_strip_Y * (*SQY_R_sNo);
	Z6He_det = cs::width_strip_X * (*SQX_R_sNo) * sin(SQR_ang);

	X6He = X6He_lab + X6He_det + inputPars[2];
	Y6He = Y6He_lab + Y6He_det;
	Z6He = Z6He_lab + Z6He_det + inputPars[3];

	TVector3 vect6He(X6He-0, Y6He-0, Z6He-0);
	sqrtheta=vect6He.Theta()*cs::rad_to_deg;
	sqrphi=vect6He.Phi()*cs::rad_to_deg;
	sqrang = vect6He.Angle(flvBeam->Vect())*cs::rad_to_deg;

if (*pro)
{
	vec_lang_1H.push_back(sqlang);
	vec_rang_1H.push_back(sqrang);
}

if (*deu)
{
	vec_lang_2H.push_back(sqlang);
	vec_rang_2H.push_back(sqrang);
}


	return kTRUE;  
}

void flash::SlaveTerminate()
{

	string option = GetOption();

	ofstream outStream("/home/zalewski/Desktop/varDist.txt", ios::app);

	TF1 *angAngFit_1H = new TF1("angAngFit_1H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit_1H->FixParameter(0, 2*cs::deg_to_rad);
	angAngFit_1H->FixParameter(1, cs::mass_6He/cs::mass_1H);
	angAngFit_1H->FixParameter(2, cs::rad_to_deg);


	TF1 *angAngFit_2H = new TF1("angAngFit_2H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit_2H->FixParameter(0, 2*cs::deg_to_rad);
	angAngFit_2H->FixParameter(1, cs::mass_6He/cs::mass_2H);
	angAngFit_2H->FixParameter(2, cs::rad_to_deg);



	lang_vs_rang_1H =  new TGraph(vec_lang_1H.size(), &vec_lang_1H[0], &vec_rang_1H[0]);
	lang_vs_rang_2H =  new TGraph(vec_lang_2H.size(), &vec_lang_2H[0], &vec_rang_2H[0]);


	hist_mml1->Fit("gaus", "Q");
	hist_mml2->Fit("gaus", "Q");
	fit1 = hist_mml1->GetFunction("gaus");
	fit2 = hist_mml2->GetFunction("gaus");
	lang_vs_rang_1H->Fit(angAngFit_1H,"Q");	
	lang_vs_rang_2H->Fit(angAngFit_2H,"Q");

	Float_t peakCntr1 = fit1->GetParameter(1);
	Float_t peakCntr2 = fit2->GetParameter(1);
	Float_t sig1 = fit1->GetParameter(2);
	Float_t sig2 = fit2->GetParameter(2);
	Float_t Chi1 = angAngFit_1H->GetChisquare();
	Float_t Chi2 = angAngFit_2H->GetChisquare();
					printf("%s\n", option.c_str());
	outStream<<inputPars[0]<<" "<<inputPars[1]<<" "<<inputPars[2]<<" "<<inputPars[3]<<" "<<peakCntr1<<" "<<sig1<<" "<<Chi1<<" "<<peakCntr2<<" "<<sig2<<" "<<Chi2<<" "<<endl;
	//printf("%f\t%f\t%f\n", fit1->GetParameter(1), fit2->GetParameter(1), fit1->GetParameter(1) - fit2->GetParameter(1));


	//lang_vs_rang_1H->Draw("");

}

void flash::Terminate()
{

	delete h2_Si, h2_CD2, h1_Si, h1_CD2;
	delete lvHe6, lvH1, lvH2, lvTar1H, lvTar2H;
}