// -*- mode:C++ -*-
#ifndef __AL_H__
#define __AL_H__ 1
#include "TTree.h"
#include "TRandom.h"


class AL
{
protected:
TTree * inTree;
TTree * outTree;
public:
AL(TTree * in,TTree * out);
virtual bool create_input_tree(TTree * inT)=0;
virtual bool create_output_tree(TTree * outT)=0;

AL();
virtual ~AL()=0;
virtual void actual_work()=0;
  
ClassDef(AL,0);
};
#endif // __AL_H__
