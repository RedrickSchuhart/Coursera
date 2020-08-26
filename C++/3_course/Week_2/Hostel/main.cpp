#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <utility>
#include <test_runner.h>

using namespace std;



class HotelManager {
public:
  HotelManager() {}
  void Book(long long int now, string hotel_name, int client_id, long int room_count) {
      persons_hotel[hotel_name][client_id] = now;
      count_persons_hotel[hotel_name].push_back(pair<int, long long int>(client_id, now));
      count_room_per_hotel[hotel_name].push_back(pair<int, long long int>(room_count, now));
      time = now;
      if(count_room_hotel.find(hotel_name) != count_room_hotel.end()){
          count_room_hotel[hotel_name] = count_room_hotel[hotel_name] + room_count;
      } else {
          count_room_hotel[hotel_name] = room_count;
      }
      //Update(hotel_name);
  }
  int Clients(string hotel_name) {
      Update(hotel_name);
      auto it = persons_hotel.find(hotel_name);
      if(it == persons_hotel.end()) {
          return 0;
      } else {
          return (*it).second.size();
      }
  }
  long long int Rooms(string hotel_name) {
      Update(hotel_name);
      auto it = count_room_hotel.find(hotel_name);
      if(it == count_room_hotel.end()) {
          return 0;
      } else {
          return (*it).second;
      }
  }

private:
  void Update(string hotel_name) {
      while((count_room_per_hotel[hotel_name].size() != 0)&&(count_room_per_hotel[hotel_name].front().second <= time - 86400)) {
              count_room_hotel[hotel_name] = count_room_hotel[hotel_name] - count_room_per_hotel[hotel_name].front().first;
              count_room_per_hotel[hotel_name].pop_front();
              if(count_persons_hotel[hotel_name].front().second == persons_hotel[hotel_name][count_persons_hotel[hotel_name].front().first])
                  persons_hotel[hotel_name].erase(count_persons_hotel[hotel_name].front().first);
              count_persons_hotel[hotel_name].pop_front();

      }
  }
  long long int time;
  map<string, long long int> count_room_hotel;
  map<string, deque<pair<int, long long int>>> count_room_per_hotel;
  map<string, deque<pair<int, long long int>>> count_persons_hotel;
  map<string, map<long int, long long int>> persons_hotel;
};


void TestReadPage() {
    { /*11
        CLIENTS Marriott
        ROOMS Marriott
        BOOK 10 FourSeasons 1 2
        BOOK 10 Marriott 1 1
        BOOK 86409 FourSeasons 2 1
        CLIENTS FourSeasons
        ROOMS FourSeasons
        CLIENTS Marriott
        BOOK 86410 Marriott 2 10
        ROOMS FourSeasons
        ROOMS Marriott*/
        HotelManager manager;
        ASSERT_EQUAL(manager.Clients("Marriott"), 0);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 0);
        manager.Book(10, "FourSeasons", 1, 2);
        manager.Book(10, "Marriott", 1, 1);
        manager.Book(86409, "FourSeasons", 2, 1);
        ASSERT_EQUAL(manager.Clients("FourSeasons"), 2);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 3);
        ASSERT_EQUAL(manager.Clients("Marriott"), 1);
        manager.Book(86410, "Marriott", 2, 10);
        ASSERT_EQUAL(manager.Rooms("FourSeasons"), 1);
        ASSERT_EQUAL(manager.Rooms("Marriott"), 10);
    }
    { //two hotel
        HotelManager manager;
        manager.Book(10, "1", 1, 2);
        manager.Book(10, "1", 2, 1);
        manager.Book(86409, "1", 2, 5);
        ASSERT_EQUAL(manager.Rooms("1"), 8);
        ASSERT_EQUAL(manager.Clients("1"), 2);
        manager.Book(186410, "2", 2, 10);
        ASSERT_EQUAL(manager.Rooms("1"), 0);
        ASSERT_EQUAL(manager.Clients("1"), 0);
        ASSERT_EQUAL(manager.Rooms("2"), 10);
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TestReadPage();
    HotelManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
      string query_type;
      cin >> query_type;

      if (query_type == "BOOK") {
          long long int time;
          cin >> time;
          string hotel_name;
          cin >> hotel_name;
          int client_id;
          cin >> client_id;
          long int room_count;
          cin >> room_count;
          manager.Book(time, hotel_name, client_id, room_count);
      } else {
          if (query_type == "CLIENTS") {
              string hotel_name;
              cin >> hotel_name;
              cout << setprecision(6) << manager.Clients(hotel_name) << "\n";
          } else {
              if (query_type == "ROOMS") {
                  string hotel_name;
                  cin >> hotel_name;
                  cout << setprecision(6) << manager.Rooms(hotel_name) << "\n";
              }
          }
      }
    }

    return 0;
}
