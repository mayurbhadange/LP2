#include<bits/stdc++.h>

using namespace std;

vector<int> dijkstrasMST(int n, int m, int source, vector<vector<int>>& edges){

    unordered_map<int, list<pair<int, int>>> adj;
    for(int i = 0; i<m; i++){
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    vector<int> dist(n, INT_MAX);
    set<pair<int, int>> setOfPairs;

    dist[source] = 0;
    setOfPairs.insert({0, source});

    while(!setOfPairs.empty()){
        auto top = *(setOfPairs.begin());
        int topNode = top.second;
        int nodeDist = top.first;

        setOfPairs.erase(setOfPairs.begin());

        for(auto &neigh : adj[topNode]){
            if(dist[neigh.first] > neigh.second + nodeDist){
                
                auto it = setOfPairs.find({dist[neigh.first], neigh.first});
                if (it != setOfPairs.end()) {
                    setOfPairs.erase(it);
                }
                dist[neigh.first] = neigh.second+nodeDist;
                setOfPairs.insert({dist[neigh.first], neigh.first});
            }
        }
    }

    return dist;
}

int main() {
    int t; // Number of test cases
    cin >> t;

    while (t--) {
        int vertices, edges;
        cin >> vertices >> edges;

        vector<vector<int>> vec(edges, vector<int>(3));
        for (int i = 0; i < edges; i++) {
            cin >> vec[i][0] >> vec[i][1] >> vec[i][2];
        }

        int source = 0; // Assuming source is always node 0
        vector<int> distances = dijkstrasMST(vertices, edges, source, vec);

        // Output distances for the current test case
        for (int i = 0; i < distances.size(); i++) {
            cout << (distances[i] == INT_MAX ? -1 : distances[i]) << " ";
        }
        cout << endl;
    }

    return 0;
}