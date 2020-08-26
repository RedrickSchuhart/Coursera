#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if((range_begin==range_end)||(next(range_begin)==range_end))
    {
    }
    else
    {
        vector<typename RandomIt::value_type>values1, values2, values3, v;
        auto aver1 = range_begin + (range_end-range_begin)/3;
        auto aver2 = range_begin + 2*(range_end-range_begin)/3;
        values1 = vector<typename RandomIt::value_type>(range_begin, aver1);
        values2 = vector<typename RandomIt::value_type>(aver1, aver2);
        values3 = vector<typename RandomIt::value_type>(aver2, range_end);
        MergeSort(values1.begin(), values1.end());
        MergeSort(values2.begin(), values2.end());
        MergeSort(values3.begin(), values3.end());
        merge(values1.begin(), values1.end(), values2.begin(), values2.end(), back_inserter(v));
        merge(v.begin(), v.end(), values3.begin(), values3.end(), range_begin);

    }
    return;
}

int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1, 5};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}

