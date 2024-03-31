// this is made in 2018/05/31 
// I (PoAn,chenpoan@outlook.com), cheange the time cut window to 1000us,
// so as to fit the time distribution,
// then extract the time cut efficiency at time cut set at 400us.
//
// you can use bash command "make timemain" to generate timemain, which is operating file.
#include <iostream>
#include <fstream>
#include "TChain.h"
#include "TFile.h"
#include "AdSimple.C"
#include "CalibStats.C"
#include "PhyEvent.h"
#include <cmath>
#include "TH1D.h"
#include "TString.h"

bool EH1=1;
bool EH2=0;
bool EH3=0;
int EH=0;

using namespace std;
const long long preVetoOfWP = 2000;
const long long pVetoOfWP   = 600000;
const long long pVetoOfAD   = 1400000;
const long long pVetoOfSH   = 400000000;
const long long timeCut     = 400000;
const long long LongTimeCut = 400000;
const double    distCut     = 500;

bool epLock[5]= {false,false,false,false,false};
bool edLock[5]= {false,false,false,false,false};
bool IBDReady[5]= {false,false,false,false,false};
bool SingleReady[5]= {false,false,false,false,false};
bool FastNepLock[5]= {false,false,false,false,false};

int main(int argc, char** argv){
    if(EH1)EH=0;
    if(EH3)EH=3;

    /////////////////parameter space//////////////////

    double a_ep[5],a_xp[5],a_yp[5],a_zp[5],a_ed[5],a_xd[5],a_yd[5],a_zd[5];
    double a_dist[5];
    long long a_dT[5],a_tp[5],a_td[5];
    int detNo;
    double a_ibd_ep[5],a_ibd_xp[5],a_ibd_yp[5],a_ibd_zp[5],a_ibd_ed[5],a_ibd_xd[5],a_ibd_yd[5],a_ibd_zd[5];
    long long a_ibd_dT[5],a_ibd_tp[5],a_ibd_td[5];

    double ep,xp,yp,zp,ed,xd,yd,zd;
    double dtlSH_high,dtlSH_mid,dtlSH_low;
    double dist;
    long long dT,tp,td;

    double a_E[5],a_X[5],a_Y[5],a_Z[5];
    double E,X,Y,Z;
    bool isVeto;
    long long a_T[5];
    long long T;
    int sdetNo;

    int theDetNo;
    long long theAbsRunTime,theLiveTime,totalTime;

    long long Date,AmcCount,liveTimeCount,N_up,N_down,N_07,N_15;
    long long NIBD              = 0;

    long long NmuonArray[5]={0,0,0,0,0};
    long long Nmuon = 0;

    long long NaccSingleArr[5]={0,0,0,0,0};
    long long NaccSingle=0;
    long long a_NIBD[5]={0,0,0,0,0};

    double multiEff = 0;
    double multiEff_Err = 0;
    long long Nsample[5]={0,0,0,0,0};
    long long Nsuccess[5]={0,0,0,0,0};

    ////////////////parameter space end////////////////

    ifstream list(argv[1]);
    string fname;

    TChain *adch = new TChain("/Event/Rec/AdSimple");
    TChain *csch = new TChain("/Event/Data/CalibStats");

    while(getline(list,fname)){
        cout<<fname<<endl;
        adch->Add(fname.c_str());
        csch->Add(fname.c_str());
    }

    AdSimple adrec(adch);
    CalibStats calst(csch);

    TFile* output = new TFile(argv[2],"RECREATE");
    output->cd();
    
    TTree* tree = new TTree("IBDPA","ibd event");
    //TTree* tree2 = new TTree("Singles","singles event");
    TTree* tree3 = new TTree("amc","Information of Amc Singles rate per every day");
    TTree* tree4 = new TTree("live","liveTime for a run");
    tree->Branch("ep",&ep);
    tree->Branch("ed",&ed);
    tree->Branch("xp",&xp);
    tree->Branch("yp",&yp);
    tree->Branch("zp",&zp);
    tree->Branch("xd",&xd);
    tree->Branch("yd",&yd);
    tree->Branch("zd",&zd);
    tree->Branch("dist",&dist);
    tree->Branch("dT",&dT);
    tree->Branch("DetNo",&detNo);

    /*tree2->Branch("es",&E);
    tree2->Branch("xs",&X);
    tree2->Branch("ys",&Y);
    tree2->Branch("zs",&Z);
    tree2->Branch("trigNs",&T);
    tree2->Branch("sDetNo",&sdetNo);
    tree2->Branch("isVeto",&isVeto);*/

    tree3->Branch("N",&AmcCount);
    tree3->Branch("N07",&N_07);
    tree3->Branch("N15",&N_15);
    tree3->Branch("N_up",&N_up);
    tree3->Branch("N_down",&N_down);
    tree3->Branch("Date",&Date);
    tree3->Branch("liveTime",&liveTimeCount);
    tree3->Branch("detNo",&detNo);
    tree3->Branch("Nmuon",&Nmuon);
    tree3->Branch("Nacc",&NaccSingle);

    tree4->Branch("liveTime",&theLiveTime);
    tree4->Branch("T",&theAbsRunTime);
    tree4->Branch("Date",&Date);
    tree4->Branch("detNo",&theDetNo);
    tree4->Branch("totalTime",&totalTime);
    tree4->Branch("NIBD",&NIBD);
    tree4->Branch("multiEff",&multiEff);
    tree4->Branch("multiEff_Err",&multiEff_Err);
    
    long long totalEventNumber  = adrec.fChain->GetEntries();
    long long thisEventTime     = 0;
    long long startTime         = 0;
    long long lastTime          = 0;
    long long MuonVetoEnd[5]    ={0,0,0,0,0};
    long long FastNVetoEnd[5]    ={0,0,0,0,0};
    long long liveTime[5]       ={0,0,0,0,0};
    long long preLiveTime[5]    ={0,0,0,0,0};
    long long AmcSingles[5]     ={0,0,0,0,0};
    long long Nup[5]            ={0,0,0,0,0};
    long long Ndown[5]          ={0,0,0,0,0};
    long long N07[5]            ={0,0,0,0,0};
    long long N15[5]            ={0,0,0,0,0};
    int day                     =1;
    long long closestPromptTime[5]={0,0,0,0,0};
    long long closestFastNPromptTime[5]={0,0,0,0,0};
    long long closestMuonTime[5]={0,0,0,0,0};
    long long closestFastNMuonTime[5]={0,0,0,0,0};
    long long closestWPMuonTime=0;
    long long closestOWSMuonTime=0;
    long long closestIWSMuonTime=0;
    long long preSingleTime[5]={0,0,0,0,0};

    bool sampleLock[5]={0,0,0,0,0};
    int stage[5] = {0,0,0,0,0};
    long long samp_pre_prompt_time[5]={0,0,0,0,0};
    long long samp_delayed_time[5]={0,0,0,0,0};

    for(long long i=0;i<totalEventNumber;i++){
        adrec.GetEntry(i);
        calst.GetEntry(i);
        PhyEvent phyEvent(calst,adrec);

        int AdNo = phyEvent.detector;
        if(EH2){
            if(AdNo==1){detNo=3;sdetNo=3;}
            if(AdNo==2){detNo=8;sdetNo=8;}
        }else{
            detNo=AdNo+EH;
            sdetNo=AdNo+EH;
        }

        if(i==0){
            thisEventTime   = phyEvent.t;
            startTime       = phyEvent.t;
            for(int j=1;j<5;j++){
                MuonVetoEnd[j]  = startTime;
                preSingleTime[j] = startTime;
                closestPromptTime[j] = 1000;
            }
        }
        else if(i==totalEventNumber-1){         //This else if is in purpose to deal with the end
            lastTime        = phyEvent.t;       //of entries, to fill in the live time
            cout<<lastTime-startTime<<endl;     //(correlated to efficient) and also the total
            totalTime       = lastTime-startTime;
            theAbsRunTime=phyEvent.trigTime_s;  // running time.
            for(int j=1;j<5;j++){
                if(EH1){
                    theDetNo=j;
                    theLiveTime=liveTime[j];
                    NIBD=a_NIBD[j];
                    multiEff=100.*double(Nsuccess[j])/double(Nsample[j]);
                    multiEff_Err=100.*sqrt(double(Nsuccess[j]))/double(Nsample[j]);
                    Date        =phyEvent.trigTime_s;
                    tree4->Fill();
                }
                if(EH2){
                    if(j==1) theDetNo=3;
                    if(j==2) theDetNo=8;
                    if(j>2) continue;
                    theLiveTime=liveTime[j];
                    NIBD=a_NIBD[j];
                    multiEff=100.*double(Nsuccess[j])/double(Nsample[j]);
                    multiEff_Err=100.*sqrt(double(Nsuccess[j]))/double(Nsample[j]);
                    Date        =phyEvent.trigTime_s;
                    tree4->Fill();
                }
                if(EH3){
                    theDetNo=j+EH;
                    theLiveTime=liveTime[j];
                    NIBD=a_NIBD[j];
                    multiEff=100.*double(Nsuccess[j])/double(Nsample[j]);
                    multiEff_Err=100.*sqrt(double(Nsuccess[j]))/double(Nsample[j]);
                    Date        =phyEvent.trigTime_s;
                    tree4->Fill();
                }
            }
        }else thisEventTime      = phyEvent.t;
        
        bool isMuon = false;
        if(!phyEvent.isGood) continue;
        if(phyEvent.isWPMu || phyEvent.isSHMu || phyEvent.isADMu) isMuon = true;
        if(isMuon){
            if(phyEvent.isWPMu){
                closestWPMuonTime = thisEventTime;
                for(int j=1;j<5;j++){
                    if(IBDReady[j]==true){
                        if(thisEventTime-preVetoOfWP<a_ibd_td[j]){
                            IBDReady[j]=false;
                        }
                    }
                    if(thisEventTime-preVetoOfWP>MuonVetoEnd[j]) 
                        liveTime[j]+=thisEventTime-preVetoOfWP-MuonVetoEnd[j];
                    MuonVetoEnd[j]      = max(MuonVetoEnd[j],thisEventTime+pVetoOfWP);
                }
                //if(phyEvent.isIWSMu){
                //    if(thisEventTime-closestOWSMuonTime>2000){
                //        for(int j =1; j<5;j++){
                //            FastNVetoEnd[j]     = max(FastNVetoEnd[j],thisEventTime+pVetoOfWP);
                //        }
                //        closestIWSMuonTime = thisEventTime;
                //    }
                //}else/* if(phyEvent.isOWSMu)*/{
                //    closestOWSMuonTime = thisEventTime;
                //}
                continue;
            }else if(phyEvent.isADMu){
                if(thisEventTime>MuonVetoEnd[AdNo]) 
                    liveTime[AdNo]+=thisEventTime-MuonVetoEnd[AdNo];
                MuonVetoEnd[AdNo]   = max(MuonVetoEnd[AdNo],thisEventTime+pVetoOfAD);
                continue;
            }else/* if(phyEvent.isSHMu)*/{
                epLock[AdNo]=false;
                if(thisEventTime>MuonVetoEnd[AdNo]) 
                    liveTime[AdNo]+=thisEventTime-MuonVetoEnd[AdNo];
                MuonVetoEnd[AdNo]   = max(MuonVetoEnd[AdNo],thisEventTime+pVetoOfSH);
                continue;
            }
        }
        ///////////AmcSingles rate counting.//////////
        if(thisEventTime-startTime>86400000000000*day){
            for(int j=1;j<5;j++){
                N_07        =N07[j];
                N_15        =N15[j];
                N_up        =Nup[j];
                N_down      =Ndown[j];
                AmcCount    =AmcSingles[j];
                Date        =phyEvent.trigTime_s;
                Nmuon       =NmuonArray[j];
                NaccSingle  =NaccSingleArr[j];
                if(MuonVetoEnd[j]>thisEventTime){
                    liveTimeCount=liveTime[j]-preLiveTime[j];
                    preLiveTime[j]=liveTime[j];
                }else{
                    liveTimeCount=liveTime[j]-preLiveTime[j]+thisEventTime-MuonVetoEnd[j];
                    preLiveTime[j]=liveTime[j]+thisEventTime-MuonVetoEnd[j];
                }
                if(EH2){
                    if(j==1){detNo=3;}
                    if(j==2){detNo=8;}
                }else{
                    detNo=j+EH;
                }
                if(N_up!=0){
                    tree3->Fill();
                }
                AmcSingles[j]=0;
                N07[j]=0;
                N15[j]=0;
                Nup[j]=0;
                Ndown[j]=0;
                NmuonArray[j]=0;
                NaccSingleArr[j]=0;
            }
                day+=1;
                detNo=sdetNo;
        }
        //////////////IBD candidates seletion start here////////////
        //if(phyEvent.isPrompt){
        //    if(thisEventTime-preSingleTime[AdNo]>1000&&thisEventTime>MuonVetoEnd[AdNo]){
        //        E=phyEvent.e;
        //        X=phyEvent.x;
        //        Y=phyEvent.y;
        //        Z=phyEvent.z;
        //        T=phyEvent.t;
        //        tree2->Fill();
        //        NaccSingleArr[AdNo]++;
        //        if(E>0.7){N07[AdNo]++;}
        //        if(E>1.5){N15[AdNo]++;}
        //        if(E>6.&&Z>0.){Nup[AdNo]++;AmcSingles[AdNo]++;}     //here two if are for
        //        if(E>6.&&Z<0.){Ndown[AdNo]++;AmcSingles[AdNo]--;}   // amc singles.
        //    }
        //    preSingleTime[AdNo]=thisEventTime;
        //}
        if(phyEvent.isPrompt){
            if(IBDReady[AdNo]){
                if(phyEvent.isDelay){
                    IBDReady[AdNo]=false;
                    if(thisEventTime-a_ibd_td[AdNo]>timeCut){
                        ep=a_ibd_ep[AdNo]; 
                        xp=a_ibd_xp[AdNo];
                        yp=a_ibd_yp[AdNo];
                        zp=a_ibd_zp[AdNo];
                        tp=a_ibd_tp[AdNo];
                        ed=a_ibd_ed[AdNo];
                        xd=a_ibd_xd[AdNo];
                        yd=a_ibd_yd[AdNo];
                        zd=a_ibd_zd[AdNo];
                        td=a_ibd_td[AdNo];
                        dT=td-tp;
                        dist=sqrt(pow(xd-xp,2)+pow(yd-yp,2)+pow(zd-zp,2));                    
                        tree->Fill();
                        a_NIBD[AdNo]++;
                    }
                }
            }
            if(epLock[AdNo]==false){
                epLock[AdNo]=true;
                a_ep[AdNo]=phyEvent.e;
                a_xp[AdNo]=phyEvent.x;
                a_yp[AdNo]=phyEvent.y;
                a_zp[AdNo]=phyEvent.z;
                a_tp[AdNo]=phyEvent.t;
            }else{
                if(thisEventTime<MuonVetoEnd[AdNo]
                        ||thisEventTime-a_tp[AdNo]>timeCut
                        ||thisEventTime-a_tp[AdNo]<1000
                        ||phyEvent.isDelay!=true
                        ||thisEventTime-closestPromptTime[AdNo]<2*timeCut
                        ||pow(a_xp[AdNo]-phyEvent.x,2)+pow(a_yp[AdNo]-phyEvent.y,2)+pow(a_zp[AdNo]-phyEvent.z,2)>25.e4){
                    closestPromptTime[AdNo]=a_tp[AdNo];
                    a_ep[AdNo]=phyEvent.e;
                    a_xp[AdNo]=phyEvent.x;
                    a_yp[AdNo]=phyEvent.y;
                    a_zp[AdNo]=phyEvent.z;
                    a_tp[AdNo]=phyEvent.t;
                }else{
                    a_ibd_ep[AdNo]=a_ep[AdNo];
                    a_ibd_xp[AdNo]=a_xp[AdNo];
                    a_ibd_yp[AdNo]=a_yp[AdNo];
                    a_ibd_zp[AdNo]=a_zp[AdNo];
                    a_ibd_tp[AdNo]=a_tp[AdNo];
                    a_ibd_ed[AdNo]=phyEvent.e;
                    a_ibd_xd[AdNo]=phyEvent.x;
                    a_ibd_yd[AdNo]=phyEvent.y;
                    a_ibd_zd[AdNo]=phyEvent.z;
                    a_ibd_td[AdNo]=phyEvent.t;
                    IBDReady[AdNo]=true;
                    epLock[AdNo]=false;
                    closestPromptTime[AdNo]=thisEventTime;
                }
            }
        }
    }
    output->Write();
}
