
// NFA to recognize identifiers
// Identifier definition used here:
//   identifier := (letter | '_') (letter | digit | '_')*
// This program simulates a tiny NFA with two states:
//   state 0 = start
//   state 1 = accepting (seen valid first char)
// Transitions:
//   from 0: on letter or '_' -> 1
//   from 1: on letter/digit/'_' -> stay in 1

#include <bits/stdc++.h>
using namespace std;

static inline bool isLetterOrUnderscore(char c) {
	return ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' );
}

static inline bool isLetterDigitOrUnderscore(char c) {
	return isLetterOrUnderscore(c) || (c >= '0' && c <= '9');
}

bool recognizeNFA(const string &s) {
	if (s.empty()) return false;
	int state = 0;
	for (char c : s) {
		if (state == 0) {
			if (isLetterOrUnderscore(c)) state = 1;
			else return false; // no valid transition -> reject
		} else if (state == 1) {
			if (isLetterDigitOrUnderscore(c)) state = 1; // stay in accept
			else return false;
		}
	}
	return state == 1; // accepting if we ended in state 1
}

int main() {
	vector<string> tokens;
    string s; cin >> s;
    tokens.push_back(s);
    while (cin >> s) {
        tokens.push_back(s);
    }

    vector<pair<string, string>> results;

	for (const auto &t : tokens) {
		bool ok = recognizeNFA(t);
		if(ok){
            results.push_back({t, "ACCEPT (identifier)"});
        }
        else{
            results.push_back({t, "REJECT"});
        }
	}

    for(auto &res : results){
        cout << res.first << ": " << res.second << endl;
    }

	return 0;
}

