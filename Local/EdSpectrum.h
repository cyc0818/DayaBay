/* This code is created by Yu-Chin Cheng on Dec.27, 2021
 * c++11 or later version is required */


#ifndef EdSpectrum_h
#define EdSpectrum_h


#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "TFile.h"
#include "TString.h"
#include "TH1D.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "UserSetting.h"
#include "Fitter.h"
#include "TH1functions.h"


using namespace std;



class EdSpectrum{

    public:

        bool isMC;
        TString Name;

        TH1D* H = nullptr;
        TH1D* Gd = nullptr;
        TH1D* C = nullptr;
        TH1D* Data = nullptr;
        TH1D* Over = nullptr;

        TF1* fH = nullptr;
        TF1* fGd = nullptr;
        TF1* fsysL = nullptr;
        TF1* fsysR = nullptr;
        TF1* frw = nullptr;     // for nGd tail reweighting

        int nHFitStatus = -10;
        int nGdFitStatus = -10;
        int s = 0;
        double r = 1;
        array<double,2> TailPar = {0,0};
        array<double,2> TailParError = {0,0};

        EdSpectrum();
        EdSpectrum(TString inname);                                     // MC
        EdSpectrum(TString inname, int ADNo);                           // AD
        EdSpectrum(TString inname, TString Sptname, TString newname, int atomicNo);   // (iuput file name, input histogram name, name of this object)
        EdSpectrum(TString EHname, EdSpectrum* ptr, int MergeNum);      // EH or site
        ~EdSpectrum(){}

        bool Add(EdSpectrum S, double c);
        bool Rename(TString newname);
        bool Load(TString inname, TString Sptname, int atomicNo);

        int nHFit(double fixalpha, double fixn);
        int nGdFit();
        int DYBFit(vector<double> fix);

        bool Rescale(int atomicNo, double unit);    // atomicNo = 1 for nH, 64 for nGd
        bool Rescale(int atomicNo, EdSpectrum MC);
        bool Shift(int atomicNo, double unit);
        bool Shift(int atomicNo, EdSpectrum MC);
        bool GaussianConvolute(int atomicNo, double unit);
        bool GaussianConvolute(int atomicNo, EdSpectrum MC);

        bool MCnHCorrection(EdSpectrum MC);
        bool MCnGdCorrection(EdSpectrum MC);
        bool TakeRatio(bool NaturalLog);
        bool TailParameterization();
        TF1 GetReweightingFunction(float nsigma, TCanvas* illu1, TCanvas* illu2);
        bool nGdTailReweight(string option);
        bool nGdTailReweightbyDYB(EdSpectrum MC, string option);

        bool Extract_nC();

};






EdSpectrum::EdSpectrum(){

    isMC = false;

    Name = "temp";
    H = new TH1D("nH_temp","nH_temp;E_{d}(MeV);Counts",1200,0,12);
    Gd = new TH1D("nGd_temp","nGd_temp;E_{d}(MeV);Counts",1200,0,12);
    Data = new TH1D("Data_temp","Data_temp;E_{d}(MeV);Counts",1200,0,12);
    Over = new TH1D("Over_temp","Over_temp;E_{d}(MeV);Ratio",1200,0,12);



}






EdSpectrum::EdSpectrum(TString inname){

    isMC = true;


    Name = "MC";
    H = new TH1D("nH_MC","nH_MC;E_{d}(MeV);Counts",1200,0,12);
    Gd = new TH1D("nGd_MC","nGd_MC;E_{d}(MeV);Counts",1200,0,12);
    C = new TH1D("nC_MC","nC_MC;E_{d}(MeV);Counts",1200,0,12);


    unique_ptr<TFile> F(new TFile(inname));
    H->Add(dynamic_cast<TH1D*>(F->Get("Ed_H_passEpdrdt")) );
    C->Add(dynamic_cast<TH1D*>(F->Get("Ed_C_passEpdrdt")));
    if(Others) Gd->Add(dynamic_cast<TH1D*>(F->Get("nGdOthers")));
    else Gd->Add(dynamic_cast<TH1D*>(F->Get("Ed_Gd_passEpdrdt")));


    F->Close();



}






