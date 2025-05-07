#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS from given source s
void bfs(vector<vector<int>>& adj, int s, vector<int> &ans) 
{
    // Create a queue for BFS
    queue<int> q;  
    
    // Initially mark all the vertices as not visited
    vector<bool> visited(adj.size(), false);

    // Mark the source node as visited and enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate over the queue
    while (!q.empty()) {
        // Dequeue a vertex from queue and print it
        int curr = q.front();
        q.pop();
        ans.push_back(curr);
        // cout << curr << " ";

        // Get all adjacent vertices of the dequeued vertex curr
        // If an adjacent has not been visited, mark it visited and enqueue it
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(vector<vector<int>>& adj, int u, int v) 
{
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected Graph
}

int main() 
{
    // Number of vertices and edges in the graph
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    // cout<<"Enter source node: "<<endl;
    // int source;
    // cin>>source;

    // cout<<"Enter destination node: "<<endl;
    // int destination;
    // cin>>destination;


    // Adjacency list representation of the graph
    vector<vector<int>> adj(V);

    // Input the edges
    cout << "Enter the edges (u v) for an undirected graph:\n";
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(adj, u, v);
    }
    vector<int> ans;

    // Source vertex for BFS
    int startVertex;
    cout << "Enter the starting vertex for BFS: ";
    cin >> startVertex;

    // Perform BFS traversal
    // cout << "BFS starting from " << startVertex << " : \n";
    bfs(adj, startVertex, ans);

    // Print the BFS traversal
    // bool flag = false;
    // for(int i=0;i<ans.size();i++){
    //     if(ans[i]==source || flag == true){
            
    //         cout<<ans[i]<<" ";
    //         if(ans[i]==destination){
    //             break;
    //         }
    //         flag = true;
    //     }
    // }

    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<" ";
    }

    return 0;
}

