#include "TOOL.h"

ClassImp(TOOL);
TOOL::TOOL()
{

}
using namespace std;
void TOOL::printSetup(	Double_t sqr_ang, Double_t sql_ang,
						Double_t sqr_dist, Double_t sql_dist,
						Float_t tar_angle)
{
	printf(	"Right telescope central angle = %i deg\n"
			"Left telescope central angle = %i deg\n\n"
			"Right telescope distance from target = %i mm\n"
			"Left telescope distance from target = %i mm\n"
			"Target at %i deg\n"
			"*****************************************\n",
			static_cast<int>(sqr_ang*s::rad_to_deg),
			static_cast<int>(sql_ang*s::rad_to_deg),
			static_cast<int>(sqr_dist),
			static_cast<int>(sql_dist),
			static_cast<int>(tar_angle*s::rad_to_deg));
}


Double_t TOOL::getT(Double_t tof, Float_t mass)
{
	beta_squared= pow((s::tofBase/tof)/s::c, 2.0);
	gamma=1.0/sqrt(1.0-beta_squared);
	return mass*(gamma-1.0);
}

bool TOOL::Get_MWPC_pos(UShort_t multi, UShort_t *wireNo,
						Float_t *MWPC_pos,Short_t MWPC_id)
{
	switch (MWPC_id)
	{
		case s::MWPC_1_X_id:
		displacement = s::MWPC1_X_displacement;
		zero_position = s::MWPC1_X_zero_position;
		break;

		case s::MWPC_1_Y_id:
		displacement = s::MWPC1_Y_displacement;
		zero_position = s::MWPC1_Y_zero_position;
		break;

		case s::MWPC_2_X_id:
		displacement = s::MWPC2_X_displacement;
		zero_position = s::MWPC2_X_zero_position;
		break;

		case s::MWPC_2_Y_id:
		displacement = s::MWPC2_Y_displacement;
		zero_position = s::MWPC2_Y_zero_position;
		break;
	}
	
	UShort_t sizeof_clust=1;
	if (multi!=0)
		{
		//one wire got signal - simplest solution
		if (multi==1)
		{
			//printf("simplest solution %i\n", wireNo[0]);
			if (MWPC_id == 0 || MWPC_id == 2)
			{
				*MWPC_pos = zero_position + displacement -
				((wireNo[0]+wireNo[multi-1])/2)*1.25;
			}

			else
			{
				*MWPC_pos = zero_position + displacement +
				((wireNo[0]+wireNo[multi-1])/2)*1.25;
			}
			
			return 1;
		}

		//more than one but is it one cluster?
		else
		{	//checking...
			for (int iii = 1; iii < multi; iii++)
			{
				if ((wireNo[iii] - wireNo[iii-1])==1)
				{
					sizeof_clust++;
				}
			}
			//
			if (sizeof_clust==multi)
			{
				/*
				printf("Good job. sizeof: %i\t pos.: %f\n", sizeof_clust, static_cast<float>(wireNo[0]+wireNo[multi-1])/2);
				for (int jjj = 0; jjj < multi; jjj++)
				{					
					printf("wireNo[%i]: %i\n", jjj, wireNo[jjj]);
				}
				*/
			if (MWPC_id == 0 || MWPC_id == 2)
			{
				*MWPC_pos = zero_position + displacement -
				((wireNo[0]+wireNo[multi-1])/2)*1.25;
			}

			else
			{
				*MWPC_pos = zero_position + displacement +
				((wireNo[0]+wireNo[multi-1])/2)*1.25;
			}
				return 1;

			}
			else if (sizeof_clust<multi)
			{
				/*
				printf("\n\nNEWGAME\n");
				printf("Two clusters? sizeof: %i\t mult.: %i\n", sizeof_clust, multi);
				if (multi==2)
				{
					printf("***************AWESOME!*************************\n");
				}
				for (int jjj = 0; jjj < multi; jjj++)
				{
					printf("wireNo"[%i]: %i\n", jjj, wireNo[jjj]);
				}
				*/
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
	return 0;
}

bool TOOL::initializeGeometry(	Double_t *sqr_ang, Double_t *sql_ang,
								Double_t *sqr_dist, Double_t *sql_dist,
								Float_t *tar_angle) 
{
	printf("\n*****************************************");
	//Read detectors geometry parameters depending on run
	switch (s::runNo)
	{
		case 7:
		printf("\nLoaded exprimental setup parameters for geometry 7:\n");
		*sqr_ang=s::sqr_ang7;
		*sql_ang=s::sql_ang7;

		*sqr_dist=s::sqr_dist_s7;
		*sql_dist=s::sql_dist_s7;
		*tar_angle=s::tar_ang_s3;
		printSetup(*sqr_ang, *sql_ang, *sqr_dist, *sql_dist, *tar_angle);
		return 1;
		break;

		case 9:
		printf("\nLoaded exprimental setup parameters for geometry 9:\n");
		*sqr_ang=s::sqr_ang9;
		*sql_ang=s::sql_ang9;
		
		*sqr_dist=s::sqr_dist_s9;
		*sql_dist=s::sql_dist_s9;
		*tar_angle=s::tar_ang_s3;
		printSetup(*sqr_ang, *sql_ang, *sqr_dist, *sql_dist, *tar_angle);
		return 1;
		break;

		case 1:
		printf("\nLoaded exprimental setup parameters for geometry 1:\n");
		*sqr_ang=s::sqr_ang_s1;
		*sql_ang=s::sql_ang_s1;
		
		*sqr_dist=s::sqr_dist_s1;
		*sql_dist=s::sql_dist_s1;
		*tar_angle=s::tar_ang_s1;
		printSetup(*sqr_ang, *sql_ang, *sqr_dist, *sql_dist, *tar_angle);
		return 1;
		break;

		case 2:
		printf("\nLoaded exprimental setup parameters for geometry 2:\n");
		*sqr_ang=s::sqr_ang_s2;
		*sql_ang=s::sql_ang_s2;
		
		*sqr_dist=s::sqr_dist_s2;
		*sql_dist=s::sql_dist_s2;
		*tar_angle=s::tar_ang_s2;
		printSetup(*sqr_ang, *sql_ang, *sqr_dist, *sql_dist, *tar_angle);
		return 1;
		break;

		case 3:
		printf("\nLoaded exprimental setup parameters for geometry 3:\n");
		*sqr_ang=s::sqr_ang_s3;
		*sql_ang=s::sql_ang_s3;
		
		*sqr_dist=s::sqr_dist_s3;
		*sql_dist=s::sql_dist_s3;
		*tar_angle=s::tar_ang_s3;
		printSetup(*sqr_ang, *sql_ang, *sqr_dist, *sql_dist, *tar_angle);
		return 1;
		break;

		case 4:
		printf("\nLoaded exprimental setup parameters for geometry 4:\n");
		*sqr_ang=s::sqr_ang_s4;
		*sql_ang=s::sql_ang_s4;
		
		*sqr_dist=s::sqr_dist_s4;
		*sql_dist=s::sql_dist_s4;
		*tar_angle=s::tar_ang_s4;
		printSetup(*sqr_ang, *sql_ang, *sqr_dist, *sql_dist, *tar_angle);
		return 1;
		break;

		default:
		printf("\nError: NO EXPERIMENTAL SETUP PARAMETERS\n");
		return 0;
		break;
	}
}

bool TOOL::getDeadLayer(TString inFileName, TString leafName,
						double *alpha_energies, Short_t chnlNo)
{

	chnlNo--;


	gSystem->cd(s::playground.Data());
	TFile *inF= new TFile((inFileName.Data()), "READ");
	TTree *inTree = (TTree*)inF->Get("AnalysisxTree");


	TF1 *linFit_Func = new TF1("linFit", "pol1", 0.0, 10.0);
	TH1I *raw_Si_spec = new TH1I("name", "title", 4096, 0, 4095);
	for (int iii = 0; iii <= chnlNo; iii++)
	{
		containerName.Form("%s[%i]", leafName.Data(), iii);
		histName.Form("HistFrom%s",containerName.Data());
		raw_Si_spec->SetName(histName.Data());
		histFillcmd.Form("%s >> %s",containerName.Data(), histName.Data());
		printf("%s\n", histFillcmd.Data());
		inTree->Draw(histFillcmd.Data());



	}

	return 0;
}


void TOOL::null_strips(	UShort_t *SQX_L, UShort_t *SQY_L, UShort_t *CsI_L,
						UShort_t *SQX_R, UShort_t *SQY_R, UShort_t *CsI_R)
{
	fill(SQX_L,SQX_L+32,32);
	fill(SQY_L,SQY_L+16,16);
	fill(CsI_L,CsI_L+16,16);
	fill(SQX_R,SQX_R+32,32);
	fill(SQY_R,SQY_R+16,16);
	fill(CsI_R,CsI_R+16,16);
}

void TOOL::null_energy( Double_t *SQX_L, Double_t *SQY_L, Double_t *CsI_L,
						Double_t *SQX_R, Double_t *SQY_R, Double_t *CsI_R)
{
	fill(SQX_L,SQX_L+32,0.);
	fill(SQY_L,SQY_L+16,0.);
	fill(CsI_L,CsI_L+16,0.);
	fill(SQX_R,SQX_R+32,0.);
	fill(SQY_R,SQY_R+16,0.);
	fill(CsI_R,CsI_R+16,0.); 
}


TOOL::~TOOL()
{
}