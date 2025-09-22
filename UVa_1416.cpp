#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> Floyd_Warshall(vector<vector<int>> dist)
{
    int n = dist.size();
    for (int k=0; k<n; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                if (dist[i][j] > dist[i][k] + dist[k][j] && dist[i][k] != INT_MAX && dist[k][j] != INT_MAX)
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    for (int i=0; i<n; i++)
    {
        if (dist[i][i] < 0)
        {
            cerr << "Negativen ciklus!";
            return {};
        }
    }
    return dist;
}

int calculate(vector<vector<int>> res, int n)
{
    int sum=0;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (res[i][j] == INT_MAX) continue;
            else sum+=res[i][j];
        }
    }
    return sum;
}

int main()
{
    int n, e, l;
    cin >> n >> e >> l;
    vector<vector<int>> dist(n, vector<int>(n, l));
    for (int i=0; i<e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;v--;
        dist[u][v] = w;
        dist[v][u] = w;
    }
    for (int i=0; i<n; i++)
    {
        dist[i][i]=0;
    }
    vector<vector<int>> res = Floyd_Warshall(dist);
    int kon_rez = calculate(res, n), ce = calculate(res, n);
    cout << kon_rez << " ";
    
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (dist[i][j] < l)
            {
                int temp = dist[i][j];
                dist[i][j] = dist[j][i] = l;
                vector<vector<int>> newDist = Floyd_Warshall(dist);
                int ce_prim = calculate(newDist, n);
                kon_rez = max(kon_rez, ce_prim);
                dist[i][j] = dist[j][i] = temp;
            }
        }
    }
    cout << kon_rez;
    return 0;
}
