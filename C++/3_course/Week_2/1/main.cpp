#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    long int a, b, c;
    c = 19451945;
    double c_f = 19451945.0;
    for(a = 1; a < sqrt(c_f); a++){
        b = sqrt(c_f-a*a);
        if((b*b+a*a)==c)
            cout << a << " " << b << endl;
    }
    cout << "Hello World!" << endl;
    return 0;
}
