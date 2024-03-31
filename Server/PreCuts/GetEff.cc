
#include <iomanip>
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


void GetEff()
{
    char FileName[200];

    TMultiGraph *mg1 = new TMultiGraph();
    TMultiGraph *mg2 = new TMultiGraph();
    
    TGraphErrors *muVetoEff[9];
    TGraphErrors *muRate[9];
    
    for(int i=0; i<9; i++) {
        muVetoEff[i] = new TGraphErrors();
        muRate[i] = new TGraphErrors();
    }
    TLegend* leg1 = new TLegend(0.75,0.7,0.92,0.4);
    
    int nPoints[9] = {0};
    int gAdNo = 0;
    
    double totalFullT[9] = {0};
    double totalLiveT[9] = {0};
    double muonvetoEff[9]= {0};

    for (int nSite=1; nSite<4; nSite++) {
        ofstream opt1;
        opt1.open(TString::Format("RunInfo_EH%1d.txt",nSite));
        
        opt1<<"[RunNo]\t[DetNo]\t[Date]\t[Full Time]\t[Live Time]\t[VetoEff]\t[AdMu]\t[ShMu]\t[WpMu]\t[NetMu]\t[muRate]"<<endl;
        for(int RunNo=20000; RunNo<80000;RunNo++)
        {
            sprintf(FileName, "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/EH%d/PreCuts/PreCut_%5d.root",nSite,RunNo);
            ifstream ReadFile(FileName);
            
            if (ReadFile) {
                TChain *aEvent = new TChain("Event");
                aEvent->Add(FileName);
                
                //////////////////////
                const int max = 200;
                ///
                int     Run = 0;
                int     Det = 0;
                int     TrigSec = 0;
                int     TrigNano= 0;
                int     AdMu = 0;
                int     ShMu = 0;
                int     WpMu = 0;
                int     NetMu = 0;
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
                aEvent->SetBranchAddress("NetMu",       &NetMu);
                
                aEvent->SetBranchAddress("TrigSec",    &TrigSec     );
                aEvent->SetBranchAddress("TrigNano",   &TrigNano    );
                aEvent->SetBranchAddress("T2PrevPlMu", &T2PrevPlMu);
                aEvent->SetBranchAddress("T2PrevAdMu", &T2PrevAdMu);
                aEvent->SetBranchAddress("T2PrevShMu", &T2PrevShMu);
                aEvent->SetBranchAddress("LiveTime",   &LiveTime);
                aEvent->SetBranchAddress("FullTime",   &FullTime);
                // ############################
                
                int nevent = aEvent->GetEntries();
                cout<<RunNo<<" "<<nevent<<endl;
                int finalEvtNo = nevent-1;
                
                for( int jentry = finalEvtNo-50; jentry < nevent; jentry++ ){
                    aEvent->GetEntry(jentry);
                    
                    if (Fold==-1 && AdMu!=0) {
                        opt1<<RunNo<<"\t"<<Det<<"\t"<<TrigSec<<"\t"<<FullTime<<"\t"<<LiveTime<<"\t"<<LiveTime/FullTime<<"\t"<<AdMu<<"\t"<<ShMu<<"\t"<<WpMu<<"\t"<<NetMu<<"\t"<<NetMu/LiveTime<<endl;
                        
                        if (nSite == 1) gAdNo = Det;
                        if (nSite == 2) gAdNo = 2+Det;
                        if (nSite == 3) gAdNo = 4+Det;
                        
                        totalLiveT[gAdNo] += LiveTime;
                        totalFullT[gAdNo] += FullTime;

                        
                        muVetoEff[gAdNo] -> SetPoint(nPoints[gAdNo],TrigSec, LiveTime/FullTime);
                        muVetoEff[gAdNo] -> SetPointError(nPoints[gAdNo],0, 0);
                        muVetoEff[gAdNo] -> SetMarkerStyle(gAdNo+20);
                        muVetoEff[gAdNo] -> SetMarkerColor(Det);
                        muVetoEff[gAdNo] -> SetLineColor(Det);
                        mg1 ->Add(muVetoEff[gAdNo]);

                        ///
                        muRate[gAdNo] -> SetPoint(nPoints[gAdNo],TrigSec, NetMu/LiveTime );
                        muRate[gAdNo] -> SetPointError(nPoints[gAdNo],0, sqrt(NetMu)/LiveTime);
                        muRate[gAdNo] -> SetMarkerStyle(gAdNo+20);
                        muRate[gAdNo] -> SetMarkerColor(Det);
                        muRate[gAdNo] -> SetLineColor(Det);
                        mg2 ->Add(muRate[gAdNo]);
                        
                        if (nPoints[gAdNo]==1)  leg1->AddEntry(muVetoEff[gAdNo],TString::Format("AD%1d",gAdNo),"lep");
                        
                        
                        nPoints[gAdNo]++;
                    }
                }
                
                delete aEvent;
            }
            
        } // end of runNo loop
    
        //delete opt1;
    }
    
    ofstream opt2;
    opt2.open(TString::Format("RunInfoTable2.txt"));
    opt2<<"[Det]\t[FullTime]\t[LiveTime]\t[MuVetoEff]\t"<<endl;
    for (int n=1; n<=8; n++) {
        muonvetoEff[n] = (1.0*totalLiveT[n])/totalFullT[n];
        opt2<<n<<"\t"<<setiosflags(ios::fixed) << setprecision(4)<<totalFullT[n]/(24.0*60.0*60.0)<<"\t"<<totalLiveT[n]/(24.0*60.0*60.0)<<"\t"<<muonvetoEff[n]<<endl;
    }
    
    
    TCanvas *c1 = new TCanvas(TString::Format("c1"),TString::Format("c1"),800,600);
    mg1->Draw("AP");
    mg1->GetXaxis()->SetTimeDisplay(1);
    mg1->GetXaxis()->SetTimeFormat("%b-%d");
    mg1->GetXaxis()->SetNdivisions(507);
    mg1->GetYaxis()->SetTitle("Muon Veto Eff.");
    mg1->GetXaxis()->SetTitle("Date");
    mg1->GetYaxis()->SetTitleOffset(1.0);
    leg1->Draw();
    c1->Print("muEff.root");
    
    TCanvas *c2 = new TCanvas(TString::Format("c2"),TString::Format("c2"),800,600);
    mg2->Draw("AP");
    mg2->GetXaxis()->SetTimeDisplay(1);
    mg2->GetXaxis()->SetTimeFormat("%b-%d");
    mg2->GetXaxis()->SetNdivisions(507);
    mg2->GetYaxis()->SetTitle("Muon Rate [Hz]");
    mg2->GetXaxis()->SetTitle("Date");
    mg2->GetYaxis()->SetTitleOffset(1.0);
    leg1->Draw();
    c2->Print("muRate.root");
    
	//return 0;
}
