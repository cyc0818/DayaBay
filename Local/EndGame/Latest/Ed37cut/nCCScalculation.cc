#include "/Users/chengyuchin/Analysis/nC/EndGame/GetCorrection.h"
#include "/Users/chengyuchin/Analysis/nC/EndGame/FluxIntegral.cc"
#include "/Users/chengyuchin/Analysis/nC/EndGame/Uncertainty.h"



// Average CS in GdLS, LS, Acrylic
const array<Double_e,3> nH_CS = {Double_e(0.25377,0.000785652), Double_e(0.311757, 0.000875588), Double_e(0.347427, 0.00101049)};  // syst vol ele
const array<Double_e,3> nC_CS = {Double_e(0.00419896,6.46033e-05), Double_e(0.00600961, 6.34761e-05), Double_e(0.00703178, 0.000107731)};// syst vol ele
const array<Double_e,3> nGd155_CS = {Double_e(54510.9,247.894), Double_e(), Double_e()};    // syst vol ele
const array<Double_e,3> nGd157_CS = {Double_e(218319,587.017), Double_e(), Double_e()};     // syst vol ele

// Normalization const for flux in GdLS
//const double correction = 0.132547;     // vol ele
//const double correction = 0.134864;     // vol
//const double correction = 0.13362;    // vol
//const double correction = 0.121969;    // test
//const double correction2 = 0.907774;    // test
//const double correction = 0.121969;    // test
//const double correction2 = 0.907774;    // test


// Volume weight
const double w_GdLS = 0.386133;
const double w_LS = 3.17016;
const double w_acry = 2.84273;


// MO spill-in
const double nH_spillin = 1;
const double nC_spillin = 1;

// Selection efficiency
// Trigger+Ep
//const Double_e nH_Epeff(0.761544,0.0019104973);     // syst no MO gen
//const Double_e nC_Epeff(0.755373,0.0018384776);     // syst no MO gen
//const Double_e nGd_Epeff(0.947208,0.0020518285);    // syst no MO gen
const Double_e nH_Epeff(0.745136,0.0019104973);     // syst no MO gen cap
const Double_e nC_Epeff(0.735014,0.0018384776);     // syst no MO gen cap
const Double_e nGd_Epeff(0.9472,0.0020518285);    // syst no MO gen cap
// dr
const Double_e nH_dreff(0.734396,0.0056044625);     // syst*
const Double_e nC_dreff(0.699494,0.0056044625);     // syst*
const Double_e nGd_dreff(0.824677,0.0056044625);    // syst*
// dt
const Double_e nH_dteff(0.87493,0.0037163854);            // syst
const Double_e nC_dteff(0.871586,0.0037534958);           // syst
const Double_e nGd_dteff(0.995302,0);                   // syst
// Ed
const Double_e nH_Edeff(0.838077,0.0026870058);     // syst
Double_e nC_Edeff(0.799292,0.0132855);       // syst
//const Double_e nC_Edeff(0.83391608,0.010727845);       // syst, single gamma
//const Double_e nC_Edeff(0.7349,0);       // syst, smear
const Double_e nGd_Edeff(0.9262,0.0011180340);       // syst


// Detector material
Volume GdLS;
Volume LS;
Volume Acrylic;


