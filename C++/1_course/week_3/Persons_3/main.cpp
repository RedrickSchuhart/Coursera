#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

string PrintNames(vector<string> names)
{
    string str;
    reverse(begin(names), end(names));
    str = names[0];
    if(names.size()>1)
    {
        str+= " (" + names[1];
        if(names.size()>2)
            for(int i=2; i<names.size(); i++)
            {
                str+= ", " + names[i];
            }
        str+= ")";
    }
    return str;
}

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

vector<string> FindNamesByYear(const map<int, string>& names, int year) {
  vector<string> name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year){
            if(name.empty()){name.push_back(item.second);}
            else{if(item.second!=name.back()) name.push_back(item.second);}
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

class Person {
public:
  Person(const string& first_name, const string& last_name, int year)
  {
      birth = year;
      first_names[year] = first_name;
      last_names[year] = last_name;
  }
  void ChangeFirstName(int year, const string& first_name) {
    if(year>=birth){first_names[year] = first_name;}
  }
  void ChangeLastName(int year, const string& last_name) {
    if(year>=birth){last_names[year] = last_name;}
  }
  string GetFullName(int year) const{
      if(year<birth)
      {
          return "No person";
      }else{
          // получаем имя и фамилию по состоянию на год year
          const string first_name = FindNameByYear(first_names, year);
          const string last_name = FindNameByYear(last_names, year);

          // если и имя, и фамилия неизвестны
          if (first_name.empty() && last_name.empty()) {
            return "Incognito";

          // если неизвестно только имя
          } else if (first_name.empty()) {
            return last_name + " with unknown first name";

          // если неизвестна только фамилия
          } else if (last_name.empty()) {
            return first_name + " with unknown last name";

          // если известны и имя, и фамилия
          } else {
            return first_name + " " + last_name;
          }
      }

  }
  string GetFullNameWithHistory(int year) const{
      if(year<birth)
      {
          return "No person";
      }else{
          const vector<string> first_name = FindNamesByYear(first_names, year);
          const vector<string> last_name = FindNamesByYear(last_names, year);
          string first, second;
          if (first_name.empty() && last_name.empty()) {
            return "Incognito";

          // если неизвестно только имя
          } else if (first_name.empty()) {
            return PrintNames(last_name) + " with unknown first name";

          // если неизвестна только фамилия
          } else if (last_name.empty()) {
            return PrintNames(first_name) + " with unknown last name";

          // если известны и имя, и фамилия
          } else {
            return  PrintNames(first_name) + " " + PrintNames(last_name);
          }
          // получить все имена и фамилии по состоянию на конец года year
      }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
  int birth;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
