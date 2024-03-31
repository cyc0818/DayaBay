void GenPostCutBash(){

    TString dataPeriod = "EH3";
    TString codePath = "/dybfs2/users/yuchincheng/workdir/IBD/code/PostCuts/";
    TString bashPath = codePath + "bashFile/" + dataPeriod + "/";
    TString dataPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/";
    

    TString inPath = dataPath + dataPeriod + "/Pairs/";
    TString outPath = dataPath + dataPeriod + "/EvtSelect/";
    string filename;
    int RunNo;


    system("rm -f " + inPath + "FileList.txt");
    system("ls -I FileList.txt -1 " + inPath + " >> " + inPath + "FileList.txt");
    ifstream Fin(inPath + "FileList.txt");
    ofstream Fout(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout.close();


    while(Fin.good()){

        getline(Fin, filename);
        if(filename.size() == 0) continue;
        RunNo = stoi(filename.substr(4,5));
        cout << RunNo << endl;


        Fout.open(bashPath + TString::Format("PostCut_%d.sh",RunNo));
        Fout << "#!/bin/bash" << endl;
        Fout << endl;
        Fout << endl;
        Fout << "source /dybfs2/users/yuchincheng/workdir/juno/J21v1r0-Pre1/new_bashrc" << endl;
        Fout << "cd " << codePath << endl;
        Fout << "./main " << inPath << filename << " " << outPath << filename << endl;
        Fout.close();


        Fout.open(bashPath + "sub.sh", ios::app);
        Fout << endl;
        Fout << "chmod 755 PostCut_" << RunNo << ".sh" << endl;
        Fout << "hep_sub -os CentOS7 -mem 4000 -wt short PostCut_" << RunNo << ".sh" << endl;
        Fout.close();


    }



}

