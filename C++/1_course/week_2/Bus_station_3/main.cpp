#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main()
{
    int q, n, i_bus=1;
    map<set<string>, int> buses;
    cin >> q;
    for(int i=0; i<q; i++)
    {
        set<string> stations;
        string str;
        cin >> n;
        for(int num=0; num<n; num++) {
            cin >> str;
            stations.insert(str);
        }
        if(buses.count(stations)==0) {
            buses[stations] = i_bus;
            cout << "New bus " << i_bus << endl;
            i_bus++;
        } else {
            cout << "Already exists for " << buses[stations] << endl;
        }
    }
    return 0;
}
