#ifndef dE_E_angle_h
#define dE_E_angle_h 1
#include <TLorentzVector.h>
#include <TTree.h>
#include <gsl/gsl_sf_lambert.h>
#include </home/guar/aku/ELC/AELC.h>
#include </home/guar/aku/ELC/ELC.h>
#include <TRandom3.h>
#include <Rtypes.h>
#include <TString.h>
#include <TMath.h>

#include "TOOL.h"
#include "constants.h"

class dE_E_angle
{
public:

dE_E_angle();
dE_E_angle(TTree *inTree, TTree *outTree);
virtual ~dE_E_angle();
bool actual_work();

private:
TTree *inTree;
TTree *outTree;
bool create_input_tree(TTree *inTree);
bool create_output_tree(TTree *outTree);


Bool_t mwpc, ms, tar;

int out_trigger, in_trigger, counter;

UShort_t in_nx1, in_nx2, in_ny1, in_ny2;
UShort_t in_x1[32], in_x2[32], in_y1[32], in_y2[32];
UShort_t CsI_L_strip[17], CsI_R_strip[17], SQX_L_strip[33], SQX_R_strip[17], SQY_L_strip[17], SQY_R_strip[17];
UShort_t out_nx1, out_nx2, out_ny1, out_ny2, out_x1[32], out_x2[32], out_y1[32], out_y2[32];
UShort_t CsI_L_mult, CsI_R_mult, SQX_L_mult, SQX_R_mult, SQY_L_mult, SQY_R_mult;
UShort_t memS_CsI_R, memS_CsI_L;

Float_t memE_CsI_R, memE_CsI_L;
Float_t blur, dist_tar_det;
Float_t dX,  dY,  dZ,  XZsum;
Float_t evX,  evY,  evZ;
Float_t Xpos,  Ypos,  Zpos;
Float_t X6He_det,  Y6He_det,  Z6He_det, X6He_lab,  Y6He_lab,  Z6He_lab;
Float_t X6He, Y6He, Z6He;
Float_t X2H_det,  Y2H_det,  Z2H_det, X2H_lab,  Y2H_lab,  Z2H_lab;
Float_t X2H, Y2H, Z2H;
Float_t lx, ly, lz;
Float_t rx, ry, rz;
Float_t virt_E, beta_squared, gamma, T, time, par_beta;
Float_t MWPC_1_X,  MWPC_1_Y,  MWPC_1_Z,  MWPC_2_X,  MWPC_2_Y,  MWPC_2_Z;

Double_t Tcoef;
Double_t CsI_L[16], CsI_R[16], SQX_L[32], SQX_R[32], SQY_L[16],	SQY_R[16];
Double_t c_CsI_L[16], c_CsI_R[16], c_SQX_L[32], c_SQX_R[32], c_SQY_L[16], c_SQY_R[16];
Double_t r_CsI_L[16], r_CsI_R[16], r_SQX_L[32], r_SQX_R[32], r_SQY_L[16], r_SQY_R[16];
Double_t raw_CsI_L[16], raw_CsI_R[16], raw_SQX_L[32], raw_SQX_R[32], raw_SQY_L[16], raw_SQY_R[16];
Double_t in_tF3[4],	in_F3[4], in_tF5[4], in_F5[4], in_tF6[4], in_F6[4];
Double_t in_tof, out_tof, in_T, out_T;
Double_t CsI_L_Edep[17], CsI_R_Edep[17], SQX_L_Edep[33], SQX_R_Edep[33], SQY_L_Edep[17], SQY_R_Edep[17];
Double_t out_tF3[4], out_F3[4], out_tF5[4], out_F5[4], out_tF6[4], out_F6[4];
Double_t sqlde, sqletot, sqlphi, sqltheta, sqlang, sqltime;
Double_t sqrde, sqretot, sqrphi, sqrtheta, sqrtheta2, sqrang, sqrtime;
Double_t missMass, mom_2H, ene_2H, mom_6He, ene_6He, mom_beam, ene_beam;
Double_t sqltheo, sqrtheo;
Double_t in_tSQX_L[32], in_tSQX_R[32], out_tSQX_L[32], out_tSQX_R[32];
Double_t in_tSQY_L[16], in_tSQY_R[16], out_tSQY_L[16], out_tSQY_R[16];
Double_t in_tCsI_L[16], in_tCsI_R[16], out_tCsI_L[16], out_tCsI_R[16];
Double_t SQR_ang, SQL_ang, SQR_dist, SQL_dist;
Double_t t_Tar, t_2H, t_6He, dist_tar_det6He, dist_tar_det2H;
Float_t tar_angle, ene_draw, out_tMWPC[4],  in_tMWPC[4];

Double_t cut_SQX_L, cut_SQX_R, cut_SQY_L, cut_SQY_R, cut_CsI_L, cut_CsI_R; 

//double gsl_sf_lambert_Wm1(double in);
TLorentzVector *LV_6He, *LV_2H, *LV_beam, *LV_Tar, *LV_draw;
TRotation beam_setting_array;


AELC *Si_Ecalc;
TOOL *maynard;

double si_A[1];
double si_Z[1];
double si_W[1];
ClassDef(dE_E_angle,0);
};
#endif
