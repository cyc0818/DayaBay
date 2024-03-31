#ifndef Uncertainty_h
#define Uncertainty_h

#include <cmath>
#include <iostream>


using namespace std;


class Double_e{

    public : 

        explicit Double_e(const double& value = 0, const double& error = 0) : m_v(value), m_e(error){}


        void SetValue(const double& value){ m_v = value;}
        void SetError(const double& error){ m_e = error;}
        void SetBoth(const double& value, const double& error){
            m_v = value;
            m_e = error;
        }


        double GetValue() const { return m_v; }
        double GetError() const { return m_e; }
        void Print() const { cout << m_v << " +/- " << m_e << endl; }


        Double_e operator+(const double& x) const;
        Double_e operator-(const double& x) const;
        Double_e operator*(const double& x) const;
        Double_e operator/(const double& x) const;


        Double_e operator+(const Double_e& x) const;
        Double_e operator-(const Double_e& x) const;
        Double_e operator*(const Double_e& x) const;
        Double_e operator/(const Double_e& x) const;


        Double_e& operator+=(const double& x);
        Double_e& operator-=(const double& x);
        Double_e& operator*=(const double& x);
        Double_e& operator/=(const double& x);


        Double_e& operator+=(const Double_e& x);
        Double_e& operator-=(const Double_e& x);
        Double_e& operator*=(const Double_e& x);
        Double_e& operator/=(const Double_e& x);


        friend Double_e sqrt(const Double_e& x);
        friend Double_e exp(const Double_e& x);
        friend Double_e log(const Double_e& x);
        friend Double_e sin(const Double_e& x);
        friend Double_e cos(const Double_e& x);
        friend Double_e tan(const Double_e& x);


        friend Double_e operator+(const double& a, const Double_e& x);
        friend Double_e operator-(const double& a, const Double_e& x);
        friend Double_e operator*(const double& a, const Double_e& x);
        friend Double_e operator/(const double& a, const Double_e& x);
        friend ostream& operator<<(ostream& os, const Double_e& x);


        friend Double_e Poisson(int n, const Double_e& x);


    private :

        double m_v;
        double m_e;


};



Double_e Double_e::operator+(const double& x) const{

    Double_e temp;


    temp.m_v = m_v + x;
    temp.m_e = m_e;


    return temp;


}




Double_e Double_e::operator+(const Double_e& x) const{

    Double_e temp;

    
    temp.m_v = m_v + x.m_v;
    temp.m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return temp;

}




Double_e Double_e::operator-(const double& x) const{

    Double_e temp;


    temp.m_v = m_v - x;
    temp.m_e = m_e;


    return temp;


}





Double_e Double_e::operator-(const Double_e& x) const{

    Double_e temp;

    
    temp.m_v = m_v - x.m_v;
    temp.m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return temp;

}





Double_e Double_e::operator*(const double& x) const{

    Double_e temp;


    temp.m_v = m_v * x;
    temp.m_e = m_e * abs(x);


    return temp;

}




Double_e Double_e::operator*(const Double_e& x) const{

    Double_e temp;


    temp.m_v = m_v * x.m_v;
    if(temp.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));


    return temp;

}





Double_e Double_e::operator/(const double& x) const{

    Double_e temp;


    if(x){
        temp.m_v = m_v / x;
        temp.m_e = m_e / abs(x);
    }


    return temp;

}





Double_e Double_e::operator/(const Double_e& x) const{

    Double_e temp;


    if(x.m_v) temp.m_v = m_v / x.m_v;
    if(m_v and x.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));


    return temp;

}




Double_e& Double_e::operator+=(const double& x){

    m_v = m_v + x;

    return *this;

}




Double_e& Double_e::operator-=(const double& x){

    m_v = m_v - x;

    return *this;

}





Double_e& Double_e::operator*=(const double& x){

    m_v = m_v * x;
    m_e = m_e * abs(x);

    return *this;

}




Double_e& Double_e::operator/=(const double& x){

    if(x){
        m_v = m_v / x;
        m_e = m_e / abs(x);
    }

    return *this;

}





Double_e& Double_e::operator+=(const Double_e& x){

    m_v = m_v + x.m_v;
    m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return *this;

}




Double_e& Double_e::operator-=(const Double_e& x){

    m_v = m_v - x.m_v;
    m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return *this;

}



