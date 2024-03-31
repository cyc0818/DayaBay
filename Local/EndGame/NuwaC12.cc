#include "TGraphErrors.h"



double NuwaC12(){

    //const char* ele = "H";
    //int iso = 1;


    string line;
    TGraphErrors* g = new TGraphErrors();
    //ifstream Fin("/Users/chengyuchin/Analysis/NuWa/1_1_Hydrogen");
    ifstream Fin("/Users/chengyuchin/Analysis/NuWa/6_12_Carbon");
    int i = 0;
    int points = 0;


    while(Fin.good()){
        i++;
        getline(Fin, line);
        if(i < 4) continue;
        if(Fin.fail()) break;


        stringstream ss(line);
        string word;
        pair<double, double> p(0,0);


        for(int j = 0; j<6; j++){
            getline(ss, word, ' ');
            if(word.empty()) continue;


            if(not(j&1)){
                //cout << "Energy = " << word;
                p.first = stod(word);
            }
            else{
                //cout << " , cross section = " << word << endl;
                p.second = stod(word);
            }


            if(p.first and p.second){
                g->SetPoint(points, p.first, p.second);
                p = {0,0};
                points++;
            }

        }


    }


    g->SetMarkerStyle(8);
    g->SetLineColor(2);
    g->SetTitle("^{1}H(n,#gamma)^{2}H cross section;E_{n}^{kin}(eV);Counts");
    g->SetTitle(TString::Format("^{12}C(n,#gamma)^{13}C cross section;E_{n}^{kin}(eV);#sigma(b)"));
    TCanvas* c1 = new TCanvas("c1","c1",3840,2160);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    g->Draw();


    double integral = 0;
    double kine = 0;
    double total = 0;
    double error = 0;
    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/NeutronKE.root");
    TH1D* h = dynamic_cast<TH1D*>(F->Get("nKE_Before_Cap_C")); 
    TCanvas* c2 = new TCanvas("c2","c2",3840,2160);
    h->Rebin(10);
    h->Draw();


    for(int bin = 1; bin<h->GetNbinsX()+1; bin++){

        total += h->GetBinContent(bin);
        integral += (h->GetBinContent(bin) * g->Eval(h->GetBinCenter(bin)*1e6));
        error += (h->GetBinContent(bin) * pow(g->Eval(h->GetBinCenter(bin)*1e6),2));
        kine += h->GetBinContent(bin) * h->GetBinCenter(bin)*1e6;

    }


    TF1* error_AoverB = new TF1("error_AoverB","([0]/[1])*sqrt(([2]/[0])^2+([3]/[1])^2)",0,0);    // Parameters(A,B,sigmaA,sigmaB)
    error = sqrt(error);
    cout << "Integral = " << integral << " +/- " << error << endl;
    cout << "Total = " << total << " +/- " << sqrt(total) << endl;
    error_AoverB->SetParameters(integral,total,error,sqrt(total));
    cout << "Weighted average of cross section = " << integral/total << " +/- " << error_AoverB->Eval(0) << endl;
    cout << "Kine = " << kine/total << endl;
    cout << g->Eval(0.05) << endl;


    F->Close();


    return integral;



}


    

