#include "date.h"
#include <iostream>
#include <iomanip>

using namespace std;

Date::Date(){
    year=0;
    month=0;
    day=0;
}

Date::Date(int NewYear, int NewMonth, int NewDay){
    year=NewYear;
    month=NewMonth;
    day=NewDay;
}

int Date::GetYear() const{
    return year;
}
int Date::GetMonth() const{
    return month;
}
int Date::GetDay() const{
    return day;
}



const bool operator<(const Date& left, const Date& right) {
    if(left.GetYear()<right.GetYear()){
        return true;
    }else{if((left.GetMonth()<right.GetMonth())&&(left.GetYear()==right.GetYear())){
            return true;
        }else{if((left.GetDay()<right.GetDay())&&(left.GetYear()==right.GetYear())&&(left.GetMonth()==right.GetMonth())){
                return true;
            }else{return false;}
        }
    }
}

const bool operator==(const Date& left, const Date& right) {
    if((left.GetYear()==right.GetYear())&&(left.GetMonth()==right.GetMonth())&&(left.GetDay()==right.GetDay()))
    {
        return true;
    } else {
        return false;
    }
}

const bool operator<=(const Date& left, const Date& right) {
    if((left<right)||(left==right)){
        return true;
    } else {
        return false;
    }
}

const bool operator>(const Date& left, const Date& right) {
    return !(left<=right);
}

const bool operator>=(const Date& left, const Date& right) {
    return !(left<right);
}

const bool operator!=(const Date& left, const Date& right) {
    return !(left==right);
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0');
    stream << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return stream;
}

/*istream& operator>>(istream& ssin, Date& date) {
    if(ssin) {
        int day, month, year;
        char ch1, ch2;
        string s;
        ssin >> s;
        stringstream stream(s);
        if((stream >> year)&&(stream >> ch1)&&(stream >> month)&&(stream >> ch2)&&
                (stream >> day)&&(stream.peek()==-1))
        {
            //cout << stream.peek() << endl;
            if((ch1=='-')&&(ch2=='-')){
                if((month>0)&&(month<13)){
                    if((day>0)&&(day<32)){
                        date=Date(year,month,day);
                    }else{
                        stringstream ss;
                        ss << "Day value is invalid: " << day << endl;
                        throw runtime_error(ss.str());
                    }
                }else{
                    stringstream ss;
                    ss << "Month value is invalid: " << month << endl;
                    throw runtime_error(ss.str());
                }
            }else{
                stringstream ss;
                ss << "Wrong date format: " << s << endl;
                throw runtime_error(ss.str());
            }
        }
        else{
            stringstream ss;
            ss << "Wrong date format: " << s << endl;
            throw runtime_error(ss.str());
        }
    }
    return ssin;
}*/

const Date ParseDate(istream& ssin){
    Date date;
    if(ssin) {
        int day, month, year;
        char ch1, ch2;
        string s;
        ssin >> s;
        stringstream stream(s);
        if((stream >> year)&&(stream >> ch1)&&(stream >> month)&&(stream >> ch2)&&
                (stream >> day))
        {
            //cout << stream.peek() << endl;
            if((ch1=='-')&&(ch2=='-')){
                if((month>0)&&(month<13)){
                    if((day>0)&&(day<32)){
                        date=Date(year,month,day);
                    }else{
                        stringstream ss;
                        ss << "Day value is invalid: " << day << endl;
                        throw runtime_error(ss.str());
                    }
                }else{
                    stringstream ss;
                    ss << "Month value is invalid: " << month << endl;
                    throw runtime_error(ss.str());
                }
            }else{
                stringstream ss;
                ss << "Wrong date format: " << s << endl;
                throw runtime_error(ss.str());
            }
        }
        else{
            stringstream ss;
            ss << "Wrong date format: " << s << endl;
            throw runtime_error(ss.str());
        }
    }
    return date;
}
