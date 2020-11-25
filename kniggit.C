#include "TString.h"
#include "constants.h"

#include "ELC/AELC.h"
#include "ELC/ELC.h"
R__LOAD_LIBRARY(libgsl.so); 
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC/build/libEloss.so);

#include "TH1.h"
#include "TFile.h"
#include "TTreeReader.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TFitter.h"
#include "TStopwatch.h"
#include "TCanvas.h"
#include "TMinuit.h"
#include "TMath.h"


TH1	*histMml1 = new TH1F("hist1", "hist mml1", 1000, -20.0, 20.0);
TH1 *histMml2 = new TH1F("hist2", "hist mml2", 1000, -20.0, 20.0);


TFile *inF = new TFile{"/home/zalewski/data/bank/dE/PG_geo.root", "READ"};
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
TTreeReaderValue<Float_t> MWPC_2_X = {fReader, "MWPC_2_X"};
TTreeReaderValue<Float_t> MWPC_2_Y = {fReader, "MWPC_2_Y"};
TTreeReaderValue<Float_t> MWPC_2_Z = {fReader, "MWPC_2_Z"};
TTreeReaderValue<Short_t> geo = {fReader, "geo"};
TTreeReaderValue<Bool_t> deu = {fReader, "deu"};
TTreeReaderValue<Bool_t> pro = {fReader, "pro"};
TTreeReaderValue<Bool_t> dEAngle = {fReader, "dEAngle"};
TTreeReaderValue<Double_t> kinE = {fReader, "kinE"};
TTreeReaderValue<Bool_t> kineProB = {fReader, "kineProB"};
TTreeReaderValue<Bool_t> kineDeuB = {fReader, "kineDeuB"};
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
TGraph *langRang1H, *flangRang1H, *langRang2H, *flangRang2H, *dELang1H, *dELang2H, *angang1H, *angang2H, *resGAngAng1, *resGAngAng2;
TGraph *resGAngAng1geo3, *resGAngAng2geo3;

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

TGraph *tmpLangRang1H;
TLorentzVector *lvHe6 = new TLorentzVector();
TLorentzVector *lvH1 = new TLorentzVector();
TLorentzVector *lvH2 = new TLorentzVector();
TVector3 vTarget(0.0, 0.0, 0.0);
TLorentzVector *lvTar1H = new TLorentzVector();
TLorentzVector *lvTar2H = new TLorentzVector();

void myFnc(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag);
void fitter();

Double_t myAngAngFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam)
{
	TLorentzVector m_lvBeamCopy(m_lvBeam);
	TLorentzVector m_TarCM{0.0,0.0,0.0,tarMass};
	TLorentzVector m_lvCM = m_lvBeam + m_TarCM;
	Double_t m_Theta = m_lvCM.Theta();
	TVector3 boostVect = m_lvCM.BoostVector();
	
	Double_t gammaSquare = m_lvCM.Gamma() *  m_lvCM.Gamma();
	Double_t tanSquare = pow(tan(m_leftAngle*TMath::DegToRad()),2);
	Double_t cosLeftAng = (1.0 - gammaSquare*tanSquare)/(1 + gammaSquare*tanSquare);
	Double_t thetaCM = TMath::Pi() - (acos(cosLeftAng)-m_Theta);

	m_lvBeam.Boost(-boostVect);
	//printf("TMath::Pi(): %f\tthetaCM: %f\tlAng: %f\n",TMath::Pi()*TMath::RadToDeg(), thetaCM*TMath::RadToDeg(), m_leftAngle);
	m_lvBeam.SetTheta(thetaCM);
	m_lvBeam.Boost(boostVect);
/*
	m_TarCM.Boost(-boostVect);
	m_TarCM.SetTheta(acos(cosLeftAng)-m_Theta);
	m_TarCM.Boost(boostVect);
	/*printf("sqlangIN: %f\tsqlangOUT: %f\tdiff: %f\tm_Theta: %f\n",m_leftAngle, m_TarCM.Vect().Angle(m_lvBeamCopy.Vect())*TMath::RadToDeg(), m_leftAngle-m_TarCM.Vect().Angle(m_lvBeamCopy.Vect())*TMath::RadToDeg(),m_Theta*TMath::RadToDeg());
*/
	return m_lvBeam.Vect().Angle(m_lvBeamCopy.Vect())*TMath::RadToDeg();
}

