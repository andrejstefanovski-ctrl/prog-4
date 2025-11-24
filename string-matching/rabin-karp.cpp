#include <bits/stdc++.h>
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

int main()
{
    string s, t;
    cin >> s >> t;
    vector<int> v = rabin_karp(s,t);
    for (auto& it:v)
    {
        cout << it << " ";
    }
    return 0;
}