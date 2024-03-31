#ifndef AllMeasurement_h
#define AllMeasurement_h

#include "/Users/chengyuchin/Analysis/nC/EndGame/Volume.h"


// Average CS in GdLS, LS, Acrylic
const array<Double_e,3> nH_CS_th = {Double_e(0.253996,0.000769066), Double_e(0.311809, 0.000872109), Double_e(0.347539, 0.000938592)};  // syst vol ele
const array<Double_e,3> nC_CS_th = {Double_e(0.00423111,5.34559e-05), Double_e(0.00600734, 6.11888e-05), Double_e(0.00703724, 7.81217e-05)};// syst vol ele rebin(100)
//const array<Double_e,3> nC_CS = {Double_e(0.0042944,2.716e-05), Double_e(0.00656089, 2.32799e-05), Double_e(0.00798453, 6.7131e-05)};// syst vol ele rebin(10)
const array<Double_e,3> nGd155_CS_th = {Double_e(54510.9,247.894), Double_e(), Double_e()};    // syst vol ele
const array<Double_e,3> nGd157_CS_th = {Double_e(218319,587.017), Double_e(), Double_e()};     // syst vol ele


// Volume weight
/*const Double_e w_GdLS(0.386096,0.00443092);
const Double_e w_LS(3.16965,0.0255612);
const Double_e w_acry(2.8418,0.0125431);*/

// MO spill-in
const double nH_spillin = 1;
const double nC_spillin = 1;

// Selection efficiency
// Trigger+Ep
//const Double_e nH_Epeff_uc(0.761544,0.0014);     // syst no MO gen
//const Double_e nC_Epeff_uc(0.755373,0.0013);     // syst no MO gen
//const Double_e nGd_Epeff_uc(0.947208,0.0015);    // syst no MO gen
const Double_e nH_Epeff_uc(0.745136,0.0014655);     // syst no MO gen cap
const Double_e nC_Epeff_uc(0.735014,0.001302);     // syst no MO gen cap
const Double_e nGd_Epeff_uc(0.9472,0.001607);    // syst no MO gen cap

//const Double_e nH_Epeff_c(0.761544,0.0013);     // syst no MO gen
//const Double_e nC_Epeff_c(0.755373,0.0013);     // syst no MO gen
//const Double_e nGd_Epeff_c(0.947208,0.0014);    // syst no MO gen
const Double_e nH_Epeff_c(0.745136,0.0014655);     // syst no MO gen cap
const Double_e nC_Epeff_c(0.735014,0.001302);     // syst no MO gen cap
const Double_e nGd_Epeff_c(0.9472,0.001607);    // syst no MO gen cap
// dr
const Double_e nH_dreff_uc(0.75316,0.0021);     // syst
const Double_e nC_dreff_uc(0.704756,0.0021);     // syst
const Double_e nGd_dreff_uc(0.826125,0.0021);    // syst
const Double_e nH_dreff_c(0.75316,0.0022);     // syst
const Double_e nC_dreff_c(0.704756,0.0022);     // syst
const Double_e nGd_dreff_c(0.826125,0.0022);    // syst
// dt
const Double_e nH_dteff_uc(0.874204,0.0036);            // syst
const Double_e nC_dteff_uc(0.870393,0.0036);           // syst
const Double_e nGd_dteff_uc(0.994837,0);                   // syst
const Double_e nH_dteff_c(0.874204,0.0011);            // syst
const Double_e nC_dteff_c(0.870393,0.0011);           // syst
const Double_e nGd_dteff_c(0.994837,0);                   // syst
// Ed
const Double_e nH_Edeff_uc(0.817876,0.00218981);     // syst
const Double_e nC_Edeff_uc(0.764293,0.0124308);       // syst
const Double_e nGd_Edeff_uc(0.92501,0.000784239);       // syst
const Double_e nH_Edeff_c(0.817876,0.00218981);     // syst
const Double_e nC_Edeff_c(0.764293,0.00868966);       // syst
const Double_e nGd_Edeff_c(0.92501,0.000394302);       // syst
// All
const Double_e nH_eff_uc = nH_Epeff_uc*nH_dreff_uc*nH_dteff_uc*nH_Edeff_uc;
const Double_e nC_eff_uc = nC_Epeff_uc*nC_dreff_uc*nC_dteff_uc*nC_Edeff_uc;
const Double_e nGd_eff_uc = nGd_Epeff_uc*nGd_dreff_uc*nGd_dteff_uc*nGd_Edeff_uc;
const Double_e nH_eff_c = nH_Epeff_c*nH_dreff_c*nH_dteff_c*nH_Edeff_c;
const Double_e nC_eff_c = nC_Epeff_c*nC_dreff_c*nC_dteff_c*nC_Edeff_c;
const Double_e nGd_eff_c = nGd_Epeff_c*nGd_dreff_c*nGd_dteff_c*nGd_Edeff_c;


