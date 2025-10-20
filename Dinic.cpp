#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int e1, e2;
    long long c, f = 0;
    Edge(int e1, int e2, long long c):e1(e1),e2(e2),c(c){}
};

struct Dinic
{
    vector<Edge> edges;
    vector<vector<int>> adjList;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
    Dinic(int n, int s, int t):n(n),s(s),t(t)
    {
        adjList.resize(n);
        level.resize(n);
        ptr.resize(n);
    }
    void add(int e1, int e2, long long c)
    {
        edges.emplace_back(e1, e2, c);
        edges.emplace_back(e2, e1, 0);
        adjList[e1].push_back(m);
        adjList[e2].push_back(m+1);
        m+=2;
    }
     bool bfs() 
     {
        while (!q.empty()) 
        {
            int v = q.front();
            q.pop();
            for (int id : adjList[v]) 
            {
                if (edges[id].c == edges[id].f)
                    continue;
                if (level[edges[id].e2] != -1)
                    continue;
                level[edges[id].e2] = level[v] + 1;
                q.push(edges[id].e2);
            }
        }
        return level[t] != -1;
    }
    long long dfs(int e1, long long pushed)
    {
        if (pushed==0) return 0;
        if (e1==t) return pushed;
        for (auto& cid = ptr[e1]; cid < adjList[e1].size(); cid++)
        {
            int id = adjList[e1][cid];
            int e2 = edges[id].e2;

            if (level[e1]+1 != level[e2]) continue;

            long long tr = dfs(e2, min(pushed, edges[id].c - edges[id].f));
            if (tr==0) continue;
            edges[id].f += tr;
            edges[id^1].f -= tr;
            return tr;
        }
        return 0;
    }
    long long flow() 
    {
        long long f=0;
        while (1)
        {
            fill(level.begin(), level.end(), -1);
            level[s]=0;
            q.push(s);
            if (!bfs()) break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s,INT_MAX))
            {
                f+=pushed;
            }
        }
        return f;
    }
};

int main()
{
    int n,m,s,t;
    cin >> n >> m >> s >> t;
    Dinic d(n,s,t);
    for (int i=0; i<n; i++)
    {
        int e1,e2,w;
        cin >> e1 >> e2 >> w;
        d.add(e1,e2,w);
    }
    long long f = d.flow();
    cout << f;
    return 0;
}