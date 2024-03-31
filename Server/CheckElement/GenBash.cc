void GenBash(){

    int Min = 1;
    int Max = 9999;
    TString codePath = "/dybfs2/users/yuchincheng/workdir/IBD/code/CheckElement/";
    TString executable = "CheckElement";
    TString bashPath = codePath + "bashFile/";
    TString inPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/prompt_eff_truth/";
    TString outPath = codePath + "log";


    ofstream Fout;


    for(int i = Min; i<Max+1; i++){
        Fout.open(bashPath + TString::Format("elecheck_%d.sh",i));
        Fout << "#!/bin/bash" << endl;
        Fout << endl;
        Fout << endl;
        Fout << "source /dybfs2/users/yuchincheng/workdir/juno/J21v1r0-Pre1/new_bashrc" << endl;
        Fout << "cd " << codePath << endl;
        Fout << "./" << executable << " " << inPath << TString::Format("prompteff_%04d.root ",i) << outPath << endl;
        Fout.close();
    }


    Fout.open(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    for(int i = Min; i<Max+1; i++){
        Fout << endl;
        Fout << "chmod 755 elecheck_" << i << ".sh" << endl;
        Fout << "hep_sub -mem 4200 -os CentOS7 elecheck_" << i << ".sh" << endl;
    }


}

