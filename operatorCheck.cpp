#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s; cin >> s;
    set<string> operators = {"+", "-", "*", "/", "%", "++", "--", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "=", "+=", "-=", "*=", "/=", "%="};
    if(operators.find(s) != operators.end()){
        cout << "The string is an operator." << endl;
    }
    else{
        cout << "The string is not an operator." << endl;
    }
}