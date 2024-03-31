void CheckTree(){

    string site = "EH3";
    string DirPath1 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Pairs/";
    string DirPath2 = "/dybfs2/users/yuchincheng/workdir/IBD/data/P17B/" + site + "/Pairs2/";
    string InputFile = DirPath1 + "FileList.txt";
    string filename;
    bool allthesame = true;


    system(("ls -I FileList.txt -1 " + DirPath1 + " >> " + InputFile).c_str());
    ifstream Fin(InputFile);


    while(Fin.good()){

        getline(Fin, filename);
        if(filename.size() == 0) continue;
        //cout << filename << endl;
        unique_ptr<TFile> f1(new TFile((DirPath1+filename).c_str()));
        unique_ptr<TFile> f2(new TFile((DirPath2+filename).c_str()));
        TTree* t1 = dynamic_cast<TTree*>(f1->Get("IBD")); 
        t1->SetName("IBD_nGd");
        TTree* t2 = dynamic_cast<TTree*>(f2->Get("IBD")); 
        t2->SetName("IBD_nH");

        if(t1->GetEntries() != t2->GetEntries()){
            cout << "Not identical : " << filename << endl;
            allthesame = false;
        }
        f1->Close();
        f2->Close();


    }

    if(allthesame) cout << "All IBD trees are the same!" << endl;



    system(("rm -f " + InputFile).c_str());


}

