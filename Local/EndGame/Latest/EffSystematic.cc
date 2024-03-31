void EffSystematic(){

    const int nor1 = 401;
    const int nor2 = 580;
    const int vary1 = 7;    // corr
    const int vary2 = 10;    // uncorr

    TFile* f = new TFile("/Users/chengyuchin/Analysis/data/MC/Efficiency_noMOcap_sq_200k.root");
    TH1D* h = f->Get<TH1D>("Ed_C_passEpdt");


    //const double eff_n = h->Integral(nor1,nor2)/h->Integral(1,1200); 
    const double eff_n = h->Integral(nor1,nor2)/h->Integral(1,610); 
    const double eff_l1 = h->Integral(nor1-vary1,nor2+vary1)/h->Integral(1,610); 
    const double eff_t1 = h->Integral(nor1+vary1,nor2-vary1)/h->Integral(1,610); 
    const double d1 = (eff_l1-eff_t1)/2;



    const double eff_l2 = h->Integral(nor1-vary2,nor2+vary2)/h->Integral(1,610); 
    const double eff_t2 = h->Integral(nor1+vary2,nor2-vary2)/h->Integral(1,610); 
    const double d2 = (eff_l2-eff_t2)/2;


    const double d = sqrt(d1*d1+d2*d2);


    cout << "---------------" << h->GetName() << "----------------" << endl;
    cout << "Nominal cut at [" << double(nor1/10)/10. << "," << double(nor2/10)/10. << "]";
    cout << " , Correlated varies = " << double(vary1)/10.;
    cout << " , Uncorrelated varies = " << double(vary2)/10. << endl;
    cout << "Cut efficiency = " << eff_n << " +/- " << d1 << " (corr) +/- " << d2 << " (uncorr)" << endl;
    cout << "Cut efficiency = " << eff_n << " +/- " << d << " (syst)" << endl;


}

