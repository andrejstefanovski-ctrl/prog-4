#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

vector<int> Dijkstra(int start, int n, vector<vector<pair<int,int>>> G)
{
    vector<int> dist(n);
    for (int i=0; i<n; i++)
    {
        dist[i]=INT_MAX;
    }
    priority_queue<pair<int,int>> pq;
    dist[start]=0;
    pq.push({0, start});
    vector<bool> vis(n, 0);
    while (!pq.empty())
    {
        pair<int,int> state = pq.top();
        pq.pop();
        int city = state.second, weight= -state.first;
        if (!vis[city])
        {
            vis[city] = 1;
            for (auto edge : G[city])
            {
                int next = edge.first, w = edge.second;
                if (dist[next] > dist[city] + w)
                {
                    dist[next] = dist[city] + w;
                    pq.push({-dist[next], next});
                }
            }
        }
    }
    return dist;
}

int main()
{
    int n, e;
    cin >> n >> e;
    vector<vector<pair<int,int>>> G(n);
    //FORMAT: od-do-tezina
    for (int i=0; i<e; i++)
    {
        int e1, e2, w;
        cin >> e1 >> e2 >> w;
        G[e1].push_back({e2, w});
    }
    int start;
    cin >> start;
    vector<int> dist = Dijkstra(start, n, G);
    for (int i=0; i<n; i++)
    {
        cout << i << ":" << dist[i] << endl;
    }
    return 0;
}