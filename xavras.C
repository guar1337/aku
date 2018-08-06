#include <iostream>
#include <TROOT.h>
#include <TSystem.h>
#include <TString.h>
#include "constants.h"
#include "dE_E_angle.h"
#include "TOOL.h"

R__LOAD_LIBRARY(libPhysics.so); // !! IF NOT WORKING, TRY **gSystem->Load("/home/guar/Desktop/Eloss/trial/libelo.so");** instead of
R__LOAD_LIBRARY(libgsl.so); //**R__LOAD_LIBRARY(/home/guar/Desktop/Eloss/trial/libelo.so);**
R__LOAD_LIBRARY(/home/guar/aku/ELC/libEloss.so);
R__LOAD_LIBRARY(/home/guar/aku/wrk/libMr_Blue_Sky.so);

void xavras()
{
TOOL *maynard = new TOOL();
Float_t CsI_par1[16];
Float_t CsI_par2[16];
Float_t CsI_par3[16];
Float_t CsI_par4[16];
Float_t CsI_par5[16];
Short_t A=2, Z=1, detNo=0;
TString runNo1{"L1"}, runNo0{"L0"};
/*
for (Short_t iii = 0; iii < 16; ++iii)
{
	maynard->data_loader(runNo0, 2, 1, iii);
	maynard->data_loader(runNo1, 2, 1, iii);
	maynard->data_loader(runNo0, 3, 1, iii);
	maynard->data_loader(runNo1, 3, 1, iii);
	maynard->data_loader(runNo0, 6, 2, iii);
	maynard->data_loader(runNo1, 6, 2, iii);
	printf("\n\n^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n");
}
*/


}
