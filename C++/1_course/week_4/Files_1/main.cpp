#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("input.txt");
    string str;
    if (input.is_open()){
        ofstream output("output.txt");
        while (getline(input, str)) {
            ofstream output("output.txt", ios::app);
            output << str << endl;
            //cout << str << endl;
        }
    }

    return 0;
}
