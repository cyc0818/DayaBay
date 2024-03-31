void nGdnHRatio(){

    TH1D* AD[6][100];       // MC, AD1-4, Near site


    double nGd[6][100];
    double errGd[6][100];
    double nH[6][100];
    double errH[6][100];
    double nt[6][100];
    double errt[6][100];
    double R[6][100];
    double errR[6][100];


    TH2D* MC[2] = {new TH2D("MC nGd/(nH+nGd)",";R^{2}(m^{2});z(m)",10,0,4,10,-2,2),
                   new TH2D("MC nGd/(nH+nGd) (normalized)",";R^{2}(m^{2});z(m)",10,0,4,10,-2,2)};
    TH2D* Near[2] = {new TH2D("Near nGd/(nH+nGd)",";R^{2}(m^{2});z(m)",10,0,4,10,-2,2),
                   new TH2D("Near nGd/(nH+nGd) (normalized)",";R^{2}(m^{2});z(m)",10,0,4,10,-2,2)};
    TH2D* Compare = new TH2D("Data/MC",";R^{2}(m^{2});z(m);nGd/(nH+nGd)",10,0,4,10,-2,2);
    TH1D* all = new TH1D("all","all",1200,0,12);
    TH1D* allMC = new TH1D("allMC","allMC",1200,0,12);


    TF1* error_AoverB = new TF1("error_AoverB","([0]/[1])*sqrt(([2]/[0])^2+([3]/[1])^2)",0,0);    // Parameters(A,B,sigmaA,sigmaB)


    TFile* F1 = new TFile("/Users/chengyuchin/Analysis/data/MC/MCCell.root");
    for(int a = 0; a<10; a++){
        for(int b = 0; b<10; b++){
            AD[0][10*a+b] = (TH1D*)F1->Get(TString::Format("Cell%d/EdSpectrum_Cell%d", 10*a+b, 10*a+b));
            AD[5][10*a+b] = new TH1D(TString::Format("Near_region%d%d",a,b), TString::Format("Near_region%d%d;E_{d}(MeV)",a,b), 1200, 0, 12);
            allMC->Add(AD[0][10*a+b]);
        }
    }


    TFile* F2 = new TFile("/Users/chengyuchin/Analysis/P17B_CellPlots.root");
    for(int ADNo = 1; ADNo<5; ADNo++){
        for(int a = 0; a<10; a++){
            for(int b = 0; b<10; b++){
                AD[ADNo][10*a+b] = (TH1D*)F2->Get(TString::Format("Cell%d/AD%d_Cell%d", 10*a+b, ADNo, 10*a+b));
                AD[5][10*a+b]->Add(AD[ADNo][10*a+b]);
                if(ADNo == 1) all->Add(AD[ADNo][10*a+b]);
            }
        }
    }


    for(int ADNo = 0; ADNo<6; ADNo++){
        for(int a = 0; a<10; a++){
            for(int b = 0; b<10; b++){
                nGd[ADNo][10*a+b] = AD[ADNo][10*a+b]->IntegralAndError(600, 1200, errGd[ADNo][10*a+b]);
                nH[ADNo][10*a+b] = AD[ADNo][10*a+b]->IntegralAndError(190, 270, errH[ADNo][10*a+b]);


                nt[ADNo][10*a+b] = nGd[ADNo][10*a+b] + nH[ADNo][10*a+b];
                errt[ADNo][10*a+b] = sqrt(errGd[ADNo][10*a+b]*errGd[ADNo][10*a+b] + errH[ADNo][10*a+b]*errH[ADNo][10*a+b]);


                R[ADNo][10*a+b] = nGd[ADNo][10*a+b] / nt[ADNo][10*a+b];
                error_AoverB->SetParameters(nGd[ADNo][10*a+b], nt[ADNo][10*a+b], errGd[ADNo][10*a+b], errt[ADNo][10*a+b]);
                errR[ADNo][10*a+b] = error_AoverB->Eval(0);
                if(ADNo == 0) cout << "MC Cell = " << a << b << " , R(%) = " << 100*R[ADNo][10*a+b] << " +/- " << 100*errR[ADNo][10*a+b] << endl;
                if(ADNo == 5) cout << "Near site Cell = " << a << b << " , R(%) = " << 100*R[ADNo][10*a+b] << " +/- " << 100*errR[ADNo][10*a+b] << endl;
            }
        }
    }


    for(int a = 0; a<10; a++){
        for(int b = 0; b<10; b++){
            MC[0]->SetBinContent(Compare->GetBin(a+1,b+1),round(1000*R[0][10*a+b])/1000);
            MC[0]->SetBinError(Compare->GetBin(a+1,b+1),round(1000*errR[0][10*a+b])/1000);
            MC[1]->SetBinContent(Compare->GetBin(a+1,b+1),round(1000*(R[0][10*a+b]/R[0][5]))/1000);
            error_AoverB->SetParameters(R[0][10*a+b],R[0][5],errR[0][10*a+b],errR[0][5]);
            MC[1]->SetBinError(Compare->GetBin(a+1,b+1),round(1000*error_AoverB->Eval(0))/1000);


            Near[0]->SetBinContent(Compare->GetBin(a+1,b+1),round(1000*R[5][10*a+b])/1000);
            Near[0]->SetBinError(Compare->GetBin(a+1,b+1),round(1000*errR[5][10*a+b])/1000);
            Near[1]->SetBinContent(Compare->GetBin(a+1,b+1),round(1000*(R[5][10*a+b]/R[5][5]))/1000);
            error_AoverB->SetParameters(R[5][10*a+b],R[5][5],errR[5][10*a+b],errR[5][5]);
            Near[1]->SetBinError(Compare->GetBin(a+1,b+1),round(1000*error_AoverB->Eval(0))/1000);


            error_AoverB->SetParameters(R[5][10*a+b],R[0][10*a+b],errR[5][10*a+b],errR[0][10*a+b]);
            cout << "Near/MC Cell = " << a << b << " R(%) = " << 100*R[5][10*a+b]/R[0][10*a+b] << " +/- " << 100*error_AoverB->Eval(0) << endl;
            Compare->SetBinContent(Compare->GetBin(a+1,b+1),round(1000*R[5][10*a+b]/R[0][10*a+b])/1000);
            Compare->SetBinError(Compare->GetBin(a+1,b+1),round(1000*error_AoverB->Eval(0))/1000);


            /*error_AoverB->SetParameters(R[2][10*a+b],R[0][10*a+b],errR[2][10*a+b],errR[0][10*a+b]);
            cout << "Near/MC Cell = " << a << b << " R(%) = " << 100*R[2][10*a+b]/R[0][10*a+b] << " +/- " << 100*error_AoverB->Eval(0) << endl;
            Compare->SetBinContent(Compare->GetBin(a+1,b+1),round(1000*R[2][10*a+b]/R[0][10*a+b])/1000);
            Compare->SetBinError(Compare->GetBin(a+1,b+1),round(1000*error_AoverB->Eval(0))/1000);*/
        }
    }


    TCanvas* c1[2] = {new TCanvas("c10","c10",3200,1800), new TCanvas("c11","c11",3200,1800)};
    for(int i = 0; i<2; i++){
        c1[i]->Divide(2,1);
        c1[i]->cd(1);
        MC[i]->Draw("colz");
        MC[i]->Draw("text e same");


        c1[i]->cd(2);
        Near[i]->Draw("colz");
        Near[i]->Draw("text e same");
    }


    TCanvas* c2 = new TCanvas("c2","c2",1600,900);
    Compare->Draw("colz");
    Compare->Draw("text e same");


    double H = all->Integral(190,270);
    double Gd = all->Integral(600,1000);
    cout << "data : " << H/Gd << endl;
    H = allMC->Integral(190,270);
    Gd = allMC->Integral(600,1000);
    cout << "MC : " << H/Gd << endl;

    TFile* F3 = new TFile("/Users/chengyuchin/Analysis/data/MC/MC4m.root");
    TH1D* test = (TH1D*)F3->Get("EdSpectrum");
    H = test->Integral(190,270);
    Gd = test->Integral(600,1000);
    cout << "MC nH = " << H << endl;
    cout << "MC nGd = " << Gd << endl;
    cout << "MC ratio = " << H/Gd << endl;


    TH1D* h50 = new TH1D("h50","",1200,0,12);
    new TCanvas;
    test->SetLineColor(2);
    test->SetMarkerColor(2);
    allMC->Draw();
    test->Draw("same");
    h50->Add(allMC,test,1,-1);
    new TCanvas;
    //gPad->SetLogy(1);
    h50->Draw("hist");



}

