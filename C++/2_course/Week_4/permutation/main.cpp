#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename Iter>
void PrintRange(Iter first, Iter last)
{
    for(auto it=first; it!=last; it++)
    {
        cout << *it << ' ';
    }
    cout << endl;
}

int main()
{
    int N;
    vector<int> nums;
    cin >> N;
    for (int i=N; i>0; i--)
    {
        nums.push_back(i);
    }
    PrintRange(nums.begin(), nums.end());
    while(prev_permutation(nums.begin(), nums.end()))
    {
        PrintRange(nums.begin(), nums.end());
    }
    return 0;
}
