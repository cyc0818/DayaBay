#include "UserSetting.h"
#include "Fitter.h"


using namespace std;


void Neutron_KE(){

    gStyle->SetOptFit(1);


    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/NeutronKE.root");
    TH1D* hInit = static_cast<TH1D*>(F->Get("nKE_Init"));
    hInit->Rebin(4);
    TH1D* hBfCap = static_cast<TH1D*>(F->Get("nKE_Before_Cap"));
    hBfCap->Rebin(8);
    hBfCap->GetXaxis()->SetRangeUser(0,3e-7);


    TF1* fInit = new TF1("f_Init",GapExp,hInit->GetXaxis()->GetXmin(),hInit->GetXaxis()->GetXmax(),3);
    fInit->SetParNames("N","E_{charc}","gap");
    fInit->SetParameters(100,hInit->GetXaxis()->GetXmax()/5, 0.001);
    fInit->SetParLimits(1,0.005,0.05);
    //fInit->FixParameter(2,0.001);
    fInit->SetParLimits(2,0.0009,0.0011);
    TCanvas* c1 = new TCanvas("c1","c1",3840,2160);
    gPad->SetLogy(1);
    hInit->Fit(fInit,"","",hInit->GetXaxis()->GetXmin(),hInit->GetXaxis()->GetXmax());
    hInit->Fit(fInit,"","",hInit->GetXaxis()->GetXmin(),hInit->GetXaxis()->GetXmax());


    TF1* fBfCap = new TF1("f_Before_Cap",ExpRiseDecay,hBfCap->GetXaxis()->GetXmin(),hBfCap->GetXaxis()->GetXmax(),4);
    fBfCap->SetParNames("N","#alpha","E_{rise}","E_{decay}");
    fBfCap->SetParameters(100,0.2,1e-8,3e-8);
    TCanvas* c2 = new TCanvas("c2","c2",3840,2160);
    gPad->SetLogy(1);
    hBfCap->Fit(fBfCap,"","",hBfCap->GetXaxis()->GetXmin(),hBfCap->GetXaxis()->GetXmax());
    hBfCap->Fit(fBfCap,"","",hBfCap->GetXaxis()->GetXmin(),hBfCap->GetXaxis()->GetXmax());
    hBfCap->Fit(fBfCap,"","",hBfCap->GetXaxis()->GetXmin(),hBfCap->GetXaxis()->GetXmax());
    //hBfCap->Draw();


}

