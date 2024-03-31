// 2015.10.20 testing
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include <TROOT.h>
#include <TFile.h>
#include <TChain.h>
#include <TMath.h>
//#include <TApplication.h>
using namespace std;

struct EventBrief {
    double sE;
    double sX,sY,sZ;
};

/// Singles pool for all ADs
map<int /* AdNo */, vector< EventBrief > > SinglesPool;

double  capTime0  = 0.000001;//s
double  capTime   = 0.0004; // s
double  multi1 = 2.0*capTime; // s
double  multi2 = 1.0*capTime; // s
double  fiducialCutZ = 3000;
double  fiducialCutR2= 9000000;
double  distFiduCutZ = 1500;
double  distFiduCutR2= 2250000;
double  distCut = 500;
double  Ehig    = 12.0;
double  Elow    = 1.5;
double  EnHdl     = 1.9039;
double  EnHdh     = 2.7095;

double  Epl	= 1.5;
double  Eph	= 12.0;
double  Edl	= 1.9;
double  Edh	= 12.0;


int main(int argc,char** argv) {


    if( argc != 3 ) {
        // ./main xxxxx.root any_xxxxx.root
        // ./main xxxxx.list any_xxxxx.root
        std::cerr << "# of arguments error." << std::endl;
        return 1;
    }

    //TFile *ifile = new TFile(argv[1]);
    //aEvent->Add(argv[1]);
    
    TChain *r_ibdTree = new TChain("IBD");
    TChain *r_sigTree = new TChain("Singles");
    
    ifstream list(argv[1]);
    string fname;
    string fileName = argv[2];
    int pol1 = fileName.find_last_of("_");
    int pol2 = fileName.find_last_of(".");
    string runNumber = fileName.substr(pol1+1,pol2-pol1-1);
    int RunNo = atoi(runNumber.c_str());
    
    while(getline(list,fname)){
        cout << fname << endl;
        r_ibdTree->Add(fname.c_str());
        r_sigTree->Add(fname.c_str());
    }
    
    TFile *ofile = new TFile(argv[2],"recreate");
    ofile->mkdir(runNumber.c_str());
    ofile->cd();
    ///
    
    TH1D* h1dCapT_IBD[5];
    //TH2D* h2dDpdVsEp[5];
    //TH2D* h2dDpdVsCapT[5];
    
    for (int AdNo=1; AdNo<5; AdNo++) {
        h1dCapT_IBD[AdNo] = new TH1D(TString::Format("h1dCapT_IBD_AD%1d",AdNo),
                                     TString::Format("h1dCapT_IBD_AD%1d",AdNo),
                                     static_cast<int>(capTime*1e6), 0, capTime*1e6);
        /*h2dDpdVsEp[AdNo] = new TH2D(TString::Format("h2dDpdVsEp_AD%1d",AdNo),
                                    TString::Format("h2dDpdVsEp_AD%1d",AdNo),
                                    120, 0, 12, 500, 0, 5000);
        h2dDpdVsCapT[AdNo] = new TH2D(TString::Format("h2dDpdVsCapT_AD%1d",AdNo),
                                      TString::Format("h2dDpdVsCapT_AD%1d",AdNo),
                                      2000, 0, capTime, 500, 0, 5000);*/
    }
    
    ofile->cd();
    ofile->cd(runNumber.c_str());
    
    TH1D* h1dDpd[5];
    TH1D* h1dEp_IBD[5];
    TH2D* h2dEpEd_IBD[5];
    TH2D* h2dVxt_IBD[5];
    
    for (int AdNo=1; AdNo<5; AdNo++) {
        h1dDpd[AdNo] = new TH1D(TString::Format("h1dDpd_%05d_AD%1d",RunNo,AdNo),
                                TString::Format("h1dDpd_%05d_AD%1d",RunNo,AdNo),
                                500, 0, 5000);
        h1dEp_IBD[AdNo]   = new TH1D(TString::Format("h1dEp_IBD_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h1dEp_IBD_%05d_AD%1d",RunNo,AdNo),
                                     120, 0, 12);
        h2dEpEd_IBD[AdNo] = new TH2D(TString::Format("h2dEpEd_IBD_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h2dEpEd_IBD_%05d_AD%1d",RunNo,AdNo),
                                     1200, 0, 12,120, 0, 12);
        h2dVxt_IBD[AdNo] = new TH2D(TString::Format("h2dVxt_IBD_%05d_AD%1d",RunNo,AdNo),
                                    TString::Format("h2dVxt_IBD_%05d_AD%1d",RunNo,AdNo),
                                    500, 0, 6500000,500, -2500, 2500);
    }
    
    ///////////////////////
    /// For IBD
    
    double ep, xp, yp, zp;
    double ed, xd, yd, zd;
    double dT, dist;
    //double multiCut1, multiCut2;
    int DetNo;
    
    r_ibdTree->SetBranchAddress( "DetNo", &DetNo);
    r_ibdTree->SetBranchAddress( "ep",    &ep   );
    r_ibdTree->SetBranchAddress( "xp",    &xp   );
    r_ibdTree->SetBranchAddress( "yp",    &yp   );
    r_ibdTree->SetBranchAddress( "zp",    &zp   );
    r_ibdTree->SetBranchAddress( "ed",    &ed   );
    r_ibdTree->SetBranchAddress( "xd",    &xd   );
    r_ibdTree->SetBranchAddress( "yd",    &yd   );
    r_ibdTree->SetBranchAddress( "zd",    &zd   );
    
    r_ibdTree->SetBranchAddress( "dT",    &dT   );
    r_ibdTree->SetBranchAddress( "dist",  &dist );
    //r_ibdTree->SetBranchAddress( "multiCut1",  &multiCut1);
    //r_ibdTree->SetBranchAddress( "multiCut2",  &multiCut2);
    
    long entries_ibdTree = r_ibdTree->GetEntries();
    cout<<entries_ibdTree<<endl;
    
    for(long ientry=0; ientry<entries_ibdTree; ientry++)
    {
        r_ibdTree->GetEntry(ientry);
        double r2= xd*xd+yd*yd;
        double z = zd;
        
        //h2dDpdVsCapT[DetNo]->Fill(dT,dist);
        //h2dDpdVsEp[DetNo]->Fill(ep,dist);


        if ( ep>Epl && ep<Eph &&
             ed>Edl && ed<Edh ) {
            h1dDpd[DetNo]->Fill(dist);
        }
        
        if ( dist>distCut) continue;
        
        if ( ep>Epl && ep<Eph &&
             ed>Edl && ed<Edh ) {
            h2dEpEd_IBD[DetNo]->Fill(ed,ep);
             h1dEp_IBD[DetNo]->Fill(ep);
             h1dCapT_IBD[DetNo]->Fill(dT*1e6);
             h2dVxt_IBD[DetNo]->Fill(r2,z);
        }
    }
    ofile->Write();
    delete r_ibdTree;
    for (int AdNo=1; AdNo<5; AdNo++) {
        delete h1dDpd[AdNo];
        delete h1dEp_IBD[AdNo];
        delete h1dCapT_IBD[AdNo];
        //delete h2dDpdVsCapT[AdNo];
        //delete h2dDpdVsEp[AdNo];
        delete h2dEpEd_IBD[AdNo];
        delete h2dVxt_IBD[AdNo];
    }
    
    ofile->Close();
    
    TFile *ofile2 = new TFile(argv[2],"UPDATE");
    ofile2->cd();
    ofile2->cd(runNumber.c_str());
    /// For Singles
    ///////////
    TH1D* h1dEs[5];
    TH1D* h1dDpd_acc[5];
    TH1D* h1dEp_acc[5];
    TH2D* h2dEpEd_acc[5];
    TH2D* h2dVxt_acc[5];
    
    for (int AdNo=1; AdNo<5; AdNo++) {
        h1dEs[AdNo] = new TH1D(TString::Format("h1dEs_%05d_AD%1d",RunNo,AdNo),
                               TString::Format("h1dEs_%05d_AD%1d",RunNo,AdNo),
                               1200, 0, 12);
        
        h1dDpd_acc[AdNo] = new TH1D(TString::Format("h1dDpd_acc_%05d_AD%1d",RunNo,AdNo),
                                    TString::Format("h1dDpd_acc_%05d_AD%1d",RunNo,AdNo),
                                    500, 0, 5000);
        h1dEp_acc[AdNo]   = new TH1D(TString::Format("h1dEp_acc_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h1dEp_acc_%05d_AD%1d",RunNo,AdNo),
                                     120, 0, 12);
        
        h2dEpEd_acc[AdNo] = new TH2D(TString::Format("h2dEpEd_acc_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h2dEpEd_acc_%05d_AD%1d",RunNo,AdNo),
                                     1200, 0, 12,120, 0, 12);
        
        h2dVxt_acc[AdNo] = new TH2D(TString::Format("h2dVxt_acc_%05d_AD%1d",RunNo,AdNo),
                                    TString::Format("h2dVxt_acc_%05d_AD%1d",RunNo,AdNo),
                                    500, 0, 6500000,500, -2500, 2500);
    }
    
    ///
    int sDetNo;
    double es, xs, ys, zs;
    //double isoCut1, isoCut2;
    
    r_sigTree->SetBranchAddress( "sDetNo", &sDetNo);
    r_sigTree->SetBranchAddress( "es",     &es );
    r_sigTree->SetBranchAddress( "xs",     &xs );
    r_sigTree->SetBranchAddress( "ys",     &ys );
    r_sigTree->SetBranchAddress( "zs",     &zs );
    
    //r_sigTree->SetBranchAddress( "isoCut1",  &isoCut1);
    //r_sigTree->SetBranchAddress( "isoCut2",  &isoCut2);
    
    int nevts = r_sigTree->GetEntries();
    int nhalf= nevts/2;
    int nquarter = nevts/4;
    cout<<nevts<<endl;
    cout<<nhalf<<endl;
    cout<<nquarter<<endl;
    for(int ientry=0; ientry<nevts; ientry++)
    {
        r_sigTree->GetEntry(ientry);
        h1dEs[sDetNo]->Fill(es);
        EventBrief pEvt;
        pEvt.sE = es;
        pEvt.sX = xs;
        pEvt.sY = ys;
        pEvt.sZ = zs;
        SinglesPool[ sDetNo ].push_back( pEvt );
    }
    
    //
    for( int AdNo=1; AdNo<=4; AdNo++ )  {
        int nEvt = SinglesPool[ AdNo ].size();
        for( int idx=0; idx<nEvt/2-1; idx++ )  {
            int prompt = idx;                       // Prompt is from the first half
            int delayed = idx+nEvt/2;               // Delayed is from the second half
            
            double dx = SinglesPool[AdNo][prompt].sX - SinglesPool[AdNo][delayed].sX;
            double dy = SinglesPool[AdNo][prompt].sY - SinglesPool[AdNo][delayed].sY;
            double dz = SinglesPool[AdNo][prompt].sZ - SinglesPool[AdNo][delayed].sZ;
            double dist_acc = sqrt( dx*dx + dy*dy + dz*dz );
            double Ep_acc = SinglesPool[AdNo][prompt].sE;
            double Ed_acc = SinglesPool[AdNo][delayed].sE;
            double r2_acc, z_acc;
           
            if ( Ep_acc>Epl && Ep_acc<Eph &&
                 Ed_acc>Edl && Ed_acc<Edh ) {
                h1dDpd_acc[AdNo]->Fill(dist_acc);
            }
            //inverse:
            if ( Ed_acc>Epl && Ed_acc<Eph &&
                 Ep_acc>Edl && Ep_acc<Edh  ){
                h1dDpd_acc[AdNo]->Fill(dist_acc);
            }
               
            if ( dist_acc>distCut) continue;
            //////////////
            if ( Ep_acc>Epl && Ep_acc<Eph &&
                 Ed_acc>Edl && Ed_acc<Edh ) {
                r2_acc = SinglesPool[AdNo][delayed].sX*SinglesPool[AdNo][delayed].sX+
                         SinglesPool[AdNo][delayed].sY*SinglesPool[AdNo][delayed].sY;
                z_acc  = SinglesPool[AdNo][delayed].sZ;
                h1dEp_acc[AdNo]->Fill( Ep_acc );
                h2dVxt_acc[AdNo] ->Fill(r2_acc,z_acc);
                h2dEpEd_acc[AdNo]->Fill( Ed_acc, Ep_acc );
            }
            
            //inverse:
            if ( Ed_acc>Epl && Ed_acc<Eph &&
                 Ep_acc>Edl && Ep_acc<Edh  ){
                r2_acc = SinglesPool[AdNo][prompt].sX*SinglesPool[AdNo][prompt].sX+
                         SinglesPool[AdNo][prompt].sY*SinglesPool[AdNo][prompt].sY;
                z_acc  = SinglesPool[AdNo][prompt].sZ;
                h1dEp_acc[AdNo]->Fill( Ed_acc );
                h2dVxt_acc[AdNo] ->Fill(r2_acc, z_acc);
                h2dEpEd_acc[AdNo]->Fill( Ep_acc, Ed_acc );
            }
        }
    }
    ////////////////////
     
    ofile2->Write();
    ofile2->Close();
     
    delete r_sigTree;
    
	return 0;
}
