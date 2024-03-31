void H_syst(){

    const double center = 0.309492;
    //vector<pair<string,double>> syst = {{"all on", 0.00308806}, {"CS", 0.00300177}, {"eff", 0.00127375}, {"material", 0.000378683},
    //                                    {"acc",3.87711e-05}, {"lkg",0}};
    /*vector<pair<string,double>> syst = {{"all on", 0.00308806}, {"Cross section", 0.00300177},{"nH Efficiency",0.00188635},
                                        {"nGd Efficiency", 0.00127375},{"Detector material", 0.000378683}, {"Accidental",3.87711e-05},
                                        {"lkg",0}};*/
    vector<pair<string,double>> syst = {{"all on", 0.0031014096}, {"Stats", 0.00308806}, {"Cross section", 0.00300177},{"nH Efficiency",0.00188635},
                                        {"nGd Efficiency", 0.00127375},{"Detector material", 0.000378683}, {"Accidental",3.87711e-05},
                                        {"lkg",0}};


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

