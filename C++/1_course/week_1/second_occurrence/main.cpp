#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n =0;
    string s;
    cin >> s;
    for(int i = 0; i < s.length();  i++)
    {
        if(s[i] == 'f')
            n = n + 1;
        if(n==2)
        {
            cout << i;
            break;
        }
    }
    if(n==1)
        cout << -1;
    if(n==0)
        cout << -2;
    return 0;
}
