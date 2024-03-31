// preCut for candidates
// 1. flashers cuts
// 2. muon veto
// 3. low energy (<0.7 MeV)
// -----By Bei-Zhen Hu  2015.09
// update: add pre Muon veto (2 micro-sec)
// 2015.11.12 update:  if ( evt.isWpMuon() || evt.isAdMuon() || evt.isAdShowerMuon() ) isMuon = true;
// 2015.12.09 update:  for muon add: if ( evt.isCross || evt.isForce || evt.isRPCNS ) continue;
// 2015.12.11 update:  livetime calculation, ending filling (fold=-1).
// 2015.12.23 update:  T2Prev__Mu bug and WP counting
// 2017.12.21 update:  follow PLD95 072006 (2017) paper
#include <iostream>
#include <deque>
#include <algorithm>
#include <fstream>
#include <TROOT.h>
#include <TFile.h>

#include "AdSimple.C"
#include "CalibStats.C"
#include "CalibReadoutHeader.C"
#include "TimeStamp.C"

#include "TH1F.h"
#include "TChain.h"

#include "Event.h"
#include "EventSummary.h"
#include "Summary.h"
#include "EventTree.h"
#include "EventTree.C"
#include "PhyEvent.h"
//#include "outfile.h"

//#include "Hists.h"
using namespace std;

const long long vSH=400000000;  // 0.4s
const long long vAD=  1400000;  //1400 us = 0.0014 s
const long long vWS=   600000;  // 600 us = 0.0006 s
const long long vpre=    2000;  //   2 us = 0.000002 s
long long EndMuonVetoWin[5] = {0};
long long PreMuonVetoWin[5] = {0};
long long LastVetoT[5] = {0};
long long CountLifeT[5] = {0};
long long GapTime[5] = {0};
long long firstT;
long long lastT;
long long vStartT;
long long lStartT;
long long preTriggerTime;
long long tBtwTriggers;
int preTriggerAD;
int date = 0;
int evtCounting[5] = {0};
int RunNo = 0;
int AdMuNum = 0;
int ShMuNum = 0;
int WpMuNum = 0;
int NetMuNum = 0;
double ThisFullTime = 0;
//TH1D* h_gap = new TH1D("h_gap","h_gap;dt(s);Conuts/0.1s",12000,0,12000);

 //////
 struct EventBrief {
    double sE;
    double sX,sY,sZ;
 };

 map<int /* AD No. */,  EventBrief  > PrevInfo;

/* Muon information */
 TimeStamp ThisVetoT;
 TimeStamp PrevVetoT;
 TimeStamp LastMuonT;
 TimeStamp FirstTriggerTime;
 TimeStamp LastTriggerTime;


 TimeStamp VetoAddition( 0, 0 );
 TimeStamp preVetoTime(0, vpre);
 map<int /* AD No. */, TimeStamp /* last pool muon time */  > LastPoolMuonT;
 map<int /* AD No. */, TimeStamp /* last AD muon time */    > LastAdMuonT;
 map<int /* AD No. */, TimeStamp /* last shower muon time */> LastShowerMuonT;
 map<int /* AD No. */, TimeStamp /* last net muon time */   > LastNetMuonT;
 map<int /* AD No. */, TimeStamp /* last sub event time */  > LastSubEvtT;
 map<int /* AD No. */, TimeStamp /* last AD event time */   > LastAdEvtT;

 map<int /* AD No. */, Event /* Event under construction */ > EventDict;
 map<int /* AD No. */, EventSummary /* Event under construction */ > EventMuonCounter;
 map<int /* AD No. */, vector<PhyEvent> /* Event under construction */ > EvtBuffer;

EventTree* aEventTree;

int TempSubEvt( int AdNo, PhyEvent &evt );
int FillTree( int AdNo, PhyEvent &evt );
int EndingFill( int AdNo );

