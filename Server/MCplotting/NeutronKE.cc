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


const int interested_Z = 1;
const int interested_A = 1;
const TString interested_name = "H";


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
    const TString ele = interested_name;


    //map<int,TString> name = { {-10,""}, {1,"_H"}, {6,"_C"}, {64,"_Gd"} };
    //map<int,TString> name = { {-10,"_"+ele}, {-5,"_woMO_"+ele}, {1,"_GdLS_"+ele}, {2,"_Acrylic_"+ele}, {3,"_LS_"+ele}, {5,"_MO_"+ele} };
    map<int,TString> name = { {-10,"_"+ele}, {-5,"_woMO_"+ele}, {1,"_GdLS_"+ele}, {2,"_IAV_"+ele}, {3,"_LS_"+ele}, {4,"_OAV_"+ele}, {5,"_MO_"+ele} };
    elemap nKE_Init, nKE_BfCap;
    for(auto i : name){
        nKE_Init.insert(elepair(i.first, new TH1D("nKE_Init"+i.second, "nKE_Init"+i.second+";E_{kin}(MeV);Counts", 5000, 0, 0.1)));
        nKE_BfCap.insert(elepair(i.first, new TH1D("nKE_Before_Cap"+i.second, "nKE_Before_Cap"+i.second+";E_{kin}(eV);Counts", 50000, 0, 1)));
    }
    //nKE_Init.insert(elepair(4,nKE_Init.at(2)));
    //nKE_BfCap.insert(elepair(4,nKE_BfCap.at(2)));


    TFile* f = new TFile(inname);
    TTree* nCapture = (TTree*)f->Get("stats/tree/nCapture");
    //int LastScatterVol;
    int CapVol, CapTarget, CapTargetMass;
    double KEgen, KEbfcap;
    //nCapture->SetBranchAddress("LastScatterVol",&LastScatterVol);
    nCapture->SetBranchAddress("CapVol",&CapVol);
    nCapture->SetBranchAddress("CapTarget",&CapTarget);
    nCapture->SetBranchAddress("CapTargetMass",&CapTargetMass);
    nCapture->SetBranchAddress("KEgen",&KEgen);
    nCapture->SetBranchAddress("KEbfcap",&KEbfcap);


    for(int i = 0; i<nCapture->GetEntries(); i++){

        nCapture->GetEntry(i);
        if(CapTarget == interested_Z and CapTargetMass == interested_A){

            elemap::iterator iter = nKE_Init.find(CapVol);
            if(iter != nKE_Init.end()){
                iter->second->Fill(KEgen);
                nKE_BfCap[iter->first]->Fill(KEbfcap*1.e6);
            }


            nKE_Init[-10]->Fill(KEgen);
            nKE_BfCap[-10]->Fill(KEbfcap*1.e6);

            if(CapVol == 5) continue;
            nKE_Init[-5]->Fill(KEgen);
            nKE_BfCap[-5]->Fill(KEbfcap*1.e6);

        }

    }
    f->Close();




    /*TTree* Event = (TTree*)f->Get("Event");
    double* E = new double[2]();       //dynamic declaration for preventing memory corruption 
    double CapTarget;
    double EkInit;
    double EkBfCap;
    int CapDet;
    Event->SetBranchAddress("E",E);
    Event->SetBranchAddress("CapTarget",&CapTarget);
    Event->SetBranchAddress("CapDet",&CapDet);
    Event->SetBranchAddress("EkInit",&EkInit);
    Event->SetBranchAddress("EkBfCap",&EkBfCap);


    for(int i = 0; i<Event->GetEntries(); i++){
        Event->GetEntry(i);
        cout << "entry : " << i << endl;
        if(EdCut(E) and EnergyDebug(E)){ 
            //if(!CapTarget) continue;
            if(not CapDet) continue;
            if(CapTarget != 64) continue;


            //elemap::iterator iter = nKE_Init.find(static_cast<int>(CapTarget));
            elemap::iterator iter = nKE_Init.find(CapDet);
            if(iter != nKE_Init.end()){
                iter->second->Fill(EkInit);
                nKE_BfCap[iter->first]->Fill(EkBfCap);
            }


            nKE_Init[-10]->Fill(EkInit);
            nKE_BfCap[-10]->Fill(EkBfCap);

            if(CapDet == 5) continue;
            nKE_Init[-5]->Fill(EkInit);
            nKE_BfCap[-5]->Fill(EkBfCap);

        }
    }
    f->Close();*/


    array<reference_wrapper<elemap>,2> v = {nKE_Init, nKE_BfCap};
    TFile* fout = new TFile(outname,"recreate");
    for(auto m : v){
        for(auto& p : m.get()){        // 2022 Jun.21 using get() to access the ref. wrapper
            //if(p.first != 4) p.second->Write();     // avoid save twice, since IAV and OAV are in the same TH1D address
            p.second->Write(); 
        }
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



