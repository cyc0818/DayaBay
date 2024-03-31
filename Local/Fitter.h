#ifndef Fitter_h
#define Fitter_h

#include <math.h>



// unspecialized function
double GausShape(double* x, double* par){

    double mu  = par[0];
    double sigma = par[1];


    double shape = 0;
    shape = (1./sigma/sqrt(2.*TMath::Pi())) * exp((-1./2.)*pow((x[0]-mu)/sigma,2));

    return shape;

}




double CBShape(double* x, double* par){

    double mean  = par[0];
    double sigma = par[1];
    double a     = par[2];
    double n     = par[3];


    double e = x[0];
    a = abs(a);

    double shape = 0;
    if( (e-mean)/sigma > -a )  {
        shape = exp( - 1/2.0*pow((e-mean)/sigma,2) );
    } else {
        shape = pow(n/a,n)*exp(-1/2.0*a*a) / pow(n/a-a-(e-mean)/sigma,n);
    }

    return shape;

}




double dCBShape(double* x, double* par){

    double scale  = (60700*0.1480 + 254000*0.1565)/(60700*0.1480*8.5364 + 254000*0.1565*7.9374);
    double Cn     = (60700*0.1480)/(254000.*0.1565);


    // Gd157
    double mean1  = par[0] * scale * 7.9374;
    double sigma1 = par[1];
    // Gd155
    double mean2  = par[0] * scale * 8.5364;
    double sigma2 = sigma1 * sqrt(8.5364/7.9374);


    double alpha  = par[2];
    double n      = par[3];

    double A = TMath::Power(n/TMath::Abs(alpha),n)*TMath::Exp(-alpha*alpha/2.);
    double B = n/TMath::Abs(alpha) - TMath::Abs(alpha);

    double shape1 = 0.0;
    double tmp1 = (x[0]-mean1)/sigma1;
    if(tmp1>-alpha) {
        shape1 = TMath::Exp(-tmp1*tmp1/2.);
    }
    else {
        shape1 = A * TMath::Power(B-tmp1, -n);
    }
    double shape2 = 0.0;
    double tmp2 = (x[0]-mean2)/sigma2;
    if(tmp2>-alpha) {
        shape2 = Cn * TMath::Exp(-tmp2*tmp2/2.);
    }
    else {
        shape2 = Cn * A * TMath::Power(B-tmp2, -n);
    }
    return (shape1 + shape2);

}



double OldDYBShape(double* x, double* par){    // single exp tail

    double mu = par[0];
    double sigma = par[1];
    double lambda = par[2];
    double alpha = par[3];




    double peak = (1./sigma/sqrt(2.*TMath::Pi())) * exp((-1./2.)*pow((x[0]-mu)/sigma,2));
    double tail1 = (lambda/2.) * exp(pow(sigma*lambda,2)/2.) * exp(lambda*x[0])
        * (erf((mu-x[0]-sigma*sigma*lambda)/sqrt(2.)/sigma) - erf((-x[0]-sigma*sigma*lambda)/sqrt(2.)/sigma))
        / (exp(lambda*mu)-1.);



    return alpha*peak + (1-alpha)*tail1;


}





double OldDYBShape2(double* x, double* par){    // double exp tail

    double mu = par[0];
    double sigma = par[1];
    double lambda1 = par[2];
    double lambda2 = par[3];
    double alpha = par[4];
    double Beta = par[5];




    double peak = (1./sigma/sqrt(2.*TMath::Pi())) * exp((-1./2.)*pow((x[0]-mu)/sigma,2));
    double tail1 = (lambda1/2.) * exp(pow(sigma*lambda1,2)/2.) * exp(lambda1*x[0])
        * (erf((mu-x[0]-sigma*sigma*lambda1)/sqrt(2.)/sigma) - erf((-x[0]-sigma*sigma*lambda1)/sqrt(2.)/sigma))
        / (exp(lambda1*mu)-1.);
    double tail2 = (lambda2/2.) * exp(pow(sigma*lambda2,2)/2.) * exp(lambda2*x[0])
        * (erf((mu-x[0]-sigma*sigma*lambda2)/sqrt(2.)/sigma) - erf((-x[0]-sigma*sigma*lambda2)/sqrt(2.)/sigma))
        / (exp(lambda2*mu)-1.);



    return alpha*peak + (1-alpha)*Beta*tail1 + (1-alpha)*(1-Beta)*tail2;


}





