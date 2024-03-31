#include <boost/math/special_functions/lambert_w.hpp>
using namespace std;
using boost::math::lambert_w0;

double N_f[8][2] = {
    {485254,3468},
    {694809,3808},
    {675643,3943},
    {771345,3218},
    {773236,3233},
    {779035,4019},
    {700126,5099},
    {607795,3568}
};
double N_f2[8][2] = {
    {4.706e7,19303},
    {6.573e7,27780},
    {6.476e7,30762},
    {7.337e7,27763},
    {7.388e7,23183},
    {7.379e7,23071},
    {6.791e7,30211},
    {5.915e7,23279}
};
double edist[8] = {1.04,1.11,1.09,1.11,1.09,1.11,1.08,1.06};
double a_P_data[8] = {2.26264,2.22768,2.14355,2.07943,2.07305,2.08532,2.07782,2.15266};
double accRate[8] = {0};
int order[8] = {0,1,2,7,3,4,5,6};

double calTheory(double r07, double r15){
    return exp(-401.e-6*r07)*exp(-399.e-6*(r07-r15))*exp(-400.e-6*r15)*399.e-6*r15*exp(-399.e-6*r15);
}
double calMultiEff(double r07, double r15){
    return exp(-800.e-6*r07-400.e-6*r15);
}



