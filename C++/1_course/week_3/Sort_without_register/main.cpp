#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

void Print(const vector<string>& A)
{
    for(auto& i:A)
        cout << i << " ";
}

void tolow(string& a)
{
    for(auto& i:a)
        i = tolower(i);
    //cout << a;
}

int main()
{
    int N;
    cin >> N;
    vector<string> A(N);
    for(auto& i:A)
        cin >> i;
    sort(begin(A), end(A), [](string a, string b){tolow(a); tolow(b); return a<b;});
    Print(A);
    return 0;
}
