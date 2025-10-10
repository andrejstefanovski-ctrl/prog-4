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
        vector<int> pat;
        int teme = t;
        while (teme != s)
        {
            pat.push_back(teme);
            teme = vis[teme];
        }
        pat.push_back(s);
        reverse(pat.begin(), pat.end());
        for (int i=0; i<pat.size(); i++)
        {
            cout << pat[i];
            if (i != pat.size()-1) cout << "->";
        }
        cout << endl;
        teme = t;
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
    int n, e;
    cin >> n >> e;
    vector<vector<int>> adjList(n+1);
    vector<vector<int>> capacity(n, vector<int>(n+1,0));
    for (int i=0; i<e; i++)
    {
        int e1, e2, w;
        cin >> e1 >> e2 >> w;
        adjList[e1].push_back(e2);
        adjList[e2].push_back(e1);
        capacity[e1][e2] += w;
    }
    int s, t;
    cin >> s >> t;
    cout << Edmonds_Karp(n,s,t,adjList,capacity);
    return 0;
}