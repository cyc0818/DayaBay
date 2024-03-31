
double binWidth = (12.0-0.0)/1200.0;
double fitL = 0.8;
double fitR = 3.5;

double CBShape(double *x,double *par)
{
  double N     = par[0];
  double mean  = par[1];
  double sigma = par[2];
  double a     = par[3];
  double n     = par[4];

  double e = x[0];
  a = abs(a);

  double pdf = 0;
  if( (e-mean)/sigma > -a )  {
    pdf = exp( - 1/2.0*pow((e-mean)/sigma,2) );
  } else {
    pdf = pow(n/a,n)*exp(-1/2.0*a*a) / pow(n/a-a-(e-mean)/sigma,n);
  }

  return N*pdf;
}

double pdfCB(double *x,double *par)
{
    double mean  = par[0];
    double sigma = par[1];
    double a     = par[2];
    double n     = par[3];
    
    double e = x[0];
    a = abs(a);
    
    double pdf = 0;
    if( (e-mean)/sigma > -a )  {
        pdf = exp( - 1/2.0*pow((e-mean)/sigma,2) );
    } else {
        pdf = pow(n/a,n)*exp(-1/2.0*a*a) / pow(n/a-a-(e-mean)/sigma,n);
    }
    
    return pdf;
}

Double_t ExpBKGFun(Double_t *x, Double_t *par)
{
    
    Double_t arg = 0;
    arg = x[0]*par[0];
    
    return TMath::Exp(arg);
}

Double_t PolBKGFun(Double_t *x, Double_t *par)
{
    double a    = par[0];
    double b    = par[1];
    double c    = 1.0;
    
    return x[0]*x[0]*a+x[0]*b+c;
    
}
////////////////////////////////////////////////

Double_t SigPart(Double_t *x, Double_t *par){
    
    double evtN  = par[0]*binWidth;
    double weight= par[1];
    double mean  = par[2];
    double sigma = par[3];
    double a     = par[4];
    double n     = par[5];
    
    TF1 *CBf = new TF1("CBf",pdfCB,fitL,fitR,4);
	CBf->SetParameters(mean,sigma,a,n);
    
    double nCBF  = CBf->Integral(fitL,fitR);
    
    return evtN*weight*pdfCB(x,&par[2])/(nCBF*1.0);
    
}

Double_t expBkgPart(Double_t *x, Double_t *par){
    
    double evtN  = par[0]*binWidth;
    double weight= par[1];
    double slope    = par[2];
    
    TF1 *expf = new TF1("expf",ExpBKGFun,fitL,fitR,1);
	expf->SetParameter(slope,par[2]);
    
    double nExpF = expf->Integral(fitL,fitR);
    
    return evtN*(1.0-weight)*ExpBKGFun(x,&par[2])/(nExpF*1.0);
    
}

Double_t polBkgPart(Double_t *x, Double_t *par){
    
    double evtN  = par[0]*binWidth;
    double weight= par[1];
    double a     = par[2];
    double b     = par[3];
    
    TF1 *polf = new TF1("polf",PolBKGFun,fitL,fitR,2);
	polf->SetParameters(a,b);
    
    double nPolF = polf->Integral(fitL,fitR);
    
    return evtN*(1.0-weight)*PolBKGFun(x,&par[2])/(nPolF*1.0);
    
}

Double_t ExpCB(Double_t *x, Double_t *par){
    
    double evtN  = par[0]*binWidth;
    double weight= par[1];
    double mean  = par[2];
    double sigma = par[3];
    double a     = par[4];
    double n     = par[5];
    double slope    = par[6];
    
    TF1 *CBf = new TF1("CBf",pdfCB,fitL,fitR,4);
	CBf->SetParameters(mean,sigma,a,n);
    TF1 *expf = new TF1("expf",ExpBKGFun,fitL,fitR,1);
	expf->SetParameter(slope,par[6]);
    
    double nExpF = expf->Integral(fitL,fitR);
    double nCBF  = CBf->Integral(fitL,fitR);
    
    return evtN*( (weight*pdfCB(x,&par[2]))/(nCBF*1.0) + ((1.0-weight)*ExpBKGFun(x,&par[6]))/(nExpF*1.0) );
    
}

