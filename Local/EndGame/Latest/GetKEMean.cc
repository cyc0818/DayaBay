#include "/Users/chengyuchin/Analysis/nC/EndGame/Volume.h"

void GetKEMean(){


    gROOT->ForceStyle();
    gStyle->SetLegendTextSize(0.06);
    gStyle->SetOptStat(0);
    //gStyle->SetOptStat("MRS");
    TString ele = "H";
    const int rebin = 1;
    //const double w_GdLS = 0.386096; // only near
    //const double w_LS = 3.16965;
    //const double w_acry = 2.8418;
    const double w_GdLS = 0.387002;   // 8AD
    const double w_LS = 3.16973;
    const double w_acry = 2.8418;
    Volume GdLS, LS, Acrylic;
    string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data2.txt";
    for(int ad = 1; ad<9; ad++){
        GdLS = GdLS + Volume(ad, 1, txtfile);
        LS = LS + Volume(ad, 2, txtfile);
        Acrylic = Acrylic + Volume(ad, 3, txtfile);
    }


    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/nKE_plot/nKE_200k.root");
    TH1D* h1 = F->Get<TH1D>("nKE_Before_Cap_GdLS_"+ele);
    TH1D* h2 = F->Get<TH1D>("nKE_Before_Cap_LS_"+ele);
    TH1D* h3 = F->Get<TH1D>("nKE_Before_Cap_Acrylic_"+ele);


    //map<double,TH1D*> m = {{w_GdLS,h1}, {w_LS,h2}, {w_acry,h3}};
    const vector<double> w = {w_GdLS, w_LS, w_acry};
    vector<TH1D*> hv = {h1, h2, h3};
    vector<Volume> v = {GdLS, LS, Acrylic};
    TH1D* h = new TH1D("h","h",h1->GetNbinsX()/rebin,h1->GetXaxis()->GetXmin(),h1->GetXaxis()->GetXmax());
    //for(auto i : m){
    for(int i = 0; i<3; i++){
        double N = 0;
        if(ele == "C") N = v.at(i).GetC();
        if(ele == "H") N = v.at(i).GetH();
        hv.at(i)->Rebin(rebin);
        hv.at(i)->Scale(1./hv.at(i)->GetEntries());
        h->Add(hv.at(i), w.at(i)*N);
        //h->Add(hv.at(i), w.at(i));
    }


    double kine = 0;
    double total = 0;
    for(int i = 1; i<h->GetNbinsX()+1; i++){
        kine += (h->GetBinContent(i)*h->GetBinCenter(i));
        total += h->GetBinContent(i);
    }


    cout << "total = " << total << endl;
    cout << "Mean KE of " << ele << " = " << kine/total << endl;
    cout << "Mode KE of " << ele << " = " << h->GetBinCenter(h->GetMaximumBin()) << endl;


    TCanvas* c1 = new TCanvas("c1","c1",1760,1060);
    ////TPaveText *pt = new TPaveText(.05,.1,.95,.8);
    TPaveText *pt = new TPaveText(.1,.005,.95,.8);
    gPad->SetLogy(1);
    h->Scale(1./total);
    h->GetXaxis()->CenterTitle(kTRUE);
    h->GetXaxis()->SetTitle("Kinetic energy (eV)");
    h->GetXaxis()->SetTitleSize(0.09);
    h->GetXaxis()->SetTitleOffset(0.74);
    h->GetYaxis()->CenterTitle(kTRUE);
    h->GetYaxis()->SetTitle("Entries/2meV");
    h->GetYaxis()->SetTitleSize(0.09);
    h->GetYaxis()->SetTitleOffset(0.69);
    h->SetLineWidth(2);
    h->SetMarkerSize(0.9);
    h->SetMarkerColor(4);
    h->SetMarkerStyle(20);
    h->Draw("e");
    for(int i = 2; i<h->GetNbinsX()+1; i++){
        if(h->Integral(1,i)>=0.5){
            cout << "Mid KE of " << ele << " = " << h->GetBinCenter(i) << endl;
            pt->AddText(TString::Format("Median\t %.5f eV",h->GetBinCenter(i)));
            break;
        }
    }
    cout << "Integral = " << h->Integral(1,h->GetNbinsX()) << endl;
    pt->AddText(TString::Format("Mode\t %.5f eV",h->GetBinCenter(h->GetMaximumBin())));
    pt->Draw("same");
    cout << "Get Mean = " << h->GetMean(1) << endl;


}

