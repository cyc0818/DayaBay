#ifndef Observables_h
#define Observables_h


#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <map>
#include <functional>
#include "TVector3.h"
#include "TTree.h"
#include "TString.h"
#include "HistogramPackage.h"


using namespace std;


// user setting for constants
const double Ep_min = 1.5;      // MeV
const double Ep_max = 12;       // MeV
const double Ed_min = 1.9;        // MeV
const double Ed_max = 12;       // MeV
const double dt_min = 1;        // us
const double dt_max = 400;      // us
const double dr_max = 500;      // mm
const int tar_vol = 1;          // 1 = GdLS, 2 = LS, 3 = MO
const bool do_fvcut = false;     // do fiducial volume cut or not



class Observables{

    public : 
        
        explicit Observables();
        virtual ~Observables(){}
        bool EpCut();
        bool EdCut();
        bool TimeIntervalCut();
        bool DistanceCut();
        bool FiducialVolCut();
        bool InTarget();
        bool Fill(HistogramPackage& pkg);   // fill all private members into histograms


        int GetCapTarget(){ return m_captarget; }
        int GetCapVol(){ return m_capvol; }


        virtual bool Link(TTree& tree) = 0;
        virtual bool Save() = 0;    // save all the physical observables into private members
        virtual bool BasicCheck() = 0;


    protected :

        // reconstruction
        TVector3 m_vtxp, m_vtxd;    // mm
        double m_dr;                // mm
        double m_ep, m_ed;          // MeV
        double m_tp, m_td, m_dt;    // us

        // true information
        TVector3 m_vtxp_t, m_vtxd_t;  // mm
        double m_dr_t;                // mm
        double m_ep_t, m_ed_t;        // MeV
        int m_captarget, m_genvol, m_capvol;

        // ptr to member in HistogramPackage
        list<pair<elemap HistogramPackage::*, double&>> object_map;
        list<pair<elemap2D HistogramPackage::*, TVector3&>> vertex_map;
        
        
};





Observables::Observables(){

    object_map = { {&HistogramPackage::h_ed,m_ed}, {&HistogramPackage::h_ep,m_ep},
                   {&HistogramPackage::h_dt,m_dt}, {&HistogramPackage::h_dr,m_dr} };

    vertex_map = { {&HistogramPackage::h_rz, m_vtxd}, {&HistogramPackage::h_rz_t, m_vtxd_t} };

}





bool Observables::EpCut(){
    
    if(m_ep > Ep_min and m_ep < Ep_max) return true;
    else return false;

}





bool Observables::EdCut(){
    
    //if(m_ed > Ed_min and m_ed < Ed_max and this->FiducialVolCut()) return true;
    //if(m_ed > Ed_min and m_ed < Ed_max) return true;
    if(m_captarget == 1 and m_ed > 1.9 and m_ed < 2.7) return true;
    if(m_captarget == 6 and m_ed > 4 and m_ed < 5.8) return true;
    if(m_captarget == 64 and m_ed > 6 and m_ed < 12) return true;

    return false;
    //return true;


}





bool Observables::TimeIntervalCut(){

    if(m_dt > dt_min and m_dt < dt_max) return true;
    else return false;


}





bool Observables::DistanceCut(){

    if(m_dr < dr_max) return true;
    else return false;


}





bool Observables::FiducialVolCut(){

    list<pair<TVector3&,bool>> vol_judge = { {m_vtxp,false}, {m_vtxd,false} };


    for(auto& i : vol_judge){

        int vol_no = 0;
        
        if(i.first.Z()>=2000 or i.first.Z()<=-2000 or i.first.Perp2()>=4000*4000) vol_no = 3;
        else if(i.first.Z()<1554 and i.first.Z()>-1554 and i.first.Perp2()<1540*1540) vol_no = 1;
        else vol_no = 2;


        if(vol_no == tar_vol) i.second = true;

    }


    bool both_in = true;
    for(auto i : vol_judge) both_in = (both_in and i.second);


    return both_in;



}




