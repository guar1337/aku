#include "finder.hh"

R__LOAD_LIBRARY(libgsl.so); 
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC_legacy/libEloss.so);

int geoSwitch = 1;

double params[] = {-1.0, -2.1375, 0.2, -1.125, 5.0};
void looper(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag);
finderC::finderC()
{

}

void finderC::miniCaller()
{
	gApplication->Connect("KeyPressed(int)","finderC", this,"b(int)");
	void KeyPressed(int key); //SIGNAL
}

void finderC::b(int me)
{
	/*
	//TStopwatch *stopwatch = new TStopwatch();
	//params[0] = 1.0;
	switch (me)
	{
	case 3:
		//std::cout<<"Case 3 (up) in switch"<<endl;
		params[0]+=2.0;
		break;

	case 4:
		//std::cout<<"Case 4 (down) in switch"<<endl;
		params[0]-=2.0;
		break;

	case 5:
		//std::cout<<"Case 5 (left) in switch"<<endl;
		params[1]-=2.0;
		break;

	case 6:
		//std::cout<<"Case 6 (right) in switch"<<endl;
		params[1]+=2.0;
		break;

	case 10:
		gApplication->Terminate();
		break;

	default:
		break;
	}
	*/

	int nPar = 2;
	std::unique_ptr<TMinuit> myMinuit(new TMinuit(nPar));
	//TMinuit *myMinuit = new TMinuit(nPar);
	myMinuit->SetPrintLevel(-1);
	myMinuit->SetFCN(looper);
//	TFitter *virtFit = new TFitter(nPar);\
	virtFit->SetFCN(looper);
	Double_t inputArgs[nPar];
	std::fill(inputArgs, inputArgs+nPar,0.0);

	myMinuit->DefineParameter(0, "MWPC1_X_displacement", 	inputArgs[0], 0.1, -15.0, 15.0);
	myMinuit->DefineParameter(1, "MWPC1_Y_displacement", 	inputArgs[1], 0.1, -15.0, 15.0);
	//myMinuit->DefineParameter(2, "MWPC1_Y_displacement", 	inputArgs[2], 0.1, -15.0, 15.0);
	Double_t cmdPars[2]={20000,0.00001};
	
	geoSwitch=1;
	//virtFit->GetMinuit()->SetPrintLevel(0);
	//myMinuit->Migrad();
	int tmpPar = myMinuit->GetNumPars();
	Double_t fTmpPar[tmpPar];
	//Double_t gin[1];
	//Double_t returner;
	double burner;

	
	for (int iii = 0; iii < tmpPar; ++iii)
	{
		myMinuit->GetParameter(iii, fTmpPar[iii], burner);
		
	}

	int nestedInPar = 4;
	std::unique_ptr<TMinuit> nestedMinuit(new TMinuit(nestedInPar));
	nestedMinuit->SetPrintLevel(-1);
	nestedMinuit->SetFCN(looper);
	Double_t nestedInputArgs[nestedInPar];
	std::fill( nestedInputArgs,  nestedInputArgs+nestedInPar,0.0);

	nestedMinuit->DefineParameter(0, "1", 	0.0, 0.1, -15.0, 15.0);
	nestedMinuit->DefineParameter(1, "2", 	0.0, 0.1, -15.0, 15.0);
	//nestedMinuit->DefineParameter(2, "3", 	0.0, 0.1, -5.0, 5.0);
	//nestedMinuit->DefineParameter(3, "4", 	0.0, 0.1, -5.0, 5.0);
	//nestedMinuit->DefineParameter(4, "5", 	0.0, 0.1, -15.0, 15.0);
	//nestedMinuit->DefineParameter(5, "6", 	0.0, 0.1, -15.0, 15.0);
	//nestedMinuit->FixParameter(0);
	//nestedMinuit->FixParameter(1);

	geoSwitch = 2;
	nestedMinuit->Migrad();

	int fnPar = nestedMinuit->GetNumPars();
	
	Double_t finPar[fnPar];
	Double_t gin[1];
	Double_t returner;
	
	
	for (int iii = 0; iii < fnPar; ++iii)
	{
		nestedMinuit->GetParameter(iii, finPar[iii], burner);
		
	}
	
	//cout<<finPar[2];
	looper(fnPar, gin, returner, finPar, 100);
	//stopwatch->Print();

}

