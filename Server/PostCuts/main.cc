#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "TFile.h"
#include "TString.h"
#include "TVector3.h"
#include "TTree.h"


using namespace std;


const double Ep_min = 1.5;      // MeV
const double Ep_max = 12;       // MeV
const double Ed_min = 1.9;      // MeV
const double Ed_max = 12;       // MeV
const double Es_min = 0.7;      // MeV
const double Es_max = 12;       // MeV
const double dt_min = 0.000001; // sec
const double dt_max = 0.0004;   // sec
const double dr_max = 5000;      // mm
const bool do_fvcut = false;     // do fiducial volume cut or not



bool EpCut(double Ep);  //Ep
bool EdCut(double Ed);  //Ed
bool EsCut(double Es);  //Es
bool TimeIntervalCut(double dt);  //time interval
bool DistanceCut(double dr); //distance
int GetVolNo(double x, double y, double z);  //fiducial volume
bool InTarget(double x, double y, double z); // in target volume




int main(int argc, const char** argv){  // input, output

    if(argc != 3){
        cerr << "Error occurs due to wrong argument number!" << endl;
        return 0;
    }


    TString inname = argv[1];
    TString outname = argv[2];


    // IBD cut
    double ep, xp, yp, zp;
    double ed, xd, yd, zd;
    double dT, dist;
    int DetNo, CellNop, CellNod;
    int VolNop = 0;
    int VolNod = 0;


    TFile* Fin = new TFile(inname);
    TTree* IBDin = (TTree*)Fin->Get("IBD");
    IBDin->SetBranchAddress("DetNo",&DetNo);
    IBDin->SetBranchAddress("ep",&ep);
    IBDin->SetBranchAddress("xp",&xp);
    IBDin->SetBranchAddress("yp",&yp);
    IBDin->SetBranchAddress("zp",&zp);
    IBDin->SetBranchAddress("CellNop",&CellNop);
    IBDin->SetBranchAddress("ed",&ed);
    IBDin->SetBranchAddress("xd",&xd);
    IBDin->SetBranchAddress("yd",&yd);
    IBDin->SetBranchAddress("zd",&zd);
    IBDin->SetBranchAddress("CellNod",&CellNod);
    IBDin->SetBranchAddress("dT",&dT);
    IBDin->SetBranchAddress("dist",&dist);


    TFile* Fout = new TFile(outname,"recreate");
    TTree* IBDout = new TTree("IBD","IBD Tree");
    IBDout->Branch("DetNo",&DetNo,"DetNo/I");
    IBDout->Branch("ep",&ep,"ep/D");
    IBDout->Branch("xp",&xp,"xp/D");
    IBDout->Branch("yp",&yp,"yp/D");
    IBDout->Branch("zp",&zp,"zp/D");
    IBDout->Branch("CellNop",&CellNop,"CellNop/I");
    IBDout->Branch("VolNop",&VolNop,"VolNop/I");
    IBDout->Branch("ed",&ed,"ed/D");
    IBDout->Branch("xd",&xd,"xd/D");
    IBDout->Branch("yd",&yd,"yd/D");
    IBDout->Branch("zd",&zd,"zd/D");
    IBDout->Branch("CellNod",&CellNod,"CellNod/I");
    IBDout->Branch("VolNod",&VolNod,"VolNod/I");
    IBDout->Branch("dT",&dT,"dT/D");
    IBDout->Branch("dist",&dist,"dist/D");


    for(int i = 0; i<IBDin->GetEntries(); i++){
        Fin->cd();
        IBDin->GetEntry(i);


        if(EpCut(ep) and EdCut(ed) and TimeIntervalCut(dT) and InTarget(xp, yp, zp) and InTarget(xd, yd, zd) and DistanceCut(dist)){ 
            VolNop = GetVolNo(xp, yp, zp);
            VolNod = GetVolNo(xd, yd, zd);
            Fout->cd();
            IBDout->Fill();
        }
    }


    Fout->cd();
    IBDout->Write();
    delete IBDin;
    delete IBDout;


    // single cut
    double es, xs, ys, zs;
    int sDetNo, CellNos;
    int VolNos;


    Fin->cd();
    TTree* Sin = (TTree*)Fin->Get("Singles");
    Sin->SetBranchAddress("sDetNo",&sDetNo);
    Sin->SetBranchAddress("es",&es);
    Sin->SetBranchAddress("xs",&xs);
    Sin->SetBranchAddress("ys",&ys);
    Sin->SetBranchAddress("zs",&zs);
    Sin->SetBranchAddress("CellNos",&CellNos);


    Fout->cd();
    TTree* Sout = new TTree("Singles","Singles Tree");
    Sout->Branch("sDetNo",&sDetNo,"sDetNo/I");
    Sout->Branch("es",&es,"es/D");
    Sout->Branch("xs",&xs,"xs/D");
    Sout->Branch("ys",&ys,"ys/D");
    Sout->Branch("zs",&zs,"zs/D");
    Sout->Branch("CellNos",&CellNos,"CellNos/I");
    Sout->Branch("VolNos",&VolNos,"VolNos/I");


    for(long long i = 0; i<IBDin->GetEntries(); i++){
        Fin->cd();
        Sin->GetEntry(i);


        if(EsCut(es) and InTarget(xs, ys, zs)){ 
            VolNos = GetVolNo(xs, ys, zs);
            Fout->cd();
            Sout->Fill();
        }
    }


    Fout->cd();
    Sout->Write();
    Fin->Close();
    Fout->Close();



}





bool EpCut(double Ep){
    
    if(Ep > Ep_min && Ep < Ep_max) return true;
    else return false;


}




bool EdCut(double Ed){
    
    if(Ed > Ed_min && Ed < Ed_max) return true;
    else return false;


}




bool EsCut(double Es){
    
    if(Es > Es_min && Es < Es_max) return true;
    else return false;


}




bool TimeIntervalCut(double dt){


    if(dt > dt_min && dt < dt_max) return true;
    else return false;


}




bool DistanceCut(double dr){


    if(dr < dr_max) return true;
    else return false;


}






int GetVolNo(double x, double y, double z){

    TVector3 vtx(x,y,z);
    int VolNo = 0;


    if(vtx.Z()>=2000 or vtx.Z()<=-2000 or vtx.Perp2()>=2000*2000) VolNo = 3;

    else if(vtx.Z()<1554 and vtx.Z()>-1554 and vtx.Perp2()<1540*1540) VolNo = 1;

    else VolNo = 2;


    return VolNo;


}





bool InTarget(double x, double y, double z){

    if(not do_fvcut) return true;


    const double resolution_r = 178.7;
    const double resolution_z = 202.3;
    const double n_sigma = 1;


    double cut_z = 2000-n_sigma*resolution_z;
    double cut_r = 2000-n_sigma*resolution_r;


    TVector3 vtx(x,y,z);
    bool judge = true;
    if(vtx.Z()>=cut_z or vtx.Z()<=-1*cut_z or vtx.Perp2()>=cut_r*cut_r) judge = false;
    //if(vtx.Z()>=1750 or vtx.Z()<=-1750 or vtx.Perp2()>=1750*1750) judge = false;


    return judge;



}





