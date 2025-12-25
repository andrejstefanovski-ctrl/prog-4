// #include <bits/stdc++.h>
// using namespace std;

// struct MyInt {
//     string num;
//     friend bool operator>=(string a, string b);
//     friend int operator+(MyInt& a, MyInt& b);
//     friend int operator-(MyInt& a, MyInt& b);
// };

// string rm_nuli(string& s) {
//     int i=0;
//     while (i+1 < s.size() && s[i]=='0') {
//         i++;
//     }
//     return s.substr(i);
// }

// bool operator>=(string a, string b) {
//     a = rm_nuli(a);
//     b = rm_nuli(b);
//     if (a.size() != b.size()) return a.size() >= b.size();
//     return a>=b;
// }

// int operator+(MyInt& a, MyInt& b) {
//     string x=a.num, y=b.num;
//     reverse(x.begin(), x.end());
//     reverse(y.begin(), y.end());
//     string res="";
//     int ost=0;
//     for (int i=0; i<max(x.size(), y.size()); i++) {
//         int br1 = (i<x.size()) ? x[i]-'0' : 0;
//         int br2 = (i<y.size()) ? y[i]-'0' : 0;
//         int sum = br1+br2+ost;
//         res.push_back(sum%10 + '0');
//         ost = sum/10;
//     }
//     if (ost) {
//         res.push_back(ost + '0');
//     }
//     reverse(res.begin(), res.end());
//     return {rm_nuli(res)};
// }

// int main() {

//     return 0;
// }
#include <bits/stdc++.h>
using namespace std;

struct MyInt {
    string num;
    friend bool operator>=(string a, string b);
    friend MyInt operator+(MyInt& a, MyInt& b);
    friend MyInt operator-(MyInt& a, MyInt& b);
};

string rm_nuli(string s) {
    int i = 0;
    while (i+1<s.size() && s[i] == '0') {
        i++;
    }
    return s.substr(i);
}

bool operator>=(string a, string b) {
    a = rm_nuli(a);
    b = rm_nuli(b);
    if (a.size()!=b.size()) return a.size() > b.size();
    return a >= b;
}

MyInt operator+(MyInt& a, MyInt& b) {
    string x = a.num, y = b.num;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    string res = "";
    int ost = 0;

    for (int i=0; i<max(x.size(), y.size()); i++) {
        int br1 = (i < x.size()) ? x[i] - '0' : 0;
        int br2 = (i < y.size()) ? y[i] - '0' : 0;
        int sum = br1 + br2 + ost;
        res.push_back(sum % 10 + '0');
        ost = sum / 10;
    }

    if (ost) res.push_back(ost + '0');

    reverse(res.begin(), res.end());
    return {rm_nuli(res)};
}

MyInt operator-(MyInt& a, MyInt& b) {
    string x=a.num, y=b.num;
    if (!(x >= y)) swap(x, y);
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    string res = "";
    int borrow = 0;
    for (int i=0; i<x.size(); i++) {
        int br1 = x[i] - '0' - borrow;
        int br2 = (i < y.size()) ? y[i] - '0' : 0;

        if (br1 < br2) {
            br1 += 10;
            borrow = 1;
        } 
        else {
            borrow = 0;
        }

        res.push_back(br1 - br2 + '0');
    }

    reverse(res.begin(), res.end());
    return {rm_nuli(res)};
}

int main() {
    MyInt a{"001234"};
    MyInt b{"567"};

    MyInt c = a + b;
    MyInt d = a - b;

    cout << c.num << "\n"; // 1801
    cout << d.num << "\n"; // 667

    return 0;
}
