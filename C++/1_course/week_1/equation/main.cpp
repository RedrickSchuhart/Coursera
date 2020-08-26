#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float a, b, c;
    float x1, x2, d;
    cin >> a >> b >> c;
    if(a==0)
    {
        if(b!=0)
        {
            x1 = -c/b;
            cout << x1;
        }
    }else
    {
        d = b*b - 4*a*c;
        if(d>0)
        {
            x1 = (-b + sqrt(d))/(2*a);
            x2 = (-b - sqrt(d))/(2*a);
            cout << x1 << ' ' << x2;
        }
        if(d==0.f)
        {
            x1 = -b/(2*a);
            cout << x1;
        }
    }
    return 0;
}
