#include "bus_manager.h"

using namespace std;

void BusManager::AddBus(const string& bus, const vector<string>& stops) {
    buses_to_stops[bus] = stops;
    for (string stop : stops) {
      stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const {
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const {
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

AllBusesResponse BusManager::GetAllBuses() const {
    AllBusesResponse a;
    a.buses_to_stops = buses_to_stops;
    return a;
}