int main(int argc,char** argv) {
	gROOT->ProcessLine("#include <vector>");
	if( argc != 3 ) {
    	cerr << "# of arguments error." << endl;
        return 1;
	}

	ifstream list(argv[1]);
	string fname;

	TChain *adch = new TChain("/Event/Rec/AdSimple");
	TChain *csch = new TChain("/Event/Data/CalibStats");
	
	while(getline(list,fname)){
		cout << fname << endl;
		adch->Add(fname.c_str());
		csch->Add(fname.c_str());
	}

	AdSimple adrec(adch);
	CalibStats calst(csch);

    aEventTree = new EventTree("Event",argv[2],0);
    LastMuonT = TimeStamp( 0, 0 );

    int ads;
    long long nevent = adrec.fChain->GetEntries();
    long long lastEventNo = nevent-1;
    cout << "nevent: " << nevent << endl;
    
	for( long long jentry = 0; jentry < nevent; ++jentry ) { // start of event loop
		
        //if ( jentry%1000000 == 0) { cout << jentry << std::endl; }
		adrec.GetEntry(jentry);
		calst.GetEntry(jentry);
        
		PhyEvent evt(calst,adrec);
        // current info:
        int DetNo = evt.detector;
        TimeStamp ThisSubEvtTime( evt.trigTime_s, evt.trigTime_ns );
        
        if (jentry==0) {
            FirstTriggerTime  = TimeStamp( evt.trigTime_s, evt.trigTime_ns);
            firstT = evt.t; //ns
            if(adrec.site==1||adrec.site==2)
                ads=2;
            else
                ads=4;
        }else{
        
            tBtwTriggers = evt.t - preTriggerTime;
            if (tBtwTriggers*1.0e-09>=30) { 
                cout << "GapTime = " << tBtwTriggers*1.0e-9 << endl;
                //h_gap->Fill(tBtwTriggers*1.0e-09);
                if(DetNo == preTriggerAD) cout << "Same AD GapTime = " << tBtwTriggers*1.0e-9 << endl;
            }
            if (tBtwTriggers*1.0e-09>120) { 
                for(int AdNo=1; AdNo<=ads; AdNo++) GapTime[AdNo]+= tBtwTriggers;
            }
        }
        
        if (jentry==lastEventNo) {
            LastTriggerTime = TimeStamp( evt.trigTime_s, evt.trigTime_ns);
            lastT = evt.t; //ns
        }
        preTriggerTime = evt.t;
        preTriggerAD = DetNo;
        
        /////////////////////////
        bool ADEvt = false;
        bool NonLowE  = false;
        bool NonHighE = false;
	    bool NomalTrigType = false;
        bool isMuon = false;

        // Flasher Cut
        if ( evt.isCross || evt.isForce || evt.isRPCNS ) continue;

        /////////////////// MUON Events ///////////////////
        if ( evt.isWpMuon() || evt.isAdMuon() || evt.isAdShowerMuon() ) isMuon = true;
        if ( !evt.isWp() && !evt.isAd() ) continue;
        
       if(isMuon){
           
           if (evt.isWpMuon()) {
               TimeStamp TbwMuons = ThisSubEvtTime-LastMuonT;
               for(int AdNo=1; AdNo<=ads; AdNo++) {
                   EventSummary& MuonCounter = EventMuonCounter[ AdNo ];
                   if (TbwMuons.GetSeconds()>0.000002)  MuonCounter.PlMuonNum += 1;
                   
                   /////// Set PreMuonVetoT and LastMuonVetoT /////
                   PreMuonVetoWin[AdNo] = evt.t-vpre;
                   if(LastVetoT[AdNo]==0)
                       LastVetoT[AdNo] = firstT;
                   else
                       LastVetoT[AdNo]  = EndMuonVetoWin[AdNo];
                   
                   ////// Counting LiveTime /////
                   if (PreMuonVetoWin[AdNo]>firstT && PreMuonVetoWin[AdNo]>LastVetoT[AdNo] ){
                       vStartT = PreMuonVetoWin[AdNo];
                       lStartT = LastVetoT[AdNo];
                       CountLifeT[AdNo]+= (vStartT-lStartT);
                       MuonCounter.NetMuonNum +=1;
                   }
                   
                   while (!EvtBuffer[AdNo].empty()) {
                       if ( EvtBuffer[AdNo][0].t < PreMuonVetoWin[AdNo] ) {
                           evtCounting[AdNo] += 1;
                           TempSubEvt(AdNo, EvtBuffer[AdNo][0]);
                           FillTree( AdNo, EvtBuffer[AdNo][0] );
                       }
                       vector<PhyEvent>::iterator k = EvtBuffer[AdNo].begin();
                       EvtBuffer[AdNo].erase(k);
                   }
                   ///
                   evtCounting[AdNo] = 0;
                   LastPoolMuonT[AdNo]  = ThisSubEvtTime;
                   EndMuonVetoWin[AdNo] = max(EndMuonVetoWin[AdNo],evt.t+vWS);
                   
               }
               
           }else if (evt.isAdMuon()) {
               EventSummary& MuonCounter = EventMuonCounter[ DetNo ];
               /////// Set PreMuonVetoT and LastMuonVetoT /////
               PreMuonVetoWin[DetNo] = evt.t;
               //PreMuonVetoWin[DetNo] = evt.t-vpre;
               if(LastVetoT[DetNo]==0)
                   LastVetoT[DetNo] = firstT;
               else
                   LastVetoT[DetNo]  = EndMuonVetoWin[DetNo];
               
               ////// Counting LiveTime /////
               if (PreMuonVetoWin[DetNo]>firstT && PreMuonVetoWin[DetNo]>LastVetoT[DetNo] ){
                   vStartT = PreMuonVetoWin[DetNo];
                   lStartT = LastVetoT[DetNo];
                   CountLifeT[DetNo]+= (vStartT-lStartT);
                   MuonCounter.NetMuonNum +=1;
               }
         
               while (!EvtBuffer[DetNo].empty()) {
      
                   if ( EvtBuffer[DetNo][0].t < PreMuonVetoWin[DetNo] ) {
                       evtCounting[DetNo] += 1;
                       TempSubEvt(DetNo, EvtBuffer[DetNo][0]);
                       FillTree( DetNo, EvtBuffer[DetNo][0] );
                   }
                   vector<PhyEvent>::iterator k = EvtBuffer[DetNo].begin();
                   EvtBuffer[DetNo].erase(k);
               }
               ///
               evtCounting[DetNo] = 0;
               if (evt.isAdShowerMuon()) {
                   MuonCounter.ShMuonNum += 1;
                   EndMuonVetoWin[DetNo] = evt.t+vSH;
                   LastShowerMuonT[DetNo]= ThisSubEvtTime;
                   
               }else{
                   MuonCounter.AdMuonNum += 1;
                   EndMuonVetoWin[DetNo] = max(EndMuonVetoWin[DetNo],evt.t+vAD);
                   LastAdMuonT[DetNo]    = ThisSubEvtTime;
               }
               
           }

            LastMuonT  = ThisSubEvtTime;
            continue;
	}
        
        ///////////// IBD Candidate //////////////////
        //// Good Event:
        // 1. not flashers
        if ( evt.isFlasher() || evt.is2inchFlasher()) continue;
        // 2. not in the muon veto window
        // apply muon veto
        if ( evt.t < EndMuonVetoWin[DetNo]) continue;
        // 3. AD Event
        if (    !evt.isAd()  )              continue;
        // 4. not low energy
        if (    evt.E<0.3 || evt.E>20.0  )  continue;
        
        if (	evt.isMultiTrig || evt.isEsumTrig || evt.isMultiAndEsumTrig )  NomalTrigType = true;
        
        if ( NomalTrigType)  EvtBuffer[ DetNo ].push_back(evt);
        
        //////////////


        
        
	} // end of event loop
    
    RunNo = atoi(argv[2]);
    ThisFullTime = (lastT-firstT)*1.e-9;
    //ThisFullTime = (LastTriggerTime-FirstTriggerTime).GetSeconds();
    date = int( ( LastTriggerTime.GetSeconds()+FirstTriggerTime.GetSeconds() )/2 );
    cout<<" FULLTime: "<<ThisFullTime<<endl;
    cout<<"Date: "<<date<<endl;
    
    for (int AdNo=1; AdNo<=ads; AdNo++) {
        cout<<AdNo<<" gapTime: "<<GapTime[AdNo]*1.0e-09<<endl;
        if (PreMuonVetoWin[AdNo]<LastVetoT[AdNo] )
            vStartT = lastT;
        else
            vStartT = PreMuonVetoWin[AdNo];
        
        lStartT = LastVetoT[AdNo];
        CountLifeT[AdNo]+= (vStartT-lStartT);
        
        while (!EvtBuffer[AdNo].empty()) {
            evtCounting[AdNo] += 1;
            TempSubEvt(AdNo, EvtBuffer[AdNo][0]);
            FillTree( AdNo, EvtBuffer[AdNo][0] );
            
            vector<PhyEvent>::iterator k = EvtBuffer[AdNo].begin();
            EvtBuffer[AdNo].erase(k);
        }
        evtCounting[AdNo] = 0;
        ///
        EventSummary& MuonCounter = EventMuonCounter[ AdNo ];
        AdMuNum = MuonCounter.AdMuonNum;
        ShMuNum = MuonCounter.ShMuonNum;
        WpMuNum = MuonCounter.PlMuonNum;
        NetMuNum = MuonCounter.NetMuonNum;

        EndingFill( AdNo );
        
    }
    
    aEventTree->Close();
    //aEventTree->Close(h_gap);
	return 0;
}

