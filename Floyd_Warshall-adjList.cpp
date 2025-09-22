#include <bits/stdc++.h>
using namespace std;

int getW(const vector<pair<int,int>>& adjList, int v) 
{
    for (auto &it : adjList) 
    {
        if (it.first == v) return it.second;
    }
    return INT_MAX;
}

void updateEdge(vector<pair<int,int>>& adjList, int v, int newW) 
{
    for (auto &it : adjList) 
    {
        if (it.first == v) 
        {
            it.second = newW;
            return;
        }
    }
    adjList.push_back({v, newW});
}

int main() 
{
    int n, e;
    cin >> n >> e;

    vector<vector<pair<int,int>>> adjList(n);

    for (int i=0; i<e; i++) 
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v, w});
    }

    for (int i=0; i<n; i++)
    {
        if (getW(adjList[i], i) == INT_MAX)
        {
            adjList[i].push_back({i, 0});
        }
    }

    for (int k=0; k<n; k++) 
    {
        for (int i=0; i<n; i++) 
        {
            int iDOk = getW(adjList[i], k);
            if (iDOk == INT_MAX) continue;

            for (int j=0; j<n; j++) 
            {
                int iDOj = getW(adjList[i], j);
                int kDOj = getW(adjList[k], j);
                if (kDOj == INT_MAX) continue;

                if (iDOj > iDOk + kDOj) 
                {
                    updateEdge(adjList[i], j, iDOk + kDOj);
                }
            }
        }
    }

    for (int i=0; i<n; i++) 
    {
        for (int j=0; j<n; j++) 
        {
            int d = getW(adjList[i], j);
            if (d == INT_MAX) cout << "∞ ";
            else cout << d << " ";
        }
        cout << endl;
    }

    return 0;
}
