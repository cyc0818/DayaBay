#include <iostream>
#include <fstream>
#include "TFile.h"
#include "TString.h"
#include "TTree.h"



using namespace std;


int main(int argc, const char** argv){

    if(argc != 3){
        cerr << "Wrong argument number!" << endl;
        return 0;
    }

    TString inname = argv[1];
    string outname = argv[2];


    int capTarget, capVol;
    unique_ptr<TFile> f(new TFile(inname));
    TTree* t = f->Get<TTree>("stats/tree/IBD");
    t->SetBranchAddress("capTarget",&capTarget);
    t->SetBranchAddress("capVol",&capVol);



    ofstream Fout(outname,ios::app);
    for(int i = 0; i<t->GetEntries(); i++){

        t->GetEntry(i);
        if(capTarget != 0 and capTarget != 1 and capTarget != 6 and capTarget != 64){
            Fout << inname << " , " << i << " , Z = " << capTarget << endl;
        }


    }


    f->Close();
    

    return 0;


}
