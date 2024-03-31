#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
//#include <boost/math/special_functions/lambert_w.hpp>


#include "TStyle.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TString.h"
#include "TMath.h"


using namespace std;


bool Postsub;
bool SavePlots;
string dataPeriod;
int BeginJob();
int EndJob();

TMultiGraph *mg1 = new TMultiGraph("mg1","muRate");
TMultiGraph *mg2 = new TMultiGraph("mg2","sgRate");
TMultiGraph *mg3 = new TMultiGraph("mg3","vetoEff");
TMultiGraph *mg4 = new TMultiGraph("mg4","multEff");
TMultiGraph *mg5 = new TMultiGraph("mg5","accRate");
TMultiGraph *mg6 = new TMultiGraph("mg6","ibdRate");
TMultiGraph *mg7 = new TMultiGraph("mg7","ibdRate2");
TTree* info = new TTree("info","information of live time and singles");

map< int /* Run */, TGraphErrors* >  Nmu_rate;
map< int /* Run */, TGraphErrors* >  Nsg_rate;
map< int /* Run */, TGraphErrors* >  Nacc_rate;
map< int /* Run */, TGraphErrors* >  Nibd_rate;
map< int /* Run */, TGraphErrors* >  veto_eff;
map< int /* Run */, TGraphErrors* >  multi_eff;
map< int /* Run */, TGraphErrors* >  ibdRate2;

map< int /* Run */, TH1D* >  h_dist_evt;
map< int /* Run */, TH1D* >  h_dist_acc;
map< int /* Run */, TH1D* >  h_dist_sub;

map< int /* Run */, TH2D* >  hEpd_evt;
map< int /* Run */, TH2D* >  hEpd_acc;
map< int /* Run */, TH2D* >  hEpd_sub;

map< int /* Run */, TH1D* >  phX;
map< int /* Run */, TH1D* >  phY;
map< int /* Run */, TH1D* >  evtP_phX;
map< int /* Run */, TH1D* >  evtP_phY;
map< int /* Run */, TH1D* >  evtA_phX;
map< int /* Run */, TH1D* >  evtA_phY;

map< int /* Run */, TH1D* >  evtP;
map< int /* Run */, TH1D* >  accP;
map< int /* Run */, TH1D* >  subP;

map< int /* Run */, TH1D* >  evtD;
map< int /* Run */, TH1D* >  accD;
map< int /* Run */, TH1D* >  subD;

map< int /* Run */, TH1D* >  tEs;

double nHAcc(double sRate, double mRate, double Tc){
    double fracTerm1 = (1.0*mRate)/(sRate+mRate);
    double fracTerm2 = (1.0*sRate)/(sRate+mRate);
    double fracTerm3 = (1.0*sRate)/(2*sRate+mRate);
    double ExpTerm1 = exp( -(sRate+mRate)*Tc);
    double ExpTerm2 = exp( -(2*sRate+mRate)*Tc);
    
    double term1 = fracTerm1*(1-ExpTerm1)+ExpTerm1;
    double term2 = fracTerm2*exp( - mRate*Tc )*(1-ExpTerm1);
    double term3 = fracTerm3*exp( - mRate*Tc )*(1-ExpTerm2);
    
    return sRate*(term1+term2+term3)*sRate*Tc*exp(-sRate*Tc);
    
}

double nHmEff(double sRate, double mRate, double Tc){
    double fracTerm1 = (1.0*mRate)/(sRate+mRate);
    double fracTerm2 = (1.0*sRate)/(sRate+mRate);
    double fracTerm3 = (1.0*sRate)/(2*sRate+mRate);
    double ExpTerm1 = exp( -(sRate+mRate)*Tc);
    double ExpTerm2 = exp( -(2*sRate+mRate)*Tc);
    
    double term1 = fracTerm1*(1-ExpTerm1)+ExpTerm1;
    double term2 = fracTerm2*exp( - mRate*Tc )*(1-ExpTerm1);
    double term3 = fracTerm3*exp( - mRate*Tc )*(1-ExpTerm2);
    
    return (term1+term2+term3)*exp(-sRate*Tc);
    
}

double binErr (double evtN, double accN, double accErr, double scaleN, double scaleErr, double factor) {
    double totalErr2 = evtN + (factor*accN)*(factor*accN)*scaleErr*scaleErr + (factor*scaleN)*(factor*scaleN)*accErr*accErr;

    return sqrt(totalErr2);
}