// Detector material
array<Volume,6> GdLS;
array<Volume,6> LS;
array<Volume,6> Acrylic;



// Measurement
const array<Double_e,6> nH_can_sta = {Double_e(), Double_e(561277,749.18422), Double_e(641035,800.64661), Double_e(609935,780.98335),
                                  Double_e(529655,727.774), Double_e()};    // stat
const array<Double_e,6> nC_can_sta = {Double_e(), Double_e(34846,186.67083), Double_e(40118,200.29478), Double_e(37159, 192.7667),
                                  Double_e(33097, 181.92581), Double_e()};  // stat
const array<Double_e,6> nGd_can_sta = {Double_e(), Double_e(623684,789.73666), Double_e(720136,848.60827), Double_e(669621,818.30373),
                                   Double_e(589858,768.02214), Double_e()}; // stat
const array<Double_e,6> nH_acc_sta = {Double_e(), Double_e(63142.9,25.9288), Double_e(69142.6,26.875), Double_e(69126.8,26.4313),
                                  Double_e(59516.1,24.4945), Double_e()};   // stat
const array<Double_e,6> nC_acc_sta = {Double_e(), Double_e(97.5211,0.0400458), Double_e(108.508,0.0421759), Double_e(107.402,0.0410661),
                                  Double_e(89.9673,0.037027), Double_e()};   // stat
const array<Double_e,6> nGd_acc_sta = {Double_e(), Double_e(45.3958,0.0186412), Double_e(49.7339,0.019331), Double_e(41.1358,0.0157287),
                                  Double_e(33.875,0.0139416), Double_e()};   // stat
const array<Double_e,6> nH_lkg_sta = {Double_e(), Double_e(2746.58,52.4078), Double_e(3092.52,55.6105), Double_e(2816.82,53.0737),
                                  Double_e(2557.7,50.5737), Double_e()};     // stat
const array<Double_e,6> nC_lkg_sta = {Double_e(), Double_e(29730.4,172.425), Double_e(34307.8,185.224), Double_e(31334.2,177.015),
                                  Double_e(27930.8,167.125), Double_e()};       // stat

const array<Double_e,6> nH_can_sys = {Double_e(), Double_e(561277,0), Double_e(641035,0), Double_e(609935,0),
                                  Double_e(529655,0), Double_e()};    // syst
const array<Double_e,6> nC_can_sys = {Double_e(), Double_e(34846,0), Double_e(40118,0), Double_e(37159,0),
                                  Double_e(33097, 0), Double_e()};  // syst
const array<Double_e,6> nGd_can_sys = {Double_e(), Double_e(623684,0), Double_e(720136,0), Double_e(669621,0),
                                   Double_e(589858,0), Double_e()}; // syst
const array<Double_e,6> nH_acc_sys = {Double_e(), Double_e(63142.9,1634.99), Double_e(69142.6,1636.35), Double_e(69126.8,564.083),
                                  Double_e(59516.1,537.66), Double_e()};   // syst
const array<Double_e,6> nC_acc_sys = {Double_e(), Double_e(97.5211,2.52517), Double_e(108.508,2.56799), Double_e(107.402,0.876411),
                                  Double_e(89.9673,0.812752), Double_e()};   // syst
const array<Double_e,6> nGd_acc_sys = {Double_e(), Double_e(45.3958,1.17546), Double_e(49.7339,1.17702), Double_e(41.1358,0.335673),
                                  Double_e(33.875,0.306022), Double_e()};   // syst
