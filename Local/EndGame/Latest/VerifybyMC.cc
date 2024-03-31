#include "/Users/chengyuchin/Analysis/nC/EndGame/GetCorrection.h"
#include "/Users/chengyuchin/Analysis/nC/EndGame/FluxIntegral.cc"
#include "/Users/chengyuchin/Analysis/nC/EndGame/Uncertainty.h"



// Average CS in GdLS, LS, Acrylic
const array<Double_e,3> nH_CS = {Double_e(0.328571,0.000958202), Double_e(0.323999, 0.000894814), Double_e(0.359997, 0.00149286)};  // syst
//const array<Double_e,3> nC_CS = {Double_e(0.00349679,1.89021e-05), Double_e(0.00344748, 1.75639e-05), Double_e(0.00382845, 2.21386e-05)};  // syst
const array<Double_e,3> nC_CS = {Double_e(0.00336836,1.88946e-05), Double_e(0.00332356, 1.75546e-05), Double_e(0.0036901, 2.18868e-05)};  // syst nat.
const array<Double_e,3> nGd155_CS = {Double_e(51399.7,236.848), Double_e(), Double_e()};    // syst 
const array<Double_e,3> nGd157_CS = {Double_e(215586,576.98), Double_e(), Double_e()};     // syst     

// Normalization const for flux in GdLS
const double correction = 0.134864;
//const double correction = 0.13362;


// MO spill-in
const double nH_spillin = 1;
const double nC_spillin = 1;

// Selection efficiency
// Trigger+Ep
const Double_e nH_Epeff(0.761544,0.0019104973);     // syst
const Double_e nC_Epeff(0.755373,0.0018384776);     // syst
const Double_e nGd_Epeff(0.947208,0.0020518285);    // syst
// dr
const Double_e nH_dreff(0.734396,0.0056044625);     // syst*
const Double_e nC_dreff(0.698758,0.0056044625);     // syst*
const Double_e nGd_dreff(0.824677,0.0056044625);    // syst*
// dt
const Double_e nH_dteff(0.87493,0.0028);            // syst*
const Double_e nC_dteff(0.871302,0.0028);           // syst*
const Double_e nGd_dteff(0.995302,0);
// Ed
const Double_e nH_Edeff(0.838077,0.0026870058);     // syst
const Double_e nC_Edeff(0.81292116,0.0099768355);       // syst
const Double_e nGd_Edeff(0.925227,0.0011180340);       // syst


// Detector material
Volume GdLS;
Volume LS;
Volume Acrylic;


// Measurement
const Double_e nH_evt(2648572,1627.4434);
const Double_e nC_evt(21353,146.12666);
const Double_e nGd_evt(3325677,1823.6439);



void VerifybyMC(){


    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    for(int ad = 1; ad<5; ad++){
        GdLS = GdLS + Volume(ad, 1, txtfile);
        LS = LS + Volume(ad, 2, txtfile);
        Acrylic = Acrylic + Volume(ad, 3, txtfile);
    }



    cout << "nC events = " << nC_evt << endl;

    // syst
    const Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
    const Double_e nC_eff = nC_Epeff*nC_dreff*nC_dteff*nC_Edeff;
    const Double_e nGd_eff = nGd_Epeff*nGd_dreff*nGd_dteff*nGd_Edeff;

    
    const Double_e ExpnH = correction*GdLS.GetHboth()*nH_CS.at(0) + LS.GetHboth()*nH_CS.at(1) + Acrylic.GetHboth()*nH_CS.at(2);
    const Double_e ExpnC = correction*GdLS.GetCboth()*nC_CS.at(0) + LS.GetCboth()*nC_CS.at(1) + Acrylic.GetCboth()*nC_CS.at(2);
    const Double_e ExpnGd = correction*(GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0));
    const Double_e Catom = correction*GdLS.GetCboth() + LS.GetCboth() + Acrylic.GetCboth();
    const Double_e Hatom = correction*GdLS.GetHboth() + LS.GetHboth() + Acrylic.GetHboth();

    cout << "exp nH = " << ExpnH << endl;
    cout << "C atom = " << Catom << endl;
    cout << "effH = " << nH_eff << endl;
    cout << "effC = " << nC_eff << endl;
    cout << "effGd = " << nGd_eff << endl;
    
    // stat
    /*Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
    Double_e nC_eff = nC_Epeff*nC_dreff*nC_dteff*nC_Edeff;
    Double_e nGd_eff = nGd_Epeff*nGd_dreff*nGd_dteff*nGd_Edeff;
    Double_e ExpnH = correction*GdLS.GetHboth()*nH_CS.at(0) + LS.GetHboth()*nH_CS.at(1) + Acrylic.GetHboth()*nH_CS.at(2);
    Double_e ExpnC = correction*GdLS.GetCboth()*nC_CS.at(0) + LS.GetCboth()*nC_CS.at(1) + Acrylic.GetCboth()*nC_CS.at(2);
    Double_e ExpnGd = correction*(GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0));
    Double_e Catom = correction*GdLS.GetCboth() + LS.GetCboth() + Acrylic.GetCboth();
    nH_eff.SetError(0);
    nC_eff.SetError(0);
    nGd_eff.SetError(0);
    ExpnH.SetError(0);
    ExpnC.SetError(0);
    ExpnGd.SetError(0);
    Catom.SetError(0);*/


    Double_e result1 = (nC_evt/nH_evt) * (ExpnH/Catom) *(nH_eff/nC_eff);
    Double_e result2 = (nC_evt/nGd_evt) * (ExpnGd/Catom) *(nGd_eff/nC_eff);
    Double_e result3 = (nH_evt/nGd_evt) * (ExpnGd/Hatom) *(nGd_eff/nH_eff);


    cout << "----------------nC part----------------" << endl;
    cout << "From nC/nH : nC CS = " << result1 << endl;
    cout << "From nC/nGd : nC CS = " << result2 << endl;
    cout << "Theoretical : nC CS = " << ExpnC/Catom << endl;



    cout << "----------------nH part----------------" << endl;
    cout << "From nH/nGd : nH CS = " << result3 << endl;
    cout << "Theoretical : nH CS = " << ExpnH/Hatom << endl;



}



