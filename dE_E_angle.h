#ifndef dE_E_angle_h
#define dE_E_angle_h 1
#include "AL.h"
#include "AELC.h"
#include "TLorentzVector.h"
#include "ELC.h"
#include "TF1.h"

class dE_E_angle: public AL
{
public:

dE_E_angle();
dE_E_angle(TTree *inTree, TTree *outTree);
virtual ~dE_E_angle();

bool create_input_tree(TTree *inTree);
bool create_output_tree(TTree *outTree);

void null_strips(UShort_t *SQX_L,  UShort_t *SQY_L,  UShort_t *CsI_L,
                 UShort_t *SQX_R,  UShort_t *SQY_R,  UShort_t *CsI_R);

void null_calib_data(Double_t  *SQX_L, Double_t  *SQY_L, Double_t  *CsI_L,
					 Double_t  *SQX_R, Double_t  *SQY_R, Double_t  *CsI_R);

void null_energy( Double_t  *SQX_L, Double_t  *SQY_L, Double_t  *CsI_L,
                  Double_t  *SQX_R, Double_t  *SQY_R, Double_t  *CsI_R);

void null_MWPC(UShort_t *x1, UShort_t *x2, UShort_t *y1, UShort_t *y2);

void actual_work();

Bool_t mwpc;

int out_trigger, in_trigger;

UShort_t in_nx1, in_nx2, in_ny1, in_ny2;
UShort_t in_x1[32], in_x2[32], in_y1[32], in_y2[32];
UShort_t CsI_L_strip[17], CsI_R_strip[17], SQX_L_strip[17], SQX_R_strip[17], SQY_L_strip[17], SQY_R_strip[17];
UShort_t out_nx1, out_nx2, out_ny1, out_ny2, out_x1[32], out_x2[32], out_y1[32], out_y2[32];
UShort_t CsI_L_mult, CsI_R_mult, SQX_L_mult, SQX_R_mult, SQY_L_mult, SQY_R_mult;

Float_t MWPC_1_X,  MWPC_1_Y,  MWPC_1_Z,  MWPC_2_X,  MWPC_2_Y,  MWPC_2_Z;
Float_t dX,  dY,  dZ,  XZsum;
Float_t evX,  evY,  evZ;
Float_t Xpos,  Ypos,  Zpos;
Float_t X6He,  Y6He,  Z6He;
Float_t X2H,  Y2H,  Z2H;

Double_t CsI_L[16], CsI_R[16], SQX_L[16], SQX_R[16], SQY_L[16],	SQY_R[16];
Double_t c_CsI_L[16], c_CsI_R[16], c_SQX_L[16], c_SQX_R[16], c_SQY_L[16], c_SQY_R[16];
Double_t in_tF3[4],	in_F3[4], in_tF5[4], in_F5[4];
Double_t in_tof, out_tof, in_T, out_T;
Double_t CsI_L_Edep[17], CsI_R_Edep[17], SQX_L_Edep[17], SQX_R_Edep[17], SQY_L_Edep[17], SQY_R_Edep[17];
Double_t out_tF3[4], out_F3[4], out_tF5[4], out_F5[4];
Double_t sqlde, sqletot, sqlphi, sqltheta, sqlang;
Double_t sqrde, sqretot, sqrphi, sqrtheta, sqrang;
Double_t missMass;

TLorentzVector lvBeam, lv2h, lv6he, lvTar;
TF1 *rnd;
AELC * deut_poly_Elo;	
double deut_poly_Elo_A[2];
double deut_poly_Elo_Z[2];
double deut_poly_Elo_W[2];

  ClassDef(dE_E_angle,0);
 };
#endif
