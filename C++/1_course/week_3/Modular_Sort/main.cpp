#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>


using namespace std;

void Print(const vector<int>& A)
{
    for(auto& i:A)
        cout << i << " ";
}

int main()
{
    int N;
    cin >> N;
    vector<int> A(N);
    for(auto& i:A)
        cin >> i;
    sort(begin(A), end(A), [](int a, int b){return (abs(a)<abs(b));});
    Print(A);
    return 0;
}
