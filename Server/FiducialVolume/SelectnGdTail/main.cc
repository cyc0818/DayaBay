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

double  Epl	= 3.5;
double  Eph	= 12.0;
double  Edl	= 6.0;
double  Edh	= 7.0;


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
    }
    
    TFile *ofile = new TFile(argv[2],"recreate");
    ofile->cd();
    
    TH1D* hR[5];
    TH1D* hz[5];
    TH1D* hdt[5];
    TH1D* hEd[5];
    TH2D* hvtx[5];
    
    for (int AdNo=1; AdNo<5; AdNo++) {
        hR[AdNo] = new TH1D(TString::Format("R2_AD%1d",AdNo),TString::Format("R2_AD%1d",AdNo),400, 0, 4000000);
        hz[AdNo] = new TH1D(TString::Format("z_AD%1d",AdNo),TString::Format("z_AD%1d",AdNo),400, -2000, 2000);
        hEd[AdNo] = new TH1D(TString::Format("Ed_AD%1d",AdNo),TString::Format("Ed_AD%1d",AdNo),1200, 0, 12);
        hdt[AdNo] = new TH1D(TString::Format("dt_AD%1d",AdNo),
                             TString::Format("dt_AD%1d",AdNo),
                             2000, 0, capTime);
        hvtx[AdNo] = new TH2D(TString::Format("Vertex_AD%1d",AdNo),
                              TString::Format("Vertex_AD%1d",AdNo),
                              400, 0, 4000000,400, -2000, 2000);
    }
    
    ///////////////////////
    /// For IBD
    
    double ep, xp, yp, zp;
    double ed, xd, yd, zd;
    double dT, dist;
    double multiCut1, multiCut2;
    int DetNo, CellNop, CellNod;
    
    r_ibdTree->SetBranchAddress( "DetNo", &DetNo);
    r_ibdTree->SetBranchAddress( "ep",    &ep   );
    r_ibdTree->SetBranchAddress( "xp",    &xp   );
    r_ibdTree->SetBranchAddress( "yp",    &yp   );
    r_ibdTree->SetBranchAddress( "zp",    &zp   );
    r_ibdTree->SetBranchAddress( "CellNop", &CellNop);
    r_ibdTree->SetBranchAddress( "ed",    &ed   );
    r_ibdTree->SetBranchAddress( "xd",    &xd   );
    r_ibdTree->SetBranchAddress( "yd",    &yd   );
    r_ibdTree->SetBranchAddress( "zd",    &zd   );
    r_ibdTree->SetBranchAddress( "CellNod", &CellNod);
    
    r_ibdTree->SetBranchAddress( "dT",    &dT   );
    r_ibdTree->SetBranchAddress( "dist",  &dist );
    r_ibdTree->SetBranchAddress( "multiCut1",  &multiCut1);
    r_ibdTree->SetBranchAddress( "multiCut2",  &multiCut2);
    
    long entries_ibdTree = r_ibdTree->GetEntries();
    cout<<entries_ibdTree<<endl;
    
    for(long ientry=0; ientry<entries_ibdTree; ientry++)
    {
        r_ibdTree->GetEntry(ientry);
        if(CellNop == 100 || CellNod == 100) continue;
        double r2= xd*xd+yd*yd;
        double z = zd;
        
        if ( dist>distCut) continue;
        
        if ( ep>Epl && ep<Eph &&
             ed>=Edl && ed<=Edh ) {
             hR[DetNo]->Fill(r2);
             hz[DetNo]->Fill(z);
             hEd[DetNo]->Fill(ed);
             hdt[DetNo]->Fill(dT);
             hvtx[DetNo]->Fill(r2,z);
        }
    }
    ofile->Write();
    delete r_ibdTree;
    for (int AdNo=1; AdNo<5; AdNo++) {
        delete hR[AdNo];
        delete hz[AdNo];
        delete hEd[AdNo];
        delete hdt[AdNo];
        delete hvtx[AdNo];
    }
    
    ofile->Close();
    
    
	return 0;
}
