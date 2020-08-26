#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    vector<T> greaterelements;
    set<T> elems = elements;
    elems.insert(border);
    auto bord = find(begin(elems), end(elems), border);
    for(++bord; bord!=end(elems); bord++)
    {
        greaterelements.push_back(*bord);
    }
    return greaterelements;
}



int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}

