#ifndef tinderh
#define tinderh

#include <vector>
#include <Rtypes.h>
#include <TTreeReader.h>
#include <TFile.h>
#include <TVector3.h>
#include "/home/zalewski/aku/wrk/ELC_legacy/AELC.h"
#include "/home/zalewski/aku/wrk/ELC_legacy/ELC.h"
#include "/usr/local/include/TString.h"
#include "/usr/local/include/TCanvas.h"
#include "/usr/local/include/TFile.h"
#include "/usr/local/include/TTreeReader.h"
#include "/usr/local/include/TLorentzVector.h"
#include "/usr/local/include/TRandom3.h"
#include "/usr/local/include/TGraph.h"
#include "/usr/local/include/TF1.h"
#include "/usr/local/include/TH1.h"
#include "/usr/local/include/TH2.h"
#include "/home/zalewski/aku/wrk/constants.h"
#include "/usr/local/include/TApplication.h"
#include "/usr/local/include/TSystem.h"

class finderC : public TQObject
{
    public:
        TFile *inF;
		Float_t tarPosZ, tarThcknss, tarAngle, SQLang, SQRang, SQLdist, SQRdist, lvsqlang, lvsqrang, tarThickness;
		Float_t X2Hlab, Y2Hlab, Z2Hlab, X6Helab, Y6Helab, Z6Helab;
		Float_t X2Hdet, Y2Hdet, Z2Hdet, X6Hedet, Y6Hedet, Z6Hedet;
		Float_t evX, evY, evZ, Tcoef;
		Float_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
		Float_t sqlphi, sqltheta, sqrphi, sqrtheta, mml, sqlang, sqrang;

		int CD2_Nel=2;
		Double_t CD2_A[2]={2, 12};
		Double_t CD2_Z[2]={1, 6};
		Double_t CD2_W[2]={2, 1};

		int si_Nel=1;
		Double_t si_A[1]={28};
		Double_t si_Z[1]={14};
		Double_t si_W[1]={1};

		AELC *h1Si;
		AELC *h1CD2;
		AELC *h2Si;
		AELC *h2CD2;
		AELC *he6Si;
		AELC *he6CD2;
	Float_t SQX_L_sNo;
	Float_t SQX_R_sNo;
	Float_t SQY_L_sNo;
	Float_t SQY_R_sNo;
	Double_t fsqlde;
	Double_t sqletot;
	Double_t sqrde;
	Double_t sqretot;
	Float_t MWPC_1_X;
	Float_t MWPC_1_Y;
	Float_t MWPC_1_Z;
	Float_t MWPC_2_X;
	Float_t MWPC_2_Y;
	Float_t MWPC_2_Z;
	Short_t geo;
	Bool_t deu;
	Bool_t pro;
	Bool_t dEAngle;
	Double_t kinE;
	Bool_t kineProB;
	Bool_t kineDeuB;
	TLorentzVector *LV_beam;

		TGraph *tmpLangRang1H;
		TLorentzVector *lvHe6;
		TLorentzVector *lvH1;
		TLorentzVector *lvH2;
		TLorentzVector *lvTar1H;
		TLorentzVector *lvTar2H;
		//double params[4] = {1.0,1.0,0.0,0.0};

		finderC();
		int looper(double *inPar);
		bool miniCaller();
		Double_t myAngAngFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam);
		Double_t myAngEneFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam);
		void b(int);
		int finder();
		int counter = 0;
		double residual_;
ClassDef(finderC, 0);
};
#endif