#include "ELC.h"

/////////////////////////////////////////////////////////////////////////
//
//ELC
//
//
/////////////////////////////////////////////////////////////////////////



extern "C" void eloss_(int *nel,
		       double *zel,double *ael,double *wel, 
		       double *den,double *zp, double *ap,
		       int *ne,double *etab,double *rtab,
		       double *zw, double *aw);

ELC::ELC(void){
  //
  //Default constructor
  //  
  fElementsNum = 0;
  fDensity = 0;
  fEnergyMax = 0;  
  fEnergyPointsNum = 0;
  
  Zion = 0;
  Aion = 0;
  
  is_ready = false;
}

ELC::ELC(int Ap,int Zp,
	 int Nel,double density, double * A, double * Z,
	 double * W,double Emax, int Epoints){
  //Constructor. It sets the number of elements, density of material,
  //Z,A,W arrays of elements, max. energy of particle, number points
  //in energy table, Z and A of particle
  
  //gsl alloc
  acc_E_of_R = gsl_interp_accel_alloc ();
  acc_R_of_E = gsl_interp_accel_alloc ();
  spline_E_of_R = gsl_spline_alloc (gsl_interp_cspline,Epoints);
  spline_R_of_E = gsl_spline_alloc (gsl_interp_cspline,Epoints);
  
  fElementsNum = Nel;
  fDensity = density;
  fEnergyMax = Emax;
  fEnergyPointsNum = Epoints;
  
  SetEtab();
  
  Zion = Zp;
  Aion = Ap;
  fZElement = new double [fElementsNum];
  fAElement = new double [fElementsNum];
  fWElement = new double [fElementsNum];
  for(int i =0;i<fElementsNum;i++){
    fZElement[i]=Z[i];
    fAElement[i]=A[i];
    fWElement[i]=W[i];
  }
  
  CallEloss();
  //throw check
    
  // gsl init
  gsl_spline_init(spline_R_of_E,fETable,fRTable,fEnergyPointsNum);
  gsl_spline_init(spline_E_of_R,fRTable,fETable,fEnergyPointsNum);
  is_ready = true;
}

ELC::~ELC(void){
  //
  //Destructor
  //
 
  if(fZElement){ delete [] fZElement; fZElement=0;}
  if(fAElement){ delete [] fAElement; fAElement=0;}
  if(fWElement){ delete [] fWElement; fWElement=0;}
  if( fETable ){ delete []  fETable ;  fETable =0;}
  if( fRTable ){ delete []  fRTable ;  fRTable =0;}
    
  //gsl free
  gsl_spline_free (spline_E_of_R);
  gsl_spline_free (spline_R_of_E);
  gsl_interp_accel_free (acc_R_of_E);
  gsl_interp_accel_free (acc_E_of_R);
} 

void ELC::SetEtab(void){
  //
  //Set list of energies
  //
  const double Energy_i = 0.;
  double EnergyStep;    // Energy step in table
  
  fETable = new double [fEnergyPointsNum];
  fRTable = new double [fEnergyPointsNum];
  EnergyStep=(fEnergyMax-Energy_i)/(double)(fEnergyPointsNum-1);  
  
  fETable[0]=Energy_i;
  for(int i = 1; i < fEnergyPointsNum;i++){
    fETable[i] =fETable[i-1]+EnergyStep;
    
  }
}

void ELC::CallEloss(void){
  //
  // Call energy losses calculation
  //
  double zw,aw,zp,ap;
  double coef = 10. / fDensity;  //== convertion mg/cm^2 -> micron
  eloss_(&fElementsNum,fZElement,fAElement,fWElement,&fDensity,
	 &(zp=(double)Zion),
	 &(ap = (double) Aion),
	 &fEnergyPointsNum, 
	 fETable, fRTable,&zw,&aw);
  for(int i = 0; i<fEnergyPointsNum;i++)
    fRTable[i]=coef*fRTable[i];
}

double ELC::GetR(const double e0,const double e){
  //
  //Calculate rase lenght using linear interpolation
  //
  return R_of_E(e0) - R_of_E(e);
} 
double ELC::GetE(const double e0, const double r){
  //
  //Calculate new energy using linear interpolation
  //
  
  double r0 = R_of_E(e0);
  if (r0 < r) return 0;
  
  return E_of_R(r0-r);
} 
