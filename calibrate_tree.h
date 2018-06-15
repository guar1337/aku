#ifndef ReCoBuild_h
#define ReCoBuild_h 1

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

#include </home/guar/aku/ELC/AELC.h>
#include </home/guar/aku/ELC/ELC.h>

AELC *Si_Ecalc;
TOOL *maynard;

double si_A[1];
double si_Z[1];
double si_W[1];

UShort_t in_CsI_L[16];
UShort_t in_CsI_R[16];
UShort_t in_SQX_L[32];
UShort_t in_SQX_R[32];
UShort_t in_SQY_L[16];
UShort_t in_SQY_R[16];

UShort_t in_tSQX_L[32];
UShort_t in_tSQX_R[32];
UShort_t in_tCsI_L[16];
UShort_t in_tCsI_R[16];
UShort_t in_tSQY_L[16];
UShort_t in_tSQY_R[16];


UShort_t in_tdcF3[4];
UShort_t in_aF3[4];
UShort_t in_tdcF5[4];
UShort_t in_aF5[4];
UShort_t in_tdcF6[4];
UShort_t in_aF6[4];

UShort_t in_nx1;
UShort_t in_nx2;
UShort_t in_ny1;
UShort_t in_ny2;

UShort_t in_x1[32];
UShort_t in_x2[32];
UShort_t in_y1[32];
UShort_t in_y2[32];
UShort_t in_tMWPC[4];

int in_trigger, counter;

//out tree branches
Double_t out_CsI_L[16];
Double_t out_CsI_R[16];
Double_t out_SQX_L[32];
Double_t out_SQX_R[32];
Double_t out_SQY_L[16];
Double_t out_SQY_R[16];

Double_t out_tSQX_L[32];
Double_t out_tSQX_R[32];
Double_t out_tCsI_L[16];
Double_t out_tCsI_R[16];
Double_t out_tSQY_L[16];
Double_t out_tSQY_R[16];

Float_t MWPC_1_X,  MWPC_1_Y,  MWPC_1_Z,  MWPC_2_X,  MWPC_2_Y,  MWPC_2_Z;

Double_t r_CsI_L[16];
Double_t r_CsI_R[16];
Double_t r_SQX_L[32];
Double_t r_SQX_R[32];
Double_t r_SQY_L[16];
Double_t r_SQY_R[16];

UShort_t out_nx1;
UShort_t out_nx2;
UShort_t out_ny1;
UShort_t out_ny2;

UShort_t out_x1[32];
UShort_t out_x2[32];
UShort_t out_y1[32];
UShort_t out_y2[32];

Double_t out_tF3[4];
Double_t out_F3[4];
Double_t out_tF5[4];
Double_t out_F5[4];
Double_t out_tF6[4];
Double_t out_F6[4];

Float_t out_tMWPC[4];

float a_CsI_L[16];
float a_CsI_R[16];
float a_SQX_L[32];
float a_SQX_R[32];
float a_tSQX_L[32];
float a_tSQX_R[32];
float a_tSQY_L[16];
float a_tSQY_R[16];
float a_tCsI_R[16];
float a_tCsI_L[16];
float a_SQY_L[16];
float a_SQY_R[16];
float pede_CsI_L[16];

float b_CsI_L[16];
float b_CsI_R[16];
float b_SQX_L[32];
float b_SQX_R[32];
float b_tSQX_L[32];
float b_tSQX_R[32];
float b_tSQY_L[16];
float b_tSQY_R[16];
float b_tCsI_R[16];
float b_tCsI_L[16];
float b_SQY_L[16];
float b_SQY_R[16];

int out_trigger;
Double_t tof;
Double_t T;
Double_t par_beta;


#endif
