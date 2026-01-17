#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> firstSet;
void findFirst(char symbol) {
    if (!firstSet[symbol].empty())
        return;

    for (string production : grammar[symbol]) {
        if (!isupper(production[0])) {
            firstSet[symbol].insert(production[0]);
        }
        else {
            findFirst(production[0]);
            for (char ch : firstSet[production[0]]) {
                firstSet[symbol].insert(ch);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (Example: E=TR):\n";
    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;
        char lhs = prod[0];
        string rhs = prod.substr(2);
        grammar[lhs].push_back(rhs);
    }

    char start;
    cout << "Enter symbol to find FIRST: ";
    cin >> start;

    findFirst(start);

    cout << "FIRST(" << start << ") = { ";
    for (char c : firstSet[start])
        cout << c << " ";
    cout << "}\n";

    return 0;
}
