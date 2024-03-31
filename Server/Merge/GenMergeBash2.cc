void GenMergeBash2(){

    string site = "EH2";
    string DirPath = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/";
    //string InputFile = DirPath + "FileList.txt";
    TString filename;
    int maxnum = 51;
    int b = 0;
    TString OutputFile = DirPath + TString::Format("merge_2_%d.sh",b);


    ofstream Fout(OutputFile);
    //ifstream Fin(InputFile);


    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    Fout << "cd " << DirPath << endl;
    Fout << "hadd -ff ../" << site << "_CellPlots_2_" << b << ".root ";


    for(int i = 0; i<maxnum+1; i++){

        filename = site + TString::Format("_CellPlots_%d.root",i);
        Fout << filename << " ";

        if(i%10 == 0 && i!=0){
            Fout << endl;
            Fout << "echo merge " << b << " complete!" << endl;
            Fout.close();
            b++;
            OutputFile = DirPath + TString::Format("merge_2_%d.sh",b);
            Fout.open(OutputFile);
            Fout << "#!/bin/bash" << endl;
            Fout << endl;
            Fout << endl;
            Fout << "cd " << DirPath << endl;
            Fout << "hadd -ff ../" << site << "_CellPlots_2_" << b << ".root ";
        }

    }


    Fout.close();
    Fout.open(DirPath + "sub2.sh");
    Fout << "#!/bin/bash" << endl;
    Fout << endl;
    Fout << endl;
    Fout << "cd " << DirPath << endl;
    for(int i = 0; i<b+1; i++){
        Fout << "chmod 755 merge_2_" << i << ".sh" << endl;
        Fout << "hep_sub merge_2_" << i << ".sh" << endl;
        Fout << endl;
    }


}

