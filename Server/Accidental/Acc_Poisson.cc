#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include <boost/math/special_functions/lambert_w.hpp>


#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TString.h"
#include "TMath.h"
#include "/dybfs2/users/yuchincheng/workdir/IBD/code/Uncertainty.h"


using namespace std;
using boost::math::lambert_w0;
using TMath::PoissonI;


// user setting
const int correction = 2;   // 0 for not correction, 1 for Poisson+lambert_w0 correction (DocDB 12566 pg.92), 2 for Poisson correction
const bool symmetric_iso = true;   // true for nH similar isolation, false for nGd similar one
const double isolation_previous_window = 800;       // us
const double isolation_following_window = 400;      // us
const double symmetric_isolation = 800;             // us
const double DAQ_distinguish = 1;                   // us


void Acc_Poisson(){

    cout.precision(14);
    vector<vector<TH1D*>> hD;
    vector<vector<TH2D*>> hE;
    array<TString,3> name = {"can","acc","sub"};


    int AD;
    double FullTime, TimeGap, LiveTime;
    double sL, sR, sp, sd;
    const double&& tL = isolation_previous_window/1.e6;
    const double&& tR = isolation_following_window/1.e6;
    const double&& tI = symmetric_isolation/1.e6;
    const double&& tD = DAQ_distinguish/1.e6;
    cout << "tL = " << tL << endl;
    cout << "tR = " << tR << endl;
    cout << "tD = " << tD << endl;
    TFile* infile = new TFile("/dybfs2/users/yuchincheng/workdir/IBD/code/Accidental/P17B_IBD_presub_800iso.root");
    TTree* tree = dynamic_cast<TTree*>(infile->Get("info"));


    tree->SetBranchAddress("AD",&AD);
    tree->SetBranchAddress("FullTime",&FullTime);
    tree->SetBranchAddress("TimeGap",&TimeGap);
    tree->SetBranchAddress("LiveTime",&LiveTime);
    tree->SetBranchAddress("LeftSingles",&sL);
    tree->SetBranchAddress("RightSingles",&sR);
    tree->SetBranchAddress("PromptLikeSingles",&sp);
    tree->SetBranchAddress("DelayedLikeSingles",&sd);


    for(int i = 0; i<tree->GetEntries(); ++i){

        tree->GetEntry(i);

        vector<TH1D*> tempD;
        vector<TH2D*> tempE;
        for(auto s : name){
            tempD.push_back(new TH1D(TString::Format("dr_AD%d_",AD) + s, ";dr(mm);Counts", 500, 0, 5000));
            tempE.push_back(new TH2D(TString::Format("EpEd_AD%d_",AD) + s, ";E_{d}(MeV);E_{p}(MeV)", 1200, 0, 12, 120, 0, 12));
        }
        hD.push_back(tempD);
        hE.push_back(tempE);


        TH1D* hdcan = dynamic_cast<TH1D*>(infile->Get(TString::Format("h1dDpd_evt_AD%d",AD)));
        TH1D* hdacc = dynamic_cast<TH1D*>(infile->Get(TString::Format("h1dDpd_acc_AD%d",AD)));
        TH2D* hecan = dynamic_cast<TH2D*>(infile->Get(TString::Format("h2dEpd_evt_AD%d",AD)));
        TH2D* heacc = dynamic_cast<TH2D*>(infile->Get(TString::Format("h2dEpd_acc_AD%d",AD)));


        double gapeff = (FullTime-TimeGap)/FullTime;
        double vetoeff = LiveTime/FullTime;
        const Double_e s07e(sL,sqrt(sL));
        const Double_e s15e(sp,sqrt(sp));
        const Double_e s19e(sd,sqrt(sd));
        Double_e isoeff;
        //double isoeff2 = 1.;
        cout << sL << endl;


        // correction for isolation cut, extract the true rate of uncorr. signals from singles by Poisson statistics
        if(correction == 0) isoeff.SetValue(1);
        else if (correction == 1){
            if(symmetric_iso) isoeff.SetValue(exp(lambert_w0(-2.*(s07e.GetValue()*tI)/(LiveTime*gapeff))));
            else isoeff.SetValue(exp(lambert_w0(-1.*(s07e.GetValue()*tL+s15e.GetValue()*tR)/(LiveTime*gapeff))));
        }
        else if (correction == 2){
            //if(symmetric_iso) isoeff = exp(-2.*(sL*tI)/(LiveTime));
            if(symmetric_iso) isoeff = exp(-2.*(s07e*tI)/(LiveTime*gapeff));
            else isoeff = exp(-1.*(s07e*tL+s15e*tR)/(LiveTime*gapeff));
        }
        else{
            cerr << "Error! Correction method should be 0 or 1 or 2" << endl;
            return 0;
        }
        //isoeff2 = exp(-1.*(sL*tL+sR*tR)/(LiveTime*gapeff));
        //cout << "AD = " << AD << " , isolation_eff = " << isoeff << endl; 
        cout << "========================AD" << AD << "===========================" << endl;
        cout << "FullTime = " << (FullTime-TimeGap)/86400. << " , LiveTime = " << LiveTime*gapeff/86400. << " , veto eff = " << LiveTime/FullTime << endl; 
        cout << "N07 = "<< sL << " , N15 = " << sp << " , N19 = " << sd << " , isoeff = " << isoeff << endl;
        cout << "CorrN07 = " << sL/isoeff << " , CorrN15 = " << sp/isoeff << " , CorrN19 = " << sd/isoeff << endl;
        //cout << "Corr2N07 = " << sL/isoeff2 << " , Corr2N15 = " << sp/isoeff2 << " , Corr2N19 = " << sd/isoeff2 << endl;
        const Double_e R07e = s07e/(LiveTime*gapeff*isoeff);
        const Double_e R15e = s15e/(LiveTime*gapeff*isoeff);
        const Double_e R19e = s19e/(LiveTime*gapeff*isoeff);
        const Double_e N19e = s19e/isoeff;


        //const double RL = sL/(LiveTime*isoeff);
        //const double RR = sR/(LiveTime*isoeff);
        //const double Rp = sp/(LiveTime*isoeff);


        // calculate the number of accidentals
        const Double_e multiEffe = Poisson(0,tL*R07e)*Poisson(0,tR*R15e);
        cout << "multi eff = " << multiEffe << endl;
        const Double_e Pacc = Poisson(0,tR*R07e)*Poisson(0,(tR-tD)*(R07e-R15e))*Poisson(1,(tR-tD)*R15e)*Poisson(0,tD*R07e)*Poisson(0,tR*R15e);
        cout << "Pacc = " << Pacc << endl;
        const Double_e Nacc = N19e*Pacc;
        cout << "Nacc = " << Nacc << endl;
        const double Norm = Nacc.GetValue()/(1.*hdacc->GetEntries());



        tempD.at(0)->Add(hdcan, 1.);
        tempD.at(1)->Add(hdacc, Norm);
        tempD.at(2)->Add(hdcan, hdacc, 1., -1.*Norm);
        tempE.at(0)->Add(hecan, 1.);
        tempE.at(1)->Add(heacc, Norm);
        tempE.at(2)->Add(hecan, heacc, 1., -1.*Norm);


    }


    /*TFile* outfile = new TFile("/dybfs2/users/yuchincheng/workdir/IBD/code/Accidental/P17B_accsub_by_Poisson_800iso.root", "recreate");
    for(auto& v : hD){
        for(auto& i : v) i->Write();
    }


    for(auto& v : hE){
        for(auto& i : v){
            i->Write();
            TH1D* hEd = i->ProjectionX();
            hEd->Write();
        }
    }*/


    //outfile->Close();
    infile->Close();



}
    