void unifiedPlots()
{

    double capTime = 0.0004;
    double tB4Ed = 2.0*capTime;
    double tAfEd = 1.0*capTime;
    /////
    #define SIZE 1000
    char line [SIZE];
    char* a="\t";
    //const char a[4]="\t";
    char* b;
    string sub_yorn;
    string save_yorn;


    cout << "Which data do you want to analyze? (P17B/P19A/P20A/P21A) " << std::endl;
    cout << ">> ";
    cin >> dataPeriod;
    if (dataPeriod != "P17B" && dataPeriod != "P19A" && dataPeriod != "P20A" && dataPeriod != "P21A"){
        cout << "Error!" << std::endl;
        return;
    }


    cout << "Is the data subtracted by accidental? (y/n)" << std::endl;
    cout << ">> ";
    cin >> sub_yorn;
    if (sub_yorn == "y") Postsub = true;
    else if (sub_yorn == "n") Postsub = false;
    else{
        cout << "Error!" << std::endl;
        return;
    }


    cout << "Do you want to save plots? (y/n)" << std::endl;
    cout << ">> ";
    cin >> save_yorn;
    if (save_yorn == "y") SavePlots = true;
    else if (save_yorn == "n") SavePlots = false;
    else{
        cout << "Error!" << std::endl;
        return;
    }


    
    cout << "Processing " << dataPeriod;
    if(Postsub) cout << " postsub ";
    else cout << " presub ";
    cout << "data ..." << std::endl;
    


    vector<string> file1;
    file1.resize(3);
    
    file1 = {
        "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/EH1/Merge2/P17B_EH1_800iso.root",
        "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/EH2/Merge2/P17B_EH2_800iso.root",
        "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/EH3/Merge2/P17B_EH3_800iso.root"
    };
    cout << "Found root file!" << endl;


    
    TH1D* hSig;
    TH1D* hEvtDist;
    TH1D* hAccDist;
    TH1D* h1EvtEp;
    TH1D* h1AccEp;
    TH2D* h2dIBD;
    TH2D* h2dACC;
    cout.precision(14);
    
    double TotalFullT[10] = {0};
    double TotalGapT[10] = {0};
    double TotalLiveT[10] = {0};
    double TotalMuon[10] = {0};
    double TotalSigles[10] = {0};
    double TotalPlike[10] = {0};
    double TotalDlike[10] = {0};
    double TotalLlike[10] = {0};
    double TotalRlike[10] = {0};
    
    long int SumAccNum[10] = {0};
    
    BeginJob();
    vector<double> tuneFactor2;
    tuneFactor2.resize(10);
   
    if (dataPeriod == "P17B") tuneFactor2 = {0, 1, 1, 1, 1, 1, 1, 1, 1,0}; //1
    //if (dataPeriod == "P17B") tuneFactor2 = {0, 0, 0, 0, 0, 0, 0, 0, 0,0}; //0
    //if (dataPeriod == "P17B") tuneFactor2 = {0, 0.525999, 0.5284606, 0.536395, 0.533212, 0.54183, 0.547246, 0.5485411, 0.547438,0}; //P17B
    //if (dataPeriod == "P17B") tuneFactor2 = {0, 0.9706645, 0.97279267, 0.9877343, 0.98596033, 1.0129578, 1.01612774, 1.01594523, 1.01386021,0}; //P17B 4mcut
    //if (dataPeriod == "P17B") tuneFactor2 = {0, 0.2695663, 0.27947297, 0.5366479, 0.5328953, 0.5414997, 0.5478713, 0.5493841, 0.5485956,0};//P17B AdScaled
    //if (dataPeriod == "P17B") tuneFactor2 = {0,0.5339067, 0.5368185, 0.5454424, 0.5421805, 0.551125, 0.5562799, 0.5576333, 0.5564747,0}; //P17B AdScaledNL
    //if (dataPeriod == "P17B") tuneFactor2 = {0,0.5395587, 0.541633, 0.5501725, 0.5481684, 0.5565015, 0.5609841, 0.56197505,0.5615063,0}; //P17B AdSimpleNL
    //if (dataPeriod == "P17B") tuneFactor2 = {0,1.0369274, 1.0372708, 1.0511066, 1.04981792, 1.0815913, 1.08419447, 1.0841926, 1.08236336,0}; //1.5 cut
    else if (dataPeriod == "P19A") tuneFactor2 = {0, 0.601761, 0.530775, 0.53872, 0.537538, 0.54511, 0.550823, 0.551214, 0.550337,0}; //P19A
    else if (dataPeriod == "P20A") tuneFactor2 = {0, 0.53318, 0.530025, 0.54125, 0.538535, 0.5454, 0.55134, 0.54954, 0.54992,0};    //P20A
    else if (dataPeriod == "P21A") tuneFactor2 = {0, 0.552, 0.5316, 0.53938, 0.53679, 0.54723, 0.55135, 0.55329, 0.552552,0};   //P21A
    else tuneFactor2 = {0, 0.5420256, 0.5294155, 0.537457, 0.5348075, 0.543297, 0.548616, 0.549697, 0.54886,0};     //all data

    for (int nSite=1; nSite<4; nSite++) {
        ifstream infile;
        infile.open(TString::Format("/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/EH%1d/Merge2/P17B_EH%1d_info.txt", nSite, nSite));
        
        int nPoints[10] = {0};
        double eachValue[12] ={0};
        while (!infile.eof()) {
            int j=0;
            
            while(infile.getline(line,sizeof(line),'\n')){
                
                b= strtok(line,a);
                int i=0;
                while (b != NULL)
                {
                    eachValue[i] = atof(b);
                    b=strtok(NULL,a);
                    i++;
                }
                
                int gAdNo = eachValue[1]+(nSite-1)*2;
                int RunNo = eachValue[0];
                int DetNo = eachValue[1];
                
                //if(eachValue[0]>54500) continue;
                unsigned int Date = eachValue[2];
                //cout<<RunNo<<endl;

                double FullT = eachValue[3]*1.0;
                double GapT = eachValue[4]*1.0;
                double LiveT = eachValue[5]*1.0;
                double NetMu = eachValue[10]*1.0;   // check the txt file, may have some problems in this column
                //cout << RunNo << " , " << DetNo << " , " << FullT << endl;
                //if(LiveT > FullT) continue;
                
                double Rmu    = NetMu/LiveT;
                double muRerr = sqrt( NetMu)/LiveT;
                double vetoEff   = LiveT/FullT;
                
                double FullDay = FullT/60.0;
                if(FullDay<=360.0){
                    //cout<<"------ less 360: "<<FullT<<"\t"<<LiveT<<"\t"<<NetMu<<"\t"<<vetoEff<<endl;
                }
                //////////////
                
                //int nDet;
                //if(eachValue[0]<54500) nDet = nSite-1;
                //if(eachValue[0]>54500) nDet = nSite+2;
                int nDet = nSite-1; //for p19a
                    TFile f1( file1[nDet].c_str() );
                
                TKey *key;
                    key = f1.FindKey(TString::Format("%1d",RunNo));
                if (key!=0 && RunNo<90000 ) //80000 for p19a
                {
                    //Get Singles Histo.
                    hSig = (TH1D*)f1.Get( TString::Format("/%1d/h1dEs_%1d_AD%1d",RunNo,RunNo,DetNo) );
                    long int singlesNum = hSig->GetEntries();
                    long int leftSingleNum = hSig->Integral( 71 , 1200);
                    long int rightSingleNum  = hSig->Integral( 151 , 1200);
                    long int promptSingleNum = hSig->Integral( 151 , 1200);
                    long int delaySingleNum  = hSig->Integral( 191 , 1200);
                    //if(leftSingleNum == 0) continue;
                    
                    Nmu_rate[gAdNo]->SetPoint(nPoints[gAdNo],  Date, Rmu);
                    Nmu_rate[gAdNo]->SetPointError(nPoints[gAdNo],0, muRerr);
                    veto_eff[gAdNo]->SetPoint(nPoints[gAdNo],  Date, vetoEff);
                
                    TotalFullT[gAdNo] += FullT;
                    TotalGapT[gAdNo] += GapT;
                    TotalLiveT[gAdNo] += LiveT;
                    TotalMuon[gAdNo] += NetMu;
                    TotalSigles[gAdNo] += singlesNum;
                    TotalPlike[gAdNo] += promptSingleNum;
                    TotalDlike[gAdNo] += delaySingleNum;
                    TotalLlike[gAdNo] += leftSingleNum;
                    TotalRlike[gAdNo] += rightSingleNum;
                    tEs[gAdNo]->Add(hSig);
                    
                    // Distance
                    hEvtDist = (TH1D*)f1.Get( TString::Format("/%1d/h1dDpd_%1d_AD%1d",RunNo,RunNo,DetNo) );
                    hAccDist = (TH1D*)f1.Get( TString::Format("/%1d/h1dDpd_acc_%1d_AD%1d", RunNo ,RunNo,DetNo) );
                    unsigned int totalAccSample = hAccDist->GetEntries();
                    //cout<<RunNo<<"\t"<<singlesNum<<"\t"<<totalAccSample<<"\t"<<hAccDist->GetEntries()<<endl;
                    //if (totalAccSample==0) continue;
                    SumAccNum[gAdNo] += totalAccSample;
                    //Get EpEd
                    h2dIBD = (TH2D*)f1.Get( TString::Format("/%1d/h2dEpEd_IBD_%1d_AD%1d",RunNo,RunNo,DetNo) );
                    h2dACC = (TH2D*)f1.Get( TString::Format("/%1d/h2dEpEd_acc_%1d_AD%1d",RunNo,RunNo,DetNo) );
                    long int NaccCut = h2dACC->GetEntries();  // after distance cut
                    
                    //TH1D *NentronSpec = h2dIBD->ProjectionX();
                    //TH1D *AccBkgSpec  = h2dACC->ProjectionX();
                    
                    // Prompt Spectrum
                    h1EvtEp = (TH1D*)f1.Get( TString::Format("/%1d/h1dEp_IBD_%1d_AD%1d",RunNo,RunNo,DetNo) );
                    h1AccEp = (TH1D*)f1.Get( TString::Format("/%1d/h1dEp_acc_%1d_AD%1d",RunNo,RunNo,DetNo) );
                    unsigned int Nibd = h1EvtEp->GetEntries();
                    unsigned int NaccData = h1AccEp->GetEntries();
                    cout << "Run = " << RunNo << " , AD = " << gAdNo << " , Events = " << h2dIBD->GetEntries() << endl; 
                    
                    
                    ///////////
                    double effABS = NaccCut*1.0/(1.0*totalAccSample);
                    double effABS_err = effABS*sqrt( 1.0/(1.0*NaccCut) + 1.0/(1.0*totalAccSample) );
                    double Eff_iso = 1;
                    //double Eff_iso = exp(ROOT::Math::lambert_W0(-1.*(promptSingleNum*tB4Ed+delaySingleNum*tAfEd)/LiveT));
                    //double Eff_iso = exp(boost::math::lambert_w0(-1.*(promptSingleNum*tB4Ed+delaySingleNum*tAfEd)/LiveT));
                    double Rs      = singlesNum/LiveT/Eff_iso;
                    double Rs_err  = sqrt(singlesNum)/LiveT/Eff_iso;
                    double Rsp     = promptSingleNum/LiveT/Eff_iso;// prompt-like
                    double Rsp_err = sqrt(promptSingleNum)/LiveT/Eff_iso;//prompt-like
                    double Rsd     = delaySingleNum/LiveT/Eff_iso;// delayed-like
                    double Rsd_err = sqrt(delaySingleNum)/LiveT/Eff_iso;//delayed-like
                    
                    /////////
                    // BCW Bei-Zhen OG:
                    double Eff_mBCW = TMath::Exp(-tB4Ed*Rsp)*TMath::Exp(-tAfEd*Rsd);
                    double Eff_mBCW_err= Eff_mBCW*sqrt( tB4Ed*tB4Ed*Rsp_err*Rsp_err + tAfEd*tAfEd*Rsd_err*Rsd_err );
                    
                    double Racc_BCW = (capTime-0.000001)*Rsp*Rsd*Eff_mBCW;
                    double Racc_BCW_err = Racc_BCW*sqrt( (tB4Ed*tB4Ed+ 1.0/(Rsp*Rsp) )*Rsp_err*Rsp_err
                                                        +(tAfEd*tAfEd+ 1.0/(Rsd*Rsd) )*Rsd_err*Rsd_err );
                    //double Racc_BCW_err = Racc_BCW*sqrt( (tB4Ed+ 1.0/Rsp)*(tB4Ed+ 1.0/Rsp)*Rsp_err*Rsp_err
                    //+(tAfEd+ 1.0/Rsd)*(tAfEd+ 1.0/Rsd)*Rsd_err*Rsd_err );
                    
                    // nH/THU:
                    double Eff_mTHU = nHmEff(Rs, Rmu, capTime);
                    double Racc_THU = Rs*Rs*capTime*Eff_mTHU;
                    // double Racc3 = nHAcc(Rs, Rmu, capTime);


                    // update from Yu-Chin

                    
                    /////
                    //double SF    = Racc_BCW*FullT*vetoEff/(1.0*totalAccSample);
                    //double SF_err = SF*sqrt( (Racc_BCW_err*Racc_BCW_err*1.0)/(Racc_BCW*Racc_BCW*1.0)+1.0/(1.0*totalAccSample) );
                    double SF    = 1;
                    double SF_err = 0;
                    //cout<<gAdNo<<"\t"<<SF<<endl;
                    double Nacc = Racc_BCW*FullT*vetoEff*effABS*(1.0*tuneFactor2[gAdNo])/(1.0*LiveT/86400.0);
                    double Nacc_err = Nacc*sqrt( (Racc_BCW_err*Racc_BCW_err*1.0)/(Racc_BCW*Racc_BCW*1.0)
                                                +(effABS_err*effABS_err*1.0)/(effABS*effABS*1.0) );
                    
                    double RnIbd = Nibd*1.0/(1.0*LiveT/86400.0);
                    double RnIbd_err = sqrt( Nibd )*1.0/(1.0*LiveT/86400.0);
                    
                    double RnIbd2 = RnIbd-Nacc;
                    double RnIbd2_err = sqrt(RnIbd_err*RnIbd_err+ Nacc_err*Nacc_err);
                    
                    double Ratio = hEvtDist->Integral(201,500) / hAccDist->Integral(201,500);
                    ///
                    h_dist_evt[gAdNo]->Add(hEvtDist,1.0);
                    h_dist_acc[gAdNo]->Add(hAccDist,1.0);//tuneFactor2[gAdNo]
                    //h_dist_acc[gAdNo]->Add(hAccDist,1.0);//tuneFactor2[gAdNo]
                    //h_dist_acc[gAdNo]->Add(hAccDist,1.0*SF*(1.0*tuneFactor2[gAdNo]));//tuneFactor2[gAdNo]
                    h_dist_sub[gAdNo]->Add(h_dist_evt[gAdNo],h_dist_acc[gAdNo],1.0, -1);
                    
                    hEpd_evt[gAdNo]->Add(h2dIBD,1.0);
                    hEpd_acc[gAdNo]->Add(h2dACC,1.0); //tuneFactor2[gAdNo]
                    //hEpd_acc[gAdNo]->Add(h2dACC,1.0*SF*(1.0*tuneFactor2[gAdNo])); //tuneFactor2[gAdNo]
                    hEpd_sub[gAdNo]->Add(hEpd_evt[gAdNo],hEpd_acc[gAdNo],1.0, -1);
                    
                    int nbins = h1EvtEp->GetNbinsX();
                    TH1D *h2   = new TH1D("h2","test histo2",nbins,0,12);
                    //cout<<nbins<<endl;
                    for (int k = 1; k <= nbins; k++) {
                        double NumE = h1EvtEp->GetBinContent(k);
                        double NumA = h1AccEp->GetBinContent(k);
                        double evtE = h1EvtEp->GetBinError(k);
                        double accE = h1AccEp->GetBinError(k);
                        double setBinE = binErr (NumE, NumA, accE, SF, SF_err, (1.0*tuneFactor2[gAdNo]));
                        //double setBinE = binErr (double evtErr, double accN, double accErr, double scaleN, double scaleErr, double factor);
                      
                        //h2 -> SetBinContent( k, NumE - Ratio*NumA);
                        //h2 -> SetBinError( k, sqrt(NumE + Ratio*NumA));
                        h2 -> SetBinContent( k, NumE - 1.0*SF*(1.0*tuneFactor2[gAdNo])*NumA);
                        h2 -> SetBinError( k, setBinE);
                    }
                    subP[gAdNo]->Add(h2,1);
                    delete h2;
                    
                    //NentronSpec
                    TString temp_name_IBD = (TString)h2dIBD->GetName() + "_px";
                    TString temp_name_ACC = (TString)h2dACC->GetName() + "_px";
                    auto h3e = h2dIBD->ProjectionX(temp_name_IBD,16,-1);
                    auto h3a = h2dACC->ProjectionX(temp_name_ACC,16,-1);
                    
                    int NSbins = h3e ->GetNbinsX();
                    TH1D *h3   = new TH1D("h3","test histo3",NSbins,0,12);
                    for (int k = 1; k <= NSbins; k++) {
                        double NumE = h3e->GetBinContent(k);
                        double NumA = h3a->GetBinContent(k);
                        double evtE = h3e->GetBinError(k);
                        double accE = h3a->GetBinError(k);
                        double setBinE = binErr (NumE, NumA, accE, SF, SF_err, (1.0*tuneFactor2[gAdNo]));
                        //double setBinE = binErr (double evtErr, double accN, double accErr, double scaleN, double scaleErr, double factor);
                        
                        //h3 -> SetBinContent( k, NumE - Ratio*NumA);
                        //h3 -> SetBinError( k, sqrt(NumE + Ratio*NumA));
                        h3 -> SetBinContent( k, NumE - 1.0*SF*(1.0*tuneFactor2[gAdNo])*NumA);
                        h3 -> SetBinError( k, setBinE);
                    }
                    subD[gAdNo]->Add(h3,1);
                    delete h3;
                    
                    
                    Nsg_rate[gAdNo]->SetPoint(nPoints[gAdNo],  Date, Rs);
                    Nsg_rate[gAdNo]->SetPointError(nPoints[gAdNo],0, Rs_err);
                    
                    multi_eff[gAdNo]->SetPoint(nPoints[gAdNo],  Date, Eff_mBCW);
                    multi_eff[gAdNo]->SetPointError(nPoints[gAdNo],0, Eff_mBCW_err);
                    
                    Nacc_rate[gAdNo]->SetPoint(nPoints[gAdNo],  Date, Nacc);
                    Nacc_rate[gAdNo]->SetPointError(nPoints[gAdNo],0, Nacc_err);
                    
                    Nibd_rate[gAdNo]->SetPoint(nPoints[gAdNo],  Date, RnIbd);
                    Nibd_rate[gAdNo]->SetPointError(nPoints[gAdNo],0, RnIbd_err);
                    
                    ibdRate2[gAdNo]->SetPoint(nPoints[gAdNo],  Date, RnIbd2);
                    ibdRate2[gAdNo]->SetPointError(nPoints[gAdNo],0, RnIbd2_err);
                    
                }
                ////////////////
                nPoints[gAdNo]++;
                //}///tmp
            }// loop each element
        }// loop each line
    }// loop each site



    int ad;
    double s,sl,sr,sp,sd;
    double tfull,tlive,tgap;


    info->Branch("AD",&ad,"AD/I");
    info->Branch("FullTime",&tfull,"FullTime/D");
    info->Branch("TimeGap",&tgap,"TimeGap/D");
    info->Branch("LiveTime",&tlive,"LiveTime/D");
    info->Branch("Singles",&s,"Singles/D");
    info->Branch("LeftSingles",&sl,"LeftSingles/D");
    info->Branch("RightSingles",&sr,"RightSingles/D");
    info->Branch("PromptLikeSingles",&sp,"PromptLikeSingles/D");
    info->Branch("DelayedLikeSingles",&sd,"DelayedLikeSingles/D");

    
    for (int n=1; n<=8; n++) {
        double tVetoEff = TotalLiveT[n]/(1.0*TotalFullT[n]);
        double tRs      = TotalSigles[n]/(1.0*TotalLiveT[n]);
        double tRs_err  = sqrt(TotalSigles[n])/(1.0*TotalLiveT[n]);
        double tRsp     = TotalPlike[n]/(1.0*TotalLiveT[n]);// prompt-like
        double tRsp_err = sqrt(TotalPlike[n])/(1.0*TotalLiveT[n]);//prompt-like
        double tRsd     = TotalDlike[n]/(1.0*TotalLiveT[n]);// delayed-like
        double tRsd_err = sqrt(TotalDlike[n])/(1.0*TotalLiveT[n]);//delayed-like
        
        double tRmu = TotalMuon[n]/(1.0*TotalLiveT[n]);
        double tRmu_err = sqrt(TotalMuon[n])/(1.0*TotalLiveT[n]);
        

        ad = n;
        tfull = TotalFullT[n];
        tgap = TotalGapT[n];
        tlive = TotalLiveT[n];
        s = TotalSigles[n];
        sl = TotalLlike[n]; 
        sr = TotalRlike[n]; 
        sp = TotalPlike[n]; 
        sd = TotalDlike[n]; 
        info->Fill();


        /////////
        // BCW:
        double tEff_mBCW = TMath::Exp(-tB4Ed*tRsp)*TMath::Exp(-tAfEd*tRsd);
        double tEff_mBCW_err= tEff_mBCW*sqrt( tB4Ed*tB4Ed*tRsp_err*tRsp_err + tAfEd*tAfEd*tRsd_err*tRsd_err );
        
        double tRacc_BCW = (capTime-0.000001)*tRsp*tRsd*tEff_mBCW;
        double tRacc_BCW_err = tRacc_BCW*sqrt( (tB4Ed+ 1.0/tRsp)*(tB4Ed+ 1.0/tRsp)*tRsp_err*tRsp_err
                                              +(tAfEd+ 1.0/tRsd)*(tAfEd+ 1.0/tRsd)*tRsd_err*tRsd_err );
        
        double tSF    = tRacc_BCW*TotalFullT[n]*tVetoEff/(1.0*SumAccNum[n]);
        double tSF_err = tSF*sqrt( (tRacc_BCW_err*tRacc_BCW_err*1.0)/(tRacc_BCW*tRacc_BCW*1.0)+1.0/(1.0*SumAccNum[n]) );
        
        //cout<<TotalFullT[n]/86400.0<<","<<tVetoEff<<","<<tEff_mBCW<<","<<tEff_mBCW_err<<","<<tRacc_BCW<<","<<tRacc_BCW_err
                                     //<<","<<tRs<<","<<tRs_err<<","<<tRmu<<","<<tRmu_err<<", "<<tSF_err<<endl;
        cout << "AD" << n << " , DAQ time = " << TotalFullT[n]/86400.0 << " , Live time = " << TotalLiveT[n]/86400.0 << " , veto eff = " << tVetoEff
             << " , Multi eff = " << tEff_mBCW << "+-" << tEff_mBCW_err << std::endl;
    }
    
    EndJob();
    
   
}



