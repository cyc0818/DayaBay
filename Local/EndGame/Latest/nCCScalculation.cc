#include "/Users/chengyuchin/Analysis/nC/EndGame/FluxIntegral.cc"
#include "/Users/chengyuchin/Analysis/nC/EndGame/Volume.h"



// Average CS in GdLS, LS, Acrylic
array<Double_e,3> nH_CS = {Double_e(0.253996,0.000769066), Double_e(0.311809, 0.000872109), Double_e(0.347539, 0.000938592)};  // syst vol ele
const array<Double_e,3> nC_CS = {Double_e(0.00423111,5.34559e-05), Double_e(0.00600734, 6.11888e-05), Double_e(0.00703724, 7.81217e-05)};// syst vol ele rebin(100)
//const array<Double_e,3> nC_CS = {Double_e(0.0042944,2.716e-05), Double_e(0.00656089, 2.32799e-05), Double_e(0.00798453, 6.7131e-05)};// syst vol ele rebin(10)
array<Double_e,3> nGd155_CS = {Double_e(54510.9,247.894), Double_e(), Double_e()};    // syst vol ele
array<Double_e,3> nGd157_CS = {Double_e(218319,587.017), Double_e(), Double_e()};     // syst vol ele

// Normalization const for flux in GdLS
//const double correction = 0.132547;     // vol ele
//const double correction = 0.134864;     // vol
//const double correction = 0.13362;    // vol
//const double correction = 0.121969;    // test
//const double correction2 = 0.907774;    // test
//const double correction = 0.121969;    // test
//const double correction2 = 0.907774;    // test


// Volume weight
//const double w_GdLS = 0.386096; // only near
//const double w_LS = 3.16965;
//const double w_acry = 2.8418;
const double w_GdLS = 0.387002;   // 8AD
const double w_LS = 3.16973;
const double w_acry = 2.8418;


// MO spill-in
const double nH_spillin = 1;
const double nC_spillin = 1;

// Selection efficiency
// Trigger+Ep
//const Double_e nH_Epeff(0.761544,0.0019104973);     // syst no MO gen
//const Double_e nC_Epeff(0.755373,0.0018384776);     // syst no MO gen
//const Double_e nGd_Epeff(0.947208,0.0020518285);    // syst no MO gen
const Double_e nH_Epeff(0.745136,0.00207253);     // syst no MO gen cap
const Double_e nC_Epeff(0.735014,0.0018413061);     // syst no MO gen cap
const Double_e nGd_Epeff(0.9472,0.0022726412);    // syst no MO gen cap
// dr
const Double_e nH_dreff(0.75316,0.0030413813);     // syst
const Double_e nC_dreff(0.704756,0.0030413813);     // syst
const Double_e nGd_dreff(0.826125,0.0030413813);    // syst
// dt
const Double_e nH_dteff(0.874204,0.0035938932);            // syst
const Double_e nC_dteff(0.870393,0.0035938932);           // syst
const Double_e nGd_dteff(0.994837,0);                   // syst
// Ed
const Double_e nH_Edeff(0.817876,0.0030968590);     // syst
const Double_e nC_Edeff(0.764293,0.0151669);       // syst
const Double_e nGd_Edeff(0.92501,0.00087778407);       // syst


// Detector material
Volume GdLS;
Volume LS;
Volume Acrylic;


