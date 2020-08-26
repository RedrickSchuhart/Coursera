#pragma once

#include <shared_mutex>
#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <future>
#include <map>
#include <string>
using namespace std;

//template <typename V>
//struct Access {
//  lock_guard<mutex> guard;
//  V& ref_to_value;
//};


class InvertedIndex {
public:
  shared_mutex m;
  void Add(const string& document);
  vector<pair<size_t,size_t>> Lookup(const string& word) const;

  size_t GetSize() const {
      return docs.size();
  }

  const vector<string>& GetDocuments() const {
      return docs;
  }

  const map<string, vector<pair<size_t, size_t>>>& GetIndex() const {
      return index;
  }

  void Update(InvertedIndex& other){
      index = move(other.GetIndex());
      docs = move(other.GetDocuments());
  }

  const string& GetDocument(size_t id) const {
    return docs[id];
  }
//    void Clear(){
//        index.clear();
//        docs.clear();
//    }

private:
  map<string, vector<pair<size_t, size_t>>> index;
  vector<string> docs;
};

class SearchServer {
public:
  size_t i=0;
  SearchServer() = default;
  template <typename Container>
  string ParalQueries(const Container& queries);
  explicit SearchServer(istream& document_input);
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
