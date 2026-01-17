#include<bits/stdc++.h>
using namespace std;
int main()
{
    map<string, bool> identifierMap; map<char, bool> specialCharMap;
    identifierMap["auto"] = true, identifierMap["break"] = true, identifierMap["case"] = true;

    specialCharMap['$'] = true, specialCharMap['@'] = true, specialCharMap['!'] = true;
    
    string s; cin >> s;
    char ch = s[0];
    if(((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')){
        for(int i = 0; i < s.length(); i++){
            if(specialCharMap.find(s[i]) != specialCharMap.end()){
                cout << "The string is not a valid identifier." << endl;
                return 0;
            }
        }
        if(identifierMap.find(s) != identifierMap.end()){
            cout << "The string is not a valid identifier." << endl;
        }
        else{
            cout << "The string is a valid identifier." << endl;
        }
    }
    else{
        cout << "The string is not a valid identifier." << endl;
    }
    return 0;
}