Double_t myAngEneFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam)
{
	TLorentzVector m_TarCM{0.0,0.0,0.0,tarMass};
	TLorentzVector m_lvCM = m_lvBeam + m_TarCM;
	Double_t m_Theta = m_lvCM.Theta();
	TVector3 boostVect = m_lvCM.BoostVector();

	Double_t gammaSquare = m_lvCM.Gamma() *  m_lvCM.Gamma();
	Double_t tanSquare = pow(tan(m_leftAngle*TMath::DegToRad()),2);
	Double_t cosLeftAng = (1.0 - gammaSquare*tanSquare)/(1 + gammaSquare*tanSquare);
	Double_t thetaCM = acos(cosLeftAng);

	m_TarCM.Boost(-boostVect);
	m_TarCM.SetTheta(acos(cosLeftAng)-m_Theta);
	m_TarCM.Boost(boostVect);

	return m_TarCM.E()-m_TarCM.M();
}


void kniggit()
{
	TStopwatch *stopwatch = new TStopwatch();

	//myFnc(nPar, gin, returner, inPar, 100);	
		int nPar = 17;
	TFitter *virtFit = new TFitter(nPar);
	virtFit->SetFCN(myFnc);
	//virtFit->SetFitMethod("loglikelihood");
	Double_t inputArgs[nPar];
	std::fill(inputArgs, inputArgs+nPar,0.0);

	virtFit->SetParameter(0, "MWPC1_X_displacement", 	inputArgs[0], 0.1, -5.0, 5.0);
	virtFit->SetParameter(1, "MWPC1_Y_displacement", 	inputArgs[1], 0.1, -5.0, 5.0);
	virtFit->SetParameter(2, "MWPC2_X_displacement",	inputArgs[2], 0.1, -5.0, 5.0);
	virtFit->SetParameter(3, "MWPC2_Y_displacement", 	inputArgs[3], 0.1, -5.0, 5.0);

	virtFit->SetParameter(4, "leftDetShift",	inputArgs[4], 0.1, -50.0, 50.0);
	virtFit->SetParameter(5, "rightDetShift",	inputArgs[5], 0.1, -50.0, 50.0);
	virtFit->SetParameter(6, "leftDetDist", 	inputArgs[6], 0.1, -50.0, 50.0);
	virtFit->SetParameter(7, "rightDetDist",	inputArgs[7], 0.1, -50.0, 50.0);

	virtFit->SetParameter(8, "rightAngShift",	inputArgs[8], 0.1, -50.0, 50.0);

	virtFit->SetParameter(9, "leftAngShift1",	inputArgs[9], 0.1, -50.0, 50.0);
	virtFit->SetParameter(10, "leftAngShift2",	inputArgs[10], 0.1, -50.0, 50.0);
	virtFit->SetParameter(11, "leftAngShift3",	inputArgs[11], 0.1, -50.0, 50.0);

	virtFit->SetParameter(12, "tarThicknessShift",	inputArgs[12], 0.1, -50.0, 50.0);
	virtFit->SetParameter(13, "tarPos", 			inputArgs[13], 0.1, -5.0, 5.0);
	
	virtFit->GetMinuit()->SetPrintLevel(2);
	virtFit->GetMinuit()->SetMaxIterations(50000);
	Double_t prec[2] = {0.0001,1};
	Double_t cmdPars[2]={20000,0.00001};
	//virtFit->ExecuteCommand("SET EPSmachine", prec,1);
	printf("%d\n",virtFit->GetMinuit()->GetMaxIterations());
	//virtFit->ExecuteCommand("migrad", cmdPars, 0);

	fnPar = virtFit->GetNumberTotalParameters();
	Double_t finPar[fnPar];
	Double_t m_gin[1];
	Double_t m_returner;
	Int_t m_nPar = 16;
	Double_t inPar[m_nPar];

	
		inPar[0] = -4.0;	//X1
	inPar[1] = -2.1375;	//Y1
		inPar[2] = -2.2;	//X2
	inPar[3] = -2.125;	//Y2
	//X1
		inPar[4] = 4.0;		//Lshift
		inPar[5] = 3.0;		//Rshift
	inPar[6] = 0.0;		//Ldist
	inPar[7] = 0.0;		//Rdist
	inPar[8] = 0.0;		//Rang
	inPar[9] = 1.0;		//Lang1
	inPar[10] = 1.0;	//Lang2
	inPar[11] = 1.0;	//Lang3
	inPar[12] = 0.0;
	inPar[13] = 0.0;
	inPar[14] = 0.0;
	inPar[15] = 0.0;

	Double_t gin[1];
	Double_t returner;
	ofstream outStream("/home/zalewski/aku/wrk/pars.dat", ios_base::trunc);
	if (!outStream) 
	{
		printf ("#Cannot open %s coefficient file\n","/home/zalewski/aku/wrk/pars.dat");
	}

	for (int iii = 0; iii < fnPar; ++iii)
	{
		finPar[iii] = virtFit->GetParameter(iii);
		outStream<<"\tstatic const float\t"<<virtFit->GetParName(iii)<<" = "<<finPar[iii]<<";\n";
		if (iii == 3 || iii == 5 || iii == 7 || iii == 10 || iii == 13)
		{
			outStream<<"\n";
		}
	}

	myFnc(m_nPar, m_gin, m_returner, inPar, 100);
	//myFnc(fnPar, m_gin, m_returner, finPar, 100);


	stopwatch->Print();
	delete inF;
	delete histMml1;
	delete histMml2;
	delete h1Si;
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

	std::vector<Float_t> resAngAng1;
	std::vector<Float_t> resAngAng2;
	std::vector<Float_t> resAngE1;
	std::vector<Float_t> resAngE2;

	std::vector<Float_t> sqlang1;
	std::vector<Float_t> sqrang1;
	std::vector<Float_t> sqlang2;
	std::vector<Float_t> sqrang2;

	std::vector<Float_t> tmpRang1;
	std::vector<Float_t> tmpRang2;

	std::vector<Float_t> resAngAng1geo3;
	std::vector<Float_t> resAngAng2geo3;

	histMml1->Reset();
	histMml2->Reset();
	lvTar1H->SetVectM(vTarget, cs::mass1H);
	lvTar2H->SetVectM(vTarget, cs::mass2H);

	Double_t sqrang1Hresidual{0.0};
	Double_t sqrang2Hresidual{0.0};
	Double_t angDE1Hresidual{0.0};
	Double_t angDE2Hresidual{0.0};

	Double_t chiSquareAngAng1H{0.0};
	Double_t chiSquareAngAng2H{0.0};
	Double_t chiSquareAngE1H{0.0};
	Double_t chiSquareAngE2H{0.0};

	int counter = -1;

	SQLdist = 170.0;
	SQRdist = 250.0;
	double X6He_bank = -50.0;
	double innerRShift = 0.0;

	while (fReader.Next())
	{
		//if (*geo!=3) continue;
		bool geoFlag = false;
		if (*geo==1)
		{
			tarPosZ = 0.0;
			tarAngle = (45.0)* TMath::DegToRad();
			SQLang = (65.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 80.0 + inPar[12];
		}

		else if(*geo==2)
		{
			tarPosZ = 2.0;
			tarAngle = (6.0)* TMath::DegToRad();
			SQLang = (50.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 160.0 + 2*inPar[12];
		}

		else if(*geo==3)
		{
			tarPosZ = 2.0;
			tarAngle = (0.0) * TMath::DegToRad();
			SQLang = (35.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 160.0 + 2*inPar[12];
			geoFlag = true;
		}

		double tempE = he6Si->GetE((*lvBeam).E() - (*lvBeam).M(), 644.0);
		//printf("%f\n", tempE);
		tempE = he6CD2->GetE(tempE, tarThickness/(2*cos(tarAngle)));
		double eneBeam = tempE + cs::mass6He;
		double momBeam = sqrt(eneBeam*eneBeam-cs::mass6He*cs::mass6He);
		double fMWPC_1_X = *MWPC_1_X + inPar[0];
		double fMWPC_1_Y = *MWPC_1_Y + inPar[1];
		double fMWPC_2_X = *MWPC_2_X + inPar[2];
		double fMWPC_2_Y = *MWPC_2_Y + inPar[3];

		double dX = fMWPC_2_X - fMWPC_1_X;
		double dY = fMWPC_2_Y - fMWPC_1_Y;
		double dZ = *MWPC_2_Z - *MWPC_1_Z;

		TVector3 tarPoint(0.0, 0.0, tarPosZ);
		TVector3 beamPoint(fMWPC_2_X, fMWPC_2_Y, *MWPC_2_Z);
		TVector3 tarPerpendicular(sin(tarAngle), 0.0, cos(tarAngle));
		TVector3 vBeam(dX, dY, dZ);
		double dCoeff = ((tarPoint-beamPoint).Dot(tarPerpendicular))/(vBeam.Dot(tarPerpendicular));
				
		vBeam.SetMag(momBeam);
		TLorentzVector *flvBeam = new TLorentzVector();
		flvBeam->SetVectM(vBeam,cs::mass6He);

		X2Hlab = SQLdist*sin(SQLang) + (cs::SQLstartX + inPar[4]) * cos(SQLang);
		Y2Hlab = cs::SQLstartY + cs::widthStripX;
		Z2Hlab = SQLdist*cos(SQLang) - (cs::SQLstartX + inPar[4]) * sin(SQLang);

		X2Hdet = cs::widthStripX * (*SQX_L_sNo) * cos(SQLang);
		Y2Hdet = cs::widthStripY * (*SQY_L_sNo);
		Z2Hdet = cs::widthStripX * (*SQX_L_sNo) * sin(SQLang);

		X2H = X2Hlab - X2Hdet;
		Y2H = Y2Hlab + Y2Hdet;
		Z2H = Z2Hlab + Z2Hdet;

		evX = fMWPC_2_X + dX * dCoeff;
		evY = fMWPC_2_Y + dY * dCoeff;
		evZ = *MWPC_2_Z + dZ * dCoeff;

		TVector3 vectH(X2H-evX, Y2H-evY, Z2H-evZ);
		sqlphi=vectH.Phi()*TMath::RadToDeg();
		sqltheta=vectH.Theta()*TMath::RadToDeg();
		sqlang = vectH.Angle(flvBeam->Vect())*TMath::RadToDeg();

		X6Helab = SQRdist*sin(-SQRang) - (cs::SQRstartX + inPar[5]) * cos(SQRang);
		Y6Helab = cs::SQRstartY;
		Z6Helab = SQRdist*cos(SQRang) - (cs::SQRstartX + inPar[5]) * sin(SQRang);

		X6Hedet = cs::widthStripX * (*SQX_R_sNo) * cos(SQRang);
		Y6Hedet = cs::widthStripY * (*SQY_R_sNo);
		Z6Hedet = cs::widthStripX * (*SQX_R_sNo) * sin(SQRang);

		X6He = X6Helab + X6Hedet;
		Y6He = Y6Helab + Y6Hedet;
		Z6He = Z6Helab + Z6Hedet;
/*
		printf("X2Hlab: %f\tY2Hlab: %f\tZ2Hlab: %f\t\n", X2Hlab, Y2Hlab, Z2Hlab);
		printf("X2Hdet: %f\tY2Hdet: %f\tZ2Hdet: %f\t\n", X2Hdet, Y2Hdet, Z2Hdet);
		printf("X6Helab: %f\tY6Helab: %f\tZ6Helab: %f\t\n", X6Helab, Y6Helab, Z6Helab);
		printf("X6Hedet: %f\tY6Hedet: %f\tZ6Hedet: %f\t\n\n", X6Hedet, Y6Hedet, Z6Hedet);
*/
		if (X6He>X6He_bank)
		{
			X6He_bank = X6He;
		}

		TVector3 vect6He(X6He-evX, Y6He-evY, Z6He-evZ);
		sqrtheta=vect6He.Theta()*TMath::RadToDeg();
		sqrphi=vect6He.Phi()*TMath::RadToDeg();
		sqrang = vect6He.Angle(flvBeam->Vect())*TMath::RadToDeg();

		sqlde = *fsqlde;
		if (*pro==1)
		{
			vecLang1H.push_back(sqlang);
			vecRang1H.push_back(sqrang);

			sqrang1Hresidual = sqrang-myAngAngFit(sqlang, cs::mass1H, *flvBeam);

			chiSquareAngAng1H += pow(4,1+abs(sqrang1Hresidual));
			resAngAng1.push_back(sqrang1Hresidual);
			tmpRang1.push_back(myAngAngFit(sqlang, cs::mass1H, *flvBeam));

			if (geoFlag)
			{
				vecfLang1H.push_back(sqlang);
				vecfRang1H.push_back(sqrang);
				resAngAng1geo3.push_back(sqrang1Hresidual);
			}

			if (*sqletot==0 && *kineProB && *fsqlde>3.0 && (*geo==1 || *geo==2))
			{
				sqlde = h1Si->GetE(*fsqlde, -3.5);
				sqlde = h1CD2->GetE(sqlde, -tarThickness/(2*cos(SQLang*TMath::DegToRad()-tarAngle)));
				/*
				ene1H = sqlde + cs::mass1H;
				mom1H = sqrt(ene1H*ene1H-cs::mass1H*cs::mass1H);
				vectH.SetMag(mom1H);
				lvH1->SetVectM(vectH, cs::mass1H);
				*lvHe6 = *lvTar1H + *flvBeam - *lvH1;
				histMml1->Fill(lvHe6->M() - cs::mass6He);
				*/
				angDE1Hresidual = sqlde - myAngEneFit(sqlang, cs::mass1H, *flvBeam);
				chiSquareAngE1H += angDE1Hresidual*angDE1Hresidual;
				resAngE1.push_back(angDE1Hresidual);

				vecDe1H.push_back(sqlde);
				vecdELang1H.push_back(sqlang);
			}

		}



		if (*deu==1)
		{

			vecLang2H.push_back(sqlang);
			vecRang2H.push_back(sqrang);

			sqrang2Hresidual = sqrang-myAngAngFit(sqlang, cs::mass2H, *flvBeam);

			chiSquareAngAng2H += pow(4,1+abs(sqrang2Hresidual));
			resAngAng2.push_back(sqrang2Hresidual);
			tmpRang2.push_back(myAngAngFit(sqlang, cs::mass2H, *flvBeam));

			if (geoFlag)
			{
				vecfLang2H.push_back(sqlang);
				vecfRang2H.push_back(sqrang);
				resAngAng2geo3.push_back(sqrang2Hresidual);
			}


			if (*sqletot==0 && *kineDeuB && *fsqlde>3.0 && (*geo==1 || *geo==2))
			{
				sqlde = h2Si->GetE(*fsqlde, -3.5);
				sqlde = h2CD2->GetE(sqlde, -tarThickness/(2*cos(SQLang*TMath::DegToRad()-tarAngle)));
				/*
				ene2H = sqlde + cs::mass2H;
				mom2H = sqrt(ene2H*ene2H-cs::mass2H*cs::mass2H);
				vectH.SetMag(mom2H);
				lvH2->SetVectM(vectH, cs::mass2H);
				*lvHe6 = *lvTar2H + *flvBeam - *lvH2;
				histMml2->Fill(lvHe6->M() - cs::mass6He);
				*/
				angDE2Hresidual = sqlde - myAngEneFit(sqlang, cs::mass2H, *flvBeam);
				chiSquareAngE2H += angDE2Hresidual*angDE2Hresidual;
				resAngE2.push_back(angDE2Hresidual);

				vecDe2H.push_back(sqlde);
				vecdELang2H.push_back(sqlang);
			}

		}
/*		if (iflag==100)
		{
			rnd = new TRandom3();

			for (int i = 0; i < 5000; ++i)
			{
				double theta_CM = rnd->Uniform(0.0,TMath::Pi());
				Double_t tmpEne = 150.0;
				Double_t tmpMom = sqrt(pow((tmpEne+cs::mass6He),2)-cs::mass6He*cs::mass6He);
				TLorentzVector tmplvbeam(0.0,0.0,tmpMom,cs::mass6He+tmpEne);
				TLorentzVector lv6He_EL = tmplvbeam;
				TLorentzVector lv1H_EL(0,0,0,cs::mass1H);
				TLorentzVector lvCM_EL = lv6He_EL+lv1H_EL;
				TVector3 boostVect_EL = lvCM_EL.BoostVector();

				lv6He_EL.Boost(-boostVect_EL);
				lv1H_EL.Boost(-boostVect_EL);

				lv6He_EL.SetTheta(TMath::Pi()-theta_CM);
				lv1H_EL.SetTheta(theta_CM);

				lv6He_EL.Boost(boostVect_EL);
				lv1H_EL.Boost(boostVect_EL);
				sqlang1.push_back(180.0 * (tmplvbeam.Angle(lv1H_EL.Vect()))/double(TMath::Pi()));
				sqrang1.push_back(180.0 * (tmplvbeam.Angle(lv6He_EL.Vect()))/double(TMath::Pi()));
			}

			for (int i = 0; i < 5000; ++i)
			{
				double theta_CM = rnd->Uniform(0.0,TMath::Pi());
				Double_t tmpEne = 150.0;
				Double_t tmpMom = sqrt(pow((tmpEne+cs::mass6He),2)-cs::mass6He*cs::mass6He);
				TLorentzVector tmplvbeam(0.0,0.0,tmpMom,cs::mass6He+tmpEne);
				TLorentzVector lv6He_EL = tmplvbeam;
				TLorentzVector lv2H_EL(0,0,0,cs::mass2H);
				TLorentzVector lvCM_EL = lv6He_EL+lv2H_EL;
				TVector3 boostVect_EL = lvCM_EL.BoostVector();

				lv6He_EL.Boost(-boostVect_EL);
				lv2H_EL.Boost(-boostVect_EL);

				lv6He_EL.SetTheta(TMath::Pi()-theta_CM);
				lv2H_EL.SetTheta(theta_CM);

				lv6He_EL.Boost(boostVect_EL);
				lv2H_EL.Boost(boostVect_EL);
				sqlang2.push_back(180.0 * (tmplvbeam.Angle(lv2H_EL.Vect()))/double(TMath::Pi()));
				sqrang2.push_back(180.0 * (tmplvbeam.Angle(lv6He_EL.Vect()))/double(TMath::Pi()));
			}

		}
	*/delete flvBeam;
	}

	fReader.Restart();

	if (iflag == 100)
	{
		std::vector<Float_t> cpySqlang1(vecLang1H);
		std::vector<Float_t> cpySqlang2(vecLang2H);
		std::vector<Float_t> cpy2Sqlang1(vecfLang1H);
		std::vector<Float_t> cpy2Sqlang2(vecfLang2H);

		tmpLangRang1H =  new TGraph(cpySqlang1.size(), &cpySqlang1[0], &tmpRang1[0]);
		//angang1H =  new TGraph(sqlang1.size(), &sqlang1[0], &sqrang1[0]);

		TGraph *langRang1H =  new TGraph(vecLang1H.size(), &vecLang1H[0], &vecRang1H[0]);
		langRang1H->SetTitle("Angle-angle relation for {}^{1}H and {}^{6}He");
		langRang1H->GetXaxis()->SetTitle("protons LAB angle [deg]");
		langRang1H->GetXaxis()->CenterTitle();
		langRang1H->GetYaxis()->SetTitle("{}^{6}He LAB angle [deg]");
		langRang1H->GetYaxis()->CenterTitle();

		dELang1H =  new TGraph(vecDe1H.size(), &vecdELang1H[0], &vecDe1H[0]);
		dELang1H->SetTitle("Energy-angle relation for protons");
		dELang1H->GetXaxis()->SetTitle("LAB angle of protons [deg]");
		dELang1H->GetXaxis()->CenterTitle();
		dELang1H->GetYaxis()->SetTitle("protons energy loss in Si det [MeV]");
		dELang1H->GetYaxis()->CenterTitle();

		TGraph *flangRang1H =  new TGraph(vecfLang1H.size(), &vecfLang1H[0], &vecfRang1H[0]);
		TGraph *resGAngAng1 = new TGraph(vecLang1H.size(), &vecLang1H[0],  &resAngAng1[0]);
		resGAngAng1->SetTitle("{}^{6}He angle deviation based on beam energy and {}^{1}H angle");
		resGAngAng1->GetXaxis()->SetTitle("LAB angle of protons [deg]");
		resGAngAng1->GetXaxis()->CenterTitle();
		resGAngAng1->GetYaxis()->SetTitle("LAB angle deviation of protons [deg]");
		resGAngAng1->GetYaxis()->CenterTitle();

		TGraph *resGAngAng1geo3 = new TGraph(cpy2Sqlang1.size(), &cpy2Sqlang1[0],  &resAngAng1geo3[0]);

		TGraph *resGAngE1 = new TGraph(vecdELang1H.size(), &vecdELang1H[0],  &resAngE1[0]);
		resGAngE1->SetTitle("{}^{1}H Energy deviation based on Eloss in Si det and {}^{1}H angle");
		resGAngE1->GetXaxis()->SetTitle("LAB angle of protons [deg]");
		resGAngE1->GetXaxis()->CenterTitle();
		resGAngE1->GetYaxis()->SetTitle("energy deviation for protons [MeV]");
		resGAngE1->GetYaxis()->CenterTitle();

		//@@@@@		deuter
		TGraph *tmpLangRang2H =  new TGraph(cpySqlang2.size(), &cpySqlang2[0], &tmpRang2[0]);
		//angang2H =  new TGraph(sqlang2.size(), &sqlang2[0], &sqrang2[0]);

		TGraph *langRang2H =  new TGraph(vecLang2H.size(), &vecLang2H[0], &vecRang2H[0]);
		langRang2H->SetTitle("Angle-angle relation for {}^{2}H and {}^{6}He");
		langRang2H->GetXaxis()->SetTitle("deuteron LAB angle [deg]");
		langRang2H->GetXaxis()->CenterTitle();
		langRang2H->GetYaxis()->SetTitle("{}^{6}He LAB angle [deg]");
		langRang2H->GetYaxis()->CenterTitle();

		dELang2H =  new TGraph(vecDe2H.size(), &vecdELang2H[0], &vecDe2H[0]);
		dELang2H->SetTitle("Energy-angle relation for deuterons");
		dELang2H->GetXaxis()->SetTitle("LAB angle of deuterons [deg]");
		dELang2H->GetXaxis()->CenterTitle();
		dELang2H->GetYaxis()->SetTitle("deuterons energy loss in Si det [MeV]");
		dELang2H->GetYaxis()->CenterTitle();

		TGraph *flangRang2H =  new TGraph(vecfLang2H.size(), &vecfLang2H[0], &vecfRang2H[0]);
		TGraph *resGAngAng2 = new TGraph(vecLang2H.size(), &vecLang2H[0],  &resAngAng2[0]);
		resGAngAng2->SetTitle("{}^{6}He angle deviation based on beam energy and {}^{2}H angle");
		resGAngAng2->GetXaxis()->SetTitle("LAB angle of deuterons [deg]");
		resGAngAng2->GetXaxis()->CenterTitle();
		resGAngAng2->GetYaxis()->SetTitle("LAB angle deviation of deuterons [deg]");
		resGAngAng2->GetYaxis()->CenterTitle();

		TGraph *resGAngAng2geo3 = new TGraph(cpy2Sqlang2.size(), &cpy2Sqlang2[0],  &resAngAng2geo3[0]);

		TGraph *resGAngE2 = new TGraph(vecdELang2H.size(), &vecdELang2H[0],  &resAngE2[0]);
		resGAngE2->SetTitle("{}^{2}H Energy deviation based on Eloss in Si det and {}^{2}H angle");
		resGAngE2->GetXaxis()->SetTitle("LAB angle of deuterons [deg]");
		resGAngE2->GetXaxis()->CenterTitle();
		resGAngE2->GetYaxis()->SetTitle("energy deviation for deuterons [MeV]");
		resGAngE2->GetYaxis()->CenterTitle();

		printf("%f\n",X6He_bank);
		printf("Am I here?\n");
		TCanvas *myCanvas = new TCanvas("myCanvas", "Minimize results", 1200, 800);
		TCanvas *myResPlotsCanv = new TCanvas("myResPlots", "residual plot", 1200, 800);
		myCanvas->Divide(2,2);
		myResPlotsCanv->Divide(2,2);

		myCanvas->cd(1);
		langRang1H->Draw("AP");
		flangRang1H->SetMarkerColor(kRed);
		flangRang1H->Draw("P,same");
		tmpLangRang1H->SetMarkerColor(kRed);
		tmpLangRang1H->Draw("P,same");
		//angang1H->Draw("P,same");

		myCanvas->cd(2);
		dELang1H->Draw("AP");
		//dELang1H->Fit(angEFit1H,"Q");
		
		myCanvas->cd(3);
		gPad->DrawFrame(20, 0, 80, 25);
		langRang2H->Draw("P,same");
		tmpLangRang2H->SetMarkerColor(kRed);
		tmpLangRang2H->Draw("P,same");
		flangRang2H->SetMarkerColor(kRed);
		flangRang2H->Draw("P,same");
				langRang1H->Draw("P,same");
		flangRang1H->SetMarkerColor(kRed);
		flangRang1H->Draw("P,same");
		tmpLangRang1H->SetMarkerColor(kRed);
		tmpLangRang1H->Draw("P,same");
		//TString pathname = "/home/zalewski/aku/wrk/movies/xR" + TString::Itoa(inPar[5]*10,10) + ".png";
		//gPad->Print(pathname.Data());
		//angang2H->Draw("P,same");

		myCanvas->cd(4);
		dELang2H->Draw("AP");
		//dELang2H->Fit(angEFit2H,"Q,same");
		myCanvas->Update();

		myResPlotsCanv->cd(1);
		resGAngAng1->Draw("AP");
		resGAngAng1geo3->SetMarkerColor(kRed);
		resGAngAng1geo3->Draw("P,same");

		myResPlotsCanv->cd(2);
		resGAngE1->Draw("AP");

		myResPlotsCanv->cd(3);
		resGAngAng2->Draw("AP");
		resGAngAng2geo3->SetMarkerColor(kRed);
		resGAngAng2geo3->Draw("P,same");

		myResPlotsCanv->cd(4);
		resGAngE2->Draw("AP");
		myResPlotsCanv->Update();
	}
	returner = chiSquareAngAng1H + chiSquareAngAng2H/* + chiSquareAngE1H + chiSquareAngE2H*/;
}
