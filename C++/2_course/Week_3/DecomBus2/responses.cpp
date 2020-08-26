#include <iostream>
#include "responses.h"

using namespace std;

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(r.f==false){
        os << "No stop";
    } else {
        for (const string& bus : r.buses) {
          os << bus << " ";
        }
    }
  return os;
}

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(r.f==false){
        os << "No bus";
    } else
    {
        int i = 0;
        for (const auto& stop : r.stops){
          os << "Stop " << stop.first << ": ";
          if (stop.second.empty()) {
              os << "no interchange";
          } else {
              for (const string& bus : stop.second) {
                  os << bus << " ";
            }
          }
          i++;
          if(i!=r.stops.size())
              os << endl;
        }
    }
  return os;
}

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
      os << "No buses";
    } else {
      int i = 0;
      for (const auto& bus_item : r.buses_to_stops) {
        os << "Bus " << bus_item.first << ": ";
        for (const string& stop : bus_item.second) {
          os << stop << " ";
        }
        i++;
        if(i!=r.buses_to_stops.size()) {
            os << endl;
        }
      }
    }
    return os;
}
