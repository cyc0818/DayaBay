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

    TH1D* h_GdR = new TH1D("GdR","GdR",400,0,4000000);
    TH1D* h_GdRT = new TH1D("GdRT","GdRT",400,0,4000000);
    TH1D* h_Gdz = new TH1D("Gdz","Gdz",400,-2000,2000);
    TH1D* h_GdzT = new TH1D("GdzT","GdzT",400,-2000,2000);
    TH2D* h_Gd2D = new TH2D("Gd2D","Gd2D",400,0,4000000,400,-2000,2000);
    TH2D* h_Gd2DT = new TH2D("Gd2DT","Gd2DT",400,0,4000000,400,-2000,2000);
    TH1D* h_HR = new TH1D("HR","HR",400,0,4000000);
    TH1D* h_HRT = new TH1D("HRT","HRT",400,0,4000000);
    TH1D* h_Hz = new TH1D("Hz","Hz",400,-2000,2000);
    TH1D* h_HzT = new TH1D("HzT","HzT",400,-2000,2000);
    TH2D* h_H2D = new TH2D("H2D","H2D",400,0,4000000,400,-2000,2000);
    TH2D* h_H2DT = new TH2D("H2DT","H2DT",400,0,4000000,400,-2000,2000);
    TH1D* h_R = new TH1D("TR","TR",400,0,4000000);
    TH1D* h_RT = new TH1D("TRT","TRT",400,0,4000000);
    TH1D* h_z = new TH1D("Tz","Tz",400,-2000,2000);
    TH1D* h_zT = new TH1D("TzT","TzT",400,-2000,2000);
    TH2D* h_2D = new TH2D("T2D","T2D",400,0,4000000,400,-2000,2000);
    TH2D* h_2DT = new TH2D("T2DT","T2DT",400,0,4000000,400,-2000,2000);
    TH1D* hdt = new TH1D("dt","dt",200,1000,400000);


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
                h_GdR->Fill(vtxd.Perp2());
                h_GdRT->Fill(vtxt.Perp2());
                h_Gdz->Fill(vtxd.Z());
                h_GdzT->Fill(vtxt.Z());
                h_Gd2D->Fill(vtxd.Perp2(),vtxd.Z());
                h_Gd2DT->Fill(vtxt.Perp2(),vtxt.Z());
            }


            if(CapTarget == 1){
                h_HR->Fill(vtxd.Perp2());
                h_HRT->Fill(vtxt.Perp2());
                h_Hz->Fill(vtxd.Z());
                h_HzT->Fill(vtxt.Z());
                h_H2D->Fill(vtxd.Perp2(),vtxd.Z());
                h_H2DT->Fill(vtxt.Perp2(),vtxt.Z());
            }
            
            
            h_R->Fill(vtxd.Perp2());
            h_RT->Fill(vtxt.Perp2());
            h_z->Fill(vtxd.Z());
            h_zT->Fill(vtxt.Z());
            h_2D->Fill(vtxd.Perp2(),vtxd.Z());
            h_2DT->Fill(vtxt.Perp2(),vtxt.Z());
            long long dt = (ts[1]-ts[0])*1e9 + (tns[1]-tns[0]);
            hdt->Fill(dt);
        }
    }
    f->Close();


    TFile* fout = new TFile(outname,"recreate");
    h_GdR->Write();
    h_GdRT->Write();
    h_Gdz->Write();
    h_GdzT->Write();
    h_Gd2D->Write();
    h_Gd2DT->Write();


    h_HR->Write();
    h_HRT->Write();
    h_Hz->Write();
    h_HzT->Write();
    h_H2D->Write();
    h_H2DT->Write();


    h_R->Write();
    h_RT->Write();
    h_z->Write();
    h_zT->Write();
    h_2D->Write();
    h_2DT->Write();
    hdt->Write();

        
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
