#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// DFS function
void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &order) {
    visited[node] = true;
    order.push_back(node);
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, order);
        }
    }
}

// BFS function
void bfs(int start, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &order) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Connectivity check using DFS
bool isConnectedDFS(int n, vector<vector<int>> &adj) {
    vector<bool> visited(n, false);
    vector<int> order;
    dfs(0, adj, visited, order);

    for (int i = 0; i < n; i++)
        if (!visited[i]) return false;
    return true;
}

// Connectivity check using BFS
bool isConnectedBFS(int n, vector<vector<int>> &adj) {
    vector<bool> visited(n, false);
    vector<int> order;
    bfs(0, adj, visited, order);

    for (int i = 0; i < n; i++)
        if (!visited[i]) return false;
    return true;
}

int main() {
    int n, m;
    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> m;

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // DFS Traversal
    vector<bool> visitedDFS(n, false);
    vector<int> dfsOrder;
    dfs(0, adj, visitedDFS, dfsOrder);
    cout << "DFS Traversal Order: ";
    for (int node : dfsOrder) cout << node << " ";
    cout << endl;

    // BFS Traversal
    vector<bool> visitedBFS(n, false);
    vector<int> bfsOrder;
    bfs(0, adj, visitedBFS, bfsOrder);
    cout << "BFS Traversal Order: ";
    for (int node : bfsOrder) cout << node << " ";
    cout << endl;

    // Connectivity check
    if (isConnectedDFS(n, adj))
        cout << "Network is Connected" << endl;
    else
        cout << "Network is Disconnected" << endl;

    return 0;
}
