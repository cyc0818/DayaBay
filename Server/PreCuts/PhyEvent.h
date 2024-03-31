#ifndef PHYEVENT_H
#define PHYEVENT_H

#include "TTimeStamp.h"
//#include "TMath.h"
//#include "CalibReadoutHeader.C"
//#include "AdScaled.C"

const double startT=1324339200;

class PhyEvent
{
    public :

	// event context
    int         runNo;
	int         site;
	int         detector;
    int         trigNo;
    int         Fold;
    double      FullTime;
	// most frequently used info (from RecData)
	float       E;
	float		X, Y, Z;
	float       nPESum;
	long long	t;
	long long	trigTime_s;
	long long	trigTime_ns;
    
	double	 	dtnAD;
	double	 	dtnWP;
	bool		passMu;
	int 		nHit;
	int			date;
    
    double      quadrant;
    double      maxQ;
    double      maxQ_2inchPMT;
    
	vector<float> nPE;
	vector<float> dtlSH;
	
	//Tags
    bool        isMultiTrig;
    bool        isEsumTrig;
    bool        isMultiAndEsumTrig;
    bool        isCross;
    bool        isForce;
    bool        isRPCNS;
    
    PhyEvent() {}
    ~PhyEvent() {}
	PhyEvent(CalibStats &calst, AdSimple &adrec);
    
    bool isFlasher();
    bool is2inchFlasher();
    bool isAdMuon();
    bool isWpMuon();
    bool isAdShowerMuon();
    bool isAd();
    bool isWp();
    bool isRpc();

};

PhyEvent::PhyEvent(CalibStats &calst, AdSimple &adrec) {

	site = adrec.site;
	detector = adrec.detector;
    trigNo = adrec.triggerNumber;
	E = adrec.energy;
	X = adrec.x;
	Y = adrec.y;
	Z = adrec.z;
	
	trigTime_s = adrec.triggerTimeSec;
	trigTime_ns = adrec.triggerTimeNanoSec;

	t = trigTime_s*1000000000+trigTime_ns;

	date = int((trigTime_s-startT)/86400);

	nHit = calst.nHit;
	nPESum = calst.NominalCharge;
    quadrant= calst.Quadrant;
    maxQ = calst.MaxQ;
    maxQ_2inchPMT = calst.MaxQ_2inchPMT;

    isMultiTrig = (adrec.triggerType==0x10000100);
    isEsumTrig  = (adrec.triggerType==0x10001000);
    isMultiAndEsumTrig = (adrec.triggerType==0x10001100);
    isCross = (adrec.triggerType==0x10000002);
    isForce = (adrec.triggerType==0x10000020);
    isRPCNS = (adrec.triggerType==0x10020000);
    
}

bool  PhyEvent::isFlasher() {
    double m_quadrant_Cut = 1.;
    double m_ratioMaxQ_Cut = 0.45;
    //if (TMath::Power((quadrant/m_quadrant_Cut), 2) + TMath::Power(maxQ/m_ratioMaxQ_Cut, 2) > 1.)
    if ((quadrant/m_quadrant_Cut)*(quadrant/m_quadrant_Cut) + (maxQ/m_ratioMaxQ_Cut)*(maxQ/m_ratioMaxQ_Cut) > 1.)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool PhyEvent::is2inchFlasher() {
    if (isAd() && maxQ_2inchPMT>100) {
    //if (isAd() && maxQ_2inchPMT>100) { && nPESum<=3000 && E<=20) {
        return true;
    }
    return false;
}

// fix the muon cut
bool PhyEvent::isAdMuon() {
    if (isAd() && nPESum>3000) {
    //if (isAd() && E>20 && E<=2500) {
        return true;
    }
    else {
        return false;
    }
}

bool PhyEvent::isWpMuon() {
    if (isWp() && nHit>12) {
        return true;
    }
    else {
        return false;
    }
}

bool PhyEvent::isAdShowerMuon() {
    if (isAd() && nPESum>300000) {
    //if (isAd() && E>2500) {
        return true;
    }
    else {
        return false;
    }
}

bool PhyEvent::isAd() {
    return (detector>=1 && detector<=4) ?true :false;
}

bool PhyEvent::isWp() {
    return (detector==5 || detector==6) ?true :false;
}

bool PhyEvent::isRpc() {
    return (detector==7) ?true :false;
}


#endif
