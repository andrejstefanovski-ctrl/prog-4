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
    vector<vector<pair<int,int>>> G(50);
    unordered_set<string> seenEdges;

    for (int i=0; i<49; i++)
    {
        int to = i+1;
        int w = (rand()%106)-5; //za test primeri 1-7 se koristi [-5,100], za primeri 8-10 se koristi [-5,200]

        string edge1 = to_string(i) + "-" + to_string(to);
        string edge2 = to_string(to) + "-" + to_string(i);

        if (seenEdges.find(edge1) == seenEdges.end() && seenEdges.find(edge2) == seenEdges.end())
        {
            G[i].push_back({to, w});
            seenEdges.insert(edge1);
        }
    }

    for (int i=0; i<50; i++)
    {
        ed = 1+(rand()%49);
        for (int j=0; j<ed; j++)
        {
            int to = rand()%50;
            int w = (rand()%106)-5; //za test primeri 1-7 se koristi [-5,100], za primeri 8-10 se koristi [-5,200]


            while (to == i)
            {
                to = rand()%50;
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
    cout << 50 << " " << e << endl;
    for (int i=0; i<G.size(); i++)
    {
        for (int j=0; j<G[i].size(); j++)
        {
            cout << i << " " << G[i][j].first << " " << G[i][j].second << endl;
        }
    }
    return 0;
}