#ifndef constants_h
#define constants_h 1
#include <Rtypes.h>
#include <TString.h>
#include <TMath.h>

namespace cs
{


	//*************************geometry**************************************************
	static const float		sql_ang7		=	70.0 * TMath::DegToRad();
	static const float		sqr_ang7		=	13.0 * TMath::DegToRad();
	static const float		sql_ang9		=	35.0 * TMath::DegToRad();
	static const float		sqr_ang9		=	18.0 * TMath::DegToRad();

	static const float		sql_ang_s0		=	0.0	* (3.1415/180.0);
	static const float		sqr_ang_s0		=	0.0	* (3.1415/180.0);

	static const float		tar_thcknss_7		=	100;
	static const float		tar_thcknss_9		=	10;
	static const float		tar_thcknss_0		=	20;


	//*************************DETS geometry**********************************************
	static const float		sqlDist0	=	170.0;
	static const float		sqrDist0	=	300.0;

	static const float		sqlDist1	=	170.0;
	static const float		sqrDist1	=	250.0;

	static const float		sqlDist2	=	170.0;
	static const float		sqrDist2	=	250.0;

	static const float		sqlDist3	=	170.0;
	static const float		sqrDist3	=	250.0;

	static const float		sqlDist4	=	170.0;
	static const float		sqrDist4	=	300.0;

	static const float		sqlDist5	=	170.0;
	static const float		sqrDist5	=	300.0;

	static const float		sqlDist7	=	170.0;
	static const float		sqrDist7	=	170.0;

	static const float		sqlDist9	=	170.0;
	static const float		sqrDist9	=	170.0;

	//*************************DETS DISPLACEMENT*******************************************
	static const float		widthStripX	=	1.8125;
	static const float		widthStripY	=	3.625;

	static const float		SQLzeroX	=	widthStripX * 15.5;//28.09375;
	static const float		SQLzeroY	=	-widthStripY * 7.5;//-27.1875;

	static const float		SQLstartX	=	SQLzeroX;
	static const float		SQLstartY	=	SQLzeroY;

	static const float		SQRzeroX	=	widthStripX * 15.5;//28.09375;
	static const float		SQRzeroY	=	-widthStripY * 7.5;//-27.1875;

	static const float		SQRstartX	=	SQRzeroX;
	static const float		SQRstartY	=	SQRzeroY;
	//DETS DISPLACEMENT - MADE FOR SQR dist = 250. Same for 300? Prolly

	//************************* CUTS FOR FOR 0-2*******************************************
	static const float		tc_SQX_L	=	200.0;
	static const float		tc_SQX_R	=	200.0;
	static const float		tc_SQY_L	=	200.0;
	static const float		tc_SQY_R	=	200.0;
	static const float		tc_CsI_L	=	1500.0;
	static const float		tc_CsI_R	=	1500.0;

	static const float		SQX_L_5	=	1.5;	//a lot of dirt below 1.5
	static const float		SQY_L_5	=	1.5;	//a lot of dirt below 1.5
	static const float		CsI_L_5	=	0.5;	//it's actually SSD_L 

	static const float		SQX_R_5	=	5.0;	//since it's for He6, I can use 5 MeV
	static const float		SQY_R_5	=	5.0;	//since it's for He6, I can use 5 MeV
	static const float		CsI_R_5	=	150.0;

	static const float		sqRDeadLayer = 3.45;
	static const float		sqLDeadLayer = 3.5;

	//************************* dets time correction *******************************************
	// 1st geo
	static const float		tcor_sqLX_I_1	=	120.0;
	static const float		tcor_sqLX_II_1	=	0.0;
	static const float		tcor_sqRX_I_1	=	400.0;
	static const float		tcor_sqRX_II_1	=	0.0;

	static const float		tcor_sqLY_1	=	120.0;
	static const float		tcor_sqRY_1	=	400.0;

