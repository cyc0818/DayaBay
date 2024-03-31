#include <iostream>
#include <cmath>
#include <string>
#include <vector>



#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TTree.h"
#include "TF1.h"
#include "UserSetting.h"
#include "Fitter.h"
#include "TH1functions.h"


using namespace std;



struct Plots{
    TH1D* MCnGd;
    TH1D* MCnH;
    TH1D* MCnC;
    TH1D* MCSum;
    TH1D* Data;
    TH1D* mdfMCnGd;
    TH1D* mdfMCnH;
    TH1D* mdfMCnC;
    TH1D* nC;
    TH1D* MCOverData;
    TH1D* PerfH;
    TH1D* PerfGd;
    TF1* fMCGd;
    TF1* fMCH;
    TF1* fMCC;
    TF1* fDataGd;
    TF1* fDataH;
    TF1* fDataC;    // for Part 2
    TF1* fC;    // Gaussian
    TF1* fData;
    TF1* fsysL;
    TF1* fsysR;
    TGraphErrors* sCurve;
    TGraphErrors* sCurve2;
    TGraphErrors* syserr;
    TString Name;
    double sGd;
    double rGd;
    double cGd;
    double sH;
    double rH;
    double cH;
    double sC;
    double rC;
};






bool GetMC(TString filename, Plots* AD);
bool GetRealData(TString filename, Plots* AD);
bool GetSitefromAD(Plots* AD, Plots* Site); 
double GetnGdDiffandRatio(Plots& p);
double GetnHDiffandRatio(Plots& p);
bool MCParameter_Writer(TString txt_path, Plots Site);
bool Result_Writer(TString txt_path, TString sitename, double C, double errorC, double Gd, double errorGd, double H, double errorH, bool addtitle, 
        bool Real, int method);
void TFile_Writer(TString filename, Plots* Site);
void GetSystematic(Plots p);





TCanvas* c[50];
int CanvasNo = 0;
TF1* error_AoverB = new TF1("error_AoverB","([0]/[1])*sqrt(([2]/[0])^2+([3]/[1])^2)",0,0);    // Parameters(A,B,sigmaA,sigmaB)
TF1* error_AminusB = new TF1("error_AminusB","sqrt(([0])^2+([1])^2)",0,0);    // Parameters(sigmaA,sigmaB)
bool have_written = false;





