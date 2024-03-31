#include "/Users/chengyuchin/Analysis/nC/EndGame/Uncertainty.h"


const double CSAD = 0.309531;
const double CSADerr = 0.00158708/CSAD;
TGraphErrors* g_theo;
Uncertainty FindEqKE();
void fitter(int& npar, double* gin, double& f, double* par, int iflag);

void PlotComparison_nH(){

    gROOT->ForceStyle();
    gStyle->SetLegendTextSize(0.05);
    gStyle->SetOptStat(0);


    const double E_thr[8] = {2.53e-2,2.53e-2,2.53e-2,2.53e-2,2.53e-2,2.53e-2,2.53e-2,2.53e-2};
    const double CS_thr[8] = {0.3363,0.329,0.3326,0.3356,0.3342,0.3331,0.328,0.326};
    const double CSe_thr[8] = {1.5e-3,2.e-3,7.e-4,8.2e-3,5.e-4,3.e-3,4.e-3,3.e-3};
    const double E_higher[21] = {20.e3,40.e3,64.e3,3.85e7,6.08e7,7.62e7,2.5e7,4.5e7,5.e7,5.51e7,6.16e7,7.e7,3.7e7,4.22e7,4.73e7,5.24e7,5.74e7,6.25e7,
                                7.26e7,1.44e7,5.5e5};
    const double CS_higher[21] = {318.e-6,203.e-6,151e-6,2.062e-5,1.662e-5,1.413e-5,2.66e-5,1.706e-5,1.607e-5,1.516e-5,1.4e-5,1.375e-5,2.12e-5,2.06e-5,
                                1.7e-5,1.76e-5,1.58e-5,1.46e-5,1.47e-5,3.06e-5,35.2e-6};
    const double CSe_higher[21] = {25.e-6,19.e-6,7.e-6,3.9e-7,2.0e-7,1.9e-7,1.5e-6,6.1e-7,7.8e-7,8.4e-7,4.9e-7,7.3e-7,1.6e-6,1.4e-6,7.e-7,
                                9.e-7,1.1e-6,1.1e-6,1.1e-6,1.8e-6,2.4e-6};
    TMultiGraph* mg = new TMultiGraph();
    TMultiGraph* mg2 = new TMultiGraph();
    TGraphErrors* g_thr = new TGraphErrors(8,E_thr,CS_thr,nullptr,CSe_thr);
    TGraphErrors* g_higher = new TGraphErrors(21,E_higher,CS_higher,nullptr,CSe_higher);
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
    g_my->SetMarkerSize(1.3);


    TFile* f = new TFile("./CScurve_nH.root");
    //TFile* f = new TFile("./CScurveAddMine.root");
    g_theo = f->Get<TGraphErrors>("CS");
    g_theo->SetLineColor(8);
    g_theo->SetMarkerStyle(20);
    g_theo->SetMarkerColor(8);
    g_theo->SetTitle("ENDF curve");
    Uncertainty eqKE = FindEqKE();
    g_my->SetPoint(0,eqKE.GetValue(),0.309492);
    g_my->SetPointError(0,eqKE.GetError(),0.0031016471);
    cout << "eq KE = " << eqKE << endl;
    TGraphErrors* g_theo2 = new TGraphErrors();
    const double dx = (0.1-0.001)/100.;
    //for(int i = 0; i<100; i++) g_theo2->SetPoint(i, 0.001+i*dx, g_theo->Eval(0.001+i*dx));
    //for(int i = 0; i<5; i++) g_theo2->SetPoint(i, 0.001+i*dx*20., g_theo->Eval(0.001+i*dx*20.));
    for(int i = 0; i<31; i++) g_theo2->SetPoint(i, g_theo->GetPointX(i+103), g_theo->GetPointY(i+103));
    g_theo2->SetLineColor(8);
    g_theo2->SetMarkerStyle(20);
    g_theo2->SetMarkerColor(8);
    g_theo2->SetLineWidth(9);
    g_theo2->SetTitle("ENDF curve");



    mg->Add(g_theo,"L");
    mg->Add(g_thr,"P");
    mg->Add(g_higher,"P");
    //mg->Add(g_my,"P");
    mg->SetTitle(";E^{kin}_{n}(eV);#sigma(b)");
    g_theo->GetYaxis()->CenterTitle(kTRUE);
    g_thr->GetYaxis()->CenterTitle(kTRUE);
    g_higher->GetYaxis()->CenterTitle(kTRUE);
    g_my->GetYaxis()->CenterTitle(kTRUE);
    //mg->GetXaxis()->CenterTitle(kTRUE);
    //mg->GetYaxis()->CenterTitle(kTRUE);
    TCanvas* c1 = new TCanvas("c1","c1",1920,1080);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    //g_theo->Draw("A");
    mg->Draw("A");
    c1->BuildLegend();



    mg2->Add(g_theo2,"LP");
    mg2->Add(g_thr,"P");
    mg2->Add(g_my,"P");
    mg2->SetTitle(";Kinetic energy (eV);Cross section (b)");
    mg2->GetXaxis()->CenterTitle(kTRUE);
    mg2->GetXaxis()->SetLabelSize(0.06);
    mg2->GetXaxis()->SetTitleSize(0.08);
    mg2->GetXaxis()->SetTitleOffset(0.88);
    mg2->GetYaxis()->CenterTitle(kTRUE);
    mg2->GetYaxis()->SetLabelSize(0.06);
    mg2->GetYaxis()->SetTitleSize(0.08);
    mg2->GetYaxis()->SetTitleOffset(0.75);
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
    f = diff*diff/CSAD/CSAD + pull*pull;
    //f = diff*diff;


}



Uncertainty FindEqKE(){

    TMinuit* minimizer = new TMinuit(2);
    minimizer->SetFCN(fitter);
    minimizer->DefineParameter(0, "KE", 0.029, 0.1, 0.029, 0.0295);
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



