#include "GetCorrection.h"
#include "FluxIntegral.cc"
#include "Uncertainty2.h"



void nC_CrossSection(){
//int main(){

    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    TString rootfile = "/Users/chengyuchin/Analysis/data/MC/Truth.root";


    Double_e flux_normal(6.22998e+06, 2495.99);
    Double_e effGd(0.719313*0.99406, 0.00107114);
    //Double_e effGd(0.719313, 0.00107114);
    Double_e effH(0.410203, 0.000616685);
    //Double_e effH(0.310203, 0.000616685);
    //Double_e effC(0.38048557, 0.0102208);
    Double_e effC(0.350817, 0.00577329);
    //Double_e effC(0.350817*0.47827, 0.00577329);
    //Double_e NumH(2.081e6*0.4783,0.002e6);
    Double_e NumH(2.081e6,0.002e6);
    //Double_e NumGd(2.596e6*0.99406403,0.002e6);
    Double_e NumGd(2.596e6,0.002e6);
    Double_e NumC(19548,166);
    //Double_e NumC(17028,166);
    Double_e RatioCH = NumC/NumH;
    Double_e RatioCGd = NumC/NumGd;
    //Double_e RatioCH(0.00939383,8.00671e-05);
    //Double_e RatioCGd(0.00752981,6.41131e-05);
    Double_e corr(GetCorrection());
    cout << "Correction = " << corr.GetValue() << endl;


    Volume GdLS, LS, acry;
    for(int ad = 1; ad<5; ad++){
            GdLS = GdLS + Volume(ad, 1, txtfile);
            LS = LS + Volume(ad, 2, txtfile);
            acry = acry + Volume(ad, 3, txtfile);
    }


    Double_e IH, IGd155, IGd157;
    IH = FluxIntegral("H",1,0.02);
    IGd155 = FluxIntegral("Gd",155,5000);
    IGd157 = FluxIntegral("Gd",157,12000);


    /*Double_e nH = effH*(corr*Double_e(GdLS.GetH(),GdLS.GetHerr()) + Double_e(LS.GetH(),LS.GetHerr())
                        + Double_e(acry.GetH(),acry.GetHerr()))*IH;
    Double_e nGd = effGd*corr*(Double_e(GdLS.GetGd(155),GdLS.GetGderr(155))*IGd155
                               + Double_e(GdLS.GetGd(157),GdLS.GetGderr(157))*IGd157);*/
    Double_e nH = (corr*Double_e(GdLS.GetH(),GdLS.GetHerr()) + Double_e(LS.GetH(),LS.GetHerr())
                        + Double_e(acry.GetH(),acry.GetHerr()))*IH;
    Double_e nGd = corr*(Double_e(GdLS.GetGd(155),GdLS.GetGderr(155))*IGd155
                               + Double_e(GdLS.GetGd(157),GdLS.GetGderr(157))*IGd157);
    Double_e C = corr*Double_e(GdLS.GetC(),GdLS.GetCerr()) + Double_e(LS.GetC(),LS.GetCerr())
                 + Double_e(acry.GetC(),acry.GetCerr());


    cout << "Expected nH = ";
    nH.Print();
    cout << "Expected nGd = ";
    nGd.Print();
    cout << "Expected C = ";
    C.Print();
    cout << "effH/effC = " << effH/effC << endl;


    Double_e cs1 = (RatioCH * nH) / (effC * C); 
    Double_e cs2 = (RatioCGd * nGd) / (effC * C); 


    cout << "Correction = " << corr << endl;
    cout << "nC cross section from nC/nH = " << cs1 << endl;
    cout << "nC cross section from nC/nGd = " << cs2 << endl;



}



