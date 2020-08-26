//#include <iostream>
//#include <sstream>

#include <algorithm>
#include <string>
#include <vector>
#include <set>


using namespace std;

class Learner {
 private:
  set<string> dict;

 public:
  int Learn(const vector<string>& words) {
    int newWords = 0;
    for (const auto& word : words) {
      if (dict.find(word) == dict.end()) {
        ++newWords;
        dict.insert(word);
      }
    }
    return newWords;
  }

  vector<string> KnownWords() {
    vector<string> finish(dict.begin(), dict.end());
    return finish;
  }
};



/*int main() {
    Learner learner;
    string line;
    while (getline(cin, line)) {
      vector<string> words;
      stringstream ss(line);
      string word;
      while (ss >> word) {
        words.push_back(word);
      }
      cout << learner.Learn(words) << "\n";
    }
    cout << "=== known words ===\n";
    for (auto word : learner.KnownWords()) {
      cout << word << "\n";
    }
  return 0;
}*/
