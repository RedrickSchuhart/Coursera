#pragma once
#include <string>
#include <map>
#include "node.h"
#include "date.h"
#include <vector>
#include <functional>
#include <set>

class Database {
public:
    void Add(const Date& date, const string& event);
    map<Date,vector<string>> GetBase() const;
    int RemoveIf(const function<bool(const Date& date, const string& event)> predicate);
    vector<pair<Date,string>> FindIf(const function<bool(const Date& date, const string& event)> predicate) const;
    pair<Date,string> Last(const Date& date) const;
    void Print(ostream& stream) const;
private:
  map<Date,vector<string>> base;
  map<Date,set<string>> base_s;
};

ostream& operator<<(ostream& stream, const pair<Date, string> events);


const string ParseEvent(istream& is);