// Measurement
/*const array<Double_e,6> nH_can = {Double_e(), Double_e(561277,749.18422), Double_e(641035,800.64661), Double_e(609935,780.98335),
                                  Double_e(529655,727.774), Double_e()};    // stat
const array<Double_e,6> nC_can = {Double_e(), Double_e(37745,194.28072), Double_e(43512,208.5953), Double_e(40215,200.53678),
                                  Double_e(35869,189.39113), Double_e()};  // stat
const array<Double_e,6> nGd_can = {Double_e(), Double_e(623684,789.73666), Double_e(720136,848.60827), Double_e(669621,818.30373),
                                   Double_e(589858,768.02214), Double_e()}; // stat
const array<Double_e,6> nH_acc = {Double_e(), Double_e(63142.9,25.9288), Double_e(69142.6,26.875), Double_e(69126.8,26.4313),
                                  Double_e(59516.1,24.4945), Double_e()};   // stat
const array<Double_e,6> nC_acc = {Double_e(), Double_e(176.902,0.0726428), Double_e(192.988,0.0750123), Double_e(194.184,0.074248),
                                  Double_e(165.68,0.0681873), Double_e()};   // stat
const array<Double_e,6> nGd_acc = {Double_e(), Double_e(45.3958,0.0186412), Double_e(49.7339,0.019331), Double_e(41.1358,0.0157287),
                                  Double_e(33.875,0.0139416), Double_e()};   // stat
const array<Double_e,6> nH_lkg = {Double_e(), Double_e(2738.84,52.3339), Double_e(3022.82,54.9802), Double_e(2771.08,52.6411),
                                  Double_e(2501.06,50.0106), Double_e()};     // stat
const array<Double_e,6> nC_lkg = {Double_e(), Double_e(32570.7,180.474), Double_e(37255,193.016), Double_e(34105.2,184.676),
                                  Double_e(30347.8,174.206), Double_e()};       // stat*/

const array<Double_e,6> nH_can = {Double_e(), Double_e(561277,0), Double_e(641035,0), Double_e(609935,0),
                                  Double_e(529655,0), Double_e()};    // syst
const array<Double_e,6> nC_can = {Double_e(), Double_e(37745,0), Double_e(43512,0), Double_e(40215,0),
                                  Double_e(35869, 0), Double_e()};  // syst
const array<Double_e,6> nGd_can = {Double_e(), Double_e(623684,0), Double_e(720136,0), Double_e(669621,0),
                                   Double_e(589858,0), Double_e()}; // syst
const array<Double_e,6> nH_acc = {Double_e(), Double_e(63142.9,1634.99), Double_e(69142.6,1636.35), Double_e(69126.8,564.083),
                                  Double_e(59516.1,537.66), Double_e()};   // syst
const array<Double_e,6> nC_acc = {Double_e(), Double_e(176.902,4.58063), Double_e(192.988,4.56732), Double_e(194.184,1.58456),
                                  Double_e(165.68,1.49673), Double_e()};   // syst
const array<Double_e,6> nGd_acc = {Double_e(), Double_e(45.3958,1.17546), Double_e(49.7339,1.17702), Double_e(41.1358,0.335673),
                                  Double_e(33.875,0.306022), Double_e()};   // syst
const array<Double_e,6> nH_lkg = {Double_e(), Double_e(2738.84,251.71), Double_e(3022.82,429.61), Double_e(2771.08,422.18),
                                  Double_e(2501.06,311.72), Double_e()};     // syst
array<Double_e,6> nC_lkg = {Double_e(), Double_e(32570.7,12.), Double_e(37255,359.9), Double_e(34105.2,694.2),
                                  Double_e(30347.8,305.3), Double_e()};       // syst

