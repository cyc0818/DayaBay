void GenAccSubBash(){

    TString codePath = "/dybfs2/users/yuchincheng/workdir/IBD/code/FiducialVolume/CellPlotsUnify/";
    TString bashPath = codePath + "bashFile/";
    TString dataPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B";


    ofstream Fout;


    for(int i = 0; i<100; i++){
        Fout.open(bashPath + TString::Format("cell_%d.sh",i));
        Fout << "#!/bin/bash" << endl;
        Fout << endl;
        Fout << endl;
        Fout << "source /dybfs2/users/yuchincheng/workdir/juno/J21v1r0-Pre1/new_bashrc" << endl;
        Fout << "cd " << codePath << endl;
        Fout << "./main " << dataPath << " " << i << endl;
        Fout.close();
    }


    Fout.open(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    for(int i = 0; i<100; i++){
        Fout << endl;
        Fout << "chmod 755 cell_" << i << ".sh" << endl;
        Fout << "hep_sub -os CentOS7 cell_" << i << ".sh" << endl;
    }


}

