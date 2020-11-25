#include <Rtypes.h>
#include "/usr/local/include/TString.h"
#include "/usr/local/include/TCanvas.h"
#include "/usr/local/include/TH1.h"
#include "/home/zalewski/aku/wrk/ELC_legacy/AELC.h"
#include "/home/zalewski/aku/wrk/ELC_legacy/ELC.h"
R__LOAD_LIBRARY(/home/zalewski/aku/wrk/ELC_legacy/libEloss.so);
double para = 1.0;


bool histogramer()
{
	int si_Nel=1;
	Double_t si_A[1]={28};
	Double_t si_Z[1]={14};
	Double_t si_W[1]={1};
    AELC *he6Si = new ELC(6, 2, si_Nel, 2.35, si_A, si_Z, si_W, 300.,1500);
    double tempE = he6Si->GetE(160.0, 644.0);
	TFile *inF = new TFile{"cernstaff.root", "READ"};
	TTreeReader fReader{"T", inF};
    TTreeReaderValue<Int_t> age = {fReader, "Age"};
	TTreeReaderValue<Int_t> service = {fReader, "Service"};
    TTreeReaderValue<Int_t> grade = {fReader, "Grade"};
    TTreeReaderValue<Int_t> children = {fReader, "Children"};
    TTreeReaderValue<Int_t> cost = {fReader, "Cost"};

    TH2D *hist1 = new TH2D("myhist1","myhist1", 100, 00.0, 100.0, 35, 0.0, 35.0);
    TH2D *hist2 = new TH2D("myhist2","myhist1", 100, 00.0, 100.0, 35, 0.0, 35.0);
    TH2D *hist3 = new TH2D("myhist3","myhist1", 100, 00.0, 100.0, 35, 0.0, 35.0);
    TH2D *hist4 = new TH2D("myhist4","myhist1", 100, 00.0, 100.0, 35, 0.0, 35.0);
    while(fReader.Next())
    {
        double ageF = *age*para;
        hist1->Fill(ageF, *service);
        hist2->Fill(ageF, *grade);
        hist3->Fill(ageF, *service);
        hist4->Fill(ageF, *children);
    }
    TCanvas *myCanv = new TCanvas();
    myCanv->Divide(2,2);
    myCanv->cd(1);
    hist1->Draw("cont");
    myCanv->cd(2);
    hist1->Draw();
    myCanv->cd(3);
    hist1->Draw();
    myCanv->cd(4);
    hist1->Draw();
    gSystem->ProcessEvents();
    myCanv->Modified();
    myCanv->Update();   
    return 1;
}

bool b(int key)
{
switch (key)
	{
	case 3:
		std::cout<<"Case 3 (up) in switch"<<endl;
		para+=0.1;
		break;

	case 4:
		std::cout<<"Case 4 (down) in switch"<<endl;
		para-=0.1;
		break;
	case 10:
		gApplication->Terminate();
		break;

	default:
		break;
	}
histogramer();
return 0;
}


int mini()
{
    gApplication->Connect("KeyPressed(int)",0,0,"b(int)");
    void KeyPressed(int key); //SIGNAL
    //gApplication->Run(kTRUE);
    return 1;
}