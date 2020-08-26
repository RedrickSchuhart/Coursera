#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    int q, n_month=0, day;
    vector<int> days ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    vector<vector<string>> affs(31);
    string aff;
    cin >> q;
    for(int i=0; i<q; i++)
    {
        string operation_code;
        cin >> operation_code;
        if (operation_code == "ADD") {
            cin >> day >> aff;
            affs[day-1].push_back(aff);
        }
        else {
            if (operation_code == "NEXT") {
                n_month++;
                if(n_month==12)
                    n_month=0;
                if(days[n_month] < affs.size())
                {
                    int i = affs.size();
                    while(i>days[n_month])
                    {
                        affs[days[n_month]-1].insert(end(affs[days[n_month]-1]), begin(affs[i-1]), end(affs[i-1]));
                        //affs[days[n_month]-1] = affs[days[n_month]-1] + " " + affs[i-1];
                        i = i - 1;
                    }
                }
                affs.resize(days[n_month], vector<string>(0));
            }
            else {
                cin >> day;
                cout << affs[day-1].size();
                for(string s:affs[day-1])
                {
                    cout << ' ' << s;
                }
                cout << endl;

            }
        }
    }
    return 0;
}
