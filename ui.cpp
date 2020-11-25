int ui()
{
    TString str_name, TreePath;  
	TString raw_data_path{"/home/zalewski/data/bank/raw/geo5/"};
	TChain *inChain = new TChain();
    TTree *currentTree;
	TSystemDirectory *dir_data = new TSystemDirectory("data",raw_data_path.Data());
	//TSelector *selector = TSelector::GetSelector("/home/zalewski/aku/gasTar/cleaner.C");
	short fcounter = 0;
	TIter bluster = dir_data->GetListOfFiles();
	while (TObject *obj = bluster())
	{
		str_name = obj->GetName();
		if (str_name.Contains("root") &&  //if we want to ommit some phrase (np.li9_3_21_0)
			!str_name.Contains("li9") //  "!"  sign is important
								)
		{
			TreePath.Form("%s%s/AnalysisxTree",raw_data_path.Data(),str_name.Data());
			TString inputFilePath = raw_data_path + str_name;
			TFile inF(inputFilePath.Data(), "READ");
            currentTree = (TTree*)inF.Get("AnalysisxTree");
			TString outputFilePath = inputFilePath.ReplaceAll("raw","cln");
			TFile outF(inputFilePath.Data(),"RECREATE");
			TTree *outputTree;
			outputTree = currentTree->CopyTree("NeEvent.trigger>1");
			outputTree->Write();
			outF.Close();
			inF.Close();

            //currentTree->Process("cleaner", str_name.Data());
			//if (!inChain->Add(TreePath.Data(),0)) return 0;
			fcounter++;
			printf("fName:\t%s\n",TreePath.Data());
		}
	}

	printf("\n#\n##\n###\n##\n#\n\n");
	printf("\n\tWe have %lld entries from %d files\n",inChain->GetEntriesFast(), fcounter);
	printf("\n#\n##\n###\n##\n#\n\n");
/*	TObjArray *fileElements=inChain->GetListOfFiles();
	TIter next(fileElements);
	TChainElement *chEl=0;
	while (( chEl=(TChainElement*)next() ))
	{
		TFile f(chEl->GetTitle());
 		printf("I opened:\t%s\t\tfile\n",chEl->GetTitle());
	}
	printf("\n#\n##\n###\n##\n#\n\n");

    //inChain->Process("cleaner.C");
	*/
    return 0;
}