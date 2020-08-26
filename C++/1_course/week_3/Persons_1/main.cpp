#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

struct names{
    string name;
    int year;
};

bool Check(names a, names b) {return a.year<b.year;}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
      first.push_back({first_name, year});
    // добавить факт изменения имени на first_name в год year
  }
  void ChangeLastName(int year, const string& last_name) {
      sec.push_back({last_name, year});
    // добавить факт изменения фамилии на last_name в год year
  }
  string GetFullName(int year) {
      sort(begin(first), end(first), Check);
      sort(begin(sec), end(sec), Check);
      string f_name, s_name;
      bool f=false, s=false;
      int i=0;
      while ((first.size()>i)&&(first[i].year<=year))
      {
          f_name = first[i].name;
          i++;
          f=true;
      }
      i=0;
      while ((sec.size()>i)&&(sec[i].year<=year))
      {
          s_name = sec[i].name;
          i++;
          s=true;
      }
      if(f==false)
      {
          if(s==false)
              return "Incognito";
          return s_name + " with unknown first name";
      }
      if(s==false)
          return f_name + " with unknown last name";
      return f_name + " " + s_name;
    // получить имя и фамилию по состоянию на конец года year
  }
private:
  vector<names> first;
  vector<names> sec;
  // приватные поля
};


int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    cout << person.GetFullName(1964) << endl;
    cout << person.GetFullName(1966) << endl;

    return 0;
}
