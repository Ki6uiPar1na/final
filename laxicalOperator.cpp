#include <bits/stdc++.h>
using namespace std;

set<string> validOperators = {
    "+", "-", "*", "/", "%", "++", "--",
    "==", "!=", ">", "<", ">=", "<=",
    "=", "+=", "-=", "*=", "/=", "%=",
    "&&", "||", "!"
};

int main() {
    cout << "Enter string of operators (space separated):\n";
    string line;
    getline(cin, line);

    stringstream ss(line);
    string token;

    cout << "\nLexical Analysis Result:\n";
    while (ss >> token) {
        if (validOperators.find(token) != validOperators.end()) {
            cout << token << " : Valid Operator\n";
        } else {
            cout << token << " : Invalid Operator\n";
        }
    }

    return 0;
}
