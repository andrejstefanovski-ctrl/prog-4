#include <bits/stdc++.h>
using namespace std;

struct MyInt {
    string num;
    friend bool operator>=(string a, string b);
    friend MyInt operator+(MyInt& a, MyInt& b);
    friend MyInt operator-(MyInt& a, MyInt& b);
    friend MyInt operator*(MyInt& a, MyInt& b);
    friend MyInt operator/(MyInt& a, MyInt& b);
    friend MyInt operator%(MyInt& a, MyInt& b);
};

string rm_nuli(string s) {
    int i = 0;
    while (i+1<s.size() && s[i] == '0') {
        i++;
    }
    return s.substr(i);
}

ostream& operator<<(ostream& os, const MyInt& a)
{
    os << rm_nuli(a.num);
    return os;
}

istream& operator>>(istream& is, MyInt& a)
{
    is >> a.num;
    a.num = rm_nuli(a.num);
    return is;
}

bool operator==(MyInt& a, MyInt& b) {
    return rm_nuli(a.num) == rm_nuli(b.num);
}

bool operator>=(string a, string b) {
    a = rm_nuli(a);
    b = rm_nuli(b);
    //stefanovski
    if (a.size() != b.size())
        return a.size() > b.size();

    return !(a<b);
}

bool operator<(MyInt& a, MyInt& b) {
    string x = rm_nuli(a.num);
    string y = rm_nuli(b.num);
    if (x.size() != y.size()) return x.size() < y.size();
    return x < y;
}

bool operator<=(MyInt& a, MyInt& b) {
    return (a < b) || (a == b);
}

vector<MyInt> dijkstraPrimes(MyInt n)
{
    vector<pair<MyInt,MyInt>> pool;
    vector<MyInt> primes;
    MyInt eden{"1"};
    MyInt dva{"2"};
    for (MyInt i=dva; i<=n; i=i+eden) {
        bool isComposite = false;
        for (int j=0; j<pool.size(); j++) {
            while (pool[j].second < i) {
                pool[j].second = pool[j].second + pool[j].first;
            }
            if (pool[j].second == i) {
                isComposite = true;
            }
        }

        if (!isComposite) {
            pool.push_back({i, i*i});
            primes.push_back(i);
        }
    }

    return primes;
}

MyInt operator+(MyInt& a, MyInt& b) {
    string x = a.num, y = b.num;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    string res = "";
    int ost = 0;
    //andrej stefanovski
    for (int i=0; i<max(x.size(), y.size()); i++) {
        int br1 = (i < x.size()) ? x[i] - '0' : 0;
        int br2 = (i < y.size()) ? y[i] - '0' : 0;
        int sum = br1 + br2 + ost;
        res.push_back(sum % 10 + '0');
        ost = sum / 10;
    }

    if (ost) res.push_back(ost + '0');

    reverse(res.begin(), res.end()); //andrej
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
        //andrej
        if (br1 < br2) {
            br1 += 10;
            borrow = 1;
        } 
        else {
            borrow = 0;
        }

        res.push_back(br1 - br2 + '0');
    }

    reverse(res.begin(), res.end()); //andrej
    return {rm_nuli(res)};
}

MyInt operator*(MyInt& a, MyInt& b) {
    string x=a.num, y=b.num;
    if (x == "0" || y == "0") return {"0"};
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());
    vector<int> res(x.size() + y.size(), 0);

    for (int i=0; i<x.size(); i++) {
        for (int j=0; j<y.size(); j++) {
            res[i+j] += (x[i]-'0') * (y[j]-'0'); //stefanovski
        }
    }

    for (int i=0; i<res.size(); i++) {
        int ost = res[i]/10;
        res[i]%=10;
        if (i+1 < res.size()) {
            res[i+1] += ost;
        }
    }

    string s="";
    for (auto& it : res) s.push_back(it+'0');
    reverse(s.begin(), s.end());
    return {rm_nuli(s)};
}

MyInt operator/(MyInt& a, MyInt& b) {
    string x = rm_nuli(a.num);
    string y = rm_nuli(b.num);

    if (y == "0") {
        cerr << "KAKO DELIS SO 0?";
        return {"-1012007"};
    }
    string cur = "";
    string res = "";
    //andrej
    for (int i = 0; i < x.size(); i++) {
        cur.push_back(x[i]);
        cur = rm_nuli(cur);

        int cnt = 0;
        while (cur >= y) {
            MyInt t1{cur}, t2{y};
            cur = (t1 - t2).num;
            cnt++;
        }
        res.push_back(cnt + '0');
    }

    return {rm_nuli(res)};
}

MyInt operator%(MyInt& a, MyInt& b) {
    string x = rm_nuli(a.num);
    string y = rm_nuli(b.num);

    if (y == "0") {
        cerr << "KAKO MODUL SO 0?";
        return {"-1012007"};
    }
    string cur = "";
    for (int i=0; i<x.size(); i++) {
        cur.push_back(x[i]);
        cur = rm_nuli(cur);

        while (cur >= y) {
            MyInt t1{cur}, t2{y};
            cur = (t1 - t2).num;
        }
    }
    return {rm_nuli(cur)};
}

int main() {
    MyInt a{"146738236478392347389234678392345674839234783947389237829467389236782947389"};
    MyInt b{"50744673827832738237283723827382372837823"};

    MyInt c = a + b;
    MyInt d = a - b;
    MyInt e = a * b;
    MyInt f = a / b;
    MyInt g = a % b;

    cout << c.num << "\n";
    cout << d.num << "\n";
    cout << e.num << "\n";
    cout << f.num << "\n";
    cout << g.num << "\n";

    MyInt n;
    cin >> n;
    vector<MyInt> niza = dijkstraPrimes(n);
    for (auto& it : niza) {
        cout << it << " ";
    }
    return 0;
}
