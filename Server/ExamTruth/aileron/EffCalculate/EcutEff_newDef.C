// spEffCalcu.C is copied from newEffCalculate.C
// 
{
	#include <iomanip>
    
    int ScaledAD = 1;
    ifstream Data1;
	//TFile f1("mcPlot.root","new");
	float Mgdls = 21.5;
	float Mls   = 19.9;
	float NprodGdls = 102762.0;
	float NprodLS	= 110351.0;
	float factor = (NprodGdls/NprodLS)*(Mls/Mgdls);

    int detID = 4; // 1: GdDopedLS; 2: LiquidScintillator; 3: Acrylic; 4:MO
        //--------------------------------------------------------------------------------------//
        char m14aIBD[200];
        TChain m14aEvent("Event");
        string m14aFileDir = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Analysis/forM14a/ExamTruth/aileron/Output/IbdSim/M14a/";
        for(int ni=3;ni<5;ni++){
            for(int i=1; i<218;i++){
            //sprintf(m14aIBD, "ExamT_IBD_20150622_140002%d_%04d.root", ni, i);
            sprintf(m14aIBD, "ExamT_IBD_M14a_140002%d_%04d.root", ni, i);
            //sprintf(m14aIBD, "ExamT_IBD_M14a_1400024_%04d.root", i);
                string m14aFileName = m14aIBD;
                m14aEvent.Add((m14aFileDir+m14aFileName).c_str());
            }
        }
        cout<<"entries# : "<<m14aEvent->GetEntries()<<endl;
    
        m14aEvent.Draw("E[1]>>h_m14aEd(400,0,12)");
        m14aEvent.Draw("E[1]>>h_m14aEd_GenDet(400,0,12)",TString::Format("GenDet==%1d",detID),"same");
        m14aEvent.Draw("E[1]>>h_m14aEd_Hcap(400,0,12)",TString::Format("CapTarget==1 && GenDet==%1d",detID),"same");
        float detSampleNum = h_m14aEd_GenDet->Integral(1,401);
        float HcapNum = h_m14aEd_Hcap->Integral(1,401);
       
	
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
    Data1.open("peakInfo_ibdAD1_mean.txt");
    for(int i=0;i<6;i++) Data1 >> Val1[i];

    //------ Without Scaled ------
/*	
    float EpScaleF= 1.0;
    float scaleF  = 1.0;
    float mean  = Val1[2];  
    float sigma = Val1[3];  
*/	
    //------  Scaled ------
    double IBDmean[9]  = {1,2.304021, 2.306428, 2.312265, 2.319766, 2.312939, 2.314307, 2.316229, 2.321682};
    double IBDsigma[9] = {1,0.138556, 0.139752, 0.137387, 0.137291, 0.139935, 0.136600, 0.141588, 0.144360};
   
    float EpScaleF = 7.94835/Val1[0];
    float scaleF  = IBDmean[ScaledAD]/Val1[2];
    //float EpScaleF= 8.0535/Val1[0];   //AD1 nGd peak
    //float scaleF  = 2.3333/Val1[2];   //AD1 nH peak
    float mean  = Val1[4];  
    float sigma = Val1[5];  
   
        float cutT = mean + sigma*3.0;
        float cutB = mean - sigma*3.0;
	float cutEp= 1.5;
	char nCut[200],pCut[200], dCut[200], TimeCut[200], TimeCut0[200], dCut0[200];
	char n3sigmaPCut[200], n3sigmaDCut[500], n3sigmaTimeCut[500], n3sigmaDCut0[200], n3sigmaTimeCut0[200];
	char notHcut[200], notHcut3sig0[200], notHcut3sig[200];
    char onlyEnCut_T0[200], onlyEnCut_T[200];

        new TCanvas;    //-------------- Ep> 1.5 MeV
        sprintf(pCut, 	 "E[0]*%f>%f && GenDet==%1d", EpScaleF, cutEp, detID);
        sprintf(TimeCut, "E[0]*%f>%f && GenDet==%1d && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)>%f && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)<%f ", EpScaleF, cutEp, detID, 0.000001, 0.0004);
        sprintf(dCut, "E[0]*%f>%f && GenDet==%1d && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)<%f && D2First[1]<%f", EpScaleF, cutEp, detID, 0.0004,500);
    
	new TCanvas;
        m14aEvent.Draw("E[1]>>h_Ed1(400,0,12)",pCut);
        float NEd_p1 = h_Ed1->Integral(1,401);
        m14aEvent.Draw("E[1]>>h_Ed2(400,0,12)",TimeCut,"same");
        float NEd_t1 = h_Ed2->Integral(1,401);
        m14aEvent.Draw("E[1]>>h_Ed3(400,0,12)",dCut,"same");
        float NEd_d1 = h_Ed3->Integral(1,401);

        new TCanvas;    // ------------- En 3sigma
        sprintf(nCut, "E[1]*%f>%f && E[1]*%f<%f && GenDet==%1d", scaleF, cutB, scaleF, cutT,detID);
        sprintf(onlyEnCut_T, "E[1]*%f>%f && E[1]*%f<%f && GenDet==%1d && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)<%f ", scaleF, cutB, scaleF, cutT, detID, 0.0004);

        m14aEvent.Draw("E[1]>>h_Ed3sig(400,0,12)", nCut,"same");
        float NEd_3sigma = h_Ed3sig->Integral(1,401);

    m14aEvent.Draw("E[1]>>h_EdT1(400,0,12)", onlyEnCut_T,"same");
    float NEd_T11 = h_EdT1->Integral(1,401);
    
    
        new TCanvas;    // ------------- En 3sigma Cut and Ep>1 MeV cut

        //sprintf(n3sigmaDCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && CapTarget ==%d && GenDet==%1d && ((TrigSec[1]-TrigSec[0])+(TrigNano[1]-TrigNano[0])*1e-9)<%f && D2First[1]<%f",scaleF, cutB,scaleF, cutT,EpScaleF, cutEp,1,detID, 0.0004, 500);
    
        sprintf(n3sigmaPCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && GenDet==%1d", scaleF, cutB, scaleF, cutT, EpScaleF, cutEp, detID);
        sprintf(n3sigmaTimeCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && GenDet==%1d && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)>%f && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)<%f ", scaleF, cutB, scaleF, cutT, EpScaleF,cutEp,detID, 0.000001, 0.0004);
        sprintf(n3sigmaDCut, "E[1]*%f>%f && E[1]*%f<%f && E[0]*%f>%f && GenDet==%1d && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)>%f && ((TrigSecT[1]-TrigSecT[0])+(TrigNanoT[1]-TrigNanoT[0])*1e-9)<%f && D2First[1]<%f", scaleF, cutB, scaleF, cutT, EpScaleF,cutEp,detID, 0.000001, 0.0004, 500);
    
	new TCanvas;
        m14aEvent.Draw("E[1]>>h_Epd1(400,0,12)", n3sigmaPCut);
        float NEdp = h_Epd1->Integral(1,401);
        m14aEvent.Draw("E[1]>>h_Epd2(400,0,12)",n3sigmaTimeCut,"same");
        float NEdpt = h_Epd2->Integral(1,401);
        m14aEvent.Draw("E[1]>>h_Epd3(400,0,12)",n3sigmaDCut,"same");
        float NEdpDist = h_Epd3->Integral(1,401);

    

    cout<<"Detector Sample: "<<detSampleNum<<endl;
	cout<<" Ep Cut      : "<<NEd_p1<<endl;
    cout<<" Ep time 400   : "<<NEd_t1<<endl;
    cout<<" Ep and Ed Time 400 : "<<NEdpt<<endl;
    cout<<" Ep and Ed, Time, Dist : "<<NEdpDist<<endl;
    cout<<"---------------------------------------"<<endl;
    cout<<" [Ep/Nibd]     [Ept/Ep]      [Epdt/Ept]    [Edist/Epdt]"<<endl;
    cout<<NEd_p1/(1.0*detSampleNum)<<"\t"<<NEd_t1/(1.0*NEd_p1)<<"\t"<<NEdpt/(1.0*NEd_t1)<<"\t"<<NEdpDist/(1.0*NEdpt)<<endl;

    
    /*
     e_Ep = N(Ep>1.5) / N(IBD)
     e_t  = N(Ep>1.5; 1<deltaT<400) / N(Ep>1.5)
     e_Ed = N(Ep>1.5; 1<deltaT<400; Ed +- 3s) / N(Ep>1.5; 1<deltaT<400)
     e_d  = N(d<500mm; Ed+-3sigma; 1<dt<400; Ep>1.5) / N(Ed+-3sigma; 1<dt<400; Ep>1.5)
     */
    

}