void calAcc(){
    TChain* chain_live = new TChain("live");
    ifstream inlist;
    inlist.open("/dybfs2/users/chenpoan/EndGame/background/Acc/Poisson/p17b.list");
    string fname;
    while(inlist>>fname){
        chain_live->Add(fname.c_str());
    }
    //cout<<"Entries:"<<chain_live->GetEntries()<<"\n";
    int detNo;
    double a_N[8];
    long long liveTime,totalTime,N07,N15,N19,timeGap;
    long long a_liveTime[8];
    long long a_totalTime[8];
    long long a_N07[8];
    long long a_N15[8];
    long long a_N19[8];
    long long a_timeGap[8];
    double a_timeGapEff[8];
    double a_eps_mu[8];
    double a_eps_multi[8];
    /*double a_eps_acc[8][2] = {
        {1.04,0.04},
        {1.11,0.04},
        {1.09,0.03},
        {1.11,0.02},
        {1.09,0.02},
        {1.11,0.02},
        {1.08,0.02},
        {1.06,0.04}
    };*/
    double a_eps_acc[8][2] = {
        {1.110,0.0009},
        {1.090,0.0008},
        {1.088,0.0008},
        {1.098,0.0005},
        {1.093,0.0005},
        {1.096,0.0005},
        {1.075,0.0005},
        {1.0722,0.0008}
    };
    double a_R07[8][2];
    double a_R15[8][2];
    double a_R19[8][2];
    double a_Poisson[8];
    double a_poisson[8][2];
    for(int detno = 0;detno<8;detno++){
        a_liveTime[detno]=0;
        a_totalTime[detno]=0;
        a_N07[detno]=0;
        a_N15[detno]=0;
        a_N19[detno]=0;
        a_timeGap[detno]=0;
    }
    chain_live->SetBranchAddress("detNo",&detNo);
    chain_live->SetBranchAddress("liveTime",&liveTime);
    chain_live->SetBranchAddress("totalTime",&totalTime);
    chain_live->SetBranchAddress("N07",&N07);
    chain_live->SetBranchAddress("N15",&N15);
    chain_live->SetBranchAddress("N19",&N19);
    chain_live->SetBranchAddress("timeGap",&timeGap);
    for(int entry = 0;entry<chain_live->GetEntries();entry++){
        chain_live->GetEntry(entry);
        if(entry%200 == 0) cout << entry << endl;
        if(N07==0){
            //cout<<"This is entry no."<<entry<<", and detector "<<detNo<<" are not avaliable now\n";
            continue;
        } 
        if((1.*liveTime)>(1.*totalTime)){
            cout<<"Entry :"<<entry<<"\n";
            continue;
        }
        a_N07[detNo-1]+=N07;
        a_N15[detNo-1]+=N15;
        a_N19[detNo-1]+=N19;
        a_liveTime[detNo-1]+=liveTime;
        a_totalTime[detNo-1]+=totalTime;
        a_timeGap[detNo-1]+=timeGap;
    }
    for(int detno = 0;detno<8;detno++){
        cout<<"AD:"<<detno+1<<"\t";
        double timeGapEff = double(a_totalTime[detno]-a_timeGap[detno])/double(a_totalTime[detno]);
        a_timeGapEff[detno] = timeGapEff;

        double liveEff = double(a_liveTime[detno])/double(a_totalTime[detno]);
        a_eps_mu[detno] = liveEff;

        double scale = 1.e9;
        double R07 = scale*double(a_N07[detno])/double(a_liveTime[detno])/timeGapEff;
        double R07E = scale*double(sqrt(a_N07[detno]))/double(a_liveTime[detno])/timeGapEff;
        double R15 = scale*double(a_N15[detno])/double(a_liveTime[detno])/timeGapEff;
        double R15E = scale*double(sqrt(a_N15[detno]))/double(a_liveTime[detno])/timeGapEff;
        double R19 = scale*double(a_N19[detno])/double(a_liveTime[detno])/timeGapEff;
        double R19E = scale*double(sqrt(a_N19[detno]))/double(a_liveTime[detno])/timeGapEff;
        double isoeff = exp(lambert_w0(-2.*(a_N07[detno]*400.e-6)/(double(a_liveTime[detno])*1.e-9*timeGapEff)));
        double isoeff2 = exp(-2.*(a_N07[detno]*400.e-6)/(double(a_liveTime[detno])*1.e-9*timeGapEff));
        a_R07[detno][0] = R07;
        a_R07[detno][1] = R07E;
        a_R15[detno][0] = R15;
        a_R15[detno][1] = R15E;
        a_R19[detno][0] = R19;
        a_R19[detno][1] = R19E;

        cout << "AD = " << detno+1 << " , N07 = "<< a_N07[detno] << " , N15 = " << a_N15[detno] << " , N19 = " << a_N19[detno] << " , isoeff = ";
        cout << isoeff << " , " << isoeff2 << endl;
        //cout<<"R15:"<<R15<<"\n";
        cout<<"Poisson probability:"<<100.*calTheory(R07,R15)<<"\t";
        a_Poisson[detno] = 100.*calTheory(R07,R15);
        //cout<<"AD"<<detno<<"\n";
        cout<<"Accidentals bkg:"<<calTheory(R07,R15)*double(a_N19[detno])*(edist[detno])/100.<<"\n";
        a_N[detno] = calTheory(R07,R15)*double(a_N19[detno])*(edist[detno])/100.;
        accRate[detno] = calTheory(R07,R15)*double(a_N19[detno])*(edist[detno])/100./double(a_liveTime[detno])/timeGapEff*86400.e9;
        //cout << "Multiplicity Cut efficiency = " << calMultiEff(R07,R15) << "\n";
        a_eps_multi[detno] = calMultiEff(R07,R15);
        //cout<<"Data Driven probability"<<(a_P_data[detno])<<"\t";
        //cout<<"Accidentals bkg:"<<0.01*(a_P_data[detno])*double(a_N15[detno])*(edist[detno])/100.<<"\n";
    }
    cout<<"FullTimes\n";
    for(int i = 0;i<8;i++)
        cout<<double(a_totalTime[order[i]])/86400.e9*a_timeGapEff[order[i]]<<" & ";
    cout<<"LiveTimes\n";
    for(int i = 0;i<8;i++)
        cout<<double(a_liveTime[order[i]])/86400.e9*a_timeGapEff[order[i]]<<" & ";
    cout<<"\nMuon Veto Efficiency\n";
//    cout<<fixed;
    for(int i = 0;i<8;i++)
        cout<<a_eps_mu[order[i]]<<" & ";
    cout<<"\nMultiplicity Cut Efficiency\n";
    for(int i = 0;i<8;i++){
        double A = exp(-800.e-6*a_R07[order[i]][0]);
        double eA = exp(-800.e-6*a_R07[order[i]][0])*800.e-6*a_R07[order[i]][1];
        double B = exp(-400.e-6*a_R15[order[i]][0]);
        double eB = exp(-400.e-6*a_R15[order[i]][0])*400.e-6*a_R15[order[i]][1];
        double f = A*B*100.;
        double error = A*B*100.*sqrt( pow(eA/A,2)+pow(eB/B,2)+(2*eA*eB/A/B));
        cout<<" & \\thead{"<<f<<"\\\\("<<error<<")}";
    }
    //cout<<"\nEps_acc_dist\n";
    //for(int i = 0;i<8;i++){
    //    double f = N_f[order[i]][0]/N_f2[order[i]][0];
    //    double A = N_f[order[i]][1]/N_f[order[i]][0];
    //    double B = N_f2[order[i]][1]/N_f2[order[i]][0];
    //    double error = f*sqrt(A*A+B*B);
    //    a_eps_acc[order[i]][0] = f;
    //    a_eps_acc[order[i]][1] = error;
    //    cout<<"\\thead{"<<100.*f<<"\\\\("<<100.*error<<")}"<< " & ";
    //}
    cout<<"\nRate of E>07 Singles\n";
    for(int i = 0;i<8;i++)
        cout<<"\\thead{"<<a_R07[order[i]][0]<<"\\\\("<<a_R07[order[i]][1]<<")}"<<" & ";
    cout<<"\nRate of E>15 Likes Singles\n";
    for(int i = 0;i<8;i++)
        cout<<"\\thead{"<<a_R15[order[i]][0]<<"\\\\("<<a_R15[order[i]][1]<<")}"<<" & ";
    cout<<"\nRate of E>19 Likes Singles\n";
    for(int i = 0;i<8;i++)
        cout<<"\\thead{"<<a_R19[order[i]][0]<<"\\\\("<<a_R19[order[i]][1]<<")}"<<" & ";
    cout<<"\nPoisson Probability\n";
    for(int i = 0;i<8;i++){
        double A = exp(-401.e-6*a_R07[order[i]][0]);
        double eA = exp(-401.e-6*a_R07[order[i]][0])*401.e-6*a_R07[order[i]][1];
        double B = exp(-400.e-6*a_R15[order[i]][0]);
        double eB = exp(-400.e-6*a_R15[order[i]][0])*400.e-6*a_R15[order[i]][1];
        double C = exp(-399.e-6*(a_R07[order[i]][0]-a_R15[order[i]][0]));
        double eC = exp(-399.e-6*(a_R07[order[i]][0]-a_R15[order[i]][0]))*399.e-6*sqrt(pow(a_R07[order[i]][1],2)+pow(a_R15[order[i]][1],2));
        double D = exp(-399.e-6*a_R15[order[i]][0]);
        double eD = exp(-399.e-6*a_R15[order[i]][0])*399.e-6*a_R15[order[i]][1];
        double E = 399.e-6*a_R15[order[i]][0];
        double eE = 399.e-6*a_R15[order[i]][1];
        double f = 100.*A*B*C*D*E;
        double error = f*sqrt( pow(eA/A,2) + pow(eB/B,2) + pow(eC/C,2) + pow(eD/D,2) + pow(eE/E,2) );
        a_poisson[order[i]][0] = f/100.;
        a_poisson[order[i]][1] = error/100.;
        cout<<"\\thead{"<<f<<"\\\\("<<error<<")}"<<" & ";
    }
    cout<<"\nAccidentals Poisson\n";
    for(int i = 0;i<8;i++){
        double r19 = a_R19[order[i]][0];
        double er19 = a_R19[order[i]][1];
        double livetime = double(a_totalTime[order[i]])*1.e-9*a_timeGapEff[order[i]];
        double epsu = a_eps_mu[order[i]];
        double Pp = a_poisson[order[i]][0];
        double ePp = a_poisson[order[i]][1];
        double epsAcc = a_eps_acc[order[i]][0]*0.01;
        double eepsAcc = a_eps_acc[order[i]][1]*0.01;
        double N = r19*livetime*epsu*Pp*epsAcc;
        double error = N*sqrt(pow(er19/r19,2)+pow(ePp/Pp,2)+pow(eepsAcc/epsAcc,2));
        //cout<<r19<<" "<<livetime<<" "<<epsu<<" "<<epsAcc<<" "<<Pp<<"\n";
        cout<<"\\thead{"<<N<<"\\\\("<<error<<")}"<<" & ";
    }
    cout<<"\nactually running time\n";
    for(int i = 0;i<8;i++){
        double livetime = double(a_liveTime[order[i]])/86400.e9*a_timeGapEff[order[i]];
        cout<<livetime<<",";
    }
    cout<<"\nAccidentals Daily Rate\n";
    for(int i = 0;i<8;i++)
        cout<<accRate[order[i]]<<" & ";
    cout<<"\nN1.9\n";
    for(int i = 0;i<8;i++)
        cout<<"\\thead{\\scriptsize "<<double(a_N19[order[i]])<<"\\\\(\\scriptsize "<<sqrt(a_N19[order[i]])<<")}"<<" & ";
    cout<<"\n\n";

}
