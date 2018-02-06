#ifndef __ELC_H__
#define __ELC_H__
#include <Rtypes.h>
#include <iostream>
#include "AELC.h"

#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>

using namespace std;

class ELC: public AELC{
  // simple energy loss calculator
protected:
  //material
  int fElementsNum;  //number of chemical elements in material
  double * fZElement;   //!
  double * fAElement;   //!
  double * fWElement;  //!
  double fDensity;    //density in g/cm3
  
  //E-range graph
  Double_t fEnergyMax;
  Int_t fEnergyPointsNum;  //  number of points in graph   
  double * fETable; 
  double * fRTable; 

  void CallEloss(void);    
  void SetEtab(void);

  inline double R_of_E(double E){
    return gsl_spline_eval(spline_R_of_E,E,acc_R_of_E); 
  }
  inline double E_of_R(double R){
    return gsl_spline_eval(spline_E_of_R,R,acc_E_of_R); 
  }

  // gsl inerpolators
  gsl_interp_accel *acc_E_of_R;
  gsl_interp_accel *acc_R_of_E;
  gsl_spline *spline_E_of_R;
  gsl_spline *spline_R_of_E;
  
public:
  ELC();
    
  ELC(int Ap,int Zp,int Nel,Double_t density, 
      Double_t * A, Double_t * Z, Double_t * W,
      Double_t Emax, Int_t Epoints);
  virtual ~ELC(void);  
  //  void PlotRE();
  virtual double GetE(const Double_t e0, const Double_t r);
  //  double GetE0dE(Double_t de, Double_t r); //de in MeV, r in microns

  virtual double GetR(const double E0,const double E1);
  
  ClassDef(ELC,0);
};

#endif
