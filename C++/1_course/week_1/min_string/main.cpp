#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s, s1, s2, s3;
    cin >> s1 >> s2 >> s3;
    if((s1<s2)&&(s1<s3))
    {
        cout << s1 << endl;
    }
    else
    {
        if (s2<s3)
        {
            cout << s2 << endl;
        }
        else
        {
            cout << s3 << endl;
        }
    }
    return 0;
}
