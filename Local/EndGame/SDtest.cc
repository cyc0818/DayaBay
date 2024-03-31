#include "Uncertainty.h"

void SDtest(){

    vector<Double_e> v;

    v.push_back(Double_e(79.72,0.11));
    v.push_back(Double_e(79.42,0.1));
    v.push_back(Double_e(79.72,0.11));
    v.push_back(Double_e(79.60,0.12));
    v.push_back(Double_e(79.45,0.4));
    v.push_back(Double_e(79.24,0.4));
    v.push_back(Double_e(79.54,0.4));
    v.push_back(Double_e(79.61,0.42));


    Double_e mean = VarWeightedMean(v);
    Double_e SD = VarWeightedStdDev(v);

    cout << "Mean = " << mean << endl;
    cout << "SD = " << SD << endl;



}
