#define jasper_cxx

#include "jasper.h"


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
	TString outFName = "/home/guar/data/he6_d/simulation/" + option + "_processed.root";
	//printf("%s\n", outFName.Data());
	outF = new TFile(outFName.Data(),"RECREATE");
	outTree = new TTree("digi","digi");

	outTree->Branch("evX",	&out_evX, "evX/D");
	outTree->Branch("evY",	&out_evY, "evY/D");
	outTree->Branch("evZ",	&out_evZ, "evZ/D");

	outTree->Branch("dX",	&dX, "dX/D");
	outTree->Branch("dY",	&dY, "dY/D");
	outTree->Branch("dZ",	&dZ, "dZ/D");

	outTree->Branch("hX",	&hX, "hX/D");
	outTree->Branch("hY",	&hY, "hY/D");
	outTree->Branch("hZ",	&hZ, "hZ/D");

	outTree->Branch("fdX",	&fdX, "fdX/D");
	outTree->Branch("fdY",	&fdY, "fdY/D");
	outTree->Branch("fdZ",	&fdZ, "fdZ/D");

	outTree->Branch("fhX",	&fhX, "fhX/D");
	outTree->Branch("fhY",	&fhY, "fhY/D");
	outTree->Branch("fhZ",	&fhZ, "fhZ/D");

	outTree->Branch("sqlang",		&sqlang, 	"sqlang/D");
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
	l_sqlang = 65.0;
	l_sqrang = 15.0;
	l_sqldist = 170.0;
	l_sqrdist = 250.0;

	dX0 = l_sqldist * sin(l_sqlang*TMath::DegToRad()) + width_strip_X * 15.5 * cos(l_sqlang*TMath::DegToRad());
	dY0 = -7.5 * width_strip_Y;
	dZ0 = l_sqldist * cos(l_sqlang*TMath::DegToRad()) + -1 * width_strip_X * 15.5 * sin(l_sqlang*TMath::DegToRad());

	hX0 = -1 * l_sqrdist * sin(l_sqrang*TMath::DegToRad()) + width_strip_X * 15.5 * cos(l_sqrang*TMath::DegToRad());
	hY0 = -7.5 * width_strip_Y;
	hZ0 = l_sqrdist * cos(l_sqrang*TMath::DegToRad()) + width_strip_X * 15.5 * sin(l_sqrang*TMath::DegToRad());

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

	const TLorentzVector lvTar(0.0, 0.0, 0.0, cs::mass_2H);


	if (std::count_if(SiheY.begin(), SiheY.end(), [](unsigned short i){return i > 5.0;}) == 1 &&
		std::count_if(SiheX.begin(), SiheX.end(), [](unsigned short i){return i > 5.0;}) == 1 &&
		std::count_if(SideutY.begin(), SideutY.end(), [](unsigned short i){return i > 1.0;}) == 1 &&
		std::count_if(SideutX.begin(), SideutX.end(), [](unsigned short i){return i > 1.0;}) == 1	)
	{
		sqletot = 0.0;
		sqretot = 0.0;
		out_evX = *fInevx;
		out_evY = *fInevy;
		out_evZ = *fInevz;

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

		SQY_R_s = std::distance(SiheY.begin(), std::max_element(SiheY.begin(), SiheY.end()));
		SQX_R_s = std::distance(SiheX.begin(), std::max_element(SiheX.begin(), SiheX.end()));
		SQY_L_s = std::distance(SideutY.begin(), std::max_element(SideutY.begin(), SideutY.end()));
		SQX_L_s = std::distance(SideutX.begin(), std::max_element(SideutX.begin(), SideutX.end()));
		
		dX = dX0 - (SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(l_sqlang*TMath::DegToRad());
		dY = dY0 + (SQY_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_Y;
		dZ = dZ0 + (SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * sin(l_sqlang*TMath::DegToRad());

		hX = hX0 - (SQX_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(l_sqrang*TMath::DegToRad());
		hY = hY0 + (SQY_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_Y;
		hZ = hZ0 - (SQX_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * sin(l_sqrang*TMath::DegToRad());
		
		sqlde = SideutX[SQX_L_s];
		sqlde = h2_CD2->GetE(sqlde, -tarThcknss/(2/**cos(fsqlang*TMath::DegToRad()-TMath::Pi()/4.0)*/));
		sqrde = SiheX[SQX_R_s];

		if (std::count_if(CsIdeut.begin(), CsIdeut.end(), [](unsigned short i){return i > 2.0;})>0)
		{
			sqletot = CsIdeut[std::distance(CsIdeut.begin(), std::max_element(CsIdeut.begin(), CsIdeut.end()))];
		}

		if (std::count_if(CsIhe.begin(), CsIhe.end(), [](unsigned short i){return i > 2.0;})>0)
		{
			sqretot = CsIhe[std::distance(CsIhe.begin(), std::max_element(CsIhe.begin(), CsIhe.end()))];
		}

		v2H->SetXYZ(dX-*fInevx, dY-*fInevy, dZ-*fInevz);

		Double_t ene2H = cs::mass_2H + sqlde;
		Double_t mom2H = sqrt(ene2H*ene2H - cs::mass_2H*cs::mass_2H);
		v2H->SetMag(mom2H);
		lv2H->SetVectM(*v2H, cs::mass_2H);
		*lv6He = lvTar + *flvbeam - *lv2H;
		mm = lv6He->M() - cs::mass_6He;

		Double_t fene2H = flv2H->E();
		Double_t fmom2H = sqrt(fene2H*fene2H - cs::mass_2H*cs::mass_2H);
		v2H->SetMag(fmom2H);
		lv2H->SetVectM(*v2H, cs::mass_2H);
		*lv6He = lvTar + *flvbeam - *flv2H;
		fmm = lv6He->M() - cs::mass_6He;

		vf2H->SetXYZ(fdX-*fInevx, fdY-*fInevy, fdZ-*fInevz);
		vf6He->SetXYZ(fhX-*fInevx, fhY-*fInevy, fhZ-*fInevz);

		sqlang = inlvBeam->Vect().Angle(*v2H)*TMath::RadToDeg();
		sqrang = inlvBeam->Vect().Angle(*v6He)*TMath::RadToDeg();

		//calculate energy of recoil particle based on its angle
		double velo_beam = 0.2377 *cs::c;
		double mass_ratio = cs::mass_2H/cs::mass_6He;
		double velo_deu = ((2 * cos(sqlang*TMath::DegToRad())) / (1+mass_ratio)) * velo_beam;
		double beta_squared= pow(velo_deu/cs::c, 2.0);
		double gamma=1.0/sqrt(1.0-beta_squared);
		resqlde =  mass_ratio*(gamma-1.0)*cs::mass_6He;

		v6He->SetXYZ(hX-*fInevx, hY-*fInevy, hZ-*fInevz);
		lv6He->SetVectM(*v6He, cs::mass_6He);

		TLorentzVector flvDeuCM = *flvbeam + lvTar;
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
	outF->Close();
}