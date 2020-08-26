#include <iostream>
#include <exception>
#include <math.h>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <system_error>
#include <iomanip>
using namespace std;

class Date {
public:
    Date(){
        year=0;
        month=0;
        day=0;
    }
    Date(int NewYear, int NewMonth, int NewDay){
        year=NewYear;
        month=NewMonth;
        day=NewDay;
    }
    int GetYear() const{
        return year;
    }
    int GetMonth() const{
        return month;
    }
    int GetDay() const{
        return day;
    }
private:
  int year;
  int month;
  int day;
};


bool operator<(const Date& left, const Date& right) {
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
ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0');
    stream << setw(4) << date.GetYear() << "-" << setw(2) << date.GetMonth() << "-" << setw(2) << date.GetDay();
    return stream;
}
istream& operator>>(istream& ssin, Date& date) {
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
}


class Database {
public:
    void AddEvent(const Date& date, const string& event){
        base[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event){
        if(base[date].count(event)!=0){
            cout << "Deleted successfully" << endl;
            base[date].erase(event);
            return true;
        }else{
            cout << "Event not found" << endl;
            return false;
        }
    }
    int  DeleteDate(const Date& date){
        int N = base[date].size();
        cout << "Deleted " << N << " events" << endl;
        base.erase(date);
        return N;
    }
    map<Date,set<string>> GetBase(){
        return base;
    }

    void Find(const Date& date){
        if(!base[date].empty())
        {
            for(const auto& event:base[date]){
                cout << event << endl;
            }
        }
    }

  void Print() const;
private:
  map<Date,set<string>> base;
};

int main() {
  try{
  Database db;
  string command, request;
  while ((getline(cin, request))) {
      if(!request.empty()){
      stringstream stream(request);
      stream >> command;
      //cout << cin.peek() << endl;
      //cout << stream.peek() << endl;
      if(command=="Add"){
          try{
          string event;
          Date date;
          stream >> date >> event;
          db.AddEvent(date, event);}
          catch (exception& ex) {
              cout << ex.what();
          }
      }else{
          if(command=="Del"){
              try {
              string event;
              Date date;
              stream >> date >> event;
              if(event.empty())
              {
                  db.DeleteDate(date);
              }else{
                  db.DeleteEvent(date, event);
              }
              } catch (exception& ex) {
              cout << ex.what();
              }
          }else{
              if(command=="Find"){
                  try {
                  Date date;
                  stream >> date;
                  db.Find(date);
                  } catch (exception& ex) {
                  cout << ex.what();
                  }
              }else{
                  if(command=="Print"){
                      for(const auto& item:db.GetBase())
                          if(!item.second.empty())
                          for(const auto& event:item.second){
                              cout << item.first << " " << event << endl;
                          }
                  }else{
                      stringstream ss;
                      ss << "Unknown command: " << command << endl;
                      throw runtime_error(ss.str());
                  }
              }
          }}
      }
  }
  } catch (exception& ex) {
    cout << ex.what();
  }
  return 0;
}
