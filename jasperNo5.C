#define jasperNo5_cxx
// The class definition in jasperNo5.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//	 Begin():		  called every time a loop on the tree starts,
//						  a convenient place to create your histograms.
//	 SlaveBegin():	called after Begin(), when on PROOF called only on the
//						  slave servers.
//	 Process():		called for each event, in this function you decide what
//						  to read and fill your histograms.
//	 SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//						  called only on the slave servers.
//	 Terminate():	 called at the end of the loop on the tree,
//						  a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("jasperNo5.C")
// root> T->Process("jasperNo5.C","some options")
// root> T->Process("jasperNo5.C+")
//


#include "jasperNo5.hh"
#include <TH2.h>
#include <TStyle.h>

void jasperNo5::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).
	rnd = new TRandom3();
	v2H = new TVector3();
	v6He = new TVector3();

	vf2H = new TVector3();
	vf6He = new TVector3();

	outF = new TFile("/home/zalewski/aku/geant4/digi.root","RECREATE");
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

	outTree->Branch("sqlang",		&out_sqlang, 	"sqlang/D");
	outTree->Branch("fsqlang",		&out_fsqlang, 	"fsqlang/D");

	outTree->Branch("fsqrangg",		&out_fsqrangg, 	"fsqrangg/D");
	outTree->Branch("fsqlangg",		&out_fsqlangg, 	"fsqlangg/D");

	outTree->Branch("sqrang",		&out_sqrang, 	"sqrang/D");
	outTree->Branch("fsqrang",		&out_fsqrang, 	"fsqrang/D");


	TString option = GetOption();
}

void jasperNo5::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).
	m_sqlang = 70.0;
	m_sqrang = 9.92;
	m_sqrDetAng = 10.65;
	m_sqldist = 170.0;
	m_sqrdist = 300.0;

	dX0 = m_sqldist * sin(m_sqlang*TMath::DegToRad()) + width_strip_X * 15.5 * cos(m_sqlang*TMath::DegToRad());
	dY0 = -7.5 * width_strip_Y;
	dZ0 = m_sqldist * cos(m_sqlang*TMath::DegToRad()) + -1 * width_strip_X * 15.5 * sin(m_sqlang*TMath::DegToRad());

	hX0 = -1 * m_sqrdist * sin(m_sqrang*TMath::DegToRad()) + width_strip_X * 15.5 * cos(m_sqrDetAng*TMath::DegToRad());
	hY0 = -7.5 * width_strip_Y;
	hZ0 = m_sqrdist * cos(m_sqrang*TMath::DegToRad()) + width_strip_X * 15.5 * sin(m_sqrDetAng*TMath::DegToRad());

}

Bool_t jasperNo5::Process(Long64_t entry)
{
	fReader.SetEntry(entry);
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

	
	Sideut_multY = 0;
	Sideut_multX = 0;
	Sihe_multX = 0;
	Sihe_multY = 0;

	out_evX = *evx;
	out_evY = *evy;
	out_evZ = *evz;

	for (int iii = 0; iii < 16; iii++)
	{
		if (SideutY[iii]>0.1)
		{
			Sideut_multY++;
			SQY_L_s = iii;
		}

		if (SiheY[iii]>0.1)	
		{
			Sihe_multY++;
			SQY_R_s = iii;
		}
	}

	for (int iii = 0; iii < 32; iii++)
	{
		if (SideutX[iii]>0.1)
		{
			Sideut_multX++;
			SQX_L_s = iii;
		}

		if (SiheX[iii]>0.1)	
		{
			Sihe_multX++;
			SQX_R_s = iii;
		}
	}


	if (Sideut_multX*Sihe_multX*Sideut_multY*Sihe_multY==1)
	{	
		dX = dX0 - (SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(m_sqlang*TMath::DegToRad());
		dY = dY0 + (SQY_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_Y;
		dZ = dZ0 + (SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * sin(m_sqlang*TMath::DegToRad());

		hX = hX0 - (SQX_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(m_sqrDetAng*TMath::DegToRad());
		hY = hY0 + (SQY_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_Y;
		hZ = hZ0 - (SQX_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * sin(m_sqrDetAng*TMath::DegToRad());

		fdX = *X2H;
		fdY = *Y2H;
		fdZ = *Z2H;

		fhX = *X6He;
		fhY = *Y6He;
		fhZ = *Z6He;
		

		v2H->SetXYZ(dX-*evx, dY-*evy, dZ-*evz);
		v6He->SetXYZ(hX-*evx, hY-*evy, hZ-*evz);

		vf2H->SetXYZ(fdX-*evx, fdY-*evy, fdZ-*evz);
		vf6He->SetXYZ(fhX-*evx, fhY-*evy, fhZ-*evz);

		out_sqlang = lvBeam->Vect().Angle(*v2H)*TMath::RadToDeg();
		out_sqrang = lvBeam->Vect().Angle(*v6He)*TMath::RadToDeg();

		out_fsqlangg = lvBeam->Vect().Angle(*vf2H)*TMath::RadToDeg();
		out_fsqrangg = lvBeam->Vect().Angle(*vf6He)*TMath::RadToDeg();

		out_fsqlang = *fsqlang;
		out_fsqrang = *fsqrang;
		//reco_sqlang.push_back(sqlang);
		//reco_sqrang.push_back(sqrang);

		//printf("SQLANG: %f\tdX: %f\tdY: %f\tdZ:%f\n",reco_sqlang.back(),dX, dY, dZ);\
		printf("evx: %f\tevy: %f\tevz:%f\n", *evx, *evy, *evz);


		TF1 *angAngFit_2H_rel = new TF1("angAngFit_2H_rel","[0]*atan(2*tan([4]-[1]*x)/(1-tan([4]-[1]*x)*tan([4]-[1]*x)/[2]+[3]*(1+tan([4]-[1]*x)*tan([4]-[1]*x)/[2])))");

		angAngFit_2H_rel->FixParameter(0, TMath::RadToDeg());
		angAngFit_2H_rel->FixParameter(1, TMath::DegToRad());
		angAngFit_2H_rel->FixParameter(2, 0.970382);
		angAngFit_2H_rel->FixParameter(3, 2.948803);
		angAngFit_2H_rel->FixParameter(4, 1.56212);

		outTree->Fill();
	}	

	return kTRUE;
}

void jasperNo5::SlaveTerminate()
{

	//TGraph *gr = new TGraph(reco_sqlang.size(), &reco_sqlang[0], &reco_sqrang[0]);
	//gr->Draw("A*");

}

void jasperNo5::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.
	outTree->Write();
	outF->Close();
}