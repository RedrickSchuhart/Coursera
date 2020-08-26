#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

int main()
{
    uint32_t N, n=0;
    double avg=0;
    cin >> N;
    vector<int64_t> temp(N);
    for(int i=0; i<N; i++){
        cin >> temp[i];
        avg += double(temp[i])/N;
    }
    for(int i=0; i<N; i++){
        if(temp[i]>avg)
            n++;
    }
    cout << n << endl;
    for(int i=0; i<N; i++){
        if(temp[i]>avg)
            cout << i << " ";
    }
    return 0;
}