void Extract_nC(){

    if(evaluating_method != 1 && evaluating_method != 2){
        cerr << "Error! Method should be 1 or 2" << endl;
        return 0;
    }
    gStyle->SetOptFit(1);


    Plots AD[9];
    Plots Site[2];
    TMultiGraph* sumsCurve = new TMultiGraph();
    TMultiGraph* sumrCurve = new TMultiGraph();
    TGraphErrors* HOverGd = new TGraphErrors();
    TGraphErrors* rCurve[3] = {new TGraphErrors(), new TGraphErrors(), new TGraphErrors()};     // nH, nGd, nC
    TH1D* MCFitPerf[2];     // nH, nGd

TF1* ff[9];

    double C, errorC;
    double Gd, errorGd;
    double H, errorH;


    Site[0].Name = "Near";
    Site[1].Name = "Far";
    //double* tunefactor = new double[2]{1,1};        //dynamic announcement for preventing memory corruption


    GetMC("/Users/chengyuchin/Analysis/data/MC/NTUNoEdCut_Plots.root",AD);
    GetRealData("/Users/chengyuchin/Analysis/P17B_IBD_AdSimple.root",AD);


    for(int ADNo = 1; ADNo<9; ADNo++){
        
        // create new histogram, graph, MC fitter
        AD[ADNo].Name = TString::Format("AD%d",ADNo);
        AD[ADNo].mdfMCnGd = new TH1D("ModifiedMC_nGd_"+AD[ADNo].Name, "ModifiedMC_nGd_"+AD[ADNo].Name, 1200, 0, 12);
        AD[ADNo].mdfMCnH = new TH1D("ModifiedMC_nH_"+AD[ADNo].Name, "ModifiedMC_nH_"+AD[ADNo].Name, 1200, 0, 12);
        AD[ADNo].sCurve = new TGraphErrors();
        if(ADNo == 1){
            AD[ADNo].fMCGd = new TF1("fMCGd", nGdFitter, 6, 9.2, 5);
            AD[ADNo].fMCH = new TF1("fMCH", MCnHFitter, MCnH_LowEdge, 2.7, 5);
        }
        else{
            AD[ADNo].fMCGd = AD[1].fMCGd;
            AD[ADNo].fMCH = AD[1].fMCH;
        }


        // translation to make two peak overlap
        *(AD[ADNo].mdfMCnH) = Translation(*(AD[ADNo].MCnH), (int)round(GetnHDiffandRatio(AD[ADNo])/AD[ADNo].MCnH->GetXaxis()->GetBinWidth(1)));
        *(AD[ADNo].mdfMCnGd) = Translation(*(AD[ADNo].MCnGd), (int)round(GetnGdDiffandRatio(AD[ADNo])/AD[ADNo].MCnGd->GetXaxis()->GetBinWidth(1)));


        // normalize to make two distribution overlap
        AD[ADNo].mdfMCnGd->Scale(AD[ADNo].rGd);
        AD[ADNo].mdfMCnH->Scale(AD[ADNo].rH);


        // Gaussian smearing
        if(Smear){
            AD[ADNo].cGd = 0.95*sqrt(AD[ADNo].fDataGd->GetParameter(2)*AD[ADNo].fDataGd->GetParameter(2)
                                    -AD[ADNo].fMCGd->GetParameter(2)*AD[ADNo].fMCGd->GetParameter(2));
            AD[ADNo].cH = 0.95*sqrt(AD[ADNo].fDataH->GetParameter(2)*AD[ADNo].fDataH->GetParameter(2)
                                   -AD[ADNo].fMCH->GetParameter(2)*AD[ADNo].fMCH->GetParameter(2));
    cout << ADNo << " , " << AD[ADNo].cH << endl;
            GaussianBinSmear(AD[ADNo].mdfMCnGd, AD[ADNo].cGd);
            GaussianBinSmear(AD[ADNo].mdfMCnH, AD[ADNo].cH);
    /*c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    ff[ADNo] = new TF1(TString::Format("ff%d",ADNo),MCnHFitter, 1.5, 2.7, 5); 
    for(int i = 0; i<5; i++) ff[ADNo]->SetParameter(i,AD[ADNo].fDataH->GetParameter(i));
    ff[ADNo]->SetParNames("N_{H}", "#mu_{H}", "#sigma_{H}", "#alpha_{H}", "n_{H}");
    AD[ADNo].mdfMCnH->Fit(ff[ADNo],"","",1.5,2.7);
    CanvasNo++;*/
        }


        // set points of s-Curve
        AD[ADNo].sCurve->SetName(AD[ADNo].Name);
        AD[ADNo].sCurve->SetMarkerStyle(47);
        AD[ADNo].sCurve->SetMarkerColor(ADNo);


        AD[ADNo].sCurve->SetPoint(0,AD[ADNo].fDataH->GetParameter(1),AD[ADNo].sH);
        error_AminusB->SetParameters(AD[ADNo].fDataH->GetParError(1),AD[ADNo].fMCH->GetParError(1));
        AD[ADNo].sCurve->SetPointError(0,AD[ADNo].fDataH->GetParError(1),error_AminusB->Eval(0));


        AD[ADNo].sCurve->SetPoint(1,AD[ADNo].fDataGd->GetParameter(1),AD[ADNo].sGd);
        error_AminusB->SetParameters(AD[ADNo].fDataGd->GetParError(1),AD[ADNo].fMCGd->GetParError(1));
        AD[ADNo].sCurve->SetPointError(1,AD[ADNo].fDataGd->GetParError(1),error_AminusB->Eval(0));
        sumsCurve->Add(AD[ADNo].sCurve);


        // set points of r-Curve
        rCurve[0]->SetPoint(ADNo-1,ADNo,AD[ADNo].rH);
        error_AoverB->SetParameters(AD[ADNo].fDataH->GetParameter(0), AD[ADNo].fMCH->GetParameter(0),
                                    AD[ADNo].fDataH->GetParError(0), AD[ADNo].fMCH->GetParError(0));
        rCurve[0]->SetPointError(ADNo-1,0,error_AoverB->Eval(0));


        rCurve[1]->SetPoint(ADNo-1,ADNo,AD[ADNo].rGd);
        error_AoverB->SetParameters(AD[ADNo].fDataGd->GetParameter(0), AD[ADNo].fMCGd->GetParameter(0),
                                    AD[ADNo].fDataGd->GetParError(0), AD[ADNo].fMCGd->GetParError(0));
        rCurve[1]->SetPointError(ADNo-1,0,error_AoverB->Eval(0));


        // set point of nH/nGd
        if(evaluating_method == 1){
            HOverGd->SetPoint(ADNo-1,ADNo,AD[ADNo].fDataH->GetParameter(0)/AD[ADNo].fDataGd->GetParameter(0));
            error_AoverB->SetParameters(AD[ADNo].fDataH->GetParameter(0), AD[ADNo].fDataGd->GetParameter(0),
                                        AD[ADNo].fDataH->GetParError(0), AD[ADNo].fDataGd->GetParError(0));
            HOverGd->SetPointError(ADNo-1,0,error_AoverB->Eval(0));
        }


        if(evaluating_method == 2){
            H = AD[ADNo].Data->IntegralAndError(AD[ADNo].Data->FindBin(1.9),AD[ADNo].Data->FindBin(2.699),errorH);
            Gd = AD[ADNo].Data->IntegralAndError(AD[ADNo].Data->FindBin(6),AD[ADNo].Data->FindBin(12),errorGd);
            HOverGd->SetPoint(ADNo-1,ADNo,H/Gd);
            error_AoverB->SetParameters(H,Gd,errorH,errorGd);
            HOverGd->SetPointError(ADNo-1,0,error_AoverB->Eval(0));
        }
    }


    // plot nH/nGd curve
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    CanvasNo++;
    HOverGd->SetNameTitle("nH/nGd",";AD;nH/nGd");
    HOverGd->SetMarkerStyle(47);
    HOverGd->SetMarkerColor(2);
    HOverGd->Draw("ap");


    const int a = CanvasNo;
    if(OnlyCheckFittingPerf){       // only check fitting performance in each AD and MC then return

        for(int i = 0; i<4; i++){
            c[a+i] = new TCanvas(TString::Format("c%d",a+i),TString::Format("c%d",a+i),1600,900);
        }


        for(int ADNo = 1; ADNo<9; ADNo++){

            // create new histogram for AD
            AD[ADNo].PerfH = new TH1D();
            AD[ADNo].PerfGd = new TH1D();


            // filling histogram of AD
            *(AD[ADNo].PerfH) = GetFitPerformance(AD[ADNo].Data, AD[ADNo].fDataH, "PerfH_"+AD[ADNo].Name, (int)((2.7-1.9)/0.01), 1.9, 2.7);
            *(AD[ADNo].PerfGd) = GetFitPerformance(AD[ADNo].Data, AD[ADNo].fDataGd, "PerfGd_"+AD[ADNo].Name, (int)((9.2-6)/0.01), 6, 9.2);


            // plotting histogram of AD
            if(ADNo < 5){
                c[a]->cd();
                AD[ADNo].PerfH->SetLineColor(ADNo);
                AD[ADNo].PerfH->Draw("same");
                c[a+1]->cd();
                AD[ADNo].PerfGd->SetLineColor(ADNo);
                AD[ADNo].PerfGd->Draw("same");
            }


            else{
                c[a+2]->cd();
                AD[ADNo].PerfH->SetLineColor(ADNo-4);
                AD[ADNo].PerfH->Draw("same");
                c[a+3]->cd();
                AD[ADNo].PerfGd->SetLineColor(ADNo-4);
                AD[ADNo].PerfGd->Draw("same");
            }
        }


        for(int i = 0; i<4; i++){
            c[a+i]->BuildLegend();
        }


        // create new histogram for MC
        MCFitPerf[0] = new TH1D();
        MCFitPerf[1] = new TH1D();


        // filling histogram of MC
        *(MCFitPerf[0]) = GetFitPerformance(AD[1].MCnH, AD[1].fMCH, "PerfH_MC", (int)((2.7-MCnH_LowEdge)/0.01), MCnH_LowEdge, 2.7);
        *(MCFitPerf[1]) = GetFitPerformance(AD[1].MCnGd, AD[1].fMCGd, "PerfGd_MC", (int)((9.2-6)/0.01), 6, 9.2);


        // plotting histogram of MC
        CanvasNo += 4;
        for(int i = 0; i<2; i++){
            c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
            MCFitPerf[i]->Draw();
            CanvasNo++;
        }


        return 1;

    }


    GetSitefromAD(AD, Site);
    const double w = Site[0].Data->GetXaxis()->GetBinWidth(1);
    double x;
    double muR , muL;
    TF1* fcorr = new TF1("fcorr","pol1",4,6);


    // Part1 : Direct Subtraction
    for(int SNo = 0; SNo<2; SNo++){

        // create new histogram, MC fitter, graph
        Site[SNo].mdfMCnGd = new TH1D("ModifiedMC_nGd_"+Site[SNo].Name, "ModifiedMC_nGd_"+Site[SNo].Name, 1200, 0, 12);
        Site[SNo].mdfMCnH = new TH1D("ModifiedMC_nH_"+Site[SNo].Name, "ModifiedMC_nH_"+Site[SNo].Name, 1200, 0, 12);
        Site[SNo].nC = new TH1D("nC_"+Site[SNo].Name, "nC_"+Site[SNo].Name, 1200, 0, 12);
        Site[SNo].fMCGd = new TF1("fMCGd", nGdFitter, 6, 9.2, 5);
        Site[SNo].fMCH = new TF1("fMCH", MCnHFitter, MCnH_LowEdge, 2.7, 5);
        Site[SNo].syserr = new TGraphErrors();
        Site[SNo].syserr->SetNameTitle("Systematic_"+Site[SNo].Name,";E_{d}(MeV);Data-MC");
        Site[SNo].fsysL = new TF1("fsysL_"+Site[SNo].Name,"pol0",3,7);
        Site[SNo].fsysR = new TF1("fsysR_"+Site[SNo].Name,"pol0",3,7);
        

        // translation to make two peak overlap
        *(Site[SNo].mdfMCnH) = Translation(*(Site[SNo].MCnH), (int)round(GetnHDiffandRatio(Site[SNo])/Site[SNo].MCnH->GetXaxis()->GetBinWidth(1)));
        *(Site[SNo].mdfMCnGd) = Translation(*(Site[SNo].MCnGd), (int)round(GetnGdDiffandRatio(Site[SNo])/Site[SNo].MCnGd->GetXaxis()->GetBinWidth(1)));


        // normalize to make two distribution overlap
        //Site[SNo].mdfMCnGd->Scale(Site[SNo].rGd);
        //Site[SNo].mdfMCnH->Scale(Site[SNo].rH);


        // set name
        Site[SNo].mdfMCnGd->SetNameTitle("RescaledMC_nGd_"+Site[SNo].Name, "RescaledMC_nGd_"+Site[SNo].Name);
        Site[SNo].mdfMCnH->SetNameTitle("RescaledMC_nH_"+Site[SNo].Name, "RescaledMC_nH_"+Site[SNo].Name);


        // subtract data by MC
        Site[SNo].nC->Add(Site[SNo].Data, Site[SNo].mdfMCnGd, 1, -1);
        Site[SNo].nC->Add(Site[SNo].mdfMCnH, -1);


        // estimate the systematic error
        for(int i = 0; i<(4.-3.)/w; i++){
            x = 3+i*w;
            Site[SNo].syserr->SetPoint(i, Site[SNo].nC->GetBinCenter(Site[SNo].nC->FindBin((x+0.1*w))), 
                                       Site[SNo].nC->GetBinContent(Site[SNo].nC->FindBin((x+0.1*w))));
            Site[SNo].syserr->SetPointError(i, 0, Site[SNo].nC->GetBinError(Site[SNo].nC->FindBin((x+0.1*w))));
        }
        for(int i = 0; i<(7.-6.)/w; i++){
            x = 6+i*w;
            Site[SNo].syserr->SetPoint(i+100, Site[SNo].nC->GetBinCenter(Site[SNo].nC->FindBin((x+0.1*w))), 
                                       Site[SNo].nC->GetBinContent(Site[SNo].nC->FindBin((x+0.1*w))));
            Site[SNo].syserr->SetPointError(i+100, 0, Site[SNo].nC->GetBinError(Site[SNo].nC->FindBin((x+0.1*w))));
        }


        // plotting
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        gPad->SetLogy(1);
        Site[SNo].Data->Draw("HIST");
        Site[SNo].mdfMCnGd->SetLineColor(2);
        Site[SNo].mdfMCnGd->DrawCopy("SAME HIST");
        Site[SNo].mdfMCnH->SetLineColor(6);
        Site[SNo].mdfMCnH->DrawCopy("SAME HIST");
        c[CanvasNo]->BuildLegend();
        CanvasNo++;


        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        Site[SNo].syserr->SetMarkerStyle(8);
        Site[SNo].syserr->Draw("ap");
        Site[SNo].syserr->Fit(Site[SNo].fsysL,"","",3,4);
        Site[SNo].syserr->Fit(Site[SNo].fsysR,"+","",6,7);
        CanvasNo++;


        // correction
        if(Correction){
            muL = Site[SNo].fsysL->GetParameter(0) + 0.5*nsigmaL*Site[SNo].fsysL->GetParError(0); 
            muR = Site[SNo].fsysR->GetParameter(0) + 0.5*nsigmaR*Site[SNo].fsysR->GetParError(0); 
            fcorr->SetParameter(0, 3*muL-2*muR);
            fcorr->SetParameter(1, (muR-muL)/2);
            for(int i = 0; i<(4.-3.)/w + 1; i++){
                x = 3+i*w;
                Site[SNo].nC->AddBinContent(Site[SNo].nC->FindBin(x+0.1*w),-1*muL);
            }

            for(int i = 0; i<(6.-4.)/w + 1; i++){
                x = 4+i*w;
                Site[SNo].nC->AddBinContent(Site[SNo].nC->FindBin(x+0.1*w),-1*fcorr->Eval(x+0.5*w));
            }
            
            for(int i = 0; i<(7.-6.)/w + 1; i++){
                x = 6+i*w;
                Site[SNo].nC->AddBinContent(Site[SNo].nC->FindBin(x+0.1*w),-1*muR);
            }

        }


        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        CanvasNo++;
        Site[SNo].fC = new TF1("fC_"+Site[SNo].Name, nCFitter3, nC_LowEdge, nC_HighEdge, 4);
        Site[SNo].fC->SetParNames("N_{C}","#mu_{C}","#sigma_{C}","const");
        Site[SNo].fC->SetParameters(1e3,4.9,0.2);
        Site[SNo].fC->FixParameter(3,(Site[SNo].fsysL->GetParameter(0)-Site[SNo].fsysL->GetParError(0)
                                     +Site[SNo].fsysR->GetParameter(0)-Site[SNo].fsysR->GetParError(0))/2);
        Site[SNo].nC->GetXaxis()->SetRangeUser(3.5,6.5);
        //Site[SNo].nC->Draw();
        Site[SNo].nC->Fit(Site[SNo].fC,"","",nC_LowEdge,5.5);
        Site[SNo].nC->Fit(Site[SNo].fC,"","",nC_LowEdge,nC_HighEdge);
        TF1* fdash = new TF1("fdash","pol0",3.5,6.5);
        fdash->SetParameter(0,Site[SNo].fC->GetParameter(3));
        fdash->SetLineColor(2);
        fdash->SetLineStyle(7);
        fdash->DrawCopy("same");


        // clear modified histogram
        //Site[SNo].mdfMCnGd->Reset();
        //Site[SNo].mdfMCnH->Reset();
    }


    // print the production rate
    cout << "----------------------Direct Subtraction-------------------------" << endl;
    if(evaluating_method == 1) cout << "------------------(Evaluating by fitting parameter)--------------------" << endl;
    if(evaluating_method == 2) cout << "------------------(Evaluating by integrating number of events)--------------------" << endl;
    cout << "----------------------Real Data Counting------------------------- , LowEdge_C = " << nC_LowEdge;
    cout << " , HighEdge_C = " << nC_HighEdge << endl;

        
    for(int SNo = 0; SNo<2; SNo++){        // 0 = near site , 1 = far site

        if(evaluating_method == 1){
            C = Site[SNo].fC->GetParameter(0);
            errorC = Site[SNo].fC->GetParError(0);
            Gd = Site[SNo].fDataGd->GetParameter(0);
            errorGd = Site[SNo].fDataGd->GetParError(0);
            H = Site[SNo].fDataH->GetParameter(0);
            errorH = Site[SNo].fDataH->GetParError(0);
        }


        if(evaluating_method == 2){
            C = Site[SNo].nC->IntegralAndError(Site[SNo].nC->FindBin(nC_LowEdge),Site[SNo].nC->FindBin(5.799),errorC);
            Gd = Site[SNo].Data->IntegralAndError(Site[SNo].Data->FindBin(6),Site[SNo].Data->FindBin(9.999),errorGd);
            H = Site[SNo].Data->IntegralAndError(Site[SNo].Data->FindBin(1.9),Site[SNo].Data->FindBin(2.699),errorH);
        }


        cout << Site[SNo].Name << " Site : nC Captured = " << C << " +/- " << errorC << endl;
        cout << Site[SNo].Name << " Site : nGd Captured = " << Gd  << " +/- " << errorGd << endl;
        cout << Site[SNo].Name << " Site : nH Captured = " << H  << " +/- " << errorH << endl;
        cout << Site[SNo].Name << " Site : Systematic error of nC = " << -1*Site[SNo].fsysL->Integral(4,5.8)/w << " , ";
        cout << -1*Site[SNo].fsysR->Integral(4,5.8)/w << endl;


        error_AoverB->SetParameters(H,Gd,errorH,errorGd);
        cout << Site[SNo].Name << " Site : nH/nGd = " << 100*H/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        error_AoverB->SetParameters(C,Gd,errorC,errorGd);
        cout << Site[SNo].Name << " Site : nC/nGd = " << 100*C/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        cout << Site[SNo].Name << " Site : Systematic error of nC/nGd = " << -100*Site[SNo].fsysL->Integral(4,5.8)/(w*Gd) << " , ";
        cout << -100*Site[SNo].fsysR->Integral(4,5.8)/(w*Gd) << " %" << endl;
        error_AoverB->SetParameters(C,H,errorC,errorH);
        cout << Site[SNo].Name << " Site : nC/nH = " << 100*C/H << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        cout << Site[SNo].Name << " Site : Systematic error of nC/nH = " << -100*Site[SNo].fsysL->Integral(4,5.8)/(w*H) << " , ";
        cout << -100*Site[SNo].fsysR->Integral(4,5.8)/(w*H) << " %" << endl;
        cout << endl;


        if(Result_output) Result_Writer("/Users/chengyuchin/Analysis/note/nC_result.txt", 
                Site[SNo].Name, C, errorC, Gd, errorGd, H, errorH, !(bool)SNo, true, evaluating_method);

    }


    TF1* component1 = new TF1("component_1", MCnCFitter, 2.5, 5.8, 8);
    component1->SetLineColor(6);
    component1->SetLineStyle(5);
    TF1* component2 = new TF1("component_2", MCnCFitter, 2.5, 5.8, 8);
    component2->SetLineColor(8);
    component2->SetLineStyle(5);

    
    // MC nC Fitting
    AD[1].fMCC = new TF1("fMCC", MCnCFitter, 2.5, 5.8, 8);
    AD[1].fMCC->SetParNames("N_{1}","#mu_{1}","#sigma_{1}","#alpha","n","N_{2}","#mu_{2}","#sigma_{2}");
    AD[1].fMCC->SetParameters(1750,5.15,0.23,1.4,0.5,150,3.92,0.28);
    AD[1].fMCC->SetParLimits(0,3000,20000);
    AD[1].fMCC->SetParLimits(1,5,5.3);
    AD[1].fMCC->SetParLimits(2,0.17,0.27);
    AD[1].fMCC->SetParLimits(3,0.5,3);
    AD[1].fMCC->SetParLimits(4,0,5);
    AD[1].fMCC->SetParLimits(5,100,2000);
    AD[1].fMCC->SetParLimits(6,3.7,4.2);
    AD[1].fMCC->SetParLimits(7,0.1,0.4);
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    gPad->SetLogy(1);
    AD[1].MCnC->Fit(AD[1].fMCC,"","",2.5,5.8);
    AD[1].MCnC->Fit(AD[1].fMCC,"","",2.5,5.8);

    for(int i = 0; i<5; i++){
        component1->SetParameter(i,AD[1].fMCC->GetParameter(i));
        if(i < 3) component2->SetParameter(i,AD[1].fMCC->GetParameter(i+5));
        else component2->SetParameter(i,50);
    }
    component1->SetParameter(5,1e-4);
    component2->SetParameter(5,1e-4);
    component1->SetParameter(7,1e3);
    component2->SetParameter(7,1e3);
        

    component1->DrawCopy("same");
    component2->DrawCopy("same");
    c[CanvasNo]->BuildLegend();
    AD[1].MCnC->GetXaxis()->SetRangeUser(2,7);
    CanvasNo++;
    

    cout << "----------------------Direct Subtraction-------------------------" << endl;
    if(evaluating_method == 1) cout << "------------------(Evaluating by fitting parameter)--------------------" << endl;
    if(evaluating_method == 2) cout << "------------------(Evaluating by integrating number of events)--------------------" << endl;


    double SH;  // s-factor of site compared to original MC nH peak
    double SGd; // s-factor of site compared to original MC nGd peak
    double sum_rH;
    double sum_rHsH;
    double sum_rGd;
    double sum_rGdsGd;


    // MC nC counting
    for(int SNo = 0; SNo<2; SNo++){

        // create new histogram, graph, and evaluate s-factor and r-factor
        Site[SNo].MCnC = AD[1].MCnC;
        Site[SNo].fMCC = AD[1].fMCC;
        Site[SNo].sC = Site[SNo].fC->GetParameter(1) - Site[SNo].fMCC->GetParameter(1);
        Site[SNo].rC = Site[SNo].fC->GetParameter(0) / Site[SNo].fMCC->GetParameter(0);
        SGd = Site[SNo].fDataGd->GetParameter(1)-AD[1].fMCGd->GetParameter(1);
        SH = Site[SNo].fDataH->GetParameter(1)-AD[1].fMCH->GetParameter(1);
        Site[SNo].mdfMCnC = new TH1D("ModifiedMC_nC_"+Site[SNo].Name, "ModifiedMC_nC_"+Site[SNo].Name, 1200, 0, 12);
        Site[SNo].MCSum = new TH1D("MC_Sum_"+Site[SNo].Name, "MC_Sum_"+Site[SNo].Name, 1200, 0, 12);
        Site[SNo].MCOverData = new TH1D("MCOverData_"+Site[SNo].Name, "MCOverData_"+Site[SNo].Name, 1200, 0, 12);
        Site[SNo].sCurve = new TGraphErrors();      // s-factor when compare to modified MC
        Site[SNo].sCurve2 = new TGraphErrors();     // s-factor when compare to original MC


        // translation to make two peak overlap
        *(Site[SNo].mdfMCnC) = Translation(*(Site[SNo].MCnC), (int)round(Site[SNo].sC/Site[SNo].MCnC->GetXaxis()->GetBinWidth(1)));


        // output the MC result
        if(evaluating_method == 1){
            C = Site[SNo].fMCC->Integral(nC_LowEdge,5.8) / w;
            errorC = sqrt(C);
            Gd = AD[1].fMCGd->GetParameter(0);
            errorGd = AD[1].fMCGd->GetParError(0);
            H = AD[1].fMCH->GetParameter(0);
            errorH = AD[1].fMCH->GetParError(0);
        }


        if(evaluating_method == 2){
            C = Site[SNo].mdfMCnC->IntegralAndError(Site[SNo].mdfMCnC->FindBin(nC_LowEdge),Site[SNo].mdfMCnC->FindBin(5.999),errorC);
            Gd = AD[1].MCnGd->IntegralAndError(AD[1].MCnGd->FindBin(6),AD[1].MCnGd->FindBin(9.999),errorGd);
            H = AD[1].MCnH->IntegralAndError(AD[1].MCnH->FindBin(1.9),AD[1].MCnH->FindBin(2.699),errorH) + 
                AD[1].MCnGd->Integral(AD[1].MCnGd->FindBin(1.9),AD[1].MCnGd->FindBin(2.699));
        }


        if(SNo == 1){
            cout << "----------------------MC Counting------------------------- , LowEdge_C = " << nC_LowEdge;
            cout << " , HighEdge_C = " << nC_HighEdge << endl;
            cout << "MC : nC Captured = " << C << " +/- " << errorC << endl;
            cout << "MC : nGd Captured = " << Gd  << " +/- " << errorGd << endl;
            cout << "MC : nH Captured = " << H  << " +/- " << errorH << endl;


            error_AoverB->SetParameters(H,Gd,errorH,errorGd);
            cout << "MC : nH/nGd = " << 100*H/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
            error_AoverB->SetParameters(C,Gd,errorC,errorGd);
            cout << "MC : nC/nGd = " << 100*C/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
            error_AoverB->SetParameters(C,H,errorC,errorH);
            cout << "MC : nC/nH = " << 100*C/H << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
            cout << endl;


            if(Result_output) have_written = Result_Writer("/Users/chengyuchin/Analysis/note/nC_result.txt", 
                    Site[SNo].Name, C, errorC, Gd, errorGd, H, errorH, !(bool)SNo, false, evaluating_method);
        }
        error_AminusB->SetParameters(Site[SNo].fC->GetParError(1),Site[SNo].fMCC->GetParError(1));
        cout << Site[SNo].Name << " Site : sC = " << Site[SNo].sC << " +/- " << error_AminusB->Eval(0) << endl;


        // normalize to make nC overlap
        Site[SNo].mdfMCnC->Scale(Site[SNo].rC);


        // sum over all MC histogram
        Site[SNo].MCSum->Add(Site[SNo].mdfMCnH,1);
        Site[SNo].MCSum->Add(Site[SNo].mdfMCnGd,1);
        Site[SNo].MCSum->Add(Site[SNo].mdfMCnC,1);


        // devide number of events in MC by one in data
        *(Site[SNo].MCOverData) = *(Site[SNo].MCSum) / *(Site[SNo].Data);


        // plotting MC and data energy spectrum
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        gPad->SetLogy(1);
        Site[SNo].mdfMCnH->SetLineColor(6);
        Site[SNo].mdfMCnH->Draw("HIST");
        Site[SNo].mdfMCnGd->SetLineColor(2);
        Site[SNo].mdfMCnGd->Draw("SAME HIST");
        Site[SNo].mdfMCnC->SetLineColor(1);
        Site[SNo].mdfMCnC->Draw("SAME HIST");
        Site[SNo].MCSum->SetLineColor(8);
        Site[SNo].MCSum->Draw("SAME HIST");
        Site[SNo].Data->Draw("SAME HIST");
        c[CanvasNo]->BuildLegend();
        CanvasNo++;
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        Site[SNo].MCOverData->SetNameTitle("MCOverData_"+Site[SNo].Name, "MCOverData_"+Site[SNo].Name);
        Site[SNo].MCOverData->GetXaxis()->SetRangeUser(3,7);
        Site[SNo].MCOverData->GetYaxis()->SetRangeUser(0,2.5);
        Site[SNo].MCOverData->Draw();
        Site[SNo].MCOverData->Fit("pol1","","",3,7);
        CanvasNo++;


        // set points of s-Curve
        Site[SNo].sCurve->SetName(Site[SNo].Name + " (Compare to modified MC)");
        Site[SNo].sCurve->SetMarkerStyle(47);
        Site[SNo].sCurve->SetMarkerColor(21*SNo+50);


        Site[SNo].sCurve->SetPoint(0,Site[SNo].fDataH->GetParameter(1),Site[SNo].sH);
        error_AminusB->SetParameters(Site[SNo].fDataH->GetParError(1),Site[SNo].fMCH->GetParError(1));
        Site[SNo].sCurve->SetPointError(0,Site[SNo].fDataH->GetParError(1),error_AminusB->Eval(0));


        Site[SNo].sCurve->SetPoint(1,Site[SNo].fDataGd->GetParameter(1),Site[SNo].sGd);
        error_AminusB->SetParameters(Site[SNo].fDataGd->GetParError(1),Site[SNo].fMCGd->GetParError(1));
        Site[SNo].sCurve->SetPointError(1,Site[SNo].fDataGd->GetParError(1),error_AminusB->Eval(0));
        sumsCurve->Add(Site[SNo].sCurve);


        Site[SNo].sCurve2->SetName(Site[SNo].Name + " (Compare to original MC)");
        Site[SNo].sCurve2->SetMarkerStyle(47);
        Site[SNo].sCurve2->SetMarkerColor(40*SNo+51);


        Site[SNo].sCurve2->SetPoint(0,Site[SNo].fDataH->GetParameter(1),SH);
        error_AminusB->SetParameters(Site[SNo].fDataH->GetParError(1),AD[1].fMCH->GetParError(1));
        Site[SNo].sCurve2->SetPointError(0,Site[SNo].fDataH->GetParError(1),error_AminusB->Eval(0));


        Site[SNo].sCurve2->SetPoint(1,Site[SNo].fDataGd->GetParameter(1),SGd);
        error_AminusB->SetParameters(Site[SNo].fDataGd->GetParError(1),AD[1].fMCGd->GetParError(1));
        Site[SNo].sCurve2->SetPointError(1,Site[SNo].fDataGd->GetParError(1),error_AminusB->Eval(0));


        Site[SNo].sCurve2->SetPoint(2,Site[SNo].fC->GetParameter(1),Site[SNo].sC);
        error_AminusB->SetParameters(Site[SNo].fC->GetParError(1),Site[SNo].fMCC->GetParError(1));
        Site[SNo].sCurve2->SetPointError(2,Site[SNo].fC->GetParError(1),error_AminusB->Eval(0));
        sumsCurve->Add(Site[SNo].sCurve2);


        // set points of r-Curve
        rCurve[0]->SetPoint(SNo+8,SNo+9,Site[SNo].rH);
        error_AoverB->SetParameters(Site[SNo].fDataH->GetParameter(0), Site[SNo].fMCH->GetParameter(0),
                                    Site[SNo].fDataH->GetParError(0), Site[SNo].fMCH->GetParError(0));
        rCurve[0]->SetPointError(SNo+8,0,error_AoverB->Eval(0));


        rCurve[1]->SetPoint(SNo+8,SNo+9,Site[SNo].rGd);
        error_AoverB->SetParameters(Site[SNo].fDataGd->GetParameter(0), Site[SNo].fMCGd->GetParameter(0),
                                    Site[SNo].fDataGd->GetParError(0), Site[SNo].fMCGd->GetParError(0));
        rCurve[1]->SetPointError(SNo+8,0,error_AoverB->Eval(0));


        rCurve[2]->SetPoint(SNo,SNo+9,Site[SNo].rC);
        error_AoverB->SetParameters(Site[SNo].fC->GetParameter(0), Site[SNo].fMCC->GetParameter(0),
                                    Site[SNo].fC->GetParError(0), Site[SNo].fMCC->GetParError(0));
        rCurve[2]->SetPointError(SNo,0,error_AoverB->Eval(0));


        // check the consistency
        sum_rH = 0;
        sum_rHsH = 0;
        sum_rGd = 0;
        sum_rGdsGd = 0;
        for(int ADNo = 1; ADNo<5; ADNo++){
            sum_rH += AD[SNo*4+ADNo].rH;
            sum_rHsH += AD[SNo*4+ADNo].rH * AD[SNo*4+ADNo].sH;
            sum_rGd += AD[SNo*4+ADNo].rGd;
            sum_rGdsGd += AD[SNo*4+ADNo].rGd * AD[SNo*4+ADNo].sGd;
        }
        cout << "-------------------Check the consistency------------------" << endl; 
        error_AminusB->SetParameters(Site[SNo].fDataH->GetParError(1),AD[1].fMCH->GetParError(1));
        cout << Site[SNo].Name << " Site estimated sH value : " << sum_rHsH / sum_rH << endl;
        cout << Site[SNo].Name << " Site fitting sH value : " << SH << " +/- " << error_AminusB->Eval(0) << endl;
        cout << Site[SNo].Name << " Site sH difference(%) : " << 100*(SH-sum_rHsH/sum_rH)/(sum_rHsH/sum_rH) << endl;
        error_AminusB->SetParameters(Site[SNo].fDataGd->GetParError(1),AD[1].fMCGd->GetParError(1));
        cout << Site[SNo].Name << " Site estimated sGd value : " << sum_rGdsGd / sum_rGd << endl;
        cout << Site[SNo].Name << " Site fitting sGd value : " << SGd << " +/- " << error_AminusB->Eval(0) << endl;
        cout << Site[SNo].Name << " Site sGd difference(%) : " << 100*(SGd-sum_rGdsGd/sum_rGd)/(sum_rGdsGd/sum_rGd) << endl;
        cout << endl;

    }


    // plotting s-Curve and r-Curve
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    sumsCurve->SetNameTitle("s-factor", "s-factor;E(MeV);s");
    sumsCurve->Draw("ap");
    c[CanvasNo]->BuildLegend();
    CanvasNo++;


    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    rCurve[0]->SetNameTitle("r_{H}","r_{H}");
    rCurve[0]->SetMarkerStyle(47);
    rCurve[0]->SetMarkerColor(4);
    sumrCurve->Add(rCurve[0]);
    rCurve[1]->SetNameTitle("r_{Gd}","r_{Gd}");
    rCurve[1]->SetMarkerStyle(47);
    rCurve[1]->SetMarkerColor(2);
    sumrCurve->Add(rCurve[1]);
    rCurve[2]->SetNameTitle("r_{C}","r_{C}");
    rCurve[2]->SetMarkerStyle(47);
    rCurve[2]->SetMarkerColor(8);
    //sumrCurve->Add(rCurve[2]);
    sumrCurve->SetNameTitle("r-factor", "r-factor;AD;r");
    sumrCurve->Draw("ap");
    c[CanvasNo]->BuildLegend();
    CanvasNo++;


    if(!Part2){
        if(TFile_output) TFile_Writer("/Users/chengyuchin/Analysis/Plots/Extract_nC.root", Site);
        delete error_AoverB;
        delete error_AminusB;
        return;
    }




    // Part2 : Fitting by template pdf generated from MC nC spectrum
    TString ParNames[17] = {"N_{C}","#mu_{C}","#sigma_{C}","#alpha_{C}","n_{C}",
                            "N_{Gd}", "N2", "#alpha_{Gd}","n_{Gd}","#mu_{Gd}", "#sigma_{Gd}", "Slope",
                            "N_{H}","#mu_{H}","#sigma_{H}","#alpha_{H}","n_{H}"};


    for(int SNo = 0; SNo<2; SNo++){

        // create new function for all spectrum fitting
        Site[SNo].fDataC = new TF1("fDataC_"+Site[SNo].Name,CBFunction,1.9,9.5,5);
        Site[SNo].fDataC->SetParNames("N_{C}","#mu_{C}","#sigma_{C}","#alpha_{C}","n_{C}");
        Site[SNo].fDataC->SetParameters(Site[SNo].rC * Site[SNo].fMCC->GetParameter(0), Site[SNo].sC + Site[SNo].fMCC->GetParameter(1),
                                        Site[SNo].fMCC->GetParameter(2), Site[SNo].fMCC->GetParameter(3), Site[SNo].fMCC->GetParameter(4));
        Site[SNo].fData = new TF1("fData_"+Site[SNo].Name, DYBSpectrum,1.9,9.5,17);
        for(int i = 0; i<17; i++){
            Site[SNo].fData->SetParName(i, ParNames[i]);
            //if(i ==7 || i==8) continue;
            if(i<5) Site[SNo].fData->SetParameter(i, Site[SNo].fDataC->GetParameter(i));
            if(i>=5 && i<12) Site[SNo].fData->FixParameter(i,Site[SNo].fDataGd->GetParameter(i-5));
            if(i>=12) Site[SNo].fData->FixParameter(i,Site[SNo].fDataH->GetParameter(i-12));
        }
        Site[SNo].fData->SetParLimits(0,10,1e5);
        Site[SNo].fData->SetParLimits(1,4.5,5.5);
        Site[SNo].fData->SetParLimits(2,0.1,1);
        Site[SNo].fData->FixParameter(3,Site[SNo].fMCC->GetParameter(3));
        Site[SNo].fData->FixParameter(4,Site[SNo].fMCC->GetParameter(4));
        //Site[SNo].fData->SetParLimits(3,0,3);
        //Site[SNo].fData->SetParLimits(4,0,2);
        //Site[SNo].fData->SetParameter(7,Site[SNo].fDataGd->GetParameter(2));
        //Site[SNo].fData->SetParameter(8,Site[SNo].fDataGd->GetParameter(3));
        //Site[SNo].fData->SetParameter(12,Site[SNo].fDataH->GetParameter(0));


        // plotting
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        gPad->SetLogy(1);
        Site[SNo].Data->Fit(Site[SNo].fData,"L","",1.9,9.5);
        Site[SNo].Data->Fit(Site[SNo].fData,"L","",1.9,9.5);
        for(int i = 0; i<7; i++){
            Site[SNo].fDataGd->SetParameter(i, Site[SNo].fData->GetParameter(i+5));
            Site[SNo].fDataGd->SetParError(i, Site[SNo].fData->GetParError(i+5));
            if(i < 5){
                Site[SNo].fDataC->SetParameter(i, Site[SNo].fData->GetParameter(i));
                Site[SNo].fDataC->SetParError(i, Site[SNo].fData->GetParError(i));
                Site[SNo].fDataH->SetParameter(i, Site[SNo].fData->GetParameter(i+12));
                Site[SNo].fDataH->SetParError(i, Site[SNo].fData->GetParError(i+12));
            }
        }
        Site[SNo].fDataC->SetLineColor(1);
        Site[SNo].fDataC->SetLineStyle(5);
        Site[SNo].fDataC->DrawF1(1.9,9.5,"same");
        Site[SNo].fDataH->SetLineColor(8);
        Site[SNo].fDataH->SetLineStyle(5);
        Site[SNo].fDataH->DrawF1(1.9,9.5,"same");
        Site[SNo].fDataGd->SetLineColor(6);
        Site[SNo].fDataGd->SetLineStyle(5);
        Site[SNo].fDataGd->DrawF1(1.9,9.5,"same");
        c[CanvasNo]->BuildLegend();
        CanvasNo++;

    }


    if(TFile_output) TFile_Writer("/Users/chengyuchin/Analysis/Plots/Extract_nC.root", Site);


    // real data result output
    cout << "----------------------Count by Fitting-------------------------" << endl;
    cout << "----------------------Real Data Counting------------------------- , LowEdge_C = " << nC_LowEdge;
    cout << " , HighEdge_C = " << nC_HighEdge << endl;
    for(int SNo = 0; SNo<2; SNo++){        // 0 = near site , 1 = far site
        C = Site[SNo].fDataC->Integral(nC_LowEdge,6) / Site[SNo].Data->GetXaxis()->GetBinWidth(1);
        errorC = sqrt(C);
        Gd = Site[SNo].fDataGd->Integral(6,10) / Site[SNo].Data->GetXaxis()->GetBinWidth(1);
        errorGd = sqrt(Gd);
        H = Site[SNo].fDataH->Integral(1.9,2.7) / Site[SNo].Data->GetXaxis()->GetBinWidth(1);
        errorH = sqrt(H);
        cout << Site[SNo].Name << " Site : nC Captured = " << C << " +/- " << errorC << endl;
        cout << Site[SNo].Name << " Site : nGd Captured = " << Gd  << " +/- " << errorGd << endl;
        cout << Site[SNo].Name << " Site : nH Captured = " << H  << " +/- " << errorH << endl;


        error_AoverB->SetParameters(C,Gd,errorC,errorGd);
        cout << Site[SNo].Name << " Site : nC/nGd = " << 100*C/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        error_AoverB->SetParameters(C,H,errorC,errorH);
        cout << Site[SNo].Name << " Site : nC/nH = " << 100*C/H << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        cout << endl;


        if(Result_output) Result_Writer("/Users/chengyuchin/Analysis/note/nC_result.txt", 
                Site[SNo].Name, C, errorC, Gd, errorGd, H, errorH, !(bool)SNo, true, evaluating_method);

    }


    // MC result output
    cout << "----------------------Count by Fitting-------------------------" << endl;
    cout << "----------------------MC Counting------------------------- , LowEdge_C = " << nC_LowEdge;
    cout << " , HighEdge_C = " << nC_HighEdge << endl;
    for(int SNo = 0; SNo<2; SNo++){        // 0 = near site , 1 = far site
        Site[SNo].fMCC->SetParameter(6,Site[SNo].fMCC->GetParameter(6) - Site[SNo].fMCC->GetParameter(1) + Site[SNo].fDataC->GetParameter(1));
        Site[SNo].fMCC->SetParameter(1,Site[SNo].fDataC->GetParameter(1));
        Site[SNo].fMCH->SetParameter(1,Site[SNo].fDataH->GetParameter(1));
        Site[SNo].fMCGd->SetParameter(4,Site[SNo].fDataGd->GetParameter(4));


        C = Site[SNo].fMCC->Integral(nC_LowEdge,6) / Site[SNo].MCnC->GetXaxis()->GetBinWidth(1);
        errorC = sqrt(C);
        Gd = Site[SNo].fMCGd->Integral(6,10) / Site[SNo].MCnGd->GetXaxis()->GetBinWidth(1);
        errorGd = sqrt(Gd);
        H = Site[SNo].fMCH->Integral(1.9,2.7) / Site[SNo].MCnH->GetXaxis()->GetBinWidth(1);
        errorH = sqrt(H);
        cout << Site[SNo].Name << " Site : nC Captured = " << C << " +/- " << errorC << endl;
        cout << Site[SNo].Name << " Site : nGd Captured = " << Gd  << " +/- " << errorGd << endl;
        cout << Site[SNo].Name << " Site : nH Captured = " << H  << " +/- " << errorH << endl;


        error_AoverB->SetParameters(C,Gd,errorC,errorGd);
        cout << Site[SNo].Name << " Site : nC/nGd = " << 100*C/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        error_AoverB->SetParameters(C,H,errorC,errorH);
        cout << Site[SNo].Name << " Site : nC/nH = " << 100*C/H << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
        cout << endl;


        if(Result_output) Result_Writer("/Users/chengyuchin/Analysis/note/nC_result.txt", 
                Site[SNo].Name, C, errorC, Gd, errorGd, H, errorH, !(bool)SNo, false, evaluating_method);


    }


    delete error_AoverB;
    delete error_AminusB;



}





