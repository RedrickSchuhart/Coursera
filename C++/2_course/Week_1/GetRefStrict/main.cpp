#include <iostream>
#include <map>
#include <stdexcept>

using namespace std;

template<typename Key, typename Second> Second& GetRefStrict(map<Key,Second> m);

template<typename Key, typename Second>
Second& GetRefStrict(map<Key,Second>& m, Key k){
    if (m.count(k)){
        return m[k];
    } else {
        throw runtime_error("");
    }
}

int main()
{
    /*map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 1);
    item = "newvalue";
    cout << m[0] << endl;*/
}
