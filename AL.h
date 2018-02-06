// -*- mode:C++ -*-
#ifndef __AL_H__
#define __AL_H__ 1

class AL
{
protected:
  
public:
  AL();
  virtual ~AL()=0;
  virtual void
  Reconstruction()=0;
  
  ClassDef(AL,0);

};
#endif // __AL_H__