bool GetMC(TString filename, Plots* AD){

    AD[1].MCnGd = new TH1D("MCnGd", "MCnGd", 1200, 0, 12);
    AD[1].MCnH = new TH1D("MCnH", "MCnH", 1200, 0, 12);
    AD[1].MCnC = new TH1D("MCnC", "MCnC", 1200, 0, 12);


    for(int ADNo = 2; ADNo<9; ADNo++){
        AD[ADNo].MCnGd = AD[1].MCnGd;
        AD[ADNo].MCnH = AD[1].MCnH;
        AD[ADNo].MCnC = AD[1].MCnC;
    }


    TFile* F = new TFile(filename);
    AD[1].MCnGd->Add((TH1D*)F->Get("nGd"));
    AD[1].MCnH->Add((TH1D*)F->Get("nH"));
    AD[1].MCnC->Add((TH1D*)F->Get("nC"));


    F->Close();
    delete F;


    return true;


}






bool GetRealData(TString filename, Plots* AD){ 

    for(int ADNo = 1; ADNo<9; ADNo++){
        AD[ADNo].Data = new TH1D(TString::Format("Data_AD%d",ADNo), TString::Format("Data_AD%d",ADNo), 1200, 0, 12);
    }


    TFile* F = new TFile(filename);
    for(int ADNo = 1; ADNo<9; ADNo++){
        AD[ADNo].Data->Add((TH1D*)F->Get(TString::Format("subD_AD%d",ADNo)));
    }


    F->Close();
    delete F;


    return true;


}



 


