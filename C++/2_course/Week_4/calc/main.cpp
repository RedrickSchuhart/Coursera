#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <deque>

using namespace std;

int main()
{
    deque<string> str;
    int N;
    string ch, num, a, chl;
    cin >> num;
    cin >> N;
    str.push_front(num);
    cin >> ch >> a;
    str.push_back(" ");
    str.push_back(ch);
    str.push_back(" ");
    str.push_back(a);
    for(int i=1; i<N; i++)
    {
        chl = ch;
        cin >> ch >> a;
        if(((ch[0]=='*')||(ch[0]=='/'))&&((chl[0]=='+')||(chl[0]=='-')))
        {
            str.push_front("(");
            str.push_back(")");
        }
        str.push_back(" ");
        str.push_back(ch);
        str.push_back(" ");
        str.push_back(a);
    }
    for(auto it = begin(str); it < end(str); it++)
        cout << *it;
    cout << endl;
}
