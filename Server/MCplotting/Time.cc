#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include "TTree.h"
#include "TVector3.h"


using namespace std;
using elemap = map<int,TH1D*>;
using elepair = pair<int,TH1D*>;



bool EpCut(double* E);  //E
bool EdCut(double* E);  //E
bool EnergyDebug(double* E); //E
bool TimeIntervalCut(int* ts, int* tns);  //TrigSec, TrigNano
bool DistanceCut(TVector3 vtxp, TVector3 vtxd); //X, Y, Z



int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];


    cout << "Processing data : " << inname << endl;


    map<int,TString> name = { {1,"_H"}, {6,"_C"}, {64,"_Gd"} };
    elemap h_dt;
    for(auto i : name){
        h_dt.insert(elepair(i.first, new TH1D("dt"+i.second, "dt"+i.second+";dt(ns);Counts", 10000, 0, 10000000)));
    }


    TFile* f = new TFile(inname);
    TTree* Event = (TTree*)f->Get("Event");
    double* E = new double[2]();       //dynamic declaration for preventing memory corruption 
    double* X = new double[2](); 
    double* Y = new double[2](); 
    double* Z = new double[2](); 
    int* ts = new int[2]();
    int* tns = new int[2]();
    double CapTarget;
    TVector3 vtxp;
    TVector3 vtxd;
    Event->SetBranchAddress("X",X);
    Event->SetBranchAddress("Y",Y);
    Event->SetBranchAddress("Z",Z);
    Event->SetBranchAddress("E",E);
    Event->SetBranchAddress("CapTarget",&CapTarget);
    Event->SetBranchAddress("TrigSec",ts);
    Event->SetBranchAddress("TrigNano",tns);


    for(int i = 0; i<Event->GetEntries(); i++){
        Event->GetEntry(i);
        cout << "entry : " << i << endl;
        vtxp.SetXYZ(X[0],Y[0],Z[0]);
        vtxd.SetXYZ(X[1],Y[1],Z[1]);
        if(EpCut(E) && EdCut(E) && EnergyDebug(E) && DistanceCut(vtxp,vtxd)){ 

            elemap::iterator iter = h_dt.find(CapTarget);
            if(iter != h_dt.end()){
                long long dt = (ts[1]-ts[0])*1e9 + (tns[1]-tns[0]);
                iter->second->Fill(dt);
            }

        }
    }
    f->Close();


    TFile* fout = new TFile(outname,"recreate");
    for(auto p : h_dt){
        p.second->Write();
    }

        
    fout->Close();
    cout << outname << " complete!" << endl;


    delete f;
    delete fout;


    return 1;



}





bool EpCut(double* E){
    
    if(E[0] > 1.5 && E[0] < 12) return true;
    else return false;


}




bool EdCut(double* E){
    
    if(E[1] > 0 && E[1] < 12) return true;
    else return false;


}




bool EnergyDebug(double* E){

    if(E[0] != E[1]) return true;
    else return false;


}




bool TimeIntervalCut(int* ts, int* tns){

    long long dt = (ts[1]-ts[0])*1e9 + (tns[1]-tns[0]);


    if(dt > 1000 && dt < 400000) return true;
    else return false;


}




bool DistanceCut(TVector3 vtxp, TVector3 vtxd){

    TVector3 Dvtx = vtxd - vtxp;
    

    if(Dvtx.Mag() < 500) return true;
    else return false;


}