double OldDYBFunc(double* x, double* par){    // single exp tail

    double N = par[0];
    double mu = par[1];
    double sigma = par[2];
    double lambda = par[3];
    double alpha = par[4];


    double peak = (1./sigma/sqrt(2.*TMath::Pi())) * exp((-1./2.)*pow((x[0]-mu)/sigma,2));
    double tail1 = (lambda/2.) * exp(pow(sigma*lambda,2)/2.) * exp(lambda*x[0])
        * (erf((mu-x[0]-sigma*sigma*lambda)/sqrt(2.)/sigma) - erf((-x[0]-sigma*sigma*lambda)/sqrt(2.)/sigma))
        / (exp(lambda*mu)-1.);



    return N*(alpha*peak + (1-alpha)*tail1);


}





double OldDYBFunc2(double* x, double* par){    // double exp tail

    double N = par[0];
    double mu = par[1];
    double sigma = par[2];
    double lambda1 = par[3];
    double lambda2 = par[4];
    double alpha = par[5];
    double Beta = par[6];


    double peak = (1./sigma/sqrt(2.*TMath::Pi())) * exp((-1./2.)*pow((x[0]-mu)/sigma,2));
    double tail1 = (lambda1/2.) * exp(pow(sigma*lambda1,2)/2.) * exp(lambda1*x[0])
        * (erf((mu-x[0]-sigma*sigma*lambda1)/sqrt(2.)/sigma) - erf((-x[0]-sigma*sigma*lambda1)/sqrt(2.)/sigma))
        / (exp(lambda1*mu)-1.);
    double tail2 = (lambda2/2.) * exp(pow(sigma*lambda2,2)/2.) * exp(lambda2*x[0])
        * (erf((mu-x[0]-sigma*sigma*lambda2)/sqrt(2.)/sigma) - erf((-x[0]-sigma*sigma*lambda2)/sqrt(2.)/sigma))
        / (exp(lambda2*mu)-1.);



    return N*(alpha*peak + (1-alpha)*Beta*tail1 + (1-alpha)*(1-Beta)*tail2);


}






double CBFunction(double* x, double* par){

    double N     = par[0];
    double mean  = par[1];
    double sigma = par[2];
    double a     = par[3];
    double n     = par[4];


    double e = x[0];
    a = abs(a);

    double shape = 0;
    if( (e-mean)/sigma > -a )  {
        shape = exp( - 1/2.0*pow((e-mean)/sigma,2) );
    } else {
        shape = pow(n/a,n)*exp(-1/2.0*a*a) / pow(n/a-a-(e-mean)/sigma,n);
    }

    return N*shape;

}






double DYBSpectrum(double* x, double *par){     //nC is CB

    double NC = par[0];
    double muC = par[1];
    double sigmaC = par[2];
    double alphaC = par[3];
    double nC = par[4];
    double NGd = par[5];
    double N2 = par[6];
    double alphaGd = par[7];
    double nGd = par[8];
    double muGd = par[9];
    double sigmaGd = par[10];
    double Slope = par[11];
    double NH = par[12];
    double muH = par[13];
    double sigmaH = par[14];
    double alphaH = par[15];
    double nH = par[16];


    TF1* fC = new TF1("fC",CBShape,1.9,9.5,5);
    fC->SetParameters(muC,sigmaC,alphaC,nC);


    TF1* fGd = new TF1("fGd",dCBShape,1.9,9.5,7);
    fGd->SetParameters(muGd,sigmaGd,alphaGd,nGd);


    TF1* fH = new TF1("fH",CBShape,1.9,9.5,5);
    fH->SetParameters(muH,sigmaH,alphaH,nH);


    return NC*fC->Eval(x[0]) + NGd*fGd->Eval(x[0]) + NH*fH->Eval(x[0]);




}





double GapExp(double* x, double* par){

    double N = par[0];
    double x0 = par[1];
    double gap = par[2];


    return x[0]>=gap ? (N/x0)*exp(-(x[0]-gap)/x0) : 0;



}






double ExpRiseDecay(double* x, double* par){

    double N = par[0];
    double alpha = par[1];
    double tau_rise = par[2];
    double tau_decay = par[3];


    double rise_term = (N*alpha/tau_rise)*exp(-x[0]/tau_rise);  
    double decay_term = (N*(1+alpha)/tau_decay)*exp(-x[0]/tau_decay);


    return decay_term - rise_term;



}





// specialized fitter (normalized in fitting range)
const double binWidth = (12.0-0.0)/1200.0;