void nCCScalculation(){


    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    for(int ad = 1; ad<5; ad++){
        GdLS = GdLS + Volume(ad, 1, txtfile);
        LS = LS + Volume(ad, 2, txtfile);
        Acrylic = Acrylic + Volume(ad, 3, txtfile);
    }



    array<Double_e,6> nH_evt;
    array<Double_e,6> nC_evt;
    array<Double_e,6> nGd_evt;
    for(int ad = 1; ad<5; ad++){
        nC_lkg.at(ad).SetError(0);
        nH_evt.at(ad) = (nH_can.at(ad) - nH_acc.at(ad) - nH_lkg.at(ad)) / nH_spillin;
        nC_evt.at(ad) = (nC_can.at(ad) - nC_acc.at(ad) - nC_lkg.at(ad)) / nC_spillin;
        nGd_evt.at(ad) = nGd_can.at(ad) - nGd_acc.at(ad);

        nH_evt.at(0) += nH_evt.at(ad);
        nC_evt.at(0) += nC_evt.at(ad);
        nGd_evt.at(0) += nGd_evt.at(ad);
    }
    nC_Edeff.SetError(0);

    cout << "nC events = " << nC_evt.at(0) << endl;

    // syst
    const Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
    const Double_e nC_eff = nC_Epeff*nC_dreff*nC_dteff*nC_Edeff;
    const Double_e nGd_eff = nGd_Epeff*nGd_dreff*nGd_dteff*nGd_Edeff;

    
    //const Double_e ExpnH = correction*GdLS.GetHboth()*nH_CS.at(0) + LS.GetHboth()*nH_CS.at(1) + Acrylic.GetHboth()*nH_CS.at(2);
    //const Double_e ExpnC = correction*GdLS.GetCboth()*nC_CS.at(0) + LS.GetCboth()*nC_CS.at(1) + Acrylic.GetCboth()*nC_CS.at(2);
    const Double_e ExpnH = w_GdLS*GdLS.GetHboth()*nH_CS.at(0) + w_LS*LS.GetHboth()*nH_CS.at(1) + w_acry*Acrylic.GetHboth()*nH_CS.at(2);
    const Double_e ExpnC = w_GdLS*GdLS.GetCboth()*nC_CS.at(0) + w_LS*LS.GetCboth()*nC_CS.at(1) + w_acry*Acrylic.GetCboth()*nC_CS.at(2);
    const Double_e ExpnGd = w_GdLS*(GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0));
    //const Double_e Catom = correction*GdLS.GetCboth() + LS.GetCboth() + Acrylic.GetCboth();
    const Double_e Catom = w_GdLS*GdLS.GetCboth() + w_LS*LS.GetCboth() + w_acry*Acrylic.GetCboth();

    
    // stat
    /*Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
    Double_e nC_eff = nC_Epeff*nC_dreff*nC_dteff*nC_Edeff;
    Double_e nGd_eff = nGd_Epeff*nGd_dreff*nGd_dteff*nGd_Edeff;
    Double_e ExpnH = w_GdLS*GdLS.GetHboth()*nH_CS.at(0) + w_LS*LS.GetHboth()*nH_CS.at(1) + w_acry*Acrylic.GetHboth()*nH_CS.at(2);
    Double_e ExpnC = w_GdLS*GdLS.GetCboth()*nC_CS.at(0) + w_LS*LS.GetCboth()*nC_CS.at(1) + w_acry*Acrylic.GetCboth()*nC_CS.at(2);
    Double_e ExpnGd = w_GdLS*(GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0));
    Double_e Catom = w_GdLS*GdLS.GetCboth() + w_LS*LS.GetCboth() + w_acry*Acrylic.GetCboth();
    nH_eff.SetError(0);
    nC_eff.SetError(0);
    nGd_eff.SetError(0);
    ExpnH.SetError(0);
    ExpnC.SetError(0);
    ExpnGd.SetError(0);
    Catom.SetError(0);*/


    cout << "exp nH = " << ExpnH << endl;
    cout << "C atom = " << Catom << endl;
    cout << "effH = " << nH_eff << endl;
    cout << "effC = " << nC_eff << endl;
    cout << "effGd = " << nGd_eff << endl;


    Double_e result1 = (nC_evt.at(0)/nH_evt.at(0)) * (ExpnH/Catom) *(nH_eff/nC_eff);
    Double_e result2 = (nC_evt.at(0)/nGd_evt.at(0)) * (ExpnGd/Catom) *(nGd_eff/nC_eff);


    cout << "From nC/nH : nC CS = " << 1e3*result1 << " mb" << endl;
    cout << "From nC/nGd : nC CS = " << 1e3*result2 << " mb" << endl;
    cout << "Theoretical : nC CS = " << 1e3*ExpnC/Catom << " mb" << endl;



}



