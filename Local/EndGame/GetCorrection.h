#ifndef GetCorrection_h
#define GetCorrection_h


#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include "Volume.h"



//double GetCorrection(TString rootname, string txtname){
Double_e GetCorrection(){

    const Double_e nHCS[2] = {Double_e(0.25429,0.000785367), Double_e(0.311837,0.000886436)};      // vol ele
    //const Double_e nHCS[2] = {Double_e(0.316944,0.000956869), Double_e(0.312537,0.000893118)};    // vol
    Double_e correction;
    const int shift = 0;    //choose 0 or 1, could assign systematic
    double volume_ratio = 7.416/8.06385;
    string txtname = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    //TString rootname = "/Users/chengyuchin/Analysis/data/MC/10times_GeninGdLS.root";
    TString rootname = "/Users/chengyuchin/Analysis/data/MC/sum_fv.root";
    //TString rootname = "/Users/chengyuchin/Analysis/data/MC/Changeto3mLS_fv.root";


    const Double_e trig_GdLS(0.969398,0.00152088);
    const Double_e trig_LS(0.848318,0.000540237);

    
    Volume GdLS, LS;
    for(int i = 1; i<5; i++){
        GdLS = GdLS + Volume(i,1,txtname);
        LS = LS + Volume(i,2,txtname);
    }


    unique_ptr<TFile> Froot(new TFile(rootname));
    //TH2D* h1 = dynamic_cast<TH2D*>(Froot->Get("RZT_H_GdLS"));
    //TH2D* h2 = dynamic_cast<TH2D*>(Froot->Get("RZT_H_LS"));
    TH2D* h1 = dynamic_cast<TH2D*>(Froot->Get("RZT_GdLS"));
    TH2D* h2 = dynamic_cast<TH2D*>(Froot->Get("RZT_LS"));
    h1->Rebin2D(10,10);
    h2->Rebin2D(10,10);


    Double_e event_GdLS(h1->Integral(2,9,43,58), sqrt(h1->Integral(2,9,43,58)));
    //Double_e event_GdLS(h1->GetEntries(), sqrt(h1->GetEntries()));
    Double_e event_LS(h2->Integral(61+shift,68+shift,43,58), sqrt(h2->Integral(61+shift,68+shift,43,58)));
    //Double_e event_LS(h2->GetEntries(), sqrt(h2->GetEntries()));
    //Double_e content_GdLS(GdLS.GetH(), GdLS.GetHerr());
    //Double_e content_LS(LS.GetH(), LS.GetHerr());


    /*int xl,yl,xh,yh,z;
    //h->GetBinXYZ(h->FindBin(0,-1554), xl, yl, z);
    //h->GetBinXYZ(h->FindBin(1540*1540,1554), xh, yh, z);
    //h->GetBinXYZ(h->FindBin(0,-1540), xl, yl, z);
    //h->GetBinXYZ(h->FindBin(2.3e6,1540), xh, yh, z);
    h->GetBinXYZ(h->FindBin(900e3,-95), xl, yl, z);
    h->GetBinXYZ(h->FindBin(1110e3,95), xh, yh, z);
    double event_GdLS = h->Integral(xl,xh,yl,yh);


    h->GetBinXYZ(h->FindBin(0,-2000), xl, yl, z);
    h->GetBinXYZ(h->FindBin(2000*2000,2000), xh, yh, z);
    h->GetBinXYZ(h->FindBin(0,-2040), xl, yl, z);
    h->GetBinXYZ(h->FindBin(4.05e6,2100), xh, yh, z);
    double event_total = h->Integral(xl,xh,yl,yh);
    double event_LS = event_total - event_GdLS;


    h->GetBinXYZ(h->FindBin(3000e3,-1745), xl, yl, z);
    h->GetBinXYZ(h->FindBin(3200e3,-1655), xh, yh, z);
    double event_LS = h->Integral(xl,xh,yl,yh);
    h->GetBinXYZ(h->FindBin(3000e3,1655), xl, yl, z);
    h->GetBinXYZ(h->FindBin(3200e3,1745), xh, yh, z);
    event_LS += h->Integral(xl,xh,yl,yh);
    //event_LS /= 2;*/

    cout << "nH event in GdLS = " << event_GdLS << endl;
    cout << "nH event in LS = " << event_LS << endl;
    //cout << "GdLS H = " << content_GdLS << endl;
    //cout << "LS H = " << content_LS << endl;

    //correction = (event_GdLS/event_LS)*(trig_LS/trig_GdLS);
    correction = (event_GdLS/event_LS)*(trig_LS/trig_GdLS)*(LS.GetH()/GdLS.GetH())*volume_ratio*(nHCS[1]/nHCS[0]);
    //correction = (event_GdLS/event_LS)*(trig_LS/trig_GdLS)*(LS.GetH()/GdLS.GetH())*(nHCS[1]/nHCS[0]);
    cout << (LS.GetH()/GdLS.GetH())*volume_ratio << endl;


    Froot->Close();
    cout << "Correction = " << correction << endl;


    return correction;



}



#endif



