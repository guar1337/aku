#ifndef __ELC_H__
#define __ELC_H__

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
  double fEnergyMax;
  int fEnergyPointsNum;  //  number of points in graph   
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
    
  ELC(int Ap,int Zp,int Nel,double density, 
      double * A, double * Z, double * W,
      double Emax, int Epoints);
  virtual ~ELC(void);  
  //  void PlotRE();
  virtual double GetE(const double e0, const double r);
  //  double GetE0dE(double de, double r); //de in MeV, r in microns

  virtual double GetR(const double E0,const double E1);
  

};

#endif
