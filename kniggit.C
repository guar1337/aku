#include "TString.h"
#include "constants.h"

#include "ELCcpy/AELC.h"
#include "ELCcpy/ELC.h"
R__LOAD_LIBRARY(libgsl.so); 
R__LOAD_LIBRARY(/home/guar/aku/wrk/ELCcpy/build/libEloss.so);



TFile *inF = new TFile{"/home/guar/data/he6_d/dE/PG_geo.root", "READ"};
TTreeReader fReader("dE_angle", inF);

TTreeReaderValue<Float_t> SQX_L_sNo = {fReader, "SQX_L_sNo"};
TTreeReaderValue<Float_t> SQX_R_sNo = {fReader, "SQX_R_sNo"};
TTreeReaderValue<Float_t> SQY_L_sNo = {fReader, "SQY_L_sNo"};
TTreeReaderValue<Float_t> SQY_R_sNo = {fReader, "SQY_R_sNo"};
TTreeReaderValue<Double_t> fsqlde = {fReader, "sqlde"};
TTreeReaderValue<Double_t> sqletot = {fReader, "sqletot"};
//TTreeReaderValue<Double_t> sqlang = {fReader, "sqlang"};
TTreeReaderValue<Double_t> sqrde = {fReader, "sqrde"};
TTreeReaderValue<Double_t> sqretot = {fReader, "sqretot"};
//TTreeReaderValue<Double_t> sqrang = {fReader, "sqrang"};
//TTreeReaderValue<Float_t> evX = {fReader, "evX"};
//TTreeReaderValue<Float_t> evY = {fReader, "evY"};
//TTreeReaderValue<Float_t> evZ = {fReader, "evZ"};
TTreeReaderValue<Float_t> MWPC_1_X = {fReader, "MWPC_1_X"};
TTreeReaderValue<Float_t> MWPC_1_Y = {fReader, "MWPC_1_Y"};
TTreeReaderValue<Float_t> MWPC_1_Z = {fReader, "MWPC_1_Z"};
TTreeReaderValue<Float_t> dX = {fReader, "dX"};
TTreeReaderValue<Float_t> dY = {fReader, "dY"};
TTreeReaderValue<Float_t> dZ = {fReader, "dZ"};
TTreeReaderValue<Short_t> geo = {fReader, "geo"};
TTreeReaderValue<Bool_t> deu = {fReader, "deu"};
TTreeReaderValue<Bool_t> pro = {fReader, "pro"};
TTreeReaderValue<Bool_t> dEAngle = {fReader, "dEAngle"};
TTreeReaderValue<Double_t> kinE = {fReader, "kinE"};
TTreeReaderValue<TLorentzVector> lvBeam = {fReader, "LV_beam."};

Float_t tarPosZ, tarThcknss, tarAngle, SQLang, SQRang, SQLdist, SQRdist, lvsqlang, lvsqrang, tarThickness;
Float_t X2Hlab, Y2Hlab, Z2Hlab, X6Helab, Y6Helab, Z6Helab;
Float_t X2Hdet, Y2Hdet, Z2Hdet, X6Hedet, Y6Hedet, Z6Hedet;
Float_t evX, evY, evZ, Tcoef;
Float_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
Float_t sqlphi, sqltheta, sqrphi, sqrtheta, mml, sqlang, sqrang;
Float_t ene1H, ene2H, mom1H, mom2H;
Float_t fEproFromLang, fEdeuFromLang, fsqltheta_1H, fsqltheta_2H, fsqrang1H, fsqrang2H;
Float_t inputPars[4];
Float_t sqlde;
TRandom3 *rnd;
TGraph *langRang1H, *flangRang1H, *langRang2H, *flangRang2H, *dELang1H, *dELang2H;

int fnPar=1; Double_t fgin[2]; Double_t freturner; Int_t iflag;

int CD2_Nel=2;
Double_t CD2_A[2]={2, 12};
Double_t CD2_Z[2]={1, 6};
Double_t CD2_W[2]={2, 1};

