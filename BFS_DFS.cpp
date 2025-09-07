#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

void addEdge(vector<vector<int>>& adjList, int e1, int e2)
{
    adjList[e1-1].push_back(e2-1);
    adjList[e2-1].push_back(e1-1);
}

void addEdgeOW(vector<vector<int>>& adjList, int e1, int e2)
{
    adjList[e1].push_back(e2);
    adjList[e2].push_back(e1);
}

void BFS_adjList(vector<vector<int>>& adjList, vector<bool>& visited, int node)
{
    visited[node]=1;
    queue<int> q;
    q.push(node);
    while (!q.empty())
    {
        int t=q.front();
        q.pop();
        cout << t+1 << " ";
        for (auto& it : adjList[t])
        {
            if (!visited[it])
            {
                q.push(it);
                visited[it]=1;
            }
        }
    }
}

void DFS_adjList(vector<vector<int>>& adjList, vector<bool>& visited, int node)
{
    stack<int> s;
    s.push(node);
    while (!s.empty())
    {
        int t=s.top();
        s.pop();
        if (!visited[t])
        {
            visited[t] = 1;
            cout << t+1 << " ";
        }
        for (auto& it : adjList[t])
        {
            if (!visited[it])
            {
                s.push(it);
            }
        }
    }
}

int main()
{
    //KOD 1 : Adjacency List
    /*int n, e;
    cin >> n >> e;
    vector<vector<int>> adjList(n);
    for (int i=0; i<e; i++)
    {
        int e1, e2;
        cin >> e1 >> e2;
        addEdge(adjList, e1, e2);
    }
    vector<bool> visited(n, 0);
    BFS_adjList(adjList, visited, 0);
    cout << endl;
    vector<bool> visited2(n, 0);
    DFS_adjList(adjList, visited2, 0); */

    /*
    
    //KOD2: Matrica
    int n;
    cin >> n;
    vector<vector<bool>> matrix(n);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            bool val;
            cin >> val;
            matrix[i].push_back(val);
        }
    }
    vector<vector<int>> adjList(n);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            if (matrix[i][j]==1) addEdgeOW(adjList, i, j);
        }
    }
    vector<bool> visited(n, 0);
    BFS_adjList(adjList, visited, 0);
    cout << endl;
    vector<bool> visited2(n, 0);
    DFS_adjList(adjList, visited2, 0);
    */
    return 0;
}