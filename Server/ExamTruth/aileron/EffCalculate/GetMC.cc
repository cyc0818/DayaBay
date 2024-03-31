void GetMC()
{
	
    TH1::AddDirectory(kFALSE);
    gStyle->SetFillColor(0);


        //--------------------------------------------------------------------------------------//

        string m14aFileDir = "/dybfs2/users/beizhenhu/mywork/Simulation/forM14a/ExamTruth/aileron/Output/IbdSim/M14a/";	
	//string m14aFileDir = "/publicfs/dyb/data/userdata/beizhenhu/mywork/Physics/Sim/Analysis/forM14a/ExamTruth/aileron/Output/IbdSim/M14a/";
    char FileName[200] ;
    TChain *Event = new TChain("Event");
    
    for(int i=1; i<8;i++){
        sprintf(FileName,"ExamM14a_%d.root",i);
        ifstream ReadFile((m14aFileDir+FileName).c_str(), ios::in);
        if (ReadFile){
            Event->Add((m14aFileDir+FileName).c_str());
            cout<<FileName<<endl;
        }
        
    }
    
    //////////////////
    int Fold = 0;
    int Det = 0;
    int GenDet=0;
    
    int TrigSecT[40] = {0};
    
    double E[40] = {0};
    double X[40] = {0};
    double Y[40] = {0};
    double Z[40] = {0};
    
    double ET[40] = {0};
    double XT[40] = {0};
    double YT[40] = {0};
    double ZT[40] = {0};
    
    double D2First[40]    = {0};
    
    Event->SetBranchAddress("Fold", &Fold);
    Event->SetBranchAddress("Det",  &Det);
    Event->SetBranchAddress("GenDet",  &GenDet);
    
    Event->SetBranchAddress("TrigSecT", TrigSecT);
    Event->SetBranchAddress("E", E);
    Event->SetBranchAddress("X", X);
    Event->SetBranchAddress("Y", Y);
    Event->SetBranchAddress("Z", Z);
    
    Event->SetBranchAddress("ET", ET);
    Event->SetBranchAddress("XT", XT);
    Event->SetBranchAddress("YT", YT);
    Event->SetBranchAddress("ZT", ZT);
    
    Event->SetBranchAddress("D2First", D2First);
    
    TH1D* hEp       = new TH1D("hEp","M14A Prompt Signal",120,0,12);
    TH1D* hEp_GdLS  = new TH1D("hEp_GdLS","M14A Prompt Signal only GdLS",120,0,12);
    TH1D* hEp_LS    = new TH1D("hEp_LS","M14A Prompt Signal only GdLS",120,0,12);
    
    TH1D* hEd       = new TH1D("hEd","M14A Delayed Signal",1200,0,12);
    TH1D* hEd_GdLS  = new TH1D("hEd_GdLS","M14A Delayed Signal only GdLS",1200,0,12);
    TH1D* hEd_LS    = new TH1D("hEd_LS","M14A Delayed Signal only LS",1200,0,12);

    long Entries    = Event->GetEntries();
    for(long ientry=0; ientry<Entries; ientry++)
    {
        Event->GetEntry(ientry);
    
        if(TrigSecT>20e6)
        {
            hEp->Fill(E[0]);
            hEd->Fill(E[1]);
            
            if(GenDet==1)
            {
                hEp_GdLS->Fill(E[0]);
                hEd_GdLS->Fill(E[1]);
            }
            if(GenDet==2)
            {
                hEp_LS->Fill(E[0]);
                hEd_LS->Fill(E[1]);
            }
        }
    
    }
	TFile *file = new TFile("IBD_MC_P14A.root","recreate");
    
    hEp->Write();
    hEp_GdLS->Write();
    hEp_LS->Write();
    hEd->Write();
    hEd_GdLS->Write();
    hEd_LS->Write();
    file->Close();
    
}
