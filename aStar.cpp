#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <set>
#include <iomanip> // For formatting

using namespace std;

// Define the structure for a node
struct Node
{
    int x, y;     // Coordinates
    double gCost; // Cost from start to current node
    double hCost; // Heuristic cost to the end node
    double fCost; // Total cost (gCost + hCost)
    Node *parent; // Parent node for path reconstruction

    Node(int x, int y, double gCost, double hCost, Node *parent = nullptr)
        : x(x), y(y), gCost(gCost), hCost(hCost), parent(parent)
    {
        fCost = gCost + hCost;
    }
};

// Heuristic function: Euclidean distance
double heuristic(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Check if a node is within the grid and not an obstacle
bool isValid(int x, int y, const vector<vector<int>> &grid)
{
    return x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 0;
}

// Find the shortest path using A*
vector<pair<int, int>> aStar(const vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end)
{
    int rows = grid.size();
    int cols = grid[0].size();

    // Directions: up, down, left, right, and diagonals
    vector<pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    // Custom comparator for the priority queue
    auto comparator = [](const Node &a, const Node &b) {
        return a.fCost > b.fCost; // Min-heap: lowest fCost has the highest priority
    };

    // Priority queue for open set
    priority_queue<Node, vector<Node>, decltype(comparator)> openSet(comparator);
    set<pair<int, int>> closedSet; // Closed set to keep track of visited nodes 

    // 2D array to track the best gCost for each node
    vector<vector<double>> gCostMap(rows, vector<double>(cols, INFINITY));

    // Add the starting node to the open set
    Node *startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, end.first, end.second));
    openSet.push(*startNode);
    gCostMap[start.first][start.second] = 0;

    // Print header for formatted output
    cout << left << setw(12) << "Node" 
         << setw(12) << "gCost" 
         << setw(12) << "hCost" 
         << setw(12) << "fCost" 
         << endl;
    cout << string(48, '-') << endl;

    while (!openSet.empty())
    {
        // Get the node with the lowest fCost
        Node current = openSet.top();
        openSet.pop();

        // Print details of the current node
        cout << "(" << current.x << ", " << current.y << ")"
             << setw(10) << " " << fixed << setprecision(2)
             << setw(12) << current.gCost
             << setw(12) << current.hCost
             << setw(12) << current.fCost << endl;

        // If we reached the destination, reconstruct the path
        if (current.x == end.first && current.y == end.second)
        {
            vector<pair<int, int>> path;
            Node *temp = &current;
            while (temp)
            {
                path.emplace_back(temp->x, temp->y);
                temp = temp->parent;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Add current node to the closed set
        closedSet.insert({current.x, current.y});

        // Explore neighbors
        for (const auto &dir : directions)
        {
            int dx = dir.first;
            int dy = dir.second;

            int nx = current.x + dx;
            int ny = current.y + dy;

            if (isValid(nx, ny, grid) && closedSet.find({nx, ny}) == closedSet.end())
            {
                double newGCost = current.gCost + heuristic(current.x, current.y, nx, ny);

                // Process the neighbor only if its gCost is better
                if (newGCost < gCostMap[nx][ny])
                {
                    double newHCost = heuristic(nx, ny, end.first, end.second);
                    gCostMap[nx][ny] = newGCost;

                    Node *neighbor = new Node(nx, ny, newGCost, newHCost, new Node(current.x, current.y, current.gCost, current.hCost, current.parent));
                    openSet.push(*neighbor);

                    // Print details of the neighbor being added to the open set
                    cout << "Adding (" << nx << ", " << ny << ")"
                         << setw(8) << " " << fixed << setprecision(2)
                         << setw(12) << newGCost
                         << setw(12) << newHCost
                         << setw(12) << (newGCost + newHCost) << endl;
                }
            }
        }
    }

    // If no path is found, return an empty path
    return {};
}

int main()
{
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}};

    pair<int, int> start = {0, 0};
    pair<int, int> end = {4, 4};

    vector<pair<int, int>> path = aStar(grid, start, end);

    if (!path.empty())
    {
        cout << "\nPath found: ";
        for (const auto &p : path)
        {
            int x = p.first;
            int y = p.second;
            cout << "(" << x << ", " << y << ") ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path found!" << endl;
    }

    return 0;
}

