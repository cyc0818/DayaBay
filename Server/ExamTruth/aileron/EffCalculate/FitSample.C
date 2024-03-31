{
	TFile f1("ET_ibdAD1_testing.root","new");
    
    int ScaledAD = 1;

        //--------------------------------------------------------------------------------------//

	char m14aIBD[200];
        TChain m14aEvent("Event");
	string m14aFileDir = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Analysis/forM14a/ExamTruth/aileron/Output/IbdSim/20150622/";
	for(int ni=3;ni<5;ni++){
        for(int i=1; i<218;i++){
        	sprintf(m14aIBD, "ExamT_IBD_20150622_140002%d_%04d.root", ni, i);
                //sprintf(m14aIBD, "ExamT_IBD_M14a_140002%d_%04d.root", ni, i);
		cout<<m14aIBD<<endl;
                string m14aFileName = m14aIBD;
                m14aEvent.Add((m14aFileDir+m14aFileName).c_str());
        	}
	}

    	float Mgdls = 21.5;
	float Mls   = 19.9;
        cout<<"entries# : "<<m14aEvent->GetEntries()<<endl;
    
        m14aEvent.Draw("E[1]>>h_m14aEd(1200,0,12)");
	new TCanvas;
        m14aEvent.Draw("E[0]>>h_m14aEp(1200,0,12)");
    
    char pCut[200];
    sprintf(pCut,    "CapTarget==%d", 6);
    m14aEvent.Draw("T2PrevSubEvt[1]>>h_m14aCapT(2000,0,0.0008)", pCut);
	
	TH1D* hEd = new TH1D("hEd","M14A Delay Signal",1200,0,12);
	new TCanvas;
	hEd->Add(h_m14aEd);
	hEd->Write();
    
    TH1D* hCapT = new TH1D("hCapT","M14A CapT",2000,0,0.0004);
    new TCanvas;
    hCapT->Add(h_m14aCapT);
    hCapT->Write();
        //--------------------------------------------------------------------------------------//
        //TH1::AddDirectory(kFALSE);
        gROOT->ProcessLine(".L CBShape.C");

        TF1 CBShape_F("oCBShape", CBShape, 0, 5, 5);
        CBShape_F.SetParNames  ("N" ,  "mean", "sigma", "a", "n");
        CBShape_F.SetParameters(23000,  2.4,    0.151,  1.6, 140 );

        CBShape_F->SetParLimits(0,  0,  0);
        CBShape_F->SetParLimits(1,  2.0,  2.6);
        CBShape_F->SetParLimits(2,  0.1,0.3);
        CBShape_F->SetParLimits(3,  1.6,  1.6);
        CBShape_F->SetParLimits(4,  140,  140);

        //--------------------------------------------------------------------------------------//
        h_m14aEd->Fit("oCBShape","I","", 2.0, 2.5);
	h_m14aEd->Write();

	float hSumNum = h_m14aEd->Integral(0,401);

        float mean    = CBShape_F->GetParameter(1);
        float mean_e  = CBShape_F->GetParError(1);
        float sigma   = CBShape_F->GetParameter(2);
        float sigma_e = CBShape_F->GetParError(2);

        ///
        double IBDmean[9]  = {1,2.304021, 2.306428, 2.312265, 2.319766, 2.312939, 2.314307, 2.316229, 2.321682};
        double IBDsigma[9] = {1,0.138556, 0.139752, 0.137387, 0.137291, 0.139935, 0.136600, 0.141588, 0.144360};
    
        //float scaleF  = 2.37/mean;
        //float cutT = 2.46873 + 0.15779*3.0;
        //float cutB = 2.46873 - 0.15779*3.0;
        //float scaleF  = 2.3683/mean; //sp AD4
        //float scaleF  = 2.3333/mean; //ibd AD1
        //float scaleF  = 2.3483/mean; //ibd AD5
        //float scaleF  = 2.3656/mean; //sp AD3
        //float scaleF  = 2.3888/mean; //sp AD5
        float scaleF = IBDmean[ScaledAD]/mean;
        float cutT = IBDmean[ScaledAD] + IBDsigma[ScaledAD]*3.0;
        float cutB = IBDmean[ScaledAD] - IBDsigma[ScaledAD]*3.0;
    
    //----------------- Fit nGd ---------------------------------//
    h_m14aEd->Fit("gaus","I","", 7.4, 8.4);
    //hSum->Fit("gaus","I","", 8.0, 8.7);
    h_m14aEd->Write();
    float nGdMean = gaus->GetParameter(1);
    float nGdSigma = gaus->GetParameter(2);
    //--------------------------------------------------------------------------------------//

	//--------------------------- scale to 2.37 MeV
	char pCutScaled[200], n3sigmaPCutScaled[200];
	char ScaledEd[200], ScaledEp[200];
	char ScaledPlotLS1[200], ScaledPlotLS2[200];
	char ScaledPlotGdLS1[200], ScaledPlotGdLS2[200];

        new TCanvas; 
        sprintf(ScaledEd, "E[1]*%f>>sh_m14aEd(1200,0,12)", scaleF);
        m14aEvent.Draw(ScaledEd);

        TH1D* rehEd = new TH1D("rehEd","scaled Ed",1200,0,12);
        new TCanvas;
        rehEd->Add(sh_m14aEd);
        rehEd->Draw();

        //--------------------------------------------------------------------------------------//

        TF1 newF("rCBShape", CBShape, 0, 5, 5);
        newF.SetParNames  ("N" ,  "mean", "sigma", "a", "n");
        newF.SetParameters(23000,  2.37,    0.151,  1.6, 140 );

        newF->SetParLimits(0,  0,  0);
        newF->SetParLimits(1,  2,  2.5);
        newF->SetParLimits(2,  0.1,0.3);
        newF->SetParLimits(3,  1.6,  1.6);
        newF->SetParLimits(4,  140,  140);

        //--------------------------------------------------------------------------------------//
        rehEd->Fit("rCBShape","I","", 2.1, 2.6);
        rehEd->Write(); 

	
        float newMean    = newF->GetParameter(1);
        float newSigma   = newF->GetParameter(2);

        float newCutT = newMean + newSigma*3.0;
        float newCutB = newMean - newSigma*3.0;

	cout<<" ------------- nGd Peak ------------- "<<endl;
	cout<<" nGd mean:  "<<nGdMean<<endl;
    cout<<" nGd sigma: "<<nGdSigma<<endl;
    
	cout<<" ------------- before scale ------------- "<<endl;
	cout<<" mean:  "<<mean<<endl;
        cout<<" sigma: "<<sigma<<endl;
	
	cout<<" ------------- after scale ------------- "<<endl;
	cout<<" mean:  "<<newMean<<endl;
        cout<<" sigma: "<<newSigma<<endl;
    
    ofstream opt1;
    opt1.open("peakInfo_ibdAD1_mean_20150622.txt");
    opt1<<nGdMean<<"\t"<<nGdSigma<<"\t"<<mean<<"\t"<<sigma<<"\t"<<newMean<<"\t"<<newSigma<<endl;
	
}
