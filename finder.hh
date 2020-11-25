#ifndef finderh
#define finderh

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
#include "/usr/local/include/TFitter.h"
#include "/usr/local/include/TStopwatch.h"
#include "/usr/local/include/TMinuit.h"
#include "/usr/local/include/TLatex.h"

class finderC : public TQObject
{
    public:
        TFile *inF;
		Float_t tarPosZ, tarThcknss, tarAngle, SQLang, SQRang, lvsqlang, lvsqrang, tarThickness;
		Float_t X2Hlab, Y2Hlab, Z2Hlab, X6Helab, Y6Helab, Z6Helab;
		Float_t X2Hdet, Y2Hdet, Z2Hdet, X6Hedet, Y6Hedet, Z6Hedet;
		Float_t evX, evY, evZ, Tcoef;
		Float_t X2H, Y2H, Z2H, X6He, Y6He, Z6He;
		Float_t sqlphi, sqltheta, sqrphi, sqrtheta, mml, sqlang, sqrang;

		TGraph *tmpLangRang1H;
		TLorentzVector *lvHe6;
		TLorentzVector *lvH1;
		TLorentzVector *lvH2;
		TLorentzVector *lvTar1H;
		TLorentzVector *lvTar2H;
		//double params[4] = {1.0,1.0,0.0,0.0};

		finderC();
		
		void miniCaller();
		static Double_t myAngAngFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam);
		static Double_t myAngEneFit(Double_t m_leftAngle, Double_t tarMass, TLorentzVector m_lvBeam);
		void b(int);
		void finder();
		int counter = 0;
		double residual;
};
#endif