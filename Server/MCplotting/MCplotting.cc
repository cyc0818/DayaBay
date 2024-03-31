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
int GetCellNo(TVector3 vtx);



int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];


    cout << "Processing data : " << inname << endl;


    /*TH1D* nGdProblem = new TH1D("nGdProblem","nGdProblem",1200,0,12);
    TH1D* nGdNormal = new TH1D("nGdNormal","nGdNormal",1200,0,12);*/
    TH1D* nGd = new TH1D("nGd","nGd",1200,0,12);
    TH1D* nH = new TH1D("nH","nH",1200,0,12);
    TH1D* nC = new TH1D("nC","nC",1200,0,12);
    TH1D* EdSpectrum = new TH1D("EdSpectrum","EdSpectrum",1200,0,12);
    TH1D* nGdOthers = new TH1D("nGdOthers","nGdOthers",1200,0,12);


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
        cout << "entry : " << i << endl;


        vtxp.SetXYZ(X[0],Y[0],Z[0]);
        vtxd.SetXYZ(X[1],Y[1],Z[1]);
        vtxt.SetXYZ(XT[1],YT[1],ZT[1]);


        if(EpCut(E) && EdCut(E) && EnergyDebug(E) && TimeIntervalCut(ts,tns) && DistanceCut(vtxp,vtxd)){ 

            /*int CellNop = GetCellNo(vtxp);
            int CellNod = GetCellNo(vtxd);
            if(CellNop == 100 or CellNod == 100) continue;*/


            if(CapTarget == 64){       //nGd

   /*             if(vtxt.Perp2()>2.36e6 && vtxt.Perp2()<2.4e6){
                    nGdProblem->Fill(E[1]);
                }
                else{
                    nGdNormal->Fill(E[1]);
                }*/
            

                nGd->Fill(E[1]);
            }


            if(CapTarget == 6){       //nC
                nC->Fill(E[1]);
            }


            if(CapTarget == 1){       //nH
                nH->Fill(E[1]);
            }
            EdSpectrum->Fill(E[1]);
        }
    }
    f->Close();


    TFile* fout = new TFile(outname,"recreate");
    nGdOthers->Add(EdSpectrum,nH,1,-1);
    nGdOthers->Add(nC,-1);
    nGd->Write();
    nC->Write();
    nH->Write();
    EdSpectrum->Write();
    nGdOthers->Write();
    //nGdProblem->Write();
    //nGdNormal->Write();

        
    fout->Close();
    cout << outname << " complete!" << endl;

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



int GetCellNo(TVector3 vtx){

    int CellNo = 100;
    int a = 15;      // for R^2
    int b = 15;      // for z, (10a + b)


    double Rsq = 0;
    double z = 0;


    Rsq = vtx.Perp2();
    z = vtx.Z() + 2000;


    a = (int)(Rsq/400000);
    if(z>0) b = (int)(z/400);


    if(a>=0 && a<10 && b>=0 && b<10) CellNo = 10*a + b;



    return CellNo;



}



