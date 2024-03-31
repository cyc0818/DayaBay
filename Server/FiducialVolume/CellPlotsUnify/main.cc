#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>


#include "TFile.h"
#include "TString.h"
#include "TKey.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"


using namespace std;


int BeginJob();
bool EndJob(TString workdir, int CellNo);
double binErr(double evtN, double accN, double accErr, double scaleN, double scaleErr, double factor);


map< int /* Run */, TH2D* >  hEpd_evt;
map< int /* Run */, TH2D* >  hEpd_acc;
map< int /* Run */, TH2D* >  hEpd_sub;


map< int /* Run */, TH1D* >  evtD;
map< int /* Run */, TH1D* >  accD;
map< int /* Run */, TH1D* >  subD;



int main(int argc, const char** argv){  // workdir, CellNo

    if(argc != 3){
        cerr << "Error occurs due to wrong argument number!" << endl;
        return 0;
    }

    TString WorkDir = argv[1];
    int CellNo = stoi(argv[2]);

    double capTime = 0.0004;
    double tB4Ed = 2.0*capTime;
    double tAfEd = 1.0*capTime;
    const int SIZE = 1000;
    char line [SIZE];
    char* a="\t";
    char* b;

    TString inRootFile[3] = {WorkDir + "/EH1_CellPlots.root",
        WorkDir + "/EH2_CellPlots.root",
        WorkDir + "/EH3_CellPlots.root"};

    TString intxtFile[3] = {WorkDir + "/P17B_EH1_info.txt",
        WorkDir + "/P17B_EH2_info.txt",
        WorkDir + "/P17B_EH3_info.txt"};

    TH1D* hSig;
    TH1D* hAccDist;
    TH2D* h2dIBD;
    TH2D* h2dACC;
    TH2D* h2dIBDcell;
    TH2D* h2dACCcell;


    BeginJob();

    double tuneFactor2[10]  = {0, 0.9706645, 0.97279267, 0.9877343, 0.98596033, 1.0129578, 1.01612774, 1.01594523, 1.01386021,0};// P17B 4mcut

    for (int nSite=1; nSite<4; nSite++) {
        ifstream infile;
        infile.open(intxtFile[nSite-1]);

        double eachValue[11] ={0};
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
                cout<<RunNo<<endl;

                double FullT = eachValue[3]*1.0;
                double LiveT = eachValue[4]*1.0;
                double NetMu = eachValue[9]*1.0;

                double Rmu    = NetMu/LiveT;
                double muRerr = sqrt( NetMu)/LiveT;
                double vetoEff   = LiveT/FullT;

                double FullDay = FullT/60.0;
                if(FullDay<=360.0){
                    cout<<"------ less 360: "<<FullT<<"\t"<<LiveT<<"\t"<<NetMu<<"\t"<<vetoEff<<endl;
                }


                TFile f1(inRootFile[nSite-1]);
                /*TKey *key;
                key = f1.FindKey(TString::Format("%d/%1d",CellNo,RunNo));*/

                //Get Singles Histo.
                hSig = (TH1D*)f1.Get( TString::Format("/%1d/h1dEs_%1d_AD%1d",RunNo,RunNo,DetNo) );
                long int singlesNum = hSig->GetEntries();
                long int promptSingleNum = hSig->Integral( 151 , 1200);
                long int delaySingleNum  = hSig->Integral( 191 , 1200);


                // Distance
                hAccDist = (TH1D*)f1.Get( TString::Format("/%1d/h1dDpd_acc_%1d_AD%1d",RunNo,RunNo,DetNo) );
                unsigned int totalAccSample = hAccDist->GetEntries();
                cout<<RunNo<<"\t"<<singlesNum<<"\t"<<totalAccSample<<"\t"<<hAccDist->GetEntries()<<endl;
                if (totalAccSample==0) continue;


                //Get EpEd
                h2dIBD = (TH2D*)f1.Get( TString::Format("/%1d/h2dEpEd_IBD_%1d_AD%1d",RunNo,RunNo,DetNo) );
                h2dACC = (TH2D*)f1.Get( TString::Format("/%1d/h2dEpEd_acc_%1d_AD%1d",RunNo,RunNo,DetNo) );
                h2dIBDcell = (TH2D*)f1.Get( TString::Format("/Cell%d/%1d/h2dEpEd_IBD_%1d_AD%1d_Cell%d",CellNo,RunNo,RunNo,DetNo,CellNo) );
                h2dACCcell = (TH2D*)f1.Get( TString::Format("/Cell%d/%1d/h2dEpEd_acc_%1d_AD%1d_Cell%d",CellNo,RunNo,RunNo,DetNo,CellNo) );
                long int NaccCut = h2dACC->GetEntries();  // after distance cut


                double effABS = NaccCut*1.0/(1.0*totalAccSample);
                double effABS_err = effABS*sqrt( 1.0/(1.0*NaccCut) + 1.0/(1.0*totalAccSample) );
                double Rs      = singlesNum/LiveT;
                double Rs_err  = sqrt(singlesNum)/LiveT;
                double Rsp     = promptSingleNum/LiveT;// prompt-like
                double Rsp_err = sqrt(promptSingleNum)/LiveT;//prompt-like
                double Rsd     = delaySingleNum/LiveT;// delayed-like
                double Rsd_err = sqrt(delaySingleNum)/LiveT;//delayed-like


                // BCW:
                double Eff_mBCW = TMath::Exp(-tB4Ed*Rsp)*TMath::Exp(-tAfEd*Rsd);
                double Eff_mBCW_err= Eff_mBCW*sqrt( tB4Ed*tB4Ed*Rsp_err*Rsp_err + tAfEd*tAfEd*Rsd_err*Rsd_err );

                double Racc_BCW = (capTime-0.000001)*Rsp*Rsd*Eff_mBCW;
                double Racc_BCW_err = Racc_BCW*sqrt( (tB4Ed*tB4Ed+ 1.0/(Rsp*Rsp) )*Rsp_err*Rsp_err
                        +(tAfEd*tAfEd+ 1.0/(Rsd*Rsd) )*Rsd_err*Rsd_err );


                double SF    = Racc_BCW*FullT*vetoEff/(1.0*totalAccSample);
                double SF_err = SF*sqrt( (Racc_BCW_err*Racc_BCW_err*1.0)/(Racc_BCW*Racc_BCW*1.0)+1.0/(1.0*totalAccSample) );


                hEpd_evt[gAdNo]->Add(h2dIBDcell,1.0);
                hEpd_acc[gAdNo]->Add(h2dACCcell,1.0*SF*(1.0*tuneFactor2[gAdNo])); //tuneFactor2[gAdNo]
                hEpd_sub[gAdNo]->Add(hEpd_evt[gAdNo],hEpd_acc[gAdNo],1.0, -1.0);


                //NentronSpec
                auto h3e = h2dIBDcell->ProjectionX();
                auto h3a = h2dACCcell->ProjectionX();

                int NSbins = h3e->GetNbinsX();
                TH1D *h3 = new TH1D("h3","test histo3",NSbins,0,12);
                for(int k = 1; k <= NSbins; k++){
                    double NumE = h3e->GetBinContent(k);
                    double NumA = h3a->GetBinContent(k);
                    double evtE = h3e->GetBinError(k);
                    double accE = h3a->GetBinError(k);
                    double setBinE = binErr (NumE, NumA, accE, SF, SF_err, (1.0*tuneFactor2[gAdNo]));


                    h3->SetBinContent( k, NumE - 1.0*SF*(1.0*tuneFactor2[gAdNo])*NumA);
                    h3->SetBinError( k, setBinE);
                }
                subD[gAdNo]->Add(h3,1);
                delete h3;

            }// loop each element
        }// loop each line
    }// loop each site


    if(EndJob(WorkDir, CellNo)) cout << "Accidental subtraction of cell " << CellNo << " complete!" << endl; 


    return 1;


}



