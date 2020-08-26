#include "search_server.h"
#include "iterator_range.h"


#include <algorithm>
#include <iterator>
#include <sstream>
#include <set>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    if(i==0) {
        InvertedIndex new_index;
        //index.Clear();
        for (string current_document; getline(document_input, current_document); ) {
            new_index.Add(move(current_document));
        }
        unique_lock g(index.m);
        index.Update(new_index);
        i=1;
    }

}

template <typename Container>
string SearchServer::ParalQueries(const Container& queries) {
    vector<pair<size_t, size_t>> search_results;
    vector<size_t> docid_count;
    ostringstream search_results_output;
    for (const string& current_query:queries) {
        const auto words = SplitIntoWords(current_query);


        {
            shared_lock g(index.m);
            search_results.resize(index.GetSize());
            docid_count.resize(index.GetSize());
            fill(docid_count.begin(), docid_count.end(), 0);
            for (const auto& word : words) {
                for (const auto& [docid, count] : index.Lookup(word)) {
                    docid_count[docid]+=count;
                }
            }
        }


        for(size_t index=0; index<docid_count.size(); index++) {
            search_results[index] = {index, docid_count[index]};
        }
        auto middle = begin(search_results);
        if(distance(begin(search_results), end(search_results))<=5) {
            middle = end(search_results);
        } else {
            middle = next(begin(search_results),5);
        }
        partial_sort(
                    begin(search_results),
                    middle,
                    end(search_results),
                    [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
            int64_t lhs_docid = lhs.first;
            auto lhs_hit_count = lhs.second;
            int64_t rhs_docid = rhs.first;
            auto rhs_hit_count = rhs.second;
            return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        }
        );

        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(search_results, 5)) {
            if(hitcount==0)
                break;
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
    return search_results_output.str();
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {


    vector<string> queries;
    vector<future<string>> futures;

    for (string current_query; getline(query_input, current_query); ) {
        queries.push_back(move(current_query));
    }
    for(auto page:Paginate(queries, queries.size()/8+1)) {
        futures.push_back(async(&SearchServer::ParalQueries<IteratorRange<vector<string>::iterator>>,
                                this, page));
    }
    for(auto& f:futures) {
        search_results_output << f.get();
    }
}

void InvertedIndex::Add(const string& document) {
    docs.push_back(document);
    map<string, map<size_t, size_t>> index_m;
    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        index_m[word][docid]++;
    }
    for(const auto& [word, map] : index_m) {
        for(const auto& elem : map) {
            index[word].push_back(move(elem));
        }
    }
}

vector<pair<size_t,size_t>> InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
