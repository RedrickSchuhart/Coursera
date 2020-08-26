#include <iostream>
#include <map>
#include <vector>
#include <string>


using namespace std;

int main()
{
    int q;
    map<string, vector<string>> buses;
    map<string, vector<string>> stations;
    cin >> q;
    for(int i=0; i<q; i++)
    {
        string operation_code;
        cin >> operation_code;
        if (operation_code == "NEW_BUS") {
            string stop, bus;
            int stop_count;
            cin >> bus;
            cin >> stop_count;
            for(int i=0; i<stop_count; i++) {
                cin >> stop;
                buses[bus].push_back(stop);
                stations[stop].push_back(bus);
            }
        } else {
            if (operation_code == "BUSES_FOR_STOP") {
                string stop;
                cin >> stop;
                if(stations.count(stop) == 0) {
                    cout << "No stop";
                } else {
                    for(const auto& bus:stations[stop])
                        cout << bus << " ";
                }
                cout << endl;
            } else {
                if (operation_code == "STOPS_FOR_BUS") {
                    string bus;
                    bool f;
                    cin >> bus;
                    if(buses.count(bus) == 0) {
                        cout << "No bus" << endl;
                    } else {
                        for(const auto& stop:buses[bus]) {
                            f = true;
                            cout << "Stop " << stop << ": ";
                            for(const auto& buss:stations[stop])
                            {
                                if(buss != bus) {
                                    f = false;
                                    cout << buss << " ";
                                }
                            }
                            if(f == true)
                                cout << "no interchange";
                            cout << endl;
                        }
                    }
                } else {
                    if(buses.size() == 0) {
                        cout << "No buses" << endl;
                    } else {
                        for(const auto& item:buses) {
                            cout << "Bus " << item.first << ": ";
                            for(const auto& stop:item.second)
                                cout << stop << " ";
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