Double_t finderC::myAngAngFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam)
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
	//printf("sqlangIN: %f\tsqlangOUT: %f\tdiff: %f\tm_Theta: %f\n",m_leftAngle, m_TarCM.Vect().Angle(m_lvBeamCopy.Vect())*TMath::RadToDeg(), m_leftAngle-m_TarCM.Vect().Angle(m_lvBeamCopy.Vect())*TMath::RadToDeg(),m_Theta*TMath::RadToDeg());
	*/
	return m_lvBeam.Vect().Angle(m_lvBeamCopy.Vect())*TMath::RadToDeg();
}

Double_t finderC::myAngEneFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam)
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

void looper(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag)
{	
	int CD2_Nel=2;
	Double_t CD2_A[2]={2, 12};
	Double_t CD2_Z[2]={1, 6};
	Double_t CD2_W[2]={2, 1};

	int si_Nel=1;
	Double_t si_A[1]={28};
	Double_t si_Z[1]={14};
	Double_t si_W[1]={1};

	std::unique_ptr<AELC> h1Si(new ELC(1, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500));
	std::unique_ptr<AELC> h1CD2(new ELC(1, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500));
	std::unique_ptr<AELC> h2Si(new ELC(2, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500));
	std::unique_ptr<AELC> h2CD2(new ELC(2, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500));
	std::unique_ptr<AELC> he6Si(new ELC(6, 2, si_Nel, 2.35, si_A, si_Z, si_W, 300.,1500));
	std::unique_ptr<AELC> he6CD2(new ELC(6, 2, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 300.,1500));

	std::vector<Float_t> v_Lang1H;
	std::vector<Float_t> v_Rang1H;
	std::vector<Float_t> v_fLang1H;
	std::vector<Float_t> v_fRang1H;

	std::vector<Float_t> v_Lang2H;
	std::vector<Float_t> v_Rang2H;
	std::vector<Float_t> v_fLang2H;
	std::vector<Float_t> v_fRang2H;

	std::vector<Float_t> v_De1H;
	std::vector<Float_t> v_dELang1H;
	std::vector<Float_t> v_De2H;
	std::vector<Float_t> v_dELang2H;

	std::vector<Float_t> resAngAng1;
	std::vector<Float_t> resAngAng2;
	std::vector<Float_t> resAngE1;
	std::vector<Float_t> resAngE2;

	std::vector<Float_t> sqlang1;
	std::vector<Float_t> sqrang1;
	std::vector<Float_t> sqlang2;
	std::vector<Float_t> sqrang2;

	std::vector<Float_t> v_tmpdE1;
	std::vector<Float_t> v_tmpdE2;

	std::vector<Float_t> resAngAng1geo3;
	std::vector<Float_t> resAngAng2geo3;

	double X6He_bank = -50.0;
	double innerRShift = 0.0;

	TFile *inF = new TFile{"/home/zalewski/data/bank/dE/PG_geo.root", "READ"};
	TTreeReader fReader{"dE_angle", inF};
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

	std::unique_ptr<TH2D> angAngRelation1H(new TH2D("angAngRelation1H", "Angle-angle relation for {}^{1}H and {}^{6}He", 100, 20.0, 90.0, 100, 0.0, 20.0));
	std::unique_ptr<TH2D> angAngRelation2H(new TH2D("angAngRelation2H", "Angle-angle relation for {}^{2}H and {}^{6}He", 100, 20.0, 90.0, 100, 0.0, 20.0));
	std::unique_ptr<TH2D> angEnergyRelation1H(new TH2D("angEnergyRelation1H", "Energy-angle relation for protons", 100, 60.0, 80.0, 100, 0.0, 20.0));
	std::unique_ptr<TH2D> angEnergyRelation2H(new TH2D("angEnergyRelation2H", "Energy-angle relation for deuterons", 100, 60.0, 80.0, 100, 0.0, 20.0));
	std::unique_ptr<TH2D> resGAngAng1(new TH2D("resGAngAng1","{}^{6}He angle deviation based on beam energy and {}^{1}H angle", 100, 20.0, 90.0, 100, -5.0, 5.0));
	std::unique_ptr<TH2D> resGAngAng2(new TH2D("resGAngAng2","{}^{6}He angle deviation based on beam energy and {}^{2}H angle", 100, 20.0, 90.0, 100, -5.0, 5.0));
	std::unique_ptr<TH2D> resGAngE1(new TH2D("resGAngE1","{}^{1}H Energy deviation based on Eloss in Si det and {}^{1}H angle", 100, 00.0, 20.0, 100, -5.0, 5.0));
	std::unique_ptr<TH2D> resGAngE2(new TH2D("resGAngE2","{}^{2}H Energy deviation based on Eloss in Si det and {}^{2}H angle", 100, 00.0, 20.0, 100, -5.0, 5.0));

	TLorentzVector *lvTar1H = new TLorentzVector();
	TLorentzVector *lvTar2H = new TLorentzVector();
	const TVector3 vTarget(0.0, 0.0, 0.0);
	lvTar1H->SetVectM(vTarget, cs::mass1H);
	lvTar2H->SetVectM(vTarget, cs::mass2H);

	Double_t sqrang1Hresidual{0.0};
	Double_t sqrang2Hresidual{0.0};
	Double_t angDE1Hresidual{0.0};
	Double_t angDE2Hresidual{0.0};

	Double_t chiSquareAngAng1H{0.0};
	Double_t chiSquareAngAng1HGeo1{0.0};
	Double_t chiSquareAngAng2H{0.0};
	Double_t chiSquareAngAng2HGeo1{0.0};
	Double_t chiSquareAngE1H{0.0};
	Double_t chiSquareAngE2H{0.0};

	int counter = -1;
	double SQLdist = 170.0;
	double SQRdist = 250.0;
	Float_t tarPosZ = 0.0, tarThcknss, tarAngle = 0.0, SQLang = 65.0, SQRang = 15.0, lvsqlang, lvsqrang, tarThickness = 80.0;
	Float_t X2Hlab, Y2Hlab, Z2Hlab, X6Helab, Y6Helab, Z6Helab;
	Float_t X2Hdet, Y2Hdet, Z2Hdet, X6Hedet, Y6Hedet, Z6Hedet;
	Float_t evX, evY, evZ, Tcoef;
	Float_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
	Float_t sqlphi, sqltheta, sqrphi, sqrtheta, mml, sqlang, sqrang;

	bool geoFlag = true;
	std::unique_ptr<TRandom3> rnd(new TRandom3());
	std::vector<Double_t> v_LeftAngleProtons;
	std::vector<Double_t> v_LeftAngleDeuterons;
	std::vector<Double_t> v_RightAngleProtons;
	std::vector<Double_t> v_RightAngleDeuterons;

	//cout<<params[4]<<" \n";
	while (fReader.Next())
	{
		//if (*geo!=1) continue;
		bool geoFlag = false;
		if (*geo==1)
		{
			tarPosZ = 0.0 + params[4];
			tarAngle = (45.0)* TMath::DegToRad();
			SQLang = (65.0) * TMath::DegToRad();
			SQRang = (15.0-0.192) * TMath::DegToRad();
			tarThickness = 80.0;
			geoFlag = true;
			}

		else if(*geo==2)
		{
			tarPosZ = 2.0 + params[4];
			tarAngle = (6.0)* TMath::DegToRad();
			SQLang = (50.0 + 0.536) * TMath::DegToRad();
			SQRang = (15.0 + 0.275) * TMath::DegToRad();
			tarThickness = 160.0;			
			
		}

		else if(*geo==3)
		{
			tarPosZ = 2.0 + params[4];
			tarAngle = (0.0) * TMath::DegToRad();
			SQLang = (35.0 + 0.536) * TMath::DegToRad();
			SQRang = (15.0 + 0.275) * TMath::DegToRad();
			tarThickness = 160.0;
						
		}
/*
		if (geoSwitch==2 && iflag==100)
		{
			cout<<inPar[2]<<endl;
		}
*/		
			
		//cout<<"finder::looper error check\t"<<"Am I getting here?"<<endl;
		double tempE = he6Si->GetE((*lvBeam).E() - (*lvBeam).M(), 644.0);
		//printf("%f\n", tempE);
		tempE = he6CD2->GetE(tempE, tarThickness/(2*cos(tarAngle)));
		double eneBeam = tempE + cs::mass6He;
		double momBeam = sqrt(eneBeam*eneBeam-cs::mass6He*cs::mass6He);
		double fMWPC_1_X = *MWPC_1_X + params[0] + inPar[0];
		double fMWPC_1_Y = *MWPC_1_Y + params[1];
		double fMWPC_2_X = *MWPC_2_X + params[2] + inPar[1];
		double fMWPC_2_Y = *MWPC_2_Y + params[3];

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
		v_LeftAngleProtons.push_back(rnd->Uniform(20.0,90.0));
		v_LeftAngleDeuterons.push_back(rnd->Uniform(20.0,90.0));
		v_RightAngleProtons.push_back(finderC::myAngAngFit(v_LeftAngleProtons.back(), cs::mass1H, *flvBeam));
		v_RightAngleDeuterons.push_back(finderC::myAngAngFit(v_LeftAngleDeuterons.back(), cs::mass2H, *flvBeam));

		X2Hlab = SQLdist*sin(SQLang) + (cs::SQLstartX) * cos(SQLang);
		Y2Hlab = cs::SQLstartY + cs::widthStripX;
		Z2Hlab = SQLdist*cos(SQLang) - (cs::SQLstartX) * sin(SQLang);

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

		X6Helab = SQRdist*sin(-SQRang) - (cs::SQRstartX) * cos(SQRang);
		Y6Helab = cs::SQRstartY;
		Z6Helab = SQRdist*cos(SQRang) - (cs::SQRstartX) * sin(SQRang);

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

		//printf("sqrang %f\t%f\t%f\n", SQRdist, cs::SQRstartY, SQRang);
		double sqlde = *fsqlde;
		if (*pro==1)
		{
			angAngRelation1H->Fill(sqlang, sqrang);
			v_Lang1H.push_back(sqlang);
			v_Rang1H.push_back(sqrang);
			angAngRelation1H->Fill(sqlang, sqrang);
			sqrang1Hresidual = sqrang-finderC::myAngAngFit(sqlang, cs::mass1H, *flvBeam);
			resGAngAng1->Fill(sqlang,sqrang1Hresidual);

			chiSquareAngAng1H += pow(2,1+abs(sqrang1Hresidual));
			resAngAng1.push_back(sqrang1Hresidual);

			if (geoFlag)
			{
				v_fLang1H.push_back(sqlang);
				v_fRang1H.push_back(sqrang);
				resAngAng1geo3.push_back(sqrang1Hresidual);
				chiSquareAngAng2HGeo1 += pow(2,1+abs(sqrang1Hresidual));
			}

			if (*sqletot==0 && *kineProB && *fsqlde>3.0 && (*geo==1 || *geo==2))
			{
				sqlde = *fsqlde;//h1Si->GetE(*fsqlde, -3.5);
				//sqlde = h1CD2->GetE(sqlde, -tarThickness/(2*cos(SQLang*TMath::DegToRad()-tarAngle)));
				double fdE1 = finderC::myAngEneFit(sqlang, cs::mass1H, *flvBeam);
				angDE1Hresidual = sqlde - fdE1;
				chiSquareAngE1H += angDE1Hresidual*angDE1Hresidual;
				resAngE1.push_back(angDE1Hresidual);

				v_De1H.push_back(sqlde);
				v_dELang1H.push_back(sqlang);
				v_tmpdE1.push_back(fdE1);

				angEnergyRelation1H->Fill(sqlang, sqlde);
				resGAngE1->Fill(sqlde,angDE1Hresidual);
			}

		}



		if (*deu==1)
		{
			angAngRelation2H->Fill(sqlang, sqrang);
			v_Lang2H.push_back(sqlang);
			v_Rang2H.push_back(sqrang);

			sqrang2Hresidual = sqrang-finderC::myAngAngFit(sqlang, cs::mass2H, *flvBeam);
			resGAngAng2->Fill(sqlang,sqrang2Hresidual);

			chiSquareAngAng2H += pow(2,1+abs(sqrang2Hresidual));
			resAngAng2.push_back(sqrang2Hresidual);

			if (geoFlag)
			{
				v_fLang2H.push_back(sqlang);
				v_fRang2H.push_back(sqrang);
				resAngAng2geo3.push_back(sqrang2Hresidual);
				chiSquareAngAng2HGeo1 += pow(2,1+abs(sqrang2Hresidual));
			}


			if (*sqletot==0 && *kineDeuB && *fsqlde>3.0 && (*geo==1 || *geo==2))
			{
				sqlde = *fsqlde;//h2Si->GetE(*fsqlde, -3.5);
				//sqlde = h2CD2->GetE(sqlde, -tarThickness/(2*cos(SQLang*TMath::DegToRad()-tarAngle)));
				double fdE2 = finderC::myAngEneFit(sqlang, cs::mass2H, *flvBeam);
				angDE2Hresidual = sqlde - fdE2;
				chiSquareAngE2H += angDE2Hresidual*angDE2Hresidual;

				resAngE2.push_back(angDE2Hresidual);
				v_De2H.push_back(sqlde);
				v_dELang2H.push_back(sqlang);

				v_tmpdE2.push_back(fdE2);

				angEnergyRelation2H->Fill(sqlang, sqlde);
				resGAngE2->Fill(sqlde, angDE2Hresidual);
			}

		}
	
	delete flvBeam;
	}


	fReader.Restart();

	if (iflag == 100)
	{
	
	std::vector<Float_t> cpyGeo3Sqlang1(v_fLang1H);
	std::vector<Float_t> cpyGeo3Sqlang2(v_fLang2H);


	TGraph *tmpLangRang1H =  new TGraph(v_LeftAngleProtons.size(), &v_LeftAngleProtons[0], &v_RightAngleProtons[0]);
	TGraph *tmpLangRang2H =  new TGraph(v_LeftAngleDeuterons.size(), &v_LeftAngleDeuterons[0], &v_RightAngleDeuterons[0]);
	TGraph *flangRang2H =  new TGraph(v_fLang2H.size(), &v_fLang2H[0], &v_fRang2H[0]);
	TGraph *flangRang1H =  new TGraph(v_fLang1H.size(), &v_fLang1H[0], &v_fRang1H[0]);
	TGraph *flangdE1H =  new TGraph(v_dELang1H.size(), &v_dELang1H[0], &v_tmpdE1[0]);
	TGraph *flangdE2H =  new TGraph(v_dELang2H.size(), &v_dELang2H[0], &v_tmpdE2[0]);

	angAngRelation1H->GetXaxis()->SetTitle("protons LAB angle [deg]");
	angAngRelation1H->GetXaxis()->CenterTitle();
	angAngRelation1H->GetYaxis()->SetTitle("{}^{6}He LAB angle [deg]");
	angAngRelation1H->GetYaxis()->CenterTitle();

	angAngRelation2H->GetXaxis()->SetTitle("deuterons LAB angle [deg]");
	angAngRelation2H->GetXaxis()->CenterTitle();
	angAngRelation2H->GetYaxis()->SetTitle("{}^{6}He LAB angle [deg]");
	angAngRelation2H->GetYaxis()->CenterTitle();
	
	angEnergyRelation1H->GetXaxis()->SetTitle("LAB angle of protons [deg]");
	angEnergyRelation1H->GetXaxis()->CenterTitle();
	angEnergyRelation1H->GetYaxis()->SetTitle("protons energy loss in Si det [MeV]");
	angEnergyRelation1H->GetYaxis()->CenterTitle();

	angEnergyRelation2H->GetXaxis()->SetTitle("LAB angle of deuterons [deg]");
	angEnergyRelation2H->GetXaxis()->CenterTitle();
	angEnergyRelation2H->GetYaxis()->SetTitle("deuterons energy loss in Si det [MeV]");
	angEnergyRelation2H->GetYaxis()->CenterTitle();

	resGAngAng1->GetXaxis()->SetTitle("LAB angle of protons [deg]");
	resGAngAng1->GetXaxis()->CenterTitle();
	resGAngAng1->GetYaxis()->SetTitle("LAB angle deviation of protons [deg]");
	resGAngAng1->GetYaxis()->CenterTitle();

	resGAngAng2->GetXaxis()->SetTitle("LAB angle of deuterons [deg]");
	resGAngAng2->GetXaxis()->CenterTitle();
	resGAngAng2->GetYaxis()->SetTitle("LAB angle deviation of deuterons [deg]");
	resGAngAng2->GetYaxis()->CenterTitle();

	resGAngE1->GetXaxis()->SetTitle("LAB angle of protons [deg]");
	resGAngE1->GetXaxis()->CenterTitle();
	resGAngE1->GetYaxis()->SetTitle("energy deviation for protons [MeV]");
	resGAngE1->GetYaxis()->CenterTitle();

	resGAngE2->GetXaxis()->SetTitle("LAB angle of deuterons [deg]");
	resGAngE2->GetXaxis()->CenterTitle();
	resGAngE2->GetYaxis()->SetTitle("energy deviation for deuterons [MeV]");
	resGAngE2->GetYaxis()->CenterTitle();

	TGraph *resGAngAng1geo3 = new TGraph(cpyGeo3Sqlang1.size(), &cpyGeo3Sqlang1[0],  &resAngAng1geo3[0]);
	TGraph *resGAngAng2geo3 = new TGraph(cpyGeo3Sqlang2.size(), &cpyGeo3Sqlang2[0],  &resAngAng2geo3[0]);

	TCanvas *myCanvas = new TCanvas("myCanvas", "Minimize results", 1987,55,1678,1025);
	//TCanvas *myResPlotsCanv = new TCanvas("myResPlots", "residual plot", 1200, 800);
	TF1 flatLine("flat","0",20,90);
	myCanvas->Divide(2,2);

	TString paramString1 = TString::Format("MWPC X 1: %.3f",params[0]);
	TString paramString2 = TString::Format("MWPC X 2: %.3f",params[1]);
	TString paramString3 = TString::Format("inPar[0]: %.3f, inPar[1] = %.3f",inPar[0], inPar[1]);
	TString paramString4 = TString::Format("inPar[2]: %.3f, inPar[1] = %.3f",inPar[2], inPar[1]);
	TString paramString5 = TString::Format("tarPos: %.3f, inPar[1] = %.3f",tarPosZ-2.0, inPar[1]);
	//myResPlotsCanv->Divide(2,2);


	myCanvas->cd(1);
	angAngRelation1H->Draw("");
	angAngRelation2H->Draw("same");
	flangRang1H->SetMarkerColor(kRed);
	flangRang1H->Draw("P,same");
	flangRang2H->SetMarkerColor(kRed);
	flangRang2H->Draw("P,same");
	tmpLangRang1H->SetMarkerColor(kGreen);
	tmpLangRang1H->Draw("P,same");
	tmpLangRang2H->SetMarkerColor(kGreen);
	tmpLangRang2H->Draw("P,same");
	TLatex *tex1 = new TLatex(22.0,4.50,paramString1.Data());
	TLatex *tex2 = new TLatex(22.0,3.50,paramString2.Data());
	TLatex *tex3 = new TLatex(22.0,2.50,paramString3.Data());
	TLatex *tex4 = new TLatex(22.0,1.50,paramString4.Data());
	TLatex *tex5 = new TLatex(22.0,0.50,paramString5.Data());
	tex1->SetLineWidth(2);
	tex1->Draw("same");
	tex2->SetLineWidth(2);
	tex2->Draw("same");
	tex3->SetLineWidth(2);
	tex3->Draw("same");
	tex4->SetLineWidth(2);
	tex4->Draw("same");
	tex5->SetLineWidth(2);
	tex5->Draw("same");

	myCanvas->cd(2);
	resGAngAng1->Draw("cont");
	flatLine.Draw("same");
/*	angEnergyRelation1H->Draw("cont");
	flangdE1H->SetMarkerColor(kRed);
	flangdE1H->Draw("P,same");
*/
	myCanvas->cd(3);
	angAngRelation1H->Draw("cont");
	angAngRelation2H->Draw("same, cont");
	tmpLangRang1H->SetMarkerColor(kGreen);
	tmpLangRang1H->Draw("P,same");
	tmpLangRang2H->SetMarkerColor(kGreen);
	tmpLangRang2H->Draw("P,same");

	myCanvas->cd(4);
	resGAngAng2->Draw("cont");
	flatLine.Draw("same");
	gSystem->ProcessEvents();

	TString pathname = TString::Format("/home/zalewski/Desktop/move/pic_%.3f_%.3f.png", params[4], params[1]);
	myCanvas->Print(pathname.Data());
/*	angEnergyRelation2H->Draw("cont");
	//dELang2H->Fit(angEFit2H,"Q,same");
	flangdE2H->SetMarkerColor(kRed);
	flangdE2H->Draw("P,same");
	gSystem->ProcessEvents();

	myResPlotsCanv->cd(1);
	resGAngAng1->Draw("cont");
	resGAngAng1geo3->SetMarkerColor(kRed);
	myResPlotsCanv->Modified();
	myResPlotsCanv->Update();
	//resGAngAng1geo3->Draw("P,same");

	myResPlotsCanv->cd(2);
	resGAngE1->Draw("cont");
	myResPlotsCanv->Modified();
	myResPlotsCanv->Update();

	myResPlotsCanv->cd(3);
	resGAngAng2->Draw("cont");
	resGAngAng2geo3->SetMarkerColor(kRed);
	myResPlotsCanv->Modified();
	myResPlotsCanv->Update();
	//resGAngAng2geo3->Draw("P,same");

	myResPlotsCanv->cd(4);
	resGAngE2->Draw("cont");	
	myResPlotsCanv->Modified();
	myResPlotsCanv->Update();
	//gSystem->ProcessEvents();
*/
	}

	if (geoSwitch == 1)
	{
		returner = chiSquareAngAng1HGeo1 + chiSquareAngAng2HGeo1;
	}

	else
	{
		returner = chiSquareAngAng1H + chiSquareAngAng2H;
	}
	
	
	
}

void finder()
{
	finderC myInst;
	//myInst.miniCaller();
	int fnPar  =2;
	Double_t finPar[2];
	Double_t gin[1];
	Double_t returner;
	//params[0]=-5.0;
	/*
	for (int iii = 0; iii < 6; iii++)
	{
		params[1] = -5.0;
		for (int jjj = 0; jjj < 11; jjj++)
		{
			myInst.b(4);
			cout<<params[0]<<"\t"<<params[1]<<"\n";
			params[1]+=1.0;
		}
	params[0]+=1.0;
	}
	*/	
	params[4] = 10.0;
	//for (int iii = 0; iii <= 50; iii++)
	{
		myInst.b(4);
		params[4]+=0.1;
	}
	

	//looper(fnPar, gin, returner, finPar, 100);
	//gApplication->Run();


}