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
protected:
Double_t beta, beta_squared, gamma, gamma_squared;
Float_t displacement, zero_position, alpha_inSi[4];
void printSetup(Double_t , Double_t , Double_t , Double_t , Float_t );

public:

TOOL();
virtual ~TOOL();
TString containerName, histName, histFillcmd;

Double_t getT(Double_t , Float_t );
Double_t getVelo(Double_t , Float_t );
Double_t gettime(Double_t , Float_t , Float_t);
bool Get_MWPC_pos(UShort_t, UShort_t *, Float_t *, Short_t);
bool initializeGeometry(Double_t *, Double_t *, Double_t *, Double_t *, Float_t *);
bool getTarCuts(Float_t *, Float_t *, Float_t *, Float_t *);
bool getTimeCorrectionForDets(	Float_t *, Float_t *, Float_t *,
								Float_t *, Float_t *, Float_t *);
bool getDeadLayer(TString, TString, double *, Short_t);

void null_strips(	UShort_t *, UShort_t *, UShort_t *,
					UShort_t *, UShort_t *, UShort_t *);
void null_energy(	Double_t *, Double_t *, Double_t *,
					Double_t *, Double_t *, Double_t *);

bool params_loader(TString , float *, float *, short);
bool params4_loader(TString , Float_t *,  Float_t *, Float_t *, Float_t *);
bool params5_loader(TString , Float_t *,  Float_t *, Float_t *, Float_t *, Float_t *);
bool gcuts_loader(TString , TCutG *, TString );
int gcut_noPoints(TString fName, TString ion);
bool data_loader(TString , Short_t , Short_t, Short_t);

Float_t kin_GetAngDeut(Float_t , Float_t );
Float_t kin_GetDeutE(Float_t , Float_t );
Float_t kin_GetAngHel(Float_t T_deut, Float_t T_beam);


ClassDef(TOOL,0);
};
#endif