// Measurement
/*const array<Double_e,9> nH_can = {Double_e(), Double_e(561277,749.18422), Double_e(641035,800.64661), Double_e(609935,780.98335),
                                  Double_e(529655,727.774), Double_e(156875,396.07449), Double_e(158326,397.90200),
                                  Double_e(159473,399.34071), Double_e(139139,373.01340)};    // stat
const array<Double_e,9> nC_can = {Double_e(), Double_e(34846,186.67083), Double_e(40118,200.29478), Double_e(37159, 192.7667),
                                  Double_e(33097, 181.92581), Double_e(5527,74.343796), Double_e(5589,74.759615),
                                  Double_e(5549,74.491610), Double_e(4960,70.427267)};  // stat
const array<Double_e,9> nGd_can = {Double_e(), Double_e(623684,789.73666), Double_e(720136,848.60827), Double_e(669621,818.30373),
                                   Double_e(589858,768.02214), Double_e(95788,309.49637), Double_e(96333,310.37558),
                                   Double_e(95660,309.28951), Double_e(86012,293.27803)}; // stat
const array<Double_e,9> nH_acc = {Double_e(), Double_e(63142.9,25.9288), Double_e(69142.6,26.875), Double_e(69126.8,26.4313),
                                  Double_e(59516.1,24.4945), Double_e(76612.9,27.8384), Double_e(79426.9,28.4733),
                                  Double_e(80337.7,28.8227), Double_e(68894.8,26.3629)};   // stat
const array<Double_e,9> nC_acc = {Double_e(), Double_e(97.5211,0.0400458), Double_e(108.508,0.0421759), Double_e(107.402,0.0410661),
                                  Double_e(89.9673,0.037027), Double_e(121.929,0.0443047), Double_e(100.104,0.0358856),
                                  Double_e(107.676,0.0386307), Double_e(84.5418,0.0323503)};   // stat
const array<Double_e,9> nGd_acc = {Double_e(), Double_e(45.3958,0.0186412), Double_e(49.7339,0.019331), Double_e(41.1358,0.0157287),
                                  Double_e(33.875,0.0139416), Double_e(8.00662,0.00290932), Double_e(8.08304,0.00289765),
                                  Double_e(8.39234,0.00301091), Double_e(6.28805,0.00240615)};   // stat
const array<Double_e,9> nH_lkg = {Double_e(), Double_e(2746.58,52.4078), Double_e(3092.52,55.6105), Double_e(2816.82,53.0737),
                                  Double_e(2557.7,50.5737), Double_e(1810.675,42.552), Double_e(0,0),
                                  Double_e(0,0), Double_e(0,0)};     // stat
const array<Double_e,9> nC_lkg = {Double_e(), Double_e(29730.4,172.425), Double_e(34307.8,185.224), Double_e(31334.2,177.015),
                                  Double_e(27930.8,167.125), Double_e(18191.7,134.877), Double_e(0,0),
                                  Double_e(0,0), Double_e(0,0)};       // stat*/

const array<Double_e,9> nH_can = {Double_e(), Double_e(561277,0), Double_e(641035,0), Double_e(609935,0),
                                  Double_e(529655,0), Double_e(156875,0), Double_e(158326,0),
                                  Double_e(159473,0), Double_e(139139,0)};    // syst
const array<Double_e,9> nC_can = {Double_e(), Double_e(34846,0), Double_e(40118,0), Double_e(37159,0),
                                  Double_e(33097, 0), Double_e(5527,0), Double_e(5589,0),
                                  Double_e(5549,0), Double_e(4960,0)};  // syst
const array<Double_e,9> nGd_can = {Double_e(), Double_e(623684,0), Double_e(720136,0), Double_e(669621,0),
                                   Double_e(589858,0), Double_e(95788,0), Double_e(96333,0),
                                   Double_e(95660,0), Double_e(86012,0)}; // syst
array<Double_e,9> nH_acc = {Double_e(), Double_e(63142.9,1634.99), Double_e(69142.6,1636.35), Double_e(69126.8,564.083),
                            Double_e(59516.1,537.66), Double_e(76612.9,703.623), Double_e(79426.9,852.079),
                            Double_e(80337.7,852.471), Double_e(68894.8,678.703)};   // syst
array<Double_e,9> nC_acc = {Double_e(), Double_e(97.5211,2.52517), Double_e(108.508,2.56799), Double_e(107.402,0.876411),
                            Double_e(89.9673,0.812752), Double_e(121.929,1.11981), Double_e(100.104,1.07389),
                            Double_e(107.676,1.14256), Double_e(84.5418,0.832847)};   // syst
