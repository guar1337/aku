#define beamCutter_cxx
// The class definition in beamCutter.h has been generated automatically
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
// root> T->Process("beamCutter.C")
// root> T->Process("beamCutter.C","some options")
// root> T->Process("beamCutter.C+")
//


#include "beamCutter.h"
#include <TH2.h>
#include <TStyle.h>

bool beamCutter::Get_MWPC_pos(UShort_t multi, unsigned short *wireNo,
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
			//printf("svBeamimplest solution %i\n", wireNo[0]);
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



void beamCutter::Begin(TTree * /*tree*/)
{
	// The Begin() function is called at the start of the query.
	// When running with PROOF Begin() is only called on the client.
	// The tree argument is deprecated (on PROOF 0 is passed).

	outF = new TFile("/home/zalewski/aku/geant4/beamSource_1.root","RECREATE");
	outTree = new TTree("beamSource","beam_Source");
	rnd = new TRandom3();

	outTree->Branch("MWPC_1_X", &MWPC_1_X,	 "MWPC_1_X/F");
	outTree->Branch("MWPC_2_X", &MWPC_2_X,	 "MWPC_2_X/F");
	outTree->Branch("MWPC_1_Y", &MWPC_1_Y,	 "MWPC_1_Y/F");
	outTree->Branch("MWPC_2_Y", &MWPC_2_Y,	 "MWPC_2_Y/F");
	outTree->Branch("MWPC_1_Z", &MWPC_1_Z,	 "MWPC_1_Z/F");
	outTree->Branch("MWPC_2_Z", &MWPC_2_Z,	 "MWPC_2_Z/F");
	outTree->Bronch("lvBeam.",	"TLorentzVector", &lvBeam);

	printf("Cutting some beans\n");
	TString option = GetOption();

}

void beamCutter::SlaveBegin(TTree * /*tree*/)
{
	// The SlaveBegin() function is called after the Begin() function.
	// When running with PROOF SlaveBegin() is called on each slave server.
	// The tree argument is deprecated (on PROOF 0 is passed).
	TString option = GetOption();
	vBeam = new TVector3;
	lvBeam = new TLorentzVector;
	nEntries = option.Atoll();
	

	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	consoleWidth = size.ws_col-8;
	//printf("No. of rows: %d\tNo. of columns: %d\n",size.ws_row, size.ws_col);


}

Bool_t beamCutter::Process(Long64_t entry)
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

	fReader.SetLocalEntry(entry);


	std::cout << "[";
	int pos = consoleWidth * progress;
	for (int i = 0; i < consoleWidth; ++i)
	{
		if (i < pos) std::cout << "#";
		else if (i == pos) std::cout << ">";
		else std::cout << ".";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();

	if( entry % ( nEntries / 100 ) == 0) progress += 0.01;


	if (*trigger==1)
	{

		tac=false;
		range=false;

		for (int iii= 0; iii<32; ++iii)
		{
			temp_x1[iii] = x1[iii];
			temp_x2[iii] = x2[iii];
			temp_y1[iii] = y1[iii];
			temp_y2[iii] = y2[iii];
			
		}

		if(tF3[0]*tF3[1]*tF3[2]*tF3[3]*tF5[0]*tF5[1]*tF5[2]*tF5[3])
		{

			if (	(tF3[0]-tF3[1]) > -50.0 && (tF3[0]-tF3[1]) < 50.0 &&
					(tF5[0]-tF5[1]) > -50.0 && (tF5[0]-tF5[1]) < 50.0	)
			{
				tac=true;
				tof=(-(tF3[0]+tF3[1]+tF3[2]+tF3[3])/4.0+(tF5[0]+tF5[1])/2)*0.125+cs::tof_const;
				//tof=(-(tF3[0]+tF3[1]+tF3[2]+tF3[3])/4.0+(tF5[0]+tF5[1])/2)*0.0625+cs::tof_const_5;


				//if (tof>175 && tof<181 && F5[0]>400 && F5[0]<800)		//gas target
				if (tac && tof>165 && tof<182 && F5[0]>600 && F5[0]<2800)
				{
					range=true;

					
					if (Get_MWPC_pos(*nx1, temp_x1, &MWPC_1_X, cs::MWPC_1_X_id)	&&
						Get_MWPC_pos(*nx2, temp_x2, &MWPC_2_X, cs::MWPC_2_X_id)	&&
						Get_MWPC_pos(*ny1, temp_y1, &MWPC_1_Y, cs::MWPC_1_Y_id)	&&
						Get_MWPC_pos(*ny2, temp_y2, &MWPC_2_Y, cs::MWPC_2_Y_id)		)
					{		
						beta_squared= pow((cs::tofBase/tof)/cs::c, 2.0);
						gamma=1.0/sqrt(1.0-beta_squared);
						kinE =  cs::mass6He*(gamma-1.0);

						MWPC_1_Z = -816.0;
						MWPC_2_Z = -270.0;

						dX = (MWPC_2_X + rnd->Uniform(0.0,1.25)-0.625) - (MWPC_1_X + rnd->Uniform(0.0,1.25)-0.625);
						dY = (MWPC_2_Y + rnd->Uniform(0.0,1.25)-0.625) - (MWPC_1_Y + rnd->Uniform(0.0,1.25)-0.625);
						dZ = (MWPC_2_Z + rnd->Uniform(0.0,1.25)-0.625) - (MWPC_1_Z + rnd->Uniform(0.0,1.25)-0.625);
						vBeam->SetXYZ(dX,dY,dZ);
				/*
						if (geoNo==5)
						{
							Tcoef=(cos(tar_angle)*cs::tar_pos_Z-sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z)/(sin(tar_angle)*dX+cos(tar_angle)*dZ);
							XZsum= - sin(tar_angle)*MWPC_1_X - cos(tar_angle)*MWPC_1_Z;
						
							evX = MWPC_1_X + dX*Tcoef;	//X,Y,Z coordinates on target plane
							evY = MWPC_1_Y + dY*Tcoef;
							evZ = MWPC_1_Z + dZ*Tcoef;
							//need to calculate distance to the gas target volume
						}
				*/		

						ene_beam = cs::mass6He + kinE;
						mom_beam = sqrt(ene_beam*ene_beam - cs::mass6He*cs::mass6He);
						
						vBeam->SetMag(mom_beam);
						lvBeam->SetVectM(*vBeam, cs::mass6He);
						outTree->Fill();
					}
				}
			}		
		}
}
	return kTRUE;
}

void beamCutter::SlaveTerminate()
{
	// The SlaveTerminate() function is called after all entries or objects
	// have been processed. When running with PROOF SlaveTerminate() is called
	// on each slave server.

}

void beamCutter::Terminate()
{
	outTree->Write();
	outF->Close();
	std::cout << std::endl;
	// The Terminate() function is the last function to be called during
	// a query. It always runs on the client, it can be used to present
	// the results graphically or save the results to file.

}