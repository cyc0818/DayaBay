#ifndef Uncertainty_h
#define Uncertainty_h

#include <cmath>
#include <iostream>


using namespace std;


class Uncertainty{

    public : 

        explicit Uncertainty(const double& value = 0, const double& error = 0) : m_v(value), m_e(error){}


        void SetValue(const double& value){ m_v = value;}
        void SetError(const double& error){ m_e = error;}
        void SetBoth(const double& value, const double& error){
            m_v = value;
            m_e = error;
        }


        double GetValue() const { return m_v; }
        double GetError() const { return m_e; }
        void Print() const { cout << m_v << " +/- " << m_e << endl; }


        Uncertainty operator+(const double& x) const;
        Uncertainty operator-(const double& x) const;
        Uncertainty operator*(const double& x) const;
        Uncertainty operator/(const double& x) const;


        Uncertainty operator+(const Uncertainty& x) const;
        Uncertainty operator-(const Uncertainty& x) const;
        Uncertainty operator*(const Uncertainty& x) const;
        Uncertainty operator/(const Uncertainty& x) const;


        Uncertainty& operator+=(const double& x);
        Uncertainty& operator-=(const double& x);
        Uncertainty& operator*=(const double& x);
        Uncertainty& operator/=(const double& x);


        Uncertainty& operator+=(const Uncertainty& x);
        Uncertainty& operator-=(const Uncertainty& x);
        Uncertainty& operator*=(const Uncertainty& x);
        Uncertainty& operator/=(const Uncertainty& x);


        friend Uncertainty sqrt(const Uncertainty& x);
        friend Uncertainty exp(const Uncertainty& x);
        friend Uncertainty log(const Uncertainty& x);
        friend Uncertainty sin(const Uncertainty& x);
        friend Uncertainty cos(const Uncertainty& x);
        friend Uncertainty tan(const Uncertainty& x);


        friend Uncertainty operator+(const double& a, const Uncertainty& x);
        friend Uncertainty operator-(const double& a, const Uncertainty& x);
        friend Uncertainty operator*(const double& a, const Uncertainty& x);
        friend Uncertainty operator/(const double& a, const Uncertainty& x);
        friend ostream& operator<<(ostream& os, const Uncertainty& x);


        friend Uncertainty Poisson(int n, const Uncertainty& x);


    private :

        double m_v;
        double m_e;


};



Uncertainty Uncertainty::operator+(const double& x) const{

    Uncertainty temp;


    temp.m_v = m_v + x;
    temp.m_e = m_e;


    return temp;


}




Uncertainty Uncertainty::operator+(const Uncertainty& x) const{

    Uncertainty temp;

    
    temp.m_v = m_v + x.m_v;
    temp.m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return temp;

}




Uncertainty Uncertainty::operator-(const double& x) const{

    Uncertainty temp;


    temp.m_v = m_v - x;
    temp.m_e = m_e;


    return temp;


}





Uncertainty Uncertainty::operator-(const Uncertainty& x) const{

    Uncertainty temp;

    
    temp.m_v = m_v - x.m_v;
    temp.m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return temp;

}





Uncertainty Uncertainty::operator*(const double& x) const{

    Uncertainty temp;


    temp.m_v = m_v * x;
    temp.m_e = m_e * abs(x);


    return temp;

}




Uncertainty Uncertainty::operator*(const Uncertainty& x) const{

    Uncertainty temp;


    temp.m_v = m_v * x.m_v;
    if(temp.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));


    return temp;

}





Uncertainty Uncertainty::operator/(const double& x) const{

    Uncertainty temp;


    if(x){
        temp.m_v = m_v / x;
        temp.m_e = m_e / abs(x);
    }


    return temp;

}





Uncertainty Uncertainty::operator/(const Uncertainty& x) const{

    Uncertainty temp;


    if(x.m_v) temp.m_v = m_v / x.m_v;
    if(m_v and x.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));


    return temp;

}




Uncertainty& Uncertainty::operator+=(const double& x){

    m_v = m_v + x;

    return *this;

}




Uncertainty& Uncertainty::operator-=(const double& x){

    m_v = m_v - x;

    return *this;

}





Uncertainty& Uncertainty::operator*=(const double& x){

    m_v = m_v * x;
    m_e = m_e * abs(x);

    return *this;

}




Uncertainty& Uncertainty::operator/=(const double& x){

    if(x){
        m_v = m_v / x;
        m_e = m_e / abs(x);
    }

    return *this;

}





Uncertainty& Uncertainty::operator+=(const Uncertainty& x){

    m_v = m_v + x.m_v;
    m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return *this;

}




Uncertainty& Uncertainty::operator-=(const Uncertainty& x){

    m_v = m_v - x.m_v;
    m_e = sqrt(m_e*m_e + x.m_e*x.m_e);


    return *this;

}



