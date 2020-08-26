#pragma once
#include <sstream>
#include <string>

using namespace std;

class Date {
public:
    Date();
    Date(int NewYear, int NewMonth, int NewDay);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
private:
  int year;
  int month;
  int day;
};

const bool operator<(const Date& left, const Date& right);

const bool operator<=(const Date& left, const Date& right);

const bool operator==(const Date& left, const Date& right);

const bool operator>(const Date& left, const Date& right);

const bool operator>=(const Date& left, const Date& right);

const bool operator!=(const Date& left, const Date& right);

ostream& operator<<(ostream& stream, const Date& date);

//istream& operator>>(istream& ssin, Date& date);

const Date ParseDate(istream& ssin);
