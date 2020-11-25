#define jasper_cxx

#include "jasper.h"

double jasper::MWPCrange(double position, int clusterMultiplicity)
{
	if (clusterMultiplicity%2 == 0)
	{
		position += rnd->Uniform(0.0, 0.23)-0.5*0.23;
	}
	else
	{
		position += rnd->Uniform(0.0, 1.02)-0.5*1.02;
	}
	return position;
}

void jasper::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).
	rnd = new TRandom3();
	v2H = new TVector3();
	v6He = new TVector3();

	vf2H = new TVector3();
	vf6He = new TVector3();
	TString option = GetOption();
	TString outFName = "/home/zalewski/Desktop/6He/analysis/may27/deu/tmpNew/data/" + option + "_processed.root";
	//printf("%s\n", outFName.Data());
	outF = new TFile(outFName.Data(),"RECREATE");
	const TString fName("digi" + std::to_string(cs::runNo));
	outTree = new TTree(fName.Data(),fName.Data());

	outTree->Branch("evX",	&evX, "evX/D");
	outTree->Branch("evY",	&evY, "evY/D");
	outTree->Branch("evZ",	&evZ, "evZ/D");

	outTree->Branch("fevX",	&fevX, "fevX/D");
	outTree->Branch("fevY",	&fevY, "fevY/D");
	outTree->Branch("fevZ",	&fevZ, "fevZ/D");

	outTree->Branch("X2H",	&X2H, "X2H/D");
	outTree->Branch("Y2H",	&Y2H, "Y2H/D");
	outTree->Branch("Z2H",	&Z2H, "Z2H/D");

	outTree->Branch("X6He",	&X6He, "X6He/D");
	outTree->Branch("Y6He",	&Y6He, "Y6He/D");
	outTree->Branch("Z6He",	&Z6He, "Z6He/D");

	outTree->Branch("fdX",	&fdX, "fdX/D");
	outTree->Branch("fdY",	&fdY, "fdY/D");
	outTree->Branch("fdZ",	&fdZ, "fdZ/D");

	outTree->Branch("fhX",	&fhX, "fhX/D");
	outTree->Branch("fhY",	&fhY, "fhY/D");
	outTree->Branch("fhZ",	&fhZ, "fhZ/D");

	outTree->Branch("sqlang",		&sqlang, 	"sqlang/D");
	outTree->Branch("sqlangCM",		&sqlangCM, 	"sqlangCM/D");
	outTree->Branch("fsqlang",		&fsqlang, 	"fsqlang/D");
	outTree->Branch("sqlde",		&sqlde,		"sqlde/D");
	outTree->Branch("resqlde",		&resqlde,	"resqlde/D");
	outTree->Branch("fsqlde",		&fsqlde,	"fsqlde/D");
	outTree->Branch("sqletot",		&sqletot,	"sqletot/D");
	outTree->Branch("fsqletot",		&fsqletot,	"fsqletot/D");

	outTree->Branch("sqrang",		&sqrang, 	"sqrang/D");
	outTree->Branch("fsqrang",		&fsqrang, 	"fsqrang/D");
	outTree->Branch("sqrde",		&sqrde,			"sqrde/D");
	outTree->Branch("fsqrde",		&fsqrde,		"fsqrde/D");
	outTree->Branch("sqretot",		&sqretot,		"sqretot/D");
	outTree->Branch("fsqretot",		&fsqretot,		"fsqretot/D");

	outTree->Branch("SQX_L_sNo",	&SQX_L_sNo,	"SQX_L_sNo/I");
	outTree->Branch("SQX_R_sNo",	&SQX_R_sNo,	"SQX_R_sNo/I");
	outTree->Branch("SQY_L_sNo",	&SQY_L_sNo,	"SQY_L_sNo/I");
	outTree->Branch("SQY_R_sNo",	&SQY_R_sNo,	"SQY_R_sNo/I");

	outTree->Branch("fthetacm",		&fthetacm,		"fthetacm/D");
	outTree->Branch("fphicm",		&fphicm,		"fphicm/D");
	outTree->Branch("fmm",			&fmm,			"fmm/D");

	outTree->Branch("thetacm",		&thetacm,		"thetacm/D");
	outTree->Branch("phicm",		&phicm,			"phicm/D");
	outTree->Branch("mm",			&mm,			"mm/D");

	outTree->Bronch("flv6He.",		"TLorentzVector",	&flv6He);
	outTree->Bronch("flv2H.",		"TLorentzVector",	&flv2H);
	outTree->Bronch("flvbeam.",		"TLorentzVector",	&flvbeam);
	outTree->Bronch("flv6Hecm.",	"TLorentzVector",	&flv6Hecm);
	outTree->Bronch("flv2Hcm.",		"TLorentzVector",	&flv2Hcm);

	outTree->Bronch("lv6He.",		"TLorentzVector",	&lv6He);
	outTree->Bronch("lv2H.",		"TLorentzVector",	&lv2H);
	
}

