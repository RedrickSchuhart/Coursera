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

struct RecordWithIt {
    Record it;
    list<Record*>::const_iterator karma, time, user;
};

// Реализуйте этот класс
class Database {
public:
    bool Put(const Record& record) {
        string id = record.id;
        list<string> l;
        if(data.find(id)==data.end()) {
            data[id].it=record;
            bytime[record.timestamp].push_back(&data[id].it);
            data[id].time=--bytime[record.timestamp].end();
            bykarma[record.karma].push_back(&data[id].it);
            data[id].karma=--bykarma[record.karma].end();
            byuser[record.user].push_back(&data[id].it);
            data[id].user=--byuser[record.user].end();
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
            return &(*it).second.it;
        }
    }
    bool Erase(const string& id) {
        auto it = data.find(id);
        if(it==data.end()) {
            return false;
        } else {
            auto& record = (*it).second.it;
            bytime[record.timestamp].erase((*it).second.time);
            bykarma[record.karma].erase((*it).second.karma);
            byuser[record.user].erase((*it).second.user);
            data.erase(it);
            return true;
        }
    }


    template <typename Callback>
    void RangeByTimestamp(int low, int high, Callback callback) const{
        auto end = bytime.upper_bound(high);
        for(auto it = bytime.lower_bound(low); it!=end; it++) {
            for(auto item : (*it).second) {
                if(callback(*item)==false)
                    return;
            }
        }
        return;
    }

    template <typename Callback>
    void RangeByKarma(int low, int high, Callback callback) const{
        auto end = bykarma.upper_bound(high);
        for(auto it = bykarma.lower_bound(low); it!=end; it++) {
            for(auto item : (*it).second) {
                if(callback(*item)==false)
                    return;
            }
        }
        return;
    }



    template <typename Callback>
    void AllByUser(const string& user, Callback callback) const{
        auto it = byuser.find(user);
        if(it!=byuser.end()) {
            for(auto item : (*it).second) {
                if(callback(*item)==false)
                    return;
            }
        }
        return;
    }

private:
    map<int, list<Record*>> bytime, bykarma;
    unordered_map<string, list<Record*>> byuser;
    unordered_map<string, RecordWithIt> data;
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
    TestRunner tr;
    RUN_TEST(tr, TestRangeBoundaries);
    RUN_TEST(tr, TestSameUser);
    RUN_TEST(tr, TestReplacement);
}
