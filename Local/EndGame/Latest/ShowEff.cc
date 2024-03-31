#include "/Users/chengyuchin/Analysis/nC/EndGame/Latest/AllMeasurement.h"



void ShowEff(){

    const Double_e nH_uc = nH_Epeff_uc * nH_dteff_uc * nH_Edeff_uc * nH_dreff_uc;
    const Double_e nC_uc = nC_Epeff_uc * nC_dteff_uc * nC_Edeff_uc * nC_dreff_uc;
    const Double_e nGd_uc = nGd_Epeff_uc * nGd_dteff_uc * nGd_Edeff_uc * nGd_dreff_uc;


    const Double_e nH_c = nH_Epeff_c * nH_dteff_c * nH_Edeff_c * nH_dreff_c;
    const Double_e nC_c = nC_Epeff_c * nC_dteff_c * nC_Edeff_c * nC_dreff_c;
    const Double_e nGd_c = nGd_Epeff_c * nGd_dteff_c * nGd_Edeff_c * nGd_dreff_c;


    cout << "nGd corr = " << nGd_c << endl;
    cout << "nGd uncorr = " << nGd_uc << endl;
    cout << "nH corr = " << nH_c << endl;
    cout << "nH uncorr = " << nH_uc << endl;
    cout << "nC corr = " << nC_c << endl;
    cout << "nC uncorr = " << nC_uc << endl;



}