int BeginJob()
{
    for(int gAdNo = 1; gAdNo<9 ;gAdNo++){

        hEpd_evt[gAdNo] = new TH2D(TString::Format("h2dEpd_evt_AD%1d",gAdNo) ,
                TString::Format("h2dEpd_evt_AD%1d",gAdNo) ,
                1200, 0, 12,120, 0, 12);

        hEpd_acc[gAdNo] = new TH2D(TString::Format("h2dEpd_acc_AD%1d",gAdNo) ,
                TString::Format("h2dEpd_acc_AD%1d",gAdNo) ,
                1200, 0, 12,120, 0, 12);

        hEpd_sub[gAdNo] = new TH2D(TString::Format("h2dEpd_sum_AD%1d",gAdNo) ,
                TString::Format("h2dEpd_sum_AD%1d",gAdNo) ,
                1200, 0, 12,120, 0, 12);

        hEpd_evt[gAdNo]->Sumw2();
        hEpd_acc[gAdNo]->Sumw2();
        hEpd_sub[gAdNo]->Sumw2();


        evtD[gAdNo] = new TH1D(TString::Format("evtD_AD%1d",gAdNo),TString::Format("evtD_AD%1d",gAdNo),1200, 0,12);
        accD[gAdNo] = new TH1D(TString::Format("accD_AD%1d",gAdNo),TString::Format("accD_AD%1d",gAdNo),1200, 0,12);
        subD[gAdNo] = new TH1D(TString::Format("subD_AD%1d",gAdNo),TString::Format("subD_AD%1d",gAdNo),1200, 0,12);

        evtD[gAdNo]->Sumw2();
        accD[gAdNo]->Sumw2();
        subD[gAdNo]->Sumw2();

    }

    return 1;
}


bool EndJob(TString workdir, int CellNo){

    TFile *ttfile = new TFile(workdir + TString::Format("/P17B_Cell%d_postsub.root",CellNo),"recreate");
    ttfile->mkdir(TString::Format("Cell%d",CellNo));
    ttfile->cd(TString::Format("Cell%d",CellNo));


    for (int nAd=1; nAd<9; nAd++) {
        hEpd_sub[nAd]->SetNameTitle(TString::Format("2DPlots_AD%d_Cell%d",nAd,CellNo),
                TString::Format("2DPlots_AD%d_Cell%d;E_{d}(MeV);E_{p}(MeV)",nAd,CellNo));
        subD[nAd]->SetNameTitle(TString::Format("AD%d_Cell%d",nAd,CellNo), TString::Format("AD%d_Cell%d;E_{d}(MeV);Counts",nAd,CellNo));


        hEpd_sub[nAd]->Write();
        subD[nAd]->Write();
    }
    ttfile->Close();


    return true;
}




double binErr(double evtN, double accN, double accErr, double scaleN, double scaleErr, double factor){

    double totalErr2 = evtN + (factor*accN)*(factor*accN)*scaleErr*scaleErr + (factor*scaleN)*(factor*scaleN)*accErr*accErr;


    return sqrt(totalErr2);


}