const array<Double_e,6> nH_lkg_sys = {Double_e(), Double_e(2746.58,242.61), Double_e(3092.52,364.22), Double_e(2816.82,386.4),
                                  Double_e(2557.7,259.75), Double_e()};     // syst
const array<Double_e,6> nC_lkg_sys = {Double_e(), Double_e(29730.4,123), Double_e(34307.8,102.1), Double_e(31334.2,342.3),
                                  Double_e(27930.8,48), Double_e()};       // syst


// for pull
const array<double,5> sys_acc = {0, nH_acc_sys.at(1).GetError()/nH_acc_sys.at(1).GetValue(), nH_acc_sys.at(2).GetError()/nH_acc_sys.at(2).GetValue(),
                                 nH_acc_sys.at(3).GetError()/nH_acc_sys.at(3).GetValue(), nH_acc_sys.at(4).GetError()/nH_acc_sys.at(4).GetValue()};
const array<double,5> sys_lkg_H = {0, nH_lkg_sys.at(1).GetError()/nH_lkg_sys.at(1).GetValue(), nH_lkg_sys.at(2).GetError()/nH_lkg_sys.at(2).GetValue(),
                                 nH_lkg_sys.at(3).GetError()/nH_lkg_sys.at(3).GetValue(), nH_lkg_sys.at(4).GetError()/nH_lkg_sys.at(4).GetValue()};
const array<double,5> sys_lkg_C = {0, nC_lkg_sys.at(1).GetError()/nC_lkg_sys.at(1).GetValue(), nC_lkg_sys.at(2).GetError()/nC_lkg_sys.at(2).GetValue(),
                                 nC_lkg_sys.at(3).GetError()/nC_lkg_sys.at(3).GetValue(), nC_lkg_sys.at(4).GetError()/nC_lkg_sys.at(4).GetValue()};
const array<double,5> sys_GdLS_H = {0, 0.31/12.01, 0.38/11.97, 0.14/11.95, 0.13/11.95};
const array<double,5> sys_GdLS_C = {0, 0.94/87.85, 0.91/87.91, 0.92/88.02, 0.92/87.9};
const array<double,5> sys_GdLS_Gd = {0, 0.0003/0.1031, 0.0006/0.1029, 0.0009/0.1032, 0.0005/0.1034};
const array<double,5> sys_LS_H = {0, 0.13/11.91, 0.12/11.98, 0.13/11.89, 0.13/11.93};
const array<double,5> sys_LS_C = {0, 0.93/88.00, 0.92/88.09, 0.92/88.16, 0.88/88.08};
const double sys_eff_H_corr = nH_eff_c.GetError()/nH_eff_c.GetValue();
const double sys_eff_C_corr = nC_eff_c.GetError()/nC_eff_c.GetValue();
const double sys_eff_Gd_corr = nGd_eff_c.GetError()/nGd_eff_c.GetValue();
const double sys_eff_H_uncorr = nH_eff_uc.GetError()/nH_eff_uc.GetValue();
const double sys_eff_C_uncorr = nC_eff_uc.GetError()/nC_eff_uc.GetValue();
const double sys_eff_Gd_uncorr = nGd_eff_uc.GetError()/nGd_eff_uc.GetValue();
const double sys_cs_H_GdLS = nH_CS_th.at(0).GetError()/nH_CS_th.at(0).GetValue();
const double sys_cs_H_LS = nH_CS_th.at(1).GetError()/nH_CS_th.at(1).GetValue();
const double sys_cs_H_acry = nH_CS_th.at(2).GetError()/nH_CS_th.at(2).GetValue();
const double sys_cs_Gd155 = nGd155_CS_th.at(0).GetError()/nGd155_CS_th.at(0).GetValue();
const double sys_cs_Gd157 = nGd157_CS_th.at(0).GetError()/nGd157_CS_th.at(0).GetValue();
const double sys_cs_C_GdLS = nC_CS_th.at(0).GetError()/nC_CS_th.at(0).GetValue();
const double sys_cs_C_LS = nC_CS_th.at(1).GetError()/nC_CS_th.at(1).GetValue();
const double sys_cs_C_acry = nC_CS_th.at(2).GetError()/nC_CS_th.at(2).GetValue();


#endif


