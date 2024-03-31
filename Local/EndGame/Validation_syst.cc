#include "GetCorrection.h"
#include "FluxIntegral.cc"
#include "Uncertainty.h"



void Validation_syst(){

    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    //TString rootfile = "/Users/chengyuchin/Analysis/data/MC/pureLS.root";
    TString rootfile = "/Users/chengyuchin/Analysis/data/MC/Truth.root";


    Double_e effGd(0.719313, 0.0020518);     // no MO gen cap
    Double_e effH(0.410203, 0.0020518);
    //Double_e effGd(0.719332, 0.00103895);     // no MO gen
    //Double_e effH(0.405465, 0.00058616);
    //Double_e corr(0.13817751);
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
    //double nGd = effGd*(GdLS.GetGd(155)*IGd155 + GdLS.GetGd(157)*IGd157);


    Double_e Ratio = nH/nGd;

    cout << "Correction = ";
    corr.Print();
    cout << "IH = ";
    IH.Print();
    cout << "IGd155 = ";
    IGd155.Print();
    cout << "IGd157 = ";
    IGd157.Print();
    cout << "nH/nGd = ";
    Ratio.Print();


}