void jasper::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	SQLdist = 170.0 + cs::leftDetDist;
	SQRdist = 250.0 + cs::rightDetDist;

	if (cs::runNo==1)
	{
		SQLang = (65.0 + cs::leftAngShift)*TMath::DegToRad();
		SQRang = (15.0 + cs::rightAngShift)*TMath::DegToRad();
		tarThcknss = 80.0 + cs::tarThicknessShift;
		tarAngle = 45.0*TMath::DegToRad();
		tarPosZ = cs::tarPos;
	}

	if (cs::runNo==2)
	{
		SQLang = (50.0 + cs::leftAngShift)*TMath::DegToRad();
		SQRang = (15.0 + cs::rightAngShift)*TMath::DegToRad();
		tarThcknss = 2*80.0 + 2*cs::tarThicknessShift;
		tarAngle = 6.0*TMath::DegToRad();
		tarPosZ = cs::tarPos + 2.0;
	}

	if (cs::runNo==3)
	{
		SQLang = (35.0 + cs::leftAngShift)*TMath::DegToRad();
		SQRang = (15.0 + cs::rightAngShift)*TMath::DegToRad();
		tarThcknss = 2*80.0 + 2*cs::tarThicknessShift;
		tarAngle = 0.0*TMath::DegToRad();
		tarPosZ = cs::tarPos + 2.0;
	}

	MWPC_1_Z = -816.0;
	MWPC_2_Z = -270.0;

	X2Hlab = SQLdist*sin(SQLang) + (cs::SQLstartX + cs::leftDetShift) * cos(SQLang);
	Y2Hlab = cs::SQLstartY + cs::widthStripX;
	Z2Hlab = SQLdist*cos(SQLang) - (cs::SQLstartX + cs::leftDetShift) * sin(SQLang);

	X6Helab = SQRdist*(sin(-SQRang)) + (cs::SQRstartX - cs::rightDetShift) * cos(SQRang);
	Y6Helab = cs::SQRstartY;
	Z6Helab = SQRdist*cos(SQRang) + (cs::SQRstartX - cs::rightDetShift) * sin(SQRang);

	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	consoleWidth = size.ws_col-8;
	//printf("No. of rows: %d\tNo. of columns: %d\n",size.ws_row, size.ws_col);

	h2_CD2	= new ELC(2, 1, CD2_Nel, 1.0, CD2_A, CD2_Z, CD2_W, 100.,1500);
	TString option = GetOption();

}


