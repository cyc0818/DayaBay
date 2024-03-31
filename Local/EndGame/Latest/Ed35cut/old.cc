#include "/Users/chengyuchin/Analysis/nC/EndGame/GetCorrection.h"
#include "/Users/chengyuchin/Analysis/nC/EndGame/FluxIntegral.cc"
#include "/Users/chengyuchin/Analysis/nC/EndGame/Uncertainty.h"



// Average CS in GdLS, LS, Acrylic
const array<Double_e,3> nH_CS = {Double_e(0.316944,0.000956869), Double_e(0.312537, 0.000893118), Double_e(0.347018, 0.00145715)};  // syst
//const array<Double_e,3> nC_CS = {Double_e(0.00483085,4.e-6), Double_e(0.00481809, 4.32e-6), Double_e(0.00566645, 2.48433e-05)};  // syst vol
const array<Double_e,3> nC_CS = {Double_e(0.00424098,6.39e-05), Double_e(0.00601832, 6.98e-05), Double_e(0.0071953, 0.000184272)};  // syst vol ele
const array<Double_e,3> nGd155_CS = {Double_e(51196.1,236.874), Double_e(), Double_e()};    // syst 
const array<Double_e,3> nGd157_CS = {Double_e(210288,263.612), Double_e(), Double_e()};     // syst     

// Normalization const for flux in GdLS
const double correction = 0.134864;
//const double correction = 0.13362;
//const double correction = 1;


// MO spill-in
const double nH_spillin = 1;
const double nC_spillin = 1;
//const double nC_spillin = 0.98719371;

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
//const Double_e nC_Edeff(0.85955711,0.010739709);       // syst single gamma
//const Double_e nC_Edeff(0.778536,0);       // syst smear
const Double_e nGd_Edeff(0.925227,0.0011180340);       // syst


// Detector material
Volume GdLS;
Volume LS;
Volume Acrylic;


// Measurement
const array<Double_e,6> nH_can = {Double_e(), Double_e(561277,749.18422), Double_e(641035,800.64661), Double_e(609935,780.98335),
                                  Double_e(529655,727.774), Double_e()};    // stat
const array<Double_e,6> nC_can = {Double_e(), Double_e(39568,198.91707), Double_e(45435,213.15487), Double_e(42081,205.13654),
                                  Double_e(37531, 193.72919), Double_e()};  // stat
const array<Double_e,6> nGd_can = {Double_e(), Double_e(623684,789.73666), Double_e(720136,848.60827), Double_e(669621,818.30373),
                                   Double_e(589858,768.02214), Double_e()}; // stat
const array<Double_e,6> nH_acc = {Double_e(), Double_e(63133.868,25.539654), Double_e(69065.381,26.464554), Double_e(69228.404,26.070378),
                                  Double_e(59584.400,24.156522), Double_e()};   // stat
const array<Double_e,6> nC_acc = {Double_e(), Double_e(341.51992,0.13815565), Double_e(369.90723,0.14174149), Double_e(378.84585,0.14266766),
                                  Double_e(317.09303,0.12855487), Double_e()};   // stat
const array<Double_e,6> nGd_acc = {Double_e(), Double_e(46.917852,0.018979760), Double_e(51.698195,0.019809775), Double_e(40.992163,0.015437033),
                                  Double_e(34.591897,0.014024139), Double_e()};   // stat
const array<Double_e,6> nH_lkg = {Double_e(), Double_e(2747.93,52.420702), Double_e(3088.2,55.571575), Double_e(2806.86,52.979807),
                                  Double_e(2553.03,50.527517), Double_e()};     // stat
const array<Double_e,6> nC_lkg = {Double_e(), Double_e(34239.5,185.03919), Double_e(39420.6,198.54622), Double_e(35960.9,189.63359),
                                  Double_e(32114.1,179.20407), Double_e()};       // stat

