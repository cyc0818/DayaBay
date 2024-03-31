// This code is for checking with nGd selection.
// IBD candidates and singles selection save to tree
// for IBD:
// 1. Energy cuts: 0.7<Ep<12 ; 6<Ed<12 (MeV)
// 2. Capture time: 0.000001<Tc<0.0002 (s)
// 3. Distance Cut: NO
// 4. Multiplicity Cuts: BCW's DMC
// -----By Bei-Zhen Hu  2016.02
//
#include <iostream>
#include <fstream>
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
    double dT, sT2Mu;
    double sDist;
    int    sTrig_s, sTrig_ns;
    int    sTrigNo;
};

/// Singles pool for all ADs
map<int /* AdNo */, vector< EventBrief > > SinglesPool;

/// previous evt
map<int /* AdNo */, vector< EventBrief > > PrevEvt;


int GetCellNo(EventBrief evt);


double  isolation = 0.0001; // s
double  capTime   = 0.0004; // s
double  be4DelayCut= 2.0*capTime;
double  aftDelayCut= 1.0*capTime;
double  Ep1 = 1.5;
double  Ep2 = 12;
double  Ed1 = 1.9;
double  Ed2 = 12;
int main(int argc,char** argv) {


    if( argc != 3 ) {
        // ./main xxxxx.root any_xxxxx.root
        // ./main xxxxx.list any_xxxxx.root
        std::cerr << "# of arguments error." << std::endl;
        return 1;
    }

    //TFile *ifile = new TFile(argv[1]);
    //aEvent->Add(argv[1]);
    
    TChain *aEvent = new TChain("Event");
    ifstream list(argv[1]);
    string fname;
    
    while(getline(list,fname)){
        cout << fname << endl;
        aEvent->Add(fname.c_str());
    }
    
    //////////////////////
    const int max = 200;
    ///
    int     Det = 0;
    int     TrigSec = 0;
    int     TrigNano= 0;
    int     TrigNo = 0;
    int     AdMu = 0;
    int     ShMu = 0;
    int     WpMu = 0;
    int     Fold = 0;
    
    double  E = 0;
    double  X = 0;
    double  Y = 0;
    double  Z = 0;
    
    double  T2PrevPlMu = 0;
    double  T2PrevAdMu = 0;
    double  T2PrevShMu = 0;
    double  LiveTime = 0;
    double  FullTime = 0;
    
    
    aEvent->SetBranchAddress("Det",        &Det);

    aEvent->SetBranchAddress("E",          &E);
    aEvent->SetBranchAddress("X",          &X);
    aEvent->SetBranchAddress("Y",          &Y);
    aEvent->SetBranchAddress("Z",          &Z);
    aEvent->SetBranchAddress("Fold",       &Fold);
    aEvent->SetBranchAddress("AdMu",       &AdMu);
    aEvent->SetBranchAddress("ShMu",       &ShMu);
    aEvent->SetBranchAddress("WpMu",       &WpMu);
    
    aEvent->SetBranchAddress("TrigSec",    &TrigSec     );
    aEvent->SetBranchAddress("TrigNano",   &TrigNano    );
    aEvent->SetBranchAddress("TrigNo",     &TrigNo    );
    aEvent->SetBranchAddress("T2PrevPlMu", &T2PrevPlMu);
    aEvent->SetBranchAddress("T2PrevAdMu", &T2PrevAdMu);
    aEvent->SetBranchAddress("T2PrevShMu", &T2PrevShMu);
    aEvent->SetBranchAddress("LiveTime",   &LiveTime);
    aEvent->SetBranchAddress("FullTime",   &FullTime);
    // ############################
    
    TFile *ofile = new TFile(argv[2],"recreate");
    TTree *m_ibdTree = new TTree("IBD","IBD Tree");    /// create tree
    TTree *m_sigTree = new TTree("Singles","Singles Tree");    /// create tree
    
    /// For IBD
    double ep, xp, yp, zp;
    double ed, xd, yd, zd;
    double dT, dist;
    double multiCut1, multiCut2;
    int DetNo, trigNp, trigNd;
    int CellNop, CellNod;
    
    m_ibdTree->Branch( "DetNo", &DetNo,  "DetNo/I");
    m_ibdTree->Branch( "ep",    &ep,     "ep/D" );
    m_ibdTree->Branch( "xp",    &xp,     "xp/D" );
    m_ibdTree->Branch( "yp",    &yp,     "yp/D" );
    m_ibdTree->Branch( "zp",    &zp,     "zp/D" );
    m_ibdTree->Branch( "trigNp",    &trigNp,     "trigNp/I" );
    m_ibdTree->Branch( "ed",    &ed,     "ed/D" );
    m_ibdTree->Branch( "xd",    &xd,     "xd/D" );
    m_ibdTree->Branch( "yd",    &yd,     "yd/D" );
    m_ibdTree->Branch( "zd",    &zd,     "zd/D" );
    m_ibdTree->Branch( "trigNd",    &trigNd,     "trigNd/I" );
    m_ibdTree->Branch( "CellNo",    &CellNod,     "CellNo/I" );
    
    m_ibdTree->Branch( "dT",    &dT,     "dT/D"  );
    m_ibdTree->Branch( "dist",  &dist,   "dist/D");
    m_ibdTree->Branch( "multiCut1",  &multiCut1,   "multiCut1/D");
    m_ibdTree->Branch( "multiCut2",  &multiCut2,   "multiCut2/D");

    /// For Singles
    int sDetNo, trigNs;
    double es, xs, ys, zs;
    double isoCut1, isoCut2;
    
    m_sigTree->Branch( "sDetNo", &sDetNo,  "sDetNo/I");
    m_sigTree->Branch( "trigNs",    &trigNs,     "trigNs/I" );
    m_sigTree->Branch( "es",    &es,     "es/D" );
    m_sigTree->Branch( "xs",    &xs,     "xs/D" );
    m_sigTree->Branch( "ys",    &ys,     "ys/D" );
    m_sigTree->Branch( "zs",    &zs,     "zs/D" );
    m_sigTree->Branch( "CellNo",    &CellNop,     "CellNo/I" );

    m_sigTree->Branch( "isoCut1",  &isoCut1,   "isoCut1/D");
    m_sigTree->Branch( "isoCut2",  &isoCut2,   "isoCut2/D");
    

    ///
    int nevent = aEvent->GetEntries();
    cout<<nevent<<endl;
    aEvent->GetEntry(nevent-1);
    double FullT = FullTime;
    int AdMuNum = AdMu;
    int ShMuNum = ShMu;
    int WpMuNum = WpMu;

    cout<<" Full Time: "<<FullT<<" Ad muon number: "<<AdMuNum<<" shower muon number: "<<ShMuNum<<" WP muon number: "<<WpMuNum<<endl;
    for( int jentry = 0; jentry < nevent; jentry++ ) {
        aEvent->GetEntry(jentry);
        
        //if (E<0.7 || E>12.0) continue;
        
        int nEvt = PrevEvt[ Det ].size();
        //cout<<"nEvt: "<<nEvt<<endl;
        if (nEvt==4) {
            bool   CandiPassDMC = true;
            bool   SinglPassDMC = true;
            bool   ibdPromptLiked  = false;
            bool   ibdDelayedLiked = false;
            bool   ibdPLikeS  = false;
            bool   ibdDLikeS = false;
            bool   PinGdLS = false;
            bool   DinGdLS = false;
            
	    double tB4Ed_s  = PrevEvt[ Det ][2].sTrig_s - PrevEvt[ Det ][0].sTrig_s;
            double tB4Ed_ns = PrevEvt[ Det ][2].sTrig_ns - PrevEvt[ Det ][0].sTrig_ns;
            double tB4Ed    = tB4Ed_s + tB4Ed_ns*1e-9;
            
            double tAfEd_s  = PrevEvt[ Det ][3].sTrig_s - PrevEvt[ Det ][2].sTrig_s;
            double tAfEd_ns = PrevEvt[ Det ][3].sTrig_ns - PrevEvt[ Det ][2].sTrig_ns;
            double tAfEd    = tAfEd_s + tAfEd_ns*1e-9;
            
            double tBWpd_s  = PrevEvt[ Det ][2].sTrig_s - PrevEvt[ Det ][1].sTrig_s;
            double tBWpd_ns = PrevEvt[ Det ][2].sTrig_ns - PrevEvt[ Det ][1].sTrig_ns;
            double tBWpd    = tBWpd_s + tBWpd_ns*1e-9;
            
            double dVxt = sqrt( (PrevEvt[ Det ][2].sX-PrevEvt[ Det ][1].sX)*(PrevEvt[ Det ][2].sX-PrevEvt[ Det ][1].sX)
                               +(PrevEvt[ Det ][2].sY-PrevEvt[ Det ][1].sY)*(PrevEvt[ Det ][2].sY-PrevEvt[ Det ][1].sY)
                               +(PrevEvt[ Det ][2].sZ-PrevEvt[ Det ][1].sZ)*(PrevEvt[ Det ][2].sZ-PrevEvt[ Det ][1].sZ));
            
            double Eprompt = PrevEvt[ Det ][1].sE;
            double Edelay  = PrevEvt[ Det ][2].sE;
            double preEp   = PrevEvt[ Det ][0].sE;
            double aftEd   = PrevEvt[ Det ][3].sE;


            CellNop = GetCellNo(PrevEvt[ Det ][1]);
            CellNod = GetCellNo(PrevEvt[ Det ][2]);


            if( (PrevEvt[ Det ][1].sX*PrevEvt[ Det ][1].sX+PrevEvt[ Det ][1].sY*PrevEvt[ Det ][1].sY) < 1540*1540
                    && PrevEvt[ Det ][1].sZ < 1554 && PrevEvt[ Det ][1].sZ > -1554) PinGdLS = true;
            if( (PrevEvt[ Det ][2].sX*PrevEvt[ Det ][2].sX+PrevEvt[ Det ][2].sY*PrevEvt[ Det ][2].sY) < 1540*1540
                    && PrevEvt[ Det ][2].sZ < 1554 && PrevEvt[ Det ][2].sZ > -1554) DinGdLS = true;
	    if ( preEp>Ep1 && preEp<Ep2 ) ibdPromptLiked  = true;
	    if ( aftEd>Ed1 && aftEd<Ed2 ) ibdDelayedLiked = true; 
            if ( (tB4Ed < be4DelayCut && ibdPromptLiked )||
                 (tAfEd < aftDelayCut && ibdDelayedLiked) )    CandiPassDMC = false;
 
            //if ( (tB4Ed < be4DelayCut )|| (tAfEd < aftDelayCut) )    CandiPassDMC = false;

            if (Eprompt>Ep1 && Eprompt<Ep2 &&
                Edelay> Ed1 && Edelay<Ed2   &&
                tBWpd>0.000001 && tBWpd< capTime &&
                CandiPassDMC   &&
                dVxt < 5000 && CellNop==CellNod && CellNod<100
                ) {
                
                    //cout<<Det<<" ------IBD testing----"<<endl;
                
                    DetNo = Det;
                    multiCut1 = tB4Ed;
                    multiCut2 = tAfEd;
                    dT = tBWpd;
                    dist = dVxt;
                
                    ep = PrevEvt[ Det ][1].sE;
                    xp = PrevEvt[ Det ][1].sX;
                    yp = PrevEvt[ Det ][1].sY;
                    zp = PrevEvt[ Det ][1].sZ;
                    trigNp = PrevEvt[ Det ][1].sTrigNo;
                

                    ed = PrevEvt[ Det ][2].sE;
                    xd = PrevEvt[ Det ][2].sX;
                    yd = PrevEvt[ Det ][2].sY;
                    zd = PrevEvt[ Det ][2].sZ;
                    trigNd = PrevEvt[ Det ][2].sTrigNo;
                
                    m_ibdTree->Fill();
                
                    vector<EventBrief>::iterator k0 =  PrevEvt[ Det ].begin();
                    PrevEvt[ Det ].erase(k0);
                    PrevEvt[ Det ].erase(k0);
                
            }else{
                
                double tB4Es_s  = PrevEvt[ Det ][1].sTrig_s - PrevEvt[ Det ][0].sTrig_s;
                double tB4Es_ns = PrevEvt[ Det ][1].sTrig_ns - PrevEvt[ Det ][0].sTrig_ns;
                double tB4Es    = tB4Es_s + tB4Es_ns*1e-9;
                
                double tAfEs_s  = PrevEvt[ Det ][2].sTrig_s - PrevEvt[ Det ][1].sTrig_s;
                double tAfEs_ns = PrevEvt[ Det ][2].sTrig_ns - PrevEvt[ Det ][1].sTrig_ns;
                double tAfEs    = tAfEs_s + tAfEs_ns*1e-9;
                
                double Esingles = PrevEvt[ Det ][1].sE;
                double preEs   = PrevEvt[ Det ][0].sE;
                double aftEs   = PrevEvt[ Det ][2].sE;
                bool SinGdLS = false;
               
            	if ( preEs>Ep1 && preEs<Ep2 ) ibdPLikeS  = true;
            	if ( aftEs>Ed1 && aftEs<Ed2 ) ibdDLikeS = true;
                if( (PrevEvt[ Det ][1].sX*PrevEvt[ Det ][1].sX+PrevEvt[ Det ][1].sY*PrevEvt[ Det ][1].sY) < 1540*1540
                    && PrevEvt[ Det ][1].sZ < 1554 && PrevEvt[ Det ][1].sZ > -1554) SinGdLS = true;
 
                if ( (tB4Es < be4DelayCut && ibdPLikeS )||
                     (tAfEs < aftDelayCut && ibdDLikeS ) )    SinglPassDMC = false;
                //if ( (tB4Es < be4DelayCut )||
                //     (tAfEs < aftDelayCut ) )    SinglPassDMC = false;
                
                if ( Esingles>Ep1 && Esingles<Ep2 && SinglPassDMC && CellNop<100) {
                    
                    sDetNo = Det;
                    isoCut1 = tB4Es;
                    isoCut2 = tAfEs;
                    
                    es = PrevEvt[ Det ][1].sE;
                    xs = PrevEvt[ Det ][1].sX;
                    ys = PrevEvt[ Det ][1].sY;
                    zs = PrevEvt[ Det ][1].sZ;
                    trigNs = PrevEvt[ Det ][1].sTrigNo;
                        
                    m_sigTree->Fill();
                }
                vector<EventBrief>::iterator k =  PrevEvt[ Det ].begin();
                PrevEvt[ Det ].erase(k);
                
            }
            
        }
        
        EventBrief preEvt;
        preEvt.sE = E;
        preEvt.sX = X;
        preEvt.sY = Y;
        preEvt.sZ = Z;
        preEvt.sTrig_s  = TrigSec;
        preEvt.sTrig_ns = TrigNano;
        preEvt.sTrigNo  = TrigNo;
        PrevEvt[ Det ].push_back( preEvt );

        
    } // end of event loop
    
    ///
    m_ibdTree->Write();
    m_sigTree->Write();
    ofile->Close();
    
	return 0;
}





int GetCellNo(EventBrief evt){

    int CellNo = 100;
    int a = 0;      // for R^2
    int b = 0;      // for z, (10a + b)


    double Rsq = 0;
    double z = 0;


    Rsq = evt.sX*evt.sX + evt.sY*evt.sY;
    z = evt.sZ + 2000;


    a = (int)(Rsq/400000);
    b = (int)(z/400);


    if(a>=0 && a<=9 && b>=0 && b<=9) CellNo = 10*a + b;



    return CellNo;



}




