#include <bits/stdc++.h>

using namespace std;

void dfs(int node, vector<vector<pair<int,int>>>& G, vector<bool>& visited)
{
    visited[node] = true;
    for (auto& edge : G[node])
    {
        int neighbor = edge.first;
        if (!visited[neighbor])
        {
            dfs(neighbor, G, visited);
        }
    }
}

bool isConnected(vector<vector<pair<int,int>>>& G)
{
    vector<bool> visited(G.size(), false);
    dfs(0, G, visited);

    for (bool v : visited)
    {
        if (!v) return false;
    }
    return true;
}

int main()
{
    srand(time(NULL));
    int ed = 0;
    unordered_set<string> seenEdges;
    int n = (rand()%50)+50;
    vector<vector<pair<int,int>>> G(n);

    for (int i=0; i<n-1; i++)
    {
        int to = i+1;
        int w = (rand()%206)-5;

        string edge1 = to_string(i) + "-" + to_string(to);
        string edge2 = to_string(to) + "-" + to_string(i);

        if (seenEdges.find(edge1) == seenEdges.end() && seenEdges.find(edge2) == seenEdges.end())
        {
            G[i].push_back({to, w});
            seenEdges.insert(edge1);
        }
    }

    for (int i=0; i<n; i++)
    {
        ed = 1+(rand()%(n-1));
        for (int j=0; j<ed; j++)
        {
            int to = rand()%n;
           // int w = (rand() % 201)+1;
            int w = (rand()%206)-5;


            while (to == i)
            {
                to = rand()%n;
            }

            string edge1 = to_string(i) + "-" + to_string(to);
            string edge2 = to_string(to) + "-" + to_string(i);

            if (seenEdges.find(edge1) == seenEdges.end() && seenEdges.find(edge2) == seenEdges.end())
            {
                G[i].push_back({to, w});
                seenEdges.insert(edge1);
            }
        }
    }
    if (!isConnected(G))
    {
        cout << "Nepovrzan graf" << endl;
    } else
    {
        cout << "Povrzan graf" << endl;
    }
    int e=0;
    for (int i=0; i<G.size(); i++)
    {
        for (int j=0; j<G[i].size(); j++)
        {
            e++;
        }
    }
    cout << n << " " << e << endl;
    for (int i=0; i<G.size(); i++)
    {
        for (int j=0; j<G[i].size(); j++)
        {
            cout << i << " " << G[i][j].first << " " << G[i][j].second << endl;
        }
    }
    return 0;
}