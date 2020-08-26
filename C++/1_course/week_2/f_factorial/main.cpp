#include <iostream>

using namespace std;

int Factorial(int x)
{
    int fact = 1;
    if(x<1)
    {return 1;}
    else
    {
        while(x>1)
        {
        fact = fact * x;
        x = x - 1;
        }
    }
    return fact;
}

int main()
{
    int x;
    cin >> x;
    cout << Factorial(x) << endl;
    return 0;
}
