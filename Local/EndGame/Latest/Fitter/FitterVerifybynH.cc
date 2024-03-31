#include "/Users/chengyuchin/Analysis/nC/EndGame/Latest/AllMeasurement.h"

using namespace std;


double HGdRatio(int AD);
void fitter(int& npar, double* gin, double& f, double* par, int iflag);


void FitterVerifybynH(){


    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    for(int ad = 1; ad<5; ad++){
        GdLS.at(ad) = Volume(ad, 1, txtfile);
        LS.at(ad) = Volume(ad, 2, txtfile);
        Acrylic.at(ad) = Volume(ad, 3, txtfile);

        /*GdLS.at(0) = GdLS.at(0) + GdLS.at(ad);
        LS.at(0) = LS.at(0) + LS.at(ad);
        Acrylic.at(0) = Acrylic.at(0) + Acrylic.at(ad);*/
    }


    TMinuit* minimizer = new TMinuit(47);
    minimizer->SetFCN(fitter);
    minimizer->DefineParameter(0, "CS_nH_TarVol", 0.309176, 0.0002, 0.2, 0.4);
    minimizer->DefineParameter(1, "pull_acc_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(2, "pull_acc_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(3, "pull_acc_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(4, "pull_acc_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(5, "pull_lkg_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(6, "pull_lkg_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(7, "pull_lkg_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(8, "pull_lkg_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(9, "pull_GdLS_Gd_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(10, "pull_GdLS_Gd_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(11, "pull_GdLS_Gd_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(12, "pull_GdLS_Gd_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(13, "pull_GdLS_H_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(14, "pull_GdLS_H_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(15, "pull_GdLS_H_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(16, "pull_GdLS_H_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(17, "pull_GdLS_C_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(18, "pull_GdLS_C_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(19, "pull_GdLS_C_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(20, "pull_GdLS_C_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(21, "pull_LS_H_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(22, "pull_LS_H_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(23, "pull_LS_H_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(24, "pull_LS_H_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(25, "pull_LS_C_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(26, "pull_LS_C_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(27, "pull_LS_C_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(28, "pull_LS_C_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(29, "pull_eff_H_corr", 0, 0.01, -10, 10);
    minimizer->DefineParameter(30, "pull_eff_H_uncorr_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(31, "pull_eff_H_uncorr_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(32, "pull_eff_H_uncorr_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(33, "pull_eff_H_uncorr_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(34, "pull_eff_Gd_corr", 0, 0.01, -10, 10);
    minimizer->DefineParameter(35, "pull_eff_Gd_uncorr_1", 0, 0.01, -10, 10);
    minimizer->DefineParameter(36, "pull_eff_Gd_uncorr_2", 0, 0.01, -10, 10);
    minimizer->DefineParameter(37, "pull_eff_Gd_uncorr_3", 0, 0.01, -10, 10);
    minimizer->DefineParameter(38, "pull_eff_Gd_uncorr_4", 0, 0.01, -10, 10);
    minimizer->DefineParameter(39, "pull_cs_H_GdLS", 0, 0.01, -10, 10);
    minimizer->DefineParameter(40, "pull_cs_H_LS", 0, 0.01, -10, 10);
    minimizer->DefineParameter(41, "pull_cs_H_acry", 0, 0.01, -10, 10);
    minimizer->DefineParameter(42, "pull_cs_Gd155", 0, 0.01, -10, 10);
    minimizer->DefineParameter(43, "pull_cs_Gd157", 0, 0.01, -10, 10);
    minimizer->DefineParameter(44, "pull_cs_C_GdLS", 0, 0.01, -10, 10);
    minimizer->DefineParameter(45, "pull_cs_C_LS", 0, 0.01, -10, 10);
    minimizer->DefineParameter(46, "pull_cs_C_acry", 0, 0.01, -10, 10);
    //for(int i = 1; i<47; i++) minimizer->FixParameter(i);
    //minimizer->DefineParameter(1, "CS_nH_GdLS", 0.25429, 0.000785367, 0.15, 1);
    //minimizer->DefineParameter(2, "CS_nH_LS", 0.311837, 0.000886436, 0.25, 1);
    //minimizer->DefineParameter(3, "CS_nH_Acrylic", 0.343103, 0.0012552, 0.2, 1);
    minimizer->Command("MIGRAD");
    minimizer->Command("MIGRAD");
    minimizer->Command("MINOS");






}








void fitter(int& npar, double* gin, double& f, double* par, int iflag){

    f = 0.;

    const double CS_nH_TarVol = par[0];
    const array<double,5> pull_acc = {0, par[1], par[2], par[3], par[4]};
    const array<double,5> pull_lkg = {0, par[5], par[6], par[7], par[8]};
    const array<double,5> pull_GdLS_Gd = {0, par[9], par[10], par[11], par[12]};
    const array<double,5> pull_GdLS_H = {0, par[13], par[14], par[15], par[16]};
    const array<double,5> pull_GdLS_C = {0, par[17], par[18], par[19], par[20]};
    const array<double,5> pull_LS_H = {0, par[21], par[22], par[23], par[24]};
    const array<double,5> pull_LS_C = {0, par[25], par[26], par[27], par[28]};
    const double pull_eff_H_corr = par[29];
    const array<double,5> pull_eff_H_uncorr = {0, par[30], par[31], par[32], par[33]};
    const double pull_eff_Gd_corr = par[34];
    const array<double,5> pull_eff_Gd_uncorr = {0, par[35], par[36], par[37], par[38]};
    const double pull_cs_H_GdLS = par[39];
    const double pull_cs_H_LS = par[40];
    const double pull_cs_H_acry = par[41];
    const double pull_cs_Gd155 = par[42];
    const double pull_cs_Gd157 = par[43];
    const double pull_cs_C_GdLS = par[44];
    const double pull_cs_C_LS = par[45];
    const double pull_cs_C_acry = par[46];



    for(int ad = 1; ad<5; ad++){

        /*const Double_e w_GdLS = GdLS.at(ad).GetHboth()/(GdLS.at(ad).GetGdboth(155)*nGd155_CS_th.at(0)
                            + GdLS.at(ad).GetGdboth(157)*nGd157_CS_th.at(0)
                            + GdLS.at(ad).GetHboth()*nH_CS_th.at(0) + GdLS.at(ad).GetCboth()*nC_CS_th.at(0)); 
        const Double_e w_LS = LS.at(ad).GetHboth()/(LS.at(ad).GetHboth()*nH_CS_th.at(1) + LS.at(ad).GetCboth()*nC_CS_th.at(1));
        const Double_e w_Acrylic = Acrylic.at(ad).GetHboth()/(Acrylic.at(ad).GetHboth()*nH_CS_th.at(2)
                                 + Acrylic.at(ad).GetCboth()*nC_CS_th.at(2));*/

        const double w_GdLS = GdLS.at(ad).GetH()*(1.+pull_GdLS_H.at(ad))/
                              (GdLS.at(ad).GetGd(155)*(1.+pull_GdLS_Gd.at(ad))*nGd155_CS_th.at(0).GetValue()*(1.+pull_cs_Gd155)
                               +GdLS.at(ad).GetGd(157)*(1.+pull_GdLS_Gd.at(ad))*nGd157_CS_th.at(0).GetValue()*(1.+pull_cs_Gd157)
                               +GdLS.at(ad).GetH()*(1.+pull_GdLS_H.at(ad))*nH_CS_th.at(0).GetValue()*(1.+pull_cs_H_GdLS)
                               +GdLS.at(ad).GetC()*(1.+pull_GdLS_C.at(ad))*nC_CS_th.at(0).GetValue()*(1.+pull_cs_C_GdLS));
        
        const double w_LS = LS.at(ad).GetH()*(1.+pull_LS_H.at(ad))/
                            (LS.at(ad).GetH()*(1.+pull_LS_H.at(ad))*nH_CS_th.at(1).GetValue()*(1.+pull_cs_H_LS)
                             +LS.at(ad).GetC()*(1.+pull_LS_C.at(ad))*nC_CS_th.at(1).GetValue()*(1.+pull_cs_C_LS));

        const double w_Acrylic = Acrylic.at(ad).GetH()/
                                (Acrylic.at(ad).GetH()*nH_CS_th.at(2).GetValue()*(1.+pull_cs_H_acry)
                                +Acrylic.at(ad).GetC()*nC_CS_th.at(2).GetValue()*(1.+pull_cs_C_acry));


        const double ExpnH = nH_eff_uc.GetValue()*(1.+pull_eff_H_corr+pull_eff_H_uncorr.at(ad))*CS_nH_TarVol
                             *(w_GdLS*GdLS.at(ad).GetH()*(1.+pull_GdLS_H.at(ad))
                                +w_LS*LS.at(ad).GetH()*(1.+pull_LS_H.at(ad))+w_Acrylic*Acrylic.at(ad).GetH());
        const double ExpnGd = nGd_eff_uc.GetValue()*(1.+pull_eff_Gd_corr+pull_eff_Gd_uncorr.at(ad))
                            * w_GdLS*(GdLS.at(ad).GetGd(155)*(1.+pull_GdLS_Gd.at(ad))*nGd155_CS_th.at(0).GetValue()*(1.+pull_cs_Gd155)
                            + GdLS.at(ad).GetGd(157)*(1.+pull_GdLS_Gd.at(ad))*nGd157_CS_th.at(0).GetValue()*(1.+pull_cs_Gd157));
        const double r_HGd = ExpnH/ExpnGd;


        const Double_e errcal = nH_can_sta.at(ad)-nH_acc_sta.at(ad)-nH_lkg_sta.at(ad)+nGd_can_sta.at(ad)-nGd_acc_sta.at(ad);
        const double stat_err = errcal.GetError();
        const double MeasnH = nH_can_sta.at(ad).GetValue()-nH_acc_sta.at(ad).GetValue()*(1.+pull_acc.at(ad))
                              -nH_lkg_sta.at(ad).GetValue()*(1.+pull_lkg.at(ad));
        const double MeasnGd = nGd_can_sta.at(ad).GetValue()-nGd_acc_sta.at(ad).GetValue()*(1.+pull_acc.at(ad));
        cout << "measured ratio = " << MeasnH/MeasnGd << endl;


        const double delta = (MeasnH-MeasnGd*r_HGd)/stat_err;
        f += (pow(delta,2) + pow(pull_acc.at(ad)/sys_acc.at(ad),2) + pow(pull_lkg.at(ad)/sys_lkg_H.at(ad),2)
             + pow(pull_GdLS_Gd.at(ad)/sys_GdLS_Gd.at(ad),2) + pow(pull_GdLS_H.at(ad)/sys_GdLS_H.at(ad),2)
             + pow(pull_GdLS_C.at(ad)/sys_GdLS_C.at(ad),2) + pow(pull_LS_H.at(ad)/sys_LS_H.at(ad),2)
             + pow(pull_LS_C.at(ad)/sys_LS_C.at(ad),2) + pow(pull_eff_H_uncorr.at(ad)/sys_eff_H_uncorr,2)
             + pow(pull_eff_Gd_uncorr.at(ad)/sys_eff_Gd_uncorr,2));

    }

    f += pow(pull_cs_H_GdLS/sys_cs_H_GdLS,2);
    f += pow(pull_cs_H_LS/sys_cs_H_LS,2);
    f += pow(pull_cs_H_acry/sys_cs_H_acry,2);
    f += pow(pull_cs_Gd155/sys_cs_Gd155,2);
    f += pow(pull_cs_Gd157/sys_cs_Gd157,2);
    f += pow(pull_cs_C_GdLS/sys_cs_C_GdLS,2);
    f += pow(pull_cs_C_LS/sys_cs_C_LS,2);
    f += pow(pull_cs_C_acry/sys_cs_C_acry,2);
    f += pow(pull_eff_H_corr/sys_eff_H_corr,2);
    f += pow(pull_eff_Gd_corr/sys_eff_Gd_corr,2);



}
