#include "phone_number.h"
#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

bool ifBack(string str)
{
    for(int i=0; i<str.length();i++)
    {
        if(str[i]==' ')
        {
            return false;
        }
    }
    return true;
}

PhoneNumber :: PhoneNumber(const string &international_number){
    istringstream number(international_number);
    bool ok = true;



    ok = ok && (number.peek() == '+');
    number.ignore(1);
    if (!ok){
        throw invalid_argument("no +");
    }

    ok = ok && (getline(number, country_code_, '-'));
    if (!ok){
        throw invalid_argument("Wrong number format: " + country_code_);
    }

    ok = ok && (getline(number, city_code_, '-'));
    if (!ok ||city_code_.size() == 0){
        throw invalid_argument("Wrong number format: " + city_code_);
    }

    ok = ok && (number >> local_number_);

    if (!ok){
      throw invalid_argument("Wrong number format: " + local_number_);
    }
}

string PhoneNumber :: GetCountryCode() const{
    return country_code_;
}
string PhoneNumber :: GetCityCode() const{
    return city_code_;
}
string PhoneNumber :: GetLocalNumber() const{
    return local_number_;
}
string PhoneNumber :: GetInternationalNumber() const{
    return '+' + GetCountryCode() + '-' + GetCityCode() + '-' + GetLocalNumber();
}
