#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "TFile.h"
#include "TDatime.h"
#include "TString.h"

using std::string;
using std::vector;
using namespace std;



void info_writing(){

    string dataPeriod = "P17B";
    string site = "EH3";
    int iterationNo = 2000;
    string input_dir = "/dybfs2/users/yuchincheng/workdir/IBD/data/" + dataPeriod + "/" + site + "/PreCuts/"; 
    string output_dir = "/dybfs2/users/yuchincheng/workdir/IBD/data/" + dataPeriod + "/" + site + "/Plots/"; 
    string input_list = input_dir + dataPeriod + "_" + site + "_list.txt";
    string output_table = output_dir + dataPeriod + "_" + site + "_info.txt";
    string rootFile;
    TFile* f;
    TTree* Event;
    TDatime stamp;
    int RunNo;
    int DetNo;
    int Date;
    int TrigSec;
    double FullTime;
    double LiveTime;
    double TimeGap;
    double VetoEff;
    double GapEff;
    int AdMu;
    int ShMu;
    int WpMu;
    int NetMu;
    double MuRate;
    double E;   //final event for each AD in every file E = -1
    int check;
    vector<bool> ADswitch;
    vector<bool> isfound;
    bool runagain = false;


    ofstream outfile(output_table);
    ifstream infile(input_list);
    outfile.precision(14);
    while(infile.good()){
        getline(infile,rootFile);
        if(rootFile.size() == 0) continue;
        RunNo = stoi(rootFile.substr(7,5));
        cout << RunNo << endl;
        check = 1;
        f = TFile::Open((input_dir + rootFile).c_str());
        Event = (TTree*)f->Get("Event"); 
        Event->SetBranchAddress("Det",&DetNo);
        Event->SetBranchAddress("TrigSec",&TrigSec);
        Event->SetBranchAddress("FullTime",&FullTime);
        Event->SetBranchAddress("LiveTime",&LiveTime);
        Event->SetBranchAddress("TimeGap",&TimeGap);
        Event->SetBranchAddress("AdMu",&AdMu);
        Event->SetBranchAddress("ShMu",&ShMu);
        Event->SetBranchAddress("WpMu",&WpMu);
        Event->SetBranchAddress("NetMu",&NetMu);
        Event->SetBranchAddress("E",&E);
        

        if(site == "EH3"){
            ADswitch.resize(5);
            isfound.resize(5);
        }
        else{
            ADswitch.resize(3);
            isfound.resize(3);
        }


        for(int i = 0; i<iterationNo; i++){
            if(i >= Event->GetEntries()) break; 
            Event->GetEntry(i);
            ADswitch[DetNo] = true;
            if(site == "EH3"){
                if(ADswitch[1] && ADswitch[2] && ADswitch[3] && ADswitch[4]) break;
            }
            else{
                if(ADswitch[1] && ADswitch[2]) break;
            }
        }


        int it = Event->GetEntries() - 1;
        long long init = 0;
        if(Event->GetEntries()-iterationNo > 0) init = Event->GetEntries()-iterationNo;
        for(long long i = init; i < Event->GetEntries() ; i++){
        //while(it>0){
            Event->GetEntry(i);
            if(E != -1) continue;
            /*if(E == -1){
                it--;
                continue;
            }*/
            stamp.Set(TrigSec);
            Date = stamp.GetDate();
            VetoEff = LiveTime/FullTime;
            GapEff = (LiveTime-TimeGap)/LiveTime;
            MuRate = NetMu/LiveTime/GapEff;
            if(ADswitch[DetNo]){
                outfile << RunNo << "\t" << DetNo << "\t" << TrigSec << "\t" << FullTime << "\t" << TimeGap << "\t" << LiveTime << "\t" << 
                VetoEff << "\t" << AdMu << "\t" << ShMu << "\t" << WpMu << "\t" << NetMu << "\t" << MuRate << endl;
            }


            /*bool allfind = true;
            for(int j = 1; j<ADswitch.size();j++){
                if(ADswitch[j]) allfind = allfind and isfound[j];
            }
            if(allfind) break;
            it--;*/
            if(DetNo != check) runagain = true;
            check ++;
        }


        if(runagain) break;
        f->Close();
        ADswitch.clear();
        isfound.clear();

    }


    if(runagain) cout << "The iteration number should be increased and run again!!" << endl;
    else cout << "Successful!" << endl;


}
