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
int GenVolume(TVector3 vtxpT);   //GdLS = 1, LS = 2, Others = 3
int CapVolume(TVector3 vtxdT);   //not in GdLS = 0, (inner, middle, outer) = (1,2,3)



int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];


    cout << "Processing data : " << inname << endl;

    /*TH1D* h_GdRT = new TH1D("GdRT","GdRT",400,0,4000000);
    TH1D* h_GdzT = new TH1D("GdzT","GdzT",400,-2000,2000);
    TH2D* h_Gd2DT = new TH2D("Gd2DT","Gd2DT",400,0,4000000,400,-2000,2000);*/
    array<TString,4> name = {"","inner","middle","outer"};
    map<int,TH1D*> h_GdRT;
    map<int,TH1D*> h_GdzT;
    map<int,TH1D*> h_nGd;
    map<int,TH2D*> h_Gd2DT;
    for(int i = 1; i<4; i++){
        h_GdRT.insert(pair<int,TH1D*>(i,new TH1D("GdRT_"+name[i],"GdRT_"+name[i],400,0,4000000)));
        h_GdzT.insert(pair<int,TH1D*>(i,new TH1D("GdzT_"+name[i],"GdzT_"+name[i],400,-2000,2000)));
        h_nGd.insert(pair<int,TH1D*>(i,new TH1D("nGd_"+name[i],"nGd_"+name[i],1200,0,12)));
        h_Gd2DT.insert(pair<int,TH2D*>(i,new TH2D("Gd2DT_"+name[i],"Gd2DT_"+name[i],400,0,4000000,400,-2000,2000)));
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
        vtxp.SetXYZ(XT[0],YT[0],ZT[0]);
        vtxd.SetXYZ(X[1],Y[1],Z[1]);
        vtxt.SetXYZ(XT[1],YT[1],ZT[1]);
        if(EpCut(E) && EdCut(E) && EnergyDebug(E) && TimeIntervalCut(ts,tns) && DistanceCut(vtxp,vtxd)){ 
            if(CapTarget == 64){
                if(CapVolume(vtxt) == 0) continue;
                h_GdRT[CapVolume(vtxt)]->Fill(vtxt.Perp2());
                h_GdzT[CapVolume(vtxt)]->Fill(vtxt.Z());
                h_nGd[CapVolume(vtxt)]->Fill(E[1]);
                h_Gd2DT[CapVolume(vtxt)]->Fill(vtxt.Perp2(),vtxt.Z());
            }


        }
    }
    f->Close();


    TFile* fout = new TFile(outname,"recreate");
    /*h_GdRT->Write();
    h_GdzT->Write();
    h_Gd2DT->Write();*/
    vector<reference_wrapper<map<int,TH1D*>>> v = {h_GdRT, h_GdzT, h_nGd};
    for(map<int,TH1D*> m : v){
        for(auto p : m){        // 2022 Feb.3 pass by ref. -> pass by value
            p.second->Write();
        }
    }
    for(auto p : h_Gd2DT) p.second->Write();


    fout->Close();

    delete[] X;
    delete[] Y;
    delete[] Z;
    delete[] E;
    delete[] ts;
    delete[] tns;
    delete f;


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



int GenVolume(TVector3 vtxpT){

    if(vtxpT.Perp2() < 1540*1540 and vtxpT.Z() < 1554 and vtxpT.Z() > -1554) return 1;

    else if (vtxpT.Perp2() >= 2000*2000 or vtxpT.Z() >= 2000 or vtxpT.Z() <= -2000) return 3;

    else return 2;


}



int CapVolume(TVector3 vtxdT){
    
    if(vtxdT.Perp2() >= 1540*1540 or vtxdT.Z() >= 1554 or vtxdT.Z() <= -1554) return 0;

    else{


        if(vtxdT.Perp2() < 1200000 and vtxdT.Z() < 780 and vtxdT.Z() > -780) return 1;

        else if(vtxdT.Perp2() >= 2000000 or vtxdT.Z() >= 1300 or vtxdT.Z() <= -1300) return 3;

        else return 2;


    }


}

    












