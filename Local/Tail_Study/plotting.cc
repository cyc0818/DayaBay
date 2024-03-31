// /Users/chengyuchin/Analysis/Plots/Cell_Near.root

struct Plots{
    TH1D* h;
    TH1D* corrMC;
    TH1D* sub;
    TF1* f;
    double s;
    double r;
};




void plotting(){


    TCanvas* c[100];
    int CanvasNo = 0;
    Plots Cell[2][100];  //MC, data
    Plots Big[3][3];
    

    TCanvas* tc = new TCanvas("tc","tc",3200,1800);
    tc->Divide(8,10);
    TCanvas* tc2 = new TCanvas("tc2","tc2",3200,1800);
    tc2->Divide(8,10);
    TF1* f[2] = {new TF1("f1","pol0",3,4), new TF1("f2","pol0",6,7)};
    TH2D* h = new TH2D("h",";R^{2}(m^{2});z(m)",10,0,4,10,-2,2);
    TH2D* h2 = new TH2D("h2",";R^{2}(m^{2});z(m)",10,0,4,10,-2,2);
    TH1D* nC = new TH1D("nC",";E_{d}(MeV)",1200,0,12);
    double d = 0;
    double sd = 0;
    double avg = 0;
    double savg = 0;


    int k = 1;
    TFile* F = new TFile("/Users/chengyuchin/Analysis/Plots/Cell_Near_new.root");
    for(int b = 9; b>-1; b--){
        for(int a = 0; a<8; a++){
            d = 0;
            F->cd();
            Cell[1][10*a+b].h = (TH1D*)F->Get(TString::Format("Near_region%d%d",a,b));
            Cell[1][10*a+b].corrMC = (TH1D*)F->Get(TString::Format("CorrMC_region%d%d",a,b));
            Cell[1][10*a+b].sub = (TH1D*)F->Get(TString::Format("sub_region%d%d",a,b));
            Cell[1][10*a+b].sub->GetXaxis()->SetRangeUser(2.9,7);


            tc->cd(k);
            gPad->SetLogy(1);
            Cell[1][10*a+b].h->Draw();
            Cell[1][10*a+b].corrMC->Draw("same");
            tc2->cd(k);
            Cell[1][10*a+b].sub->Fit(f[0],"Q","",3.2,4);
            Cell[1][10*a+b].sub->Fit(f[1],"Q+","",6,7);
            Cell[1][10*a+b].sub->DrawCopy();
            //d = sqrt(f[0]->GetParameter(0)*f[0]->GetParameter(0)+f[1]->GetParameter(0)*f[1]->GetParameter(0));
            d = f[1]->GetParameter(0)-f[0]->GetParameter(0);
            sd = sqrt(f[1]->GetParError(0)*f[1]->GetParError(0)+f[0]->GetParError(0)*f[0]->GetParError(0));
            avg = (f[0]->GetParameter(0)+f[1]->GetParameter(0))/2;
            savg = sd/2;
            cout << "Cell = " << a << b << " , L = " << f[0]->GetParError(0) << " , R = " << f[1]->GetParError(0) << " , d = " << d;
            cout << " , error = " << sd << endl;
            k++;


            /*c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
            gPad->SetLogy(1);
            Cell[1][10*a+b].corrMC->SetLineColor(2);
            Cell[1][10*a+b].h->Draw();
            Cell[1][10*a+b].corrMC->Draw("same");
            CanvasNo++;*/


            /*c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
            Cell[1][10*a+b].sub->DrawCopy();
            CanvasNo++;*/


            h->SetBinContent(h->GetBin(a+1,b+1),round(1000*d)/1000);
            h->SetBinError(h->GetBin(a+1,b+1),round(1000*sd)/1000);
            h2->SetBinContent(h2->GetBin(a+1,b+1),round(1000*avg)/1000);
            h2->SetBinError(h2->GetBin(a+1,b+1),round(1000*savg)/1000);


            if (d<2) nC->Add(Cell[1][10*a+b].sub);


        }
    }


    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    h->Draw("colz");
    h->Draw("text e same");
    CanvasNo++;

    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    h2->Draw("colz");
    h2->Draw("text e same");
    CanvasNo++;

    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    nC->GetXaxis()->SetRangeUser(3.5,6.5);
    nC->Draw();
    CanvasNo++;


    c[CanvasNo] = new TCanvas(TString::Format("c%d",CanvasNo),TString::Format("c%d",CanvasNo),1600,900);
    Cell[1][18].sub->Draw();


}

