#include <bits/stdc++.h>
using namespace std;

vector<int> rabin_karp(string& t, string& s)
{
    int p=13;
    int mod=1e9+9;
    int slen=s.length(), tlen=t.length();
    vector<long long> deg(max(slen, tlen));
    deg[0]=1;
    for (int i=1; i<max(slen,tlen); i++)
    {
        deg[i]=(deg[i-1]*p)%mod;
    }
    vector<long long> hash(tlen+1, 0);
    for (int i=0; i<tlen; i++)
    {
        hash[i+1] = (hash[i] + (t[i]-'a'+1) * deg[i]) % mod;
    }
    long long hash_string=0;
    for (int i=0; i<slen; i++)
    {
        hash_string = (hash_string + (s[i]-'a'+1) * deg[i]) % mod;
    } 
    vector<int> occurances;
    for (int i=0; i+slen-1<tlen; i++)
    {
        long long cur_h = (hash[i+slen]+mod-hash[i])%mod;
        if (cur_h == hash_string * deg[i] % mod)
        {
            occurances.push_back(i);
        }
    }
    return occurances;
}

int main()
{
    int T;
    cin >> T;
    vector<pair<int,vector<int>>> rezultati;
    for (int i=0; i<T; i++)
    {
        string a, b;
        cin >> a >> b;
        vector<int> temp = rabin_karp(a,b);
        rezultati.push_back({temp.size(), temp});
    }
    for (int i=0; i<T; i++)
    {
        if (rezultati[i].first == 0)
        {
            cout << "Not Found\n\n";
        }
        else
        {
            cout << rezultati[i].first << '\n';
            for (auto& it : rezultati[i].second)
            {
                cout << it+1 << " ";
            }
            cout << endl;
            cout << endl;
        }
    }
    return 0;
}