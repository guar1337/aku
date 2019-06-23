#define geoMaker_cxx
// The class definition in geoMaker.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//	 Begin():		  called every time a loop on the tree starts,
//						  a convenient place to create your histograms.
//	 SlaveBegin():	called after Begin(), when on PROOF called only on the
//						  slave servers.
//	 Process():		called for each event, in this function you decide what
//						  to read and fill your histograms.
//	 SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//						  called only on the slave servers.
//	 Terminate():	 called at the end of the loop on the tree,
//						  a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("geoMaker.C")
// root> T->Process("geoMaker.C","some options")
// root> T->Process("geoMaker.C+")
//


#include "geoMaker.h"
#include <TH2.h>
#include <TStyle.h>

bool geoMaker::Get_MWPC_pos(UShort_t multi, unsigned short *wireNo,
						Float_t *MWPC_pos, Short_t MWPC_id)
{
	switch (MWPC_id)
	{
		case cs::MWPC_1_X_id:
		displacement = cs::MWPC1_X_displacement;
		zero_position = cs::MWPC1_X_zero_position;
		break;

		case cs::MWPC_1_Y_id:
		displacement = cs::MWPC1_Y_displacement;
		zero_position = cs::MWPC1_Y_zero_position;
		break;

		case cs::MWPC_2_X_id:
		displacement = cs::MWPC2_X_displacement;
		zero_position = cs::MWPC2_X_zero_position;
		break;

		case cs::MWPC_2_Y_id:
		displacement = cs::MWPC2_Y_displacement;
		zero_position = cs::MWPC2_Y_zero_position;
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
				*MWPC_pos = zero_position + displacement - wireNo[0]*1.25;
			}

			else
			{
				*MWPC_pos = zero_position + displacement + wireNo[0]*1.25;
			}
			
			return 1;
		}

		//more than one but is it one cluster?
		else
		{  //checking...
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

void geoMaker::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).
	rnd = new TRandom3();
	diffX =  new TH1F ("diffX", "evX - detX", 200, -20.0,20.0);
	diffY =  new TH1F ("diffY", "evY - detY", 200, -20.0,20.0);
	diffZ =  new TH1F ("diffZ", "evZ - detZ", 200, -20.0,20.0);

	TString option = GetOption();
	tar_angle = 0.0;
	tar_pos_Z = 170.0;
	MWPC_1_Z = -816.0;
	MWPC_2_Z = -270.0;
	SQR_ang = 0.0;
	SQL_ang = 0.0;
	SQR_dist = 170.0;
	SQL_dist = 200.0;
}

void geoMaker::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).

	option = GetOption();
}

