#include <array>
#include <memory>
#include "TFile.h"
#include "Observables.h"


using namespace std;
using Relation = pair<bool (Observables::*)(), HistogramPackage>;


int main(int argc, const char** argv){
    
    if(argc != 4){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    const int tar_vol = stoi(argv[1]);
    TString inname = argv[2];
    TString outname = argv[3];
    cout << "Processing data : " << inname << endl;


    array<TString,4> cut_name = {"","Ep","Epdr","Epdrdt"};
    vector<Relation> seq_map;
    for(int i = 0; i<4; i++){
        seq_map.push_back(Relation(cut_seq[i], HistogramPackage(cut_name[i])));
    }


    unique_ptr<TFile> f(new TFile(inname));
    unique_ptr<TTree> tree(dynamic_cast<TTree*>(f->Get("Event")));
    int mode = 1;
    if(!tree){
            tree = unique_ptr<TTree>(dynamic_cast<TTree*>(f->Get("stats/tree/IBD")));
            mode = 2;
            if(!tree){
                cerr << "Error! Unexpected data format." << endl;
                return 0;
            }
    }


    Observables IBD(2);
    IBD.Link(*tree, mode);


    for(int i = 0; i<tree->GetEntries(); i++){

        tree->GetEntry(i);
        if(IBD.capVol != tar_vol) continue;


        if(mode == 1){
            if(IBD.E.at(0) == IBD.E.at(1)) continue;
            if(IBD.Fold != 2) continue;
        }


        IBD.Save(mode);
        for(auto& step : seq_map){
            if(not (IBD.*step.first)()) break;
            IBD.Fill(step.second);
        }

    }
    f->Close();


    vector<elemap HistogramPackage::*> ptr_to_mem = {&HistogramPackage::h_ed, &HistogramPackage::h_ep,
                                                      &HistogramPackage::h_dt, &HistogramPackage::h_dr};

    vector<elemap2D HistogramPackage::*> ptr_to_mem2 = {&HistogramPackage::h_rz, &HistogramPackage::h_rz_t};

    unique_ptr<TFile> fout(new TFile(outname,"recreate"));
    for(auto& step : seq_map){

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