int FillTree( int AdNo, PhyEvent &evt )
{
    Event& CurrEvent = EventDict[ AdNo ];
    
    aEventTree->Run          = CurrEvent.Run;
    aEventTree->Det          = AdNo;
    aEventTree->Fold         = CurrEvent.Fold;
    aEventTree->TrigSec      = CurrEvent.TrigSec;
    aEventTree->TrigNano     = CurrEvent.TrigNano;
    aEventTree->TrigNo       = CurrEvent.TrigNo;
    aEventTree->E            = CurrEvent.E;
    aEventTree->X            = CurrEvent.X;
    aEventTree->Y            = CurrEvent.Y;
    aEventTree->Z            = CurrEvent.Z;
    
    aEventTree->T2PrevPlMu   = CurrEvent.T2PrevPlMu;
    aEventTree->T2PrevAdMu   = CurrEvent.T2PrevAdMu;
    aEventTree->T2PrevShMu   = CurrEvent.T2PrevShMu;
    
    aEventTree->FullTime     = CurrEvent.FullTime;
    aEventTree->LiveTime     = CountLifeT[AdNo]*1.0e-09;
    aEventTree->TimeGap      = GapTime[AdNo]*1.0e-9;
    //aEventTree->LiveTime     = (CountLifeT[AdNo]-GapTime[AdNo])*1.0e-09;
    aEventTree->AdMu         = CurrEvent.AdMu;
    aEventTree->ShMu         = CurrEvent.ShMu;
    aEventTree->WpMu         = CurrEvent.WpMu;
    aEventTree->NetMu         = CurrEvent.NetMu;
    
    aEventTree->Fill();
    CurrEvent.Reset();
    
    return 1;
}

