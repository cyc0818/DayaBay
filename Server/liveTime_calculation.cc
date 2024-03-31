void calEffMuon(long long* live, long long* total){
    for(int i = 1; i<9; i++){
        cout<<"AD"<<i<<" total running time :"<<1./86400/1e9*(((long long*)total)[i])<<endl;
        cout<<"AD"<<i<<" efficiency :"<<100.*(((long long*)live)[i])/(((long long*)total)[i])<<endl;
    }
}
void showStatus(long long * thelong){
    for(int j =0;j<9;j++) cout<<thelong[j]<<endl;
}

void liveTime_calculation(){
    ifstream infile;
    infile.open("test.list");
    string fname;
    TTree* tree;
    TFile* tempfile;
    bool p11b=true;
    bool p15a=true;
    bool EH1;
    long long LiveTime[9];
    long long TotalTime[9];
    for(int a=0;a<9;a++){
        LiveTime[a]=0;
        TotalTime[a]=0;
    }
    while(infile>>fname){
        cout<<fname<<endl;
        tempfile=new TFile(fname.c_str(),"READ");
        tempfile->GetObject("live",tree);
        long long liveTime=0;
        long long totalTime=0;
        long long gap = 0;
        long long T=0;
        int detNo=0;
        tree->SetBranchAddress("detNo",&detNo);
        tree->SetBranchAddress("liveTime",&liveTime);
        tree->SetBranchAddress("timeGap",&gap);
        tree->SetBranchAddress("totalTime",&totalTime);
        tree->SetBranchAddress("T",&T);
        tree->GetEntry(0);
        if(T>1.87455E+7&&p11b){
            LiveTime[7]=0;
            LiveTime[8]=0;
            TotalTime[7]=0;
            TotalTime[8]=0;
            cout<<"this is p11b"<<endl;
            showStatus(LiveTime);
            p11b=false;
        }
        if(T>1.1370783E+8&&p15a){
            cout<<"this is p15a"<<endl;
            showStatus(LiveTime);
            p15a=false;
        }
        if(tree->GetMaximum("detNo")==4&&tree->GetMinimum("detNo")==1)EH1=true;
        else EH1=false;
        for(int i = 0;i<tree->GetEntries();i++){
            tree->GetEntry(i);
            if(EH1){
               if(detNo==3||detNo==4) continue; 
            }
            LiveTime[detNo]+=liveTime;
            LiveTime[detNo]-=gap;
            TotalTime[detNo]+=totalTime;
            TotalTime[detNo]-=gap;
        }
        tempfile->Close();
        delete tempfile;
    }
    showStatus(LiveTime);
    cout<<"Calculating Now..."<<endl;
    showStatus(TotalTime);
    cout<<"this is p17b"<<endl;
    calEffMuon(LiveTime,TotalTime);
    
    ofstream outputfile;
    outputfile.open("table.txt",ios_base::app);
    outputfile<<"LiveTime(days)"<<"\t\t";
    for(int i = 1;i<9;i++){
        outputfile<<1.*(((long long*)TotalTime)[i])/86400./1e9<<"\t\t";
    }
    outputfile<<endl;
    outputfile<<"MuonEfficiency(%)"<<"\t\t";
    for(int i = 1;i<9;i++){
        outputfile<<100.*(((long long*)LiveTime)[i])/(((long long*)TotalTime)[i])<<"\t\t";
    }
    outputfile<<endl;
}
