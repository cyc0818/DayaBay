void CheckTree(){

    string site = "EH1";
    string DirPath1 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Pairs/";
    string DirPath2 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Pairs2/";
    string InputFile = DirPath + "FileList.txt";
    string filename;


    system(("ls -I FileList.txt -1 " + DirPath + " >> " + InputFile).c_str());
    ifstream Fin(InputFile);


    while(Fin.good()){

        getline(Fin, filename);
        if(filename.size() == 0) continue;
        unique_ptr<TFile> f1(new TFile((DirPath1+filename).c_str()));
        unique_ptr<TFile> f2(new TFile((DirPath2+filename).c_str()));
        TTree* t1 = dynamic_cast<TTree*>(f1->Get("IBD")); 
        TTree* t2 = dynamic_cast<TTree*>(f2->Get("IBD")); 


        if(t1->GetEntries() != t2->GetEntries()) cout << "Not identical : " << filename << end;
        f1->Close();
        f2->Close();


    }



    system(("rm -f " + InputFile).c_str());


}

