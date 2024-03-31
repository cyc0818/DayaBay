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
int GetCellNo(TVector3 vtxd);



int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];


    cout << "Processing data : " << inname << endl;


    TH1D* nGd[101];
    TH1D* nC[101];
    TH1D* nH[101];
    TH1D* EdSpectrum[101];
    TH1D* nGdOthers[101];
    for(int i = 0; i<100; i++){
        nGd[i] = new TH1D(TString::Format("nGd_Cell%d",i),TString::Format("nGd_Cell%d",i),1200,0,12);
        nC[i] = new TH1D(TString::Format("nC_Cell%d",i),TString::Format("nC_Cell%d",i),1200,0,12);
        nH[i] = new TH1D(TString::Format("nH_Cell%d",i),TString::Format("nH_Cell%d",i),1200,0,12);
        EdSpectrum[i]  = new TH1D(TString::Format("EdSpectrum_Cell%d",i),TString::Format("EdSpectrum_Cell%d",i),1200,0,12);
        nGdOthers[i] = new TH1D(TString::Format("nGdOthers_Cell%d",i),TString::Format("nGdOthers_Cell%d",i),1200,0,12);
    }
    nGd[100] = new TH1D("nGd","nGd",1200,0,12);
    nH[100] = new TH1D("nH","nH",1200,0,12);
    nC[100] = new TH1D("nC","nC",1200,0,12);
    EdSpectrum[100] = new TH1D("EdSpectrum","EdSpectrum",1200,0,12);
    nGdOthers[100] = new TH1D("nGdOthers","nGdOthers",1200,0,12);


    TFile* f = new TFile(inname);
    TTree* Event = (TTree*)f->Get("Event");
    double* E = new double[2]();       //dynamic declaration for preventing memory corruption 
    double* X = new double[2](); 
    double* Y = new double[2](); 
    double* Z = new double[2](); 
    int* ts = new int[2]();
    int* tns = new int[2]();
    TVector3 vtxp;
    TVector3 vtxd;
    double CapTarget;
    Event->SetBranchAddress("X",X);
    Event->SetBranchAddress("Y",Y);
    Event->SetBranchAddress("Z",Z);
    Event->SetBranchAddress("E",E);
    Event->SetBranchAddress("TrigSec",ts);
    Event->SetBranchAddress("TrigNano",tns);
    Event->SetBranchAddress("CapTarget",&CapTarget);


    for(int i = 0; i<Event->GetEntries(); i++){       //0 = near , 1 = far
        Event->GetEntry(i);
        cout << "entry : " << i << endl;
        vtxp.SetXYZ(X[0],Y[0],Z[0]);
        vtxd.SetXYZ(X[1],Y[1],Z[1]);
        int cell1 = GetCellNo(vtxp);
        int cell2 = GetCellNo(vtxd);
        if(EpCut(E) && EdCut(E) && EnergyDebug(E) && TimeIntervalCut(ts,tns) && DistanceCut(vtxp,vtxd) && cell1<100 && cell2<100){ 
            if(CapTarget == 64){       //nGd
                nGd[cell]->Fill(E[1]);
                nGd[100]->Fill(E[1]);
            }


            if(CapTarget == 6){       //nC
                nC[cell]->Fill(E[1]);
                nC[100]->Fill(E[1]);
            }


            if(CapTarget == 1){       //nH
                nH[cell]->Fill(E[1]);
                nH[100]->Fill(E[1]);
            }
            EdSpectrum[cell]->Fill(E[1]);
            EdSpectrum[100]->Fill(E[1]);
        }
    }
    f->Close();


    TFile* fout = new TFile(outname,"recreate");
    for(int i = 0; i<101; i++){
        nGdOthers[i]->Add(EdSpectrum[i],nH[i],1,-1);
        nGdOthers[i]->Add(nC[i],-1);
        if(i == 100) fout->cd();
        else{
            fout->mkdir(TString::Format("Cell%d",i));
            fout->cd(TString::Format("Cell%d",i));
        }
        nGd[i]->Write();
        nC[i]->Write();
        nH[i]->Write();
        EdSpectrum[i]->Write();
        nGdOthers[i]->Write();
    }

        
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


 
int GetCellNo(TVector3 vtxd){

    int CellNo = 100;
    int a = 15;      // for R^2
    int b = 15;      // for z, (10a + b)


    double Rsq = 0;
    double z = 0;


    Rsq = vtxd.Perp2();
    z = vtxd.Z() + 2000;


    a = (int)(Rsq/400000);
    if(z>0) b = (int)(z/400);


    if(a>=0 && a<10 && b>=0 && b<10) CellNo = 10*a + b;



    return CellNo;



}



