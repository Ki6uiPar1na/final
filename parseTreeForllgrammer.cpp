#include <bits/stdc++.h>
using namespace std;

/* Parse tree node */
struct Node {
    string symbol;
    vector<Node*> children;
};

/* Parsing Table: M[NonTerminal][Terminal] */
map<pair<string, string>, vector<string>> parsingTable;

/* Print parse tree (DFS) */
void printTree(Node* root, int level = 0) {
    for (int i = 0; i < level; i++)
        cout << "  ";
    cout << root->symbol << endl;

    for (auto child : root->children)
        printTree(child, level + 1);
}

/* Split production string into tokens (terminals and non-terminals) */
vector<string> tokenize(string prod) {
    vector<string> tokens;
    for (int i = 0; i < prod.size(); ) {
        if (prod.substr(i,2) == "id") { // identifier token
            tokens.push_back("id");
            i += 2;
        } else {
            tokens.push_back(string(1, prod[i]));
            i++;
        }
    }
    return tokens;
}

int main() {
    /* Grammar:
        E  -> T A
        A  -> + T A | E
        T  -> F B
        B  -> * F B | E
        F  -> ( E ) | id
    */

    /* LL(1) Parsing Table */
    parsingTable[{"E","id"}] = {"T","A"};
    parsingTable[{"E","("}] = {"T","A"};

    parsingTable[{"A","+"}] = {"+","T","A"};
    parsingTable[{"A",")"}] = {"E"}; // epsilon
    parsingTable[{"A","$"}] = {"E"};

    parsingTable[{"T","id"}] = {"F","B"};
    parsingTable[{"T","("}] = {"F","B"};

    parsingTable[{"B","+"}] = {"E"}; // epsilon
    parsingTable[{"B","*"}] = {"*","F","B"};
    parsingTable[{"B",")"}] = {"E"}; // epsilon
    parsingTable[{"B","$"}] = {"E"}; // epsilon

    parsingTable[{"F","id"}] = {"id"};
    parsingTable[{"F","("}] = {"(","E",")"};

    /* Input */
    string input;
    cout << "Enter input string (tokens separated by space, end with $): ";
    getline(cin, input);
    stringstream ss(input);
    vector<string> tokens;
    string tok;
    while (ss >> tok) tokens.push_back(tok);

    stack<Node*> st;
    Node* root = new Node{"E"};
    st.push(new Node{"$"});
    st.push(root);

    int ip = 0;

    while (!st.empty()) {
        Node* top = st.top();
        string currInput = (ip < tokens.size()) ? tokens[ip] : "";

        st.pop();

        if (top->symbol == "$") {
            if (currInput == "$") {
                cout << "\nParsing Successful!\n\nParse Tree:\n";
                printTree(root);
                return 0;
            }
        }
        else if (top->symbol != "" && !isupper(top->symbol[0])) {
            // Terminal
            if (top->symbol == currInput) {
                ip++;
            } else if (top->symbol == "E") {
                // epsilon, do nothing
            } else {
                cout << "Parsing Error at token: " << currInput << endl;
                return 0;
            }
        }
        else {
            // Non-terminal
            auto key = make_pair(top->symbol, currInput);
            if (parsingTable.find(key) == parsingTable.end()) {
                cout << "Parsing Error at token: " << currInput << endl;
                return 0;
            }

            vector<string> prod = parsingTable[key];

            if (!(prod.size() == 1 && prod[0] == "E")) {
                vector<Node*> children;
                for (auto c : prod)
                    children.push_back(new Node{c});

                top->children = children;

                for (int i = children.size() - 1; i >= 0; i--)
                    st.push(children[i]);
            } else {
                top->children.push_back(new Node{"E"});
            }
        }
    }

    return 0;
}
