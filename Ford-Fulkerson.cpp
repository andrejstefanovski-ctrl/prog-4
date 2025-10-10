#include <bits/stdc++.h>
using namespace std;

int DFS(int u, int t, int flow, vector<int>& vis, vector<vector<int>>& adjList, vector<vector<int>>& capacity)
{
    if (u == t) return flow;

    vis[u] = 1;

    for (int v : adjList[u])
    {
        if (!vis[v] && capacity[u][v] > 0)
        {
            int new_flow = min(flow, capacity[u][v]);
            int pushed = DFS(v, t, new_flow, vis, adjList, capacity);
            if (pushed > 0)
            {
                capacity[u][v] -= pushed;
                capacity[v][u] += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

int Ford_Fulkerson(int n, int s, int t, vector<vector<int>>& adjList, vector<vector<int>>& capacity)
{
    int maxFlow = 0;
    while (1)
    {
        vector<int> vis(n, 0);
        int pushed = DFS(s, t, INT_MAX, vis, adjList, capacity);
        if (pushed == 0) break;
        maxFlow += pushed;
    }
    return maxFlow;
}

int main()
{
    int n, e;
    cin >> n >> e;

    vector<vector<int>> adjList(n);
    vector<vector<int>> capacity(n, vector<int>(n, 0));

    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        capacity[u][v] += w;
    }

    int s, t;
    cin >> s >> t;

    cout << Ford_Fulkerson(n, s, t, adjList, capacity) << endl;
    return 0;
}
