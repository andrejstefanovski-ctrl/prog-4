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

void Print(vector<vector<int>> res, int n)
{
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (res[i][j] == INT_MAX) cout << "∞ ";
            else cout << res[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n, e;
    cin >> n >> e;
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (int i=0; i<e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w;
    }
    for (int i=0; i<n; i++)
    {
        dist[i][i]=0;
    }
    vector<vector<int>> res = Floyd_Warshall(dist);

    Print(res, n);
    return 0;
}