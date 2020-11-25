#define beamTracker_cxx

#include "beamTracker.h"
#include <TH2.h>
#include <TStyle.h>

//this is the way to load library to root
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/libMr_Blue_Sky.so);

//I am defining my own function inside automatically generated TSelector
//It has to be defined in .h file
//In this case it's a function for choosing position of hit in MWPC
bool beamTracker::Get_MWPC_pos(UShort_t multi, unsigned short *wireNo,
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


void beamTracker::Begin(TTree * /*tree*/)
{
	//I am creating my file with output data - outF
	//It's pointer is defined in header file, so that it is visible throught the code
	//I am assigning value to the TFile, creating file by giving its path and mode in which it should be open
	//You can give just the name of the file and it will be created in the directory in which you started your root session
	//	https://root.cern.ch/doc/v608/classTFile.html - don't read about the structure of the file itself (headers, bytes and compression)
	outF = new TFile("/home/zalewski/Desktop/6He/analysis/SQRBeamAxis/beamSQRinput.root", "RECREATE");

	// I am creating the outTree - it is automatically connnected to the outF - I don't know how
	//	https://root.cern.ch/doc/v608/classTTree.html - there is a lot of reading, so don't overdo it
	//	You can find info on the names (beamTracker and beam_Tracker)
	outTree = new TTree("beamTracker","beam_Tracker");
	
	//I have to create the structure of my Tree by adding branches to it
	// First I have label (1), than data holder (2) and than name for outTree (3)
	//	1.1 Label is for me
	//	2.1 Data holder is the !address! of variable holding my data
	//	2.2 & (address of operator) if it's normal data structure
	//	2.3 and nothing if it's array (name of the array is a pointer to the first element)
	//	3.1 Name under which you save to outTree
	//	3.2 You need to include size of the array ie. [4]
	//	3.3 You need to specify type of data (F for float, I for Integer). Details at the beginning of TTree class reference
	outTree->Branch("MWPC_1_X", &MWPC_1_X,	 "MWPC_1_X/F");
	outTree->Branch("MWPC_2_X", &MWPC_2_X,	 "MWPC_2_X/F");
	outTree->Branch("MWPC_1_Y", &MWPC_1_Y,	 "MWPC_1_Y/F");
	outTree->Branch("MWPC_2_Y", &MWPC_2_Y,	 "MWPC_2_Y/F");
	outTree->Branch("SQX_R_strip", &SQX_R_strip,	"SQX_R_strip/I");
	outTree->Branch("SQY_R_strip", &SQY_R_strip,	"SQY_R_strip/I");
	outTree->Branch("CsI_R_strip", &CsI_R_strip,	"CsI_R_strip/I");

	outTree->Branch("X6He", &X6He,	 "X6He/D");
	outTree->Branch("X6Helab", &X6Helab, "X6Helab/D");
	outTree->Branch("X6Hedet", &X6Hedet, "X6Hedet/D");

	outTree->Branch("Y6He", &Y6He,	 "Y6He/D");
	outTree->Branch("Y6Helab", &Y6Helab, "Y6Helab/D");
	outTree->Branch("Y6Hedet", &Y6Hedet, "Y6Hedet/D");

	outTree->Branch("Z6He", &Z6He,	 "Z6He/D");
	outTree->Branch("Z6Helab", &Z6Helab, "Z6Helab/D");
	outTree->Branch("Z6Hedet", &Z6Hedet, "Z6Hedet/D");

	outTree->Branch("evX", &evX, "evX/D");
	outTree->Branch("evY", &evY, "evY/D");
	outTree->Branch("evZ", &evZ, "evZ/D");

	outTree->Branch("tF6", tF6,	"tF6[4]/D");
	outTree->Branch("F6", F6,	"F6[4]/D");

	outTree->Branch("sqrde", &sqrde, "sqrde/D");
	outTree->Branch("fsqrde", &fsqrde, "fsqrde/D");
	outTree->Branch("sqretot", &sqretot, "sqretot/D");

	outTree->Branch("kinE", &kinE, "kinE/D");
	outTree->Branch("tof", &tof, "tof/D");

	outTree->Branch("geo", &geo,	"geo/I");
	outTree->Branch("run", &run,	"run/I");

	//	 I am printing (in console) what I've just created to check if it's correct
	outTree->Print();

	//	I will use TRandom3 for smearing bins
	rnd = new TRandom3();

	//	You can supply TTreeSelector with Option (TString) and you can access it	
	TString option = GetOption();

	//	I am defining my supprt class which has method of reading calibration parameters from my .txt file
	//	
	maynard = new TOOL();
	maynard->params_loader("SQX_R_ec.cal", a_SQX_R, b_SQX_R, 32);
	maynard->params_loader("SQY_R_ec.cal", a_SQY_R, b_SQY_R, 16);
	maynard->params_loader("csi_r_ec.cal", a_CsI_R, b_CsI_R, 16);
}

void beamTracker::SlaveBegin(TTree * /*tree*/)
{

	TString option = GetOption();

	//	I used option to pass total number of events
	//	I use Atoll to convert string to long long
	nEntries = option.Atoll();

	//	This reads width of console so I can create status bar later
	struct winsize size;
	ioctl(STDOUT_FILENO,TIOCGWINSZ,&size);
	consoleWidth = size.ws_col-8;

	xCut = new TCutG("Xcut",8);
	xCut->SetVarX("X6He");
	xCut->SetVarY("evX");
	xCut->SetFillStyle(1000);
	xCut->SetPoint(0,-34.7604,-24.2486);
	xCut->SetPoint(1,-45.8866,-23.549);
	xCut->SetPoint(2,-52.7646,-20.5758);
	xCut->SetPoint(3,-53.4221,-27.9214);
	xCut->SetPoint(4,-52.9163,-41.9129);
	xCut->SetPoint(5,-49.4773,-51.8819);
	xCut->SetPoint(6,-34.8615,-47.5096);
	xCut->SetPoint(7,-34.7604,-24.2486);

	yCut = new TCutG("Ycut",12);
	yCut->SetVarX("Y6He");
	yCut->SetVarY("evY");
	yCut->SetTitle("Graph");
	yCut->SetFillStyle(1000);
	yCut->SetPoint(0,17.7597,24.4572);
	yCut->SetPoint(1,-1.14915,16.2939);
	yCut->SetPoint(2,-10.6036,15.5778);
	yCut->SetPoint(3,-14.9912,3.11807);
	yCut->SetPoint(4,-18.5954,-11.2035);
	yCut->SetPoint(5,-16.6627,-18.7939);
	yCut->SetPoint(6,-3.13406,-13.3517);
	yCut->SetPoint(7,8.04408,-1.46482);
	yCut->SetPoint(8,26.744,8.27383);
	yCut->SetPoint(9,26.0127,18.2989);
	yCut->SetPoint(10,24.4979,25.1732);
	yCut->SetPoint(11,17.7597,24.4572);

	dehe = new TCutG("dehe",8);
	dehe->SetVarX("sqretot");
	dehe->SetVarY("sqrde");
	dehe->SetTitle("Graph");
	dehe->SetFillStyle(1000);
	dehe->SetPoint(0,96.7182,23.3559);
	dehe->SetPoint(1,176.741,16.1147);
	dehe->SetPoint(2,178.467,13.998);
	dehe->SetPoint(3,152.264,14.6664);
	dehe->SetPoint(4,139.554,15.3905);
	dehe->SetPoint(5,113.35,17.8971);
	dehe->SetPoint(6,90.285,21.6292);
	dehe->SetPoint(7,96.7182,23.3559);
}

Bool_t beamTracker::Process(Long64_t entry)
{
	fReader.SetLocalEntry(entry);

	//	I am getting name of the tree in order to get number of the file
	std::string fName = fReader.GetTree()->GetCurrentFile()->GetName();
	std::string fNumber = fName.substr(fName.find("run0")+3, 2);
	run = std::stoi(fNumber);

	//	setting flags (for each event)
	fMWPC = false;
	fTDC = false;
	fMulti = false;
	sqrde = 0;
	sqretot = 0;
	fxfit = false;
	fyfit = false;
	fdehe = false;

	//	This is my status bar
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

	//	saving data from TTreeReader into my data container
	for (int iii = 0; iii < 4; ++iii)
	{
		F6[iii] = inF6[iii];
		tF6[iii] = intF6[iii];
	}

	//SQR calibration
	for (int iii = 0; iii < 16; ++iii)
	{
		CsI_R[iii]=(in_CsI_R[iii]+gRandom->Uniform())*b_CsI_R[iii]+a_CsI_R[iii];
		SQY_R[iii]=(in_SQY_R[iii]+gRandom->Uniform())*b_SQY_R[iii]+a_SQY_R[iii];
	}

	//	saving MWPC info into my own container, since it's hard to pass is directly from TTreeReader
	for (int iii= 0; iii<32; ++iii)
	{
		temp_x1[iii] = x1[iii];
		temp_x2[iii] = x2[iii];
		temp_y1[iii] = y1[iii];
		temp_y2[iii] = y2[iii];
		SQX_R[iii]=(in_SQX_R[iii]+gRandom->Uniform())*b_SQX_R[iii]+a_SQX_R[iii];
		//if ( SQX_R[iii]>0) printf("%f\n", SQX_R[iii]);
	}

	//choosing events w multiplicity==1
	if (std::count_if(std::begin(SQX_R), std::end(SQX_R), [](float i){return i > 5.0;}) == 1	&&
		 std::count_if(std::begin(SQY_R), std::end(SQY_R), [](float i){return i > 5.0;}) == 1)
		{
			CsI_R_strip = std::distance(std::begin(CsI_R), std::max_element(std::begin(CsI_R), std::end(CsI_R)));
			SQX_R_strip = std::distance(std::begin(SQX_R), std::max_element(std::begin(SQX_R), std::end(SQX_R)));
			SQY_R_strip = std::distance(std::begin(SQY_R), std::max_element(std::begin(SQY_R), std::end(SQY_R)));

			sqrde = SQX_R[SQX_R_strip];
			sqretot = CsI_R[CsI_R_strip];

			if (dehe->IsInside(sqretot,sqrde))
				{
					fdehe = true;
				}
		}

	//proper times in TDCs
	if((tF3[0]-tF3[1]) > -50.0 && (tF3[0]-tF3[1]) < 50.0 &&
		(tF3[0]-tF3[2]) > -50.0 && (tF3[0]-tF3[2]) < 50.0 &&
		(tF3[0]-tF3[3]) > -50.0 && (tF3[0]-tF3[3]) < 50.0 &&
		(tF5[0]-tF5[1]) > -50.0 && (tF5[0]-tF5[1]) < 50.0 &&
		(tF5[0]-tF5[2]) > -50.0 && (tF5[0]-tF5[2]) < 50.0 &&
		(tF5[0]-tF5[3]) > -50.0 && (tF5[0]-tF5[3]) < 50.0 && fdehe)
		{
			tof = ((tF5[0]+tF5[1]+tF5[2]+tF5[3])/4 - (tF3[0]+tF3[1]+tF3[2]+tF3[3])/4.0)*0.125 + cs::tof_const;
			if (tof>100 && tof<200)
			{
				fTDC=true;
			}			
			//printf("Sup fTDC\n");
		}

	//proper tracking - my function (at the beginning) returns true if the event is correct
	if (	Get_MWPC_pos(*nx1, temp_x1, &MWPC_1_X, cs::MWPC_1_X_id)	&&
			Get_MWPC_pos(*nx2, temp_x2, &MWPC_2_X, cs::MWPC_2_X_id)	&&
			Get_MWPC_pos(*ny1, temp_y1, &MWPC_1_Y, cs::MWPC_1_Y_id)	&&
			Get_MWPC_pos(*ny2, temp_y2, &MWPC_2_Y, cs::MWPC_2_Y_id)	&& fTDC	)
		{
			fMWPC=true;
			//printf("Sup fMWPC\n");
		}

	//I am starting my code only here and only if I have proper TDC signals, MWPC and multiplicity in Si dets
	if (fMWPC)
	{
		double SQRdist = 250.0;
		double SQRang = 15.0 * TMath::DegToRad();
		
		double SQX_R_s = SQX_R_strip + rnd->Uniform(0.0,1.0)-0.5;
		double SQY_R_s = SQY_R_strip + rnd->Uniform(0.0,1.0)-0.5;

		fMWPC_1_X = MWPC_1_X + rnd->Uniform(0.0,1.25)-0.625;
		fMWPC_1_Y = MWPC_1_Y + rnd->Uniform(0.0,1.25)-0.625;
		fMWPC_2_X = MWPC_2_X + rnd->Uniform(0.0,1.25)-0.625;
		fMWPC_2_Y = MWPC_2_Y + rnd->Uniform(0.0,1.25)-0.625;
		fMWPC_1_Z = -816.0;
		fMWPC_2_Z = -270.0;

		dX = fMWPC_2_X - fMWPC_1_X;
		dY = fMWPC_2_Y - fMWPC_1_Y;
		dZ = fMWPC_2_Z - fMWPC_1_Z;

		TVector3 sqrPoint(SQRdist*sin(-SQRang), 0.0, SQRdist*cos(SQRang));
		TVector3 beamPoint(fMWPC_2_X, fMWPC_2_Y, fMWPC_2_Z);
		TVector3 sqrPerpendicular(SQRdist*sin(-SQRang), 0.0, SQRdist*cos(SQRang));
		TVector3 vBeam(dX, dY, dZ);
		double dCoeff = ((sqrPoint-beamPoint).Dot(sqrPerpendicular))/(vBeam.Dot(sqrPerpendicular));

		evX = fMWPC_2_X + dX * dCoeff;
		evY = fMWPC_2_Y + dY * dCoeff;
		evZ = fMWPC_2_Z + dZ * dCoeff;

		X6Helab = SQRdist*sin(-SQRang) - cs::SQRstartX * cos(SQRang);
		Y6Helab = cs::SQRstartY;
		Z6Helab = SQRdist*cos(SQRang) - cs::SQRstartX * sin(SQRang);

		X6Hedet = cs::widthStripX * SQX_R_s * cos(SQRang);
		Y6Hedet = cs::widthStripY * SQY_R_s;
		Z6Hedet = cs::widthStripX * SQX_R_s * sin(SQRang);

		X6He = X6Helab + X6Hedet;
		Y6He = Y6Helab + Y6Hedet;
		Z6He = Z6Helab + Z6Hedet;

		if (yCut->IsInside(Y6He,evY))
		{
			if (xCut->IsInside(X6He,evX))
			{
				fxfit = true;
			}
		}
		
		double beta_squared = pow((cs::tofBase/tof)/cs::c, 2.0);
		double gamma=1.0/sqrt(1.0-beta_squared);

		if (F5[0]>660 && tof>155 && tof<180)
		{
			kinE = cs::mass6He * (gamma-1.0);
		}

		else if (F5[0]<660 && F5[0]>0 && tof>155 && tof<180)
		{
			kinE = cs::mass3H * (gamma-1.0);
		}

		else if (F5[0]>0 && tof>140 && tof<155)
		{
			kinE = cs::mass8Li * (gamma-1.0);
		}

		geo = 1;

		//	crucial moment - you have to Fill Tree after each event

		if (fxfit)
		{
			outTree->Fill();
		}
		
	}

	return kTRUE;
}

void beamTracker::SlaveTerminate()
{
	//once you finish loop, you need to Write the Tree and Close outFile
	outTree->Write();
	outF->Close();
	std::cout << std::endl;
}

void beamTracker::Terminate()
{
}
