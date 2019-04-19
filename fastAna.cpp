#include "fastAna.hh"

Int_t kine(TLorentzVector *m_lvBeam, Double_t &sqlang, Double_t &sqrang)
{
	r = new TRotation();
	r->SetZAxis(m_lvBeam->Vect());
	r->Invert();
	m_lvBeam->Transform(*r);
	m_lv2H = lvTarget;
	m_lv6He = *m_lvBeam;
	TVector3 tmp_beamVect{m_lv6He.Vect().X(), m_lv6He.Vect().Y(), m_lv6He.Vect().Z()};
	m_lv6He.SetVectM(tmp_beamVect, mass_6He);
	m_lvCM = m_lv2H + m_lv6He;
	m_vBoost = m_lvCM.BoostVector();
	//printf("X: %f\tY: %f\tZ: %f\n",m_vBoost.X(), m_vBoost.Y(), m_vBoost.Z());
	m_lv2H.Boost(-m_vBoost);
	m_lv6He.Boost(-m_vBoost);


	m_lv2H.SetTheta(thetaCM);
	m_lv6He.SetTheta(thetaCM-TMath::Pi());



	m_lv2H.Boost(m_vBoost);
	m_lv6He.Boost(m_vBoost);
	sqlang = m_lv2H.Angle(m_lvBeam->Vect());
	sqrang = m_lv6He.Angle(m_lvBeam->Vect());
	return -1;
}



Int_t kineRel(TLorentzVector *m_lvBeam, Double_t &sqlang, Double_t &sqrang)
{
	m_lv2H = lvTarget;
	m_lv6He = *m_lvBeam;
	TVector3 tmp_beamVect{m_lv6He.Vect().X(), m_lv6He.Vect().Y(), m_lv6He.Vect().Z()};
	m_lv6He.SetVectM(tmp_beamVect, mass_6He);
	//printf("%f\n", m_lvBeam->E()-m_lvBeam->M());
	m_lvCM = m_lv2H + m_lv6He;

	m_vBoost = m_lvCM.BoostVector();

	thetaCM = acos(rnd->Uniform(-1.0,1.0));


	Double_t Beta = m_lvBeam->P()/(m_lv2H.E()+m_lv6He.E());
	m_lv2H.Boost(-m_vBoost);
	m_lv6He.Boost(-m_vBoost);
	Double_t Beta2H_CM = sqrt(m_lv2H.E()*m_lv2H.E() - mass_1H*mass_1H)/m_lv2H.E();
	Double_t Beta6He_CM = sqrt(m_lv6He.E()*m_lv6He.E() - mass_6He*mass_6He)/m_lv6He.E();

	Double_t theta2H_LAB = atan(sin(thetaCM)/(m_lvCM.Gamma()*(cos(thetaCM)+m_lvCM.Beta()/Beta2H_CM)));
	Double_t theta6He_LAB = atan(sin(TMath::Pi()-thetaCM)/(m_lvCM.Gamma()*(cos(TMath::Pi()-thetaCM)+m_lvCM.Beta()/Beta6He_CM)));
	Double_t param1 = (m_lvCM.Beta()/Beta6He_CM)/(mass_6He/mass_2H)-1/m_lvCM.Gamma();

	sqlang = theta2H_LAB;
	sqrang = theta6He_LAB;
	//printf("%f\n",1 - m_lvCM.Beta()*m_lvCM.Beta());
	return -1;
}



