#ifndef SUMMARY_H
#define SUMMARY_H

#include <iostream>
#include <fstream>
#include <string>
#include "TTimeStamp.h"

//#include "CalibReadoutHeader.C"
//#include "AdScaled.C"
#define plVetoT 0.0006 //600 us
#define adVetoT 0.0014 //1400 us
#define shVetoT 0.4    //0.4 s

using namespace std;

class Summary
{
    
    public :
    
    int runNo;
    int detNo;
    int startTime_s;
    int startTime_ns;
    int stopTime_s;
    int stopTime_ns;
    int WpMuNum;
    int AdMuNum;
    int ShMuNum;
    int NetMuon;
    double overLapTime;
    double vetoTime;
    double liveTime();
    double runTime();
    double muonRate();
    double muonEff();
    
    Summary(int n1, int n2, int n3, int n4, int n5, int n6, int adMu, int shMu, int wpMu, int n7, double n10);

};


double Summary::liveTime()
{
    return  runTime()-vetoTime;
}

double Summary::runTime()
{
    return  (stopTime_s-startTime_s)+(stopTime_ns-startTime_ns)*1.0e-09;
}
double Summary::muonRate()
{
    return  NetMuon*1.0/liveTime();
}
double Summary::muonEff()
{
    return  1.0-vetoTime/runTime();
}

Summary::Summary(int n1, int n2, int n3, int n4, int n5, int n6, int adMu, int shMu, int wpMu, int n7, double n10)
{
    runNo       = n1;
    detNo       = n2;
    startTime_s = n3;
    startTime_ns= n4;
    stopTime_s  = n5;
    stopTime_ns = n6;
    NetMuon     = n7; //NetMuon
    vetoTime    = n10;
    AdMuNum     = adMu;
    ShMuNum     = shMu;
    WpMuNum     = wpMu;
    
    char txtFileName[200];
    sprintf(txtFileName,"RunInfo_%d.txt",runNo);
    cout<<txtFileName<<endl;
    ofstream myfile;
    myfile.open (txtFileName,ios::app);
    myfile<<runNo<<"\t"<< detNo <<"\t"<<startTime_s<<"\t"<<startTime_ns<<"\t"
          <<stopTime_s<<"\t"<<stopTime_ns<<"\t"<<runTime()<<"\t"<<liveTime()<<"\t"<<vetoTime<<"\t"
          <<AdMuNum<<"\t"<<ShMuNum<<"\t"<<WpMuNum<<"\t"
          <<NetMuon<<"\t"<<muonRate()<<"\t"<<muonEff()<<endl;
    myfile.close();
}

#endif
