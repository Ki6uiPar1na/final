#include <bits/stdc++.h>
using namespace std;

map<string, vector<string>> prod; // use string for NTs, to allow A' etc.
int nextNT = 1; // counter for generating new NTs

// Find longest common prefix of strings in vec
string longestCommonPrefix(vector<string>& vec) {
    if (vec.empty()) return "";
    string prefix = vec[0];
    for (int i = 1; i < vec.size(); i++) {
        int j = 0;
        while (j < prefix.size() && j < vec[i].size() && prefix[j] == vec[i][j])
            j++;
        prefix = prefix.substr(0, j);
    }
    return prefix;
}

// Perform left factoring for a single non-terminal
void leftFactor(string nt) {
    vector<string>& rules = prod[nt];

    while (true) {
        map<string, vector<string>> prefixMap;

        // Group rules by first character
        for (string rule : rules) {
            string key = rule.empty() ? "E" : string(1, rule[0]);
            prefixMap[key].push_back(rule);
        }

        bool factored = false;
        for (auto &entry : prefixMap) {
            if (entry.second.size() > 1) {
                string lcp = longestCommonPrefix(entry.second);
                if (lcp.empty() || lcp == "E") continue;

                string newNT = nt + "'"; // create new non-terminal like A'
                int count = 1;
                while (prod.count(newNT)) { // ensure uniqueness
                    newNT = nt + "'" + to_string(count);
                    count++;
                }

                vector<string> newRules;
                for (string r : entry.second) {
                    string suffix = r.substr(lcp.size());
                    if (suffix.empty()) suffix = "E";
                    newRules.push_back(suffix);
                }

                // Remove original rules
                rules.erase(remove_if(rules.begin(), rules.end(),
                            [&](string s){ return find(entry.second.begin(), entry.second.end(), s) != entry.second.end(); }),
                            rules.end());
                rules.push_back(lcp + newNT); // add factored production
                prod[newNT] = newRules;

                factored = true;
                break; // reprocess after factoring
            }
        }

        if (!factored) break; // no more factoring
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
        leftFactor(nt);

    cout << "\nLeft Factored Grammar:\n";
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