int BeginJob()
{
    cout << "Initializing ..." << endl;
    for(int gAdNo = 1; gAdNo<9 ;gAdNo++){
        Nmu_rate[gAdNo]   = new TGraphErrors();
        Nsg_rate[gAdNo]   = new TGraphErrors();
        Nacc_rate[gAdNo]   = new TGraphErrors();
        Nibd_rate[gAdNo]   = new TGraphErrors();
        veto_eff[gAdNo]    = new TGraphErrors();
        multi_eff[gAdNo]   = new TGraphErrors();
        ibdRate2[gAdNo]   = new TGraphErrors();
        ////
        
        
        h_dist_evt[gAdNo] = new TH1D(TString::Format("h1dDpd_evt_AD%1d",gAdNo),
                                     TString::Format("h1dDpd_evt_AD%1d",gAdNo),
                                     500, 0, 5000);
        h_dist_acc[gAdNo] = new TH1D(TString::Format("h1dDpd_acc_AD%1d",gAdNo),
                                     TString::Format("h1dDpd_acc_AD%1d",gAdNo),
                                     500, 0, 5000);
        h_dist_sub[gAdNo] = new TH1D(TString::Format("h1dDpd_sub_AD%1d",gAdNo),
                                     TString::Format("h1dDpd_sub_AD%1d",gAdNo),
                                     500, 0, 5000);
        
        
        hEpd_evt[gAdNo] = new TH2D(TString::Format("h2dEpd_evt_AD%1d",gAdNo) ,
                                   TString::Format("h2dEpd_evt_AD%1d",gAdNo) ,
                                   1200, 0, 12,120, 0, 12);
        
        hEpd_acc[gAdNo] = new TH2D(TString::Format("h2dEpd_acc_AD%1d",gAdNo) ,
                                   TString::Format("h2dEpd_acc_AD%1d",gAdNo) ,
                                   1200, 0, 12,120, 0, 12);
        
        hEpd_sub[gAdNo] = new TH2D(TString::Format("h2dEpd_sum_AD%1d",gAdNo) ,
                                   TString::Format("h2dEpd_sum_AD%1d",gAdNo) ,
                                   1200, 0, 12,120, 0, 12);
        
        h_dist_evt[gAdNo] -> Sumw2();
        h_dist_acc[gAdNo] -> Sumw2();
        h_dist_sub[gAdNo] -> Sumw2();
        hEpd_evt[gAdNo] -> Sumw2();
        hEpd_acc[gAdNo] -> Sumw2();
        hEpd_sub[gAdNo] -> Sumw2();
        
        phY[gAdNo] = new TH1D(TString::Format("phY_AD%1d",gAdNo),TString::Format("phY_AD%1d",gAdNo),120, 0,12);
        phX[gAdNo] = new TH1D(TString::Format("phX_AD%1d",gAdNo),TString::Format("phX_AD%1d",gAdNo),1200, 0,12);
        
        evtP_phX[gAdNo] = new TH1D(TString::Format("evt_phX_AD%1d",gAdNo),TString::Format("evt_phX_AD%1d",gAdNo),120, 0,12);
        evtP_phY[gAdNo] = new TH1D(TString::Format("evt_phY_AD%1d",gAdNo),TString::Format("evt_phY_AD%1d",gAdNo),1200, 0,12);
        
        evtA_phX[gAdNo] = new TH1D(TString::Format("acc_phX_AD%1d",gAdNo),TString::Format("acc_phX_AD%1d",gAdNo),120, 0,12);
        evtA_phY[gAdNo] = new TH1D(TString::Format("acc_phY_AD%1d",gAdNo),TString::Format("acc_phY_AD%1d",gAdNo),1200, 0,12);
    
        evtP[gAdNo] = new TH1D(TString::Format("evtP_AD%1d",gAdNo),TString::Format("evtP_AD%1d",gAdNo),120, 0,12);
        accP[gAdNo] = new TH1D(TString::Format("accP_AD%1d",gAdNo),TString::Format("accP_AD%1d",gAdNo),120, 0,12);
        subP[gAdNo] = new TH1D(TString::Format("subP_AD%1d",gAdNo),TString::Format("subP_AD%1d",gAdNo),120, 0,12);
        
        evtD[gAdNo] = new TH1D(TString::Format("evtD_AD%1d",gAdNo),TString::Format("evtD_AD%1d",gAdNo),1200, 0,12);
        accD[gAdNo] = new TH1D(TString::Format("accD_AD%1d",gAdNo),TString::Format("accD_AD%1d",gAdNo),1200, 0,12);
        subD[gAdNo] = new TH1D(TString::Format("subD_AD%1d",gAdNo),TString::Format("subD_AD%1d",gAdNo),1200, 0,12);

        tEs[gAdNo] = new TH1D(TString::Format("Es_AD%d",gAdNo),TString::Format("Es_AD%d",gAdNo),1200,0,12); 
        
        evtP[gAdNo] -> Sumw2();
        accP[gAdNo] -> Sumw2();
        subP[gAdNo] -> Sumw2();
        evtD[gAdNo] -> Sumw2();
        accD[gAdNo] -> Sumw2();
        subD[gAdNo] -> Sumw2();
        
    }
    
    return 1;
}