bool GetSitefromAD(Plots* AD, Plots* Site){

    for(int SNo = 0; SNo < 2; SNo++){
        Site[SNo].Data = new TH1D("Data_"+Site[SNo].Name,"Data_"+Site[SNo].Name,1200,0,12);
        Site[SNo].MCnH = new TH1D("MCnH_"+Site[SNo].Name,"MCnH_"+Site[SNo].Name,1200,0,12);
        Site[SNo].MCnGd = new TH1D("MCnGd_"+Site[SNo].Name,"MCnGd_"+Site[SNo].Name,1200,0,12);
    }


    for(int ADNo = 1; ADNo < 9; ADNo++){
        if(ADNo <= 4){
            Site[0].Data->Add(AD[ADNo].Data,1.0);
            Site[0].MCnH->Add(AD[ADNo].mdfMCnH,1.0);
            Site[0].MCnGd->Add(AD[ADNo].mdfMCnGd,1.0);
        }
        else{
            Site[1].Data->Add(AD[ADNo].Data,1.0);
            Site[1].MCnH->Add(AD[ADNo].mdfMCnH,1.0);
            Site[1].MCnGd->Add(AD[ADNo].mdfMCnGd,1.0);
        }

        //AD[ADNo].Data->Clear();
    }


    return true;


}


