void fitter(int& npar, double* gin, double& f, double* par, int iflag){

    const double x = par[0];
    const double y = par[1];
    f = (x-3)*(x-3)+(y-5)*(y-5);

}



void test(){

    TMinuit* minimizer = new TMinuit(2);
    minimizer->SetFCN(fitter);
    minimizer->DefineParameter(0, "x", 9, 0.01, -5, 10);
    minimizer->DefineParameter(1, "y", 9, 0.01, -5, 10);
    minimizer->FixParameter(0);
    minimizer->Command("MIGRAD");
    minimizer->Command("MIGRAD");
    minimizer->Command("MINOS");


    double x, x_err, y, y_err;
    minimizer->GetParameter(0,x,x_err);
    minimizer->GetParameter(1,y,y_err);


    cout << "x = " << x << " +/- " << x_err << endl;
    cout << "y = " << y << " +/- " << y_err << endl;


}

