using namespace RooFit;
using namespace std;



void testroofit2(){

    TFile* Fmc = new TFile("./data/MC/NTUNoEdCut_Plots.root");
    TH1D* mcC = (TH1D*)Fmc->Get("nC");
    mcC->SetName("MCnC");


    TFile* Fdata = new TFile("./Plots/Extract_nC.root");
    TH1D* mcGd = (TH1D*)Fdata->Get("CorrectedMC_nGd_Near");
    mcGd->SetName("MCnGd");
    TH1D* data = (TH1D*)Fdata->Get("Data_Near");
    const double dy = -1*round(data->GetBinContent(data->GetMinimumBin())) + 100;
    cout << "dy = " << dy << endl;
    /*for(int i = 1; i<data->GetNbinsX()+1; i++){
        data->AddBinContent(i,dy);
    }*/


    RooRealVar x("x","x",4,6);
    RooRealVar sC("sC","sC",0.2,-1.0,1.0);
    RooRealVar sGd("sGd","sGd",0.1,-0.5,1.0);
    RooFormulaVar shift("shift","x-sC",RooArgSet(x,sC));
    RooFormulaVar shift2("shift2","x-sGd",RooArgSet(x,sGd));


    RooDataHist rmcC("rmcC","rmcC",RooArgList(x),mcC);
    RooDataHist rmcGd("rmcGd","rmcGd",RooArgList(x),mcGd);
    RooDataHist rd("rd","rd",RooArgList(x),data);


    RooHistPdf fC("fC","fC",x,rmcC,0);
    RooHistPdf fGd("fGd","fGd",x,rmcGd,0);
    RooRealVar Nc("Nc","Nc",1,0,1000000);
    RooRealVar NGd("NGd","NGd",1,0,100000000);
    RooAddPdf model("model","fC+fGd",RooArgList(fC,fGd),RooArgList(Nc,NGd));
    model.fitTo(rd);
    

    TCanvas* c1 = new TCanvas("c1","c1",1600,900);
    gPad->SetLogy(1);
    RooPlot* fr = x.frame();
    //rmc.plotOn(fr,MarkerColor(2),LineColor(2));
    rd.plotOn(fr);
    model.plotOn(fr);
    model.plotOn(fr,Components(fGd),LineStyle(7),LineColor(4));
    model.plotOn(fr,Components(fC),LineStyle(7),LineColor(2));
    fr->Draw();
    c1->BuildLegend();


}


