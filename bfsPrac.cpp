#include<bits/stdc++.h>

using namespace std;

void bfs(vector<vector<int>> &adj, int start, vector<int>&ans){
    queue<int> q;

    int v = adj.size();
    vector<bool> visited(v,0);
    
    visited[start] = 1;
    q.push(start);

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        ans.push_back(curr);

        for(int x : adj[curr]){
            if(visited[x] != 1){
                q.push(x);
                visited[x] = 1;
            }
        }
    }
    
}

void dfsRecur(vector<vector<int>>&adj, vector<int>& res, vector<int>& visited, int s){
    visited[s] = 1;
    res.push_back(s);

    for(int x : adj[s]){
        if(visited[x] == false){
            dfsRecur(adj, res, visited, x);
        }
    }
    
}

vector<int> dfs(vector<vector<int>>&adj ){
    vector<int> res;
    vector<int> visited(adj.size(), 0);
    dfsRecur(adj, res, visited, 0);
    return res;
}

void addEdge(int u, int v, vector<vector<int>>& adj){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int main(){

    int V, E;
    cout<<"Enter no. of vertices: "<<endl;
    cin>>V;
    cout<<"Enter no. of edges: "<<endl;
    cin>>E;

    vector<vector<int>> adj(V);

    for(int i = 0; i<E; ++i){
        int u,v;
        cin>>u>>v;

        addEdge(u,v,adj);
    }

    cout<<"BFS: "<<endl;
    vector<int> ans;
    bfs(adj, 0, ans);
    for(int i = 0; i<ans.size(); i++){
        cout<<ans[i]<<" ";
    }

    cout<<endl<<"DFS: "<<endl;
    vector<int> res = dfs(adj);
    for(int i = 0; i<res.size(); i++){
        cout<<res[i]<<" ";
    }


    return 0;
}