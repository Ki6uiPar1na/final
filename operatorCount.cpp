#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s; cin >> s;
    int countOperators = 0;
    set<string> operators = {"+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "=", "+=", "-=", "*=", "/=", "%="};
    for(int i = 0; i < s.length(); i++){
        string op;
        op += s[i];
        if(i + 1 < s.length()){
            op += s[i+1];
            if(operators.find(op) != operators.end()){
                cout << "Operator found: " << op << endl;
                countOperators++;
                i++;
                continue;
            }
            op.pop_back();
        }
        if(operators.find(op) != operators.end()){
            countOperators++;
            cout << "Operator found: " << op << endl;
        }
    }
    cout << "Total operators found: " << countOperators << endl;
    return 0;
}