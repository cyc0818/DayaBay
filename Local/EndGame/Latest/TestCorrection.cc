#include "/Users/chengyuchin/Analysis/nC/EndGame/Volume.h"


using namespace std;
// Average CS in GdLS, LS, Acrylic
const array<Double_e,3> nH_CS = {Double_e(0.253996,0.000769066), Double_e(0.311809, 0.000872109), Double_e(0.347539, 0.000938592)};  // syst vol ele
const array<Double_e,3> nC_CS = {Double_e(0.00423111,5.34559e-05), Double_e(0.00600734, 6.11888e-05), Double_e(0.00703724, 7.81217e-05)};// syst vol ele rebin(100)
//const array<Double_e,3> nC_CS = {Double_e(0.0042944,2.716e-05), Double_e(0.00656089, 2.32799e-05), Double_e(0.00798453, 6.7131e-05)};// syst vol ele rebin(10)
const array<Double_e,3> nGd155_CS = {Double_e(54510.9,247.894), Double_e(), Double_e()};    // syst vol ele
const array<Double_e,3> nGd157_CS = {Double_e(218319,587.017), Double_e(), Double_e()};     // syst vol ele


// Trigger efficiency
const Double_e trig_GdLS(0.969398,0.00152088);
const Double_e trig_LS(0.848318,0.000540237);

void TestCorrection(){

    TString rootname = "/Users/chengyuchin/Analysis/data/MC/sum_fv.root";
    const int shift = 0;    // 0 or 1
    const double volume_ratio = 7.416/8.06385;
    string txtname = "/Users/chengyuchin/Analysis/nC/EndGame/data2.txt";


    Volume GdLS, LS, Acrylic;
    //for(int i = 1; i<5; i++){
    for(int i = 1; i<9; i++){
        GdLS = GdLS + Volume(i,1,txtname);
        LS = LS + Volume(i,2,txtname);
        Acrylic = Acrylic + Volume(i, 3, txtname);
    }



    const Double_e S_GdLS = GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0) + GdLS.GetHboth()*nH_CS.at(0) + GdLS.GetCboth()*nC_CS.at(0);
    const Double_e S_LS = LS.GetHboth()*nH_CS.at(1) + LS.GetCboth()*nC_CS.at(1);
    const Double_e S_acry = Acrylic.GetHboth()*nH_CS.at(2) + Acrylic.GetCboth()*nC_CS.at(2);
    //const Double_e S_GdLS = GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0) + GdLS.GetHboth()*nH_CS.at(0);
    //const Double_e S_LS = LS.GetHboth()*nH_CS.at(1);
    //const Double_e S_acry = Acrylic.GetHboth()*nH_CS.at(2);
    cout << "S_LS = " << S_LS << endl;
    cout << "S_LS_nH = " << LS.GetHboth()*nH_CS.at(1) << endl;
    cout << "r = " << LS.GetHboth()*nH_CS.at(1)/S_LS << endl;
    
    //const Double_e correction = (GdLS.GetHboth()/LS.GetHboth()) * (S_LS/S_GdLS);
    //const Double_e correction2 = (Acrylic.GetHboth()/LS.GetHboth()) * (S_LS/S_acry);
    //const Double_e correction = (GdLS.GetMass()*0.1198/LS.GetMass()/0.1195) * (S_LS/S_GdLS);
    //const Double_e correction2 = (Acrylic.GetMass()*0.0805/LS.GetMass()/0.1195) * (S_LS/S_acry);
    //const Double_e correction = (event_GdLS/event_LS) * (S_LS/S_GdLS) * (trig_LS/trig_GdLS) / volume_ratio;
    //cout << "Correction factor GdLS = " << correction << endl;
    //cout << "Correction factor Acrylic = " << correction2 << endl;
    cout << "Target proton GdLS/LS = " << GdLS.GetHboth()/ LS.GetHboth() << endl;


    const Double_e w_GdLS = GdLS.GetHboth()/S_GdLS;
    const Double_e w_LS = LS.GetHboth()/S_LS;
    const Double_e w_acry = Acrylic.GetHboth()/S_acry;


    cout << "w_GdLS = " << w_GdLS << endl;
    cout << "w_LS = " << w_LS << endl;
    cout << "w_acry = " << w_acry << endl;


}