double GetnGdDiffandRatio(Plots& p){

    if(p.fMCGd->GetParameter(0) == 0){

        int MCNum = p.MCnGd->Integral(600 , 1000);
        p.fMCGd->SetParNames("N_{Gd}", "#mu_{Gd}", "#sigma_{Gd}", "#alpha_{Gd}", "n_{Gd}");
        p.fMCGd->SetParameters(MCNum, 8.089, 0.309, 1.7, 0.78);
        p.fMCGd->SetParLimits(0, 0,  500000000);   // N1


        cout << "----------------------Fitting MC nGd ---------------------" << endl;
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        CanvasNo++;
        gPad->SetLogy(1);
        p.MCnGd->Fit(p.fMCGd,"","",6,9.2);
        p.MCnGd->Fit(p.fMCGd,"","",6,9.2);

    }


    p.fDataGd = new TF1("fDataGd_"+p.Name, nGdFitter, 6, 9.2, 5);  
    int DataNum = p.Data->Integral(600 , 1000);


    p.fDataGd->SetParNames("N_{Gd}", "#mu_{Gd}", "#sigma_{Gd}", "#alpha_{Gd}", "n_{Gd}");
    p.fDataGd->SetParameters(DataNum, 8.089, 0.309, 1.7, 0.78);
    p.fDataGd->SetParLimits(0, 0,  5000000);   // N1
    p.fDataGd->SetParLimits(3, 0, 2);
    p.fDataGd->SetParLimits(4, 0, 1.2);


    cout << "----------------------Fitting nGd " << p.Name << "---------------------" << endl;
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    CanvasNo++;
    gPad->SetLogy(1);
    p.Data->Fit(p.fDataGd,"","",6,9.2);
    p.Data->Fit(p.fDataGd,"","",6,9.2);
    p.Data->DrawCopy();


    p.sGd = p.fDataGd->GetParameter(1) - p.fMCGd->GetParameter(1);
    p.rGd = p.fDataGd->GetParameter(0) / p.fMCGd->GetParameter(0);
    error_AminusB->SetParameters(p.fDataGd->GetParError(1), p.fMCGd->GetParError(1));
    error_AoverB->SetParameters(p.fDataGd->GetParameter(0), p.fMCGd->GetParameter(0),
                                p.fDataGd->GetParError(0), p.fMCGd->GetParError(0));


    cout << p.Name << " sGd = " << p.sGd << " +/- " << error_AminusB->Eval(0) << endl;
    cout << p.Name << " rGd = " << p.rGd << " +/- " << error_AoverB->Eval(0) << endl;
    

    return p.sGd;


}






