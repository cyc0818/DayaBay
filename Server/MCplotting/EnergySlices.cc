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




bool EpCut(double* E);  //E
bool EdCut(double* E);  //E
bool EnergyDebug(double* E); //E
bool TimeIntervalCut(int* ts, int* tns);  //TrigSec, TrigNano
bool DistanceCut(TVector3 vtxp, TVector3 vtxd); //X, Y, Z
bool DFiducial(TVector3 vtxd);



int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];


    cout << "Processing data : " << inname << endl;


    TH1D* h_GdRT[6];
    TH1D* h_GdzT[6];
    TH2D* h_Gd2DT[6];


    for(int i = 0 ; i<6; i++){
        h_GdRT[i] = new TH1D(TString::Format("GdRT%d",i+1),TString::Format("GdRT%d",i+1),400,0,4000000);
        h_GdzT[i] = new TH1D(TString::Format("GdzT%d",i+1),TString::Format("GdzT%d",i+1),400,-2000,2000);
        h_Gd2DT[i] = new TH2D(TString::Format("Gd2DT%d",i+1),TString::Format("Gd2DT%d",i+1),400,0,4000000,400,-2000,2000);
    }


    TFile* f = new TFile(inname);
    TTree* Event = (TTree*)f->Get("Event");
    double* E = new double[2]();       //dynamic declaration for preventing memory corruption 
    double* X = new double[2](); 
    double* Y = new double[2](); 
    double* Z = new double[2](); 
    double* XT = new double[2](); 
    double* YT = new double[2](); 
    double* ZT = new double[2](); 
    int* ts = new int[2]();
    int* tns = new int[2]();
    TVector3 vtxp;
    TVector3 vtxd;
    TVector3 vtxt;
    double CapTarget;
    Event->SetBranchAddress("X",X);
    Event->SetBranchAddress("Y",Y);
    Event->SetBranchAddress("Z",Z);
    Event->SetBranchAddress("E",E);
    Event->SetBranchAddress("XT",XT);
    Event->SetBranchAddress("YT",YT);
    Event->SetBranchAddress("ZT",ZT);
    Event->SetBranchAddress("TrigSec",ts);
    Event->SetBranchAddress("TrigNano",tns);
    Event->SetBranchAddress("CapTarget",&CapTarget);
    for(int i = 0; i<Event->GetEntries(); i++){       //0 = near , 1 = far
        Event->GetEntry(i);
        vtxp.SetXYZ(X[0],Y[0],Z[0]);
        vtxd.SetXYZ(X[1],Y[1],Z[1]);
        vtxt.SetXYZ(XT[1],YT[1],ZT[1]);
        if(EpCut(E) && EdCut(E) && EnergyDebug(E) && TimeIntervalCut(ts,tns) && DistanceCut(vtxp,vtxd)){ 
            if(CapTarget == 64){

                if(E[1]<3) continue;
                int n = (int)(E[1]-3);
                if(n>5) continue;
                h_GdRT[n]->Fill(vtxt.Perp2());
                h_GdzT[n]->Fill(vtxt.Z());
                h_Gd2DT[n]->Fill(vtxt.Perp2(),vtxt.Z());
            }


        }
    }
    f->Close();


    TFile* fout = new TFile(outname,"recreate");

    for(int i = 0 ; i<6; i++){
        h_GdRT[i]->Write();
        h_GdzT[i]->Write();
        h_Gd2DT[i]->Write();
    }


    fout->Close();


    return 1;



}





bool EpCut(double* E){
    
    if(E[0] >= 1.5 && E[0] <= 12) return true;
    else return false;


}




bool EdCut(double* E){
    
    if(E[1] > 0 && E[1] <= 12) return true;
    else return false;


}




bool EnergyDebug(double* E){

    if(E[0] != E[1]) return true;
    else return false;


}




bool TimeIntervalCut(int* ts, int* tns){

    long long dt = (ts[1]-ts[0])*1e9 + (tns[1]-tns[0]);


    if(dt >= 1000 && dt <= 400000) return true;
    else return false;


}




bool DistanceCut(TVector3 vtxp, TVector3 vtxd){

    TVector3 Dvtx = vtxd - vtxp;
    

    if(Dvtx.Mag() <= 500) return true;
    else return false;


}


 
bool DFiducial(TVector3 vtxd){

    bool a = false;


    if(vtxd.Perp2() <= 2000*2000 && vtxd.Z() < 2000 && vtxd.Z() > -2000) a = true;


    return a;

}
