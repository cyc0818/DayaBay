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



void gen_subsh(){

    string dataPeriod = "P17B";
    string site = "EH1";
    int LowerLimit = 50000;
    int UpperLimit = 80000;
    string jobtype = "PreCuts";
    string input_dir = "/dybfs2/users/yuchincheng/workdir/IBD/data/" + dataPeriod + "/" + site + "/PreCuts/"; 
    string output_dir = "/dybfs2/users/yuchincheng/workdir/IBD/code/" + jobtype + "/tcshFile/" + site + "/"; 
    string input_list = output_dir + dataPeriod + "_" + site + "_list.txt";
    string output_sh = output_dir + "sub.sh";
    string tcshFile;
    int RunNo;


    ofstream outfile(output_sh);
    outfile << "#!/bin/bash" << endl;
    outfile << "cd " << output_dir << endl;
    ifstream infile(input_list);
    while(infile.good()){
        getline(infile,tcshFile);
        
        if(tcshFile.size() == 0) continue;
        RunNo = stoi(tcshFile.substr(7,5));
        
        if(RunNo >= UpperLimit || RunNo < LowerLimit) continue;
        outfile << "chmod a+x PreCut_" << RunNo << ".csh" << endl;
        outfile << "hepsub -os SL6 -mem 4500 PreCut_" << RunNo << ".csh" << endl;
        outfile << endl;


    }



}
