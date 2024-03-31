{
	#include <iomanip>
    
    ifstream Data1;
	//TFile f1("mcPlot.root","new");
	float Mgdls = 21.5;
	float Mls   = 19.9;
	float NprodGdls = 102762.0;
	float NprodLS	= 110351.0;
	float factor = (NprodGdls/NprodLS)*(Mls/Mgdls);

        //--------------------------------------------------------------------------------------//

	char gdlsIBD[200], lsIBD[200], oldLsIBD[200];
        TChain gdlsEvent("Event");
        //string gdlsFileDir = "/work/wangzhe_work/bzhu/Sim/Analysis/ExamTruth/aileron/output/oldGdLS/";
	//string gdlsFileDir = "/work/wangzhe_work/bzhu/Sim/Analysis/ExamTruth/aileron/output/GdLS/r20369/";
        string gdlsFileDir = "/work/wangzhe_work/bzhu/Sim/Analysis/ExamTruth/aileron/output/Acrylic/ibdInGdLS/r20369/Case1/"; 
        for(int i=0; i<151;i++){
		//sprintf(gdlsIBD, "ExamT_IBD_DYB_AD1_GdLS_%02d.root", i);
                //sprintf(gdlsIBD, "ExamT_recon_GdLS_modif_Absop_p3_r%02d.root", i);
                sprintf(gdlsIBD, "ExamT_IBD_DYB_AD1_GdLS_Case1_%02d.root", i);
                string gdlsFileName = gdlsIBD;
                gdlsEvent.Add((gdlsFileDir+gdlsFileName).c_str());
        }

        TChain lsEvent("Event");
        //string lsFileDir = "/work/wangzhe_work/bzhu/Sim/Analysis/ExamTruth/aileron/output/oldLS/";
	//string lsFileDir = "/work/wangzhe_work/bzhu/Sim/Analysis/ExamTruth/aileron/output/LS/r20369/";
        string lsFileDir = "/work/wangzhe_work/bzhu/Sim/Analysis/ExamTruth/aileron/output/Acrylic/ibdInLS/r20369/Case3/"; 
        for(int i=0; i<51;i++){
		//sprintf(lsIBD, "ExamT_IBD_DYB_AD1_LS_%02d.root", i);
                //sprintf(lsIBD, "ET_recon_LS_modif_Absop_p3_r%02d.root", i);
                sprintf(lsIBD, "ExamT_IBD_DYB_AD1_LS_Case3_%02d.root", i);
                string lsFileName = lsIBD;
                lsEvent.Add((lsFileDir+lsFileName).c_str());
        }

	cout<<gdlsEvent->GetEntries()<<"\t"<<lsEvent->GetEntries()<<endl;
        gdlsEvent.Draw("E[1]>>h_gdls0(400,0,12)");
        gdlsEvent.Draw("E[1]>>h_gdLs0b(400,0,12)","CapTarget==1","same");
        float HcapGdls = h_gdLs0b->Integral(1,401);
	new TCanvas;
        lsEvent.Draw("E[1]>>h_ls0(400,0,12)");
        lsEvent.Draw("E[1]>>h_ls0b(400,0,12)","CapTarget==1","same");
        float HcapLs = h_ls0b->Integral(1,401);

	
        //--------------------------------------------------------------------------------------//
        gROOT->ProcessLine(".L CBShape.C");

        TF1 CBShape_F("CBShape", CBShape, 0, 5, 5);
        CBShape_F.SetParNames  ("N" ,  "mean", "sigma", "a", "n");
        CBShape_F.SetParameters(5500,  2.4,    0.151,  1.5, 10 );

        CBShape_F->SetParLimits(0,  0,  50000);
        CBShape_F->SetParLimits(1,  2,  2.6);
        CBShape_F->SetParLimits(2,  0.1,0.3);
        CBShape_F->SetParLimits(3,  1,  2);
        CBShape_F->SetParLimits(4,  0,  200);

        //--------------------------------------------------------------------------------------//
        //hSum->Fit("CBShape","","", 2, 3.1);
	//hSum->Write();
    
    float Val1[6];
    Data1.open("peakInfo-LSibd-Oav+1.5.txt");
    for(int i=0;i<4;i++) Data1 >> Val1[i];

    //------ Without Scaled ------
    float EpScaleF= 1.0;
    float scaleF  = 1.0;
    float mean  = Val1[0];  
    float sigma = Val1[1];  
    //------  Scaled ------
    
    /*	
    float EpScaleF= 2.3344/Val1[0];//8.0535/Val1[0];   //AD1 nGd peak
    float scaleF  = 2.3344/Val1[0];   //AD1 nH peak
    float mean  = Val1[2];  
    float sigma = Val1[3];  
   */
     
        float cutT = mean + sigma*3.0;
        float cutB = mean - sigma*3.0;
	float cutEp= 1.5;
	char nCut[200],pCut[200], dCut[200], TimeCut[200];
	char n3sigmaPCut[200], n3sigmaDCut[200], n3sigmaTimeCut[200]; 
	char notHcut[200], notHcut3sig0[200], notHcut3sig[200];		

        new TCanvas;    //-------------- En> 1 MeV
        sprintf(pCut, 	 "E[0]*%f>%f && CapTarget==%d ", EpScaleF, cutEp, 1);
        sprintf(notHcut, "E[0]*%f>%f && CapTarget!=%d ", EpScaleF, cutEp, 1);
        sprintf(TimeCut, "E[0]*%f>%f && CapTarget==%d && ((TrigSec[1]-TrigSec[0])+(TrigNano[1]-TrigNano[0])*1e-9)<%f ", EpScaleF, cutEp, 1,0.0004);
        sprintf(dCut, "E[0]*%f>%f && CapTarget==%d && ((TrigSec[1]-TrigSec[0])+(TrigNano[1]-TrigNano[0])*1e-9)<%f && D2First[1]<%f", EpScaleF, cutEp, 1,0.0004,500);
        lsEvent.Draw("E[1]>>h_ls1(400,0,12)",pCut);
        float Nls1p = h_ls1->Integral(1,401);
        lsEvent.Draw("E[1]>>h_ls2(400,0,12)",TimeCut,"same");
        float Nls1t = h_ls2->Integral(1,401);
        lsEvent.Draw("E[1]>>h_ls3(400,0,12)",dCut,"same");
        float Nls1d = h_ls3->Integral(1,401);
        lsEvent.Draw("E[1]>>h_ls4(400,0,12)",notHcut,"same");
        float Nls1other = h_ls4->Integral(1,401);

	new TCanvas;
        gdlsEvent.Draw("E[1]>>h_gdls1(400,0,12)",pCut);
        float Ngdls1p = h_gdls1->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdls2(400,0,12)",TimeCut,"same");
        float Ngdls1t = h_gdls2->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdls3(400,0,12)",dCut,"same");
        float Ngdls1d = h_gdls3->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdls4(400,0,12)",notHcut,"same");
        float Ngdls1other = h_gdls4->Integral(1,401);

        new TCanvas;    // ------------- En 3sigma 
        sprintf(nCut, "E[1]*%f>%f && E[1]*%f<%f && CapTarget ==%d ", scaleF, cutB, scaleF, cutT,1);
        sprintf(notHcut3sig0, "E[1]*%f>%f && E[1]*%f<%f && CapTarget !=%d ", scaleF, cutB,scaleF, cutT,1);
        lsEvent.Draw("E[1]>>h_lsEd0(400,0,12)", nCut);
        float NlsEdH = h_lsEd0->Integral(1,401);
        lsEvent.Draw("E[1]>>h_lsEd1(400,0,12)", notHcut3sig0,"same");
        float NlsEdOther = h_lsEd1->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdlsEd0(400,0,12)", nCut,"same");
        float NgdlsEdH = h_gdlsEd0->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdlsEd1(400,0,12)", notHcut3sig0,"same");
        float NgdlsEdOther = h_gdlsEd1->Integral(1,401);

        new TCanvas;    // ------------- En 3sigma Cut and Ep>1 MeV cut
        sprintf(n3sigmaPCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && CapTarget ==%d ", scaleF, cutB, scaleF, cutT, EpScaleF, cutEp,1);
        sprintf(notHcut3sig, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && CapTarget !=%d ", scaleF, cutB,scaleF, cutT, EpScaleF, cutEp,1);
        sprintf(n3sigmaTimeCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && CapTarget ==%d && ((TrigSec[1]-TrigSec[0])+(TrigNano[1]-TrigNano[0])*1e-9)<%f ", scaleF, cutB, scaleF, cutT, EpScaleF,cutEp,1,0.0004);
        sprintf(n3sigmaDCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && CapTarget ==%d && ((TrigSec[1]-TrigSec[0])+(TrigNano[1]-TrigNano[0])*1e-9)<%f && D2First[1]<%f",scaleF, cutB,scaleF, cutT,EpScaleF, cutEp,1,0.0004, 500);
        lsEvent.Draw("E[1]>>h_lsS1(400,0,12)", n3sigmaPCut,"same");
        float Nls3p = h_lsS1->Integral(1,401);
        lsEvent.Draw("E[1]>>h_lsS2(400,0,12)",n3sigmaTimeCut,"same");
        float Nls3t = h_lsS2->Integral(1,401);
        lsEvent.Draw("E[1]>>h_lsS3(400,0,12)",n3sigmaDCut,"same");
        float Nls3d = h_lsS3->Integral(1,401);
        lsEvent.Draw("E[1]>>h_lsS4(400,0,12)",notHcut3sig,"same");
        float Nls3other = h_lsS4->Integral(1,401);

	new TCanvas;
        gdlsEvent.Draw("E[1]>>h_gdlsS1(400,0,12)", n3sigmaPCut);
        float Ngdls3p = h_gdlsS1->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdlsS2(400,0,12)",n3sigmaTimeCut,"same");
        float Ngdls3t = h_gdlsS2->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdlsS3(400,0,12)",n3sigmaDCut,"same");
        float Ngdls3d = h_gdlsS3->Integral(1,401);
        gdlsEvent.Draw("E[1]>>h_gdlsS4(400,0,12)",notHcut3sig,"same");
        float Ngdls3other = h_gdlsS4->Integral(1,401);

	cout<<"Total H cap  (gdls/ ls): "<<HcapGdls<<"\t"<<HcapLs<<endl;
	cout<<" Ep Cut    (gdls /  ls): "<<Ngdls1p<<"\t"<<Nls1p<<endl;
	cout<<" Ep other  (gdls /  ls): "<<Ngdls1other<<"\t"<<Nls1other<<endl;
	//cout<<" TimeCut  (gdls /  ls): "<<Ngdls1t<<"\t"<<Nls1t<<endl;
	//cout<<" DisCut   (gdls /  ls): "<<Ngdls1d<<"\t"<<Nls1d<<endl;
	cout<<" Ed Cut    (gdls /  ls): "<<NgdlsEdH<<"\t"<<NlsEdH<<endl;
	cout<<" Ed other  (gdls /  ls): "<<NgdlsEdOther<<"\t"<<NlsEdOther<<endl;
        cout<<" Ep and Ed Cut    (gdls /  ls): "<<Ngdls3p<<"\t"<<Nls3p<<endl;
        //cout<<" TimeCut  (gdls /  ls): "<<Ngdls3t<<"\t"<<Nls3t<<endl;
        //cout<<" DisCut   (gdls /  ls): "<<Ngdls3d<<"\t"<<Nls3d<<endl;
	cout<<" Ep and Ed other  (gdls /  ls): "<<Ngdls3other<<"\t"<<Nls3other<<endl;

    float totalGdLs = gdlsEvent->GetEntries();
    float totalLs = lsEvent->GetEntries();
    ofstream opt1;
    opt1.open("effTable-LSibd-Oav+1.5.txt");
    opt1<<" & Total Events & Total H cap & E_p Cut & E_d Cut & E_p and E_d Cut & E_p other & E_d other & E_p and E_d other "<<endl; 
    opt1<<" GdLS & "<<gdlsEvent->GetEntries()<<" & "<<HcapGdls<<" & "<<Ngdls1p<<" & "<<NgdlsEdH<<" & "<<Ngdls3p<<" & "<<Ngdls1other<<" & "<<NgdlsEdOther<<" & "<<Ngdls3other<<endl;
    opt1<<" LS & "<<lsEvent->GetEntries()<<" & "<<HcapLs<<" & "<<Nls1p<<" & "<<NlsEdH<<" & "<<Nls3p<<" & "<<Nls1other<<" & "<<NlsEdOther<<" & "<<Nls3other<<endl;
    opt1<<" & $frac{Total H cap}{Total Events}$ & & $varepsilon_{e-p}$ & $varepsilon_{e-d}$ & $varepsilon_{e-pd}$ & $varepsilon_{o-p}$ & $varepsilon_{o-d}$ & $varepsilon_{o-pd}$ "<<endl;
    opt1<<setiosflags(ios::fixed) << setprecision(4)
        <<" GdLS & "<<HcapGdls/(1.0*totalGdLs )<<" & "<<Ngdls1p/(1.0*HcapGdls)<<" & "<<NgdlsEdH/(1.0*HcapGdls)<<" & "<<Ngdls3p/(1.0*HcapGdls)<<" & "<<Ngdls1other/(1.0*HcapGdls)<<" & "<<NgdlsEdOther/(1.0*HcapGdls)<<" & "<<Ngdls3other/(1.0*HcapGdls)<<endl;
    opt1<<" LS & "<<HcapLs/(1.0*totalLs )<<" & "<<Nls1p/(1.0*HcapLs)<<" & "<<NlsEdH/(1.0*HcapLs)<<" & "<<Nls3p/(1.0*HcapLs)<<" & "<<Nls1other/(1.0*HcapLs)<<" & "<<NlsEdOther/(1.0*HcapLs)<<" & "<<Nls3other/(1.0*HcapLs)<<endl;

}