double GetnHDiffandRatio(Plots& p){
        
    if(p.fMCH->GetParameter(0) == 0){

        int MCNum = p.MCnH->Integral(191 , 270);
        p.fMCH->SetParNames("N_{H}","#mu_{H}","#sigma_{H}","#alpha_{H}","n_{H}");
        p.fMCH->SetParameters(MCNum, 2.3, 0.16, 1.55867, 0);
        p.fMCH->SetParLimits(1, 2.15,  2.45);
        p.fMCH->SetParLimits(2, 0.1,  0.5);
        //p.fMCH->SetParLimits(3, 1.1,  1.6);
        p.fMCH->SetParLimits(4, 0,  20);


        cout << "----------------------Fitting MC nH ---------------------" << endl;
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        CanvasNo++;
        gPad->SetLogy(1);
        p.MCnH->Fit(p.fMCH,"","",MCnH_LowEdge,2.7);
        p.MCnH->Fit(p.fMCH,"","",MCnH_LowEdge,2.7);


        if(MCParameter_output) MCParameter_Writer("/Users/chengyuchin/Analysis/note/MCnH_Parameter.txt", p);
    }


    p.fDataH = new TF1("fDataH_"+p.Name, nHFitter, 1.9, 2.7, 5);  
    int DataNum = p.Data->Integral(191 , 270);


    p.fDataH->SetParNames("N_{H}","#mu_{H}","#sigma_{H}","#alpha_{H}","n_{H}");
    p.fDataH->SetParameters(DataNum, 2.3, 0.16, 1.55867, 0);
    p.fDataH->SetParLimits(1, 2.15,  2.45);
    p.fDataH->SetParLimits(2, 0.1,  0.5);
    p.fDataH->FixParameter(3, p.fMCH->GetParameter(3));
    p.fDataH->FixParameter(4, p.fMCH->GetParameter(4));
    //p.fDataH->SetParLimits(3, 1.1,  1.6);
    //p.fDataH->SetParLimits(4, 0,  20);


    cout << "----------------------Fitting nH " << p.Name << "---------------------" << endl;
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    CanvasNo++;
    gPad->SetLogy(1);
    p.Data->Fit(p.fDataH,"","",1.9,2.7);
    p.Data->Fit(p.fDataH,"","",1.9,2.7);
    p.Data->DrawCopy();


    p.sH = p.fDataH->GetParameter(1) - p.fMCH->GetParameter(1);
    p.rH = p.fDataH->GetParameter(0) / p.fMCH->GetParameter(0);
    error_AminusB->SetParameters(p.fDataH->GetParError(1), p.fMCH->GetParError(1));
    error_AoverB->SetParameters(p.fDataH->GetParameter(0), p.fMCH->GetParameter(0),
                                p.fDataH->GetParError(0), p.fMCH->GetParError(0));


    cout << p.Name << " sH = " << p.sH << " +/- " << error_AminusB->Eval(0) << endl;
    cout << p.Name << " rH = " << p.rH << " +/- " << error_AoverB->Eval(0) << endl;
    

    return p.sH;


}




