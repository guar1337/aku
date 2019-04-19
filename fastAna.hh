#ifndef fastAna_h
#define fastAna_h 1

#include <TROOT.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TLorentzVector.h>
#include <TRotation.h>

const TString fpath = "/home/guar/data/mar2018/dE/geos/shortF.root";
TFile *inFile = new TFile(fpath.Data(), "READ");

TRandom3 *rnd;
TTreeReader *fReader = new TTreeReader("shortT", inFile);

TTreeReaderValue<Double_t> tSQX_L = {*fReader, "tSQX_L"};
TTreeReaderValue<Double_t> tSQX_R = {*fReader, "tSQX_R"};

TTreeReaderValue<Double_t> SQX_L_e = {*fReader, "SQX_L_e"};
TTreeReaderValue<Double_t> SQX_R_e = {*fReader, "SQX_R_e"};
TTreeReaderValue<Double_t> CsI_L_e = {*fReader, "CsI_L_e"};
TTreeReaderValue<Double_t> CsI_R_e = {*fReader, "CsI_R_e"};

TTreeReaderValue<Short_t> SQX_L_s = {*fReader, "SQX_L_s"};
TTreeReaderValue<Short_t> SQX_R_s = {*fReader, "SQX_R_s"};
TTreeReaderValue<Short_t> SQY_L_s = {*fReader, "SQY_L_s"};
TTreeReaderValue<Short_t> SQY_R_s = {*fReader, "SQY_R_s"};
TTreeReaderValue<Short_t> CsI_L_s = {*fReader, "CsI_L_s"};
TTreeReaderValue<Short_t> CsI_R_s = {*fReader, "CsI_R_s"};

TTreeReaderValue<Float_t> evX = {*fReader, "evX"};
TTreeReaderValue<Float_t> evY = {*fReader, "evY"};
TTreeReaderValue<Float_t> evZ = {*fReader, "evZ"};

TTreeReaderValue<Double_t> tof = {*fReader, "tof"};
TTreeReaderValue<Double_t> aF5 = {*fReader, "aF5"};

TTreeReaderValue<Bool_t> angAng1H = {*fReader, "angAng1H"};
TTreeReaderValue<Bool_t> angAng2H = {*fReader, "angAng2H"};
TTreeReaderValue<TLorentzVector> lvBeam = {*fReader, "LV_beam."};

Double_t sqlang, sqrang, fsqlang, fsqrang, dX, dY, dZ, hX, hY, hZ;
Double_t dX0, dY0, dZ0, hX0, hY0, hZ0;
Double_t par_sqlang, par_sqrang, par_sqldist, par_sqrdist;
Double_t thetaCM;

TVector3 *v2H, *v6He;

std::vector<Float_t> v_sqlang1;
std::vector<Float_t> v_sqrang1;
std::vector<Float_t> v_sqlang2;
std::vector<Float_t> v_sqrang2;

std::vector<Float_t> v_fsqlang2_lv;		//for beam from dE_geo1.root
std::vector<Float_t> v_fsqrang2_lv;		//for beam from dE_geo1.root

std::vector<Float_t> v_fsqlang2_lv_cln;	//for beam from dE_geo1.root, but (0,0,1,M)
std::vector<Float_t> v_fsqrang2_lv_cln;	//for beam from dE_geo1.root, but (0,0,1,M)



constexpr Float_t width_strip_X{58.0/32};
constexpr Float_t width_strip_Y{58.0/16};
constexpr Float_t u_to_MeV{931.4936};
constexpr Float_t mass_1H{static_cast<Float_t>(1.00727647)*u_to_MeV};
constexpr Float_t mass_2H{static_cast<Float_t>(2.01410177)*u_to_MeV};
constexpr Float_t mass_6He{static_cast<Float_t>(6.01888589)*u_to_MeV};

const TLorentzVector lvTarget{0.0,0.0,0.0,mass_1H};
TLorentzVector lv6He, lv2H, lvCM;
//TLorentzVector m_lvBeam, m_lvH2, m_lvHe6;
TVector3 boostVect;

TLorentzVector *m_lvBeam;
TLorentzVector m_lvCM, m_lv2H, m_lv6He;

Double_t para1;
short counter1, counter2;

TVector3 m_vBoost;
std::ofstream outStream_1H;
std::ofstream outStream_2H;


TRotation *r;
TF1 *angAngFit_2H;
TF1 *angAngFit_2H_rel;
TF1 *angAngFit_1H_rel;
TF1 *f_left_det_nullPos;

#endif