int si_Nel=1;
Double_t si_A[1]={28};
Double_t si_Z[1]={14};
Double_t si_W[1]={1};

AELC *h1Si = new ELC(1, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
AELC *h1CD2 = new ELC(1, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);

AELC *h2Si = new ELC(2, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
AELC *h2CD2 = new ELC(2, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);

AELC *he6Si = new ELC(6, 2, si_Nel, 2.35, si_A, si_Z, si_W, 300.,1500);
AELC *he6CD2 = new ELC(6, 2, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 300.,1500);

TVector3 *vBeam, v6He;
//TLorentzVector *lvH1, *lvH2, *lvHe6, *lvTar1H, *lvTar2H;
TF1 *fit1, *fit2;

TH1	*histMml1 = new TH1F("hist1", "hist mml1", 1000, -50.0, 50.0);
TH1 *histMml2 = new TH1F("hist2", "hist mml2", 1000, -50.0, 50.0);

TF1 *angAngFit1H;
TF1 *angAngFit2H;
TF1 *angEFit1H;
TF1 *angEFit2H;

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

	angAngFit1H = new TF1("angAngFit1H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit1H->FixParameter(0, 2*TMath::DegToRad());
	angAngFit1H->FixParameter(1, cs::mass6He/cs::mass1H);
	angAngFit1H->FixParameter(2, TMath::RadToDeg());

	angAngFit2H = new TF1("angAngFit2H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit2H->FixParameter(0, 2*TMath::DegToRad());
	angAngFit2H->FixParameter(1, cs::mass6He/cs::mass2H);
	angAngFit2H->FixParameter(2, TMath::RadToDeg());

	angEFit1H = new TF1("angEFit1H", "[0]*(1.0/sqrt(1.0-pow(((2 * cos(x*[1])) / (1.0+[0])) * [2], 2.0))-1.0)*[3]");
	angEFit1H->FixParameter(0,cs::mass1H/cs::mass6He);
	angEFit1H->FixParameter(1,TMath::DegToRad());
	angEFit1H->FixParameter(2, 0.2388);
	angEFit1H->FixParameter(3,cs::mass6He);

	angEFit2H = new TF1("angEFit2H", "[0]*(1.0/sqrt(1.0-pow(((2 * cos(x*[1])) / (1.0+[0])) * [2], 2.0))-1.0)*[3]");
	angEFit2H->FixParameter(0,cs::mass2H/cs::mass6He);
	angEFit2H->FixParameter(1,TMath::DegToRad());
	angEFit2H->FixParameter(2, 0.2388);
	angEFit2H->FixParameter(3,cs::mass6He);


	Int_t fnPar = 8;
	Double_t finPar[fnPar];
	finPar[0] = 0.136211;
	finPar[1] = 2.68637;
	finPar[2] = 7.21955;
	finPar[3] = 1.41038;
	finPar[4] = 2.62977;
	finPar[5] = 1.86681;
	finPar[6] = -18.0818;
	finPar[7] = 11.0166;
	Double_t gin[1];
	Double_t returner;

	//myFnc(fnPar, gin, returner, finPar, 100);	
	fitter();

	stopwatch->Print();
	delete angAngFit1H, angAngFit2H;
}

void fitter()
{
	TFitter *virtFit = new TFitter(6);
	virtFit->SetFCN(myFnc);
	Double_t inputArgs[6];
	inputArgs[0] = 0.0;
	inputArgs[1] = 10.0;
	inputArgs[2] = 0.0;
	inputArgs[3] = 0.0;
	inputArgs[4] = 0.0;
	inputArgs[5] = 0.0;

	Double_t cmdPars[2]={1,0.01};
	virtFit->SetParameter(0, "tarShift", 		inputArgs[0], 0.1, -20.0, 20.0);
	virtFit->SetParameter(1, "tarShift 2", 		inputArgs[1], 0.1, -20.0, 20.0);
	virtFit->SetParameter(2, "Left det Shift",	inputArgs[2], 0.1, -20.0, 20.0);
	virtFit->SetParameter(3, "Right det Shift", inputArgs[3], 0.1, -20.0, 20.0);
	virtFit->SetParameter(4, "Left det dist", 	inputArgs[4], 0.1, -20.0, 20.0);
	virtFit->SetParameter(5, "Right det dist",	inputArgs[5], 0.1, -20.0, 20.0);
	
	virtFit->GetMinuit()->SetPrintLevel(2);
	Double_t prec[2] = {0.0001,1};
	virtFit->ExecuteCommand("SET EPSmachine", prec,1);
	virtFit->ExecuteCommand("MINImize", cmdPars, 0);

	fnPar = virtFit->GetNumberTotalParameters();
	Double_t finPar[fnPar];
	Double_t gin[1];
	Double_t returner;

	for (int iii = 0; iii < fnPar; ++iii)
	{
		finPar[iii] = virtFit->GetParameter(iii);
	}
	myFnc(fnPar, gin, returner, finPar, 100);

}

void myFnc(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag)
{
	std::vector<Float_t> vecLang1H;
	std::vector<Float_t> vecRang1H;
	std::vector<Float_t> vecfLang1H;
	std::vector<Float_t> vecfRang1H;

	std::vector<Float_t> vecLang2H;
	std::vector<Float_t> vecRang2H;
	std::vector<Float_t> vecfLang2H;
	std::vector<Float_t> vecfRang2H;

	std::vector<Float_t> vecDe1H;
	std::vector<Float_t> vecdELang1H;
	std::vector<Float_t> vecDe2H;
	std::vector<Float_t> vecdELang2H;

	histMml1->Reset();
	histMml2->Reset();
	lvTar1H->SetVectM(vTarget, cs::mass1H);
	lvTar2H->SetVectM(vTarget, cs::mass2H);
	int counter = -1;

	SQLdist = 170.0 + inPar[4];
	SQRdist = 250.0 + inPar[5];

	while (fReader.Next())
	{
		//if (*geo==1) continue;
		bool geoFlag = false;
		if (*geo==1)
		{
			tarPosZ = cs::tarPos + inPar[0];
			tarAngle = 45.0 * TMath::DegToRad();
			SQLang = (65.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();

			tarThickness = 80.0/* + inPar[6]*/;
		}

		else if(*geo==2)
		{
			tarPosZ = cs::tarPos + inPar[1];
			tarAngle = 6.0 * TMath::DegToRad();
			SQLang = (50.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			geoFlag = true;
			tarThickness = 80.0/* + inPar[6]*/;
		}

		else if(*geo==3)
		{
			tarPosZ = cs::tarPos + inPar[1];
			tarAngle = 0.0 * TMath::DegToRad();
			SQLang = (35.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 80.0/* + inPar[6]*/;
		}

		double tempE = he6Si->GetE((*lvBeam).E() - (*lvBeam).M(), 550.0);
		//printf("%f\n", tempE);
		tempE = he6CD2->GetE(tempE, tarThickness/2);
		TLorentzVector *flvBeam = new TLorentzVector((*lvBeam).Px(), (*lvBeam).Py(), (*lvBeam).Pz(), tempE + cs::mass6He);

		X2Hlab = SQLdist*sin(SQLang) + (cs::SQLstartX + inPar[2]) * cos(SQLang);
		Y2Hlab = cs::SQLstartY + cs::widthStripX;
		Z2Hlab = SQLdist*cos(SQLang) - (cs::SQLstartX + inPar[2]) * sin(SQLang);

		X2Hdet = cs::widthStripX * (*SQX_L_sNo) * cos(SQLang);
		Y2Hdet = cs::widthStripY * (*SQY_L_sNo);
		Z2Hdet = cs::widthStripX * (*SQX_L_sNo) * sin(SQLang);

		X2H = X2Hlab - X2Hdet;
		Y2H = Y2Hlab + Y2Hdet;
		Z2H = Z2Hlab + Z2Hdet;

		Tcoef=(cos(tarAngle)*tarPosZ-sin(tarAngle) * (*MWPC_1_X) - cos(tarAngle) * (*MWPC_1_Z)) / (sin(tarAngle) * (*dX) + cos(tarAngle) * (*dZ));

		evX = (*MWPC_1_X) + (*dX) * Tcoef;
		evY = (*MWPC_1_Y) + (*dY) * Tcoef;
		evZ = (*MWPC_1_Z) + (*dZ) * Tcoef;

		TVector3 vectH(X2H-evX, Y2H-evY, Z2H-evZ);
		sqlphi=vectH.Phi()*TMath::RadToDeg();
		sqltheta=vectH.Theta()*TMath::RadToDeg();
		sqlang = vectH.Angle(flvBeam->Vect())*TMath::RadToDeg();

		X6Helab = SQRdist*(sin(-SQRang)) - (cs::SQRstartX + inPar[3]) * cos(SQRang);
		Y6Helab = cs::SQRstartY;
		Z6Helab = SQRdist*cos(SQRang) - (cs::SQRstartX + inPar[3]) * sin(SQRang);

		X6Hedet = cs::widthStripX * (*SQX_R_sNo) * cos(SQRang);
		Y6Hedet = cs::widthStripY * (*SQY_R_sNo);
		Z6Hedet = cs::widthStripX * (*SQX_R_sNo) * sin(SQRang);

		X6He = X6Helab + X6Hedet;
		Y6He = Y6Helab + Y6Hedet;
		Z6He = Z6Helab + Z6Hedet;

		TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
		sqrtheta=vect6He.Theta()*TMath::RadToDeg();
		sqrphi=vect6He.Phi()*TMath::RadToDeg();
		sqrang = vect6He.Angle(flvBeam->Vect())*TMath::RadToDeg();

		sqlde = *fsqlde;
		if (*pro==1)
		{
			vecLang1H.push_back(sqlang);
			vecRang1H.push_back(sqrang);
			if (geoFlag)
			{
				vecfLang1H.push_back(sqlang);
				vecfRang1H.push_back(sqrang);
			}


			if (*sqletot==0 && *fsqlde>2.0 && sqlang>60.0 && *dEAngle)
			{
				sqlde = h1Si->GetE(*fsqlde, -3.5);
				sqlde = h1CD2->GetE(sqlde, -tarThickness/(2*cos(sqlang*TMath::DegToRad()-tarAngle)));
				ene1H = sqlde + cs::mass1H;
				mom1H = sqrt(ene1H*ene1H-cs::mass1H*cs::mass1H);
				vectH.SetMag(mom1H);
				lvH1->SetVectM(vectH, cs::mass1H);
				*lvHe6 = *lvTar1H + *flvBeam - *lvH1;
				histMml1->Fill(lvHe6->M() - cs::mass6He);
				vecDe1H.push_back(sqlde);
				vecdELang1H.push_back(sqlang);
			}

		}



		if (*deu==1)
		{

			vecLang2H.push_back(sqlang);
			vecRang2H.push_back(sqrang);
			if (geoFlag)
			{
				vecfLang2H.push_back(sqlang);
				vecfRang2H.push_back(sqrang);
			}


			if (*sqletot==0 && *fsqlde>3.0 && sqlang>60.0 && *dEAngle)
			{
				sqlde = h2Si->GetE(*fsqlde, -3.0);
				sqlde = h2CD2->GetE(sqlde, -tarThickness/(2*cos(sqlang*TMath::DegToRad()-tarAngle)));
				ene2H = sqlde + cs::mass2H;
				mom2H = sqrt(ene2H*ene2H-cs::mass2H*cs::mass2H);
				vectH.SetMag(mom2H);
				lvH2->SetVectM(vectH, cs::mass2H);
				*lvHe6 = *lvTar2H + *flvBeam - *lvH2;
				histMml2->Fill(lvHe6->M() - cs::mass6He);
				vecDe2H.push_back(sqlde);
				vecdELang2H.push_back(sqlang);
				//printf("%f\t%f\t%f\n",*sqlde, sqlang, lvHe6->M() - cs::mass_6He);
			}

		}
	//delete flvBeam;
	}

	fReader.Restart();
	//histMml1->Rebin();
	//histMml2->Rebin();

	//printf("%f\t%f\n", fit2->GetParameter(1), inPar[0]);
	
	langRang1H =  new TGraph(vecLang1H.size(), &vecLang1H[0], &vecRang1H[0]);
	flangRang1H =  new TGraph(vecfLang1H.size(), &vecfLang1H[0], &vecfRang1H[0]);
	langRang1H->Fit(angAngFit1H, "QN0");
	langRang2H =  new TGraph(vecLang2H.size(), &vecLang2H[0], &vecRang2H[0]);
	flangRang2H =  new TGraph(vecfLang2H.size(), &vecfLang2H[0], &vecfRang2H[0]);
	langRang2H->Fit(angAngFit2H, "QN0");

	dELang1H =  new TGraph(vecDe1H.size(), &vecdELang1H[0], &vecDe1H[0]);
	//dELang1H->Fit(angAngFit1H, "QN0");
	dELang2H =  new TGraph(vecDe2H.size(), &vecdELang2H[0], &vecDe2H[0]);
	//dELang2H->Fit(angAngFit1H, "QN0");
/*
	histMml1->Fit("gaus", "QO");
	histMml2->Fit("gaus", "QO");

	dELang1H->Fit(angEFit1H,"QNO");
	dELang2H->Fit(angEFit2H,"QNO");

	fit1 = histMml1->GetFunction("gaus");
	fit2 = histMml2->GetFunction("gaus");

	double missM1 = abs(histMml1->GetFunction("gaus")->GetParameter(1));
	double missM2 = abs(histMml2->GetFunction("gaus")->GetParameter(1));*/

	double angAng1H = angAngFit1H->GetChisquare();
	double angAng2H = angAngFit2H->GetChisquare();
	double dEAng1H = angEFit1H->GetChisquare();
	double dEAng2H = angEFit2H->GetChisquare();
	
	//printf("%f\t%f\n", angAng1H, angAng2H);
	if (iflag == 100)
	{
		printf("Am I here?\n");
		TCanvas *myCanvas = new TCanvas("myCanvas", "Minimize results", 1200, 800);
		myCanvas->Divide(3,2);

		myCanvas->cd(1);
		langRang1H->Draw("AP");
		flangRang1H->SetMarkerColor(kRed);
		langRang1H->Fit(angAngFit1H, "Q");
		flangRang1H->Draw("P,same");

		myCanvas->cd(2);
		histMml1->Draw("");
		histMml1->Fit("gaus", "");

		myCanvas->cd(3);
		dELang1H->Draw("AP");
		dELang1H->Fit(angEFit1H,"Q");
		
		myCanvas->cd(4);
		langRang2H->Draw("AP");
		langRang2H->Fit(angAngFit2H, "Q");
		flangRang2H->SetMarkerColor(kRed);
		flangRang2H->Draw("P,same");

		myCanvas->cd(5);
		histMml2->Draw("");
		histMml2->Fit("gaus", "");

		myCanvas->cd(6);
		dELang2H->Draw("AP");
		dELang2H->Fit(angEFit2H,"Q");
	}

	//printf("%f\t%f\t%f\t%f\t%f\n", fit2->GetParameter(2), inPar[0], inPar[1], inPar[2], inPar[3]);
	returner = angAng1H + angAng2H/* + missM1 + missM2*/;
	//returner = dEAng2H;
	//printf("%f\t%f\t%f\t%f\t%f\n", result_1H, result_2H, fit1->GetParameter(1), fit2->GetParameter(1));

	delete lvHe6, lvH1, lvH2, lvTar1H, lvTar2H, langRang1H, langRang2H;
}