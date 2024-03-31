#include <array>
#include <memory>
#include "TFile.h"
#include "Observables.h"


using namespace std;
using Relation = pair<bool (Observables::*)(), HistogramPackage>;


int main(int argc, const char** argv){
    
    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    TString outname = argv[2];
    cout << "Processing data : " << inname << endl;


    array<TString,4> cut_name = {"Ep","Epdt","EpdtEd","EpdtEddr"};
    //array<TString,4> cut_name = {"","Ep","Epdr","Epdrdt"};
    //array<TString,5> cut_name = {"","Ep","Epdr","Epdrdt","EpdrdtFV"};
    vector<Relation> seq_map;
    for(int i = 0; i<4; i++){
        seq_map.push_back(Relation(cut_seq[i], HistogramPackage(cut_name[i])));
    }


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
        for(auto& step : seq_map){
            if(not (IBD->*step.first)()) break;
            IBD->Fill(step.second);
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




