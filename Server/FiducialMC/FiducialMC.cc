#include <array>
#include <memory>
#include "TFile.h"
#include "Observables.h"


using namespace std;


int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];
    cout << "Processing data : " << inname << endl;


    //array<TString,6> vol_name = {"tot","GdLS","IAV","LS","OAV","MO"};
    array<TString,5> vol_name = {"MO","LS","GdLS","Acrylic","tot"};
    map<int,HistogramPackage> vol_map;
    //vol_map.insert(pair<int,HistogramPackage>(-10,HistogramPackage(vol_name.at(0))));
    vol_map.insert(pair<int,HistogramPackage>(-10,HistogramPackage(vol_name.at(4))));
    //for(int i = 1; i<6; i++){
    for(int i = 0; i<4; i++){
        vol_map.insert(pair<int,HistogramPackage>(i,HistogramPackage(vol_name.at(i))));
    }
    HistogramPackage& tot = vol_map.at(-10);


    Observables* IBD;
    unique_ptr<TFile> f(new TFile(inname));
    unique_ptr<TTree> tree(dynamic_cast<TTree*>(f->Get("Event")));


    if(tree) IBD = new FormatBZ(2);
    else{
        
        tree = unique_ptr<TTree>(dynamic_cast<TTree*>(f->Get("stats/tree/IBD")));
        if(not tree){
            cerr << "Error! Unexpected data format." << endl;
            return 0;
        }

        IBD = new FormatPA();

    }


    IBD->Link(*tree);


    for(int i = 0; i<tree->GetEntries(); i++){

        tree->GetEntry(i);
        if(not IBD->BasicCheck()) continue;


        IBD->Save();
        //int vol = IBD->GetCapVol();
        int vol = IBD->GetGenVol();
        if(vol) IBD->Fill(vol_map.at(vol));
        IBD->Fill(tot);

    }
    f->Close();


    //vector<elemap HistogramPackage::*> ptr_to_mem = {&HistogramPackage::h_ed};
    vector<elemap HistogramPackage::*> ptr_to_mem = {&HistogramPackage::h_ep};
    //vector<elemap HistogramPackage::*> ptr_to_mem = {&HistogramPackage::h_dt};

    vector<elemap2D HistogramPackage::*> ptr_to_mem2 = {&HistogramPackage::h_rz_t};

    unique_ptr<TFile> fout(new TFile(outname,"recreate"));
    for(auto& step : vol_map){

        for(auto& ptr : ptr_to_mem){
            for(auto& p : step.second.*ptr){
                p.second->Write();
            }
        }

        
        for(auto& ptr2 : ptr_to_mem2){
            for(auto& p : step.second.*ptr2){ 
                p.second->Write();
            }
        }
    
    }


    tree.release();
    fout->Close();


    return 0;



}




