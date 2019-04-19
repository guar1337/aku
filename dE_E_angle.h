#ifndef dE_E_angle_h
#define dE_E_angle_h 1
#include <TLorentzVector.h>
#include <TTree.h>
#include <gsl/gsl_sf_lambert.h>
#include "ELC/AELC.h"
#include "ELC/ELC.h"
#include <TRandom3.h>
#include <Rtypes.h>
#include <TString.h>
#include <TMath.h>
#include <TCutG.h>
#include <TVectorT.h>

#include "TOOL.h"
#include "constants.h"

class dE_E_angle
{
public:

dE_E_angle();
dE_E_angle(TTree *inTree, TTree *outTree, TString inFile, int geoNo);
virtual ~dE_E_angle();
Float_t actual_work_gas();
Float_t actual_work(Int_t);
Float_t actual_work(Int_t, Float_t, Float_t, std::vector<Float_t> &,  std::vector<Float_t> &,  std::vector<Float_t> &,  std::vector<Float_t> &);

private:
TTree *inTree;
TTree *outTree;
bool create_input_tree(TTree *inTree);
bool create_output_tree(TTree *outTree);


Bool_t he6, angAng1H, angAng2H;

int out_trig, in_trig, counter;

UShort_t in_nx1, in_nx2, in_ny1, in_ny2;
UShort_t in_x1[32], in_x2[32], in_y1[32], in_y2[32];
UShort_t CsI_L_strip[17], CsI_R_strip[17], SQX_L_strip[33], SQX_R_strip[17], SQY_L_strip[17], SQY_R_strip[17], SQ300_strip[17];
UShort_t out_nx1, out_nx2, out_ny1, out_ny2, out_x1[32], out_x2[32], out_y1[32], out_y2[32];
UShort_t CsI_L_mult, CsI_R_mult, SQX_L_mult, SQX_R_mult, SQY_L_mult, SQY_R_mult, SQ300_mult;
UShort_t memS_CsI_R, memS_CsI_L, memS_CsI_0L, Ion_ID, Run_ID, Geo_ID, s_csir, s_csil;
Short_t run;

Int_t rest_of_events;

Float_t memE_CsI_R, memE_CsI_L, memE_CsI_0L;
Float_t dist_tar_det;
Float_t dX,  dY,  dZ,  XZsum;
Float_t evX,  evY,  evZ, f5X,  f5Y,  f5Z, f6X,  f6Y,  f6Z;
Float_t Xpos,  Ypos,  Zpos;
Float_t X6He_det,  Y6He_det,  Z6He_det, X6He_lab,  Y6He_lab,  Z6He_lab;
Float_t X6He, Y6He, Z6He;
Float_t X2H_det,  Y2H_det,  Z2H_det, X2H_lab,  Y2H_lab,  Z2H_lab;
Float_t X2H, Y2H, Z2H;
//Float_t virt_E, beta_squared, gamma, time, par_beta;
Float_t MWPC_1_X,  MWPC_1_Y,  MWPC_1_Z,  MWPC_2_X,  MWPC_2_Y,  MWPC_2_Z;


Float_t dummy01, dummy02, dummy1, dummy2;

Double_t SQ300[16], r_SQ300[16], in_tSQ300[16], SQ300_Edep[16];
Double_t CsI_L[16], CsI_0L[16], CsI_R[16], SQX_L[32], SQX_Ln[32], SQX_R[32], SQY_L[16],	SQY_R[16];
Double_t c_CsI_L[16], c_CsI_R[16], c_SQX_L[32], c_SQX_R[32], c_SQY_L[16], c_SQY_R[16];
Double_t r_CsI_L[16], r_CsI_R[16], r_SQX_L[32], r_SQX_R[32], r_SQY_L[16], r_SQY_R[16];
Double_t raw_CsI_L[16], raw_CsI_R[16], raw_SQX_L[32], raw_SQX_R[32], raw_SQY_L[16], raw_SQY_R[16];
Double_t in_tF3[4],	in_F3[4], in_tF5[4], in_F5[4], in_tF6[4], in_F6[4];
Double_t in_tof, out_tof, tempT1, tempT2, out_T1, out_T2, T, in_AZ, out_AZ;
Double_t CsI_L_Edep[17], CsI_R_Edep[17], SQX_L_Edep[33], SQX_L_Edep2[33], SQX_R_Edep[33], SQY_L_Edep[17], SQY_R_Edep[17];
Double_t out_tF3[4], out_F3[4], out_tF5[4], out_F5[4], out_tF6[4], out_F6[4];
Double_t sqlde, sqletot, kinsqle_1H, kinsqle_2H, sqlphi, sqltheta, fsqltheta_1H, fsqltheta_2H, sqlang, sqlxtime, sqlytime, fel_2H, fdel_2H, ftot;
Double_t sqrde, sqretot, sqrphi, sqrtheta, fsqrtheta1, fsqrtheta2, sqrang, sqrxtime, sqrytime;

Double_t mml, mom_2H, ene_2H;
Double_t mom_6He, ene_6He, mom_beam, ene_beam;

Double_t in_tSQX_L[32], in_tSQX_R[32], out_tSQX_L[32], out_tSQX_R[32];
Double_t in_tSQY_L[16], in_tSQY_R[16], out_tSQY_L[16], out_tSQY_R[16];
Double_t in_tCsI_L[16], in_tCsI_R[16], out_tCsI_L[16], out_tCsI_R[16];
Double_t SQR_ang, SQL_ang, SQR_dist, SQL_dist;
Double_t t_Tar, in_aF5, out_aF5;
Float_t tar_angle, kine_2H, kine_1H, out_tMWPC[4],  in_tMWPC[4], tar_thcknss;
Float_t tar_cut_lo_X, tar_cut_hi_X, tar_cut_lo_Y, tar_cut_hi_Y;
Float_t tcor_sqLX_I, tcor_sqLX_II, tcor_sqLY, tcor_sqRX_I, tcor_sqRX_II, tcor_sqRY;

Double_t cut_SQX_L, cut_SQX_R, cut_SQY_L, cut_SQY_R, cut_CsI_L, cut_CsI_R;
Double_t Si_L_bank, Tcoef;
Int_t cr;

Float_t pede1[16], A1[16], B1[16], C1[16], D1[16];
Float_t pede2[16], A2[16], B2[16], C2[16], D2[16];
Float_t pede3[16], A3[16], B3[16], C3[16], D3[16];
Float_t pede4[16], A4[16], B4[16], C4[16], D4[16];
Float_t pede[16];
Float_t B[16];
Float_t C[16];
Float_t D[16];


//double gsl_sf_lambert_Wm1(double in);
TLorentzVector *LV_6He, *LV_2H, *LV_beam, *LV_tar_2H;
TRotation beam_setting_array;
TString s_curFile;

AELC *h2_Si;
AELC *h2_CsI;
AELC *h2_BoPET;
AELC *h2_CD2;

AELC *h3_Si;
AELC *he4_Si;

AELC *he6_Si;
AELC *he6_CsI;
AELC *he6_BoPET;
AELC *he6_CD2;

AELC *li7_Si;
AELC *li8_Si;
AELC *be9_Si;
TOOL *maynard;

TCutG *gcut_h2, *gcut_h3, *gcut_he4, *gcut_he6, *gcut_li7, *gcut_li8;
TCutG *gcut_be9, *gcut_dehe6, *gcut_AngAng1H_w6He, *gcut_AngAng2H_w6He;
TF1 *angAngFit_2H = new TF1();

double si_A[1];
double si_Z[1];
double si_W[1];
double csi_A[2];
double csi_Z[2];
double csi_W[2];

double CD2_A[2];
double CD2_Z[2];
double CD2_W[2];

double BoPET_A[3];
double BoPET_Z[3];
double BoPET_W[3];

TVector3 *vBeam, *vTarget;
TRandom3 *rnd;

ClassDef(dE_E_angle,0);
};
#endif
