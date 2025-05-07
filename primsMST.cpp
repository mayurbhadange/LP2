#include<bits/stdc++.h>

using namespace std;

vector<pair<pair<int, int>, int>> calcPrimsMst(int n, int m, vector<pair<pair<int, int>, int>>& g){
    unordered_map<int, list<pair<int, int>>> adj;

    for(int i = 0; i<m; i++){
        int u = g[i].first.first;
        int v = g[i].first.second;
        int w = g[i].second;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<int> keys(n+1, INT_MAX);
    vector<bool> mst(n+1, 0);
    vector<int> parent(n+1, -1);

    keys[1] = 0;
    // mst[1] = 1;


    for(int  i = 1; i<=n; i++){
        int u = -1;
        int mini = INT_MAX;

        for(int v = 1; v<=n; v++){
            if(mst[v] == 0 && keys[v] < mini){
                u = v;
                mini = keys[v];
            }
        }

        mst[u] = 1;

        for(auto &neigh : adj[u]){
            if(mst[neigh.first] == 0 && keys[neigh.first]>neigh.second){
                keys[neigh.first] = neigh.second;
                parent[neigh.first] = u;
            }
        }
    }

    vector<pair<pair<int, int>, int>> result;

    for(int i = 2; i<=n; i++){
        int v = parent[i];
        int u = i;
        int w = keys[u];
        result.push_back({{u,v}, w});
    }

    return result;
}

int main() {
    int n, m;
    cin >> n >> m;  // Input number of nodes and edges

    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;  // Input each edge with weight
        edges.push_back({{u, v}, w});
    }

    vector<pair<pair<int, int>, int>> mst = calcPrimsMst(n, m, edges);

    cout << "Minimum Spanning Tree Edges:\n";
    for (auto &edge : mst) {
        cout << edge.first.first << " - " << edge.first.second << " : " << edge.second << "\n";
    }

    return 0;
}