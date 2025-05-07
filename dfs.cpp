#include <bits/stdc++.h>
using namespace std;

// Recursive function for DFS traversal
void DFSRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &ans) {
    visited[s] = true;

    // Store the current vertex in the ans vector
    ans.push_back(s);

    // Recursively visit all adjacent vertices that are not visited yet
    for (int i : adj[s]) {
        if (!visited[i]) {
            DFSRec(adj, visited, i, ans);
        }
    }
}

// Main DFS function that initializes the visited array
// and calls DFSRec
void DFS(vector<vector<int>> &adj, int s, vector<int> &ans) {
    vector<bool> visited(adj.size(), false);
    DFSRec(adj, visited, s, ans);
}

// To add an edge in an undirected graph
void addEdge(vector<vector<int>> &adj, int s, int t) {
    adj[s].push_back(t);
    adj[t].push_back(s);
}

int main() {
    int V, E;

    // Input number of vertices and edges
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    cout<<"Enter source node: "<<endl;
    int source;
    cin>>source;

    cout<<"Enter destination node: "<<endl;
    int destination;
    cin>>destination;


    vector<vector<int>> adj(V);

    // Input edges
    cout << "Enter the edges (u v) for an undirected graph:\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(adj, u, v);
    }

    // Input the starting vertex for DFS
    // int s;
    // cout << "Enter the starting vertex for DFS: ";
    // cin >> s;

    // Vector to store the DFS traversal
    vector<int> ans;

    // Perform DFS
    DFS(adj, 0, ans);

    // Output the DFS traversal stored in ans
    cout << "DFS traversal from source to destination: ";
    bool flag = false;
    for (int node : ans) {
        if(node==source || flag == true){
            cout << node << " ";
            if(node==destination){
                break;
            }
            flag = true;
        }
    }
    cout << endl;

    return 0;
}
