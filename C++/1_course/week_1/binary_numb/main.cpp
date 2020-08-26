#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int a, i=1;
    vector<int> bin;
    cin >> a;
    while(a>0)
    {
        i = a%2;
        a = (a - i)/2;
        bin.push_back(i);
    }
    reverse(bin.begin(), bin.end());
    for ( int x : bin )
        cout << x;
    return 0;
}
