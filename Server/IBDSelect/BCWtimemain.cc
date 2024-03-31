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

bool EH1=1;
bool EH2=0;
bool EH3=0;
int EH=0;

using namespace std;
const long long preVetoOfWP = 2000;
const long long pVetoOfWP   = 600000;
const long long pVetoOfAD   = 1400000;
const long long pVetoOfSH   = 400000000;
const long long timeCut     = 1000000;
const long long LongTimeCut = 1000000;
const double    distCut     = 6000;

bool epLock[5]= {false,false,false,false,false};
bool edLock[5]= {false,false,false,false,false};
bool IBDReady[5]= {false,false,false,false,false};
bool SingleReady[5]= {false,false,false,false,false};

int main(int argc, char** argv){
    if(EH1)EH=0;
    if(EH3)EH=3;

    /////////////////parameter space//////////////////

    double a_ep[5],a_xp[5],a_yp[5],a_zp[5],a_ed[5],a_xd[5],a_yd[5],a_zd[5];
    double a_dist[5];
    long long a_dT[5],a_tp[5],a_td[5];
    int detNo;

    double ep,xp,yp,zp,ed,xd,yd,zd;
    double dist;
    long long dT,tp,td;

    double a_E[5],a_X[5],a_Y[5],a_Z[5];
    double E,X,Y,Z;
    long long a_T[5];
    long long T;
    int sdetNo;

    int theDetNo;
    long long theAbsRunTime,theLiveTime,totalTime;

    long long Date,AmcCount,liveTimeCount,N_up,N_down;

    long long NmuonArray[5]={0,0,0,0,0};
    long long Nmuon = 0;

    long long NaccSingleArr[5]={0,0,0,0,0};
    long long NaccSingle=0;

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

    TFile *output = new TFile(argv[2],"RECREATE");
    output->cd();
    TTree* tree = new TTree("IBD","ibd event");
    TTree* tree2 = new TTree("Singles","singles event");
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
    tree->Branch("detNo",&detNo);

    tree2->Branch("E",&E);
    tree2->Branch("X",&X);
    tree2->Branch("Y",&Y);
    tree2->Branch("Z",&Z);
    tree2->Branch("T",&T);
    tree2->Branch("detNo",&sdetNo);

    tree3->Branch("N",&AmcCount);
    tree3->Branch("N_up",&N_up);
    tree3->Branch("N_down",&N_down);
    tree3->Branch("Date",&Date);
    tree3->Branch("liveTime",&liveTimeCount);
    tree3->Branch("detNo",&detNo);
    tree3->Branch("Nmuon",&Nmuon);
    tree3->Branch("Nacc",&NaccSingle);

    tree4->Branch("liveTime",&theLiveTime);
    tree4->Branch("T",&theAbsRunTime);
    tree4->Branch("detNo",&theDetNo);
    tree4->Branch("totalTime",&totalTime);
    
    long long totalEventNumber  = adrec.fChain->GetEntries();
    long long thisEventTime     = 0;
    long long startTime         = 0;
    long long lastTime          = 0;
    long long MuonVetoEnd[5]    ={0,0,0,0,0};
    long long liveTime[5]       ={0,0,0,0,0};
    long long preLiveTime[5]    ={0,0,0,0,0};
    long long AmcSingles[5]     ={0,0,0,0,0};
    long long Nup[5]            ={0,0,0,0,0};
    long long Ndown[5]          ={0,0,0,0,0};
    int day                     =1;
    long long closestPromptTime[5]={0,0,0,0,0};
    long long preSingleTime[5]={0,0,0,0,0};
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
                    if(j>2) continue;
                    theDetNo=j;
                    theLiveTime=liveTime[j];
                    tree4->Fill();
                }
                if(EH2){
                    if(j==1) theDetNo=3;
                    if(j==2) theDetNo=8;
                    if(j>2) continue;
                    theLiveTime=liveTime[j];
                    tree4->Fill();
                }
                if(EH3){
                    theDetNo=j+EH;
                    theLiveTime=liveTime[j];
                    tree4->Fill();
                }
            }
        }                                       //It ends here.
        else thisEventTime      = phyEvent.t;
        
        bool isMuon = false;
        if(!phyEvent.isGood) continue;
        if(phyEvent.isWPMu || phyEvent.isSHMu || phyEvent.isADMu) isMuon = true;
        if(isMuon){
            if(phyEvent.isWPMu){
                for(int j=1;j<5;j++){
                    epLock[j]=false;
                    if(thisEventTime-preVetoOfWP>MuonVetoEnd[j]) liveTime[j]+=thisEventTime-preVetoOfWP-MuonVetoEnd[j];
                    MuonVetoEnd[j]      = max(MuonVetoEnd[j],thisEventTime+pVetoOfWP);
                    if(thisEventTime-preVetoOfWP<a_T[j]) SingleReady[j]=false;
                    if(thisEventTime-preVetoOfWP<a_td[j]) IBDReady[j]=false;
                    NmuonArray[j]+=1;
                }
            }
            if(phyEvent.isADMu){
                    if(thisEventTime>MuonVetoEnd[AdNo]) liveTime[AdNo]+=thisEventTime-MuonVetoEnd[AdNo];
                    MuonVetoEnd[AdNo]   = max(MuonVetoEnd[AdNo],thisEventTime+pVetoOfAD);
                    NmuonArray[AdNo]+=1;
            }
            if(phyEvent.isSHMu){
                    if(thisEventTime>MuonVetoEnd[AdNo]) liveTime[AdNo]+=thisEventTime-MuonVetoEnd[AdNo];
                    MuonVetoEnd[AdNo]   = max(MuonVetoEnd[AdNo],thisEventTime+pVetoOfSH);
                    NmuonArray[AdNo]+=1;
            }
            continue;
        }
        ///////////AmcSingles rate counting.//////////
        if(thisEventTime-startTime>86400000000000*day){
            for(int j=1;j<5;j++){
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
                Nup[j]=0;
                Ndown[j]=0;
                NmuonArray[j]=0;
                NaccSingleArr[j]=0;
            }
                day+=1;
                detNo=sdetNo;
        }
        ////////////////IBD candidates seletion start here////////////
        if(MuonVetoEnd[AdNo]>thisEventTime) continue;
        if(IBDReady[AdNo]==true&&phyEvent.isDelay==true){//delayed cut applied here
                tree->Fill();
                IBDReady[AdNo]=false;
        }
        if(phyEvent.isPrompt){
            if(thisEventTime-preSingleTime[AdNo]>timeCut){// time cut & isolation cut applied

                if(SingleReady[AdNo]){
                    E=a_E[AdNo];
                    X=a_X[AdNo];
                    Y=a_Y[AdNo];
                    Z=a_Z[AdNo];
                    T=a_T[AdNo];
                    tree2->Fill();
                    NaccSingleArr[AdNo]++;
                    if(E>6.&&Z>0.){Nup[AdNo]++;AmcSingles[AdNo]++;}     //here two if are for
                    if(E>6.&&Z<0.){Ndown[AdNo]++;AmcSingles[AdNo]--;}   // amc singles.
                }
                a_E[AdNo]=phyEvent.e;
                a_X[AdNo]=phyEvent.x;
                a_Y[AdNo]=phyEvent.y;
                a_Z[AdNo]=phyEvent.z;
                a_T[AdNo]=phyEvent.t;
                preSingleTime[AdNo]=thisEventTime;
                SingleReady[AdNo]=true;
            }else{
                SingleReady[AdNo]=false;
                preSingleTime[AdNo]=thisEventTime;
            }
        }
        if(epLock[AdNo]==false&&edLock[AdNo]==false&&phyEvent.isPrompt==true){
            epLock[AdNo]=true;
            a_ep[AdNo]=phyEvent.e;
            a_xp[AdNo]=phyEvent.x;
            a_yp[AdNo]=phyEvent.y;
            a_zp[AdNo]=phyEvent.z;
            a_tp[AdNo]=phyEvent.t;
            continue;
        }
        if(epLock[AdNo]==true&&edLock[AdNo]==false&&phyEvent.isPrompt==true){
            if(thisEventTime-a_tp[AdNo]>LongTimeCut){
                closestPromptTime[AdNo]=a_tp[AdNo];
                a_ep[AdNo]=phyEvent.e;    
                a_xp[AdNo]=phyEvent.x;
                a_yp[AdNo]=phyEvent.y;
                a_zp[AdNo]=phyEvent.z;
                a_tp[AdNo]=phyEvent.t;
                continue;
            }             
            else{
                if(phyEvent.isDelay){
                    edLock[AdNo]=true;
                    a_ed[AdNo]=phyEvent.e;
                    a_xd[AdNo]=phyEvent.x;
                    a_yd[AdNo]=phyEvent.y;
                    a_zd[AdNo]=phyEvent.z;
                    a_td[AdNo]=phyEvent.t;
                    if(sqrt(pow(a_xd[AdNo]-a_xp[AdNo],2)+pow(a_yd[AdNo]-a_yp[AdNo],2)+pow(a_zd[AdNo]-a_zp[AdNo],2))>distCut){
                        epLock[AdNo]=false;// We remove distance cut here.
                        edLock[AdNo]=false;
                        closestPromptTime[AdNo]=thisEventTime;
                        continue;
                    }
                    ep=a_ep[AdNo];             
                    xp=a_xp[AdNo];
                    yp=a_yp[AdNo];
                    zp=a_zp[AdNo];
                    tp=a_tp[AdNo];
                    ed=a_ed[AdNo];
                    xd=a_xd[AdNo];
                    yd=a_yd[AdNo];
                    zd=a_zd[AdNo];
                    td=a_td[AdNo];
                    dT=td-tp;
                    dist=sqrt(pow(xd-xp,2)+pow(yd-yp,2)+pow(zd-zp,2));
                    IBDReady[AdNo]=true;
                    epLock[AdNo]=false;
                    edLock[AdNo]=false;
                    if(td-closestPromptTime[AdNo]<(2*timeCut)||td-MuonVetoEnd[AdNo]<(2*timeCut)) IBDReady[AdNo]=false;
                    closestPromptTime[AdNo]=thisEventTime;
                    continue;
                }
            }
        }
    }
    output->Write();
}
