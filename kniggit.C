#include "TString.h"
#include "constants.h"
/*
#include "ELC/AELC.h"
#include "ELC/ELC.h"
R__LOAD_LIBRARY(libgsl.so); 
R__LOAD_LIBRARY(/home/guar/aku/wrk/ELC/libEloss.so);
*/


TFile *inF = new TFile{"/home/guar/data/he6_d/dE/PG_geo12.root", "READ"};
TTreeReader fReader("dE_angle", inF);

TTreeReaderValue<Float_t> SQX_L_sNo = {fReader, "SQX_L_sNo"};
TTreeReaderValue<Float_t> SQX_R_sNo = {fReader, "SQX_R_sNo"};
TTreeReaderValue<Float_t> SQY_L_sNo = {fReader, "SQY_L_sNo"};
TTreeReaderValue<Float_t> SQY_R_sNo = {fReader, "SQY_R_sNo"};
TTreeReaderValue<Double_t> sqlde = {fReader, "sqlde"};
TTreeReaderValue<Double_t> sqletot = {fReader, "sqletot"};
//TTreeReaderValue<Double_t> sqlang = {fReader, "sqlang"};
TTreeReaderValue<Double_t> sqrde = {fReader, "sqrde"};
TTreeReaderValue<Double_t> sqretot = {fReader, "sqretot"};
//TTreeReaderValue<Double_t> sqrang = {fReader, "sqrang"};
TTreeReaderValue<Float_t> evX = {fReader, "evX"};
TTreeReaderValue<Float_t> evY = {fReader, "evY"};
TTreeReaderValue<Float_t> evZ = {fReader, "evZ"};
TTreeReaderValue<Float_t> dX = {fReader, "dX"};
TTreeReaderValue<Float_t> dY = {fReader, "dY"};
TTreeReaderValue<Float_t> dZ = {fReader, "dZ"};
TTreeReaderValue<Short_t> geo = {fReader, "geo"};
TTreeReaderValue<Bool_t> deu = {fReader, "deu"};
TTreeReaderValue<Bool_t> pro = {fReader, "pro"};
TTreeReaderValue<Double_t> kinE = {fReader, "kinE"};
TTreeReaderValue<TLorentzVector> lvBeam = {fReader, "LV_beam."};

Float_t tar_pos_Z, tar_thcknss, tar_angle, SQL_ang, SQR_ang, SQL_dist, SQR_dist, lvsqlang, lvsqrang, tar;
Float_t X2H_lab, Y2H_lab, Z2H_lab, X6He_lab, Y6He_lab, Z6He_lab;
Float_t X2H_det, Y2H_det, Z2H_det, X6He_det, Y6He_det, Z6He_det;
Float_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
Float_t sqlphi, sqltheta, sqrphi, sqrtheta, mml, sqlang, sqrang;
Float_t ene_1H, ene_2H, mom_1H, mom_2H;
Float_t fEproFromLang, fEdeuFromLang, fsqltheta_1H, fsqltheta_2H, fsqrang1H, fsqrang2H;
Float_t inputPars[4];
TRandom3 *rnd;
TGraph *lang_vs_rang_1H, *lang_vs_rang_2H;

Double_t si_A[1], si_Z[1], si_W[1];
Double_t CD2_A[2], CD2_Z[2], CD2_W[2];

//AELC *h2_Si, *h2_CD2, *h1_Si, *h1_CD2;

TVector3 *vBeam, v6He;
//TLorentzVector *lvH1, *lvH2, *lvHe6, *lvTar1H, *lvTar2H;
TF1 *fit1, *fit2;

std::vector<Float_t> vec_lang_1H;
std::vector<Float_t> vec_rang_1H;
std::vector<Float_t> vec_lang_2H;
std::vector<Float_t> vec_rang_2H;
TH1	*hist_mml1 = new TH1F("hist1", "hist mml1", 200, -10.0, 10.0);
TH1 *hist_mml2 = new TH1F("hist2", "hist mml2", 200, -10.0, 10.0);

TLorentzVector *lvHe6 = new TLorentzVector();
TLorentzVector *lvH1 = new TLorentzVector();
TLorentzVector *lvH2 = new TLorentzVector();
TVector3 vTarget(0.0, 0.0, 0.0);
TLorentzVector *lvTar1H = new TLorentzVector();
TLorentzVector *lvTar2H = new TLorentzVector();

void myFnc(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag);
void fitter();


void kniggit()
{
	TStopwatch *stopwatch = new TStopwatch();
	fitter();
	stopwatch->Print();
}

