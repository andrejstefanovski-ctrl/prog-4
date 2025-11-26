#include <bits/stdc++.h>
using namespace std;

long long get_hash(int l, int r, vector<long long>& h, vector<long long>& p_pow, int n, long long mod) 
{
    long long res = (h[r+1] - h[l] + mod) % mod;
    res = (res * p_pow[n-l]) % mod;
    return res;
}


int main() 
{
    string s, t;
    int k;
    cin >> s >> t >> k;

    int n = s.size();
    vector<int> bad(n+1, 0);

    for (int i=0; i<n; i++) 
    {
        if (t[s[i] - 'a'] == '0')
        {
            bad[i+1] = bad[i] + 1;
        }
        else
        {
            bad[i+1] = bad[i];
        }
    }


    long long mod = 1e9 + 9;
    long long p = 31;

    vector<long long> p_pow(n+1);
    p_pow[0] = 1;
    for (int i=1; i<=n; i++)
    {
        p_pow[i] = (p_pow[i-1] * p) % mod;
    }
    vector<long long> h(n+1, 0);
    for (int i=0; i<n; i++) 
    {
        h[i+1] = (h[i] + (s[i]-'a'+1) * p_pow[i]) % mod;
    }

    unordered_set<long long> seen;
    seen.reserve(1e5);

    for (int i=0; i<n; i++) 
    {
        for (int j=i; j<n; j++) 
        {
            int badctr = bad[j+1] - bad[i];
            if (badctr > k) break;
            long long hh = get_hash(i, j, h, p_pow, n, mod);
            seen.insert(hh);
        }
    }
    cout << seen.size();
    return 0;
}
