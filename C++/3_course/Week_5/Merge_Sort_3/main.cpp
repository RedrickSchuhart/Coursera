#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    if(!((range_begin==range_end)||(next(range_begin)==range_end))) {
        vector<typename RandomIt::value_type>values1, values2, values3, v;
        auto aver1 = range_begin + (range_end-range_begin)/3;
        auto aver2 = range_begin + 2*(range_end-range_begin)/3;
        values1 = vector<typename RandomIt::value_type>(make_move_iterator(range_begin), make_move_iterator(aver1));
        values2 = vector<typename RandomIt::value_type>(make_move_iterator(aver1), make_move_iterator(aver2));
        values3 = vector<typename RandomIt::value_type>(make_move_iterator(aver2), make_move_iterator(range_end));
        MergeSort(values1.begin(), values1.end());
        MergeSort(values2.begin(), values2.end());
        MergeSort(values3.begin(), values3.end());
        merge(make_move_iterator(values1.begin()), make_move_iterator(values1.end()),
              make_move_iterator(values2.begin()), make_move_iterator(values2.end()),
              back_inserter(v));
        merge(make_move_iterator(v.begin()), make_move_iterator(v.end()),
              make_move_iterator(values3.begin()), make_move_iterator(values3.end()),
              range_begin);
//        vector<typename RandomIt::value_type>values1, values2,v;
//        auto aver1 = range_begin + (range_end-range_begin)/2;
//        values1 = vector<typename RandomIt::value_type>(make_move_iterator(range_begin), make_move_iterator(aver1));
//        values2 = vector<typename RandomIt::value_type>(make_move_iterator(aver1), make_move_iterator(range_end));
//        MergeSort(values1.begin(), values1.end());
//        MergeSort(values2.begin(), values2.end());
//        move(values1.begin(), values1.end(), range_begin);
//        move(values2.begin(), values2.end(), aver1);
//        merge(make_move_iterator(values1.begin()), make_move_iterator(values1.end()),
//              make_move_iterator(values2.begin()), make_move_iterator(values2.end()),
//              range_begin);
    }
    return;
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
