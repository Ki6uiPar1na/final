#include<bits/stdc++.h>
using namespace std;
int main()

{
    string s; cin >> s;
    bool isComment = false;
    if(s.substr(0,2) == "//" || (s.substr(0, 2) == "/*" && s.substr(s.length()-2,2) == "*/")){
        isComment = true;
    }
    if(isComment){
        cout << "The line is a comment line." << endl;
    }
    else{
        cout << "The line is not a comment line." << endl;
    }
}