double nHFitter(double* x, double* par){

    double N  = par[0]*binWidth;
    double mean  = par[1];
    double sigma = par[2];
    double a     = par[3];
    double n     = par[4];

    unique_ptr<TF1> CBf(new TF1("CBf",CBShape,1.9,2.7,4));
    CBf->SetParameters(mean,sigma,a,n);

    double normal = CBf->Integral(1.9,2.7);

    return N*CBShape(x,&par[1])/(normal*1.0);

}




double nHFitter2(double* x, double* par){

    double N  = par[0];
    double mean  = par[1];
    double sigma = par[2];
    double lambda = par[3];
    double alpha  = par[4];


    unique_ptr<TF1> DYBf(new TF1("DYBf",OldDYBShape,0,12,4));
    DYBf->SetParameters(mean,sigma,lambda,alpha);


    return N*DYBf->Eval(x[0]);

}





double MCnHFitter(double* x, double* par){      // only for getting tail usage, normalized in (1.9,2.7)

    double N  = par[0]*binWidth;
    double mean  = par[1];
    double sigma = par[2];
    double a     = par[3];
    double n     = par[4];

    unique_ptr<TF1> CBf(new TF1("CBf",CBShape,MCnH_LowEdge,2.7,4));
    CBf->SetParameters(mean,sigma,a,n);

    double normal = CBf->Integral(1.9,2.7);

    return N*CBShape(x,&par[1])/(normal*1.0);

}




double nGdFitter(double* x, double* par){

    double N     = par[0]*binWidth;
    double mean   = par[1];
    double sigma  = par[2];
    double a      = par[3];
    double n      = par[4];

    unique_ptr<TF1> dCBf(new TF1("dCBf",dCBShape,6,9.2,4));
    dCBf->SetParameters(mean,sigma,a,n);

    double normal = dCBf->Integral(6,9.2);

    return N*dCBShape(x,&par[1])/(normal*1.0);

}





double nGdFitter2(double* x, double* par){

    // Gd157 : Gaussian + single exp. tail
    double N_157  = par[0];
    double mean_157  = par[1];
    double sigma_157 = par[2];
    double lambda_157 = par[3];
    double alpha_157  = par[4];

    // Gd155 : Gaussian + single exp. tail
    double N_155  = par[5];
    double mean_155  = par[6];
    double sigma_155 = par[7];
    double lambda_155 = par[8];
    double alpha_155  = par[9];

    unique_ptr<TF1> DYB157(new TF1("DYB157",OldDYBShape,1.5,12,4));
    DYB157->SetParameters(mean_157,sigma_157,lambda_157,alpha_157);
    unique_ptr<TF1> DYB155(new TF1("DYB155",OldDYBShape,1.5,12,4));
    DYB155->SetParameters(mean_155,sigma_155,lambda_155,alpha_155);


    return N_157*DYB157->Eval(x[0]) + N_155*DYB155->Eval(x[0]);

}






double nGdFitter3(double* x, double* par){

    // Gd157 : Gaussian + double exp. tail
    double N_157  = par[0];
    double mean_157  = par[1];
    double sigma_157 = par[2];
    double lambda1_157 = par[3];
    double lambda2_157 = par[4];
    double alpha_157  = par[5];
    double Beta_157 = par[6];

    // Gd155 : Gaussian
    double N_155  = par[7];
    double mean_155  = par[8];
    double sigma_155 = par[9];

    unique_ptr<TF1> DYB157(new TF1("DYB157",OldDYBShape2,1.5,12,6));
    DYB157->SetParameters(mean_157,sigma_157,lambda1_157,lambda2_157,alpha_157,Beta_157);
    unique_ptr<TF1> DYB155(new TF1("DYB155",GausShape,1.5,12,2));
    DYB155->SetParameters(mean_155,sigma_155);


    return N_157*DYB157->Eval(x[0]) + N_155*DYB155->Eval(x[0]);

}





double nCFitter(double* x, double* par){    // Gaussian

    double N     = par[0]*binWidth;
    double mean   = par[1];
    double sigma  = par[2];

    unique_ptr<TF1> Gausf(new TF1("Gausf",GausShape,nC_LowEdge,nC_HighEdge,2));
    Gausf->SetParameters(mean,sigma);

    double normal = Gausf->Integral(nC_LowEdge,nC_HighEdge);

    return N*GausShape(x,&par[1])/(normal*1.0);

}





