#include "UserSetting.h"
#include "Fitter.h"
#include "TH1functions.h"



using namespace std;



struct Plots{
    TH1D* h;
    TH1D* corrMC;
    TH1D* sub;
    TF1* f;
    double s;
    double r;
    int FitSta;
};



void nGdTailCompare(){

    //Plots AD[9][100];
    //Plots Site[2][100];
    TCanvas* c[200];
    Plots Cell[2][100];  //MC, AD
    Plots Big[3][3];
    const int AD = 4;
    int CanvasNo = 0;
    vector<int> Fail;
    Fail.push_back(-500);


    if(OnlyCheckFittingPerf) gStyle->SetOptFit(1);


    for(int a = 0; a<8; a++){
        for(int b = 0; b<10; b++){
            Cell[0][10*a+b].h = new TH1D(TString::Format("MC_region%d%d",a,b), TString::Format("MC_region%d%d;E_{d}(MeV)",a,b), 1200, 0, 12);
            Cell[1][10*a+b].h = new TH1D(TString::Format("Near_region%d%d",a,b), TString::Format("Near_region%d%d;E_{d}(MeV)",a,b), 1200, 0, 12);
            Cell[1][10*a+b].corrMC = new TH1D(TString::Format("cor_region%d%d",a,b), TString::Format("cor_region%d%d;E_{d}(MeV)",a,b), 1200, 0, 12);
            Cell[1][10*a+b].sub = new TH1D(TString::Format("sub_region%d%d",a,b), TString::Format("sub_region%d%d;E_{d}(MeV)",a,b), 1200, 0, 12);
        }
    }


    TFile* F = new TFile("/Users/chengyuchin/Analysis/data/MC/MCCell_new.root");
    for(int a = 0; a<8; a++){
        for(int b = 0; b<10; b++){
            Cell[0][10*a+b].h->Add((TH1D*)F->Get(TString::Format("Cell%d/nGdOthers_Cell%d", 10*a+b, 10*a+b)));
        }
    }
    F->Close();


    F = TFile::Open("/Users/chengyuchin/Analysis/P17B_CellPlots_postsubnew.root");
    for(int a = 0; a<8; a++){
        for(int b = 0; b<10; b++){
            Cell[1][10*a+b].h->Add((TH1D*)F->Get(TString::Format("Cell%d/AD%d_Cell%d", 10*a+b, AD, 10*a+b)));
        }
    }
    F->Close();


    for(int a = 0; a<8; a++){
        for(int b = 0; b<10; b++){

            // fit MC
            Cell[0][10*a+b].f = new TF1(TString::Format("fMC%d%d",a,b), nGdFitter, 6, 9.2, 5);
            Cell[0][10*a+b].f->SetParNames("N_{Gd}", "#mu_{Gd}", "#sigma_{Gd}", "#alpha_{Gd}", "n_{Gd}");
            Cell[0][10*a+b].f->SetParameters(Cell[0][10*a+b].h->Integral(600,920), 8.089, 0.309, 1.7, 0.78);
            Cell[0][10*a+b].f->SetParLimits(3, 0, 3);
            Cell[0][10*a+b].f->SetParLimits(4, 0, 2);
            cout << "----------------Fitting MC Cell" << a << b << "-------------------" << endl;
            if(OnlyCheckFittingPerf){
                c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
                gPad->SetLogy(1);
                Cell[0][10*a+b].h->Fit(Cell[0][10*a+b].f,"L","",6,9.2);
                Cell[0][10*a+b].FitSta = Cell[0][10*a+b].h->Fit(Cell[0][10*a+b].f,"L","",6,9.2);
                cout <<"---------------------- status = " << Cell[0][10*a+b].FitSta << endl;
                if(Cell[0][10*a+b].FitSta != 0) Cell[0][10*a+b].h->Draw("HIST");
                CanvasNo++;
            }
            else{
                Cell[0][10*a+b].h->Fit(Cell[0][10*a+b].f,"L0","",6,9.2);
                Cell[0][10*a+b].FitSta = Cell[0][10*a+b].h->Fit(Cell[0][10*a+b].f,"L0","",6,9.2);
                if(Cell[0][10*a+b].FitSta != 0 && Fail.back() != (10*a+b)){
                    Fail.push_back(10*a+b);
                    continue;
                }
            }


            // fit data
            Cell[1][10*a+b].f = new TF1(TString::Format("f%d%d",a,b), nGdFitter, 6, 9.2, 5);
            Cell[1][10*a+b].f->SetParNames("N_{Gd}", "#mu_{Gd}", "#sigma_{Gd}", "#alpha_{Gd}", "n_{Gd}");
            Cell[1][10*a+b].f->SetParameters(Cell[1][10*a+b].h->Integral(600,920), 8.089, 0.309, 2, 1);
            Cell[1][10*a+b].f->SetParLimits(0, 0, 2*Cell[1][10*a+b].h->Integral(600,920));
            Cell[1][10*a+b].f->SetParLimits(2, 0, 0.7);
            Cell[1][10*a+b].f->SetParLimits(3, 0, 4.5);
            Cell[1][10*a+b].f->SetParLimits(4, 0, 3);
            cout << "----------------Fitting AD" << AD <<" Cell" << a << b << "-------------------" << endl;
            if(OnlyCheckFittingPerf){
                c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
                gPad->SetLogy(1);
                Cell[1][10*a+b].h->Fit(Cell[1][10*a+b].f,"L","",6,9.2);
                Cell[1][10*a+b].FitSta = Cell[1][10*a+b].h->Fit(Cell[1][10*a+b].f,"L","",6,9.2);
                cout <<"---------------------- status = " << Cell[1][10*a+b].FitSta << endl;
                if(Cell[1][10*a+b].FitSta != 0) Cell[1][10*a+b].h->Draw("HIST");
                CanvasNo++;
            }
            else{
                Cell[1][10*a+b].h->Fit(Cell[1][10*a+b].f,"L0","",6,9.2);
                Cell[1][10*a+b].FitSta = Cell[1][10*a+b].h->Fit(Cell[1][10*a+b].f,"L0","",6,9.2);
                if(Cell[1][10*a+b].FitSta != 0 && Fail.back() != (10*a+b)){
                    Fail.push_back(10*a+b);
                    continue;
                }


                // get r,s
                Cell[1][10*a+b].r = Cell[1][10*a+b].f->GetParameter(0) / Cell[0][10*a+b].f->GetParameter(0);
                Cell[1][10*a+b].s = Cell[1][10*a+b].f->GetParameter(1) - Cell[0][10*a+b].f->GetParameter(1);


                // Correct MC
                *(Cell[1][10*a+b].corrMC) = Translation(*(Cell[0][10*a+b].h),
                                                        (int)round(Cell[1][10*a+b].s/Cell[0][10*a+b].h->GetXaxis()->GetBinWidth(1)));
                Cell[1][10*a+b].corrMC->Scale(Cell[1][10*a+b].r);
                Cell[1][10*a+b].corrMC->SetNameTitle(TString::Format("CorrMC_region%d%d",a,b), TString::Format("CorrMC_region%d%d;E_{d}(MeV)",a,b));


                // subtraction
                Cell[1][10*a+b].sub->Add(Cell[1][10*a+b].h, Cell[1][10*a+b].corrMC, 1, -1);


                // plotting
                c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
                gPad->SetLogy(1);
                Cell[1][10*a+b].corrMC->SetLineColor(2);
                Cell[1][10*a+b].h->Draw();
                Cell[1][10*a+b].corrMC->Draw("same");
                c[CanvasNo]->BuildLegend();
                CanvasNo++;
                c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
                Cell[1][10*a+b].sub->Draw();
                CanvasNo++;
            }
        }
    }


    if(OnlyCheckFittingPerf) return 0;


    // merge 4 cells into 1
    /*for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            Big[i][j].h = new TH1D(TString::Format("Near_merge%d%d",i,j), TString::Format("Near_merge%d%d;E_{d}(MeV)",i,j), 1200, 0, 12);
            Big[i][j].corrMC = new TH1D(TString::Format("CorrMC_merge%d%d",i,j), TString::Format("CorrMC_merge%d%d;E_{d}(MeV)",i,j), 1200, 0, 12);
            Big[i][j].sub = new TH1D(TString::Format("sub_merge%d%d",i,j), TString::Format("sub_merge%d%d;E_{d}(MeV)",i,j), 1200, 0, 12);
        }
    } 


    int p = 100;
    int q = 100;
    for(int a = 0; a<6; a++){
        for(int b = 2; b<8; b++){
            p = a/2;
            q = (b-2)/2;


            Big[p][q].h->Add(Cell[1][10*a+b].h);
            Big[p][q].corrMC->Add(Cell[1][10*a+b].corrMC);
            Big[p][q].sub->Add(Cell[1][10*a+b].sub);
        }
    }


    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
            gPad->SetLogy(1);
            Big[i][j].corrMC->SetLineColor(2);
            Big[i][j].h->Draw();
            Big[i][j].corrMC->Draw("same");
            c[CanvasNo]->BuildLegend();
            CanvasNo++;
            c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
            Big[i][j].sub->Draw();
            CanvasNo++;
        }
    }*/


    for(int i = 0; i<Fail.size(); i++){
        cout << Fail[i] << endl;
    }
    //TH1D* hfail[2] = new TH1D("hfail","hfail",1200,0,12);


    if(TFile_output){
        TFile* Fout = new TFile(TString::Format("/Users/chengyuchin/Analysis/Plots/Cell_AD%d.root",AD),"recreate");

        for(int a = 0; a<8; a++){
            for(int b = 0; b<10; b++){
                Cell[1][10*a+b].h->Write();
                Cell[1][10*a+b].corrMC->Write();
                Cell[1][10*a+b].sub->Write();
            }
        }


        /*for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                Big[i][j].h->Write();
                Big[i][j].corrMC->Write();
                Big[i][j].sub->Write();
            }
        }*/

        Fout->Close();

    }


}








