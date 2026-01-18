#include <bits/stdc++.h>
using namespace std;
enum class TokenType { IDENTIFIER, CONSTANT, OPERATOR, UNKNOWN };
static inline bool isLetterOrUnderscore(char c) {
    return (isalpha(static_cast<unsigned char>(c)) || c == '_');
}
static inline bool isLetterDigitOrUnderscore(char c) {
    return (isalnum(static_cast<unsigned char>(c)) || c == '_');
}
bool isIdentifierDFA(const string &s) {
    if (s.empty()) return false;
    int state = 0; // 0 = start, 1 = in identifier (accept)
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (state == 0) {
            if (isLetterOrUnderscore(c)) state = 1;
            else return false;
        } else if (state == 1) {
            if (isLetterDigitOrUnderscore(c)) state = 1;
            else return false;
        }
    }
    return state == 1;
}
bool isConstantDFA(const string &s) {
    if (s.empty()) return false;
    int state = 0;
    size_t i = 0;
    while (i < s.size()) {
        char c = s[i];
        if (state == 0) {
            if (c == '+' || c == '-') { state = 1; }
            else if (isdigit(static_cast<unsigned char>(c))) { state = 2; }
            else if (c == '.') { state = 3; }
            else return false;
        } else if (state == 1) {
            if (isdigit(static_cast<unsigned char>(c))) state = 2;
            else if (c == '.') state = 3;
            else return false;
        } else if (state == 2) {
            if (isdigit(static_cast<unsigned char>(c))) state = 2;
            else if (c == '.') state = 4;
            else return false;
        } else if (state == 3) {
            if (isdigit(static_cast<unsigned char>(c))) state = 4;
            else return false;
        } else if (state == 4) {
            if (isdigit(static_cast<unsigned char>(c))) state = 4;
            else return false;
        }
        ++i;
    }
    return (state == 2 || state == 4);
}
TokenType classifyToken(const string &s) {
    static const unordered_set<string> operators = {
        "+","-","*","/","%","=","==","!=","<","<=",">", ">=",
        "++","--","+=","-=","*=","/=","%=","&&","||","!","~",
        "<<",">>","<<=",">=","^","|","&","|=","^=","->",".",",",":",";",
        "(",")","{","}","[","]"
    };
    if (operators.find(s) != operators.end()) return TokenType::OPERATOR;
    if (isIdentifierDFA(s)) return TokenType::IDENTIFIER;
    if (isConstantDFA(s)) return TokenType::CONSTANT;
    return TokenType::UNKNOWN;
}
string tokenTypeName(TokenType t) {
    switch (t) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::CONSTANT: return "CONSTANT";
        case TokenType::OPERATOR: return "OPERATOR";
        default: return "UNKNOWN";
    }
}
int main(int argc, char* argv[]) {
    vector<string> tokens;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) tokens.emplace_back(argv[i]);
    } else {
        cout << "Enter tokens (whitespace separated). Press Ctrl+D when done:\n";
        string tok;
        while (cin >> tok) tokens.push_back(tok);
    }
    if (tokens.empty()) {
        cerr << "No tokens provided. Usage: " << argv[0] << " token1 token2 ...\n";
        return 1;
    }
    for (const auto &t : tokens) {
        TokenType ty = classifyToken(t);
        cout << t << " : " << tokenTypeName(ty) << '\n';
    }
    return 0;
}