Double_e& Double_e::operator*=(const Double_e& x){

    Double_e temp;


    temp.m_v = m_v * x.m_v;
    if(temp.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));
    *this = temp;


    return *this;

}




Double_e& Double_e::operator/=(const Double_e& x){

    Double_e temp;


    if(x.m_v) temp.m_v = m_v / x.m_v;
    if(m_v and x.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));
    *this = temp;


    return *this;

}





Double_e sqrt(const Double_e& x){

    if(x.m_v <= 0) return Double_e(0,0);


    Double_e temp;


    temp.m_v = sqrt(x.m_v); 
    temp.m_e = x.m_e/2/temp.m_v;


    return temp;


}




Double_e exp(const Double_e& x){

    Double_e temp;


    temp.m_v = exp(x.m_v);
    temp.m_e = temp.m_v * x.m_e;


    return temp;


}




Double_e log(const Double_e& x){

    Double_e temp;


    if(x.m_v){
        temp.m_v = log(x.m_v);
        temp.m_e = abs(x.m_e/x.m_v);
    }


    return temp;


}




Double_e sin(const Double_e& x){

    Double_e temp;


    temp.m_v = sin(x.m_v);
    temp.m_e = cos(x.m_v) * x.m_e;


    return temp;


}





Double_e cos(const Double_e& x){

    Double_e temp;


    temp.m_v = cos(x.m_v);
    temp.m_e = sin(x.m_v) * x.m_e;


    return temp;


}





Double_e tan(const Double_e& x){

    Double_e temp;


    temp.m_v = tan(x.m_v);
    temp.m_e = x.m_e / cos(x.m_v) / cos(x.m_v);


    return temp;


}




Double_e operator+(const double& a, const Double_e& x){

    return x+a;

}




Double_e operator-(const double& a, const Double_e& x){

    Double_e temp(x);

    temp.m_v = a - x.m_v;

    
    return temp;


}




Double_e operator*(const double& a, const Double_e& x){

    return x*a;

}




Double_e operator/(const double& a, const Double_e& x){

    Double_e temp;

    if(x.m_v){
        temp.m_v = a / x.m_v;
        temp.m_e = abs(a*x.m_e) / (x.m_v * x.m_v);
    }

    
    return temp;


}




ostream& operator<<(ostream& os, const Double_e& x){

    os << x.m_v << " +/- " << x.m_e;


    return os;


}


Double_e Poisson(int n, const Double_e& x){

    if(n < 0) return Double_e(0,0);
    else{

        Double_e temp(1,0);
        double fact = 1;
        for(int i = n; i>0; i--){
            temp *= x;
            fact *= i;
        }


        return temp*exp(-1.*x)/fact;


    }



}




Double_e VarWeightedMean(const vector<Double_e>& v){

    double numer = 0;
    double denom = 0;


    for(const Double_e& i : v){

        double w = 1/i.GetError()/i.GetError();
        numer += (w*i.GetValue());
        denom += w;

    }


    Double_e temp(numer/denom, sqrt(1/denom));


    return temp;



}





Double_e VarWeightedMean(const deque<Double_e>& v){

    double numer = 0;
    double denom = 0;


    for(const Double_e& i : v){

        double w = 1/i.GetError()/i.GetError();
        numer += (w*i.GetValue());
        denom += w;

    }


    Double_e temp(numer/denom, sqrt(1/denom));


    return temp;



}





Double_e VarWeightedStdDev(const vector<Double_e>& v){

    Double_e sum_wd(0,0);
    double sum_w = 0;
    const Double_e mean = VarWeightedMean(v);


    for(const Double_e& i : v){

        double w = 1/i.GetError()/i.GetError();
        sum_wd += (w*(i-mean)*(i-mean));
        sum_w += w;

    }


    const double frac = double(v.size()-1)/double(v.size());
    Double_e temp = sqrt(sum_wd/(sum_w*frac));


    return temp;



}





Double_e VarWeightedStdDev(const deque<Double_e>& v){

    Double_e sum_wd(0,0);
    double sum_w = 0;
    const Double_e mean = VarWeightedMean(v);


    for(const Double_e& i : v){

        double w = 1/i.GetError()/i.GetError();
        sum_wd += (w*(i-mean)*(i-mean));
        sum_w += w;

    }


    const double frac = double(v.size()-1)/double(v.size());
    Double_e temp = sqrt(sum_wd/(sum_w*frac));


    return temp;



}




#endif

        
        