int EndJob()
{
    
    
    for (int nAd=1; nAd<9; nAd++) {
        
        Nmu_rate[nAd]->SetMarkerSize(1);
        Nmu_rate[nAd]->SetMarkerColor(nAd);
        Nmu_rate[nAd]->SetLineColor(nAd);
        Nmu_rate[nAd]->SetMarkerStyle(4);
        
        Nsg_rate[nAd]->SetMarkerSize(1);
        Nsg_rate[nAd]->SetMarkerColor(nAd);
        Nsg_rate[nAd]->SetLineColor(nAd);
        Nsg_rate[nAd]->SetMarkerStyle(4);
        
        Nacc_rate[nAd]->SetMarkerSize(1);
        Nacc_rate[nAd]->SetMarkerColor(nAd);
        Nacc_rate[nAd]->SetLineColor(nAd);
        Nacc_rate[nAd]->SetMarkerStyle(4);
        
        Nibd_rate[nAd]->SetMarkerSize(1);
        Nibd_rate[nAd]->SetMarkerColor(nAd);
        Nibd_rate[nAd]->SetLineColor(nAd);
        Nibd_rate[nAd]->SetMarkerStyle(4);
        
        veto_eff[nAd]->SetMarkerSize(1);
        veto_eff[nAd]->SetMarkerColor(nAd);
        veto_eff[nAd]->SetLineColor(nAd);
        veto_eff[nAd]->SetMarkerStyle(4);
        
        multi_eff[nAd]->SetMarkerSize(1);
        multi_eff[nAd]->SetMarkerColor(nAd);
        multi_eff[nAd]->SetLineColor(nAd);
        multi_eff[nAd]->SetMarkerStyle(4);
        
        ibdRate2[nAd]->SetMarkerSize(1);
        ibdRate2[nAd]->SetMarkerColor(nAd);
        ibdRate2[nAd]->SetLineColor(nAd);
        ibdRate2[nAd]->SetMarkerStyle(4);
        
        mg1->Add( Nmu_rate[nAd] );
        mg2->Add( Nsg_rate[nAd] );
        mg3->Add( veto_eff[nAd] );
        mg4->Add( multi_eff[nAd] );
        mg5->Add( Nacc_rate[nAd] );
        mg6->Add( Nibd_rate[nAd] );
        mg7->Add( ibdRate2[nAd] );
    }
    
    TString outputpath = "/Users/chengyuchin/Analysis/Plots/" + dataPeriod + "/";
    TCanvas *c1 = new TCanvas(TString::Format("c1"),TString::Format("c1"),800,600);
    mg1->Draw("AP");
    mg1->GetXaxis()->SetTimeDisplay(1);
    mg1->GetXaxis()->SetTimeFormat("%b-%d");
    mg1->GetXaxis()->SetNdivisions(712);
    mg1->GetYaxis()->SetTitle("muon rate");
    mg1->GetXaxis()->SetTitle("Date");
    if(SavePlots && Postsub) c1->SaveAs( outputpath+"MuRate.png");
    
    TCanvas *c2 = new TCanvas(TString::Format("c2"),TString::Format("c2"),800,600);
    mg2->Draw("AP");
    mg2->GetXaxis()->SetTimeDisplay(1);
    mg2->GetXaxis()->SetTimeFormat("%b-%d");
    mg2->GetXaxis()->SetNdivisions(712);
    mg2->GetYaxis()->SetTitle("Singles rate");
    mg2->GetXaxis()->SetTitle("Date");
    if(SavePlots && Postsub) c2->SaveAs( outputpath+"SgRate.png");
    
    TCanvas *c3 = new TCanvas(TString::Format("c3"),TString::Format("c3"),800,600);
    mg3->Draw("AP");
    mg3->GetXaxis()->SetTimeDisplay(1);
    mg3->GetXaxis()->SetTimeFormat("%b-%d");
    mg3->GetXaxis()->SetNdivisions(712);
    mg3->GetYaxis()->SetTitle("Veto Eff");
    mg3->GetXaxis()->SetTitle("Date");
    if(SavePlots && Postsub) c3->SaveAs( outputpath+"VetoEff.png");
    
    TCanvas *c4 = new TCanvas(TString::Format("c4"),TString::Format("c4"),800,600);
    mg4->Draw("AP");
    mg4->GetXaxis()->SetTimeDisplay(1);
    mg4->GetXaxis()->SetTimeFormat("%b-%d");
    mg4->GetXaxis()->SetNdivisions(712);
    mg4->GetYaxis()->SetTitle("Multi Eff");
    mg4->GetXaxis()->SetTitle("Date");
    if(SavePlots && Postsub) c4->SaveAs( outputpath+"MultiEff.png");
    
    TCanvas *c5 = new TCanvas(TString::Format("c5"),TString::Format("c5"),800,600);
    mg5->Draw("AP");
    mg5->GetXaxis()->SetTimeDisplay(1);
    mg5->GetXaxis()->SetTimeFormat("%b-%d");
    mg5->GetXaxis()->SetNdivisions(712);
    mg5->GetYaxis()->SetTitle("Acc Rate");
    mg5->GetXaxis()->SetTitle("Date");
    mg5->GetYaxis()->SetLimits(-500,5000);
    if(SavePlots && Postsub) c5->SaveAs( outputpath+"AccRate.png");
    
    TCanvas *c6 = new TCanvas(TString::Format("c6"),TString::Format("c6"),800,600);
    mg6->Draw("AP");
    mg6->GetXaxis()->SetTimeDisplay(1);
    mg6->GetXaxis()->SetTimeFormat("%b-%d");
    mg6->GetXaxis()->SetNdivisions(712);
    mg6->GetYaxis()->SetTitle("IBD Candidate Rate");
    mg6->GetXaxis()->SetTitle("Date");
    mg6->GetYaxis()->SetLimits(-500,5000);
    if(SavePlots && Postsub) c6->SaveAs( outputpath+"IBDCRate.png");

    TCanvas *c7 = new TCanvas(TString::Format("c7"),TString::Format("c7"),800,600);
    mg7->Draw("AP");
    mg7->GetXaxis()->SetTimeDisplay(1);
    mg7->GetXaxis()->SetTimeFormat("%b-%d");
    mg7->GetXaxis()->SetNdivisions(712);
    mg7->GetYaxis()->SetTitle("IBD Rate");
    mg7->GetXaxis()->SetTitle("Date");
    mg7->GetYaxis()->SetLimits(-500,5000);
    if(SavePlots && Postsub) c7->SaveAs( outputpath+"IBDRate.png");
    

    string rootname;
    if(Postsub) rootname = "postsub";
    else rootname = "presub";
    int l = 10;
    TCanvas* cvs[100];
    if(SavePlots && !Postsub) gStyle->SetOptFit(1);
    TFile *ttfile = new TFile(TString::Format("%s_IBD_%s.root",dataPeriod.c_str(),rootname.c_str()),"recreate");
    for (int nAd=1; nAd<9; nAd++) {
        //double Ratio = h_dist_evt[nAd]->Integral(201,500)/h_dist_acc[nAd]->Integral(201,500);
        //h_dist_sub[nAd]->Add(h_dist_evt[nAd],h_dist_acc[nAd],1.,-1.*Ratio);
        
        cvs[l] = new TCanvas(TString::Format("c%i",l),TString::Format("c%i",l),1600,900);
        if(Postsub){
            h_dist_evt[nAd]->Draw("");
            h_dist_acc[nAd]->Draw("same");
            h_dist_sub[nAd]->Draw("same");
        }
        else{
            h_dist_sub[nAd]->Draw();
            h_dist_sub[nAd]->Fit("pol0","","",2000,5000);
            h_dist_evt[nAd]->Draw("same");
            h_dist_acc[nAd]->Draw("same");
            if(SavePlots) cvs[l]->SaveAs( outputpath + TString::Format("AD%i_dpd_sub.png",nAd));
        }
        l++;

        cvs[l] = new TCanvas(TString::Format("c%i",l),TString::Format("c%i",l),1600,900);
        gPad->SetLogz(1);
        hEpd_sub[nAd]->Draw("colz");
        if(SavePlots && Postsub) cvs[l]->SaveAs( outputpath + TString::Format("AD%i_2D.png",nAd));

        phX[nAd] = hEpd_sub[nAd]->ProjectionX();
        phY[nAd] = hEpd_sub[nAd]->ProjectionY();
        
        evtP_phX[nAd] = hEpd_evt[nAd]->ProjectionX();
        evtP_phY[nAd] = hEpd_evt[nAd]->ProjectionY();
        evtA_phX[nAd] = hEpd_acc[nAd]->ProjectionX();
        evtA_phY[nAd] = hEpd_acc[nAd]->ProjectionY();
        l++;
        
        cvs[l] = new TCanvas(TString::Format("c%i",l),TString::Format("c%i",l),1600,900);
        gPad->SetLogy(1);
        evtP_phX[nAd]->Draw("");
        evtA_phX[nAd]->Draw("same");
        phX[nAd]->Draw("same");
        evtP_phX[nAd]->SetLineColor(1);
        evtA_phX[nAd]->SetLineColor(2);
        phX[nAd]->SetLineColor(4);
        phX[nAd]->SetTitle("");
        phX[nAd]->GetXaxis()->SetTitle("E [MeV]");
        evtP_phX[nAd]->SetTitle("");
        evtP_phX[nAd]->GetXaxis()->SetTitle("E [MeV]");
        evtA_phX[nAd]->SetTitle("");
        evtA_phX[nAd]->GetXaxis()->SetTitle("E [MeV]");
        if(SavePlots && Postsub) cvs[l]->SaveAs( outputpath + TString::Format("AD%i_Ed.png",nAd));
        l++;
        
        cvs[l] = new TCanvas(TString::Format("c%i",l),TString::Format("c%i",l),1600,900);
        gPad->SetLogy(1);
        evtP_phY[nAd]->Draw("");
        evtA_phY[nAd]->Draw("same");
        phY[nAd]->Draw("same");
        evtP_phY[nAd]->SetLineColor(1);
        evtA_phY[nAd]->SetLineColor(2);
        phY[nAd]->SetLineColor(4);
        phY[nAd]->SetTitle("");
        phY[nAd]->GetXaxis()->SetTitle("E [MeV]");
        evtP_phY[nAd]->SetTitle("");
        evtP_phY[nAd]->GetXaxis()->SetTitle("E [MeV]");
        evtA_phY[nAd]->SetTitle("");
        evtA_phY[nAd]->GetXaxis()->SetTitle("E [MeV]");
        h_dist_evt[nAd]->Write();
        if(SavePlots && Postsub) cvs[l]->SaveAs( outputpath + TString::Format("AD%i_Ep.png",nAd));
        l++;
        
        cvs[l] = new TCanvas(TString::Format("c%i",l),TString::Format("c%i",l),1600,900);
        gPad->SetLogy(1);
        subP[nAd]->Draw("");
        subP[nAd]->SetLineColor(1);
        subP[nAd]->SetMarkerStyle(20);
        subP[nAd]->SetMarkerSize(0.3);
        l++;
        
        cvs[l] = new TCanvas(TString::Format("c%i",l),TString::Format("c%i",l),1600,900);
        gPad->SetLogy(1);
        subD[nAd]->Draw("");
        subD[nAd]->SetLineColor(1);
        subD[nAd]->SetMarkerStyle(20);
        subD[nAd]->SetMarkerSize(0.3);
        l++;
        
        h_dist_evt[nAd]->SetLineColor(1);
        h_dist_acc[nAd]->SetLineColor(2);
        h_dist_sub[nAd]->SetLineColor(4);
        
        
        
        
        
        h_dist_acc[nAd]->Write();
        h_dist_sub[nAd]->Write();
        hEpd_evt[nAd]->Write();
        hEpd_acc[nAd]->Write();
        hEpd_sub[nAd]->Write();
        evtP_phX[nAd]->Write();
        evtA_phX[nAd]->Write();
        phX[nAd]->Write();
        evtP_phY[nAd]->Write();
        evtA_phY[nAd]->Write();
        phY[nAd]->Write();
        subP[nAd]->Write();
        subD[nAd]->Write();
        tEs[nAd]->Write();
        

        long int evtNum0 = h_dist_evt[nAd]->Integral( 0, 50);
        long int bkgNum0 = h_dist_acc[nAd]->Integral( 0, 50);
        long int subNum0 = h_dist_sub[nAd]->Integral( 0, 50);
        
        long int evtNum = h_dist_evt[nAd]->Integral( 200, 500);
        long int bkgNum = h_dist_acc[nAd]->Integral( 200, 500);
        long int subNum = h_dist_sub[nAd]->Integral( 200, 500);
        //cout<<nAd<<"\t"<<evtNum0<<"\t"<<bkgNum0<<"\t"<<subNum0<<"\t"<<(1.0*subNum0)/(1.0*bkgNum0)<<endl;
        
        //cout<<nAd<<"\t"<<evtNum<<"\t"<<bkgNum<<"\t"<<subNum<<"\t"<<(1.0*subNum)/(1.0*bkgNum)<<endl;
    }



    info->Write();
    
    return 1;
}

/////////
//long int singlesNum = hSig->GetEntries();
//long int promptSingleNum = hSig->Integral( 71 , 1200);
//long int delaySingleNum  = hSig->Integral( 601 , 1200);
/*
 long int singlesNum = hSig->Integral( 151 , 1200);
 long int promptSingleNum = hSig->Integral( 151 , 1200);
 long int delaySingleNum  = hSig->Integral( 190 , 271);
 */

/*
 h_dist_evt[nAd]->Rebin(2);
 h_dist_acc[nAd]->Rebin(2);
 h_dist_sub[nAd]->Rebin(2);

 
 hEpd_evt[nAd]->GetXaxis()->SetRangeUser(1.5,12);
 hEpd_evt[nAd]->GetYaxis()->SetRangeUser(1.5,12);
 hEpd_acc[nAd]->GetXaxis()->SetRangeUser(1.5,12);
 hEpd_acc[nAd]->GetYaxis()->SetRangeUser(1.5,12);
 
 hEpd_sub[nAd]->GetXaxis()->SetRangeUser(1.5,12);
 hEpd_sub[nAd]->GetYaxis()->SetRangeUser(1.5,12);
 */
int main(){
    unifiedPlots();
    return 0;
}
