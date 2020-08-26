#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int is_command(const string& s)
{
    if(s[0]=='C'){return 0;}
    if(s[0]=='Q'){return 1;}
    if(s[5]=='_'){return 2;}
    return 3;
}

int main()
{
    int n=0, count_com, com;
    string buffer;
    vector<bool> is_worry;
    cin >> count_com;
    for(int i=0; i<count_com; i++)
    {
        cin >> buffer;
        com = is_command(buffer);
        switch (com) {
        case 0:
            cin >> n;
            is_worry.resize(is_worry.size()+n, false);
            break;
         case 1:
            cin >> n;
            is_worry[n]=false;
            break;
        case 2:
            n = 0;
            for(bool f:is_worry)
            {
                if(f == true)
                    n++;
            }
            cout << n << endl;
            break;
        case 3:
            cin >> n;
            is_worry[n]=true;
            break;

        }

    }
    return 0;
}
