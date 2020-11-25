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
			static_cast<int>(round(sqr_ang*TMath::RadToDeg())),
			static_cast<int>(round(sql_ang*TMath::RadToDeg())),
			static_cast<int>(round(sqr_dist)),
			static_cast<int>(round(sql_dist)),
			static_cast<int>(round(tar_angle*TMath::RadToDeg())));
}


Double_t TOOL::getT(Double_t tof, Float_t mass)
{
	beta_squared= pow((cs::tofBase/tof)/cs::c, 2.0);
	gamma=1.0/sqrt(1.0-beta_squared);
	return mass*(gamma-1.0);
}

Double_t TOOL::gettime(Double_t T, Float_t mass, Float_t dist)
{
	gamma_squared = pow(T/mass+1.0, 2.0);
	beta = sqrt(1-1/gamma_squared);
	return dist/(beta*cs::c);
}

Double_t TOOL::getVelo(Double_t T, Float_t mass)
{
	gamma_squared = pow(T/(mass)+1,2.0);

	beta = sqrt(1-1/gamma_squared);
	return beta*cs::c;
}


bool TOOL::Get_MWPC_pos(UShort_t multi, UShort_t *wireNo,
						Float_t *MWPC_pos, Short_t MWPC_id)
{
	UShort_t sizeof_clust=1;
	if (multi!=0)
		{
		//one wire got signal - simplest solution
		if (multi==1)
		{
			//printf("simplest solution %i\n", wireNo[0]);
			if (MWPC_id == 0 || MWPC_id == 2)
			{
				*MWPC_pos = (15.5 - wireNo[0])*1.25;
			}

			else
			{
				*MWPC_pos = (-15.5 + wireNo[0])*1.25;
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

				if (MWPC_id == 0 || MWPC_id == 2)
				{
					*MWPC_pos = (15.5 - (wireNo[0]+wireNo[multi-1])/2.0)*1.25;
				}

				else
				{
					*MWPC_pos = (-15.5 + (wireNo[0]+wireNo[multi-1])/2.0)*1.25;
				}
				return 1;

			}
			else if (sizeof_clust<multi)
			{
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

bool TOOL::params_loader(TString fname, float *AConst, float *BConst, short chNo)
{
	ifstream instream(fname.Copy().Prepend(cs::dir_params.Data()).Data());
	string dummy;
	float CConst;

	if (!instream) 
	{
		printf ("#Cannot open %s coefficient file\n",
				fname.Copy().Prepend(cs::dir_params.Data()).Data());
		return 0;
	}

	for (int iii=0; iii<chNo; iii++)
	{
		instream>>AConst[iii]>>BConst[iii]>>CConst;
		//cout<<AConst[iii]<<"  "<<BConst[iii]<<endl;
	}
//cout<<endl;
	instream.close();
	return 1;
}

bool TOOL::gcuts_loader(TString fName, TCutG *gcut, TString ion, int geoNo)
{
	fName.ReplaceAll("clb_","").ReplaceAll(".root","/");
	string dummy, dummy2;
	int points;
	TString dir_cur;
	dir_cur.Form("%sgeo%i/%s",cs::dir_gcut.Data(),geoNo,ion.Data());
	ifstream instream(dir_cur.Data());
	//printf("Patrz co kot przyniosl: %s\n",dir_cur.Data() );

	if (!instream) 
	{
		printf ("!!Cannot open %s coefficient file\n",dir_cur.Data());
		return false;
	}
	
	for (int iii = 0; iii < 4; ++iii)//clean lines before No of points
	{
		getline(instream, dummy);
	}

	getline(instream, dummy, ',');
	getline(instream, dummy, ')');
	points = stoi(dummy);//"I am number of points now"

	for (int iii = 0; iii < 5; ++iii)//clean lines after No of points
	{
		getline(instream, dummy);
	}

	for (int iii = 0; iii < points; ++iii)
	{
		getline(instream, dummy, '(');
		getline(instream, dummy, ',');
		getline(instream, dummy, ',');
		getline(instream, dummy2, ')');
		//printf("gcut->SetPoint(%i, %f, %f);\n",iii, stof(dummy), stof(dummy2));
		gcut->SetPoint(iii, stof(dummy), stof(dummy2));

	}

	instream.close();
	
	return true;

}

int TOOL::gcut_noPoints(TString fName, TString ion, int geoNo)
{
	fName.ReplaceAll("clb_","").ReplaceAll(".root","/");
	string dummy, dummy2;
	int points;
	TString dir_cur;
	dir_cur.Form("%sgeo%i/%s",cs::dir_gcut.Data(),geoNo,ion.Data());
	ifstream instream(dir_cur.Data());
	
	if (!instream) 
	{
		printf ("#Cannot open %s coefficient file\n",(dir_cur.Data()));
		return 0;
	}
	for (int iii = 0; iii < 4; ++iii)//clean lines before No of points
	{
		getline(instream, dummy);
	}

	getline(instream, dummy, ',');
	getline(instream, dummy, ')');
	//printf("%s\n%s\n",dummy.c_str(), dir_cur.Data());
	points = stoi(dummy);//"I am number of points now"
	return points;

}

Float_t TOOL::kin_GetAngRecoil(Float_t T_deu, Float_t T_beam, Float_t massRatio)
{
	Float_t velo_deu, velo_beam;
	velo_deu = getVelo(T_deu, cs::mass6He*massRatio);
	velo_beam = getVelo(T_beam, cs::mass6He);
	return acos( ( (1+massRatio)/2.0) * (velo_deu/velo_beam))*TMath::RadToDeg();
}

Float_t TOOL::kin_GetERecoil(Float_t theta, Float_t T_beam, Float_t massRatio)
{
	Float_t velo_deu, velo_beam;
	velo_beam = getVelo(T_beam, cs::mass6He);
	velo_deu = ((2 * cos(theta)) / (1+massRatio)) * velo_beam;
	beta_squared= pow(velo_deu/cs::c, 2.0);
	gamma=1.0/sqrt(1.0-beta_squared);
	return massRatio*(gamma-1.0)*cs::mass6He;
}

Float_t TOOL::kin_GetAngProjectile(Float_t T_deut, Float_t T_beam, Float_t massRatio)
{
	Float_t velo_hel, velo_beam, vel_R;
	velo_hel = getVelo(T_beam - T_deut, cs::mass6He);
	velo_beam = getVelo(T_beam, cs::mass6He);
	vel_R = velo_hel/velo_beam;
	return acos(((1+massRatio)*vel_R*vel_R+1-massRatio)/(2*vel_R))*TMath::RadToDeg();
}

Int_t TOOL::GetRunNumber(TString fileName)
{
	Int_t fileName_begin{fileName.Index("run")};
	fileName.Remove(0, fileName_begin+3);
	Int_t fileName_end{fileName.Index(".root")};
	fileName.Remove(fileName_end, 5);
	return fileName.Atoi();
}


TOOL::~TOOL()
{
}
