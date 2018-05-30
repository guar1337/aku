#ifndef constants_h
#define constants_h 1
#include <Rtypes.h>
#include <TString.h>

namespace s
{
	//*************************geometry**************************************************
	static const float		sql_ang7		=	70.0	* (3.1415/180.0);
	static const float		sqr_ang7		=	13.0	* (3.1415/180.0);
	static const float		sql_ang9		=	35.0	* (3.1415/180.0);
	static const float		sqr_ang9		=	18.0	* (3.1415/180.0);

	static const float		sql_ang_s1		=	65.0	* (3.1415/180.0);
	static const float		sqr_ang_s1		=	15.0	* (3.1415/180.0);

	static const float		sql_ang_s2		=	50.0	* (3.1415/180.0);
	static const float		sqr_ang_s2		=	15.0	* (3.1415/180.0);

	static const float		sql_ang_s3		=	35.0	* (3.1415/180.0);
	static const float		sqr_ang_s3		=	15.0	* (3.1415/180.0);

	static const float		sql_ang_s4		=	75.0	* (3.1415/180.0);
	static const float		sqr_ang_s4		=	10.08	* (3.1415/180.0);

	static const float		tar_ang_s1		=	45.0	* (3.1415/180.0);
	static const float		tar_ang_s2		=	6.0		* (3.1415/180.0);
	static const float		tar_ang_s3		=	0.0		* (3.1415/180.0);
	static const float		tar_ang_s4		=	32.0	* (3.1415/180.0);
	static const float		tar_pos_Z		=	0.0;

	//*************************DETS geometry**********************************************
	static const float		sql_dist_s1	=	170.0;
	static const float		sqr_dist_s1	=	250.0;

	static const float		sql_dist_s2	=	170.0;
	static const float		sqr_dist_s2	=	250.0;

	static const float		sql_dist_s3	=	170.0;
	static const float		sqr_dist_s3	=	250.0;

	static const float		sql_dist_s4	=	170.0;
	static const float		sqr_dist_s4	=	300.0;

	static const float		sql_dist_s7	=	170.0;
	static const float		sqr_dist_s7	=	170.0;

	static const float		sql_dist_s9	=	170.0;
	static const float		sqr_dist_s9	=	170.0;

	//*************************DETS DISPLACEMENT*******************************************
	static const float		SQL_displacement_X	=	2.116;
	static const float		SQL_displacement_Y	=	1.282;

	static const float		SQL_zero_X	=	31.0;
	static const float		SQL_zero_Y	=	-30.0;

	static const float		SQL_start_X	=	SQL_displacement_X + SQL_zero_X;
	static const float		SQL_start_Y	=	SQL_displacement_Y + SQL_zero_Y;


	static const float		SQR_displacement_X	=	-0.606;
	static const float		SQR_displacement_Y	=	1.697;

	static const float		SQR_zero_X	=	-31.0;
	static const float		SQR_zero_Y	=	-30.0;

	static const float		SQR_start_X	=	SQR_displacement_X + SQR_zero_X;
	static const float		SQR_start_Y	=	SQR_displacement_Y + SQR_zero_Y;
	//DETS DISPLACEMENT - MADE FOR SQR dist = 250. Same for 300? Prolly

	//************************* CUTS FOR FOR 0-2*******************************************
	static const float		tc_SQX_L	=	500.0;
	static const float		tc_SQX_R	=	500.0;
	static const float		tc_SQY_L	=	900.0;
	static const float		tc_SQY_R	=	900.0;
	static const float		tc_CsI_L	=	1500.0;
	static const float		tc_CsI_R	=	1500.0;

	//*************************MWPC******************************************************
	static const float		MWPC1_X_displacement	=	-1.0;
	static const float		MWPC1_Y_displacement	=	-2.1375;
	static const float		MWPC2_X_displacement	=	0.2;
	static const float		MWPC2_Y_displacement	=	-1.125;

	static const float		MWPC1_X_zero_position	=	15.5*1.25;
	static const float		MWPC1_Y_zero_position	=	-15.5*1.25;
	static const float		MWPC2_X_zero_position	=	15.5*1.25;
	static const float		MWPC2_Y_zero_position	=	-15.5*1.25;

	static const short		MWPC_1_X_id	=	0;
	static const short		MWPC_1_Y_id	=	1;
	static const short		MWPC_2_X_id	=	2;
	static const short		MWPC_2_Y_id	=	3;

	//*************************PHYSICS**************************************************
	static const float		alpha_from_Ra226[4]{4.415, 5.153, 5.683, 7.419};
	static const float		rad_to_deg	=	180.0	/ 3.1415927;
	static const float		u_to_MeV	=	931.4936;
	static const float 		mass_2H 	=	1875.61292;
	static const float 		mass_6He 	=	5606.55667;
	static const float 		mass_1H 	=	938.782;
	static const float		c			=	299.792;	// mm/ns
	
	static const float		tofBase			=	12348.0;
	static const float		dist_Tar_to_F5	=	953.0;

	static const TString 	rootF_dir("/home/guar/data/mar2018/rawroot");
	static const TString 	misc_dir("/home/guar/data/mar2018/miscroot");
	static const TString 	inFname("run02");
	static const TString	playground("/home/guar/data/tools/");


	static const int		runNo=	1;	
}
#endif