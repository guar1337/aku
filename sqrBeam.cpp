#include "TString.h"
#include "constants.h"

#include "ELC/AELC.h"
#include "ELC/ELC.h"
R__LOAD_LIBRARY(libgsl.so); 
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC/build/libEloss.so);

TFile *inF = new TFile{"/home/zalewski/Desktop/6He/analysis/SQRBeamAxis/beamSQRinput.root", "READ"};
TTreeReader fReader("beamTracker", inF);


TTreeReaderValue<Float_t> MWPC_1_X = {fReader, "MWPC_1_X"};
TTreeReaderValue<Float_t> MWPC_1_Y = {fReader, "MWPC_1_Y"};
TTreeReaderValue<Float_t> MWPC_2_X = {fReader, "MWPC_2_X"};
TTreeReaderValue<Float_t> MWPC_2_Y = {fReader, "MWPC_2_Y"};
TTreeReaderValue<Int_t> SQX_R_s = {fReader, "SQX_R_strip"};
TTreeReaderValue<Int_t> SQY_R_s = {fReader, "SQY_R_strip"};
TTreeReaderValue<Int_t> CsI_R_s = {fReader, "CsI_R_strip"};
//TTreeReaderValue<Int_t> geo = {fReader, "geo"};

TH1F histX("histX", "evX-X6He", 200, -50, 50);
TH1F histY("histY", "evY-Y6He", 200, -50, 50);
TH2F evX_detX("evX_detX","evX vs X6He", 50,-70,-10,50,-70,-30);
TH2F evY_detY("evY_detY","evY vs Y6He", 60,-30,30,10,-25,25);
//TH2F evY_detY("evY_detY","evY vs Y6He", 100,-30,30,100,-30,30);

TH2F evX_evY("evX_evY","evX vs evY", 50,-70,-10,50,-30,30);
TH2F detX_detY("detX_detY","detX vs detY", 200,-70,-10,200,-30,30);

TH2F evX_evZ("evX_evZ","evX vs evZ", 200,-70,-10,200,240,260);
TH2F detX_detZ("detX_detZ","detX vs detZ", 200,-70,-10,200,240,260);
TF1 *fitX, *fitY;



Float_t SQRang, SQRdist;
Float_t X6Helab, Y6Helab, Z6Helab;
Float_t X6Hedet, Y6Hedet, Z6Hedet;
Float_t X6He, Y6He, Z6He;
Float_t evX, evY, evZ, Tcoef;
Float_t sqrphi, sqrtheta, sqrang;

TRandom3 *rnd = new TRandom3();

int fnPar=1; Double_t fgin[2]; Double_t freturner; Int_t iflag;

TVector3 *vBeam, v6He;

void myFnc(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag);
void fitter();

void sqrBeam()
{
	TStopwatch *stopwatch = new TStopwatch();

	fitX = new TF1("fitX", "[0] + [1]*x", -70.0, -10.0);
	fitX->FixParameter(0, 0.0);
	fitX->FixParameter(1, 1.0);

	fitY = new TF1("fitY", "[0] + [1]*x", -50.0, 50.0);
	fitY->FixParameter(0, 0.0);
	fitY->FixParameter(1, 1.0);

	int nPar = 7;
	TFitter *virtFit = new TFitter(nPar);
	virtFit->SetFCN(myFnc);
	Double_t inputArgs[nPar];
	std::fill(inputArgs, inputArgs+nPar,0.0);

	//virtFit->SetParameter(0, "MWPC1_X_displacement", 	inputArgs[0], 0.1, -5.0, 5.0);
	virtFit->SetParameter(1, "MWPC1_Y_displacement", 	inputArgs[1], 0.1, -5.0, 5.0);
	//virtFit->SetParameter(2, "MWPC2_X_displacement",	inputArgs[2], 0.1, -5.0, 5.0);
	virtFit->SetParameter(3, "MWPC2_Y_displacement", 	inputArgs[3], 0.1, -5.0, 5.0);
	//virtFit->SetParameter(4, "Yshift",	inputArgs[4], 0.1, -5.0, 5.0);

	//virtFit->SetParameter(4, "rightDetShift",	inputArgs[4], 0.1, -50.0, 50.0);
	//virtFit->SetParameter(5, "rightDetDist",	inputArgs[5], 0.1, -50.0, 50.0);
	//virtFit->SetParameter(6, "rightAngShift",	inputArgs[6], 0.1, -50.0, 50.0);
	
	virtFit->GetMinuit()->SetPrintLevel(2);
	Double_t prec[2] = {1000,1};
	Double_t cmdPars[2]={20000,0.00001};
	virtFit->ExecuteCommand("SET EPSmachine", prec,1);
	virtFit->ExecuteCommand("migrad", cmdPars, 0);

	fnPar = virtFit->GetNumberTotalParameters();
	Double_t finPar[fnPar];
	Double_t m_gin[1];
	Double_t m_returner;
	Int_t m_nPar = 16;
	Double_t inPar[m_nPar];

	Double_t gin[1];
	Double_t returner;
	ofstream outStream("/home/zalewski/aku/wrk/BeamPars.dat", ios_base::trunc);

	if (!outStream) 
	{
		printf ("#Cannot open %s coefficient file\n","/home/zalewski/aku/wrk/BeamPars.dat");
		return 0;
	}

	for (int iii = 0; iii < fnPar; ++iii)
	{
		finPar[iii] = virtFit->GetParameter(iii);
		outStream<<"\tstatic const float\t"<<virtFit->GetParName(iii)<<" = "<<finPar[iii]<<";\n";
	}
/*
	finPar[1] = -5.0;
	finPar[3] = -5.0;

	//myFnc(m_nPar, m_gin, m_returner, inPar, 100);
	for (int iii = 0; iii < 11; iii++)
	{
		finPar[1] = -5.0;
		for (int jjj = 0; jjj < 11; jjj++)
		{
			myFnc(fnPar, m_gin, m_returner, finPar, 100);
			finPar[1]+=1.0;
		}
		finPar[3]+=1.0;
	}
	

*/
	myFnc(fnPar, m_gin, m_returner, finPar, 100);
	stopwatch->Print();
}