bool MCParameter_Writer(TString txt_path, Plots Site){

    ofstream Fout(txt_path, ios::app);
    Fout << "MC nH Parameter : " << MCnH_LowEdge << " , " << Site.fMCH->GetParameter(1) << " , " << Site.fMCH->GetParameter(2) << " , ";
    Fout << Site.fMCH->GetParameter(3) << " , " << Site.fMCH->GetParameter(4) << endl;
    Fout.close();


    return true;



}




bool Result_Writer(TString txt_path, TString sitename, double C, double errorC, double Gd, double errorGd, double H, double errorH, bool addtitle, 
        bool Real, int method){

    ofstream Fout(txt_path, ios::app);


    if(addtitle){
        if(!have_written){
            Fout << "----------------------Direct Subtraction-------------------------" << endl;
            if(method == 1) Fout << "------------------(Evaluating by fitting parameter)--------------------" << endl;
            if(method == 2) Fout << "------------------(Evaluating by integrating number of events)--------------------" << endl;
        }
        else Fout << "----------------------Count by Fitting-------------------------" << endl;
        if(Real) Fout << "----------------------Real Data Counting------------------------- , LowEdge_C = " << nC_LowEdge << endl;
        else Fout << "----------------------MC Counting------------------------- , LowEdge_C = " << nC_LowEdge << endl;
    }


    Fout << sitename << " Site : nC Captured = " << C << " +/- " << errorC << endl;
    Fout << sitename << " Site : nGd Captured = " << Gd  << " +/- " << errorGd << endl;
    Fout << sitename << " Site : nH Captured = " << H  << " +/- " << errorH << endl;


    error_AoverB->SetParameters(C,Gd,errorC,errorGd);
    Fout << sitename << " Site : nC/nGd = " << 100*C/Gd << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
    error_AoverB->SetParameters(C,H,errorC,errorH);
    Fout << sitename << " Site : nC/nH = " << 100*C/H << " +/- " << 100*error_AoverB->Eval(0) << " %" << endl;
    Fout << endl;


    return true;



}





void TFile_Writer(TString filename, Plots* Site){

    TFile* F = new TFile(filename,"recreate");
    for(int SNo = 0; SNo<2; SNo++){

        Site[SNo].MCSum->Write();
        Site[SNo].Data->Write();
        Site[SNo].mdfMCnGd->Write();
        Site[SNo].mdfMCnH->Write();
        Site[SNo].mdfMCnC->Write();
        Site[SNo].nC->Write();
        Site[SNo].MCOverData->Write();
        Site[SNo].fDataGd->Write();
        Site[SNo].fDataH->Write();
        Site[SNo].fC->Write();
        if(Part2){
            Site[SNo].fData->Write();
            Site[SNo].fDataC->Write();
        }

    }


    for(int i = 0; i<CanvasNo; i++){
        c[i]->Write();
    }


}