EdSpectrum::EdSpectrum(TString inname, int ADNo){

    isMC = false;
    int EH = ((ADNo-1)/2+1)*2/3 + 1; 
    int AD = ADNo - 2*(EH-1);


    Name = TString::Format("EH%dAD%d",EH,AD);
    Data = new TH1D("Data_"+Name, "Data_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);


    unique_ptr<TFile> F(new TFile(inname));
    Data->Add(dynamic_cast<TH1D*>(F->Get(TString::Format("subD_AD%d",ADNo))));


    F->Close();



}






EdSpectrum::EdSpectrum(TString inname, TString Sptname, TString newname, int atomicNo){

    TH1D* hptr = nullptr;
    isMC = false;
    Name = newname;

    if(atomicNo == 0){
        Data = new TH1D("Data_"+Name, "Data_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        hptr = Data;
    }

    if(atomicNo == 1){
        H = new TH1D("nH_"+Name, "nH_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        hptr = H;
    }

    if(atomicNo == 64){
        Gd = new TH1D("nGd_"+Name, "nGd_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        hptr = Gd;
    }


    unique_ptr<TFile> F(new TFile(inname));
    hptr->Add(dynamic_cast<TH1D*>(F->Get(Sptname)));


    F->Close();



}






EdSpectrum::EdSpectrum(TString EHname, EdSpectrum* ptr, int MergeNum = 1){

    isMC = false;
    bool HExist = true;
    bool GdExist = true;
    bool DataExist = true;
    bool CExist = true;


    Name = EHname;
    for(int i = 0; i<MergeNum; i++){
        HExist = HExist and ptr[i].H;
        GdExist = GdExist and ptr[i].Gd;
        DataExist = DataExist and ptr[i].Data;
        CExist = CExist and ptr[i].C;
    }


    if(HExist){
        H = new TH1D("CorrMCnH_"+Name, "CorrMCnH_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        for(int i = 0; i<MergeNum; i++){
            (this->H)->Add(ptr[i].H);
        }
        cout << "Corrected MC nH merged for " << Name << " complete!" << endl; 
    }


    if(GdExist){
        Gd = new TH1D("CorrMCnGd_"+Name, "CorrMCnGd_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        for(int i = 0; i<MergeNum; i++){
            (this->Gd)->Add(ptr[i].Gd);
        }
        cout << "Corrected MC nGd merged for " << Name << " complete!" << endl; 
    }


    if(DataExist){
        Data = new TH1D("Data_"+Name, "Data_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        for(int i = 0; i<MergeNum; i++){
            (this->Data)->Add(ptr[i].Data);
        }
        cout << "Data of ADs in " << Name << " merged complete!" << endl; 
    }


    if(CExist){
        C = new TH1D("nC_"+Name, "nC_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12);
        for(int i = 0; i<MergeNum; i++){
            (this->C)->Add(ptr[i].C);
        }
        cout << "nC spectrum of ADs in " << Name << " merged complete!" << endl; 
    }



}






bool EdSpectrum::Add(EdSpectrum S, double c = 1){

    if(this->H and S.H) (this->H)->Add(S.H, c);

    if(this->Gd and S.Gd) (this->Gd)->Add(S.Gd, c);

    if(this->C and S.C) (this->C)->Add(S.C, c);

    if(this->Data and S.Data) (this->Data)->Add(S.Data, c);


    return true;



}






bool EdSpectrum::Rename(TString newname){

    Name = newname;


    if(H) H->SetNameTitle("CorrMCnH_"+Name, "CorrMCnH_"+Name+";E_{d}(MeV);Counts");

    if(Gd) Gd->SetNameTitle("CorrMCnGd_"+Name, "CorrMCnGd_"+Name+";E_{d}(MeV);Counts");

    if(C) C->SetNameTitle("nC_"+Name, "nC_"+Name+";E_{d}(MeV);Counts");

    if(Data) Data->SetNameTitle("Data_"+Name, "Data_"+Name+";E_{d}(MeV);Counts");


    return true;



}






bool EdSpectrum::Load(TString inname, TString Sptname, int atomicNo){

    TH1D* hptr = nullptr;

    if(atomicNo == 0){
        hptr = Data;
    }

    if(atomicNo == 1){
        hptr = H;
    }

    if(atomicNo == 64){
        hptr = Gd;
    }


    unique_ptr<TFile> F(new TFile(inname));
    cout << "---add start---" << endl;
    hptr->Add(dynamic_cast<TH1D*>(F->Get(Sptname)));
    cout << "---add finish---" << endl;


    F->Close();


    return true;



}






int EdSpectrum::nHFit(double fixalpha = 0, double fixn = 0){

    TH1D* hptr = nullptr;


    if(isMC and H){
        hptr = H;
        //fH = new TF1("fH_"+Name, MCnHFitter, MCnH_LowEdge, 2.7, 5);
    }

    else if((not isMC) and Data){
        hptr = Data;
        //fH = new TF1("fH_"+Name, nHFitter, 1.9, 2.7, 5);  
    }

    else{
        cerr << "Error! The " << Name << " nH histogram to be fitted is a null pointer" << endl; 
        return nHFitStatus;
    }


    fH = new TF1("fH_"+Name, nHFitter2, 1.5, 2.7, 5);  
    fH->SetParNames("N_{H}","#mu_{H}","#sigma_{H}","#lambda_{H}","#alpha_{H}");
    fH->SetParameters(hptr->Integral(151,270)/100, 2.35,0.136,1.75,0.95);
    fH->SetParLimits(1, 2.15, 2.45);
    fH->SetParLimits(2, 0.1, 0.5);
    fH->SetParLimits(3, 0, 10);
    fH->SetParLimits(4, 0, 1);
    //fH->SetParLimits(4, 0, 20);
    /*if(fixalpha!=0 or fixn!=0){
        fH->FixParameter(3,fixalpha);
        fH->FixParameter(4,fixn);
    }*/


    cout << "----------------------Fitting " << Name << " nH ---------------------" << endl;
    hptr->Fit(fH,"R");
    nHFitStatus = hptr->Fit(fH,"R");


    return nHFitStatus;



}






int EdSpectrum::nGdFit(){

    TH1D* hptr = nullptr;


    if(isMC and Gd) hptr = Gd;

    else if((not isMC) and Data) hptr = Data;

    else{
        cerr << "Error! The " << Name << " nGd histogram to be fitted is a null pointer" << endl; 
        return nGdFitStatus;
    }


    fGd = new TF1("fGd"+Name, nGdFitter3, 3, 9.2, 10);  
    fGd->SetParNames("N_{Gd157}","#mu_{Gd157}","#sigma_{Gd157}","#lambda_{Gd157,1}","#lambda_{Gd157,2}",
                     "#alpha_{Gd157}","#beta_{Gd157}","N_{Gd155}","#mu_{Gd155}","#sigma_{Gd155}");
    fGd->SetParameters(hptr->Integral(301,920)*5/6/100, 7.94, 0.3, 0.5, 2.6, 0.8, 0.8,
                       hptr->Integral(301,920)/6/100, 8.54, 0.4);


    /*fGd = new TF1("fGd_"+Name, nGdFitter3, 6, 9.2, 10);  
    fGd->SetParNames("N_{Gd157}","#mu_{Gd157}","#sigma_{Gd157}","#lambda_{Gd157,1}","#lambda_{Gd157,2}",
                     "#alpha_{Gd157}","#beta_{Gd157}","N_{Gd155}","#mu_{Gd155}","#sigma_{Gd155}");
    fGd->SetParameters(hptr->Integral(601,920)*5/6/100, 7.94, 0.3, 0.5, 2.6, 0.8, 0.8,
                       hptr->Integral(601,920)/6/100, 8.54, 0.4);*/


    // Gd157
    fGd->SetParLimits(1, 7.85, 8.1);
    fGd->SetParLimits(2, 0.1, 0.6);
    fGd->SetParLimits(3, 0, 1.3);
    fGd->SetParLimits(4, 1.3, 8);
    fGd->SetParLimits(5, 0, 1);
    fGd->SetParLimits(6, 0, 1);


    // Gd155
    fGd->SetParLimits(8, 8.45, 8.8);
    fGd->SetParLimits(9, 0, 0.6);


    /*fGd->SetParNames("N_{Gd}", "#mu_{Gd}", "#sigma_{Gd}", "#alpha_{Gd}", "n_{Gd}");
    fGd->SetParameters(hptr->Integral(601,920), 8.089, 0.309, 1.7, 0.78);
    fGd->SetParLimits(0, 0, 5e6);
    fGd->SetParLimits(3, 0, 3);
    fGd->SetParLimits(4, 0, 2);*/


    cout << "----------------------Fitting " << Name << " nGd ---------------------" << endl;
    //hptr->Fit(fGd,"R");
    nGdFitStatus = hptr->Fit(fGd,"R");
    nGdFitStatus = hptr->Fit(fGd,"R");


    return nGdFitStatus;



}





int EdSpectrum::DYBFit(vector<double> fix = {0}){

    TH1D* hptr = nullptr;


    if(isMC and Gd) hptr = Gd;

    else if((not isMC) and Data) hptr = Data;

    else{
        cerr << "Error! The " << Name << " Ed histogram to be fitted is a null pointer" << endl; 
        return nGdFitStatus;
    }


    fGd = new TF1("fDYB"+Name, DYBFitter3, 1.5, 9.4, 18);  
    vector<TString> base = {"N_", "#mu_", "#sigma_", "#lambda_", "#alpha_"};
    vector<TString> index = {"{Gd157}", "{Gd155}", "{H}", "{C}"};
    vector<double> init = {Data->Integral(601,920)*5/6/100, 7.94, 0.3, 0.5, 2.6, 0.8, 0.8,
                           Data->Integral(601,920)/6/100, 8.54, 0.4,
                           Data->Integral(151,270)/100, 2.3, 0.15, 1.7, 0.75, 
                           215, 5.2, 0.5, 0.6904, 0.8}; 


    fGd->SetParNames("N_{Gd157}","#mu_{Gd157}","#sigma_{Gd157}","#lambda_{Gd157,1}","#lambda_{Gd157,2}",
                     "#alpha_{Gd157}","#beta_{Gd157}","N_{Gd155}","#mu_{Gd155}","#sigma_{Gd155}");
    for(int i = 0; i<20; i++){
        fGd->SetParameter(i, init.at(i));
        if(i>=10){
            fGd->SetParName(i,base.at(i%5)+index.at(i/5)); 
        }
    }
                           


    // Gd157
    fGd->SetParLimits(1, 7.85, 8.1);
    fGd->SetParLimits(2, 0.1, 0.6);
    fGd->SetParLimits(3, 0, 1.5);
    fGd->SetParLimits(4, 1.5, 8);
    fGd->SetParLimits(5, 0, 1);
    fGd->SetParLimits(6, 0, 1);


    // Gd155
    fGd->SetParLimits(8, 8.45, 8.8);
    fGd->SetParLimits(9, 0, 0.6);

    
    // H
    fGd->SetParLimits(11, 2.2, 2.4);
    fGd->SetParLimits(12, 0.1, 0.6);
    fGd->SetParLimits(13, 0, 10);
    fGd->SetParLimits(14, 0, 1);


    // C
    fGd->SetParLimits(16, 4.7, 5.5);
    fGd->SetParLimits(17, 0.1, 1.5);
    //fGd->SetParLimits(18, 0, 5);
    //fGd->SetParLimits(19, 0, 1);



    /*fGd->SetParNames("N_{Gd}", "#mu_{Gd}", "#sigma_{Gd}", "#alpha_{Gd}", "n_{Gd}");
    fGd->SetParameters(hptr->Integral(601,920), 8.089, 0.309, 1.7, 0.78);
    fGd->SetParLimits(0, 0, 5e6);
    fGd->SetParLimits(3, 0, 3);
    fGd->SetParLimits(4, 0, 2);*/


    cout << "----------------------Fitting " << Name << " Ed Spectrum ---------------------" << endl;
    //Data->Fit(fGd,"R");
    hptr->Fit(fGd,"R");
    int Status = hptr->Fit(fGd,"R");


    return Status;



}





bool EdSpectrum::Rescale(int atomicNo, double unit){

    if(atomicNo == 64 and Gd){

        Gd->Scale(unit);
        r = unit;
        cout << "The MC nGd for " << Name << " is rescaled " << unit << " times" << endl;

    }


    else if(atomicNo == 1 and H){

        H->Scale(unit);
        cout << "The MC nH for " << Name << " is rescaled " << unit << " times" << endl;

    }


    else if(atomicNo == 0 and Data){

        Data->Scale(unit);
        cout << "The " << Name << " Ed spectrum is rescaled " << unit << " times" << endl;

    }


    else if (atomicNo != 0 and atomicNo != 1 and atomicNo != 64){

        cerr << "Error! Atomic number should be 0 (for total spectrum) or 1 (for nH) or 64 (for nGd)" << endl;
        return false;

    }


    else{

        cerr << "Error! The spectrum in " << Name << " to be rescaled is a null pointer" << endl;
        return false;

    }


    return true;



}






bool EdSpectrum::Rescale(int atomicNo, EdSpectrum MC){

    if(atomicNo == 64 and MC.Gd){

        if(not(this->fGd and MC.fGd)){
            cerr << "Error! The " << Name << " nGd fitting should be done first!" << endl;
            return false;
        }


        if(not this->Gd){
            Gd = new TH1D("CorrMCnGd_"+Name, "CorrMCnGd_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12); 
            (this->Gd)->Add(MC.Gd);
        }


        (this->Gd)->Scale((this->fGd)->Integral(6,9.2) / (MC.fGd)->Integral(6,9.2));
        r = (this->fGd)->Integral(6,9.2) / (MC.fGd)->Integral(6,9.2);
        //(this->Gd)->Scale((this->fGd)->GetParameter(0) / (MC.fGd)->GetParameter(0));
        cout << "The MC nGd for " << Name << " is rescaled " << (this->fGd)->GetParameter(0) / (MC.fGd)->GetParameter(0) << " times" << endl;

    }


    else if(atomicNo == 1 and MC.H){

        if(not(this->fH and MC.fH)){
            cerr << "Error! The " << Name << " nH fitting should be done first!" << endl;
            return false;
        }


        if(not this->H){
            H = new TH1D("CorrMCnH_"+Name, "CorrMCnH_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12); 
            (this->H)->Add(MC.H);
        }


        (this->H)->Scale((this->fH)->Integral(1.9,2.7) / (MC.fH)->Integral(1.9,2.7));
        cout << "The MC nH for " << Name << " is rescaled " << (this->fH)->GetParameter(0) / (MC.fH)->GetParameter(0) << " times" << endl;

    }


    else if (atomicNo != 1 and atomicNo != 64){

        cerr << "Error! Atomic number should be either 1 (for nH) or 64 (for nGd)" << endl;
        return false;

    }


    else{

        cerr << "Error! The spectrum in " << Name << " to be rescaled is a null pointer" << endl;
        return false;

    }


    return true;



}






bool EdSpectrum::Shift(int atomicNo, double unit){

    if(atomicNo == 64 and Gd){

        const double w = Gd->GetXaxis()->GetBinWidth(1);
        *Gd = Translation(*Gd, (int)round(unit/w));
        s = (int)round(unit/w);
        cout << "The MC nGd for " << Name << " is shifted by " << round(unit/w)*w << " MeV" << endl;

    }


    else if(atomicNo == 1 and H){

        const double w = H->GetXaxis()->GetBinWidth(1);
        *H = Translation(*H, (int)round(unit/w));
        cout << "The MC nH for " << Name << " is shifted by " << round(unit/w)*w << " MeV" << endl;

    }


    else if(atomicNo == 0 and Data){

        const double w = Data->GetXaxis()->GetBinWidth(1);
        *Data = Translation(*Data, (int)round(unit/w));
        cout << "The " << Name << " Ed spectrum is shifted by " << round(unit/w)*w << " MeV" << endl;

    }


    else if (atomicNo != 0 and atomicNo != 1 and atomicNo != 64){

        cerr << "Error! Atomic number should be 0 (for total spectrum) or 1 (for nH) or 64 (for nGd)" << endl;
        return false;

    }


    else{

        cerr << "Error! The spectrum in " << Name << " to be shifted is a null pointer" << endl;
        return false;

    }


    return true;



}






bool EdSpectrum::Shift(int atomicNo, EdSpectrum MC){

    if(atomicNo == 64 and MC.Gd){

        if(not(this->fGd and MC.fGd)){
            cerr << "Error! The " << Name << " nGd fitting should be done first!" << endl;
            return false;
        }


        if(not this->Gd){
            Gd = new TH1D("CorrMCnGd_"+Name, "CorrMCnGd_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12); 
            (this->Gd)->Add(MC.Gd);
        }


        const double w = MC.Gd->GetXaxis()->GetBinWidth(1);
        const double t = (this->fGd)->GetParameter(1) - (MC.fGd)->GetParameter(1); 
        *(this->Gd) = Translation(*(this->Gd), (int)round(t/w));
        s = (int)round(t/w);
        cout << "The MC nGd for " << Name << " is shifted by " << round(t/w)*w << " MeV" << endl;

    }


    else if(atomicNo == 1 and MC.H){

        if(not(this->fH and MC.fH)){
            cerr << "Error! The " << Name << " nH fitting should be done first!" << endl;
            return false;
        }


        if(not this->H){
            H = new TH1D("CorrMCnH_"+Name, "CorrMCnH_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12); 
            (this->H)->Add(MC.H);
        }


        const double w = MC.H->GetXaxis()->GetBinWidth(1);
        const double t = (this->fH)->GetParameter(1) - (MC.fH)->GetParameter(1); 
        *(this->H) = Translation(*(this->H), (int)round(t/w));
        cout << "The MC nH for " << Name << " is shifted by " << round(t/w)*w << " MeV" << endl;

    }


    else if (atomicNo != 1 and atomicNo != 64){

        cerr << "Error! Atomic number should be either 1 (for nH) or 64 (for nGd)" << endl;
        return false;

    }


    else{

        cerr << "Error! The spectrum in " << Name << " to be shifted is a null pointer" << endl;
        return false;

    }


    return true;



}






bool EdSpectrum::GaussianConvolute(int atomicNo, double unit){

    if(atomicNo == 64 and Gd){

        GaussianBinSmear(Gd, unit);
        cout << "The MC nGd for " << Name << " is convoluted with a Gaussian with sigma = " << unit << endl;

    }


    else if(atomicNo == 1 and H){

        GaussianBinSmear(H, unit);
        cout << "The MC nH for " << Name << " is convoluted with a Gaussian with sigma = " << unit << endl;

    }


    else if(atomicNo == 0 and Data){

        GaussianBinSmear(Data, unit);
        cout << "The " << Name << " Ed spectrum is convoluted with a Gaussian with sigma = " << unit << endl;

    }


    else if (atomicNo != 0 and atomicNo != 1 and atomicNo != 64){

        cerr << "Error! Atomic number should be 0 (for total spectrum) or 1 (for nH) or 64 (for nGd)" << endl;
        return false;

    }


    else{

        cerr << "Error! The spectrum in " << Name << " to be convoluted is a null pointer" << endl;
        return false;

    }


    return true;



}






bool EdSpectrum::GaussianConvolute(int atomicNo, EdSpectrum MC){

    if(atomicNo == 64 and MC.Gd){

        if(not(this->fGd and MC.fGd)){
            cerr << "Error! The " << Name << " nGd fitting should be done first!" << endl;
            return false;
        }


        if(not this->Gd){
            Gd = new TH1D("CorrMCnGd_"+Name, "CorrMCnGd_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12); 
            (this->Gd)->Add(MC.Gd);
        }


        const double sd = 1.0*sqrt(pow((this->fGd)->GetParameter(2), 2) - pow((MC.fGd)->GetParameter(2), 2)); 
        GaussianBinSmear(Gd, sd);
        cout << "The MC nGd for " << Name << " is convoluted with a Gaussian with sigma = " << sd << endl;

    }


    else if(atomicNo == 1 and MC.H){

        if(not(this->fH and MC.fH)){
            cerr << "Error! The " << Name << " nH fitting should be done first!" << endl;
            return false;
        }


        if(not this->H){
            H = new TH1D("CorrMCnH_"+Name, "CorrMCnH_"+Name+";E_{d}(MeV);Counts", 1200, 0, 12); 
            (this->H)->Add(MC.H);
        }


        const double sd = 1.0*sqrt(pow((this->fH)->GetParameter(2), 2) - pow((MC.fH)->GetParameter(2), 2)); 
        GaussianBinSmear(H, sd);
        cout << "The MC nH for " << Name << " is convoluted with a Gaussian with sigma = " << sd << endl;

    }


    else if (atomicNo != 1 and atomicNo != 64){

        cerr << "Error! Atomic number should be either 1 (for nH) or 64 (for nGd)" << endl;
        return false;

    }


    else{

        cerr << "Error! The spectrum in " << Name << " to be convoluted is a null pointer" << endl;
        return false;

    }


    return true;



}






bool EdSpectrum::MCnHCorrection(EdSpectrum MC){

    bool check = true;


    if(Smear){

        if(this->GaussianConvolute(1, MC)){

            double mudata = this->fH->GetParameter(1);
            double Ndata = this->fH->GetParameter(0);
            this->isMC = true;
            this->nHFit();


            check = check and this->Shift(1, mudata - (this->fH->GetParameter(1)));
            check = check and this->Rescale(1, Ndata / (this->fH->GetParameter(0)));
            this->isMC = false;

        }

        else return false;

    }


    else{

        check = check and this->Shift(1, MC);
        check = check and this->Rescale(1, MC);

    }


    return check;



}






bool EdSpectrum::MCnGdCorrection(EdSpectrum MC){

    bool check = true;


    if(Smear){

        if(this->GaussianConvolute(64, MC)){

            double mudata = this->fGd->GetParameter(1);
            double Ndata = this->fGd->GetParameter(0);
            this->isMC = true;
            this->nGdFit();


            check = check and this->Shift(64, mudata - (this->fGd->GetParameter(1)));
            check = check and this->Rescale(64, Ndata / (this->fGd->GetParameter(0)));
            this->isMC = false;

        }

        else return false;

    }


    else{

        check = check and this->Shift(64, MC);
        check = check and this->Rescale(64, MC);

    }


    return check;



}






bool EdSpectrum::TakeRatio(bool NaturalLog = false){

    if(not(Data and Gd and H)){

        cerr << "Error! Prepare Data, MCnGd, MCnH to take ratio (" << Name << ")" << endl;
        return false;

    }


    Over = new TH1D("Ratio_"+Name, "Ratio_"+Name+";E_{d}(MeV);Data/MC", 1200, 0, 12);
    unique_ptr<TH1D> hptr(new TH1D("htemp","htemp;E_{d}(MeV)",1200,0,12));


    Over->Add(Data);
    hptr->Add(Gd,H,1,1);
    if(NaturalLog){
        for(int i = 1; i<Over->GetNbinsX()+1; i++){
            if(Over->GetBinContent(i) > 0){
                double err1 = Over->GetBinError(i) / Over->GetBinContent(i);
                double err2 = hptr->GetBinError(i) / hptr->GetBinContent(i);
                Over->SetBinContent(i,log(Over->GetBinContent(i)));
                Over->SetBinError(i,err1);
                hptr->SetBinContent(i,log(hptr->GetBinContent(i)));
                hptr->SetBinError(i,err2);
            }
        }
    }
    Over->Divide(hptr.get());


    return true;



}






bool EdSpectrum::TailParameterization(){

    TH1D* hptr = nullptr;
    bool check;


    if(isMC and Gd){
        hptr = Gd;
        check = false;
    }

    else if((not isMC) and Data){
        hptr = Data;
        check = true;
    }

    else{
        cerr << "Error! The " << Name << " nGd histogram to be parameterized is a null pointer" << endl; 
        return false;
    }


    unique_ptr<TGraphErrors> g_Tail(new TGraphErrors());
    unique_ptr<TF1> f_Tail(new TF1("fTail","pol1",0,8));


    const double w = hptr->GetXaxis()->GetBinWidth(1);
    int a = 0;
    for(int j = 0; j<(4.-3.)/w; j++){
        double x = 3+j*w;
        if(check and not(hptr->GetBinContent(hptr->FindBin(x+0.1*w)) > 0)) continue;
        g_Tail->SetPoint(a, hptr->GetBinCenter(hptr->FindBin(x+0.1*w)), 
                         log(hptr->GetBinContent(hptr->FindBin(x+0.1*w))));
        g_Tail->SetPointError(a, 0,
                              hptr->GetBinError(hptr->FindBin(x+0.1*w))/hptr->GetBinContent(hptr->FindBin(x+0.1*w)));
        a++;
    }


    for(int j = 0; j<(7.-6.)/w; j++){
        double x = 6+j*w;
        if(check and not(hptr->GetBinContent(hptr->FindBin(x+0.1*w)) > 0)) continue;
        g_Tail->SetPoint(a, hptr->GetBinCenter(hptr->FindBin(x+0.1*w)), 
                         log(hptr->GetBinContent(hptr->FindBin(x+0.1*w))));
        g_Tail->SetPointError(a, 0,
                              hptr->GetBinError(hptr->FindBin(x+0.1*w))/hptr->GetBinContent(hptr->FindBin(x+0.1*w)));
        a++;
    }


    g_Tail->Fit(f_Tail.get());
    for(int i = 0; i<2; i++){
        TailPar[i] = f_Tail->GetParameter(i);
        TailParError[i] = f_Tail->GetParError(i);
    }


    return true;



}






TF1 EdSpectrum::GetReweightingFunction(float nsigma = 0, TCanvas* illu1 = nullptr, TCanvas* illu2 = nullptr){

    if(not(Data and Gd)){

        cerr << "Error! Prepare Data, MCnGd to reweight (" << Name << ")" << endl;
        return TF1();

    }


    unique_ptr<TGraphErrors> gd(new TGraphErrors());
    unique_ptr<TGraphErrors> gmc(new TGraphErrors());


    unique_ptr<TF1> fd(new TF1("fd","pol1",0,8));
    unique_ptr<TF1> fmc(new TF1("fmc","pol1",0,8));
    frw = new TF1("frw_"+Name,"expo",0,8);


    const double w = Data->GetXaxis()->GetBinWidth(1);
    int a = 0;
    for(int j = 0; j<(nC_LowEdge-3.)/w; j++){
        double x = 3+j*w;
        if(Data->GetBinContent(Data->FindBin(x+0.1*w)) > 0){
            gd->SetPoint(a, Data->GetBinCenter(Data->FindBin(x+0.1*w)), 
                         log(Data->GetBinContent(Data->FindBin(x+0.1*w))));
            gd->SetPointError(a, 0,
                              Data->GetBinError(Data->FindBin(x+0.1*w))/Data->GetBinContent(Data->FindBin(x+0.1*w)));
            a++;
        }

        gmc->SetPoint(j, Gd->GetBinCenter(Gd->FindBin(x+0.1*w)), 
                      log(Gd->GetBinContent(Gd->FindBin(x+0.1*w))));
        gmc->SetPointError(j, 0,
                           Gd->GetBinError(Gd->FindBin(x+0.1*w))/Gd->GetBinContent(Gd->FindBin(x+0.1*w)));
    }


    for(int j = 0; j<(7.-6.)/w; j++){
        double x = 6+j*w;
        if(Data->GetBinContent(Data->FindBin(x+0.1*w)) > 0){
            gd->SetPoint(a, Data->GetBinCenter(Data->FindBin(x+0.1*w)), 
                         log(Data->GetBinContent(Data->FindBin(x+0.1*w))));
            gd->SetPointError(a, 0,
                              Data->GetBinError(Data->FindBin(x+0.1*w))/Data->GetBinContent(Data->FindBin(x+0.1*w)));
            a++;
        }

        gmc->SetPoint(j+100, Gd->GetBinCenter(Gd->FindBin(x+0.1*w)), 
                      log(Gd->GetBinContent(Gd->FindBin(x+0.1*w))));
        gmc->SetPointError(j+100, 0,
                           Gd->GetBinError(Gd->FindBin(x+0.1*w))/Gd->GetBinContent(Gd->FindBin(x+0.1*w)));
    }


    gd->SetMarkerStyle(8);
    gd->Fit(fd.get(),"","",3,7);
    gmc->SetMarkerStyle(8);
    gmc->Fit(fmc.get(),"","",3,7);
    if(illu1 and illu2){
        illu1->cd();
        gd->Draw("ap");
        gd.release();

        illu2->cd();
        gmc->Draw("ap");
        gmc.release();
    }


    frw->SetParameter(0, fd->GetParameter(0) - fmc->GetParameter(0) + nsigma*fd->GetParError(0));
    frw->SetParameter(1, fd->GetParameter(1) - fmc->GetParameter(1) + nsigma*fd->GetParError(1));


    return *frw;



}





bool EdSpectrum::nGdTailReweight(string option = ""){

    if(not frw){

        cerr << "Error! Get the function for reweighting first (" << Name << ")" << endl;
        return false;

    }


    const double w = Data->GetXaxis()->GetBinWidth(1);
    double dx = 0.5*w; 
    if(option == "L") dx = 0;
    if(option == "R") dx = w;


    //for(int j = 0; j<(7.-3.)/w; j++){
        //double x = 3+j*w;
    for(int j = 0; j<(7.-1.5)/w; j++){
        double x = 1.5+j*w;
        Gd->SetBinContent(Gd->FindBin(x+0.1*w),
                          frw->Eval(x+dx) * Gd->GetBinContent(Gd->FindBin(x+0.1*w)));
        Gd->SetBinError(Gd->FindBin(x+0.1*w),
                        frw->Eval(x+dx) * Gd->GetBinError(Gd->FindBin(x+0.1*w)));
    }


    return true;



}





bool EdSpectrum::nGdTailReweightbyDYB(EdSpectrum MC, string option = ""){

    if(not (fGd and MC.fGd)){

        cerr << "Error! Get the function for reweighting first (" << Name << ")" << endl;
        return false;

    }


    const double w = Data->GetXaxis()->GetBinWidth(1);
    double dx = 0.5*w; 
    if(option == "L") dx = 0;
    if(option == "R") dx = w;
    unique_ptr<TF1> tail(new TF1("tail_temp",nGdFitter3,1.5,12,10));
    for(int i = 0; i<10; i++) tail->SetParameter(i,fGd->GetParameter(i));


    //for(int j = 0; j<(7.-3.)/w; j++){
        //double x = 3+j*w;
    for(int j = 0; j<(7.-1.5)/w; j++){
        double x = 1.5+j*w;
        double rw = tail->Eval(x+dx)/MC.fGd->Eval(x+dx-w*s)/r; 
        Gd->SetBinContent(Gd->FindBin(x+0.1*w),
                          rw * Gd->GetBinContent(Gd->FindBin(x+0.1*w)));
        Gd->SetBinError(Gd->FindBin(x+0.1*w),
                        rw * Gd->GetBinError(Gd->FindBin(x+0.1*w)));
    }


    return true;



}






bool EdSpectrum::Extract_nC(){

    if(not Data){

        cerr << "Error! The Ed spectrum in " << Name << " to be extracted from is a null pointer!" << endl;
        return false;

    }


    if(not Gd){

        cerr << "Error! The pure nGd spectrum in " << Name << " is a null pointer!" << endl;
        return false;

    }


    C = new TH1D("nC_"+Name,"nC_"+Name+";E_{d}(MeV);Counts",1200,0,12);
    C->Add(Data,Gd,1,-1);
    if(H) C->Add(H,-1);


    return true;



}




#endif



