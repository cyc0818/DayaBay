#ifndef TH1functions_h
#define TH1functions_h


#include <vector>
#include <math.h>
#include "TString.h"
#include "TH1D.h"
#include "TF1.h"

using namespace std;



TH1D Translation(TH1D h, int n){   // n : the translation to be performed (unit : translation length / binsize)

    vector<double> v;
    

    if(n == 0) return h;

    else if (n < 0){
        
        for(int i = -n; i < h.GetNbinsX()+1-n; i++){

            if(i < h.GetNbinsX()+1){
                v.push_back(h.GetBinContent(i));
            }
            else{
                v.push_back(0);
            }
        }

    }

    else if (n > 0){

        for(int i = 0; i < n+1; i++){
            v.push_back(0);
        }

        for(int i = 1; i < h.GetNbinsX()+1-n; i++){
            v.push_back(h.GetBinContent(i));
        }

    }


    h.SetContent(&v[0]);
    

    return h;


}




TH1D GetFitPerformance(TH1D* h, TF1* f, TString OutputName){

    int Nbins = h->GetNbinsX();
    double low_edge = h->GetXaxis()->GetXmin();
    double high_edge = h->GetXaxis()->GetXmax();


    TH1D perf(OutputName, OutputName, Nbins, low_edge, high_edge);
    double q = 0;   // (yi - f(xi))^2 / err_yi^2


    for(int i = 1; i<Nbins+1; i++){
        q = pow((h->GetBinContent(i) - f->Eval(h->GetBinCenter(i))) / h->GetBinError(i), 2);
        if(isnormal(q) and h->GetBinContent(i) != 0) perf.SetBinContent(i,q);
    }
    cout << OutputName << " : Chi Square = " << perf.Integral(1,Nbins) << std::endl;


    return perf;




}




TH1D GetRatioHistogram(TH1D* h, TF1* f, TString OutputName){
    int Nbins = h->GetNbinsX();
    double low_edge = h->GetXaxis()->GetXmin();
    double high_edge = h->GetXaxis()->GetXmax();


    TH1D perf(OutputName, OutputName, Nbins, low_edge, high_edge);
    double q = 0;   // (f(xi) - yi) / yi


    for(int i = 1; i<Nbins+1; i++){
        q = (f->Eval(h->GetBinCenter(i)) - h->GetBinContent(i)) / h->GetBinContent(i);
        if(isnormal(q) and h->GetBinContent(i) != 0) perf.SetBinContent(i,q);
    }



    return perf;


}






void GaussianBinSmear(TH1D* h, double sd){

    const double w = h->GetXaxis()->GetBinWidth(1);
    const int n = 4*sd/w + 1;
    vector<double> fraction;    // Gaussian smearing factor for each bin
    vector<double> bincont;     // original bin content
    vector<TH1D> v;             // each histogram is a bin in original one after smearing


    TF1 fsmear("fsmear","TMath::Gaus(x,0,[0],1)",-5*sd,5*sd);
    fsmear.SetParameter(0,sd);
    for(int i = 0; i<n+1; i++){
        fraction.push_back(fsmear.Integral((i-0.5)*w,(i+0.5)*w));
    }


    bincont.push_back(0);
    v.push_back(TH1D());
    for(int bin = 1; bin < h->GetNbinsX()+1; bin++){
        bincont.push_back(h->GetBinContent(bin));
        v.push_back(TH1D(TString::Format("h%d",bin), TString::Format("h%d",bin), h->GetNbinsX(), h->GetXaxis()->GetXmin(), h->GetXaxis()->GetXmax()));
    }


    h->Reset();
    for(int bin = 1; bin < h->GetNbinsX()+1; bin++){
        for(int i = 0; i<n+1; i++){
            if(bin+i <= h->GetNbinsX()) v[bin].AddBinContent(bin+i, bincont[bin]*fraction[i]);
            if((i!=0) && (bin-i >= 1)) v[bin].AddBinContent(bin-i, bincont[bin]*fraction[i]);
        }

        h->Add(&v[bin],1);
    }



}




#endif

