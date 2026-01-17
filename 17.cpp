#include <bits/stdc++.h>
using namespace std;

map<string, vector<vector<string>>> prod;  // Non-terminal -> RHS tokens
map<string, set<string>> firstSet, followSet;
set<string> terminals, nonTerminals;

// Tokenize production RHS (handles "id" as a terminal)
vector<string> tokenize(string s) {
    vector<string> tokens;
    for (int i = 0; i < s.size(); ) {
        if (i + 1 < s.size() && s.substr(i,2) == "id") {
            tokens.push_back("id");
            i += 2;
        } else {
            tokens.push_back(string(1,s[i]));
            i++;
        }
    }
    return tokens;
}

// Compute FIRST set of X
set<string> FIRST(string X) {
    if (!isupper(X[0])) return {X}; // terminal
    if (!firstSet[X].empty()) return firstSet[X];

    set<string> result;
    for (auto rhs : prod[X]) {
        bool epsilonAll = true;
        for (auto sym : rhs) {
            set<string> temp = FIRST(sym);
            for (auto t : temp)
                if (t != "E") result.insert(t);
            if (temp.find("E") == temp.end()) {
                epsilonAll = false;
                break;
            }
        }
        if (epsilonAll) result.insert("E");
    }
    firstSet[X] = result;
    return result;
}

// Compute FOLLOW sets
void computeFOLLOW(string start) {
    followSet[start].insert("$");

    bool changed;
    do {
        changed = false;
        for (auto &p : prod) {
            string A = p.first;
            for (auto rhs : p.second) {
                for (int i = 0; i < rhs.size(); i++) {
                    string B = rhs[i];
                    if (!isupper(B[0])) continue;

                    bool epsilonNext = true;
                    for (int j = i + 1; j < rhs.size(); j++) {
                        set<string> temp = FIRST(rhs[j]);
                        for (auto t : temp)
                            if (t != "E" && followSet[B].insert(t).second) changed = true;
                        if (temp.find("E") == temp.end()) {
                            epsilonNext = false;
                            break;
                        }
                    }
                    if (i == rhs.size() - 1 || epsilonNext) {
                        for (auto t : followSet[A])
                            if (followSet[B].insert(t).second) changed = true;
                    }
                }
            }
        }
    } while (changed);
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    cin.ignore();

    cout << "Enter productions (format: A->α, E for epsilon):\n";
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin,line);
        string lhs = line.substr(0,1);
        string rhsStr = line.substr(3);
        vector<string> rhs = tokenize(rhsStr);
        prod[lhs].push_back(rhs);
        nonTerminals.insert(lhs);
        for (auto t : rhs)
            if (!isupper(t[0]) && t != "E") terminals.insert(t);
    }

    string start = prod.begin()->first;

    // Compute FIRST and FOLLOW sets
    for (auto nt : nonTerminals) FIRST(nt);
    computeFOLLOW(start);

    // Build LL(1) table
    map<pair<string,string>, vector<string>> table;
    for (auto &p : prod) {
        string A = p.first;
        for (auto rhs : p.second) {
            set<string> first_rhs;
            if (rhs.size()==1 && rhs[0]=="E") first_rhs.insert("E");
            else {
                bool epsilonAll = true;
                for (auto s : rhs) {
                    set<string> temp = FIRST(s);
                    for (auto t : temp) if (t != "E") first_rhs.insert(t);
                    if (temp.find("E") == temp.end()) {
                        epsilonAll = false;
                        break;
                    }
                }
                if (epsilonAll) first_rhs.insert("E");
            }

            for (auto t : first_rhs)
                if (t != "E") table[{A,t}] = rhs;

            if (first_rhs.find("E") != first_rhs.end()) {
                for (auto f : followSet[A]) table[{A,f}] = rhs;
            }
        }
    }

    // Convert terminals to a sorted vector for consistent printing
    vector<string> termList(terminals.begin(), terminals.end());
    sort(termList.begin(), termList.end());
    termList.push_back("$"); // Add end marker

    // Print FIRST sets
    cout << "\nFIRST Sets:\n";
    for (auto nt : nonTerminals) {
        cout << "FIRST(" << nt << ") = { ";
        for (auto t : firstSet[nt]) cout << t << " ";
        cout << "}\n";
    }

    // Print FOLLOW sets
    cout << "\nFOLLOW Sets:\n";
    for (auto nt : nonTerminals) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (auto f : followSet[nt]) cout << f << " ";
        cout << "}\n";
    }

    // Print LL(1) parsing table
    cout << "\nLL(1) Parsing Table:\n";
    cout << setw(10) << "NT/T";
    for (auto t : termList) cout << setw(10) << t;
    cout << "\n";

    for (auto nt : nonTerminals) {
        cout << setw(10) << nt;
        for (auto t : termList) {
            if (table.count({nt,t})) {
                string s = "";
                for (auto tok : table[{nt,t}]) s += tok;
                cout << setw(10) << s;
            } else cout << setw(10) << "-";
        }
        cout << "\n";
    }

    return 0;
}
