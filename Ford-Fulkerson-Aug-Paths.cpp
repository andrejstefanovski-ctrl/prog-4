#include <bits/stdc++.h>
using namespace std;

int DFS(int u, int t, int flow, vector<int>& vis, vector<int>& parent, vector<vector<int>>& adjList, vector<vector<int>>& capacity)
{
    if (u == t) return flow;
    vis[u] = 1;

    for (int v : adjList[u])
    {
        if (!vis[v] && capacity[u][v] > 0)
        {
            parent[v] = u;
            int pushed = DFS(v, t, min(flow, capacity[u][v]), vis, parent, adjList, capacity);
            if (pushed > 0) return pushed;
        }
    }
    return 0;
}

int Ford_Fulkerson(int n, int s, int t, vector<vector<int>>& adjList, vector<vector<int>>& capacity)
{
    int maxFlow = 0;
    while (true)
    {
        vector<int> vis(n, 0), parent(n, -1);
        int pushed = DFS(s, t, INT_MAX, vis, parent, adjList, capacity);
        if (!pushed) break;
        maxFlow += pushed;

        int v = t;
        vector<int> path;
        while (v != -1) 
        {
            path.push_back(v); v = parent[v]; 
        }
        reverse(path.begin(), path.end());
        for (int i=0; i<path.size(); i++) 
        { 
            cout<<path[i];
            if(i+1<path.size())cout<<"->";
        }
        cout << endl;

        v = t;
        while (parent[v] != -1)
        {
            int u = parent[v];
            capacity[u][v] -= pushed;
            capacity[v][u] += pushed;
            v = u;
        }
    }
    return maxFlow;
}

int main()
{
    int n, e;
    cin >> n >> e;
    vector<vector<int>> adjList(n);
    vector<vector<int>> capacity(n, vector<int>(n,0));

    for(int i=0;i<e;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adjList[u].push_back(v); adjList[v].push_back(u);
        capacity[u][v]+=w;
    }

    int s,t;
    cin>>s>>t;
    cout << Ford_Fulkerson(n,s,t,adjList,capacity) << endl;
}
