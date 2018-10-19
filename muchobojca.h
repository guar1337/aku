#ifndef muchobojca_h
#define muchobojca_h 1

#include <iostream>
#include <vector>
#include <stdio.h>
#include "TFile.h"
#include "TObjArray.h"
#include "TTree.h"
#include "Riostream.h"
#include "constants.h"
#include "TOOL.h"
#include "dE_E_angle.h"
#include <TString.h>
#include <TRandom3.h>

#include "ELC/AELC.h"
#include "ELC/ELC.h"

class muchobojca
{
public:
muchobojca();
virtual ~muchobojca();
bool wrk(TTree *, TTree *, TString);
TOOL *maynard;

protected:


UShort_t in_CsI_L[16];
UShort_t in_CsI_R[16];
UShort_t in_SQX_L[32];
UShort_t in_SQX_R[32];
UShort_t in_SQY_L[16];
UShort_t in_SQY_R[16];
UShort_t in_SQ300[16];

UShort_t in_tSQX_L[32];
UShort_t in_tSQX_R[32];
UShort_t in_tCsI_L[16];
UShort_t in_tCsI_R[16];
UShort_t in_tSQY_L[16];
UShort_t in_tSQY_R[16];
UShort_t in_tSQ300[16];

UShort_t in_tdcF3[4];
UShort_t in_aF3[4];
UShort_t in_tdcF5[4];
UShort_t in_aF5[4];
UShort_t in_tdcF6[4];
UShort_t in_aF6[4];

UShort_t in_x1[32];
UShort_t in_x2[32];
UShort_t in_y1[32];
UShort_t in_y2[32];

UShort_t out_tF3[4];
UShort_t out_F3[4];
UShort_t out_tF5[4];
UShort_t out_F5[4];
UShort_t out_tF6[4];
UShort_t out_F6[4];

UShort_t in_nx1;
UShort_t in_nx2;
UShort_t in_ny1;
UShort_t in_ny2;

UShort_t out_nx1;
UShort_t out_nx2;
UShort_t out_ny1;
UShort_t out_ny2;


UShort_t out_x1[32];
UShort_t out_x2[32];
UShort_t out_y1[32];
UShort_t out_y2[32];
UShort_t in_tMWPC[4];

int counter, in_trig, out_trig;

//out tree branches
UShort_t out_CsI_L[16];
UShort_t out_CsI_R[16];
UShort_t out_SQX_L[32];
UShort_t out_SQX_R[32];
UShort_t out_SQY_L[16];
UShort_t out_SQY_R[16];
UShort_t out_SQ300[16];

UShort_t out_tSQX_L[32];
UShort_t out_tSQX_R[32];
UShort_t out_tCsI_L[16];
UShort_t out_tCsI_R[16];
UShort_t out_tSQY_L[16];
UShort_t out_tSQY_R[16];
UShort_t out_tSQ300[16];

UShort_t out_tMWPC[4];

Float_t MWPC_1_X, MWPC_1_Y, MWPC_1_Z;
Float_t MWPC_2_X, MWPC_2_Y, MWPC_2_Z;
Float_t dX,  dY,  dZ,  XZsum;
Double_t sumF5, tof;
Bool_t mwpc, amp, tac, tof_range;
Float_t a_tSQX_R[32], b_tSQX_R[32], tSQX_R[32], AZ;
Short_t sql_count, sqr_count;

ClassDef(muchobojca,0);
};
#endif
