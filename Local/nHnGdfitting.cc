#include "EdSpectrum.h"
#include "/Users/chengyuchin/Analysis/nC/EndGame/Uncertainty.h"


using namespace std;
void nHnGdfitting(){
//int main(){

    unique_ptr<TStopwatch> timer(new TStopwatch());
    timer->Start();
    gStyle->SetOptFit(1);
    TString MCpath = "/Users/chengyuchin/Analysis/data/MC/Efficiency.root";
    TString datapath = "/Users/chengyuchin/Analysis/P17B_accsub_by_dis.root";
    TCanvas* c[50];
    int CanvasNo = 0;


    vector<EdSpectrum> AD;
    AD.push_back(EdSpectrum(MCpath));
    for(int i = 1; i<9;i++){
        AD.push_back(EdSpectrum(datapath,i));
    }


    AD[0].nHFit();
    AD[0].nGdFit();
    const double w = AD[1].Data->GetXaxis()->GetBinWidth(1);
    TF1* Gdbase = new TF1("Gdbase","[0]",0,10);
    Gdbase->SetParameter(0,AD[0].fGd->GetParameter(1));
    TF1* Hbase = new TF1("Hbase","[0]",0,10);
    Hbase->SetParameter(0,AD[0].fH->GetParameter(1));


    TGraphErrors* gH = new TGraphErrors();
    gH->SetTitle("nH peak position;AD;#mu_{H}(MeV)");
    gH->SetMarkerStyle(8);
    TGraphErrors* gGd = new TGraphErrors();
    gGd->SetTitle("nGd peak position;AD;#mu_{Gd}(MeV)");
    gGd->SetMarkerStyle(8);


    double sum_wx_H = 0;
    double sum_wx_Gd = 0;
    double sum_w_H = 0;
    double sum_w_Gd = 0;


    for(int i = 1; i<9;i++){

        AD[i].nHFit(AD[0].fH->GetParameter(3),AD[0].fH->GetParameter(4));
        AD[i].nGdFit();


        gH->SetPoint(i-1, i, AD[i].fH->GetParameter(1));
        gH->SetPointError(i-1, 0, AD[i].fH->GetParError(1));
        gGd->SetPoint(i-1, i, AD[i].fGd->GetParameter(1));
        gGd->SetPointError(i-1, 0, AD[i].fGd->GetParError(1));


        double w_H = 1/(AD[i].fH->GetParError(1)*AD[i].fH->GetParError(1));
        double w_Gd = 1/(AD[i].fGd->GetParError(1)*AD[i].fGd->GetParError(1));


        sum_w_H += w_H;
        sum_w_Gd += w_Gd;
        sum_wx_H += w_H * AD[i].fH->GetParameter(1);
        sum_wx_Gd += w_Gd * AD[i].fGd->GetParameter(1);

        
    }


    Double_e avg_H(sum_wx_H/sum_w_H, sqrt(1/sum_w_H));
    Double_e avg_Gd(sum_wx_Gd/sum_w_Gd, sqrt(1/sum_w_Gd));




    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    gGd->Draw("ap");
    Gdbase->Draw("same");
    CanvasNo++;



    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    gH->Draw("ap");
    Hbase->Draw("same");
    CanvasNo++;


    cout << "avg H = " << avg_H << endl;
    cout << "avg Gd = " << avg_Gd << endl;

    
    timer->Stop();
    timer->Print();



}

