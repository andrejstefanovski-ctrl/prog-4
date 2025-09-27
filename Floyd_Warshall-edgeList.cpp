#include<bits/stdc++.h>

using namespace std;

int getW(vector<pair<pair<int,int>,int>> edges, int u, int v)
{
    for (auto& it : edges)
    {
        if (it.first.first == u && it.first.second == v)
        {
            return it.second;
        }
    }
    return INT_MAX;
}

void update(vector<pair<pair<int,int>,int>>& edges, int u, int v, int value)
{
    for (auto& it : edges)
    {
        if (it.first.first == u && it.first.second == v)
        {
            it.second = value;
            return;
        }
    }
    edges.push_back({{u,v},value});
}

void Floyd_warshall(int n, vector<pair<pair<int,int>,int>>& edges)
{
    for (int k=0; k<n; k++)
    {
        for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                int iDOk = getW(edges, i, k), kDOj = getW(edges, k, j), iDOj = getW(edges, i, j);
                if (kDOj < INT_MAX && iDOk < INT_MAX)
                {
                    if (iDOj > iDOk + kDOj)
                    {
                        update(edges, i, j, iDOk+kDOj);
                    }
                }
            }
        }
    }
}

int main()
{
    int n, e;
    cin >> n >> e;
    vector<pair<pair<int,int>,int>> edges;
    for (int i=0; i<e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({{u,v},w});
    }
    Floyd_warshall(n, edges);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            int x = getW(edges, i, j);
            if (x==INT_MAX) cout << i <<"->" << j <<": ∞" << endl;
            else cout << i << "->" << j << ": " << x << endl;
        }
    }
    return 0;
}