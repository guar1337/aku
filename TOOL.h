#ifndef TOOL_h
#define TOOL_h 1
#include "constants.h"
#include <TSystem.h>
#include <TString.h>
#include <TH1I.h>
#include <TF1.h>
#include <TTree.h>
#include <TFile.h>
#include <TCutG.h>
#include <algorithm>
#include <Riostream.h>



class TOOL
{
public:
TOOL();
virtual ~TOOL();
Double_t getT(Double_t , Float_t );
Double_t getVelo(Double_t , Float_t );
Double_t gettime(Double_t , Float_t , Float_t);
bool Get_MWPC_pos(UShort_t, UShort_t *, Float_t *, Short_t);
bool getDeadLayer(TString, TString, double *, Short_t);

bool params_loader(TString , float *, float *, short);

bool gcuts_loader(TString , TCutG *, TString, int);
int gcut_noPoints(TString fName, TString ion, int);

Float_t kin_GetAngRecoil(Float_t , Float_t, Float_t);
Float_t kin_GetERecoil(Float_t , Float_t, Float_t);
Float_t kin_GetAngProjectile(Float_t , Float_t , Float_t);
Int_t GetRunNumber(TString);
void printSetup(Double_t , Double_t , Double_t , Double_t , Float_t );



protected:
Double_t beta, beta_squared, gamma, gamma_squared;
Float_t displacement, zero_position, alpha_inSi[4];
TString containerName, histName, histFillcmd;
ClassDef(TOOL,0);
};
#endif
