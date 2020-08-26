#include "airline_ticket.h"
#include "test_runner.h"

#include <iomanip>

using namespace std;

#define UPDATE_FIELD(ticket, field, values) \
  {auto it = values.find(#field);             \
  if (it != values.end()) {                \
    istringstream is(it->second);           \
    is >> ticket.field;                     \
  }}                                        \

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time


istream& operator>>(istream& ssin, Date& date) {
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
                        date=Date{year,month,day};
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

istream& operator>>(istream& ssin, Time& time) {
    if(ssin) {
        int hour, minute;
        char ch;
        string s;
        ssin >> s;
        stringstream stream(s);
        if((stream >> hour)&&(stream >> ch)&&(stream >> minute))
        {
            if(ch == ':')
            {
                time = Time{hour, minute};
            }
        }
    }
    return ssin;
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

bool operator<(const Date& left, const Date& right) {
    if(left.year<right.year){
        return true;
    }else{if((left.month<right.month)&&(left.year==right.year)){
            return true;
        }else{if((left.day<right.day)&&(left.year==right.year)&&(left.month==right.month)){
                return true;
            }else{return false;}
        }
    }
}

bool operator==(const Date& left, const Date& right) {
    if((left.year==right.year)&&(left.month==right.month)&&(left.day==right.day))
    {
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setfill('0');
    stream << setw(4) << date.year << "-" << setw(2) << date.month << "-" << setw(2) << date.day;
    return stream;
}

bool operator<(const Time& left, const Time& right) {
    if(left.hours<right.hours) {
        return true;
    } else {
        if((left.minutes<right.minutes)&&(left.hours==right.hours)) {
            return true;
        } else {
            return false;
        }
    }
}

bool operator==(const Time& left, const Time& right) {
    if((left.hours==right.hours)&&(left.minutes==right.minutes))
    {
        return true;
    } else {
        return false;
    }
}

ostream& operator<<(ostream& stream, const Time& time) {
    stream << setfill('0');
    stream << setw(2) << time.hours << "-" << setw(2) << time.minutes;
    return stream;
}


int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
