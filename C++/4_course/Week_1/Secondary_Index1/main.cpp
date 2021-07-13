#include "test_runner.h"

#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

struct Record {
    string id;
    string title;
    string user;
    int timestamp;
    int karma;
};

// Реализуйте этот класс
class Database {
public:
    bool Put(const Record& record) {
        string id = record.id;
        list<string> l;
        if(data.find(id)==data.end()) {
            data[id]=record;
            bytime[record.timestamp].push_back(id);
            bykarma[record.karma].push_back(id);
            byuser[record.user].push_back(id);
            return true;
        } else {
            return false;
        }
    }
    const Record* GetById(const string& id) const {
        auto it = data.find(id);
        if(it==data.end()) {
            return nullptr;
        } else {
            return &(*it).second;
        }
    }
    bool Erase(const string& id) {
        auto it = data.find(id);
        if(it==data.end()) {
            return false;
        } else {
            auto& record = (*it).second;
            bytime[record.timestamp].erase(find(bytime[record.timestamp].begin(), bytime[record.timestamp].end(), id));
            bykarma[record.karma].erase(find(bykarma[record.karma].begin(), bykarma[record.karma].end(), id));
            byuser[record.user].erase(find(byuser[record.user].begin(), byuser[record.user].end(), id));;
            data.erase(it);
            return true;
        }
    }

    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const {
        auto end = bytime.find(high);
        end++;
        for(auto it = bytime.find(low); it!=end; it++) {
            for(auto item:(*it).second) {
                callback;
            }
        }
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const {
        auto end = bykarma.find(high);
        end++;
        int i =0;
        for(auto it = bykarma.find(low); it!=end; it++) {
            auto& list = (*it).second;
            for(auto& item : list) {
                i++;
                //if(callback()==true) {

                //}
            }

        }
    }

    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const {
        auto it = byuser.find(user);
        for(auto item:(*it).second) {
            callback;
        }

    }
private:
    map<int, list<string>> bytime, bykarma;
    unordered_map<string, list<string>> byuser;
    unordered_map<string, Record> data;
};

void TestRangeBoundaries() {
    const int good_karma = 1000;
    const int bad_karma = -10;

    Database db;
    db.Put({"id1", "Hello there", "master", 1536107260, good_karma});
    db.Put({"id2", "O>>-<", "general2", 1536107260, bad_karma});

    int count = 0;
    db.RangeByKarma(bad_karma, good_karma, [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestSameUser() {
    Database db;
    db.Put({"id1", "Don't sell", "master", 1536107260, 1000});
    db.Put({"id2", "Rethink life", "master", 1536107260, 2000});

    int count = 0;
    db.AllByUser("master", [&count](const Record&) {
        ++count;
        return true;
    });

    ASSERT_EQUAL(2, count);
}

void TestReplacement() {
    const string final_body = "Feeling sad";

    Database db;
    db.Put({"id", "Have a hand", "not-master", 1536107260, 10});
    db.Erase("id");
    db.Put({"id", final_body, "not-master", 1536107260, -10});

    auto record = db.GetById("id");
    ASSERT(record != nullptr);
    ASSERT_EQUAL(final_body, record->title);
}

int main() {
    int n;
    cin >> n;
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
    return 0;
}