array<Double_e,9> nGd_acc = {Double_e(), Double_e(45.3958,1.17546), Double_e(49.7339,1.17702), Double_e(41.1358,0.335673),
                            Double_e(33.875,0.306022), Double_e(8.00662,0.0735338), Double_e(8.08304,0.0867135),
                            Double_e(8.39234,0.0890519), Double_e(6.28805,0.0619455)};   // syst
array<Double_e,9> nH_lkg = {Double_e(), Double_e(2746.58,116.79762), Double_e(3092.52,170.05919), Double_e(2816.82,176.431),
                                  Double_e(2557.7,121.482), Double_e(1810.675,13.564), Double_e(0,0),
                                  Double_e(0,0), Double_e(0,0)};     // syst
array<Double_e,9> nC_lkg = {Double_e(), Double_e(29730.4,60.227), Double_e(34307.8,62.386), Double_e(31334.2,147.255),
                                  Double_e(27930.8,34.7067), Double_e(18191.7,259.77276), Double_e(0,0),
                                  Double_e(0,0), Double_e(0,0)};       // syst

void nCCScalculation(){


    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data2.txt";
    for(int ad = 1; ad<9; ad++){
        GdLS = GdLS + Volume(ad, 1, txtfile);
        LS = LS + Volume(ad, 2, txtfile);
        Acrylic = Acrylic + Volume(ad, 3, txtfile);
    }



    array<Double_e,9> nH_evt;
    array<Double_e,9> nC_evt;
    array<Double_e,9> nGd_evt;
    for(int ad = 1; ad<9; ad++){
        // uncertainty on/off
        if(ad<nH_acc.size()) nH_acc.at(ad).SetError(0);
        if(ad<nGd_acc.size()) nGd_acc.at(ad).SetError(0);
        if(ad<nC_acc.size()) nC_acc.at(ad).SetError(0);
        if(ad<nC_lkg.size()) nC_lkg.at(ad).SetError(0);
        if(ad<nH_lkg.size()) nH_lkg.at(ad).SetError(0);
        //if(ad<nC_lkg.size()) nC_lkg.at(ad).SetError(nC_lkg.at(ad).GetError());
        //if(ad<nH_lkg.size()) nH_lkg.at(ad).SetError(nH_lkg.at(ad).GetError());


        nH_evt.at(ad) = (nH_can.at(ad) - nH_acc.at(ad) - nH_lkg.at(ad)) / nH_spillin;
        nC_evt.at(ad) = (nC_can.at(ad) - nC_acc.at(ad) - nC_lkg.at(ad)) / nC_spillin;
        nGd_evt.at(ad) = nGd_can.at(ad) - nGd_acc.at(ad);
        cout << "ad = " << ad << " , nC events = " << nC_evt.at(ad) << endl;

        nH_evt.at(0) += nH_evt.at(ad);
        nC_evt.at(0) += nC_evt.at(ad);
        nGd_evt.at(0) += nGd_evt.at(ad);
    }
    //nC_Edeff.SetError(0);

    cout << "nC events = " << nC_evt.at(0) << endl;
    cout << "measured ratio = " << nC_evt.at(0)/nGd_evt.at(0) << endl;

    // syst
    Double_e nH_eff = nH_Epeff*nH_dreff*nH_dteff*nH_Edeff;
    Double_e nC_eff = nC_Epeff*nC_dreff*nC_dteff*nC_Edeff;
    Double_e nGd_eff = nGd_Epeff*nGd_dreff*nGd_dteff*nGd_Edeff;


    // uncertainty on/off
    for(int i = 0; i<9; i++){
        if(i<nGd155_CS.size()) nGd155_CS.at(i).SetError(0);
        if(i<nGd157_CS.size()) nGd157_CS.at(i).SetError(0);
        if(i<nH_CS.size()) nH_CS.at(i).SetError(0);
    }
    nH_eff.SetError(0);
    nGd_eff.SetError(0);
    nC_eff.SetError(0);
    GdLS.ErrorOff();
    LS.ErrorOff();
    Acrylic.ErrorOff();

    
    //const Double_e ExpnH = correction*GdLS.GetHboth()*nH_CS.at(0) + LS.GetHboth()*nH_CS.at(1) + Acrylic.GetHboth()*nH_CS.at(2);
    //const Double_e ExpnC = correction*GdLS.GetCboth()*nC_CS.at(0) + LS.GetCboth()*nC_CS.at(1) + Acrylic.GetCboth()*nC_CS.at(2);
    const Double_e ExpnH = w_GdLS*GdLS.GetHboth()*nH_CS.at(0) + w_LS*LS.GetHboth()*nH_CS.at(1) + w_acry*Acrylic.GetHboth()*nH_CS.at(2);
    const Double_e ExpnC = w_GdLS*GdLS.GetCboth()*nC_CS.at(0) + w_LS*LS.GetCboth()*nC_CS.at(1) + w_acry*Acrylic.GetCboth()*nC_CS.at(2);
    const Double_e ExpnGd = w_GdLS*(GdLS.GetGdboth(155)*nGd155_CS.at(0) + GdLS.GetGdboth(157)*nGd157_CS.at(0));
    //const Double_e Catom = correction*GdLS.GetCboth() + LS.GetCboth() + Acrylic.GetCboth();
    const Double_e Catom = w_GdLS*GdLS.GetCboth() + w_LS*LS.GetCboth() + w_acry*Acrylic.GetCboth();

    cout << "nH in LS fraction = " << (w_LS*LS.GetHboth()*nH_CS.at(1)+w_acry*Acrylic.GetHboth()*nH_CS.at(2))/ExpnH << endl;
    cout << "nC in LS fraction = " << (w_LS*LS.GetCboth()*nC_CS.at(1)+w_acry*Acrylic.GetCboth()*nC_CS.at(2))/ExpnC << endl;
    
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


    cout << "exp nGd = " << nGd_eff*ExpnGd << endl;
    cout << "C atom = " << Catom << endl;
    cout << "effH = " << nH_eff << endl;
    cout << "effC = " << nC_eff << endl;
    cout << "effGd = " << nGd_eff << endl;
    
    cout << "test factor = " << w_LS*LS.GetHboth()*nH_CS.at(1)/(w_GdLS*GdLS.GetHboth()*nH_CS.at(0).GetValue()+w_LS*LS.GetHboth()*nH_CS.at(1)) << endl;
    cout << "test factor C = " << w_LS*LS.GetCboth()*nC_CS.at(1)/(w_GdLS*GdLS.GetCboth()*nC_CS.at(0)+w_LS*LS.GetCboth()*nC_CS.at(1)) << endl;


    Double_e result1 = (nC_evt.at(0)/nH_evt.at(0)) * (ExpnH/Catom) * (nH_eff/nC_eff);
    Double_e result2 = (nC_evt.at(0)/nGd_evt.at(0)) * (ExpnGd/Catom) * (nGd_eff/nC_eff);


    cout << "Expected nC/nH (%) = " << ExpnC*nC_eff/ExpnH/nH_eff*100. << endl;
    cout << "Measured nC/nH (%) = " << nC_evt.at(0)/nH_evt.at(0)*100. << endl;
    cout << "Expected nC/nGd (%) = " << ExpnC*nC_eff/ExpnGd/nGd_eff*100. << endl;
    cout << "Measured nC/nGd (%) = " << nC_evt.at(0)/nGd_evt.at(0)*100. << endl;
    cout << "From nC/nH : nC CS = " << 1e3*result1 << " mb" << endl;
    cout << "From nC/nGd : nC CS = " << 1e3*result2 << " mb" << endl;
    cout << "Average : nC CS = " << 1e3*(result1+result2)/2. << " mb" << endl;
    cout << "Theoretical : nC CS = " << 1e3*ExpnC/Catom << " mb" << endl;



}



