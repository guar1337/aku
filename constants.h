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

	static const float		sql_ang_s0		=	0.0	* (3.1415/180.0);
	static const float		sqr_ang_s0		=	0.0	* (3.1415/180.0);

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
	static const float		tar_pos_Z		=	170.0;

	static const float		tar_gcut_low_X_1	=	-13.0;
	static const float		tar_gcut_high_X_1	=	18.0;
	static const float		tar_gcut_low_Y_1	=	-14.0;
	static const float		tar_gcut_high_Y_1	=	17.0;

	static const float		tar_gcut_low_X_2	=	-20.0;
	static const float		tar_gcut_high_X_2	=	21.0;
	static const float		tar_gcut_low_Y_2	=	-16.0;
	static const float		tar_gcut_high_Y_2	=	20.0;

	static const float		tar_gcut_low_X_3	=	0.0;
	static const float		tar_gcut_high_X_3	=	0.0;
	static const float		tar_gcut_low_Y_3	=	0.0;
	static const float		tar_gcut_high_Y_3	=	0.0;

	static const float		tar_gcut_low_X_4	=	-17.5;
	static const float		tar_gcut_high_X_4	=	22.0;
	static const float		tar_gcut_low_Y_4	=	-16.0;
	static const float		tar_gcut_high_Y_4	=	20.0;

	//*************************DETS geometry**********************************************
	static const float		sql_dist_s0	=	170.0;
	static const float		sqr_dist_s0	=	300.0;

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
	static const float		tc_SQX_L	=	200.0;
	static const float		tc_SQX_R	=	200.0;
	static const float		tc_SQY_L	=	200.0;
	static const float		tc_SQY_R	=	200.0;
	static const float		tc_CsI_L	=	1500.0;
	static const float		tc_CsI_R	=	1500.0;
	static const float		gc_CsI_R	=	1500.0;
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
	static const float		deg_to_rad	=	3.1415927/180.0;
	static const float		PI 			=	3.1415927;
	static const float		u_to_MeV	=	931.4936;

	static const float 		mass_1H 	= 1.00782503*u_to_MeV;
	static const float 		mass_2H 	= 2.01410177*u_to_MeV;
	static const float 		mass_3H 	= 3.01604927*u_to_MeV;
	static const float 		mass_4He 	= 4.00260325*u_to_MeV;
	static const float 		mass_6He 	= 6.01888589*u_to_MeV;
	static const float 		mass_7Li 	= 7.01600343*u_to_MeV;
	static const float 		mass_8Li 	= 8.02248624*u_to_MeV;
	static const float 		mass_9Li 	= 9.02679019*u_to_MeV;
	static const float 		mass_9Be 	= 9.01218306*u_to_MeV;


	static const float		c			=	299.792;	// mm/ns
	
	static const float		tofBase			=	12348.0;
	static const float		dist_Tar_to_F5	=	953.0;
	static const float		tof_const	=	89.165;

	static const TString 	dir_runs("/home/guar/data/mar2018/raw");
	static const TString 	dir_CsI("/home/guar/data/mar2018/miscroot/CsI/parts");
	static const TString 	dir_params("/home/guar/data/mar2018/calib/params/");	
	static const TString 	s_inFname("csiL0");
	static const TString	s_playground("/home/guar/data/tools/");
	static const TString	dir_gcut("/home/guar/data/mar2018/miscroot/CsI/gcuts/");

	static const TString	dir_len_data("/home/guar/data/");
	static const TString	dir_len_calib("/home/guar/aku/calib_files/");


	static const int		runNo=	0;
}
#endif