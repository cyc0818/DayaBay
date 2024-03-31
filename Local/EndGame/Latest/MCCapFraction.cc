#include "/Users/chengyuchin/Analysis/nC/EndGame/Volume.h"


void MCCapFraction(){

    map<int,pair<int,string>> ZAmap = {{1,{1,"Hydrogen"}}, {12,{6,"Carbon"}}, {155,{64,"Gadolinium"}}, {157,{64,"Gadolinium"}}};
    map<int,TGraphErrors*> gm;
    map<int,TCanvas*> gc;
    vector<double> En;


    for(auto s : ZAmap){

        TGraphErrors* temp = new TGraphErrors();
        gm.insert(pair<int,TGraphErrors*>(s.first, temp));


        string line;
        int i = 0;
        int points = 0;
        ifstream infile(TString::Format("/Users/chengyuchin/Analysis/NuWa/%d_%d_%s",s.second.first,s.first,s.second.second.c_str()));
        while(infile.good()){
            i++;
            getline(infile, line);
            if(i < 4) continue;


            stringstream ss(line);
            string word;
            pair<double, double> p(0,0);    // < kinetic energy , cross section >


            for(int j = 0; j<6; j++){
                getline(ss, word, ' ');
                if(not j) continue;
                if(word.empty()) continue;


                if(not(j&1)){
                    //cout << "Energy = " << word;
                    p.first = stod(word);
                }
                else{
                    //cout << " , cross section = " << word << endl;
                    p.second = stod(word);
                }


                if(p.first and p.second){
                    temp->SetPoint(points, p.first, p.second);
                    if(s.first == 155) En.push_back(p.first);
                    p = {0,0};
                    points++;
                }

            }


        }


        TCanvas* temp_c = new TCanvas(TString::Format("c%d",s.first), TString::Format("c%d",s.first), 1920, 1080);
        gPad->SetLogx(1);
        gPad->SetLogy(1);
        temp->Draw();
        gc.insert(pair<int,TCanvas*>(s.first, temp_c));

    }



    Volume GdLS;
    Volume LS;
    Volume Acrylic;
    const string txtfile = "/Users/chengyuchin/Analysis/nC/EndGame/data.txt";
    for(int ad = 1; ad<5; ad++){
        GdLS = GdLS + Volume(ad, 1, txtfile);
        LS = LS + Volume(ad, 2, txtfile);
        Acrylic = Acrylic + Volume(ad, 3, txtfile);
    }


    TGraphErrors* frac = new TGraphErrors();
    for(int i = 0; i < En.size(); i++){

        const double x = En.at(i);
        //if(x > 4e-2) break;
        Volume& target = GdLS;
        const Double_e numer = target.GetCboth()*Double_e(gm.at(12)->Eval(x), 4.e-4); 
        const Double_e denom = target.GetGdboth(155)*Double_e(gm.at(155)->Eval(x), 5000.) + target.GetGdboth(157)*Double_e(gm.at(157)->Eval(x), 12000.)
                             + target.GetHboth()*Double_e(gm.at(1)->Eval(x), 0.02) + target.GetCboth()*Double_e(gm.at(12)->Eval(x), 4.e-4);

        const Double_e f = numer/denom;
        frac->SetPoint(i, x, f.GetValue());
        frac->SetPointError(i, 0, f.GetError());

    }


    TCanvas* c0 = new TCanvas("c0","c0",1920,1080);
    gPad->SetLogx(1);
    gPad->SetLogy(1);
    frac->GetXaxis()->SetRangeUser(1.e-4,3.e-2);
    frac->Draw();




}
