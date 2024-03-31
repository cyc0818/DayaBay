#include "/Users/chengyuchin/Analysis/nC/EndGame/Uncertainty.h"


const double CSAD = 5.9332e-3;
const double CSADerr = 0.0570839e-3/CSAD;
TGraphErrors* g_theo;
Uncertainty FindEqKE();
void fitter(int& npar, double* gin, double& f, double* par, int iflag);

void PlotComparison(){

    gROOT->ForceStyle();
    gStyle->SetLegendTextSize(0.05);
    gStyle->SetOptStat(0);


    const double E_thr[5] = {2.53e-2,2.53e-2,2.53e-2,2.53e-2,2.53e-2};
    //const double CS_thr[5] = {3.87e-3,3.53e-3,3.8e-3,3.29e-3,3.53e-3};
    //const double CSe_thr[5] = {0.03e-3,0.07e-3,4.e-4,1.5e-4,0.07e-3};
    const double CS_thr[5] = {3.87,3.53,3.8,3.29,3.53};
    const double CSe_thr[5] = {0.03,0.07,4.e-1,1.5e-1,0.07};
    const double E_higher[27] = {21.e3,40.e3,50.e3,60.e3,97.e3,199.e3,30.e3,5.e3,6.e3,7.e3,8.e3,9.e3,10.e3,12.5e3,15.e3,17.5e3,20.e3,25.e3,30.e3,
                                35.e3,40.e3,45.e3,50.e3,60.e3,70.e3,85.e3,100.e3};
    double CS_higher[27] = {11.9e-6,11.2e-6,13.1e-6,15.9e-6,15.2e-6,21.6e-6,16.8e-6,8.015e-6,7.49e-6,7.24e-6,7.195e-6,7.295e-6,7.47e-6,8.e-6,
                                8.4e-6,8.59e-6,8.595e-6,8.24e-6,7.665e-6,7.045e-6,6.46e-6,5.925e-6,5.45e-6,4.67e-6,4.07e-6,3.415e-6,2.94e-6};
    double CSe_higher[27] = {2.2e-6,1.7e-6,1.6e-6,3.4e-6,1.7e-6,4.1e-6,2.1e-6,7.5e-8,2.4e-7,5.3e-7,9.15e-7,1.375e-6,1.86e-6,2.98e-6,3.82e-6,
                                4.35e-6,4.625e-6,4.69e-6,4.425e-6,4.045e-6,3.65e-6,3.275e-6,2.94e-6,2.38e-6,1.95e-6,1.485e-6,1.16e-6};
    for(auto& i : CS_higher) i *= 1.e3;
    for(auto& i : CSe_higher) i *= 1.e3;
    TMultiGraph* mg = new TMultiGraph();
    TMultiGraph* mg2 = new TMultiGraph();
    TGraphErrors* g_thr = new TGraphErrors(5,E_thr,CS_thr,nullptr,CSe_thr);
    TGraphErrors* g_higher = new TGraphErrors(27,E_higher,CS_higher,nullptr,CSe_higher);
    TGraphErrors* g_my = new TGraphErrors();
    g_thr->SetTitle("Thermal experiment");
    g_higher->SetTitle("High energy experiment");
    g_my->SetTitle("Measurement in this analysis");
    //g_my->SetPoint(0,0.005,6.07756e-3);
    //g_my->SetPoint(0,0.02075,6.07756e-3);
    //g_my->SetPoint(0,0.02075,5.933e-3);
    //g_my->SetPointError(0,0,0.14729483e-3);


    g_thr->SetMarkerStyle(20);
    g_thr->SetMarkerColor(1);
    g_thr->SetLineColor(1);
    g_thr->SetLineWidth(4);
    g_thr->SetMarkerSize(1.3);
    g_higher->SetMarkerStyle(20);
    g_higher->SetMarkerColor(4);
    g_higher->SetLineColor(4);
    g_my->SetMarkerStyle(20);
    g_my->SetMarkerColor(2);
    g_my->SetLineColor(2);
    g_my->SetLineWidth(4);
    g_my->SetMarkerSize(1.4);


    TGraphErrors* g_theo1 = new TGraphErrors();
    TFile* f = new TFile("./CScurve_nC.root");
    //TFile* f = new TFile("./CScurveAddMine.root");
    g_theo = f->Get<TGraphErrors>("CS");
    for(int i = 0; i<g_theo->GetN(); i++) g_theo1->SetPoint(i, g_theo->GetPointX(i), g_theo->GetPointY(i)*1.e3);
    g_theo1->SetLineColor(8);
    g_theo1->SetMarkerStyle(20);
    g_theo1->SetMarkerColor(8);
    g_theo1->SetMarkerSize(1.4);
    g_theo1->SetLineWidth(8);
    g_theo1->SetTitle("ENDF curve");
    Uncertainty eqKE = FindEqKE();
    //g_my->SetPoint(0,eqKE.GetValue(),6.07756e-3);
    //g_my->SetPointError(0,eqKE.GetError(),0.14729483e-3);
    g_my->SetPoint(0,eqKE.GetValue(),6.07756);
    g_my->SetPointError(0,eqKE.GetError(),0.14729483);
    cout << "eq KE = " << eqKE << endl;
    TGraphErrors* g_theo2 = new TGraphErrors();
    const double dx = (0.1-0.001)/100.;
    //for(int i = 0; i<100; i++) g_theo2->SetPoint(i, 0.001+i*dx, g_theo->Eval(0.001+i*dx));
    //for(int i = 0; i<5; i++) g_theo2->SetPoint(i, 0.001+i*dx*20., g_theo->Eval(0.001+i*dx*20.));
    //for(int i = 0; i<3; i++) g_theo2->SetPoint(i, g_theo->GetPointX(i+1), g_theo->GetPointY(i+1));
    for(int i = 0; i<3; i++) g_theo2->SetPoint(i, g_theo->GetPointX(i+1), g_theo->GetPointY(i+1)*1.e3);
    g_theo2->SetLineColor(8);
    g_theo2->SetMarkerStyle(20);
    g_theo2->SetMarkerColor(8);
    g_theo2->SetMarkerSize(1.4);
    g_theo2->SetLineWidth(8);
    g_theo2->SetTitle("ENDF curve");



    mg->Add(g_theo1,"LP");
    mg->Add(g_thr,"P");
    mg->Add(g_higher,"P");
    mg->Add(g_my,"P");
    mg->SetTitle(";Kinetic energy (eV);Cross section (mb)");
    //g_theo1->GetYaxis()->CenterTitle(kTRUE);
    //g_thr->GetYaxis()->CenterTitle(kTRUE);
    //g_higher->GetYaxis()->CenterTitle(kTRUE);
    //g_my->GetYaxis()->CenterTitle(kTRUE);
    //mg->GetXaxis()->CenterTitle(kTRUE);
    //mg->GetYaxis()->CenterTitle(kTRUE);
    TCanvas* c1 = new TCanvas("c1","c1",1920,1080);
    //mg->GetXaxis()->CenterTitle(kTRUE);
    //g_theo1->GetXaxis()->SetRangeUser(2.5e-4,2.5e2);
    //mg->GetYaxis()->CenterTitle(kTRUE);
    g_theo1->GetYaxis()->SetRangeUser(1.e-5,1.e7);
    //g_theo->Draw("A");
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    mg->Draw("A");
    c1->BuildLegend();



    mg2->Add(g_theo2,"LP");
    mg2->Add(g_thr,"P");
    mg2->Add(g_my,"P");
    mg2->SetTitle(";Kinetic energy (eV);Cross section (mb)");
    mg2->GetXaxis()->CenterTitle(kTRUE);
    mg2->GetXaxis()->SetLabelSize(0.07);
    mg2->GetXaxis()->SetTitleSize(0.08);
    mg2->GetXaxis()->SetTitleOffset(0.88);
    mg2->GetYaxis()->CenterTitle(kTRUE);
    mg2->GetYaxis()->SetLabelSize(0.07);
    mg2->GetYaxis()->SetTitleSize(0.08);
    mg2->GetYaxis()->SetTitleOffset(0.7);
    TCanvas* c2 = new TCanvas("c2","c2",1760,1060);
    mg2->Draw("A");
    c2->BuildLegend();



}



void fitter(int& npar, double* gin, double& f, double* par, int iflag){

    f = 0.;
    const double KE = par[0];
    const double nuisance_CS = par[1];

    const double diff = (CSAD*(1.+nuisance_CS)-g_theo->Eval(KE));
    const double pull = nuisance_CS/CSADerr;


    //f = diff*diff/g_theo->Eval(KE) + pull*pull;
    f = diff*diff/CSAD + pull*pull;
    //f = diff*diff;


}



Uncertainty FindEqKE(){

    TMinuit* minimizer = new TMinuit(2);
    minimizer->SetFCN(fitter);
    minimizer->DefineParameter(0, "KE", 0.02, 0.1, 0.0195, 0.021);
    minimizer->DefineParameter(1, "nuisance_CS", 0, 0.01, -100, 100);
    //minimizer->FixParameter(1);
    minimizer->Command("MIGRAD");
    minimizer->Command("MIGRAD");
    //minimizer->Command("MINOS");
    minimizer->Command("HESSE");
    

    double x, x_err;
    minimizer->GetParameter(0,x,x_err);
    Uncertainty temp(x,x_err);


    return temp;



}



