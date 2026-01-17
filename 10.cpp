#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
using namespace std;

bool isKeyword(const string &str) {
    string keywords[] = {
        "int", "float", "double", "char", "if", "else",
        "for", "while", "do", "return", "void"
    };

    for (string k : keywords) {
        if (k == str)
            return true;
    }
    return false;
}

int main() {
    ifstream fin("input.txt");
    char ch;
    string token;

    if (!fin) {
        cout << "Error opening file\n";
        return 1;
    }

    while (fin.get(ch)) {

        // Ignore spaces, tabs, and newlines
        if (isspace(ch))
            continue;

        // Ignore single-line comments
        if (ch == '/') {
            char next = fin.peek();
            if (next == '/') {
                while (fin.get(ch) && ch != '\n');
                continue;
            }
            // Ignore multi-line comments
            else if (next == '*') {
                fin.get(ch);
                while (fin.get(ch)) {
                    if (ch == '*' && fin.peek() == '/') {
                        fin.get(ch);
                        break;
                    }
                }
                continue;
            }
        }

        // Identifier or keyword
        if (isalpha(ch) || ch == '_') {
            token = ch;
            while (fin.peek() != EOF && (isalnum(fin.peek()) || fin.peek() == '_')) {
                fin.get(ch);
                token += ch;
            }

            if (isKeyword(token))
                cout << token << " : Keyword\n";
            else
                cout << token << " : Identifier\n";
        }

        // Number
        else if (isdigit(ch)) {
            token = ch;
            while (fin.peek() != EOF && isdigit(fin.peek())) {
                fin.get(ch);
                token += ch;
            }
            cout << token << " : Number\n";
        }

        // Operator or special symbol
        else {
            cout << ch << " : Operator/Symbol\n";
        }
    }

    fin.close();
    return 0;
}
