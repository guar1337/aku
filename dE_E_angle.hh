#ifndef ReCoBuild_h
#define ReCoBuild_h 1

Double_t CsI_L[16];
Double_t CsI_R[16];
Double_t SQX_L[16];
Double_t SQX_R[16];
Double_t SQY_L[16];
Double_t SQY_R[16];

Double_t c_CsI_L[16];
Double_t c_CsI_R[16];
Double_t c_SQX_L[16];
Double_t c_SQX_R[16];
Double_t c_SQY_L[16];
Double_t c_SQY_R[16];

Double_t in_tF3[4];
Double_t in_F3[4];
Double_t in_tF5[4];
Double_t in_F5[4];

UShort_t in_nx1;
UShort_t in_nx2;
UShort_t in_ny1;
UShort_t in_ny2;

UShort_t in_x1[32];
UShort_t in_x2[32];
UShort_t in_y1[32];
UShort_t in_y2[32];

int in_trigger;
Double_t in_tof;
Double_t out_tof;
Double_t in_T;
Double_t out_T;

//out tree branches
UShort_t CsI_L_mult;
UShort_t CsI_R_mult;
UShort_t SQX_L_mult;
UShort_t SQX_R_mult;
UShort_t SQY_L_mult;
UShort_t SQY_R_mult;

Double_t CsI_L_Edep[17];
Double_t CsI_R_Edep[17];
Double_t SQX_L_Edep[17];
Double_t SQX_R_Edep[17];
Double_t SQY_L_Edep[17];
Double_t SQY_R_Edep[17];

UShort_t CsI_L_strip[17];
UShort_t CsI_R_strip[17];
UShort_t SQX_L_strip[17];
UShort_t SQX_R_strip[17];
UShort_t SQY_L_strip[17];
UShort_t SQY_R_strip[17];

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

int out_trigger;


Double_t sqlde;
Double_t sqletot;
Double_t sqlphi;
Double_t sqltheta;
Double_t sqlphi2;
Double_t sqltheta2;
Double_t sqlphi3;
Double_t sqltheta3;
Double_t sqlang;

Double_t sqrde;
Double_t sqretot;
Double_t sqrphi;
Double_t sqrtheta;
Double_t sqrphi2;
Double_t sqrtheta2;
Double_t sqrphi3;
Double_t sqrtheta3;
Double_t sqrang;

Double_t relabAngHe;
Double_t relabAng2H;
Double_t rethetaCM;
Double_t reTbeam;

Float_t Xpos;
Float_t Ypos;
Float_t Zpos;

Float_t X6He;
Float_t Y6He;
Float_t Z6He;

Float_t X2H;
Float_t Y2H;
Float_t Z2H;

Float_t MWPC_1_X;
Float_t MWPC_1_Y;
Float_t MWPC_1_Z;
Float_t MWPC_2_X;
Float_t MWPC_2_Y;
Float_t MWPC_2_Z;
Float_t dX;
Float_t dY;
Float_t dZ;
Float_t XZsum;
Float_t evX;
Float_t evY;
Float_t evZ;

Bool_t mwpc;




#endif