bool looper(Float_t l_sqlang, Float_t l_sqrang, Float_t l_sqldist, Float_t l_sqrdist)
{
	dX0 = l_sqldist * sin(l_sqlang*TMath::DegToRad()) + width_strip_X * 15.5 * cos(l_sqlang*TMath::DegToRad());
	dY0 = -7.5 * width_strip_Y;
	dZ0 = l_sqldist * cos(l_sqlang*TMath::DegToRad()) + -1 * width_strip_X * 15.5 * sin(l_sqlang*TMath::DegToRad());

	hX0 = -1 * l_sqrdist * sin(l_sqrang*TMath::DegToRad()) - width_strip_X * 15.5 * cos(l_sqrang*TMath::DegToRad());
	hY0 = -7.5 * width_strip_Y;
	hZ0 = l_sqrdist * cos(l_sqrang*TMath::DegToRad()) - width_strip_X * 15.5 * sin(l_sqrang*TMath::DegToRad());
	
	//printf("dX0 = %f\tdZ0 = %f\t\thX0 = %f\thZ0 = %f\t\n", dX0, dZ0, hX0, hZ0);

//printf("l_sqlang: %f\tl_sqrang: %f\tcounter: %d\n",l_sqlang, l_sqrang, counter1, counter2);
	while (fReader->Next())	//loop on whole tree
	{
		//printf("l_sqlang: %f\tl_sqrang: %f\tcounter: %lld\n",l_sqlang, l_sqrang, counter1);

		dX = dX0 - (*SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(l_sqlang*TMath::DegToRad());
		dY = dY0 + (*SQY_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_Y;
		dZ = dZ0 + (*SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * sin(l_sqlang*TMath::DegToRad());

		hX = hX0 + (*SQX_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(l_sqrang*TMath::DegToRad());
		hY = hY0 + (*SQY_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_Y;
		hZ = hZ0 + (*SQX_R_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * sin(l_sqrang*TMath::DegToRad());
		

		v2H->SetXYZ(dX-*evX, dY-*evY, dZ-*evZ);
		v6He->SetXYZ(hX-*evX, hY-*evY, hZ-*evZ);

		sqlang = lvBeam->Vect().Angle(*v2H);
		sqrang = lvBeam->Vect().Angle(*v6He);


		if (*angAng2H)
		{
			v_sqlang2.push_back(sqlang*TMath::RadToDeg());
			v_sqrang2.push_back(sqrang*TMath::RadToDeg());
			//counter2++;
		}

		else
		{
			v_sqlang1.push_back(sqlang*TMath::RadToDeg());
			v_sqrang1.push_back(sqrang*TMath::RadToDeg());
			//counter1++;
		}

//		kineRel(&(*lvBeam), sqlang, sqrang);
//		v_sqlang1.push_back(sqlang*TMath::RadToDeg());
//		v_sqrang1.push_back(sqrang*TMath::RadToDeg());


	}

	fReader->Restart();
	
	TGraph *angAngGraph_1H = new TGraph(	v_sqlang1.size(), &v_sqlang1[0], &v_sqrang1[0]);
	TGraph *angAngGraph_2H = new TGraph(	v_sqlang2.size(), &v_sqlang2[0], &v_sqrang2[0]);

	angAngGraph_1H->SetMarkerColor(kGreen);
	angAngGraph_1H->SetMarkerSize(0.2);
	angAngGraph_1H->SetMarkerStyle(20);

	angAngGraph_2H->SetMarkerColor(kBlue);
	angAngGraph_2H->SetMarkerSize(0.2);
	angAngGraph_2H->SetMarkerStyle(20);


	TMultiGraph *angAngMultiGraph = new TMultiGraph();
	angAngMultiGraph->Add(angAngGraph_1H);
	angAngMultiGraph->Add(angAngGraph_2H);


	angAngMultiGraph->Draw("AP");
	angAngGraph_1H->Fit(angAngFit_1H_rel, "");
	angAngGraph_2H->Fit(angAngFit_2H_rel, "");


	//printf("%f\t%f\n",angAngFit_1H_rel->GetChisquare()/410, angAngFit_2H_rel->GetChisquare()/1793);

	//outStream_1H.is_open() ? printf("Open\n") : printf("Closed\n"); 
	//angAngFit_1H_rel->GetChisquare();
	//angAngFit_2H_rel->GetChisquare();

	ofstream outStream_1H("chisquare_1H.dat", std::ios::app);
	ofstream outStream_2H("chisquare_2H.dat", std::ios::app);
	outStream_1H<<angAngFit_1H_rel->GetChisquare()<<"\t";
	outStream_2H<<angAngFit_2H_rel->GetChisquare()<<"\t";

	outStream_1H.close();
	outStream_2H.close();

	v_sqlang2.clear();
	v_sqrang2.clear();
	v_sqlang2.clear();
	v_sqrang2.clear();

	return 1;
}

void fastAna()
{
	TProof::Open("");
	TStopwatch time{};
	rnd = new TRandom3();
	if (fReader->IsZombie())
	{
		printf("Wrong tree_name of file_name\n");
		return 0;
	}

	angAngFit_2H = new TF1("angAngFit_2H","[2]*atan(sin([0]*x)/([1]-cos([0]*x)))");
	angAngFit_2H->FixParameter(0, 2*TMath::DegToRad());
	angAngFit_2H->FixParameter(1, 6.01888589/2.01410177);
	angAngFit_2H->FixParameter(2, TMath::RadToDeg());

	angAngFit_2H_rel = new TF1("angAngFit_2H_rel","[0]*atan(2*tan([4]-[1]*x)/(1-tan([4]-[1]*x)*tan([4]-[1]*x)/[2]+[3]*(1+tan([4]-[1]*x)*tan([4]-[1]*x)/[2])))");

	angAngFit_2H_rel->FixParameter(0, TMath::RadToDeg());
	angAngFit_2H_rel->FixParameter(1, TMath::DegToRad());
	angAngFit_2H_rel->FixParameter(2, 0.970382);
	angAngFit_2H_rel->FixParameter(3, 2.948803);
	angAngFit_2H_rel->FixParameter(4, 1.56212);

	angAngFit_1H_rel = new TF1("angAngFit_1H_rel","[0]*atan(2*tan([4]-[1]*x)/(1-tan([4]-[1]*x)*tan([4]-[1]*x)/[2]+[3]*(1+tan([4]-[1]*x)*tan([4]-[1]*x)/[2])))");

	angAngFit_1H_rel->FixParameter(0, TMath::RadToDeg());
	angAngFit_1H_rel->FixParameter(1, TMath::DegToRad());
	angAngFit_1H_rel->FixParameter(2, 0.961505);
	angAngFit_1H_rel->FixParameter(3, 5.862506);
	angAngFit_1H_rel->FixParameter(4, 1.56212);

/*
//														[0] 150 - 190   [1] 60 - 70    [2] fixed     [3] fixed                   [1]         [2]
	f_left_det_nullPos = new TF1("f_left_det_nullPos","l_sqldist * sin(l_sqlang*TMath::DegToRad()) + [3] * 15.5 * cos(l_sqlang*TMath::DegToRad())");
	

	f_left_det_nullPos->SetParameter(0, 170);
	f_left_det_nullPos->SetParLimits(0, 150, 190);
	f_left_det_nullPos->SetParameter(1, 65);
	f_left_det_nullPos->SetParLimits(1, 60, 70);
	f_left_det_nullPos->FixParameter(2, TMath::DegToRad());
	f_left_det_nullPos->FixParameter(3, width_strip_X);

	f_left_det_Pos = new TF1("f_left_det_Pos","[0] * sin([1]*[2]) + [3] * 15.5 * cos([1]*[2]) - x * [3] * cos([0]*[2])");
	

	f_left_det_nullPos->SetParameter(0, 170);
	f_left_det_nullPos->SetParLimits(0, 150, 190);
	f_left_det_nullPos->SetParameter(1, 65);
	f_left_det_nullPos->SetParLimits(1, 60, 70);
	f_left_det_nullPos->FixParameter(2, TMath::DegToRad());
	f_left_det_nullPos->FixParameter(3, width_strip_X);
*/

//dX = dX0 - (*SQX_L_s+rnd->Uniform(-0.5,0.5)) * width_strip_X * cos(l_sqlang*TMath::DegToRad());

	v2H = new TVector3();
	v6He = new TVector3();
	r = new TRotation();
	short count{10};
	Float_t b_flang{60.0}, b_frang{12.0}, b_fldist{150.0}, b_frdist{220.0};
	Float_t flang{b_flang}, frang{b_frang}, fldist{b_fldist}, frdist{b_frdist};
	ofstream outStream_1H("chisquare_1H.dat", std::ios::trunc);
	ofstream outStream_2H("chisquare_2H.dat", std::ios::trunc);
	outStream_1H.close();
	outStream_2H.close();
	counter1 = 0;
/*
	for (short iii = 0; iii < count; ++iii)					//frdist:	230 - 270
	{
		printf("I got %d%%\n", counter1);
		counter1++;
		for (short jjj = 0; jjj < count; ++jjj)				//fldist:	150 - 190
		{
			for (short kkk = 0; kkk < count; ++kkk)			//frang:	13 - 17
			{
				for (short lll = 0; lll < count; ++lll)		//flang:	60 - 70
				{
					looper(flang, frang, fldist, frdist);	
					flang+=1.0;
				}
				flang=b_flang;
				frang+=0.4;
				ofstream outStream_1H("chisquare_1H.dat", std::ios::app);
				ofstream outStream_2H("chisquare_2H.dat", std::ios::app);
				outStream_1H<<angAngFit_1H_rel->GetChisquare()<<"\n";
				outStream_2H<<angAngFit_2H_rel->GetChisquare()<<"\n";
				outStream_1H.close();
				outStream_2H.close();
			}

			ofstream outStream_1H("chisquare_1H.dat", std::ios::app);
			ofstream outStream_2H("chisquare_2H.dat", std::ios::app);
			outStream_1H<<angAngFit_1H_rel->GetChisquare()<<"\n\n";
			outStream_2H<<angAngFit_2H_rel->GetChisquare()<<"\n\n";
			outStream_1H.close();
			outStream_2H.close();
			frang=b_frang;
			fldist+=4.0;
		}
		frdist+=4.0;
	}
*/
	looper(68.0, 15.0, 170.0, 250.0);

	
	//printf("%d\t%d\t%lld\n",counter1,counter2,fReader->GetEntries(kTRUE));
	printf("\nI was working for %.2f seconds\n", time.RealTime());
	//printf("*\n**\n***\nSwitch on PROOF\n***\n**\n*\n");

}