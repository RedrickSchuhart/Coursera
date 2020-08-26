#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> PalindromFilter(vector<string> words, int minLength){
    vector<string> result;
    for(string s:words)
    {
        if(s.length()>=minLength)
        {
            bool f = true;
            for (size_t i = 0; i < s.size() / 2; ++i) {
                if (s[i] != s[s.size() - i - 1]) {
                    f = false;
                }
            }
            if(f==true)
                result.push_back(s);
        }
    }
    return result;
}

int main()
{
    vector<string> result, input;
    int l;
    string buffer = "";
    //cin >> l;
        do {
            getline(cin, buffer);
            if (buffer.size() > 0) {
                input.push_back(buffer);
            }
        } while (buffer != "");
    cin >> l;
    result = PalindromFilter(input, l);
    for(string s:result)
    {
        cout << s << " ";
    }
    return 0;
}
