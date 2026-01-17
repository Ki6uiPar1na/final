#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> prod; // use string for NTs
int nextNT = 1; // for creating new non-terminals

// Function to eliminate left recursion for a non-terminal
void eliminateLeftRecursion(string nt) {
    vector<string> alpha; // left-recursive
    vector<string> beta;  // non-left-recursive

    for (string rule : prod[nt]) {
        if (rule[0] == nt[0]) { // direct left recursion
            alpha.push_back(rule.substr(1)); // remove leading NT
        } else {
            beta.push_back(rule);
        }
    }

    if (!alpha.empty()) {
        string newNT = nt + "'"; // new non-terminal A'
        int count = 1;
        while (prod.count(newNT)) {
            newNT = nt + "'" + to_string(count);
            count++;
        }

        vector<string> newBeta;
        for (string b : beta) {
            newBeta.push_back(b + newNT);
        }

        vector<string> newAlpha;
        for (string a : alpha) {
            newAlpha.push_back(a + newNT);
        }
        newAlpha.push_back("E"); // epsilon

        prod[nt] = newBeta;
        prod[newNT] = newAlpha;
    }
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (use E for epsilon, e.g., A->E):\n";
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        string lhs = s.substr(0,1);
        string rhs = s.substr(3);
        prod[lhs].push_back(rhs);
    }

    vector<string> nts;
    for (auto &p : prod) nts.push_back(p.first);

    for (string nt : nts)
        eliminateLeftRecursion(nt);

    cout << "\nGrammar after eliminating left recursion:\n";
    for (auto &p : prod) {
        cout << p.first << " -> ";
        for (int i = 0; i < p.second.size(); i++) {
            cout << p.second[i];
            if (i != p.second.size() - 1) cout << " | ";
        }
        cout << endl;
    }

    return 0;
}

