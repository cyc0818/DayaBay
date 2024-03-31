void GenBash(){

    int Min = 1;
    int Max = 200000;
    TString codePath = "/dybfs2/users/yuchincheng/workdir/IBD/code/Efficiency/";
    TString executable = "Efficiency";
    TString bashPath = codePath + "bashFile/";
    //TString inPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/M14A/";
    //TString outPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/M14A/eff/";
    TString inPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/nKE_tree/";
    TString outPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/noMOcap_sq/";


    ofstream Fout;


    for(int i = Min; i<Max+1; i++){
        Fout.open(bashPath + TString::Format("mccut_%d.sh",i));
        Fout << "#!/bin/bash" << endl;
        Fout << endl;
        Fout << endl;
        Fout << "source /dybfs2/users/yuchincheng/workdir/juno/J21v1r0-Pre1/new_bashrc" << endl;
        Fout << "cd " << codePath << endl;
        Fout << "./" << executable << " " << inPath << TString::Format("prompteff_%04d.root ",i) << outPath << TString::Format("eff_%04d.root",i) << endl;
        Fout.close();
    }


    Fout.open(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    for(int i = Min; i<Max+1; i++){
        Fout << endl;
        Fout << "chmod 755 mccut_" << i << ".sh" << endl;
        Fout << "hep_sub -mem 4200 -os CentOS7 mccut_" << i << ".sh" << endl;
    }


}

