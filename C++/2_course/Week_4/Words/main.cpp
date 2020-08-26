#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

vector<string> SplitIntoWords(const string& str)
{
    vector<string> words;
    string s = str;
    auto first = begin(s);
    auto second = find(begin(s), end(s), ' ');
    while(second!=end(s))
    {
        words.push_back(string(first, second));
        first = second + 1;
        *second = 'a';
        second = find(begin(s), end(s), ' ');
    }
    words.push_back(string(first, second));
    return words;
}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}

