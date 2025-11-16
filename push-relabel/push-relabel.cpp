#include <bits/stdc++.h>
using namespace std;

void push(int u, int v, vector<int>& visina, vector<int>& ostatok, vector<vector<int>>& c, vector<vector<int>>& f, queue<int>& aktivni_teminja)
{
    int d = min(ostatok[u], c[u][v]-f[u][v]); //kolku protok moze maks da pustime od u do v
    f[u][v]+=d;
    f[v][u]-=d;
    ostatok[u]-=d;
    ostatok[v]+=d;
    if (d!=0 && ostatok[v]==d) //ova ako v stane aktivno, odnosno pominuva nekakov protok do nego
    {
        aktivni_teminja.push(v);
    }
}

void relabel(int u, int n, vector<int>& visina, vector<int>& ostatok, vector<vector<int>>& c, vector<vector<int>>& f, queue<int>& aktivni_teminja)
{
    int d = INT_MAX;
    for (int v=0; v<n; v++)
    {
        if (c[u][v]-f[u][v]>0) //ako seuste moze da se pusti protok niz rebroto u-v
        {
            d=min(d, visina[v]); //izberi go toa v taka sto ima najmala visina
        }
    }
    if (d<INT_MAX)
    {
        visina[u]=d+1; //nadogradi ja visinata na u
    }
}

void discharge(int u, int n, vector<int>& checkpoint, vector<int>& visina, vector<int>& ostatok, vector<vector<int>>& c, vector<vector<int>>& f, queue<int>& aktivni_teminja)
{
    while (ostatok[u] > 0) //da se oslobodime od celiot protok sto e vo u
    {
        if (checkpoint[u] < n) //ako seuste imame sosedi za koi mozeme da probame
        {
            int v = checkpoint[u];
            if (c[u][v]-f[u][v]>0 && visina[u]>visina[v])
            {
                push(u,v,visina,ostatok,c,f,aktivni_teminja);
            }
            else
            {
                checkpoint[u]++; //go menuvame checkpointot, bidejki nekoj uslov ne e zadovolen(za push) za momentalniot sosed za nareden pat da ne pocneme so proverka od pocetok
            }
        }
        else
        {
            relabel(u,n,visina,ostatok,c,f,aktivni_teminja);
            checkpoint[u]=0; //nova visina na u, pa znaci pocni so proverka od pocetok
        }
    }
}

int max_flow(int s, int t, int n, vector<int>& checkpoint, vector<int>& visina, vector<int>& ostatok, vector<vector<int>>& c, vector<vector<int>>& f, queue<int>& aktivni_teminja)
{
    visina.resize(n,0);
    visina[s]=n;
    f.resize(n, vector<int>(n,0));
    ostatok.resize(n,0);
    ostatok[s]=INT_MAX; //moze kaj sakame da pushneme

    for (int i=0; i<n; i++)
    {
        if (i!=s)
        {
            push(s,i,visina,ostatok,c,f,aktivni_teminja); //pusti protok do site mozni sosedi na izvorot
        }
    }
    checkpoint.resize(n,0);

    while(!aktivni_teminja.empty())
    {
        int u = aktivni_teminja.front();
        aktivni_teminja.pop();
        if (u!=s && u!=t) //ako aktivnoto teme ne e izvor ili slivnik isprazni go, napravi go neaktivno
        {
            discharge(u,n,checkpoint,visina,ostatok,c,f,aktivni_teminja);
        }
    }
    
    int max_flow=0;
    for (int i=0; i<n; i++)
    {
        max_flow+=f[i][t];
    }
    return max_flow;
}

int main()
{
    int n, m; //broj na teminja/rebra
    cin >> n >> m;
    vector<vector<int>> c, f; //kapacitet, protok
    vector<int> visina, ostatok, checkpoint; //visina, ostatok, indeks na sosed na koj probuvame da mu dodademe
    queue<int> aktivni_teminja; //queue od aktivni teminja, odnosno imaat ostatok
    c.resize(n, vector<int>(n,0));
    for (int i=0; i<m; i++)
    {
        int u,v,w;
        cin >> u >> v >> w;
        c[u][v]=w;
    }
    int s, t;
    cin >> s >> t;
    int rez = max_flow(s,t,n,checkpoint,visina,ostatok,c,f,aktivni_teminja);
    cout << rez;
    return 0;
}