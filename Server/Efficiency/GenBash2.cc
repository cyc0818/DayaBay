void GenBash2(){

    int Min = 1;
    int Max = 11000;
    int Fiducial_Vol = 3;
    TString codePath = "/dybfs2/users/yuchincheng/workdir/IBD/code/Efficiency/";
    TString executable = "FiducialEff";
    TString bashPath = codePath + "bashFile/";
    TString inPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/prompt_eff_truth/";
    TString outPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/MC3142/Efficiency/FiducialVolume/LS/";


    ofstream Fout;


    for(int i = Min; i<Max+1; i++){
        Fout.open(bashPath + TString::Format("mccut_%d.sh",i));
        Fout << "#!/bin/bash" << endl;
        Fout << endl;
        Fout << endl;
        Fout << "source /dybfs2/users/yuchincheng/workdir/juno/J21v1r0-Pre1/new_bashrc" << endl;
        Fout << "cd " << codePath << endl;
        Fout << "./" << executable << " " << Fiducial_Vol << " " << inPath << TString::Format("prompteff_%04d.root ",i) << outPath;
        Fout << TString::Format("eff_%04d.root",i) << endl;
        Fout.close();
    }


    Fout.open(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    for(int i = Min; i<Max+1; i++){
        Fout << endl;
        Fout << "chmod 755 mccut_" << i << ".sh" << endl;
        Fout << "hep_sub -os CentOS7 mccut_" << i << ".sh" << endl;
    }


}