bool Observables::InTarget(){

    if(not do_fvcut) return true;


    bool judge_p = true;
    if(m_vtxp.Z()>=1750 or m_vtxp.Z()<=-1750 or m_vtxp.Perp2()>=1750*1750) judge_p = false;
    bool judge_d = true;
    if(m_vtxd.Z()>=1750 or m_vtxd.Z()<=-1750 or m_vtxd.Perp2()>=1750*1750) judge_d = false;


    return (judge_p and judge_d);



}




bool Observables::Fill(HistogramPackage& pkg){

    elemap::iterator it;
    for(auto i_pair : object_map){
        
        if(save_all_element){
            it = (pkg.*i_pair.first).find(index_for_all_elements);
            it->second->Fill(i_pair.second);
        }


        it = (pkg.*i_pair.first).find(m_captarget);
        if(it != (pkg.*i_pair.first).end()) it->second->Fill(i_pair.second);

    }


    elemap2D::iterator it2;
    for(auto i_pair : vertex_map){
        
        if(save_all_element){
            it2 = (pkg.*i_pair.first).find(index_for_all_elements);
            it2->second->Fill(i_pair.second.Perp2(), i_pair.second.Z());
        }


        it2 = (pkg.*i_pair.first).find(m_captarget);
        if(it2 != (pkg.*i_pair.first).end()) it2->second->Fill(i_pair.second.Perp2(), i_pair.second.Z());

    }


    return true;



}





class FormatBZ : public Observables{

    public : 

        vector<double> E, X, Y, Z;
        vector<double> ET, XT, YT, ZT;
        vector<int> TrigSec, TrigNano;
        double CapTarget;
        int Fold, GenDet, CapDet;
        

        bool Link(TTree& tree);
        bool Save();    // save all the physical observables into private members
        bool BasicCheck();


        explicit FormatBZ(size_t size);

};




FormatBZ::FormatBZ(size_t size) : Observables(){

    vector<reference_wrapper<vector<double>>> v_ref_vd = {E,X,Y,Z,ET,XT,YT,ZT};
    vector<reference_wrapper<vector<int>>> v_ref_vi = {TrigSec,TrigNano};

    for(auto& ref_v : v_ref_vd) ref_v.get().resize(size);
    for(auto& ref_v : v_ref_vi) ref_v.get().resize(size);
    CapTarget = -1;


}





bool FormatBZ::Link(TTree& tree){
    
    map<TString,int&> relation_i;
    map<TString,double&> relation_d;
    map<TString,vector<int>&> relation_vi;
    map<TString,vector<double>&> relation_vd;


    relation_vd = { {"E",E}, {"X",X}, {"Y",Y}, {"Z",Z},
                    {"ET",ET}, {"XT",XT}, {"YT",YT}, {"ZT",ZT} };

    relation_vi = { {"TrigSec",TrigSec}, {"TrigNano",TrigNano} };
    relation_d = { {"CapTarget",CapTarget} };
    relation_i = { {"Fold",Fold}, {"GenDet",GenDet}, {"CapDet",CapDet} };


    for(auto& p : relation_vd) tree.SetBranchAddress(p.first, &p.second.at(0)); 
    for(auto& p : relation_vi) tree.SetBranchAddress(p.first, &p.second.at(0)); 
    for(auto& p : relation_d) tree.SetBranchAddress(p.first, &p.second); 
    for(auto& p : relation_i) tree.SetBranchAddress(p.first, &p.second); 


    return true;



}





