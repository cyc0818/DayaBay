#include "/Users/chengyuchin/Analysis/nC/EndGame/Volume.h"


using namespace std;
// Average CS in GdLS, LS, Acrylic
const array<Double_e,3> nH_CS = {Double_e(0.25429,0.000785367), Double_e(0.311837, 0.000886436), Double_e(0.343103, 0.0012552)};  // syst vol ele
//const array<Double_e,3> nC_CS = {Double_e(0.00483085,4.e-6), Double_e(0.00481809, 4.32e-6), Double_e(0.00566645, 2.48433e-05)};  // syst vol
const array<Double_e,3> nC_CS = {Double_e(0.00424098,6.39e-05), Double_e(0.00601832, 6.98e-05), Double_e(0.0071953, 0.000184272)};  // syst vol ele
const array<Double_e,3> nGd155_CS = {Double_e(53375.3,243.436), Double_e(), Double_e()};    // syst vol ele
const array<Double_e,3> nGd157_CS = {Double_e(219001,586.323), Double_e(), Double_e()};     // syst vol ele


// Trigger efficiency
const Double_e trig_GdLS(0.969398,0.00152088);
const Double_e trig_LS(0.848318,0.000540237);

void Correction(){

    TString rootname = "/Users/chengyuchin/Analysis/data/MC/sum_fv.root";
    const int shift = 0;    // 0 or 1
    const double volume_ratio = 7.416/8.06385;
    string txtname = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";


    Volume GdLS, LS;
    for(int i = 1; i<5; i++){
        GdLS = GdLS + Volume(i,1,txtname);
        LS = LS + Volume(i,2,txtname);
    }


    unique_ptr<TFile> Froot(new TFile(rootname));
    TH2D* h1 = dynamic_cast<TH2D*>(Froot->Get("RZT_GdLS"));
    TH2D* h2 = dynamic_cast<TH2D*>(Froot->Get("RZT_LS"));
    h1->Rebin2D(10,10);
    h2->Rebin2D(10,10);
    //const Double_e event_GdLS(h1->GetEntries(), sqrt(h1->GetEntries()));
    //const Double_e event_LS(h2->GetEntries(), sqrt(h2->GetEntries()));
    const Double_e event_GdLS(h1->Integral(2,9,43,58), sqrt(h1->Integral(2,9,43,58)));
    const Double_e event_LS(h2->Integral(61+shift,68+shift,43,58), sqrt(h2->Integral(61+shift,68+shift,43,58)));


    const Double_e S_GdLS = GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0) + GdLS.GetHboth()*nH_CS.at(0) + GdLS.GetCboth()*nC_CS.at(0);
    const Double_e S_LS = LS.GetHboth()*nH_CS.at(1) + LS.GetCboth()*nC_CS.at(1);
    
    const Double_e correction = (event_GdLS/event_LS) * (S_LS/S_GdLS) * (trig_LS/trig_GdLS);
    //const Double_e correction = (event_GdLS/event_LS) * (S_LS/S_GdLS) * (trig_LS/trig_GdLS) / volume_ratio;
    cout << "Correction factor = " << correction << endl;


}