/*const array<Double_e,6> nH_can = {Double_e(), Double_e(561277,0), Double_e(641035,0), Double_e(609935,0),
                                  Double_e(529655,0), Double_e()};    // syst
const array<Double_e,6> nC_can = {Double_e(), Double_e(39568,0), Double_e(45435,0), Double_e(42081,0),
                                  Double_e(37531, 0), Double_e()};  // syst
const array<Double_e,6> nGd_can = {Double_e(), Double_e(623684,0), Double_e(720136,0), Double_e(669621,0),
                                   Double_e(589858,0), Double_e()}; // syst
const array<Double_e,6> nH_acc = {Double_e(), Double_e(63133.868,1578.0058), Double_e(69065.381,1591.2180), Double_e(69228.404,749.70208),
                                  Double_e(59584.400,675.90756), Double_e()};   // syst
const array<Double_e,6> nC_acc = {Double_e(), Double_e(341.51992,8.5360387), Double_e(369.90723,8.5224037), Double_e(378.84585,4.1026733),
                                  Double_e(317.09303,3.5970082), Double_e()};   // syst
const array<Double_e,6> nGd_acc = {Double_e(), Double_e(46.917852,1.1726929), Double_e(51.698195,1.1910902), Double_e(40.992163,0.44392053),
                                  Double_e(34.591897,0.39240010), Double_e()};   // syst
const array<Double_e,6> nH_lkg = {Double_e(), Double_e(2747.93,242.61), Double_e(3088.2,364.22), Double_e(2806.86,386.4),
                                  Double_e(2553.03,259.75), Double_e()};     // syst
const array<Double_e,6> nC_lkg = {Double_e(), Double_e(34239.5,45.8), Double_e(39420.6,159.9), Double_e(35960.9,655.6),
                                  Double_e(32114.1,139.6), Double_e()};       // syst*/

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
        nH_evt.at(ad) = (nH_can.at(ad) - nH_acc.at(ad) - nH_lkg.at(ad)) * nH_spillin;
        nC_evt.at(ad) = (nC_can.at(ad) - nC_acc.at(ad) - nC_lkg.at(ad)) * nC_spillin;
        nGd_evt.at(ad) = nGd_can.at(ad) - nGd_acc.at(ad);

        nH_evt.at(0) += nH_evt.at(ad);
        nC_evt.at(0) += nC_evt.at(ad);
        nGd_evt.at(0) += nGd_evt.at(ad);
    }

    cout << "nC events = " << nC_evt.at(0) << endl;

    // syst
    /*const Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
    const Double_e nC_eff = nC_Epeff*nC_dreff*nC_dteff*nC_Edeff;
    const Double_e nGd_eff = nGd_Epeff*nGd_dreff*nGd_dteff*nGd_Edeff;

    
    const Double_e ExpnH = correction*GdLS.GetHboth()*nH_CS.at(0) + LS.GetHboth()*nH_CS.at(1) + Acrylic.GetHboth()*nH_CS.at(2);
    const Double_e ExpnC = correction*GdLS.GetCboth()*nC_CS.at(0) + LS.GetCboth()*nC_CS.at(1) + Acrylic.GetCboth()*nC_CS.at(2);
    const Double_e ExpnGd = correction*(GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0));
    const Double_e Catom = correction*GdLS.GetCboth() + LS.GetCboth() + Acrylic.GetCboth();

    cout << "exp nH = " << ExpnH << endl;
    cout << "C atom = " << Catom << endl;
    cout << "effH = " << nH_eff << endl;
    cout << "effC = " << nC_eff << endl;
    cout << "effGd = " << nGd_eff << endl;*/
    
    // stat
    Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
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
    Catom.SetError(0);


    Double_e result1 = (nC_evt.at(0)/nH_evt.at(0)) * (ExpnH/Catom) *(nH_eff/nC_eff);
    Double_e result2 = (nC_evt.at(0)/nGd_evt.at(0)) * (ExpnGd/Catom) *(nGd_eff/nC_eff);


    cout << "From nC/nH : nC CS = " << 1e3*result1 << " mb" << endl;
    cout << "From nC/nGd : nC CS = " << 1e3*result2 << " mb" << endl;
    cout << "Theoretical : nC CS = " << 1e3*ExpnC/Catom << " mb" << endl;



}



