#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    int N, M, number;
    input >> N;
    input.ignore(1);
    input >> M;
    input.ignore(1);
    for(int x=0; x<N; x++)
    {
        for(int y=0; y<M; y++)
        {
            input >> number;
            input.ignore(1);
            cout << setw(10) << number;
            if(y!=M-1)
                cout << " ";
        }
        if(x!=N-1)
            cout << endl;
    }

    return 0;
}