double nCFitter2(double* x, double* par){   // Crystal ball

    double N  = par[0]*binWidth;
    double mean  = par[1];
    double sigma = par[2];
    double a     = par[3];
    double n     = par[4];

    unique_ptr<TF1> CBf(new TF1("CBf",CBShape,nC_LowEdge,6,4));
    CBf->SetParameters(mean,sigma,a,n);

    double normal = CBf->Integral(nC_LowEdge,6);

    return N*CBShape(x,&par[1])/(normal*1.0);

}





double nCFitter3(double* x, double* par){    // Gaussian + const

    double N     = par[0]*binWidth;
    double mean   = par[1];
    double sigma  = par[2];
    double c = par[3];

    unique_ptr<TF1> Gausf(new TF1("Gausf",GausShape,nC_LowEdge,nC_HighEdge,2));
    Gausf->SetParameters(mean,sigma);

    double normal = Gausf->Integral(nC_LowEdge,nC_HighEdge);

    return N*GausShape(x,&par[1])/(normal*1.0) + c;


}





double MCnCFitter(double* x, double* par){

    double N1     = par[0]*binWidth;
    double mean1   = par[1];
    double sigma1  = par[2];
    double a      = par[3];
    double n      = par[4];
    double N2     = par[5]*binWidth;
    double mean2   = par[6];
    double sigma2  = par[7];


    unique_ptr<TF1> CBf(new TF1("CBf",CBShape,2.5,5.8,4));
    CBf->SetParameters(mean1,sigma1,a,n);
    unique_ptr<TF1> Gausf(new TF1("Gausf",GausShape,2.5,5.8,2));
    Gausf->SetParameters(mean2,sigma2);


    double normal1 = CBf->Integral(2.5,5.8);
    double normal2 = Gausf->Integral(2.5,5.8);


    return N1 * CBf->Eval(x[0])/(normal1*1.0) + N2 * Gausf->Eval(x[0])/(normal2*1.0);



}






double DYBFitter(double* x, double* par){

    // Gd157 : Gaussian + single exp. tail
    double N_157  = par[0];
    double mean_157  = par[1];
    double sigma_157 = par[2];
    double lambda_157 = par[3];
    double alpha_157  = par[4];

    // Gd155 : Gaussian + single exp. tail
    double N_155  = par[5];
    double mean_155  = par[6];
    double sigma_155 = par[7];
    double lambda_155 = par[8];
    double alpha_155  = par[9];

    // H : Gaussian + single exp. tail
    double N_H  = par[10];
    double mean_H  = par[11];
    double sigma_H = par[12];
    double lambda_H = par[13];
    double alpha_H  = par[14];

    // C : Gaussian + single exp. tail
    double N_C  = par[15];
    double mean_C  = par[16];
    double sigma_C = par[17];
    double lambda_C = par[18];
    double alpha_C  = par[19];


    unique_ptr<TF1> DYB157(new TF1("DYB157",OldDYBShape,1.5,9.2,4));
    DYB157->SetParameters(mean_157,sigma_157,lambda_157,alpha_157);
    unique_ptr<TF1> DYB155(new TF1("DYB155",OldDYBShape,1.5,9.2,4));
    DYB155->SetParameters(mean_155,sigma_155,lambda_155,alpha_155);
    unique_ptr<TF1> DYBH(new TF1("DYBH",OldDYBShape,1.5,9.2,4));
    DYBH->SetParameters(mean_H,sigma_H,lambda_H,alpha_H);
    unique_ptr<TF1> DYBC(new TF1("DYBC",OldDYBShape,1.5,9.2,4));
    DYBC->SetParameters(mean_C,sigma_C,lambda_C,alpha_C);


    return N_157*DYB157->Eval(x[0]) + N_155*DYB155->Eval(x[0])
           + N_H*DYBH->Eval(x[0])+ N_C*DYBC->Eval(x[0]);



}





