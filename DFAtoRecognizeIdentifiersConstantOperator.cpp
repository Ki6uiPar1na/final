//Write a program(cpp) to implement DFA that recognizes identifiers, constants, and operators. 

#include <iostream>
#include <cctype>
using namespace std;

bool isIdentifier(const string &s) {
    if (!(isalpha(s[0]) || s[0] == '_'))
        return false;

    for (char c : s) {
        if (!(isalnum(c) || c == '_'))
            return false;
    }
    return true;
}

bool isConstant(const string &s) {
    bool hasDecimal = false;

    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i]))
            continue;
        else if (s[i] == '.' && !hasDecimal) {
            hasDecimal = true;
        } else {
            return false;
        }
    }
    return true;
}

bool isOperator(const string &s) {
    string operators = "+-*/=<>";
    return (s.length() == 1 && operators.find(s[0]) != string::npos);
}

int main() {
    string input;
    cout << "Enter a token: ";
    cin >> input;

    if (isIdentifier(input))
        cout << "Recognized as IDENTIFIER\n";
    else if (isConstant(input))
        cout << "Recognized as CONSTANT\n";
    else if (isOperator(input))
        cout << "Recognized as OPERATOR\n";
    else
        cout << "Invalid token\n";

    return 0;
}