Uncertainty& Uncertainty::operator*=(const Uncertainty& x){

    Uncertainty temp;


    temp.m_v = m_v * x.m_v;
    if(temp.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));
    *this = temp;


    return *this;

}




Uncertainty& Uncertainty::operator/=(const Uncertainty& x){

    Uncertainty temp;


    if(x.m_v) temp.m_v = m_v / x.m_v;
    if(m_v and x.m_v) temp.m_e = abs(temp.m_v) * sqrt(pow(m_e/m_v,2) + pow(x.m_e/x.m_v,2));
    *this = temp;


    return *this;

}





Uncertainty sqrt(const Uncertainty& x){

    if(x.m_v <= 0) return Uncertainty(0,0);


    Uncertainty temp;


    temp.m_v = sqrt(x.m_v); 
    temp.m_e = x.m_e/2/temp.m_v;


    return temp;


}




Uncertainty exp(const Uncertainty& x){

    Uncertainty temp;


    temp.m_v = exp(x.m_v);
    temp.m_e = temp.m_v * x.m_e;


    return temp;


}




Uncertainty log(const Uncertainty& x){

    Uncertainty temp;


    if(x.m_v){
        temp.m_v = log(x.m_v);
        temp.m_e = abs(x.m_e/x.m_v);
    }


    return temp;


}




Uncertainty sin(const Uncertainty& x){

    Uncertainty temp;


    temp.m_v = sin(x.m_v);
    temp.m_e = cos(x.m_v) * x.m_e;


    return temp;


}





Uncertainty cos(const Uncertainty& x){

    Uncertainty temp;


    temp.m_v = cos(x.m_v);
    temp.m_e = sin(x.m_v) * x.m_e;


    return temp;


}





Uncertainty tan(const Uncertainty& x){

    Uncertainty temp;


    temp.m_v = tan(x.m_v);
    temp.m_e = x.m_e / cos(x.m_v) / cos(x.m_v);


    return temp;


}




Uncertainty operator+(const double& a, const Uncertainty& x){

    return x+a;

}




Uncertainty operator-(const double& a, const Uncertainty& x){

    Uncertainty temp(x);

    temp.m_v = a - x.m_v;

    
    return temp;


}




Uncertainty operator*(const double& a, const Uncertainty& x){

    return x*a;

}




Uncertainty operator/(const double& a, const Uncertainty& x){

    Uncertainty temp;

    if(x.m_v){
        temp.m_v = a / x.m_v;
        temp.m_e = abs(a*x.m_e) / (x.m_v * x.m_v);
    }

    
    return temp;


}




ostream& operator<<(ostream& os, const Uncertainty& x){

    os << x.m_v << " +/- " << x.m_e;


    return os;


}


Uncertainty Poisson(int n, const Uncertainty& x){

    if(n < 0) return Uncertainty(0,0);
    else{

        Uncertainty temp(1,0);
        double fact = 1;
        for(int i = n; i>0; i--){
            temp *= x;
            fact *= i;
        }


        return temp*exp(-1.*x)/fact;


    }



}




Uncertainty VarWeightedMean(const vector<Uncertainty>& v){

    double numer = 0;
    double denom = 0;


    for(const Uncertainty& i : v){

        double w = 1/i.GetError()/i.GetError();
        numer += (w*i.GetValue());
        denom += w;

    }


    Uncertainty temp(numer/denom, sqrt(1/denom));


    return temp;



}





Uncertainty VarWeightedMean(const deque<Uncertainty>& v){

    double numer = 0;
    double denom = 0;


    for(const Uncertainty& i : v){

        double w = 1/i.GetError()/i.GetError();
        numer += (w*i.GetValue());
        denom += w;

    }


    Uncertainty temp(numer/denom, sqrt(1/denom));


    return temp;



}





Uncertainty VarWeightedStdDev(const vector<Uncertainty>& v){

    Uncertainty sum_wd(0,0);
    double sum_w = 0;
    const Uncertainty mean = VarWeightedMean(v);


    for(const Uncertainty& i : v){

        double w = 1/i.GetError()/i.GetError();
        sum_wd += (w*(i-mean)*(i-mean));
        sum_w += w;

    }


    const double frac = double(v.size()-1)/double(v.size());
    Uncertainty temp = sqrt(sum_wd/(sum_w*frac));


    return temp;



}





Uncertainty VarWeightedStdDev(const deque<Uncertainty>& v){

    Uncertainty sum_wd(0,0);
    double sum_w = 0;
    const Uncertainty mean = VarWeightedMean(v);


    for(const Uncertainty& i : v){

        double w = 1/i.GetError()/i.GetError();
        sum_wd += (w*(i-mean)*(i-mean));
        sum_w += w;

    }


    const double frac = double(v.size()-1)/double(v.size());
    Uncertainty temp = sqrt(sum_wd/(sum_w*frac));


    return temp;



}




#endif

        
        
