#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include "Volume.h"
#include "FluxIntegral.cc"



Double_e GetCorrection2(){

    string txtname = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    Volume GdLS, LS;
    for(int i = 1; i<5; i++){
        GdLS = GdLS + Volume(i,1,txtname);
        LS = LS + Volume(i,2,txtname);
    }


    cout << "GdLS H = " << GdLS.GetH() << endl;
    cout << "LS H = " << LS.GetH() << endl;
    Double_e vol_fraction = GdLS.GetMass()/LS.GetMass();
    //double vol_fraction = 7.416/8.06385;
    cout  << "Volume fraction = "<< vol_fraction << endl;


    Double_e IH = FluxIntegral("H",1);
    vector<int> tar_iso = {152,154,155,156,157,158,160};
    map<int,Double_e> IGd;
    for(auto i : tar_iso){
        IGd.insert(pair<int,Double_e>(i,FluxIntegral("Gd",i)));
    }
    Double_e& IGd155 = IGd.at(155);
    Double_e& IGd157 = IGd.at(157);

    Double_e correction;    // a/b
    Double_e a = Double_e(LS.GetH(),LS.GetHerr()) * IH;
    //Double_e c = Double_e(GdLS.GetGd(155),GdLS.GetGderr(155)) * IGd155 + Double_e(GdLS.GetGd(157),GdLS.GetGderr(157)) * IGd157;
    Double_e b = Double_e(GdLS.GetH(),GdLS.GetHerr()) * IH;
    for(auto& p : IGd){
        b += Double_e(GdLS.GetGd(p.first),GdLS.GetGderr(p.first)) * p.second;
    }
    //Double_e b = Double_e(GdLS.GetH(),GdLS.GetHerr()) * IH + Double_e(GdLS.GetGd(155),GdLS.GetGderr(155)) * IGd155 +
    //             Double_e(GdLS.GetGd(157),GdLS.GetGderr(157)) * IGd157;

    correction = (a/b)*vol_fraction;
    //correction = a / b;

    cout << correction << endl;


    Double_e one = a*6.02e-2/8.06385/3.1415926;
    Double_e two = b*6.02e-2/7.416/3.1415926;
    cout << "LS = " << one << endl;
    cout << "GdLS = " << two << endl;


    return correction;


}