Double_t PolCB(Double_t *x, Double_t *par){

    double evtN  = par[0]*binWidth;
    double weight= par[1];
    double mean  = par[2];
    double sigma = par[3];
    double a     = par[4];
    double n     = par[5];
    double a1    = par[6];
    double b1    = par[7];
    
    TF1 *CBf = new TF1("CBf",pdfCB,fitL,fitR,4);
	CBf->SetParameters(mean,sigma,a,n);
    TF1 *polf = new TF1("polf",PolBKGFun,fitL,fitR,2);
	polf->SetParameters(a1,b1);
    
    double nCBF  = CBf->Integral(fitL,fitR);
    double nPolF = polf->Integral(fitL,fitR);
    
    return evtN*( weight*pdfCB(x,&par[2])/(nCBF*1.0) +  (1.0-weight)*PolBKGFun(x,&par[6])/(nPolF*1.0) );
    
}

///////////////////////////////////

Double_t SigPart2(Double_t *x, Double_t *par){
    
    double N1    = par[0]*binWidth;
    double mean  = par[1];
    double sigma = par[2];
    double a     = par[3];
    double n     = par[4];
    
    TF1 *CBf = new TF1("CBf",pdfCB,fitL,fitR,4);
	CBf->SetParameters(mean,sigma,a,n);
    
    double nCBF  = CBf->Integral(fitL,fitR);
    
    return N1*pdfCB(x,&par[1])/(nCBF*1.0);
    
}
Double_t expBkgPart2(Double_t *x, Double_t *par){
    
    double N2  = par[0]*binWidth;
    double slope    = par[1];
    
    TF1 *expf = new TF1("expf",ExpBKGFun,fitL,fitR,2);
	expf->SetParameter(slope,par[1]);
    
    double nExpF = expf->Integral(fitL,fitR);
    
    return N2*ExpBKGFun(x,&par[1])/(nExpF*1.0);
    
}

Double_t polBkgPart2(Double_t *x, Double_t *par){
    
    double N2    = par[0]*binWidth;
    double a     = par[1];
    double b     = par[2];
    
    TF1 *polf = new TF1("polf",PolBKGFun,fitL,fitR,2);
	polf->SetParameters(a,b);
    
    double nPolF = polf->Integral(fitL,fitR);
    
    return N2*PolBKGFun(x,&par[1])/(nPolF*1.0);
    
}

Double_t ExpCB2(Double_t *x, Double_t *par){
    
    double N1    = par[0]*binWidth;
    double N2    = par[1]*binWidth;
    double mean  = par[2];
    double sigma = par[3];
    double a     = par[4];
    double n     = par[5];
    double slope    = par[6];
    
    TF1 *CBf = new TF1("CBf",pdfCB,fitL,fitR,4);
	CBf->SetParameters(mean,sigma,a,n);
    TF1 *expf = new TF1("expf",ExpBKGFun,fitL,fitR,1);
	expf->SetParameter(slope,par[6]);
    
    double nExpF = expf->Integral(fitL,fitR);
    double nCBF  = CBf->Integral(fitL,fitR);
    
    return N1*pdfCB(x,&par[2])/(nCBF*1.0) + N2*ExpBKGFun(x,&par[6])/(nExpF*1.0);
    
}

Double_t PolCB2(Double_t *x, Double_t *par){
    
    double N1    = par[0]*binWidth;
    double N2    = par[1]*binWidth;
    double mean  = par[2];
    double sigma = par[3];
    double a     = par[4];
    double n     = par[5];
    double a1    = par[6];
    double b1    = par[7];
    
    TF1 *CBf = new TF1("CBf",pdfCB,fitL,fitR,4);
	CBf->SetParameters(mean,sigma,a,n);
    TF1 *polf = new TF1("polf",PolBKGFun,fitL,fitR,2);
	polf->SetParameters(a1,b1);
    
    double nCBF  = CBf->Integral(fitL,fitR);
    double nPolF = polf->Integral(fitL,fitR);
    
    return N1*pdfCB(x,&par[2])/(nCBF*1.0) +  N2*PolBKGFun(x,&par[6])/(nPolF*1.0);
    
}

