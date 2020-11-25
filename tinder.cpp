#include "tinder.hh"
R__LOAD_LIBRARY(libgsl.so); 
//R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC_legacy/libEloss.so);

double params[4] = {0.0,0.0,0.0,0.0};

finderC::finderC()
{
	cout<<"ctor\n";
}

bool finderC::miniCaller()
{
	//void KeyPressed(int key); //SIGNAL
	//gApplication->Connect("KeyPressed(int)","finderC", this,"b(int)");
	return true;
}

void finderC::b(int me)
{
	std::cout<<me<<endl;
	//params[0] = 1.0;
	std::cout<<params[0]<<"\t"<<params[1]<<endl;
	switch (me)
	{
	case 3:
		std::cout<<"Case 3 (up) in switch"<<endl;
		params[0]+=0.1;
		break;

	case 4:
		std::cout<<"Case 4 (down) in switch"<<endl;
		params[0]-=0.1;
		break;

	case 5:
		std::cout<<"Case 5 (left) in switch"<<endl;
		params[1]+=0.1;
		break;

	case 6:
		std::cout<<"Case 6 (right) in switch"<<endl;
		params[1]-=0.1;
		break;

	case 10:
		gApplication->Terminate();
		break;

	default:
		break;
	}
	looper(params);
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

int finderC::looper(double *inPar)
{	
	int CD2_Nel=2;
	Double_t CD2_A[2]={2, 12};
	Double_t CD2_Z[2]={1, 6};
	Double_t CD2_W[2]={2, 1};

	int si_Nel=1;
	Double_t si_A[1]={28};
	Double_t si_Z[1]={14};
	Double_t si_W[1]={1};
/*
	h1Si = new ELC(1, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
	h1CD2 = new ELC(1, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);
	h2Si = new ELC(2, 1, si_Nel, 2.35, si_A, si_Z, si_W, 100.,1500);
	h2CD2 = new ELC(2, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);
	he6Si = new ELC(6, 2, si_Nel, 2.35, si_A, si_Z, si_W, 300.,1500);
	he6CD2 = new ELC(6, 2, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 300.,1500);
	*/
	//cout<<"where is the problem"<<endl;
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

	std::vector<Float_t> tmpRang1;
	std::vector<Float_t> tmpRang2;
	std::vector<Float_t> v_tmpdE1;
	std::vector<Float_t> v_tmpdE2;

	std::vector<Float_t> resAngAng1geo3;
	std::vector<Float_t> resAngAng2geo3;

	SQLdist = 170.0;
	SQRdist = 250.0;
	double X6He_bank = -50.0;
	double innerRShift = 0.0;
    TLorentzVector *LV_beam;
   inF = new TFile{"/home/zalewski/data/bank/dE/PG_geo.root", "READ"};
	TTree *inT;
    inT = (TTree*)inF->Get("dE_angle");
    inT->Print();
	inT->SetBranchAddress("SQX_L_sNo", &SQX_L_sNo);
	inT->SetBranchAddress("SQX_L_sNo", &SQX_L_sNo);
	inT->SetBranchAddress("SQX_R_sNo", &SQX_R_sNo);
	inT->SetBranchAddress("SQY_L_sNo", &SQY_L_sNo);
	inT->SetBranchAddress("SQY_R_sNo", &SQY_R_sNo);
	inT->SetBranchAddress("sqlde", &fsqlde);
	inT->SetBranchAddress("sqletot", &sqletot);

	inT->SetBranchAddress("sqrde", &sqrde);
	inT->SetBranchAddress("sqretot", &sqretot);

	inT->SetBranchAddress("MWPC_1_X", &MWPC_1_X);
	inT->SetBranchAddress("MWPC_1_Y", &MWPC_1_Y);
	inT->SetBranchAddress("MWPC_1_Z", &MWPC_1_Z);
	inT->SetBranchAddress("MWPC_2_X", &MWPC_2_X);
	inT->SetBranchAddress("MWPC_2_Y", &MWPC_2_Y);
	inT->SetBranchAddress("MWPC_2_Z", &MWPC_2_Z);
	inT->SetBranchAddress("geo", &geo);
	inT->SetBranchAddress("deu", &deu);
	inT->SetBranchAddress("pro", &pro);
	inT->SetBranchAddress("dEAngle", &dEAngle);
	inT->SetBranchAddress("kinE", &kinE);
	inT->SetBranchAddress("kineProB", &kineProB);
	inT->SetBranchAddress("kineDeuB", &kineDeuB);
	inT->SetBranchAddress("LV_beam.", "TLorentzVector", &LV_beam);
/*
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
*/
	TH2D *angAngRelation1H = new TH2D("angAngRelation1H", "Angle-angle relation for {}^{1}H and {}^{6}He", 100, 20.0, 90.0, 100, 0.0, 20.0);
	TH2D *angAngRelation2H = new TH2D("angAngRelation2H", "Angle-angle relation for {}^{2}H and {}^{6}He", 100, 20.0, 90.0, 100, 0.0, 20.0);

	TH2D *angEnergyRelation1H = new TH2D("angEnergyRelation1H", "Energy-angle relation for protons", 100, 60.0, 80.0, 100, 0.0, 20.0);
	TH2D *angEnergyRelation2H = new TH2D("angEnergyRelation2H", "Energy-angle relation for deuterons", 100, 60.0, 80.0, 100, 0.0, 20.0);

	TH2D *resGAngAng1 = new TH2D("resGAngAng1","{}^{6}He angle deviation based on beam energy and {}^{1}H angle", 100, 20.0, 90.0, 100, -5.0, 5.0);
	TH2D *resGAngAng2 = new TH2D("resGAngAng2","{}^{6}He angle deviation based on beam energy and {}^{2}H angle", 100, 20.0, 90.0, 100, -5.0, 5.0);

	TH2D *resGAngE1 = new TH2D("resGAngE1","{}^{1}H Energy deviation based on Eloss in Si det and {}^{1}H angle", 100, 00.0, 20.0, 100, -5.0, 5.0);
	TH2D *resGAngE2 = new TH2D("resGAngE2","{}^{2}H Energy deviation based on Eloss in Si det and {}^{2}H angle", 100, 00.0, 20.0, 100, -5.0, 5.0);

	lvTar1H = new TLorentzVector();
	lvTar2H = new TLorentzVector();
	const TVector3 vTarget(0.0, 0.0, 0.0);
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
    Long64_t nEntries = inT->GetEntries();
for (Long64_t entry=0; entry<nEntries; entry++)
{
	inT->GetEntry(entry);
		//if (*geo!=3) continue;
		bool geoFlag = false;
		if (geo==1)
		{
			tarPosZ = 0.0;
			tarAngle = (45.0)* TMath::DegToRad();
			SQLang = (65.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 80.0;
		}

		else if(geo==2)
		{
			tarPosZ = 2.0;
			tarAngle = (6.0)* TMath::DegToRad();
			SQLang = (50.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 160.0;
		}

		else if(geo==3)
		{
			tarPosZ = 2.0;
			tarAngle = (0.0) * TMath::DegToRad();
			SQLang = (35.0) * TMath::DegToRad();
			SQRang = (15.0) * TMath::DegToRad();
			tarThickness = 160.0;
			geoFlag = true;
		}
		//cout<<"finder::looper error check\t"<<"Am I getting here?"<<endl;
		double tempE = 160;//he6Si->GetE((*lvBeam).E() - (*lvBeam).M(), 644.0);

		//tempE = he6CD2->GetE(tempE, tarThickness/(2*cos(tarAngle)));
		double eneBeam = tempE + cs::mass6He;
		double momBeam = sqrt(eneBeam*eneBeam-cs::mass6He*cs::mass6He);
		double fMWPC_1_X = MWPC_1_X + inPar[0];
		double fMWPC_1_Y = MWPC_1_Y;
		double fMWPC_2_X = MWPC_2_X + inPar[1];
		double fMWPC_2_Y = MWPC_2_Y;

		double dX = fMWPC_2_X - fMWPC_1_X;
		double dY = fMWPC_2_Y - fMWPC_1_Y;
		double dZ = MWPC_2_Z - MWPC_1_Z;

		TVector3 tarPoint(0.0, 0.0, tarPosZ);
		TVector3 beamPoint(fMWPC_2_X, fMWPC_2_Y, MWPC_2_Z);
		TVector3 tarPerpendicular(sin(tarAngle), 0.0, cos(tarAngle));
		TVector3 vBeam(dX, dY, dZ);
		double dCoeff = ((tarPoint-beamPoint).Dot(tarPerpendicular))/(vBeam.Dot(tarPerpendicular));
				
		vBeam.SetMag(momBeam);
		TLorentzVector *flvBeam = new TLorentzVector();
		flvBeam->SetVectM(vBeam,cs::mass6He);

		X2Hlab = SQLdist*sin(SQLang) + (cs::SQLstartX) * cos(SQLang);
		Y2Hlab = cs::SQLstartY + cs::widthStripX;
		Z2Hlab = SQLdist*cos(SQLang) - (cs::SQLstartX) * sin(SQLang);

		X2Hdet = cs::widthStripX * (SQX_L_sNo) * cos(SQLang);
		Y2Hdet = cs::widthStripY * (SQY_L_sNo);
		Z2Hdet = cs::widthStripX * (SQX_L_sNo) * sin(SQLang);

		X2H = X2Hlab - X2Hdet;
		Y2H = Y2Hlab + Y2Hdet;
		Z2H = Z2Hlab + Z2Hdet;

		evX = fMWPC_2_X + dX * dCoeff;
		evY = fMWPC_2_Y + dY * dCoeff;
		evZ = MWPC_2_Z + dZ * dCoeff;

		TVector3 vectH(X2H-evX, Y2H-evY, Z2H-evZ);
		sqlphi=vectH.Phi()*TMath::RadToDeg();
		sqltheta=vectH.Theta()*TMath::RadToDeg();
		sqlang = vectH.Angle(flvBeam->Vect())*TMath::RadToDeg();

		X6Helab = SQRdist*sin(-SQRang) - (cs::SQRstartX) * cos(SQRang);
		Y6Helab = cs::SQRstartY;
		Z6Helab = SQRdist*cos(SQRang) - (cs::SQRstartX) * sin(SQRang);

		X6Hedet = cs::widthStripX * (SQX_R_sNo) * cos(SQRang);
		Y6Hedet = cs::widthStripY * (SQY_R_sNo);
		Z6Hedet = cs::widthStripX * (SQX_R_sNo) * sin(SQRang);

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

		double sqlde = fsqlde;
		if (pro==1)
		{
			v_Lang1H.push_back(sqlang);
			v_Rang1H.push_back(sqrang);
			angAngRelation1H->Fill(sqlang, sqrang);
			sqrang1Hresidual = sqrang-myAngAngFit(sqlang, cs::mass1H, *flvBeam);
			resGAngAng1->Fill(sqlang,sqrang1Hresidual);

			chiSquareAngAng1H += pow(2,1+abs(sqrang1Hresidual));
			resAngAng1.push_back(sqrang1Hresidual);
			tmpRang1.push_back(myAngAngFit(sqlang, cs::mass1H, *flvBeam));

			if (geoFlag)
			{
				v_fLang1H.push_back(sqlang);
				v_fRang1H.push_back(sqrang);
				resAngAng1geo3.push_back(sqrang1Hresidual);
			}

			if (sqletot==0 && kineProB && fsqlde>3.0 && (geo==1 || geo==2))
			{
				sqlde = fsqlde;//h1Si->GetE(*fsqlde, -3.5);
				//sqlde = h1CD2->GetE(sqlde, -tarThickness/(2*cos(SQLang*TMath::DegToRad()-tarAngle)));
				double fdE1 = myAngEneFit(sqlang, cs::mass1H, *flvBeam);
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



		if (deu==1)
		{

			v_Lang2H.push_back(sqlang);
			v_Rang2H.push_back(sqrang);

			sqrang2Hresidual = sqrang-myAngAngFit(sqlang, cs::mass2H, *flvBeam);
			resGAngAng2->Fill(sqlang,sqrang2Hresidual);

			chiSquareAngAng2H += pow(2,1+abs(sqrang2Hresidual));
			resAngAng2.push_back(sqrang2Hresidual);
			tmpRang2.push_back(myAngAngFit(sqlang, cs::mass2H, *flvBeam));

			if (geoFlag)
			{
				v_fLang2H.push_back(sqlang);
				v_fRang2H.push_back(sqrang);
				resAngAng2geo3.push_back(sqrang2Hresidual);
			}


			if (sqletot==0 && kineDeuB && fsqlde>3.0 && (geo==1 || geo==2))
			{
				sqlde = fsqlde;//h2Si->GetE(*fsqlde, -3.5);
				//sqlde = h2CD2->GetE(sqlde, -tarThickness/(2*cos(SQLang*TMath::DegToRad()-tarAngle)));
				double fdE2 = myAngEneFit(sqlang, cs::mass2H, *flvBeam);
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
	angAngRelation2H->Fill(sqlang, sqrang);
	delete flvBeam;
	}


	std::vector<Float_t> cpyGeo3Sqlang1(v_fLang1H);
	std::vector<Float_t> cpyGeo3Sqlang2(v_fLang2H);

	TGraph *tmpLangRang1H =  new TGraph(v_Lang1H.size(), &v_Lang1H[0], &tmpRang1[0]);
	TGraph *tmpLangRang2H =  new TGraph(v_Lang2H.size(), &v_Lang2H[0], &tmpRang2[0]);
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

	TCanvas *myCanvas = new TCanvas("myCanvas", "Minimize results", 1200, 800);
	TCanvas *myResPlotsCanv = new TCanvas("myResPlots", "residual plot", 1200, 800);
	myCanvas->Divide(2,2);
	myResPlotsCanv->Divide(2,2);

	myCanvas->cd(1);
	angAngRelation2H->Draw("");
	tmpLangRang1H->SetMarkerColor(kRed);
	tmpLangRang1H->Draw("P,same");
	tmpLangRang2H->SetMarkerColor(kRed);
	tmpLangRang2H->Draw("P,same");
	myCanvas->Modified();
	myCanvas->Update();

	myCanvas->cd(2);
	angEnergyRelation1H->Draw("cont");
	flangdE1H->SetMarkerColor(kRed);
	flangdE1H->Draw("P,same");
	myCanvas->Modified();
	myCanvas->Update();
		
	myCanvas->cd(3);
	angAngRelation2H->Draw("cont");
	tmpLangRang1H->SetMarkerColor(kRed);
	tmpLangRang1H->Draw("P,same");
	tmpLangRang2H->SetMarkerColor(kRed);
	tmpLangRang2H->Draw("P,same");
	myCanvas->Modified();
	myCanvas->Update();

	myCanvas->cd(4);
	angEnergyRelation2H->Draw("cont");
	//dELang2H->Fit(angEFit2H,"Q,same");
	flangdE2H->SetMarkerColor(kRed);
	flangdE2H->Draw("P,same");
	myCanvas->Modified();
	myCanvas->Update();
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
	
	myCanvas->SaveAs("/home/zalewski/Desktop/myCanvas.png");
	myResPlotsCanv->SaveAs("/home/zalewski/Desktop/myResPlotsCanv.png");

	delete angAngRelation1H;
	delete angAngRelation2H;
	delete angEnergyRelation1H;
	delete angEnergyRelation2H;
	delete resGAngAng1;
	delete resGAngAng2;
	delete resGAngE1;
	delete resGAngE2;

	delete resGAngAng1geo3;
	delete resGAngAng2geo3;
	delete tmpLangRang1H;
	delete tmpLangRang2H;
	delete flangRang2H;
	delete flangRang1H;
	delete flangdE1H;
	delete flangdE2H;
/*
	delete h1Si;
	delete h1CD2;
	delete h2Si;
	delete h2CD2;
	delete he6Si;
	delete he6CD2;
*/
    return 5;

}

int tinder()
{
	finderC myInst;

	cout<<"Am I getting called?"<<endl;
	myInst.miniCaller();
	//gApplication->Run(kTRUE);
    myInst.looper(params);

	return 1;

}