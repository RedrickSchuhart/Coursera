#include <iostream>
#include <math.h>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <exception>
using namespace std;

class Rational {
public:
    Rational() {
        p=0;
        q=1;
    }
    Rational(int numerator, int denominator) {
        if(denominator==0)
        {
            stringstream ss;
            ss <<  "invalid_argument";
            throw invalid_argument(ss.str());
        }
        if(denominator<0)
        {
            numerator=-numerator;denominator=-denominator;
        }
        int nod = Nod(abs(numerator),abs(denominator));
        p=numerator/nod;
        q=denominator/nod;
    }
    int Nod(int a, int b) {
        if (!((a>0)&&(b>0)))
        {
            return a+b;
        }
        if (a > b)
            a = a % b;
        else
            b = b % a;
        return Nod(a, b);
    }
    int Numerator() const {
        return p;
    }
    int Denominator() const {
        return q;
    }
private:
    int p, q;
};

ostream& operator<<(ostream& stream, const Rational& number) {
    stream << number.Numerator() << "/" << number.Denominator();
    return stream;
}

istream& operator>>(istream& stream, Rational& number) {
    if(stream) {
        int p, q;
        char ch;
        if((stream >> p)&&(stream >> ch)&&(stream >> q)&&(ch=='/'))
        {number=Rational(p,q);} 
        //else {stream=false}
        /*stream >> p;
        stream.ignore(1);
        stream >> q;
        stream.ignore(1);*/
        //number=Rational(p,q);
    }
    return stream;
}

Rational operator+(Rational left, Rational right) {
    return Rational(left.Numerator()*right.Denominator()+right.Numerator()*left.Denominator(),
                    left.Denominator()*right.Denominator());
}

Rational operator-(Rational left, Rational right) {
    return Rational(left.Numerator()*right.Denominator()-right.Numerator()*left.Denominator(),
                    left.Denominator()*right.Denominator());
}

Rational operator*(Rational left, Rational right) {
    return Rational(left.Numerator()*right.Numerator(), left.Denominator()*right.Denominator());
}

Rational operator/(Rational left, Rational right) {
    if(right.Numerator()==0)
    {
        stringstream ss;
        ss <<  "domain_error";
        throw domain_error(ss.str());
    }
    return Rational(left.Numerator()*right.Denominator(), left.Denominator()*right.Numerator());
}

bool operator==(Rational left, Rational right) {
    if((left.Numerator()*right.Denominator())==(right.Numerator()*left.Denominator()))
    {return true;} else{return false;}
}

bool operator<(Rational left, Rational right) {
    if((left.Numerator()*right.Denominator())<(right.Numerator()*left.Denominator()))
    {return true;} else{return false;}
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;
    return 0;
}
