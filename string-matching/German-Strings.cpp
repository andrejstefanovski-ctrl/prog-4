//
// Created by Andrej on 12/1/2025.
//
#include <cstring>
#include <string>
#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

vector<int> rabin_karp(string& s, string& t) //s e pattern a t e string vo koj barame pattern
{
    int p=13; //mal prost broj
    int mod=1e9+9; //koristime modul za da izbegneme pregolemi brojki. modulot e prost broj
    int slen=s.length(), tlen=t.length();
    vector<long long> deg(max(slen, tlen)); //niza od stepeni na p po moudl mod
    deg[0]=1; //ova e p^0
    for (int i=1; i<max(slen,tlen); i++)
    {
        deg[i]=(deg[i-1]*p)%mod; //za da bide stringot so unikatna vrednost, odnosno da ne bide ista vrednosta na ABC so BCA primer
    }
    //ANDREJ STEFANOVSKI
    vector<long long> hash(tlen+1, 0);
    for (int i=0; i<tlen; i++)
    {
        hash[i+1] = (hash[i] + (t[i]-'a'+1) * deg[i]) % mod; //presmetaj hash vrednost na t[0,1,...,tlen-1]
    }
    long long hash_string=0; //hash na petternot s
    for (int i=0; i<slen; i++)
    {
        hash_string = (hash_string + (s[i]-'a'+1) * deg[i]) % mod;
    }
    vector<int> occurances;
    for (int i=0; i+slen-1<tlen; i++) //pomini gi site substringovi od dolzina slen vo t
    {
        long long cur_h = (hash[i+slen]+mod-hash[i])%mod; //momentalniot hash e prefix(desno)-prefix(levo). +mod e za da izbegneme negativni vrednosti po moduliranje
        if (cur_h == hash_string * deg[i] % mod) //shiftaj go predpresmetaniot string za da bide kako za momentalniot substring
        {
            occurances.push_back(i);
        }
    }
    return occurances;
}

class GermanString {
    uint32_t len;
    char data[12];

    bool isShort() const {
        return len <= 12;
    }

    char* getPtr() const {
        char* p;
        memcpy(&p, data + 4, sizeof(p));
        //ANDREJ STEFANOVSKI
        return p;
    }

    void setPtr(char* p) {
        memcpy(data + 4, &p, sizeof(p));
    }

public:
    GermanString(const string& s) {
        len = s.size();

        if (isShort()) {
            memcpy(data, s.data(), len);
            if (len < 12) memset(data + len, 0, 12 - len); //stavi gi nuli do kraj, ne treba ptr
        }
        else {
            memcpy(data, s.data(), 4);
            char* heap = new char[len];
            memcpy(heap, s.data(), len);
            setPtr(heap);
        }
    }

    GermanString(const GermanString& o) {
        len = o.len;
        if (isShort()) {
            memcpy(data, o.data, 12);
        }
        else {
            memcpy(data, o.data, 4);
            char* heap = new char[len];
            memcpy(heap, o.getPtr(), len);
            setPtr(heap);
        }
    }

    GermanString& operator=(const GermanString& o) {
        len = o.len;
        if (isShort()) {
            memcpy(data, o.data, 12);
        }
        else {
            memcpy(data, o.data, 4);
            char* heap = new char[len];
            memcpy(heap, o.getPtr(), len);
            setPtr(heap);
        }
        return *this;
    }

    ~GermanString() {
        if (!isShort())
            delete[] getPtr();
    }

    string makeString() const {
        if (isShort()) return string(data, len);
        return string(getPtr(), len); //ANDST
    }

    int getLen() const {
        return len;
    }

    char& operator[](int index) {
        if (isShort()) {
            return data[index];
        }
        return getPtr()[index];
    }

    bool operator==(const GermanString& o) const {
        if (len != o.len) return false;
        if (memcmp(data, o.data, 4) != 0) return false;

        if (isShort())
            return memcmp(data, o.data, len) == 0;

        return memcmp(getPtr(), o.getPtr(), len) == 0;
    }

    char at(int ind) {
        if (isShort()) {
            return data[ind];
        }
        return getPtr()[ind];
    }

    GermanString operator+(const GermanString& o) const {
        string temp = this->makeString() + o.makeString();
        return GermanString(temp);
    }

    bool find(string s) {
        string a = this->makeString();
        vector<int> occurances = rabin_karp(s, a);
        //ANDREJ STEFANOVSKI
        if (occurances.size() == 0) {
            return false;
        }
        return true;
    }

    bool find(GermanString s) {
        string ss = s.makeString();
        return find(ss);
    }

    bool empty() const {
        return len == 0;
    }

    void clear() {
        if (!isShort()) {
            delete[] getPtr();
        }
        len = 0;
        memset(data, 0, 12);
    }
};

ostream& operator<<(ostream& os, const GermanString& gs) {
    os << gs.makeString();
    return os;
}

int main() {
    GermanString gha("brout");
    cout << gha << '\n';
    string c = "Proba1";
    GermanString g(c);
    cout << g.at(2) << '\n';
    string txt="Ova e proben tekst", patternT="proben", patternF="prboen";
    GermanString gg(txt);
    GermanString cc1(patternT), cc2(patternF);
    GermanString ck = cc1+cc2;
    cout << ck << '\n';
    bool x = ck==gg, y = ck==ck;
    cout << x << " " << y << '\n';
    cout << ck.getLen() << '\n';
    cout << gg.find(patternT) << " " << gg.find(patternF) << '\n';
    cout << c[1] << '\n';
    c[1]='k';
    cout << c << '\n';
    GermanString ng("Eve ti neshto"), nng("kratko");
    GermanString ng1 = ng, nng1=nng;
    cout << ng1 << '\n';
    cout << nng1 << '\n';
    ng1 = nng1;
    cout << ng1 << '\n';
    cout << gg.find(nng) << '\n';
    cout << gg.find(cc1);
    return 0;
}