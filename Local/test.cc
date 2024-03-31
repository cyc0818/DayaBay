#include "EdSpectrum.h"


using namespace std;
void test(){
//int main(){

    unique_ptr<TStopwatch> timer(new TStopwatch());
    TVirtualFitter::SetMaxIterations(100000);
    timer->Start();
    gStyle->SetOptFit(1);
    gStyle->SetOptStat(0);
    //TString MCpath = "/Users/chengyuchin/Analysis/data/MC/fromLiJJ/MC3142Cell.root";
    //TString MCpath = "/Users/chengyuchin/Analysis/data/MC/Efficiency_noMOgen.root";
    TString MCpath = "/Users/chengyuchin/Analysis/data/MC/Efficiency_old.root";
    //TString MCpath = "/Users/chengyuchin/Analysis/data/MC/M14A/NTUNoEdCut_Plots.root";
    TString datapath = "/Users/chengyuchin/Analysis/data/P17B_new/AccSub/P17B_accsub_final_800iso_mergefar_40.root";
    //TString datapath = "/Users/chengyuchin/Analysis/P17B_accsub_by_dis_1515cut.root";
    //TString datapath = "./smearnGd.root";
    //TString datapath = "/Users/chengyuchin/Analysis/Spc_Cut/P17B_IBD_AdSimple.root";
    TCanvas* c[50];
    //TF1* func[9][3];
    int CanvasNo = 0;
    c[45] = new TCanvas("c45","c45",1920,1080);
    c[46] = new TCanvas("c46","c46",1920,1080);


    vector<EdSpectrum> AD;
    vector<TGraphErrors*> g;
    vector<TGraphErrors*> g2;
    AD.push_back(EdSpectrum(MCpath));
    g.push_back(nullptr);
    g2.push_back(nullptr);
    //for(int i = 1; i<6;i++){
    for(int i = 1; i<5;i++){
        AD.push_back(EdSpectrum(datapath,i));
        g.push_back(new TGraphErrors());
        g2.push_back(new TGraphErrors());
        /*func[i][0] = new TF1(TString::Format("fAD%d_%d",i,0),"pol1",0,8);
        func[i][1] = new TF1(TString::Format("fAD%d_%d",i,1),"pol1",0,8);
        func[i][2] = new TF1(TString::Format("fAD%d_%d",i,2),"expo",0,8);*/
    }


    AD[0].nHFit();
    AD[0].nGdFit();
    const double w = AD[1].Data->GetXaxis()->GetBinWidth(1);
    //AD[5].Rename("EH3");


    //for(int i = 1; i<6;i++){
    for(int i = 1; i<5;i++){

        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        AD[i].nHFit();
        AD[i].MCnHCorrection(AD[0]);
        CanvasNo++;


        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        //AD[i].nGdFit();
        AD[i].DYBFit();
        AD[i].MCnGdCorrection(AD[0]);
        //AD[i].GaussianConvolute(64,0.03528);
        AD[i].isMC = true;
        AD[i].DYBFit();
        CanvasNo++;

        
        /*int a = 0;
        for(int j = 0; j<(4.-3.)/w; j++){
            double x = 3+j*w;
            if(AD[i].Data->GetBinContent(AD[i].Data->FindBin((x+0.1*w))) > 0){
                g[i]->SetPoint(a, AD[i].Data->GetBinCenter(AD[i].Data->FindBin((x+0.1*w))), 
                               log(AD[i].Data->GetBinContent(AD[i].Data->FindBin((x+0.1*w)))));
                g[i]->SetPointError(a, 0,
                                    AD[i].Data->GetBinError(AD[i].Data->FindBin((x+0.1*w)))/AD[i].Data->GetBinContent(AD[i].Data->FindBin((x+0.1*w))));
                a++;
            }

            g2[i]->SetPoint(j, AD[i].Gd->GetBinCenter(AD[i].Gd->FindBin((x+0.1*w))), 
                            log(AD[i].Gd->GetBinContent(AD[i].Gd->FindBin((x+0.1*w)))));
            g2[i]->SetPointError(j, 0,
                                 AD[i].Gd->GetBinError(AD[i].Gd->FindBin((x+0.1*w)))/AD[i].Gd->GetBinContent(AD[i].Gd->FindBin((x+0.1*w))));
        }
        for(int j = 0; j<(7.-6.)/w; j++){
            double x = 6+j*w;
            if(AD[i].Data->GetBinContent(AD[i].Data->FindBin((x+0.1*w))) > 0){
                g[i]->SetPoint(a, AD[i].Data->GetBinCenter(AD[i].Data->FindBin((x+0.1*w))), 
                               log(AD[i].Data->GetBinContent(AD[i].Data->FindBin((x+0.1*w)))));
                g[i]->SetPointError(a, 0,
                                    AD[i].Data->GetBinError(AD[i].Data->FindBin((x+0.1*w)))/AD[i].Data->GetBinContent(AD[i].Data->FindBin((x+0.1*w))));
                a++;
            }

            g2[i]->SetPoint(j+100, AD[i].Gd->GetBinCenter(AD[i].Gd->FindBin((x+0.1*w))), 
                            log(AD[i].Gd->GetBinContent(AD[i].Gd->FindBin((x+0.1*w)))));
            g2[i]->SetPointError(j+100, 0,
                                 AD[i].Gd->GetBinError(AD[i].Gd->FindBin((x+0.1*w)))/AD[i].Gd->GetBinContent(AD[i].Gd->FindBin((x+0.1*w))));
        }




        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        g[i]->SetMarkerStyle(8);
        g[i]->Fit(func[i][0]);
        g[i]->Draw("ap");
        CanvasNo++;


        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        g2[i]->SetMarkerStyle(8);
        g2[i]->Fit(func[i][1]);
        g2[i]->Draw("ap");
        CanvasNo++;


        func[i][2]->SetParameters(func[i][0]->GetParameter(0)-func[i][1]->GetParameter(0), func[i][0]->GetParameter(1)-func[i][1]->GetParameter(1));
        for(int j = 0; j<(7.-3.)/w; j++){
            double x = 3+j*w;
            AD[i].Gd->SetBinContent(AD[i].Gd->FindBin(x+0.1*w),
                                    func[i][2]->Eval(x+0.5*w) * AD[i].Gd->GetBinContent(AD[i].Gd->FindBin(x+0.1*w)));
            AD[i].Gd->SetBinError(AD[i].Gd->FindBin(x+0.1*w),
                                  func[i][2]->Eval(x+0.5*w) * AD[i].Gd->GetBinError(AD[i].Gd->FindBin(x+0.1*w)));
        }*/
        AD[i].GetReweightingFunction();
        AD[i].nGdTailReweight();
        //AD[i].nGdTailReweightbyDYB(AD[0]);
                                    

        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1920,1080);
        gPad->SetLogy(1);
        AD[i].H->SetLineColor(6);
        AD[i].Gd->SetLineColor(2);
        AD[i].Gd->SetName(TString::Format("subD_AD%d",i));
        AD[i].Data->Draw("hist");
        //AD[i].H->Draw("hist same");
        AD[i].Gd->Draw("hist same");
        c[CanvasNo]->BuildLegend();
        cout << AD[i].fGd->GetParameter(1) << endl;
        CanvasNo++;


        AD[i].Extract_nC();
        c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
        AD[i].C->GetXaxis()->SetRangeUser(3.5,6.5);
        AD[i].C->Draw();
        CanvasNo++;
        

        cout << "AD" << i << " nGd tail in nC region = " << AD[i].Gd->Integral(401,580) << " +/- " << sqrt(AD[i].Gd->Integral(401,580)) << endl;
        cout << "AD" << i << " nGd tail in nH region = " << AD[i].Gd->Integral(191,270) << " +/- " << sqrt(AD[i].Gd->Integral(191,270)) << endl;

    }


    EdSpectrum Near("Near",&(AD[1]),4);
    Near.H->SetLineColor(6);
    Near.Gd->SetLineColor(2);
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    //Near.C->Draw();
    gPad->SetLogy(1);
    Near.Data->Draw("hist");
    Near.H->Draw("hist same");
    Near.Gd->Draw("hist same");
    c[CanvasNo]->BuildLegend();
    CanvasNo++;


    Near.TakeRatio(false);
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    Near.Over->Draw();
    CanvasNo++;


    /*TF1* fL = new TF1("fL", "pol0", 3, 4);
    Near.C->Fit(fL,"0","",3,4);
    TF1* fR = new TF1("fR", "pol0", 6, 7);
    Near.C->Fit(fR,"0","",6,7);*/


    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    Near.C->GetXaxis()->SetRangeUser(3.5,6.5);
    TF1* fC = new TF1("fC", nCFitter, nC_LowEdge, 6.5, 3);
    fC->SetParNames("N_{C}","#mu_{C}","#sigma_{C}");
    fC->SetParameters(1e3,4.9,0.2);
    //fC->SetParLimits(2,0,1);
    fC->FixParameter(1,5.1);
    fC->FixParameter(2,0.3);
    //fC->FixParameter(3,(fL->GetParameter(0)+fR->GetParameter(0))/2);
   // Near.C->Fit(fC,"","",nC_LowEdge, nC_HighEdge);
   // Near.C->Fit(fC,"","",nC_LowEdge, nC_HighEdge);
    //Near.C->Draw();


    for(int i = 1; i<5; i++){
        double err = 0;
        cout << AD[i].Name << " : nC = " << AD[i].C->IntegralAndError(401,600,err) << " +/- " << err << endl;
    }


    //Near.nHFit(AD[0].fH->GetParameter(3),AD[0].fH->GetParameter(4));
    //Near.nGdFit();
    //Near.GetReweightingFunction();
    //Near.nGdTailReweight();
    //Near.Extract_nC();


    cout << "nC tail [3.7,4] = " << Near.C->Integral(371,400) << endl;
    AD[3].Gd->SetName("twosteps_corr");
    TFile* Fout = new TFile("./test123.root","recreate");
    //for(int i = 1; i<9; i++) AD[i].Gd->Write();
    /*Near.Data->Write();
    Near.H->Write();
    Near.Gd->Write();
    Near.C->Write();*/
    AD[3].Gd->Write();
    AD[3].C->Rebin(10);
    AD[3].C->GetXaxis()->SetRangeUser(4,6);
    AD[3].C->Write();
    Fout->Close();

    cout << "Near site nC/nH = " << Near.C->Integral(401,580)/(Near.Data->Integral(191,270)-Near.Gd->Integral(191,270)) << endl;
    //cout << "Far site nC/nH = " << AD.at(5).C->Integral(401,580)/(AD.at(5).Data->Integral(191,270)-AD.at(5).Gd->Integral(191,270)) << endl;
    cout << "Near site nC/nGd = " << Near.C->Integral(401,580)/Near.Data->Integral(601,1200) << endl;
    //cout << "Far site nC/nGd = " << AD.at(5).C->Integral(401,580)/AD.at(5).Data->Integral(601,1200) << endl;
    cout << "Near site nH/nGd = " << (Near.Data->Integral(191,270)-Near.Gd->Integral(191,270))/Near.Data->Integral(601,1200) << endl;
    //cout << "Far site nH/nGd = " << (AD.at(5).Data->Integral(191,270)-AD.at(5).Gd->Integral(191,270))/AD.at(5).Data->Integral(601,1200) << endl;


    CanvasNo++;
    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    //AD[3].C->Rebin(10);
    AD[3].C->GetXaxis()->SetRangeUser(4,6);
    AD[3].C->Draw();
    //AD[3].C->Fit(fC,"","",nC_LowEdge, 6.5);

    
    timer->Stop();
    timer->Print();



}

