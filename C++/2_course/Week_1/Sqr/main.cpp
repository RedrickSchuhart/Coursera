#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

// Предварительное объявление шаблонных функций
template<typename First, typename Second> map<First,Second> Sqr(map<First,Second> m);
template<typename First, typename Second> pair<First,Second> Sqr(pair<First,Second> p);
template<typename T> T Sqr(T x);
template<typename N> vector<N> Sqr(vector<N> v);
//template<typename T> void FuncB(T x);

// Объявляем шаблонные функции
template<typename First, typename Second>
map<First,Second> Sqr(map<First,Second> m) {
    for (auto& i : m) {
        i.second = Sqr(i.second);
    }
    return m;
}

template<typename First, typename Second>
pair<First,Second> Sqr(pair<First,Second> p) {
    p.first = Sqr(p.first);
    p.second = Sqr(p.second);
    return p;
}


template<typename N>
vector<N> Sqr(vector<N> v) {
    for (auto& i : v) {
        i = Sqr(i);
    }
    return v;
}

template<typename T>
T Sqr(T x) {
    return x*x;
}

int main()
{
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
      cout << ' ' << x;
    }
    cout << endl;

    map<int, vector<int>> map_of_pairs = {
      {4, {2, 2, 3}},
      {7, {4, 3, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
      cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}
