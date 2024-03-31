void C_syst(){

    const double center = 6.07793;
    /*vector<pair<string,double>> syst = {{"all on", 0.21070281}, {"Stats", 0.158932},{"nC Efficiency",0.0954008},{"nGd leakage tail",0.0556077},
                                        {"nH Efficiency",0.0314556},{"Detector material",0.0160601},{"others",0} };     // nC/nH*/
    /*vector<pair<string,double>> syst = {{"all on", 0.20683394}, {"Stats", 0.153766}, {"nC Efficiency",0.0865441},{"nGd leakage tail",0.0385079},
                                        {"nGd Efficiency", 0.0271374},{"Detector material",0.0142747},{"others",0}};     // nC/nGd*/
    /*vector<pair<string,double>> syst = {{"all on", 0.110571}, {"nC Efficiency",0.0644034},{"nGd leakage tail", 0.0338197},
                                        {"nH Efficiency", 0.0248612},{"Detector material",0.017379},{"others",0}};     // both*/
    /*vector<pair<string,double>> syst = {{"all on", 0.17712591}, {"Stats", 0.110571}, {"nC Efficiency",0.0644034},{"Energy-leaked nGd", 0.0338197},
                                        {"nH Efficiency", 0.0248612},{"others",0}};     // both*/
    /*vector<pair<string,double>> syst = {{"all on", 0.17712591}, {"Stats", 0.110571}, {"nC Efficiency",0.0644034},{"nGd leakage tail", 0.0338197},
                                        {"nH Efficiency", 0.0248612},{"Detector material",0.017379},{"others",0}};     // both*/
    vector<pair<string,double>> syst = {{"all on", 0.17712591}, {"Stats", 0.110571}, {"nC Efficiency",0.0644034},{"nGd leakage tail", 0.0338197},
                                        {"nH Efficiency", 0.0248612},{"Detector material",0.017379},{"nGd Efficiency",0.0107435},
                                        {"Accidental", 0.0100581}, {"nGd cross section", 0.00710716}, {"nH cross section",0}};     // both


    vector<pair<string,double>> contribution;
    double total = 0;
    for(auto j = syst.begin()+1; j!=syst.end(); j++){
        auto i = j-1;
        pair<string,double> temp(j->first, i->second*i->second-j->second*j->second);
        contribution.push_back(temp);
        total += (i->second*i->second-j->second*j->second);
    }



    const int size = syst.size()-1;
    int color[size];
    double frac[size];
    const char* label[size];
    for(int i = 0; i<size; i++){
        color[i] = i+2;
        frac[i] = contribution.at(i).second/total;
        label[i] = contribution.at(i).first.c_str();
        //cout << label[i] << " : " << frac[i] << endl;
        cout << label[i] << "&" << frac[i]*100 << "\\\\" << endl;
    }


    TPie* pie = new TPie("pie","Systematic uncertainty contribution",size,frac,color);
    pie->SetLabels(label);
    pie->SetLabelsOffset(0.01);
    pie->SetTextSize(1);
    pie->SetAngularOffset(15.);
    pie->SetRadius(0.3);
    pie->SetLabelFormat("#splitline{%txt}{(%perc)}");
    pie->SetTextSize(0.04);
    TCanvas* c1 = new TCanvas("c1","c1",1760,1060);
    pie->Draw("nol <");


}

