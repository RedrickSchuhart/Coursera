#include <iostream>

using namespace std;

int main()
{
    int a, b, i;
    cin >> a >> b;
    if(a%2 == 1)
    {
        a++;
    }
    for(i = a; i <= b; i=i+2)
        cout << i << ' ';
    return 0;
}
