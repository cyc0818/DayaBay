#include <TFile.h>
#ifndef outfile_h
#define outfile_h
#include "PhyEvent.h"
class outfile {

public : 
//	TFile *file;// = new TFile("out.root","RECREATE");
	TTree *tr;// = new TTree("tr","");

	outfile();
	int site;
	int detector;
	int date;
	float ed,ep;
	float xp,yp,zp,xd,yd,zd;
	float dt;
	vector<float> dtlSH,nPESum;
	void FillIBD(PhyEvent &evtp,PhyEvent &evtd);

};

outfile::outfile() {

//	file = new TFile(filename,"RECREATE");
	tr = new TTree("Heli",""); 


	tr->Branch("site",&site);	
	tr->Branch("detector",&detector);
	tr->Branch("date",&date);
	tr->Branch("ep",&ep);
	tr->Branch("ed",&ed);
	tr->Branch("dt",&dt);
	tr->Branch("xp",&xp);
	tr->Branch("yp",&yp);
	tr->Branch("zp",&zp);
	tr->Branch("xd",&xd);
	tr->Branch("yd",&yd);
	tr->Branch("zd",&zd);
	tr->Branch("dtlSH",&dtlSH);
	tr->Branch("nPESum",&nPESum);
}


void outfile::FillIBD(PhyEvent &evtp,PhyEvent &evtd) {
	site = evtp.site;
	detector = evtp.detector;
	date = evtp.date;	
	ep = evtp.e;
	ed = evtd.e;
	dt = double(evtd.t-evtp.t)/1000.0;	
	xp = evtp.x;
	yp = evtp.y;
	zp = evtp.z;
	xd = evtd.x;
	yd = evtd.y;
	zd = evtd.z;
	dtlSH=evtp.dtlSH;
	nPESum=evtp.nPE;
	tr->Fill();
}

#endif
