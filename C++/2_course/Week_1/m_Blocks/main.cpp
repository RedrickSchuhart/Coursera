#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    uint32_t N;
    uint16_t P;
    uint64_t W, H, D, m=0;
    cin >> N >> P;
    for(uint32_t i = 0; i<N; i++){
        cin >> W >> H >> D;
        m += static_cast<uint64_t>(W)*H*D*P;
    }
    cout << m << endl;
    return 0;
}
