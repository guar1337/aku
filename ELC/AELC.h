// -*- mode:C++ -*-
#ifndef __AELC_H__
#define __AELC_H__ 1

class AELC
{
  // abstract class for energy loss calculation
  // in approximation dE = f(E,Rase)
protected:
  bool is_ready; // ready to use flag
  int  Zion;  //Z of ion
  int  Aion;  //A of ion
public:
  AELC(){;};
  virtual ~AELC()=0;
  virtual double GetE(const double E0,const double R)=0;
  virtual double  GetR(const double E0,const double E1)=0;
  
  virtual bool IsReady(){return is_ready;}

};

#endif
