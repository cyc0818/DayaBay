void test(){

    double x[2] = {1,10};
    double y[2] = {1,3};
    TGraph* g = new TGraph(2,x,y);
    TGraph* g2 = new TGraph();
    const double dx = (10.-1.)/100.;
    const double dy = (3.-1.)/100.;
    for(int i = 0; i<101; i++){
        g2->SetPoint(i,1.+i*dx,1.+i*dy);
    }
    new TCanvas;
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    g->SetMarkerStyle(8);
    g2->SetLineColor(2);
    g2->SetMarkerColor(2);
    g->Draw("ALP");
    g2->Draw("LP");


}
