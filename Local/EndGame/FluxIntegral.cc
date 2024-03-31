#include "TGraphErrors.h"
#include "Uncertainty2.h"



Double_e FluxIntegral(const char* ele, int iso, double given_err){

    //const char* ele = "H";
    //int iso = 1;


    gROOT->ForceStyle();
    string line;
    TGraphErrors* g = new TGraphErrors();
    ifstream Fin(TString::Format("/Users/chengyuchin/Downloads/%s%d-102.dat",ele,iso));
    int i = 0;
    int points = 0;


    while(Fin.good()){
        i++;
        getline(Fin, line);
        if(i < 6) continue;


        stringstream ss(line);
        string word;
        pair<double, double> p(0,0);    // < kinetic energy , cross section >


        for(int j = 0; j<7; j++){
            getline(ss, word, ' ');
            if(not j) continue;
            if(word.empty()) continue;


            if(j&1){
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


    g->SetTitle("^{1}H(n,#gamma)^{2}H cross section;E_{n}^{kin}(eV);Counts");
    g->SetTitle(TString::Format("^{%d}%s(n,#gamma)^{%d}%s cross section;Kinetic energy (eV);Cross section (b)",iso,ele,iso+1,ele));
    g->SetMarkerStyle(20);
    g->SetMarkerColor(2);
    g->SetLineColor(2);
    g->SetMarkerSize(1.4);
    g->GetXaxis()->CenterTitle(kTRUE);
    g->GetYaxis()->CenterTitle(kTRUE);
    TCanvas* c1 = new TCanvas("c1","c1",1760,1060);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    g->Draw();


    Double_e integral;
    double kine = 0;
    double total = 0;
    double error = 0;
    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/Volume_flux_C.root");
    //TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/NeutronKE.root");
    TH1D* h = dynamic_cast<TH1D*>(F->Get("nKE_Before_Cap_woMO_C")); 
    //TH1D* h = dynamic_cast<TH1D*>(F->Get("nKE_Before_Cap")); 
    TCanvas* c2 = new TCanvas("c2","c2",3840,2160);
    h->Rebin(100);
    //h->Rebin(10);
    h->Draw();


    for(int bin = 1; bin<h->GetNbinsX()+1; bin++){

        Double_e N(h->GetBinContent(bin), sqrt(h->GetBinContent(bin)));
        Double_e cs(g->Eval(h->GetBinCenter(bin)*1e6), given_err);
        //Double_e cs(g->Eval(h->GetBinCenter(bin)*1e6), g->Eval(h->GetBinCenter(bin)*1e6)*percent_err);
        Double_e temp = N*cs;


        integral += temp;
        total += h->GetBinContent(bin);
        kine += h->GetBinContent(bin) * h->GetBinCenter(bin)*1e6;

    }


    cout << "Integral = " << integral << endl;
    cout << "Total = " << total << " +/- " << sqrt(total) << endl;
    cout << "Weighted average of cross section = " << integral/total << endl;
    cout << "Kine = " << kine/total << endl;
    cout << g->Eval(0.05) << endl;


    F->Close();


    //return integral;
    return integral/total;



}


Double_e GetCSinVolume(const char* ele, int iso, int vol, double given_err = 0){


    string line;
    TGraphErrors* g = new TGraphErrors();
    g->SetName("CS");
    ifstream Fin(TString::Format("/Users/chengyuchin/Downloads/%s%d-102.dat",ele,iso));
    int i = 0;
    int points = 0;


    while(Fin.good()){
        i++;
        getline(Fin, line);
        if(i < 6) continue;


        stringstream ss(line);
        string word;
        pair<double, double> p(0,0);    // < kinetic energy , cross section >


        for(int j = 0; j<7; j++){
            getline(ss, word, ' ');
            if(not j) continue;
            if(word.empty()) continue;


            if(j&1){
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


    //g->SetMarkerStyle(8);
    g->SetLineColor(2);
    g->SetTitle("^{1}H(n,#gamma)^{2}H cross section;E_{n}^{kin}(eV);Counts");
    g->SetTitle(TString::Format("^{%d}%s(n,#gamma)^{%d}%s cross section;E_{n}^{kin}(eV);#sigma(b)",iso,ele,iso+1,ele));
    //g->GetXaxis()->CenterTitle(kTRUE);
    g->GetYaxis()->CenterTitle(kTRUE);
    //g->GetXaxis()->SetTitleSize(0.04);
    g->GetYaxis()->SetTitleSize(0.05);
    TCanvas* c1 = new TCanvas("c1","c1",3840,2160);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    g->Draw();


    Double_e integral;
    double kine = 0;
    double total = 0;
    double error = 0;
    TString vname[7] = {"_","_GdLS_","_LS_","_Acrylic_","_MO_","_IAV_","_OAV_"};
    bool Gdswitch = false;
    if(string(ele) == "Gd") Gdswitch = true;
    //TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/VolEle_flux.root");
    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/nKE_plot/nKE_200k.root");
    //TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/nKE_plot/nKE_testIAVOAV.root");
    TH1D* h;
    if(Gdswitch) h = dynamic_cast<TH1D*>(F->Get("nKE_Before_Cap"+vname[vol]+ele+TString::Format("%d",iso))); 
    else h = dynamic_cast<TH1D*>(F->Get("nKE_Before_Cap"+vname[vol]+ele));
    TCanvas* c2 = new TCanvas("c2","c2",3840,2160);
    h->Rebin(10);
    //if(string(ele) == "C") h->Rebin(10);
    h->Draw();


    for(int bin = 1; bin<h->GetNbinsX()+1; bin++){

        Double_e N(h->GetBinContent(bin), sqrt(h->GetBinContent(bin)));
        //Double_e cs(g->Eval(h->GetBinCenter(bin)*1e6), given_err);
        Double_e cs(g->Eval(h->GetBinCenter(bin)), given_err);
        //Double_e cs(g->Eval(h->GetBinCenter(bin)*1e6), g->Eval(h->GetBinCenter(bin)*1e6)*percent_err);
        Double_e temp = N*cs;


        integral += temp;
        total += h->GetBinContent(bin);
        //kine += h->GetBinContent(bin) * h->GetBinCenter(bin)*1e6;
        kine += h->GetBinContent(bin) * h->GetBinCenter(bin);

    }


    cout << "Integral = " << integral << endl;
    cout << "Total = " << total << " +/- " << sqrt(total) << endl;
    cout << "Weighted average of cross section = " << integral/total << endl;
    cout << "Kine = " << kine/total << endl;


    TFile* outfile = new TFile("./CScurve_nH.root","recreate");
    g->Write();
    outfile->Close();
    F->Close();


    return integral/total;



}



    

Double_e GetMCVolCS(const char* filename, int vol, double given_err = 0){


    string line;
    TGraphErrors* g = new TGraphErrors();
    ifstream Fin(TString::Format("/Users/chengyuchin/Analysis/NuWa/%s",filename));
    int i = 0;
    int points = 0;


    while(Fin.good()){
        i++;
        getline(Fin, line);
        if(i < 4) continue;


        stringstream ss(line);
        string word;
        pair<double, double> p(0,0);    // < kinetic energy , cross section >


        for(int j = 0; j<6; j++){
            getline(ss, word, ' ');
            if(not j) continue;
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
    g->SetTitle(TString::Format("%s cross section;E_{n}^{kin}(eV);#sigma(b)",filename));
    TCanvas* c1 = new TCanvas("c1","c1",3840,2160);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    g->Draw();


    Double_e integral;
    double kine = 0;
    double total = 0;
    double error = 0;
    TString vname[5] = {"","_GdLS","_LS","_Acrylic","_MO"};
    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/nKE_plot/nKE_200k.root");
    TH1D* h = dynamic_cast<TH1D*>(F->Get("nKE_Before_Cap"+vname[vol]+"_C"));
    TCanvas* c2 = new TCanvas("c2","c2",3840,2160);
    h->Rebin(10);
    h->Draw();


    for(int bin = 1; bin<h->GetNbinsX()+1; bin++){

        Double_e N(h->GetBinContent(bin), sqrt(h->GetBinContent(bin)));
        Double_e cs(g->Eval(h->GetBinCenter(bin)), given_err);
        //Double_e cs(g->Eval(h->GetBinCenter(bin)*1e6), g->Eval(h->GetBinCenter(bin)*1e6)*percent_err);
        Double_e temp = N*cs;


        integral += temp;
        total += h->GetBinContent(bin);
        kine += h->GetBinContent(bin) * h->GetBinCenter(bin);

    }


    cout << "Integral = " << integral << endl;
    cout << "Total = " << total << " +/- " << sqrt(total) << endl;
    cout << "Weighted average of cross section = " << integral/total << endl;
    cout << "Kine = " << kine/total << endl;


    F->Close();


    return integral/total;



}




