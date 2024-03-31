#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TString.h"

using std::string;
using std::vector;
using namespace std;


void FillHistogram(){
    TString dataPeriod = "P21A"; 
    TString site = "EH3"; 
    TFile* f = new TFile("./"+dataPeriod+"_"+site+".root","RECREATE");
    TH1D* hEp_ttl = new TH1D("hEp_ttl","Prompt Energy;E_{p}(MeV);Counts",1200,0,12);
    TH1D* hEd_ttl = new TH1D("hEd_ttl","Delayed Energy;E_{d}(MeV);Counts",1200,0,12);
    TH1D* hdr_ttl = new TH1D("hdr_ttl","Two Signals distance;#Deltad(mm);Counts",540,0,5400);
    TH2D* h2D_ttl = new TH2D("h2D_ttl",";E_{p}(MeV);E_{d}(MeV);Counts",1200,0,12,1200,0,12);
    TH1D* hEp_s = new TH1D("hEp_s","Prompt Energy(singles);E_{p}(MeV);Counts",1200,0,12);
    TH1D* hEd_s = new TH1D("hEd_s","Delayed Energy(singles);E_{d}(MeV);Counts",1200,0,12);
    TH1D* hdr_s = new TH1D("hdr_s","Two Signals distance(singles);#Deltad(mm);Counts",540,0,5400);
    TH2D* h2D_s = new TH2D("h2D_s",";E_{p}(MeV);E_{d}(MeV);Counts",1200,0,12,1200,0,12);
    TH1D* hEp = new TH1D("hEp","Prompt Energy(sub);E_{p}(MeV);Counts",1200,0,12);
    TH1D* hEd = new TH1D("hEd","Delayed Energy(sub);E_{d}(MeV);Counts",1200,0,12);
    TH1D* hdr = new TH1D("hdr","Two Signals distance(sub);#Deltad(mm);Counts",540,0,5400);
    TChain* AllIBD = new TChain("IBD");
    TChain* AllSingles[2] = { new TChain("Singles") , new TChain("Singles") };
    double Ep;
    double xp;
    double yp;
    double zp;
    double Ed;
    double xd;
    double yd;
    double zd;
    double dt;
    double Es[2];
    double xs[2];
    double ys[2];
    double zs[2];
    TVector3 vtx_p;
    TVector3 vtx_d;
    TVector3 dr;


    AllIBD->Add("./Evt_*");
    AllIBD->SetBranchAddress("ep",&Ep);
    AllIBD->SetBranchAddress("xp",&xp);
    AllIBD->SetBranchAddress("yp",&yp);
    AllIBD->SetBranchAddress("zp",&zp);
    AllIBD->SetBranchAddress("ed",&Ed);
    AllIBD->SetBranchAddress("xd",&xd);
    AllIBD->SetBranchAddress("yd",&yd);
    AllIBD->SetBranchAddress("zd",&zd);
    AllIBD->SetBranchAddress("dT",&dt);
    for(int chainidx = 0;chainidx<2;chainidx++){
        AllSingles[chainidx]->Add("./Evt_*");
        AllSingles[chainidx]->SetBranchAddress("es",&Es[chainidx]);
        AllSingles[chainidx]->SetBranchAddress("xs",&xs[chainidx]);
        AllSingles[chainidx]->SetBranchAddress("ys",&ys[chainidx]);
        AllSingles[chainidx]->SetBranchAddress("zs",&zs[chainidx]);
    }

    
    double progress = 0.1;
	cout << "Reading IBD data and filling histogram..." << std::endl;
    for(int i=0;i<AllIBD->GetEntries();i++){
        if((double)i/AllIBD->GetEntries() >=progress || i == AllIBD->GetEntries()-1){
            cout << "Progress : " << 100*progress << "%" << std::endl;
            progress = progress + 0.1;
        }
        else{}
        AllIBD->GetEntry(i);
        hEp_ttl->Fill(Ep);
        hEd_ttl->Fill(Ed);
        h2D_ttl->Fill(Ep,Ed);
        vtx_p.SetXYZ(xp,yp,zp);
        vtx_d.SetXYZ(xd,yd,zd);
        dr = vtx_d - vtx_p;
        hdr_ttl->Fill(dr.Mag());
    }


    progress = 0.1;
	cout << "Reading single data and filling histogram..." << std::endl;
    for(long long i=0;i<AllSingles[0]->GetEntries()/2;i++){
        if((double)i/(AllSingles[0]->GetEntries()/2) >=progress || i == (AllSingles[0]->GetEntries()/2)-1){
            cout << "Progress : " << 100*progress << "%" << std::endl;
            progress = progress + 0.1;
        }
        else{}
        AllSingles[0]->GetEntry(i);
        AllSingles[1]->GetEntry(i+(AllSingles[0]->GetEntries()/2));
        hEp_s->Fill(Es[0]);
        hEd_s->Fill(Es[1]);
        h2D_s->Fill(Es[0],Es[1]);
        vtx_p.SetXYZ(xs[0],ys[0],zs[0]);
        vtx_d.SetXYZ(xs[1],ys[1],zs[1]);
        dr = vtx_d - vtx_p;
        hdr_s->Fill(dr.Mag());
    }


	cout << "Saving histogram in root file" << std::endl;
    hEp_ttl->Write();
    hEd_ttl->Write();
    hdr_ttl->Write();
    h2D_ttl->Write();
    hEp_s->Write();
    hEd_s->Write();
    hdr_s->Write();
    h2D_s->Write();


    f->Close();
	cout << "Successful!" << std::endl;


}
