#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
    int q;
    map<string, string> cap_country;
    cin >> q;
    for(int i=0; i<q; i++)
    {
        string operation_code;
        cin >> operation_code;
        if (operation_code == "CHANGE_CAPITAL") {
            string country, new_capital;
            cin >> country >> new_capital;
            if(cap_country.count(country)==0) {
                cout << "Introduce new country " << country << " with capital " << new_capital << endl;
            } else {
                if(cap_country[country] == new_capital) {
                    cout << "Country " << country << " hasn't changed its capital" << endl;
                } else {
                    cout << "Country " << country << " has changed its capital from " << cap_country[country] << " to " << new_capital << endl;
                }
            }
            cap_country[country] = new_capital;
        } else {
            if(operation_code == "RENAME") {
                string old_country_name, new_country_name;
                cin >> old_country_name >> new_country_name;
                cap_country[new_country_name] = cap_country[old_country_name];
                cap_country.erase(old_country_name);
            } else {
                if(operation_code == "ABOUT") {
                    string country;
                    cin >> country;
                    cout << cap_country[country] << endl;
                } else {
                    for(const auto& item:cap_country)
                    {
                        cout << item.first << "/" << item.second << " ";
                    }
                }
            }
        }
    }

    return 0;
}