bool FormatBZ::Save(){

    // reconstruction
    m_vtxp.SetXYZ(X.at(0), Y.at(0), Z.at(0));
    m_vtxd.SetXYZ(X.at(1), Y.at(1), Z.at(1));
    TVector3 dvtx = m_vtxd - m_vtxp;
    m_dr = dvtx.Mag();
    m_ep = E.at(0);
    m_ed = E.at(1);


    m_tp = TrigSec.at(0)*1e6 + TrigNano.at(0)*1e-3;
    m_td = TrigSec.at(1)*1e6 + TrigNano.at(1)*1e-3;
    m_dt = m_td - m_tp;


    // true information
    m_vtxp_t.SetXYZ(XT.at(0), YT.at(0), ZT.at(0));
    m_vtxd_t.SetXYZ(XT.at(1), YT.at(1), ZT.at(1));
    TVector3 dvtx_t = m_vtxd_t - m_vtxp_t;
    m_dr_t = dvtx_t.Mag();
    m_ep_t = ET.at(0);
    m_ed_t = ET.at(1);
    m_captarget = static_cast<int>(CapTarget);
    m_genvol = GenDet;
    m_capvol = CapDet;
    

    return true;



}





bool FormatBZ::BasicCheck(){

    bool judge = true;


    if(E.size() != 2) return false;
    else{
        if(E.at(0) == E.at(1)) judge = false;
        if(Fold != 2) judge = false;
    }


    return judge;



}





class FormatPA : public Observables{

    public :

        double ep, xp, yp, zp;
        double ed, xd, yd, zd;
        double ept, xpt, ypt, zpt;
        double xdt, ydt, zdt;
        long long dT;
        int capTarget, genType, capVol;


        bool Link(TTree& tree);
        bool Save();    // save all the physical observables into private members
        bool BasicCheck();


        explicit FormatPA() : Observables(){}

};





bool FormatPA::Link(TTree& tree){
    
    map<TString,int&> relation_i;
    map<TString,long long&> relation_ll;
    map<TString,double&> relation_d;


    relation_d = { {"ep",ep}, {"xp",xp}, {"yp",yp}, {"zp",zp},
                   {"ed",ed}, {"xd",xd}, {"yd",yd}, {"zd",zd}, 
                   {"ept",ept}, {"xpt",xpt}, {"ypt",ypt}, {"zpt",zpt},
                   {"xdt",xdt}, {"ydt",ydt}, {"zdt",zdt} }; 
        
    relation_i = { {"capTarget",capTarget}, {"genType",genType}, {"capVol",capVol} };
    relation_ll = { {"dT",dT} };


    for(auto& p : relation_d) tree.SetBranchAddress(p.first, &p.second); 
    for(auto& p : relation_i) tree.SetBranchAddress(p.first, &p.second); 
    for(auto& p : relation_ll) tree.SetBranchAddress(p.first, &p.second); 


    return true;



}





bool FormatPA::Save(){

    m_vtxp.SetXYZ(xp, yp, zp);
    m_vtxd.SetXYZ(xd, yd, zd);
    TVector3 dvtx = m_vtxd - m_vtxp;
    m_dr = dvtx.Mag();
    m_ep = ep;
    m_ed = ed;


    m_vtxp_t.SetXYZ(xpt, ypt, zpt);
    m_vtxd_t.SetXYZ(xdt, ydt, zdt);
    TVector3 dvtx_t = m_vtxd_t - m_vtxp_t;
    m_dr_t = dvtx_t.Mag();
    m_ep_t = ept;
    m_ed_t = -1;


    m_tp = -1;
    m_td = -1;
    m_dt = static_cast<double>(dT)*1e-3;
    m_captarget = capTarget;
    m_genvol = genType;
    m_capvol = capVol;


    return true;



}





bool FormatPA::BasicCheck(){

    bool judge = true;
    //if(genType == 0) judge = false;
    if(capVol == 5) judge = false;
    //if(capVol == 4) judge = false;
    //if(capVol != 5) judge = false;


    return judge;


}




/*vector<bool (Observables::*)()> cut_seq = {&Observables::EdCut, &Observables::EpCut, 
                                           &Observables::DistanceCut, &Observables::TimeIntervalCut, &Observables::InTarget};*/
vector<bool (Observables::*)()> cut_seq = {&Observables::EpCut, &Observables::TimeIntervalCut, 
                                           &Observables::EdCut, &Observables::DistanceCut};


#endif
