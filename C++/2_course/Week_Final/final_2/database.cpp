#include "database.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

int Database::RemoveIf(const function<bool(const Date& date, const string& event)> predicate){
    int count=0;
    /*for(auto& item:base)
    {
        Date date = item.first;
        auto it = stable_partition(item.second.begin(), item.second.end(), [predicate, date](const string& event) {
            return !predicate(date, event);
          });
        if (it == item.second.begin()) {
            count += (item.second.end()-it);
            base.erase(date);
        } else {
            count += (item.second.end()-it);
            item.second.erase(it, item.second.end());
        }
    }*/
    for (auto item=base.begin(); item!=base.end();){
        Date date = (*item).first;
        auto it = stable_partition((*item).second.begin(), (*item).second.end(), [predicate, date](const string& event) {
            return !predicate(date, event);
          });
        if (it == (*item).second.begin()) {
            base_s[(*item).first] = set<string>();
            count += ((*item).second.end()-it);
            base.erase(item++);
        } else {
            count += ((*item).second.end()-it);
            (*item).second.erase(it, (*item).second.end());
            base_s[(*item).first] = set<string>((*item).second.begin(), (*item).second.end());
            item++;
        }
    }
    return count;
}


vector<pair<Date,string>> Database::FindIf(const function<bool(const Date& date, const string& event)> predicate) const{
    string date_;
    Date date;
    vector<string> events;
    vector<pair<Date,string>> finish;
    /*for(auto& item:base)
    {
        date = item.first;
        events = item.second;
        auto it = stable_partition(events.begin(), events.end(), [predicate, date](const string& event) {
            return predicate(date, event);
          });
        date_ = date.DateToString();
        for (auto i = events.begin(); i<it; i++)
        {
            finish.push_back(date_ + " " + (*i));
        }
    }*/
    for(auto& item:base){
        for(auto& event:item.second){
            if(predicate(item.first, event))
                finish.push_back(pair<Date,string>(item.first, event));
        }
    }
    return finish;
}

pair<Date,string> Database::Last(const Date& date) const{
    /*auto it = find_if(base.begin(), base.end(), [date](pair<Date, vector<string>> pair_) {
            return pair_.first > date;
      });*/
    //string date_;
    pair<Date,string> event;

    auto it = base.upper_bound(date);
    if(it == base.begin())
    {
        throw invalid_argument("empty");
    } else {
        it--;
        //date_ = (*it).first.DateToString();
        //event = date_ + " " + (*it).second.back();
        event = pair<Date,string>((*it).first, (*it).second.back());
    }
    return event;
}


void Database::Add(const Date& date, const string& event){
    if((base_s[date].find(event)==end(base_s[date]))&&(!event.empty())){
        base[date].push_back(event);
        base_s[date].insert(event);
    }
}

map<Date,vector<string>> Database::GetBase() const{
    return base;
}

void Database::Print(ostream& stream) const{
    for(const auto& item:base)
        if(!item.second.empty())
            for(const auto& event:item.second)
                stream << item.first << " " << event << endl;
}

const string ParseEvent(istream& is){
  string line;
  getline(is, line);
  auto it = find_if(begin(line), end(line),[](char& ch){return !(ch==' ');});
  line = string(it, end(line));
  return line;
}


ostream& operator<<(ostream& stream, const pair<Date, string> event) {
    stream << event.first << " " << event.second;
    return stream;
}

