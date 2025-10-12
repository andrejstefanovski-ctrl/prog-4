#include <bits/stdc++.h>
using namespace std;

int BFS(int s, int t, vector<int>& vis, vector<vector<int>>& adjList, vector<vector<int>>& capacity)
{
    fill(vis.begin(), vis.end(), -1);
    vis[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INT_MAX});
    while (!q.empty())
    {
        int teme = q.front().first;
        int protok = q.front().second;
        q.pop();
        for (auto& it : adjList[teme])
        {
            if (vis[it] == -1 && capacity[teme][it])
            {
                vis[it] = teme;
                int nov_protok = min(protok, capacity[teme][it]);
                if (it == t)
                {
                    return nov_protok;
                }
                q.push({it, nov_protok});
            }
        }
    }
    return 0;
}

int Edmonds_Karp(int n, int s, int t, vector<vector<int>> &adjList, vector<vector<int>>& capacity)
{
    int protok = 0;
    vector<int> vis(n);
    int nov_protok;
    while (nov_protok = BFS(s, t, vis, adjList, capacity))
    {
        protok += nov_protok;
        int teme = t;
        while (teme != s)
        {
            int prev = vis[teme];
            capacity[prev][teme] -= nov_protok;
            capacity[teme][prev] += nov_protok;
            teme = prev;
        }
    }
    return protok;
}

int main() 
{
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<pair<pair<int,int>,int>> rebra;
    vector<vector<int>> adjList(n);
    vector<vector<int>> capacity(n, vector<int>(n,0)), cTemp;
    int minFlow = INT_MAX;
    pair<int, int> bestEdge;
    
    for (int i=0; i<m; i++)
    {
        int e1, e2, w;
        cin >> e1 >> e2 >> w;
        adjList[e1].push_back(e2);
        adjList[e2].push_back(e1);
        capacity[e1][e2] = w;
        rebra.push_back({{e1, e2}, w});
    }

    for (auto& e : rebra)
    {
        cTemp = capacity;
        int e1 = e.first.first, e2 = e.first.second, w = e.second;

        cTemp[e1][e2] = 0;
        auto it1 = find(adjList[e1].begin(), adjList[e1].end(), e2);
        auto it2 = find(adjList[e2].begin(), adjList[e2].end(), e1);
        if (it1 != adjList[e1].end()) adjList[e1].erase(it1);
        if (it2 != adjList[e2].end()) adjList[e2].erase(it2);

        int flow = Edmonds_Karp(n, s, t, adjList, capacity);

        if (flow < minFlow)
        {
            minFlow = flow;
            bestEdge = {e1, e2};
        }

        adjList[e1].push_back(e2);
        adjList[e2].push_back(e1);
        cTemp[e1][e2] = w;
    }

    cout << bestEdge.first << " -> " << bestEdge.second << endl;
    cout << minFlow << endl;

    return 0;
}