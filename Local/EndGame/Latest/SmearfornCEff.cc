#include "/Users/chengyuchin/Analysis/nC/TH1functions.h"

const double sigma_near = 0.433438;
const double sigma_MC = 2.36815e-01;
const double unit = 0.95*sqrt(sigma_near*sigma_near-sigma_MC*sigma_MC);


void SmearfornCEff(){

    TH1D* hC = new TH1D("hC","",1200,0,12);
    TH1D* h = new TH1D("h","",1200,0,12);
    TFile* f = new TFile("/Users/chengyuchin/Analysis/data/MC/Efficiency_noMOcap.root");
    hC->Add(f->Get<TH1D>("Ed_C_passEpdrdt"));
    h->Add(f->Get<TH1D>("Ed_passEpdrdt"));
    h->Add(f->Get<TH1D>("Ed_C_passEpdrdt"), -1.);


    GaussianBinSmear(hC,unit); 
    TCanvas* c1 = new TCanvas("c1","c1",1920,1080);
    hC->Draw();
    cout << "Eff in [3.5,5.8] = " << hC->Integral(351,580)/hC->Integral(1,680) << endl;
    cout << "Eff in [4.0,5.8] = " << hC->Integral(401,580)/hC->Integral(1,680) << endl;


    h->Add(hC);
    TCanvas* c2 = new TCanvas("c2","c2",1920,1080);
    h->Draw();


    TFile* outfile = new TFile("/Users/chengyuchin/Analysis/nC/smearnC.root","recreate");
    hC->Write();



}