Bool_t jasper::Process(Long64_t entry)
{
	fReader.SetEntry(entry);
	nEntries = fReader.GetEntries(kTRUE);
	
	std::cout << "[";
	int pos = consoleWidth * progress;
	for (int i = 0; i < consoleWidth; ++i)
	{
		if (i < pos) std::cout << "#";
		else if (i == pos) std::cout << ">";
		else std::cout << ".";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();

	if( entry % ( nEntries / 100 ) == 0) progress += 0.01;
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// When processing keyed objects with PROOF, the object is already loaded
	// and is available via the fObject pointer.
	//
	// This function should contain the \"body\" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.

	flv6He = new TLorentzVector(*inlv6He);
	flv2H = new TLorentzVector(*inlv2H);
	flvbeam = new TLorentzVector(*inlvBeam);
	flv6Hecm = new TLorentzVector(*inlv6Hecm);
	flv2Hcm = new TLorentzVector(*inlv2Hcm);
	lv2H = new TLorentzVector();
	lv6He = new TLorentzVector();
	vBeam = new TVector3();
	lvBeam = new TLorentzVector();

	const TLorentzVector lvTar(0.0, 0.0, 0.0, cs::mass2H);
/*		printf("SiheY %d\t",std::count_if(SiheY.begin(), SiheY.end(), [](unsigned short i){return i > 5.0;}));
		printf("SiheX %d\t",std::count_if(SiheY.begin(), SiheY.end(), [](unsigned short i){return i > 5.0;}));
		printf("SideutY %d\t",std::count_if(SiheY.begin(), SiheY.end(), [](unsigned short i){return i > 5.0;}));
		printf("SideutX %d\n",std::count_if(SiheY.begin(), SiheY.end(), [](unsigned short i){return i > 5.0;}));
		*/
	int count = 0;
	if (std::count_if(SiheY.begin(), SiheY.end(), [](unsigned short i){return i > 5.0;}) == 1 &&
		std::count_if(SiheX.begin(), SiheX.end(), [](unsigned short i){return i > 5.0;}) == 1 &&
		std::count_if(SideutY.begin(), SideutY.end(), [](unsigned short i){return i > 1.0;}) == 1 &&
		std::count_if(SideutX.begin(), SideutX.end(), [](unsigned short i){return i > 1.0;}) == 1	)
	{

		sqletot = 0.0;
		sqretot = 0.0;

		fevX = *fInevx;
		fevY = *fInevy;
		fevZ = *fInevz;

		MWPC_1_X = MWPCrange(*fMWPC_1_X, *fnx1) + cs::MWPC1_X_displacement;
		MWPC_1_Y = MWPCrange(*fMWPC_1_Y, *fny1) + cs::MWPC1_Y_displacement;

		MWPC_2_X = MWPCrange(*fMWPC_2_X, *fnx2) + cs::MWPC2_X_displacement;
		MWPC_2_Y = MWPCrange(*fMWPC_2_Y, *fny2) + cs::MWPC2_Y_displacement;

		dX=MWPC_2_X-MWPC_1_X;
		dY=MWPC_2_Y-MWPC_1_Y;
		dZ=MWPC_2_Z-MWPC_1_Z;

		double kinE = inlvBeam->E() - inlvBeam->M();
		vBeam->SetXYZ(dX,dY,dZ);
		Double_t ene_beam = cs::mass6He + kinE;
		Double_t mom_beam = sqrt(ene_beam*ene_beam - cs::mass6He*cs::mass6He);
		vBeam->SetMag(mom_beam);
		lvBeam->SetVectM(*vBeam, cs::mass6He);

		double Tcoef=(cos(tarAngle)*tarPosZ-sin(tarAngle)*MWPC_1_X - cos(tarAngle)*MWPC_1_Z)/(sin(tarAngle)*dX+cos(tarAngle)*dZ);

		evX = MWPC_1_X + dX*Tcoef;
		evY = MWPC_1_Y + dY*Tcoef;
		evZ = MWPC_1_Z + dZ*Tcoef;

		fdX = *fInX2H;
		fdY = *fInY2H;
		fdZ = *fInZ2H;

		fhX = *fInX6He;
		fhY = *fInY6He;
		fhZ = *fInZ6He;

		fsqlang = *fInsqlang;
		fsqrang = *fInsqrang;
		fthetacm = flv2Hcm->Theta()*TMath::RadToDeg();
		fphicm = flv2Hcm->Phi()*TMath::RadToDeg();

		fsqlde = *fInsqlde;
		fsqrde = *fInsqrde;
		fsqletot = *fInsqletot;
		fsqretot = *fInsqretot;

		SQY_R_sNo= std::distance(SiheY.begin(), std::max_element(SiheY.begin(), SiheY.end()));
		SQX_R_sNo= std::distance(SiheX.begin(), std::max_element(SiheX.begin(), SiheX.end()));
		SQY_L_sNo= std::distance(SideutY.begin(), std::max_element(SideutY.begin(), SideutY.end()));
		SQX_L_sNo= std::distance(SideutX.begin(), std::max_element(SideutX.begin(), SideutX.end()));
		
		double blur = rnd->Uniform(0.0,1.0)-0.5;
		X2Hdet = cs::widthStripX * (SQX_L_sNo + blur) * cos(SQLang);
		Y2Hdet = cs::widthStripY * (SQY_L_sNo + rnd->Uniform(0.0,1.0)-0.5);
		Z2Hdet = cs::widthStripX * (SQX_L_sNo + blur) * sin(SQLang);

		X2H = X2Hlab - X2Hdet + cs::leftDetShiftX;
		Y2H = Y2Hlab + Y2Hdet;
		Z2H = Z2Hlab + Z2Hdet;
		//printf("%f\t%f\t%f\n", Z2Hlab, Z2Hdet, Z2H);
		blur = rnd->Uniform(0.0,1.0)-0.5;
		X6Hedet = cs::widthStripX * (SQX_R_sNo + blur) * cos(SQRang);
		Y6Hedet = cs::widthStripY * (SQY_R_sNo + rnd->Uniform(0.0,1.0)-0.5);
		Z6Hedet = cs::widthStripX * (SQX_R_sNo + blur) * sin(SQRang);

		X6He = X6Helab - X6Hedet;
		Y6He = Y6Helab + Y6Hedet;
		Z6He = Z6Helab - Z6Hedet;
		
		sqlde = SideutX[SQX_L_sNo];
		sqlde = h2_CD2->GetE(sqlde, -tarThcknss/(2*cos(fsqlang*TMath::DegToRad()-TMath::Pi()/4.0)));
		//printf("%f\t%f\n", tarThcknss/2.0, tarThcknss/(2*cos(fsqlang*TMath::DegToRad()-TMath::Pi()/4.0)));
		sqrde = SiheX[SQX_R_sNo];

		if (std::count_if(CsIdeut.begin(), CsIdeut.end(), [](unsigned short i){return i > 2.0;})>0)
		{
			sqletot = CsIdeut[std::distance(CsIdeut.begin(), std::max_element(CsIdeut.begin(), CsIdeut.end()))];
		}

		if (std::count_if(CsIhe.begin(), CsIhe.end(), [](unsigned short i){return i > 2.0;})>0)
		{
			sqretot = CsIhe[std::distance(CsIhe.begin(), std::max_element(CsIhe.begin(), CsIhe.end()))];
		}

		v2H->SetXYZ(X2H-evX, Y2H-evY, Z2H-evZ);
		Double_t ene2H = cs::mass1H + sqlde;
		Double_t mom2H = sqrt(ene2H*ene2H - cs::mass1H*cs::mass1H);
		v2H->SetMag(mom2H);
		lv2H->SetVectM(*v2H, cs::mass1H);
		*lv6He = lvTar + *flvbeam - *lv2H;
		mm = lv6He->M() - cs::mass6He;

		v6He->SetXYZ(X6He-evX, Y6He-evY, Z6He-evZ);
		Double_t ene6He = cs::mass6He + sqrde;
		Double_t mom6He = sqrt(ene6He*ene6He - cs::mass6He*cs::mass6He);
		v6He->SetMag(mom6He);
		lv6He->SetVectM(*v6He, cs::mass6He);

		sqlang = lvBeam->Vect().Angle(*v2H)*TMath::RadToDeg();
		sqrang = lvBeam->Vect().Angle(*v6He)*TMath::RadToDeg();

		Double_t fene2H = flv2H->E();
		Double_t fmom2H = sqrt(fene2H*fene2H - cs::mass1H*cs::mass1H);
		v2H->SetMag(fmom2H);
		lv2H->SetVectM(*v2H, cs::mass1H);
		*lv6He = lvTar + *flvbeam - *flv2H;
		fmm = lv6He->M() - cs::mass6He;

		vf2H->SetXYZ(fdX-*fInevx, fdY-*fInevy, fdZ-*fInevz);
		vf6He->SetXYZ(fhX-*fInevx, fhY-*fInevy, fhZ-*fInevz);

		//calculate energy of recoil particle based on its angle
		double velo_beam = 0.2377 *cs::c;
		double massratio = cs::mass1H/cs::mass6He;
		double velo_deu = ((2 * cos(sqlang*TMath::DegToRad())) / (1+massratio)) * velo_beam;
		double beta_squared= pow(velo_deu/cs::c, 2.0);
		double gamma=1.0/sqrt(1.0-beta_squared);
		resqlde =  massratio*(gamma-1.0)*cs::mass6He;

		TLorentzVector flvDeuCM = *flvbeam + lvTar;

		Double_t m_ThetaCM2H = flvDeuCM.Theta();
		Double_t gammaSquare2H = flvDeuCM.Gamma()*flvDeuCM.Gamma();
		Double_t tanSquare = tan(sqlang*TMath::DegToRad()) * tan(sqlang*TMath::DegToRad());
		Double_t cosLeftAng = (1.0 - gammaSquare2H*tanSquare)/(1 + gammaSquare2H*tanSquare);
		sqlangCM = (TMath::Pi() - (acos(cosLeftAng)-m_ThetaCM2H))*TMath::RadToDeg();

		TVector3 fvboost = flvDeuCM.BoostVector();
		lv2H->Boost(-fvboost);

		thetacm = lv2H->Theta()*TMath::RadToDeg();
		phicm = lv2H->Phi()*TMath::RadToDeg();
		outTree->Fill();
	}	
	
	return kTRUE;
}

void jasper::SlaveTerminate()
{
	printf("\n");

}

void jasper::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	outTree->Write();
	printf("%lld\n",outTree->GetEntries());
	outF->Close();
}
