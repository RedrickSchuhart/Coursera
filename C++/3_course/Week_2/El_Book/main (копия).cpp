#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>

using namespace std;

class ReadingManager {
public:
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        count_users(0) {}

  void Read(int user_id, int page_count) {
    auto it = sorted_pages_users.lower_bound(page_count);

    if(it!=sorted_pages_users.end()){
        sorted_pages_users[page_count] = (*it).second++;
    } else {
        sorted_pages_users[page_count] = 1;
    }

    for(auto i=sorted_pages_users.begin(); i != it; i++){
        (*i).second++;
    }


    if (user_page_counts_[user_id] == 0) {
      //AddUser(user_id);
        count_users++;
    } else {
        sorted_pages_users[user_page_counts_[user_id]]--;
    }
    user_page_counts_[user_id] = page_count;
    /*user_page_counts_[user_id] = page_count;
    int& position = user_positions_[user_id];
    while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
      SwapUsers(position, position - 1);
    }*/
    cout << count_users << endl;
  }

  double Cheer(int user_id) const {
      cout << count_users << " ";
    if (user_page_counts_[user_id] == 0) {
        cout << "t0 ";
      return 0;
    }
    if (count_users == 1) {
        cout << "t1 ";
      return 1;
    }
    /*const int page_count = user_page_counts_[user_id];
    int position = user_positions_[user_id];
    while (position < user_count &&
      user_page_counts_[sorted_users_[position]] == page_count) {
      ++position;
    }
    if (position == user_count) {
        return 0;
    }*/
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    int pages = user_page_counts_[user_id];
    auto it = sorted_pages_users.find(pages);
    if(it != sorted_pages_users.end()){
        cout << "t2 users " << (*it).second - 1;
       return (((*it).second - 1) * 1.0) / (count_users - 1);
    }
  }

private:
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;

  vector<int> user_page_counts_;
  set<int> users;
  map<int, int> sorted_pages_users;
  int count_users;

  /*int GetUserCount() const {
    return sorted_users_.size();
  }
  void AddUser(int user_id) {
    sorted_users_.push_back(user_id);
    user_positions_[user_id] = sorted_users_.size() - 1;
  }
  void SwapUsers(int lhs_position, int rhs_position) {
    const int lhs_id = sorted_users_[lhs_position];
    const int rhs_id = sorted_users_[rhs_position];
    swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
    swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }*/
};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  //ios::sync_with_stdio(false);
  //cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
