#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> prod; // Productions: NT -> list of RHS (tokens)
vector<string> targetTokens;
bool found = false;

/* Tokenize a string into terminals/non-terminals */
vector<string> tokenize(string s) {
    vector<string> tokens;
    for (int i = 0; i < s.size(); ) {
        if (i + 1 < s.size() && s.substr(i,2) == "id") {
            tokens.push_back("id");
            i += 2;
        } else {
            tokens.push_back(string(1, s[i]));
            i++;
        }
    }
    return tokens;
}

/* Tokenize target string (split by space or multi-character terminals) */
vector<string> tokenizeTarget(string s) {
    vector<string> tokens;
    for (int i = 0; i < s.size(); ) {
        if (i + 1 < s.size() && s.substr(i,2) == "id") {
            tokens.push_back("id");
            i += 2;
        } else if (s[i] != ' ') {
            tokens.push_back(string(1, s[i]));
            i++;
        } else i++;
    }
    return tokens;
}

/* Check if the terminal prefix matches target */
bool isValid(vector<string> current) {
    if (current.size() > targetTokens.size()) return false;
    for (int i = 0; i < current.size(); i++) {
        string c = current[i];
        if (prod.find(c) == prod.end()) { // terminal
            if (i >= targetTokens.size() || c != targetTokens[i])
                return false;
        }
    }
    return true;
}

/* Leftmost derivation DFS */
void leftmostDerivation(vector<string> current, vector<vector<string>>& steps) {
    if (found) return;

    if (current == targetTokens) {
        cout << "\nLeftmost Derivation:\n";
        for (auto &s : steps) {
            for (auto tok : s) cout << tok;
            cout << endl;
        }
        found = true;
        return;
    }

    if (!isValid(current)) return;

    for (int i = 0; i < current.size(); i++) {
        string tok = current[i];
        if (prod.find(tok) != prod.end()) { // non-terminal
            for (auto rhs : prod[tok]) {
                vector<string> next;
                next.insert(next.end(), current.begin(), current.begin() + i);
                if (!(rhs.size() == 1 && rhs[0] == "E")) // epsilon
                    next.insert(next.end(), rhs.begin(), rhs.end());
                next.insert(next.end(), current.begin() + i + 1, current.end());

                steps.push_back(next);
                leftmostDerivation(next, steps);
                steps.pop_back();
            }
            return; // only expand leftmost non-terminal
        }
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cin.ignore();

    cout << "Enter productions (use E for epsilon, e.g., A->E):\n";
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        string lhs = line.substr(0,1);
        string rhs = line.substr(3);
        vector<string> rhsTokens = tokenize(rhs);
        prod[lhs].push_back(rhsTokens);
    }

    string target;
    cout << "Enter target string: ";
    getline(cin, target);
    targetTokens = tokenizeTarget(target);

    vector<vector<string>> steps;
    steps.push_back(vector<string>{prod.begin()->first});

    leftmostDerivation(vector<string>{prod.begin()->first}, steps);

    if (!found)
        cout << "\nNo leftmost derivation possible.\n";

    return 0;
}