void myFnc(Int_t &npar, Double_t *gin, Double_t &returner, Double_t *inPar, Int_t iflag)
{
	histX.Reset();
	histY.Reset();

	evX_detX.Reset();
	evY_detY.Reset();

	detX_detY.Reset();
	evX_evY.Reset();

	evX_evZ.Reset();
	detX_detZ.Reset();

	std::vector<Float_t> vevX;
	std::vector<Float_t> vevY;
	std::vector<Float_t> vevZ;

	std::vector<Float_t> vhe6X;
	std::vector<Float_t> vhe6Y;
	std::vector<Float_t> vhe6Z;

	std::vector<Float_t> vDiffX;
	std::vector<Float_t> vDiffY;
	std::vector<Float_t> vDiffZ;

	Float_t tmpBank = 0.0;

	SQRdist = 250.0 + inPar[5];
	SQRang = (15.0 + inPar[6]) * TMath::DegToRad();
	while (fReader.Next())
	{

		/*
		bool geoFlag = false;
		if (*geo==1)
		{
			tarPosZ = 0.0 + inPar[13];
			SQRang = (15.0 + inPar[8]) * TMath::DegToRad();
		}

		else if(*geo==2)
		{
			tarPosZ = 2.0 + inPar[13];
			SQRang = (15.0 + inPar[8]) * TMath::DegToRad();
		}

		else if(*geo==3)
		{
			tarPosZ = 2.0 + inPar[13];
			SQRang = (15.0 + inPar[8]) * TMath::DegToRad();
		}
*/

		double fMWPC_1_X = *MWPC_1_X + inPar[0];
		double fMWPC_1_Y = *MWPC_1_Y + inPar[1];
		double fMWPC_2_X = *MWPC_2_X + inPar[2];
		double fMWPC_2_Y = *MWPC_2_Y + inPar[3];
		double fMWPC_1_Z = -816.0;
		double fMWPC_2_Z = -270.0;

		double dX = fMWPC_2_X - fMWPC_1_X;
		double dY = fMWPC_2_Y - fMWPC_1_Y;
		double dZ = fMWPC_2_Z - fMWPC_1_Z;

		TVector3 sqrPoint(SQRdist*sin(-SQRang), 0.0, SQRdist*cos(SQRang));
		TVector3 beamPoint(fMWPC_2_X, fMWPC_2_Y, fMWPC_2_Z);
		TVector3 sqrPerpendicular(SQRdist*sin(-SQRang), 0.0, SQRdist*cos(SQRang));
		TVector3 vBeam(dX, dY, dZ);
		double dCoeff = ((sqrPoint-beamPoint).Dot(sqrPerpendicular))/(vBeam.Dot(sqrPerpendicular));

		evX = fMWPC_2_X + dX * dCoeff;
		evY = fMWPC_2_Y + dY * dCoeff;
		evZ = fMWPC_2_Z + dZ * dCoeff;

		X6Helab = SQRdist*sin(-SQRang) - (cs::SQRstartX) * cos(SQRang);
		Y6Helab = cs::SQRstartY;
		Z6Helab = SQRdist*cos(SQRang) - (cs::SQRstartX) * sin(SQRang);

		X6Hedet = cs::widthStripX * (*SQX_R_s + rnd->Uniform(-0.5,0.5)) * cos(SQRang);
		Y6Hedet = cs::widthStripY * (*SQY_R_s + rnd->Uniform(-0.5,0.5));
		Z6Hedet = cs::widthStripX * (*SQX_R_s + rnd->Uniform(-0.5,0.5)) * sin(SQRang);

		X6He = X6Helab + X6Hedet;
		Y6He = Y6Helab + Y6Hedet;
		Z6He = Z6Helab + Z6Hedet;

		vhe6X.push_back(X6He);
		vhe6Y.push_back(Y6He);
		vhe6Z.push_back(Z6He);

		vevX.push_back(evX);
		vevY.push_back(evY);
		vevZ.push_back(evZ);


		histX.Fill(evX-X6He);
		histY.Fill(evY-Y6He);

		evX_evY.Fill(evX,evY);
		detX_detY.Fill(X6He,Y6He);

		evX_detX.Fill(evX,X6He);
		evY_detY.Fill(evY,Y6He);

		evX_evZ.Fill(evX,evZ);
		detX_detZ.Fill(X6He,Z6He);
/*
		printf("X6He: %f\tevX: %f\tY6He: %f\tevY: %f\tZ6He: %f\tevZ: %f\n", X6He, evX, Y6He, evY, Z6He, evZ);
/*		printf("X2Hdet: %f\tY2Hdet: %f\tZ2Hdet: %f\t\n", X2Hdet, Y2Hdet, Z2Hdet);
		printf("X6Helab: %f\tY6Helab: %f\tZ6Helab: %f\t\n", X6Helab, Y6Helab, Z6Helab);
		printf("X6Hedet: %f\tY6Hedet: %f\tZ6Hedet: %f\t\n\n", X6Hedet, Y6Hedet, Z6Hedet);
*/

	}

	fReader.Restart();

	if (iflag == 100)
	{

		TGraph *diffX =  new TGraph(vhe6X.size(), &vhe6X[0], &vevX[0]);
		diffX->SetTitle("Angle-angle relation for {}^{1}H and {}^{6}He");
		diffX->GetXaxis()->SetTitle("protons LAB angle [deg]");
		diffX->GetXaxis()->CenterTitle();
		diffX->GetYaxis()->SetTitle("{}^{6}He LAB angle [deg]");
		diffX->GetYaxis()->CenterTitle();

		TGraph *diffY =  new TGraph(vhe6Y.size(), &vhe6Y[0], &vevY[0]);
		diffY->SetTitle("Energy-angle relation for protons");
		diffY->GetXaxis()->SetTitle("LAB angle of protons [deg]");
		diffY->GetXaxis()->CenterTitle();
		diffY->GetYaxis()->SetTitle("protons energy loss in Si det [MeV]");
		diffY->GetYaxis()->CenterTitle();

		TGraph *diffZ = new TGraph(vhe6Z.size(), &vhe6Z[0], &vevZ[0]);
		diffZ->SetTitle("{}^{6}He angle deviation based on beam energy and {}^{1}H angle");
		diffZ->GetXaxis()->SetTitle("LAB angle of protons [deg]");
		diffZ->GetXaxis()->CenterTitle();
		diffZ->GetYaxis()->SetTitle("LAB angle deviation of protons [deg]");
		diffZ->GetYaxis()->CenterTitle();
/*
		TGraph *resGAngAng1geo3 = new TGraph(cpy2Sqlang1.size(), &cpy2Sqlang1[0],  &resAngAng1geo3[0]);

		TGraph *resGAngE1 = new TGraph(vecdELang1H.size(), &vecdELang1H[0],  &resAngE1[0]);
		resGAngE1->SetTitle("{}^{1}H Energy deviation based on Eloss in Si det and {}^{1}H angle");
		resGAngE1->GetXaxis()->SetTitle("LAB angle of protons [deg]");
		resGAngE1->GetXaxis()->CenterTitle();
		resGAngE1->GetYaxis()->SetTitle("energy deviation for protons [MeV]");
		resGAngE1->GetYaxis()->CenterTitle();

		//@@@@@		deuter
		TGraph *tmpLangRang2H =  new TGraph(cpySqlang2.size(), &cpySqlang2[0], &tmpRang2[0]);

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
*/		TCanvas *myCanvas = new TCanvas("myCanvas", "Minimize results", 1200, 800);
		
		myCanvas->Divide(2,2);

		myCanvas->cd(1);		
		evX_detX.Draw("col");
		fitX->Draw("same");

		myCanvas->cd(2);
		evY_detY.Draw("cont");
		fitY->Draw("same");

		myCanvas->cd(3);
		histX.Draw("");

		myCanvas->cd(4);
		histY.Draw("");

		TString pathname = "/home/zalewski/Desktop/6He/analysis/movies/fixY/fixY_" + TString::Itoa(inPar[1]*10,10) + "_" + TString::Itoa(inPar[3]*10,10) + ".png";
		myCanvas->Print(pathname.Data());
		



/*
		TCanvas *myResPlotsCanv = new TCanvas("myResPlots", "residual plot", 1200, 800);
		myResPlotsCanv->Divide(2,2);

		myResPlotsCanv->cd(1);
		evX_evY.Draw("col");

		myResPlotsCanv->cd(2);
		detX_detY.Draw("col");

		myResPlotsCanv->cd(3);
		detX_detZ.Draw("col");
		evX_evZ.Draw("col, same");
		myResPlotsCanv->cd(4);
		
		myResPlotsCanv->Update();
		*/
	}


	evY_detY.Fit(fitY,"N");

	returner = fitY->GetChisquare();
	//int c = getchar();
}
