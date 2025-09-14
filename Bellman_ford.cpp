#include <iostream>
#include <vector>
#include <climits>

using namespace std;

vector<int> BellmanFord(int start, int n, vector<vector<pair<int,int>>> G)
{
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    for (int i=0; i<n-1; i++)
    {
        for (int u=0; u<n; u++)
        {
            if (dist[u] == INT_MAX) continue;
            for (auto edge : G[u])
            {
                int v = edge.first;
                int w = edge.second;
                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }

    for (int u=0; u<n; u++)
    {
        if (dist[u] == INT_MAX) continue;
        for (auto edge : G[u])
        {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w)
            {
                cout << "Negativen ciklus!" << endl;
                return {};
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

    for (int i=0; i<e; i++)
    {
        int e1, e2, w;
        cin >> e1 >> e2 >> w;
        G[e1].push_back({e2, w});
    }
    int start;
    cin >> start;
    vector<int> dist = BellmanFord(start, n, G);
    if (!dist.empty())
    {
        for (int i=0; i<n; i++)
        {
            cout << i << ":" << dist[i] << endl;
        }
    }
    return 0;
}
