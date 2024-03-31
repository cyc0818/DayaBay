void GenMergeBash(){

    string site = "EH3";
    string DirPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Plots/";
    string bashPath = "/dybfs2/users/yuchincheng/workdir/IBD/code/Merge/bashFile/" + site + "/";
    string InputFile = DirPath + "FileList.txt";
    string filename;
    int a = 0;
    int b = 0;
    TString OutputFile = static_cast<TString>(bashPath) + TString::Format("merge_%d.sh",b);
    string MergeFinalPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Merge1/";


    system(("ls -I FileList.txt -1 " + DirPath + " >> " + InputFile).c_str());
    ofstream Fout(OutputFile);
    ifstream Fin(InputFile);


    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    Fout << "cd " << DirPath << endl;
    Fout << "hadd -ff " << MergeFinalPath << site << "_MergePlots_" << b << ".root ";


    while(Fin.good()){

        getline(Fin, filename);
        if(filename.size() == 0) continue;
        Fout << filename << " ";
        a++;

        if(a%100 == 0){
            Fout << endl;
            Fout << "echo merge " << b << " complete!" << endl;
            Fout.close();
            b++;
            OutputFile = static_cast<TString>(bashPath) + TString::Format("merge_%d.sh",b);
            Fout.open(OutputFile);
            Fout << "#!/bin/bash" << endl;
            Fout << endl;
            Fout << endl;
            Fout << "cd " << DirPath << endl;
            Fout << "hadd -ff " << MergeFinalPath << site << "_MergePlots_" << b << ".root ";
        }

    }


    Fout.close();
    Fout.open(bashPath + "sub.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    Fout << "cd " << bashPath << endl;
    for(int i = 0; i<b+1; i++){
        Fout << "chmod 755 merge_" << i << ".sh" << endl;
        Fout << "hep_sub merge_" << i << ".sh" << endl;
        Fout << endl;
    }


    system(("rm -f " + InputFile).c_str());


}

