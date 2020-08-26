#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main()
{
    int q;
    map<string,set<string>> words;
    cin >> q;
    for(int i=0; i<q; i++)
    {
        string operation_code;
        cin >> operation_code;
        if (operation_code == "ADD") {
            string word1, word2;
            cin >> word1 >> word2;
            words[word1].insert(word2);
            words[word2].insert(word1);
        } else {
            if (operation_code == "COUNT") {
                string word;
                cin >> word;
                cout << words[word].size() << endl;
            } else {
                string word1, word2;
                cin >> word1 >> word2;
                if(words[word1].count(word2)==0){cout << "NO" << endl;}
                else{cout << "YES" << endl;}
            }
        }
    }
    return 0;
}