	//	2nd geo
	static const float		tcor_sqLX_I_2	=	150.0;
	static const float		tcor_sqLX_II_2	=	0.0;
	static const float		tcor_sqRX_I_2	=	450.0;
	static const float		tcor_sqRX_II_2	=	0.0;

	static const float		tcor_sqLY_2	=	150.0;
	static const float		tcor_sqRY_2	=	450.0;

	//	3rd geo
	static const float		tcor_sqLX_I_3	=	0.0;
	static const float		tcor_sqLX_II_3	=	0.0;
	static const float		tcor_sqRX_I_3	=	0.0;
	static const float		tcor_sqRX_II_3	=	0.0;

	static const float		tcor_sqLY_3	=	350.0;
	static const float		tcor_sqRY_3	=	400.0;

	//4th geo
	static const float		tcor_sqLX_I_4	=	90.0;
	static const float		tcor_sqLX_II_4	=	10.0;
	static const float		tcor_sqRX_I_4	=	100.0;
	static const float		tcor_sqRX_II_4	=	0.0;

	static const float		tcor_sqLY_4	=	100.0;
	static const float		tcor_sqRY_4	=	400.0;

	//*************************MWPC******************************************************

	static const float	MWPC1_X_displacement = -1.0;
	static const float	MWPC1_Y_displacement = 0.0;
	static const float	MWPC2_X_displacement = -2.1375;
	static const float	MWPC2_Y_displacement = 0.0;

	static const float	leftDetShift = 0.0;
	static const float	rightDetShift = 0.0;
	static const float	leftDetShiftX = 0.0;
	static const float	rightDetShiftX = 0.0;

	static const float	leftDetDist = 0.0;
	static const float	rightDetDist = 0.0;

	static const float	leftAngShift = 0.536;
	static const float	rightAngShift = 0.275;

	static const float	tarThicknessShift = 36.8251;
	static const float	tarPos = 10.0;
	static const float	tarAngle = 0.0;
	


	static const float		MWPC1_X_zero_position	=	15.5*1.25;
	static const float		MWPC1_Y_zero_position	=	-15.5*1.25;
	static const float		MWPC2_X_zero_position	=	15.5*1.25;
	static const float		MWPC2_Y_zero_position	=	-15.5*1.25;

	static const short		MWPC_1_X_id	=	0;
	static const short		MWPC_1_Y_id	=	1;
	static const short		MWPC_2_X_id	=	2;
	static const short		MWPC_2_Y_id	=	3;

	//*************************PHYSICS**************************************************
	static const float		alpha_from_Ra226[4]{4.751, 5.459, 5.972, 7.661};
	static const float		u_to_MeV	=	931.4936;

	static const float		massN	= 939.565;
	static const float 		mass1H 	= 938.272013;
	static const float 		mass2H 	= 1876.124366211;
	static const float 		mass3H 	= 2808.921;
	static const float 		mass4He = 3727.379000;
	static const float 		mass5He = 4668.699;//4668.699
	static const float 		mass6He = 5606.558019;
	static const float 		mass7He = 6546.524420563;
	static const float 		mass8Li = 8022.48625;

	static const float		c			=	299.792;	// mm/ns
	
	static const float		tofBase			=	12320.0;
	static const float		dist_Tar_to_F5	=	-953.0;
	static const float		dist_Tar_to_F6	=	478.0;
	static const float		tof_const		=	87.8;
	static const float		tof_const_5		=	68.475;


	static const TString 	dir_runs("/home/zalewski/data/bank/");
	static const TString 	dir_CsI("/home/zalewski/data/he6_d/miscroot/CsI/parts");
	static const TString 	dir_params("/home/zalewski/aku/calibrationParameters/");	
	static const TString 	s_inFname("run00_12");
	static const TString	dir_gcut("/home/zalewski/aku/wrk/GCuts/");

	static const int		runNo = 3;
	static const TString	inDir = "cal";
	static const bool 		fixedMWPC = false;
	static const int		tarMass = 2;
}
#endif