Bool_t geoMaker::Process(Long64_t entry)
{
	// The Process() function is called for each entry in the tree (or possibly
	// keyed object in the case of PROOF) to be processed. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	// When processing keyed objects with PROOF, the object is already loaded
	// and is available via the fObject pointer.
	//
	// This function should contain the \"body\" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	//
	// Use fStatus to set the return value of TTree::Process().
	//
	// The return value is currently not used.

	fReader.SetEntry(entry);
	
	if (option.Contains("1"))
	{
		if (std::count_if(SQY_R.begin(), SQY_R.end(), [](unsigned short i){return i > cs::tc_SQY_R;}) == 1)
		{
			SQY_R_strip = std::distance(SQY_R.begin(), std::max_element(SQY_R.begin(), SQY_R.end()));

			if (std::count_if(SQX_R.begin(), SQX_R.end(), [](unsigned short i){return i > cs::tc_SQX_R;}) == 1)
			{
				SQX_R_strip = std::distance(SQX_R.begin(), std::max_element(SQX_R.begin(), SQX_R.end()));
				//printf("%d\n", std::distance(SQY_R.begin(), std::max_element(SQY_R.begin(), SQY_R.end())));
				for (int iii= 0; iii<32; ++iii)
				{
					temp_x1[iii] = x1[iii];
					temp_x2[iii] = x2[iii];
					temp_y1[iii] = y1[iii];
					temp_y2[iii] = y2[iii];
					
				}

				if (	Get_MWPC_pos(*nx1, temp_x1, &MWPC_1_X, cs::MWPC_1_X_id)  &&
						Get_MWPC_pos(*nx2, temp_x2, &MWPC_2_X, cs::MWPC_2_X_id)  &&
						Get_MWPC_pos(*ny1, temp_y1, &MWPC_1_Y, cs::MWPC_1_Y_id)  &&
						Get_MWPC_pos(*ny2, temp_y2, &MWPC_2_Y, cs::MWPC_2_Y_id)	)
				{
					MWPC_1_X += rnd->Uniform(0.0,1.25)-0.6125;
					MWPC_1_Y += rnd->Uniform(0.0,1.25)-0.6125;
					
					MWPC_2_X += rnd->Uniform(0.0,1.25)-0.6125;
					MWPC_2_Y += rnd->Uniform(0.0,1.25)-0.6125;
					
					dX=MWPC_2_X-MWPC_1_X;
					dY=MWPC_2_Y-MWPC_1_Y;
					dZ=MWPC_2_Z-MWPC_1_Z;

					Tcoef=(cos(tar_angle)*tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);

					evX = MWPC_1_X + dX*Tcoef;
					evY = MWPC_1_Y + dY*Tcoef;
					evZ = MWPC_1_Z + dZ*Tcoef;

					X6He_lab = SQR_dist*(-sin(SQR_ang)) + cs::SQR_start_X * cos(SQR_ang);
					Y6He_lab = cs::SQR_start_Y;
					Z6He_lab = SQR_dist*cos(SQR_ang) + cs::SQR_start_X * sin(SQR_ang);		

					X6He_det	= cs::width_strip_X	*	(SQX_R_strip+rnd->Uniform(0.0,1.0)-0.5) * cos(SQR_ang);
					Y6He_det	= cs::width_strip_Y	*	(SQY_R_strip+rnd->Uniform(0.0,1.0)-0.5);
					Z6He_det	= cs::width_strip_X	*	(SQX_R_strip+rnd->Uniform(0.0,1.0)-0.5) * sin(SQR_ang);

					detX = X6He_lab + X6He_det;
					detY = Y6He_lab + Y6He_det;
					detZ = Z6He_lab + Z6He_det;

					diffX->Fill(evX-detX);
					diffY->Fill(evY-detY);
					diffZ->Fill(evZ-detZ);
				}
			}
		}
	}

	else
	{
		if (std::count_if(SQY_L.begin(), SQY_L.end(), [](unsigned short i){return i > cs::tc_SQY_L;}) == 1)
		{
			SQY_L_strip = std::distance(SQY_L.begin(), std::max_element(SQY_L.begin(), SQY_L.end()));

			if (std::count_if(SQX_L.begin(), SQX_L.end(), [](unsigned short i){return i > cs::tc_SQX_L;}) == 1)
			{
				SQX_L_strip = std::distance(SQX_L.begin(), std::max_element(SQX_L.begin(), SQX_L.end()));
				//printf("%d\n", std::distance(SQY_L.begin(), std::max_element(SQY_L.begin(), SQY_L.end())));
				for (int iii= 0; iii<32; ++iii)
				{
					temp_x1[iii] = x1[iii];
					temp_x2[iii] = x2[iii];
					temp_y1[iii] = y1[iii];
					temp_y2[iii] = y2[iii];
					
				}

				if (	Get_MWPC_pos(*nx1, temp_x1, &MWPC_1_X, cs::MWPC_1_X_id)  &&
						Get_MWPC_pos(*nx2, temp_x2, &MWPC_2_X, cs::MWPC_2_X_id)  &&
						Get_MWPC_pos(*ny1, temp_y1, &MWPC_1_Y, cs::MWPC_1_Y_id)  &&
						Get_MWPC_pos(*ny2, temp_y2, &MWPC_2_Y, cs::MWPC_2_Y_id)	)
				{
					MWPC_1_X += rnd->Uniform(0.0,1.25)-0.6125;
					MWPC_1_Y += rnd->Uniform(0.0,1.25)-0.6125;
					
					MWPC_2_X += rnd->Uniform(0.0,1.25)-0.6125;
					MWPC_2_Y += rnd->Uniform(0.0,1.25)-0.6125;
					
					dX=MWPC_2_X-MWPC_1_X;
					dY=MWPC_2_Y-MWPC_1_Y;
					dZ=MWPC_2_Z-MWPC_1_Z;

					Tcoef=(cos(tar_angle)*tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);

					evX = MWPC_1_X + dX*Tcoef;
					evY = MWPC_1_Y + dY*Tcoef;
					evZ = MWPC_1_Z + dZ*Tcoef;

					X2H_lab = SQL_dist*sin(SQL_ang) + cs::SQL_start_X * cos(SQL_ang);
					Y2H_lab = cs::SQL_start_Y;
					Z2H_lab = SQL_dist*cos(SQL_ang) - cs::SQL_start_X * sin(SQL_ang);	

					X2H_det = -cs::width_strip_X * (SQX_L_strip+rnd->Uniform(0.0,1.0)-0.5) * cos(SQL_ang);
					Y2H_det = cs::width_strip_Y *  (SQY_L_strip+rnd->Uniform(0.0,1.0)-0.5);
					Z2H_det = cs::width_strip_X * (SQX_L_strip+rnd->Uniform(0.0,1.0)-0.5) * sin(SQL_ang);

					detX = X2H_lab + X2H_det;
					detY = Y2H_lab + Y2H_det;
					detZ = Y2H_lab + Z2H_det;

					diffX->Fill(evX-detX);
					diffY->Fill(evY-detY);
					diffZ->Fill(evZ-detZ);
				}
			}
		}
	}



	return kTRUE;
}

void geoMaker::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.
	diffX->Draw();

}	

void geoMaker::Terminate()
{
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.

}