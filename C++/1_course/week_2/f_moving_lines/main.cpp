#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination)
{
    for (string s:source)
        destination.push_back(s);
    source.clear();
}

void Reverse(vector<int>& v)
{
    reverse(v.begin(), v.end());
}

int main()
{
    return 0;
}