int TempSubEvt( int AdNo, PhyEvent &evt )
{
    Event& CurrEvent = EventDict[ AdNo ];
    
    CurrEvent.Run   = RunNo;
    CurrEvent.Fold = evtCounting[AdNo];
    
    CurrEvent.E   = evt.E;
    CurrEvent.X   = evt.X;
    CurrEvent.Y   = evt.Y;
    CurrEvent.Z   = evt.Z;
    
    CurrEvent.TrigSec    = evt.trigTime_s;
    CurrEvent.TrigNano   = evt.trigTime_ns;
    CurrEvent.TrigNo     = evt.trigNo;

    ///
    CurrEvent.T2PrevPlMu = ( TimeStamp(evt.trigTime_s, evt.trigTime_ns) - LastPoolMuonT[ AdNo ] ).GetSeconds();
    CurrEvent.T2PrevAdMu = ( TimeStamp(evt.trigTime_s, evt.trigTime_ns) - LastAdMuonT[ AdNo ] ).GetSeconds();
    CurrEvent.T2PrevShMu = ( TimeStamp(evt.trigTime_s, evt.trigTime_ns) - LastShowerMuonT[ AdNo ] ).GetSeconds();
    
    //CurrEvent.FullTime       = ThisFullTime-GapTime[AdNo]*1.0e-09;
    CurrEvent.FullTime       = ThisFullTime;
    CurrEvent.TimeGap = GapTime[AdNo]*1.0e-9;
   
    CurrEvent.AdMu           = AdMuNum;
    CurrEvent.ShMu           = ShMuNum;
    CurrEvent.WpMu           = WpMuNum;
    CurrEvent.NetMu          = NetMuNum;
    
    
    return 1;
}

int EndingFill( int AdNo )
{
    aEventTree->Run            = RunNo;
    aEventTree->Det            = AdNo;
    aEventTree->Fold           = -1;
    aEventTree->TrigSec        = date;
    aEventTree->TrigNano       = -1;
    aEventTree->TrigNo         = -1;
    aEventTree->E              = -1;
    aEventTree->X              = -9999;
    aEventTree->Y              = -9999;
    aEventTree->Z              = -9999;
    
    aEventTree->T2PrevPlMu     = -9999;
    aEventTree->T2PrevAdMu     = -9999;
    aEventTree->T2PrevShMu     = -9999;
    
    aEventTree->FullTime       = ThisFullTime;
    aEventTree->LiveTime       = CountLifeT[AdNo]*1.0e-09;
    aEventTree->TimeGap        = GapTime[AdNo]*1.0e-9;
    //aEventTree->FullTime       = ThisFullTime-GapTime[AdNo]*1.0e-09;
    //aEventTree->LiveTime       = (CountLifeT[AdNo]-GapTime[AdNo])*1.0e-09;
    aEventTree->AdMu           = AdMuNum;
    aEventTree->ShMu           = ShMuNum;
    aEventTree->WpMu           = WpMuNum;
    aEventTree->NetMu          = NetMuNum;
    aEventTree->Fill();
    
    return 1;
}

