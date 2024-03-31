void MergeTree(){

    string site = "EH1";
    string DirPath1 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Pairs/";
    string DirPath2 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/IBDSelect/";
    string bashPath = "/dybfs2/users/yuchincheng/workdir/IBD/code/Merge/bashFile2/" + site + "/";
    string InputFile = DirPath1 + "FileList.txt";
    string filename;
    string MergeFinalPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/EvtSelect/";
    int run = 0;
    vector<int> runQ;


    system(("ls -I FileList.txt -1 " + DirPath1 + " >> " + InputFile).c_str());
    ofstream Fout;
    ifstream Fin(InputFile);




    while(Fin.good()){

        getline(Fin, filename);
        if(filename.size() == 0) continue;
        run = stoi(rootFile.substr(4,5));
        runQ.push_back(run);
        TString OutputFile = static_cast<TString>(bashPath) + TString::Format("mergetree_%d.sh",b);
        Fout.open(static_cast<string>(OutputFile));
        Fout << "#!/bin/bash" << endl;
        Fout << endl;
        Fout << endl;
        Fout << "hadd -ff " << MergeFinalPath << filename << " " << DirPath1 << filename << " " << DirPath2 << "IBD_run" << run << ".root" << endl;
        Fout.close();

    }


    Fout.open(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    Fout << "cd " << bashPath << endl;
    for(int i : runQ){
        Fout << "chmod 755 mergetree_" << i << ".sh" << endl;
        Fout << "hep_sub mergetree_" << i << ".sh" << endl;
        Fout << endl;
    }


    system(("rm -f " + InputFile).c_str());


}

