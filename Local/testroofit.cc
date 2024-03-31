using namespace RooFit;
using namespace std;

// h->GetFunction("fC_Near")->SetBit(TF1::kNotDraw)

void testroofit(){

    //RooMinuit::setVerbose(1);
    //TVirtualFitter::SetMaxIterations(10000000);
    //RooMinimizer::setMaxFunctionCalls(1000000);
    gStyle->SetOptFit(1);
    const double Lowedge = 3.8;
    TFile* Fmc = new TFile("/Users/chengyuchin/Analysis/data/MC/Efficiency_LiJJ_PoAn.root");
    //TFile* Fmc = new TFile("/Users/chengyuchin/Analysis/data/MC/Efficiency_noMOgencap.root");
    //TFile* Fmc = new TFile("/Users/chengyuchin/Analysis/data/MC/Efficiency_FV.root");
    //TFile* Fmc = new TFile("/Users/chengyuchin/Analysis/nC/smearnC.root");
    TH1D* mc = (TH1D*)Fmc->Get("Ed_C_passEpdrdt");
    //mc->Rebin(10);
    //TH1D* mc = (TH1D*)Fmc->Get("hC");
    //mc->Sumw2();
    //TFile* Fmc = new TFile("/Users/chengyuchin/Analysis/data/MC/nCpdf.root");
    //TH1D* mc = (TH1D*)Fmc->Get("nC");
    mc->SetName("MCnC");


    TFile* Fdata = new TFile("./test123.root");
    //TFile* Fdata = new TFile("./nC.root");
    //TFile* Fdata = new TFile("/Users/chengyuchin/Analysis/trashcodes/nC/nC_AD1.root");
    //TH1D* data = (TH1D*)Fdata->Get("sub");
    //TH1D* data = (TH1D*)Fdata->Get("nC_Near");
    TH1D* data = (TH1D*)Fdata->Get("nC_EH1AD2");
    //data->Rebin(10);
    data->GetXaxis()->SetRangeUser(Lowedge,6);
    const double dy = -1*data->GetBinContent(data->GetMinimumBin()) + data->GetBinError(data->GetMinimumBin());
    const double range = 5.8-Lowedge;
    //data->GetXaxis()->SetRangeUser(3.5,6.5);
    //const double dy = 300;
    cout << "dy = " << dy << endl;
    for(int i = 1; i<data->GetNbinsX()+1; i++){
        data->AddBinContent(i,dy);
    }


    RooRealVar x("x","x",Lowedge,5.8);
    //RooRealVar sc("sc","sc",-0.2,-0.6,0.0);
    RooRealVar sc("sc","sc",0,-0.6,0.6);
    RooFormulaVar shift("shift","x-sc",RooArgSet(x,sc));


    RooDataHist rmc("rmc","rmc",RooArgList(x),mc);
    RooDataHist rd("rd","rd",RooArgList(x),data);


    //RooHistPdf f("f","f",x,rmc,0);
    RooHistPdf f("f","f",shift,x,rmc,0);
    cout << "f(x) = " << f.getVal() << endl;
    RooPolynomial pol("pol","pol",x,RooArgList());
    //RooRealVar slope("slope","slope",0,0,1000000);
    //RooPolynomial pol("pol","pol",x,RooArgList(slope));
    RooRealVar Nc("Nc","Nc",1,0,1000000);
    RooRealVar Const("Const","Const",dy,0,1000000);
    Const.setVal(dy*range/0.01);
    //Const.setVal(dy*(range-0.05)/0.01);
    Const.setConstant(kTRUE);
    //RooRealSumPdf model("model","f+pol",RooArgList(f,pol),RooArgList(Nc,Const),true);
    RooAddPdf model("model","f+pol",RooArgList(f,pol),RooArgList(Nc,Const));
    //model.fitTo(rd,AsymptoticError(true));
    //model.fitTo(rd,Minos(true));
    //model.fitTo(rd,SumW2Error(true));
    //model.fitTo(rd,IntegrateBins(1));
    model.chi2FitTo(rd);


    TCanvas* c1 = new TCanvas("c1","c1",1600,900);
    //gPad->SetLogy(1);
    RooPlot* fr = x.frame();
    //rmc.plotOn(fr,MarkerColor(2),LineColor(2),Name("MCnC"));
    rd.plotOn(fr,Name("sub"));
    //rd.plotOn(fr,Name("Near_nC"));
    model.plotOn(fr,Name("fitting_pdf"),DataError(1));
    model.plotOn(fr,Components(pol),LineStyle(7),LineColor(4),Name("pdf_const_term"));
    fr->Draw();


    //auto lg = fr->BuildLegend();
    //lg->DrawClone();


    x.setRange("nCcut",4,5.8);
    //x.setRange("syscut",3.5,4);
    RooAbsReal* fraction = f.createIntegral(x,NormSet(x), Range("nCcut"));
    //RooAbsReal* syserr = f.createIntegral(x, Range("syscut"));
    //RooAbsReal* syserr2 = Const.createIntegral(x, Range("syscut"));
    cout << "Intrgral Fraction = " << fraction->getVal() << endl;
    cout << "Nc in [4,5.8] = " << Nc.getVal() * fraction->getVal() << " +/- " << Nc.getError() * fraction->getVal() << endl; 
    //cout << "systematic est. = " << (syserr->getVal())/0.5 << endl;
    cout << "Nc error " << Nc.getError() << endl;


}


