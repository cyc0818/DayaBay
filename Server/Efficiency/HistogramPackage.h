#ifndef HistogramPackage_h
#define HistogramPackage_h


#include <iostream>
#include <cmath>
#include <map>
#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"


using namespace std;
using elepair = pair<int,TH1D*>;
using elemap = map<int,TH1D*>;
using elepair2D = pair<int,TH2D*>;
using elemap2D = map<int,TH2D*>;


const int index_for_all_elements = -100;
const bool save_all_element = true;
map<int,TString> interest_tar = { {1,"_H"}, {6,"_C"}, {64,"_Gd"} };     //<atomic no., its name>


struct HistogramPackage{

    elemap h_ep;
    elemap h_ed;
    elemap h_dr;
    elemap h_dt;
    elemap2D h_rz;
    elemap2D h_rz_t;

    HistogramPackage(TString pass_con);

};


HistogramPackage::HistogramPackage(TString pass_con){

    if(save_all_element) interest_tar.insert(pair<int,TString>(index_for_all_elements,""));
    if(pass_con != "") pass_con.Insert(0,"_pass");

    for(auto i : interest_tar){
        h_ep.insert(elepair(i.first, new TH1D("Ep"+i.second+pass_con, "Ep"+i.second+pass_con+";E_{p}(MeV);Counts", 1200, 0, 12)));
        h_ed.insert(elepair(i.first, new TH1D("Ed"+i.second+pass_con, "Ed"+i.second+pass_con+";E_{d}(MeV);Counts", 1200, 0, 12)));
        h_dr.insert(elepair(i.first, new TH1D("dr"+i.second+pass_con, "dr"+i.second+pass_con+";dr(mm);Counts", 500, 0, 5000)));
        h_dt.insert(elepair(i.first, new TH1D("dt"+i.second+pass_con, "dt"+i.second+pass_con+";dt(#mus);Counts", 10000, 0, 10000)));
        h_rz.insert(elepair2D(i.first, new TH2D("RZ"+i.second+pass_con, "RZ"+i.second+pass_con+";R^{2}(mm^{2});z(mm);Counts",
                                                625, 0, 6250000, 500, -2500, 2500)));
        h_rz_t.insert(elepair2D(i.first, new TH2D("RZT"+i.second+pass_con, "RZT"+i.second+pass_con+";R_{true}^{2}(mm^{2});z_{true}(mm);Counts",
                                                  625, 0, 6250000, 500, -2500, 2500)));
    }


}



#endif



