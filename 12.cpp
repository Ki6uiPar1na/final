#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> prod;
map<char, set<char>> firstSet, followSet;
set<char> nonTerminals;
int n;

/* Compute FIRST of a symbol */
set<char> FIRST(char c) {
    if (!isupper(c)) return {c};

    if (!firstSet[c].empty())
        return firstSet[c];

    set<char> result;

    for (string rhs : prod[c]) {
        if (rhs == "E") {
            result.insert('E');
            continue;
        }

        bool epsilonAll = true;
        for (char sym : rhs) {
            set<char> temp = FIRST(sym);
            for (char t : temp)
                if (t != 'E') result.insert(t);

            if (temp.find('E') == temp.end()) {
                epsilonAll = false;
                break;
            }
        }
        if (epsilonAll)
            result.insert('E');
    }

    firstSet[c] = result;
    return result;
}

/* Compute FOLLOW sets */
void computeFOLLOW(char start) {
    followSet[start].insert('$');

    bool changed;
    do {
        changed = false;

        for (auto &p : prod) {
            char A = p.first;
            for (string rhs : p.second) {
                for (int i = 0; i < rhs.size(); i++) {
                    char B = rhs[i];
                    if (!isupper(B)) continue;

                    bool epsilonNext = true;
                    for (int j = i + 1; j < rhs.size(); j++) {
                        set<char> temp = FIRST(rhs[j]);
                        for (char t : temp) {
                            if (t != 'E' && followSet[B].insert(t).second)
                                changed = true;
                        }
                        if (temp.find('E') == temp.end()) {
                            epsilonNext = false;
                            break;
                        }
                    }

                    if (i == rhs.size() - 1 || epsilonNext) {
                        for (char t : followSet[A]) {
                            if (followSet[B].insert(t).second)
                                changed = true;
                        }
                    }
                }
            }
        }
    } while (changed);
}

int main() {
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use E for epsilon):\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        char lhs = s[0];
        string rhs = s.substr(3);
        prod[lhs].push_back(rhs);
        nonTerminals.insert(lhs);
    }

    char startSymbol = prod.begin()->first;

    for (char nt : nonTerminals)
        FIRST(nt);

    computeFOLLOW(startSymbol);

    cout << "\nFOLLOW sets:\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char c : followSet[nt])
            cout << c << " ";
        cout << "}\n";
    }

    return 0;
}
