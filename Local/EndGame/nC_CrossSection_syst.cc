#include "GetCorrection.h"
#include "FluxIntegral.cc"
#include "Uncertainty.h"



void nC_CrossSection_syst(){
//int main(){

    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    TString rootfile = "/Users/chengyuchin/Analysis/data/MC/Truth.root";


    Double_e flux_normal(6.22998e+06, 0);
    Double_e effGd(0.719313, 0.00205183);
    Double_e effH(0.410203, 0.00205183);
    Double_e effC(0.350817, 0.00269258);
    Double_e RatioCH(0.00939383,0);
    Double_e RatioCGd(0.00752981,0);
    Double_e corr(GetCorrection());
    corr.SetError(0);
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


    IH.SetError(0);
    IGd155.SetError(0);
    IGd157.SetError(0);


    Double_e nH = effH*(corr*Double_e(GdLS.GetH(),GdLS.GetHerr()) + Double_e(LS.GetH(),LS.GetHerr())
                        + Double_e(acry.GetH(),acry.GetHerr()))*IH;
    Double_e nGd = effGd*corr*(Double_e(GdLS.GetGd(155),GdLS.GetGderr(155))*IGd155
                               + Double_e(GdLS.GetGd(157),GdLS.GetGderr(157))*IGd157);
    Double_e C = corr*Double_e(GdLS.GetC(),GdLS.GetCerr()) + Double_e(LS.GetC(),LS.GetCerr())
                 + Double_e(acry.GetC(),acry.GetCerr());


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



