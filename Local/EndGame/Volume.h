#ifndef Volume_h
#define Volume_h


#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <utility>
#include <array>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Uncertainty2.h"


using namespace std;


class Volume{

    public:

        Volume() : m_AD(0), m_vol(0){}
        Volume(int AD, int vol, string infile, bool masserror);     // If one is trying to esimate something like ratio when both numerator and
                                                                    // denominator share the same target volume, the "masserror" should turn off.

        
        int GetAD(){ return m_AD;}
        int GetVolNo(){ return m_vol;}
        double GetH(){ return m_H;}             // unit : kmol
        double GetHerr(){ return m_H_err;}
        Double_e GetHboth(){ return Double_e(m_H,m_H_err);}
        double GetC(){ return m_C;}
        double GetCerr(){ return m_C_err;}
        Double_e GetCboth(){ return Double_e(m_C,m_C_err);}
        double GetGd(int isotope);
        double GetGderr(int isotope);
        Double_e GetGdboth(int isotope);
        Double_e GetMass(){ return m_mass;}
        void ErrorOff();


        Volume operator+(const Volume& v) const;


        //void GetMass(double& central, double& error);
        //void GetFraction(int atomic_no, double& central, double& error);


    private:

        int m_AD;
        int m_vol;
        Double_e m_mass;
        map<int, Double_e> m_fraction;    //atomic no., central value, error


        // after evaluation
        double m_H = 0;
        double m_H_err = 0;
        double m_C = 0;
        double m_C_err = 0;
        double m_Gd = 0;
        double m_Gd_err = 0;


        bool Evaluate();


};



Volume::Volume(int AD, int vol, string infile, bool masserror = true){

    m_AD = AD;
    m_vol = vol;


    string line;
    ifstream Fin(infile);
    bool notyetfind = true;
    int read_AD = 0;
    int read_vol = 0;
    vector<double> data;


    while(Fin and notyetfind){

        getline(Fin, line);
        if(Fin.fail()) break;


        stringstream ss(line);
        string word;
        getline(ss, word, ' ');
        read_AD = stoi(word);
        if(read_AD != m_AD) continue;


        getline(ss, word, ' ');
        read_vol = stoi(word);
        if(read_vol != m_vol) continue;


        notyetfind = false;
        for(int i = 2; i<10; i++){
            getline(ss, word, ' ');
            data.push_back(stod(word));
        }


    }


    if(notyetfind) cerr << "Error! Didn't find the data" << endl;
    else{

        if(masserror) m_mass.SetBoth(data.at(0), data.at(1));
        else m_mass.SetBoth(data.at(0), 0);
        array<int,3> ele = {1,6,64};


        for(int i = 2; i<8; i+=2){
            Double_e temp(data.at(i), data.at(i+1));
            m_fraction.insert(pair<int,Double_e>(ele.at(i/2-1), temp));
        }

    }


    this->Evaluate();



}




Volume Volume::operator+(const Volume& v) const{

    Volume temp;


    if(m_AD == v.m_AD) temp.m_AD = v.m_AD;
    else if(m_AD < v.m_AD) temp.m_AD = 10*m_AD + v.m_AD;
    else temp.m_AD = 10*v.m_AD + m_AD;



    if(m_vol == v.m_vol) temp.m_vol = v.m_vol;
    else if(m_vol < v.m_vol) temp.m_vol = 10*m_vol + v.m_vol;
    else temp.m_vol = 10*v.m_vol + m_vol;

    
    temp.m_mass = m_mass + v.m_mass;


    temp.m_H = m_H + v.m_H;
    temp.m_C = m_C + v.m_C;
    temp.m_Gd = m_Gd + v.m_Gd;


    temp.m_H_err = sqrt(m_H_err*m_H_err + v.m_H_err*v.m_H_err);
    temp.m_C_err = sqrt(m_C_err*m_C_err + v.m_C_err*v.m_C_err);
    temp.m_Gd_err = sqrt(m_Gd_err*m_Gd_err + v.m_Gd_err*v.m_Gd_err);


    return temp;



}




double Volume::GetGd(int isotope){

    map<int,double> isomap = { {152,0.002}, {154,0.0218}, {155,0.148}, {156,0.2047},
                               {157,0.1565}, {158,0.2484}, {160,0.2186} };


    map<int,double>::iterator it = isomap.find(isotope);
    if(it == isomap.end()){
        cerr << "Error! Didn't find this isotope." << endl;
        return 0;
    }


    return m_Gd * it->second;


}





double Volume::GetGderr(int isotope){

    map<int,double> isomap = { {152,0.002}, {154,0.0218}, {155,0.148}, {156,0.2047},
                               {157,0.1565}, {158,0.2484}, {160,0.2186} };


    map<int,double>::iterator it = isomap.find(isotope);
    if(it == isomap.end()){
        cerr << "Error! Didn't find this isotope." << endl;
        return 0;
    }


    return m_Gd_err * it->second;


}






Double_e Volume::GetGdboth(int isotope){

    map<int,double> isomap = { {152,0.002}, {154,0.0218}, {155,0.148}, {156,0.2047},
                               {157,0.1565}, {158,0.2484}, {160,0.2186} };


    map<int,double>::iterator it = isomap.find(isotope);
    if(it == isomap.end()){
        cerr << "Error! Didn't find this isotope." << endl;
        return Double_e();
    }


    return Double_e(m_Gd * it->second, m_Gd_err * it->second);


}





bool Volume::Evaluate(){

    Double_e H(0,0);
    Double_e C(0,0);
    Double_e Gd(0,0);
    map<int,double> ato_mass = { {1,1.008}, {6,12.011}, {64,157.25} };
    map<int,Double_e&> refer = { {1,H}, {6,C}, {64,Gd} };


    for(auto i : ato_mass){

        refer.at(i.first) = m_mass * m_fraction.at(i.first) / i.second;

    }


    m_H = H.GetValue()*0.9998;          // H-1 abundance : 99.98%
    m_H_err = H.GetError()*0.9998;
    m_C = C.GetValue()*0.989;           // C-12 abundance : 98.9%
    m_C_err = C.GetError()*0.989;


    m_Gd = Gd.GetValue();
    m_Gd_err = Gd.GetError();


    return true;



}


void Volume::ErrorOff(){

    m_H_err = 0;
    m_C_err = 0;
    m_Gd_err = 0;


}




#endif



