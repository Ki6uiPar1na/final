//stringCheck(a,abb,a*b+).cpp

#include<bits/stdc++.h>
using namespace std;
int main()
{
    string s; cin >> s;
    if(s == "a" || s == "abb"){
        cout << "Yes, the string matches the pattern a,(abb),(a*b+)." << endl;
    }
    else{
        bool flag = true;
        int i = 0;
        int cn = 0;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == 'a'){
                cn++;
            }
            else{
                break;
            }
        }
        for(int j = cn; j < s.length(); j++){
            if(s[j] != 'b'){
                flag = false;
                break;
            }
        }
        if(flag && cn >= 0 and s[s.length()-1] == 'b'){
            cout << "Yes, the string matches the pattern a,(abb),(a*b+)." << endl;
        }
        else{
            cout << "No, the string does not match the pattern a,(abb),(a*b+)." << endl;
        }
    }
}