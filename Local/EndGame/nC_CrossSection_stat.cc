#include "GetCorrection.h"
#include "FluxIntegral.cc"
#include "Uncertainty.h"



void nC_CrossSection_stat(){
//int main(){

    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    TString rootfile = "/Users/chengyuchin/Analysis/data/MC/Truth.root";


    Double_e flux_normal(6.22998e+06, 2495.99);
    Double_e effGd(0.719313, 0.00107114);
    Double_e effH(0.410203, 0.000616685);
    Double_e effC(0.350817, 0.00577329);
    Double_e RatioCH(0.00939383,8.00671e-05);
    Double_e RatioCGd(0.00752981,6.41131e-05);
    Double_e corr(GetCorrection());
    //Double_e corr(GetCorrection(rootfile, txtfile));
    cout << "Correction = " << corr.GetValue() << endl;


    Volume GdLS, LS, acry;
    for(int ad = 1; ad<5; ad++){
            GdLS = GdLS + Volume(ad, 1, txtfile);
            LS = LS + Volume(ad, 2, txtfile);
            acry = acry + Volume(ad, 3, txtfile);
        }


    Double_e IH, IGd155, IGd157;
    IH = FluxIntegral("H",1);
    IGd155 = FluxIntegral("Gd",155);
    IGd157 = FluxIntegral("Gd",157);


    Double_e nH = effH*(corr*GdLS.GetH() + LS.GetH() + acry.GetH())*IH;
    Double_e nGd = effGd*corr*(GdLS.GetGd(155)*IGd155 + GdLS.GetGd(157)*IGd157);
    Double_e C = corr*GdLS.GetC() + LS.GetC() + acry.GetC();


    cout << "Expected nH = ";
    nH.Print();
    cout << "Expected nGd = ";
    nGd.Print();
    cout << "Expected C = ";
    C.Print();


    Double_e cs1 = (RatioCH * nH) / (effC * C); 
    Double_e cs2 = (RatioCGd * nGd) / (effC * C); 


    cout << "Correction = " << corr << endl;
    cout << "nC cross section from nC/nH = " << cs1 << endl;
    cout << "nC cross section from nC/nGd = " << cs2 << endl;



}