double DYBFitter2(double* x, double* par){

    // Gd157 : Gaussian + double exp. tail
    double N_157  = par[0];
    double mean_157  = par[1];
    double sigma_157 = par[2];
    double lambda1_157 = par[3];
    double lambda2_157 = par[4];
    double alpha_157  = par[5];
    double Beta_157 = par[6];

    // Gd155 : Gaussian
    double N_155  = par[7];
    double mean_155  = par[8];
    double sigma_155 = par[9];

    // H : Gaussian + single exp. tail
    double N_H  = par[10];
    double mean_H  = par[11];
    double sigma_H = par[12];
    double lambda_H = par[13];
    double alpha_H  = par[14];

    // C : Gaussian + single exp. tail
    double N_C  = par[15];
    double mean_C  = par[16];
    double sigma_C = par[17];
    double lambda_C = par[18];
    double alpha_C  = par[19];


    unique_ptr<TF1> DYB157(new TF1("DYB157",OldDYBShape2,1.5,12,6));
    DYB157->SetParameters(mean_157,sigma_157,lambda1_157,lambda2_157,alpha_157,Beta_157);
    unique_ptr<TF1> DYB155(new TF1("DYB155",GausShape,1.5,12,2));
    DYB155->SetParameters(mean_155,sigma_155);
    unique_ptr<TF1> DYBH(new TF1("DYBH",OldDYBShape,1.5,9.2,4));
    DYBH->SetParameters(mean_H,sigma_H,lambda_H,alpha_H);
    unique_ptr<TF1> DYBC(new TF1("DYBC",OldDYBShape,1.5,9.2,4));
    DYBC->SetParameters(mean_C,sigma_C,lambda_C,alpha_C);


    return N_157*DYB157->Eval(x[0]) + N_155*DYB155->Eval(x[0])
           + N_H*DYBH->Eval(x[0])+ N_C*DYBC->Eval(x[0]);



}






double DYBFitter3(double* x, double* par){

    // Gd157 : Gaussian + double exp. tail
    double N_157  = par[0];
    double mean_157  = par[1];
    double sigma_157 = par[2];
    double lambda1_157 = par[3];
    double lambda2_157 = par[4];
    double alpha_157  = par[5];
    double Beta_157 = par[6];

    // Gd155 : Gaussian
    double N_155  = par[7];
    double mean_155  = par[8];
    double sigma_155 = par[9];

    // H : Gaussian + single exp. tail
    double N_H  = par[10];
    double mean_H  = par[11];
    double sigma_H = par[12];
    double lambda_H = par[13];
    double alpha_H  = par[14];

    // C : Gaussian
    double N_C  = par[15];
    double mean_C  = par[16];
    double sigma_C = par[17];


    unique_ptr<TF1> DYB157(new TF1("DYB157",OldDYBShape2,1.5,12,6));
    DYB157->SetParameters(mean_157,sigma_157,lambda1_157,lambda2_157,alpha_157,Beta_157);
    unique_ptr<TF1> DYB155(new TF1("DYB155",GausShape,1.5,12,2));
    DYB155->SetParameters(mean_155,sigma_155);
    unique_ptr<TF1> DYBH(new TF1("DYBH",OldDYBShape,1.5,9.2,4));
    DYBH->SetParameters(mean_H,sigma_H,lambda_H,alpha_H);
    unique_ptr<TF1> DYBC(new TF1("DYBC",GausShape,1.5,9.2,4));
    DYBC->SetParameters(mean_C,sigma_C);


    return N_157*DYB157->Eval(x[0]) + N_155*DYB155->Eval(x[0])
           + N_H*DYBH->Eval(x[0]) + N_C*DYBC->Eval(x[0]);



}





double nHnGdFitter(double* x, double* par){

    //if(x[0] > 4.4892 and x[0] < 5.8788){
    //if(x[0] > 4.2854 and x[0] < 5.9486){
    if(x[0] > 4.2 and x[0] < 5.8){
      TF1::RejectPoint();
      return 0;
    }


    // Gd157 : Gaussian + double exp. tail
    double N_157  = par[0];
    double mean_157  = par[1];
    double sigma_157 = par[2];
    double lambda1_157 = par[3];
    double lambda2_157 = par[4];
    double alpha_157  = par[5];
    double Beta_157 = par[6];

    // Gd155 : Gaussian
    double N_155  = par[7];
    double mean_155  = par[8];
    double sigma_155 = par[9];

    // H : Gaussian + single exp. tail
    double N_H  = par[10];
    double mean_H  = par[11];
    double sigma_H = par[12];
    double lambda_H = par[13];
    double alpha_H  = par[14];


    unique_ptr<TF1> DYB157(new TF1("DYB157",OldDYBShape2,1.5,12,6));
    DYB157->SetParameters(mean_157,sigma_157,lambda1_157,lambda2_157,alpha_157,Beta_157);
    unique_ptr<TF1> DYB155(new TF1("DYB155",GausShape,1.5,12,2));
    DYB155->SetParameters(mean_155,sigma_155);
    unique_ptr<TF1> DYBH(new TF1("DYBH",OldDYBShape,1.5,9.2,4));
    DYBH->SetParameters(mean_H,sigma_H,lambda_H,alpha_H);


    return N_157*DYB157->Eval(x[0]) + N_155*DYB155->Eval(x[0]) + N_H*DYBH->Eval(x[0]);



}




#endif


