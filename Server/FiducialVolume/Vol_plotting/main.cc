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
    int VolNo;
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
    
    TH1D* h1dCapT_IBD[4][5];
    TH2D* h2dDpdVsEp[4][5];
    TH2D* h2dDpdVsCapT[4][5];
    
    for(int AdNo=1; AdNo<5; AdNo++){
        h1dCapT_IBD[0][AdNo] = new TH1D(TString::Format("h1dCapT_IBD_AD%1d",AdNo),
                                     TString::Format("h1dCapT_IBD_AD%1d",AdNo),
                                     2000, 0, capTime);
        h2dDpdVsEp[0][AdNo] = new TH2D(TString::Format("h2dDpdVsEp_AD%1d",AdNo),
                                    TString::Format("h2dDpdVsEp_AD%1d",AdNo),
                                    120, 0, 12, 500, 0, 5000);
        h2dDpdVsCapT[0][AdNo] = new TH2D(TString::Format("h2dDpdVsCapT_AD%1d",AdNo),
                                      TString::Format("h2dDpdVsCapT_AD%1d",AdNo),
                                      2000, 0, capTime, 500, 0, 5000);
    }
    

    TH1D* h1dDpd[4][5];
    TH1D* h1dEp_IBD[4][5];
    TH2D* h2dEpEd_IBD[4][5];
    TH2D* h2dVxt_IBD[4][5];


    ofile->cd(runNumber.c_str());
    

    for(int AdNo=1; AdNo<5; AdNo++){
        h1dDpd[0][AdNo] = new TH1D(TString::Format("h1dDpd_%05d_AD%1d",RunNo,AdNo),
                                TString::Format("h1dDpd_%05d_AD%1d",RunNo,AdNo),
                                500, 0, 5000);
        h1dEp_IBD[0][AdNo]   = new TH1D(TString::Format("h1dEp_IBD_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h1dEp_IBD_%05d_AD%1d",RunNo,AdNo),
                                     120, 0, 12);
        h2dEpEd_IBD[0][AdNo] = new TH2D(TString::Format("h2dEpEd_IBD_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h2dEpEd_IBD_%05d_AD%1d",RunNo,AdNo),
                                     1200, 0, 12,120, 0, 12);
        h2dVxt_IBD[0][AdNo] = new TH2D(TString::Format("h2dVxt_IBD_%05d_AD%1d",RunNo,AdNo),
                                    TString::Format("h2dVxt_IBD_%05d_AD%1d",RunNo,AdNo),
                                    500, 0, 6500000,500, -2500, 2500);
    }


    for(int cell = 1; cell<4; cell++){

        ofile->cd();


        for(int AdNo=1; AdNo<5; AdNo++){
            h1dCapT_IBD[cell][AdNo] = new TH1D(TString::Format("h1dCapT_IBD_AD%1d_Vol%d",AdNo,cell),
                                               TString::Format("h1dCapT_IBD_AD%1d_Vol%d",AdNo,cell),
                                               2000, 0, capTime);
            h2dDpdVsEp[cell][AdNo] = new TH2D(TString::Format("h2dDpdVsEp_AD%1d_Vol%d",AdNo,cell),
                                              TString::Format("h2dDpdVsEp_AD%1d_Vol%d",AdNo,cell),
                                              120, 0, 12, 500, 0, 5000);
            h2dDpdVsCapT[cell][AdNo] = new TH2D(TString::Format("h2dDpdVsCapT_AD%1d_Vol%d",AdNo,cell),
                                                TString::Format("h2dDpdVsCapT_AD%1d_Vol%d",AdNo,cell),
                                                2000, 0, capTime, 500, 0, 5000);
        }


        ofile->cd();
        ofile->mkdir(TString::Format("%d",RunNo));
        ofile->cd(TString::Format("%d",RunNo));


        for(int AdNo=1; AdNo<5; AdNo++){
            h1dDpd[cell][AdNo] = new TH1D(TString::Format("h1dDpd_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                          TString::Format("h1dDpd_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                          500, 0, 5000);
            h1dEp_IBD[cell][AdNo] = new TH1D(TString::Format("h1dEp_IBD_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                             TString::Format("h1dEp_IBD_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                             120, 0, 12);
            h2dEpEd_IBD[cell][AdNo] = new TH2D(TString::Format("h2dEpEd_IBD_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                               TString::Format("h2dEpEd_IBD_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                               1200, 0, 12,120, 0, 12);
            h2dVxt_IBD[cell][AdNo] = new TH2D(TString::Format("h2dVxt_IBD_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                              TString::Format("h2dVxt_IBD_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                              500, 0, 6500000,500, -2500, 2500);
        }

    }
    ofile->cd();

    
    ///////////////////////
    /// For IBD
    
    double ep, xp, yp, zp;
    double ed, xd, yd, zd;
    double dT, dist;
    int DetNo, CellNop, CellNod;
    int VolNop, VolNod;
    
    r_ibdTree->SetBranchAddress( "DetNo", &DetNo);
    r_ibdTree->SetBranchAddress( "ep",    &ep   );
    r_ibdTree->SetBranchAddress( "xp",    &xp   );
    r_ibdTree->SetBranchAddress( "yp",    &yp   );
    r_ibdTree->SetBranchAddress( "zp",    &zp   );
    r_ibdTree->SetBranchAddress( "CellNop", &CellNop);
    r_ibdTree->SetBranchAddress( "VolNop", &VolNop);
    r_ibdTree->SetBranchAddress( "ed",    &ed   );
    r_ibdTree->SetBranchAddress( "xd",    &xd   );
    r_ibdTree->SetBranchAddress( "yd",    &yd   );
    r_ibdTree->SetBranchAddress( "zd",    &zd   );
    r_ibdTree->SetBranchAddress( "CellNod", &CellNod);
    r_ibdTree->SetBranchAddress( "VolNod", &VolNod);
    
    r_ibdTree->SetBranchAddress( "dT",    &dT   );
    r_ibdTree->SetBranchAddress( "dist",  &dist );
    
    long entries_ibdTree = r_ibdTree->GetEntries();
    cout<<entries_ibdTree<<endl;
    
    for(long ientry=0; ientry<entries_ibdTree; ientry++)
    {
        r_ibdTree->GetEntry(ientry);
        if(CellNop == 100 || CellNod == 100) continue;
        if(VolNop == 0 || VolNod == 0) continue;
        double r2= xd*xd+yd*yd;
        double z = zd;
        
        h1dDpd[0][DetNo]->Fill(dist);
        h2dDpdVsCapT[0][DetNo]->Fill(dT,dist);
        h2dDpdVsEp[0][DetNo]->Fill(ep,dist);


        h1dDpd[VolNod][DetNo]->Fill(dist);
        h2dDpdVsCapT[VolNod][DetNo]->Fill(dT,dist);
        h2dDpdVsEp[VolNod][DetNo]->Fill(ep,dist);
        

        if ( dist>distCut) continue;
        h2dEpEd_IBD[0][DetNo]->Fill(ed,ep);
        h2dEpEd_IBD[VolNod][DetNo]->Fill(ed,ep);
        
        if ( ep>Epl && ep<Eph &&
             ed>Edl && ed<Edh ) {
             h1dEp_IBD[0][DetNo]->Fill(ep);
             h1dCapT_IBD[0][DetNo]->Fill(dT);
             h2dVxt_IBD[0][DetNo]->Fill(r2,z);


             h1dEp_IBD[VolNod][DetNo]->Fill(ep);
             h1dCapT_IBD[VolNod][DetNo]->Fill(dT);
             h2dVxt_IBD[VolNod][DetNo]->Fill(r2,z);
        }
    }
    ofile->Write();
    delete r_ibdTree;
    for(int cell=0; cell<4; cell++){
        for(int AdNo=1; AdNo<5; AdNo++){
            delete h1dDpd[cell][AdNo];
            delete h1dEp_IBD[cell][AdNo];
            delete h1dCapT_IBD[cell][AdNo];
            delete h2dDpdVsCapT[cell][AdNo];
            delete h2dDpdVsEp[cell][AdNo];
            delete h2dEpEd_IBD[cell][AdNo];
            delete h2dVxt_IBD[cell][AdNo];
        }
    }
    
    ofile->Close();
    
    TFile *ofile2 = new TFile(argv[2],"UPDATE");
    ofile2->cd();
    ofile2->cd(runNumber.c_str());
    /// For Singles
    ///////////
    TH1D* h1dEs[4][5];
    TH1D* h1dDpd_acc[4][5];
    TH1D* h1dEp_acc[4][5];
    TH2D* h2dEpEd_acc[4][5];
    TH2D* h2dVxt_acc[4][5];
    
    for(int AdNo=1; AdNo<5; AdNo++){
        h1dEs[0][AdNo] = new TH1D(TString::Format("h1dEs_%05d_AD%1d",RunNo,AdNo),
                               TString::Format("h1dEs_%05d_AD%1d",RunNo,AdNo),
                               1200, 0, 12);
        
        h1dDpd_acc[0][AdNo] = new TH1D(TString::Format("h1dDpd_acc_%05d_AD%1d",RunNo,AdNo),
                                    TString::Format("h1dDpd_acc_%05d_AD%1d",RunNo,AdNo),
                                    500, 0, 5000);

        h1dEp_acc[0][AdNo] = new TH1D(TString::Format("h1dEp_acc_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h1dEp_acc_%05d_AD%1d",RunNo,AdNo),
                                     120, 0, 12);
        
        h2dEpEd_acc[0][AdNo] = new TH2D(TString::Format("h2dEpEd_acc_%05d_AD%1d",RunNo,AdNo),
                                     TString::Format("h2dEpEd_acc_%05d_AD%1d",RunNo,AdNo),
                                     1200, 0, 12,120, 0, 12);
        
        h2dVxt_acc[0][AdNo] = new TH2D(TString::Format("h2dVxt_acc_%05d_AD%1d",RunNo,AdNo),
                                    TString::Format("h2dVxt_acc_%05d_AD%1d",RunNo,AdNo),
                                    500, 0, 6500000,500, -2500, 2500);
    }


    for(int cell = 1; cell<4; cell++){

        ofile2->cd(TString::Format("%d",RunNo));


        for(int AdNo=1; AdNo<5; AdNo++){
            h1dEs[cell][AdNo] = new TH1D(TString::Format("h1dEs_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                         TString::Format("h1dEs_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                         1200, 0, 12);
        
            h1dDpd_acc[cell][AdNo] = new TH1D(TString::Format("h1dDpd_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                              TString::Format("h1dDpd_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                              500, 0, 5000);
            
            h1dEp_acc[cell][AdNo] = new TH1D(TString::Format("h1dEp_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                             TString::Format("h1dEp_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                             120, 0, 12);
        
            h2dEpEd_acc[cell][AdNo] = new TH2D(TString::Format("h2dEpEd_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                               TString::Format("h2dEpEd_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                               1200, 0, 12,120, 0, 12);
        
            h2dVxt_acc[cell][AdNo] = new TH2D(TString::Format("h2dVxt_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                              TString::Format("h2dVxt_acc_%05d_AD%1d_Vol%d",RunNo,AdNo,cell),
                                              500, 0, 6500000,500, -2500, 2500);
        }
    }


    
    ///
    int sDetNo, CellNos, VolNos;
    double es, xs, ys, zs;
    
    r_sigTree->SetBranchAddress( "sDetNo", &sDetNo);
    r_sigTree->SetBranchAddress( "es",     &es );
    r_sigTree->SetBranchAddress( "xs",     &xs );
    r_sigTree->SetBranchAddress( "ys",     &ys );
    r_sigTree->SetBranchAddress( "zs",     &zs );
    r_sigTree->SetBranchAddress( "CellNos", &CellNos);
    r_sigTree->SetBranchAddress( "VolNos", &VolNos);
    

    int nevts = r_sigTree->GetEntries();
    int nhalf= nevts/2;
    int nquarter = nevts/4;
    cout<<nevts<<endl;
    cout<<nhalf<<endl;
    cout<<nquarter<<endl;
    for(int ientry=0; ientry<nevts; ientry++)
    {
        r_sigTree->GetEntry(ientry);
        if(CellNos == 100) continue;
        if(VolNos == 0) continue;
        h1dEs[100][sDetNo]->Fill(es);
        h1dEs[VolNos][sDetNo]->Fill(es);
        EventBrief pEvt;
        pEvt.sE = es;
        pEvt.sX = xs;
        pEvt.sY = ys;
        pEvt.sZ = zs;
        pEvt.VolNo = VolNos;
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
            int VolNo_fp = SinglesPool[AdNo][prompt].VolNo;   // fp : fake prompt
            int VolNo_fd = SinglesPool[AdNo][delayed].VolNo;   // fd : fake delayed
           

            if ( Ed_acc>Edl && Ed_acc<Edh ){
                h1dDpd_acc[0][AdNo]->Fill(dist_acc);
                h1dDpd_acc[VolNo_fd][AdNo]->Fill(dist_acc);
            }


            //inverse:
            if ( Ep_acc>Edl && Ep_acc<Edh ){
                h1dDpd_acc[0][AdNo]->Fill(dist_acc);
                h1dDpd_acc[VolNo_fp][AdNo]->Fill(dist_acc);
            }
               

            if ( dist_acc>distCut) continue;


            if ( Ed_acc>Edl && Ed_acc<Edh ){
                h2dEpEd_acc[0][AdNo]->Fill( Ed_acc, Ep_acc );
                h2dEpEd_acc[VolNo_fd][AdNo]->Fill( Ed_acc, Ep_acc );
            }


            //inverse:
            if ( Ep_acc>Edl && Ep_acc<Edh ){
                h2dEpEd_acc[0][AdNo]->Fill( Ep_acc, Ed_acc );
                h2dEpEd_acc[VolNo_fp][AdNo]->Fill( Ep_acc, Ed_acc );
            }


            if ( Ep_acc>Epl && Ep_acc<Eph &&
                 Ed_acc>Edl && Ed_acc<Edh ){
                    r2_acc = SinglesPool[AdNo][delayed].sX*SinglesPool[AdNo][delayed].sX+
                             SinglesPool[AdNo][delayed].sY*SinglesPool[AdNo][delayed].sY;
                    z_acc  = SinglesPool[AdNo][delayed].sZ;

                    h1dEp_acc[0][AdNo]->Fill( Ep_acc );
                    h2dVxt_acc[0][AdNo] ->Fill(r2_acc,z_acc);

                    h1dEp_acc[VolNo_fd][AdNo]->Fill( Ep_acc );
                    h2dVxt_acc[VolNo_fd][AdNo] ->Fill(r2_acc,z_acc);
            }
            
            //inverse:
            if ( Ed_acc>Epl && Ed_acc<Eph &&
                 Ep_acc>Edl && Ep_acc<Edh  ){
                    r2_acc = SinglesPool[AdNo][prompt].sX*SinglesPool[AdNo][prompt].sX+
                             SinglesPool[AdNo][prompt].sY*SinglesPool[AdNo][prompt].sY;
                    z_acc  = SinglesPool[AdNo][prompt].sZ;

                    h1dEp_acc[0][AdNo]->Fill( Ed_acc );
                    h2dVxt_acc[0][AdNo] ->Fill(r2_acc, z_acc);

                    h1dEp_acc[VolNo_fp][AdNo]->Fill( Ed_acc );
                    h2dVxt_acc[VolNo_fp][AdNo] ->Fill(r2_acc, z_acc);
            }
        }
    }
    ////////////////////
     
    ofile2->Write();
    ofile2->Close();
     
    delete r_sigTree;
    
	return 0;
}
