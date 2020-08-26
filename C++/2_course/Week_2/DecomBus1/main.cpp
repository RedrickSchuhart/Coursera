#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    cin >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        int stop_count;
        cin >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
          cin >> stop;
        }

    } else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;

    } else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;

    } else if (operation_code == "ALL_BUSES") {
        q.type = QueryType::AllBuses;

    }
  return is;
}

struct BusesForStopResponse {
  bool f=true;
  vector<string> buses;
};

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

struct StopsForBusResponse {
    bool f=true;
    vector<pair<string, vector<string>>> stops;
};

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

struct AllBusesResponse {
  map<string, vector<string>> buses_to_stops;
};

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

class BusManager {
public:
  void AddBus(const string& bus, const vector<string>& stops) {
      buses_to_stops[bus] = stops;
      for (string stop : stops) {
        stops_to_buses[stop].push_back(bus);
      }
  }

  BusesForStopResponse GetBusesForStop(const string& stop) const {
      BusesForStopResponse buses;
      if (stops_to_buses.count(stop) == 0) {
          buses.f = false;
      } else {
          for (const string& bus : stops_to_buses.at(stop)) {
              buses.buses.push_back(bus);
          }
      }
      return buses;
  }

  StopsForBusResponse GetStopsForBus(const string& bus) const {
      StopsForBusResponse stops;
      if (buses_to_stops.count(bus) == 0) {
          stops.f = false;
      } else {
        for (const string& stop : buses_to_stops.at(bus)) {
            vector<string> buss;
            for (const string& other_bus : stops_to_buses.at(stop)) {
              if (bus != other_bus) {
                buss.push_back(other_bus);
              }
            }
            pair<string, vector<string>> p(stop, buss);
            stops.stops.push_back(p);
        }
      }
      return stops;
  }

  AllBusesResponse GetAllBuses() const {
      AllBusesResponse a;
      a.buses_to_stops = buses_to_stops;
      return a;
  }
  map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