void fitter()
{
	TFitter *virtFit = new TFitter(2);
	virtFit->SetFCN(myFnc);
	virtFit->SetParameter(0, "sqlang", 3.5, 10.0, 2.0, 5.0);
	virtFit->SetParameter(1, "tar position", 0.0, 0.1, -15.0, 15.0);
	//virtFit->SetParameter(2, "tar thickness", 40.0, 0.5, 30.0, 50.0);
	virtFit->GetMinuit()->SetPrintLevel(2);
	Double_t inputArgs[3];
	virtFit->ExecuteCommand("MIGRAD", inputArgs, 3);
}

void myFnc(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag)
{
	lvTar1H->SetVectM(vTarget, cs::mass_1H);
	lvTar2H->SetVectM(vTarget, cs::mass_2H);
	printf("%f\t%f\n", inPar[0], inPar[1]);
	while (fReader.Next())
	{
	TLorentzVector *flvBeam = new TLorentzVector((*lvBeam).Px(), (*lvBeam).Py(), (*lvBeam).Pz(), (*lvBeam).E());

	
	if (*geo==2)
	{
		tar_pos_Z = cs::tar_pos_Z + 2.0  + inPar[1];
		tar_angle = 6.0 * cs::deg_to_rad;
		SQL_ang = (50.0 + inPar[0]) * cs::deg_to_rad;
		SQR_ang = (15.0) * cs::deg_to_rad;
		SQL_dist = cs::sql_dist_s2;
		SQR_dist = cs::sqr_dist_s2;
	}

	else
	{
		tar_pos_Z = cs::tar_pos_Z + inPar[1];	
		tar_angle = 45.0 * cs::deg_to_rad;
		SQL_ang = (65.0 + inPar[0]) * cs::deg_to_rad;
		SQR_ang = (15.0) * cs::deg_to_rad;
		SQL_dist = cs::sql_dist_s1;
		SQR_dist = cs::sqr_dist_s1;
	}

	X2H_lab = SQL_dist*sin(SQL_ang) + cs::SQL_start_X * cos(SQL_ang);
	Y2H_lab = cs::SQL_start_Y;
	Z2H_lab = SQL_dist*cos(SQL_ang) - cs::SQL_start_X * sin(SQL_ang);

	X2H_det = -cs::width_strip_X * (*SQX_L_sNo) * cos(SQL_ang);
	Y2H_det = cs::width_strip_Y * (*SQY_L_sNo);
	Z2H_det = cs::width_strip_X * (*SQX_L_sNo) * sin(SQL_ang);

	X2H = X2H_lab + X2H_det;
	Y2H = Y2H_lab + Y2H_det;
	Z2H = Z2H_lab + Z2H_det;

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
			ene_1H = *sqlde + cs::mass_1H;
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
			
			ene_2H = *sqlde + cs::mass_2H;
			mom_2H = sqrt(ene_2H*ene_2H-cs::mass_2H*cs::mass_2H);
			vectH.SetMag(mom_2H);
			lvH2->SetVectM(vectH, cs::mass_2H);
			*lvHe6 = *lvTar2H + *flvBeam - *lvH2;
			hist_mml2->Fill(lvHe6->M() - cs::mass_6He);	
			//printf("%f\t%f\t%f\n",*sqlde, sqlang, lvHe6->M() - cs::mass_6He);
		}

	}

	X6He_lab = SQR_dist*(sin(-SQR_ang)) - cs::SQR_start_X * cos(SQR_ang);
	Y6He_lab = cs::SQR_start_Y;
	Z6He_lab = SQR_dist*cos(SQR_ang) - cs::SQR_start_X * sin(SQR_ang);		

	X6He_det = cs::width_strip_X * (*SQX_R_sNo) * cos(SQR_ang);
	Y6He_det = cs::width_strip_Y * (*SQY_R_sNo);
	Z6He_det = cs::width_strip_X * (*SQX_R_sNo) * sin(SQR_ang);

	X6He = X6He_lab + X6He_det;
	Y6He = Y6He_lab + Y6He_det;
	Z6He = Z6He_lab + Z6He_det;

	TVector3 vect6He(X6He-*evX, Y6He-*evY, Z6He-*evZ);
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
	}

	fReader.Restart();
	//hist_mml1->Fit("gaus", "Q");
	hist_mml2->Fit("gaus", "Q");
	//fit1 = hist_mml1->GetFunction("gaus");
	fit2 = hist_mml2->GetFunction("gaus");
	//printf("%f\n", fit2->GetParameter(1));
	returner = fit2->GetParameter(1);

	delete lvHe6, lvH1, lvH2, lvTar1H, lvTar2H;
	printf("%f\n",hist_mml2->GetEntries() );
	hist_mml1->Reset();
	hist_mml2->Reset();
	
}