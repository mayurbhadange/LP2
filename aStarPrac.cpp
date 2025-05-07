#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
#include<set>

using namespace std;

struct Node
{
    /* data */
    int x;
    int y;
    double gCost;
    double hCost;
    double fCost;
    Node* parent;

    Node(int x, int y, double gCost, double hCost, Node* parent = nullptr)
        :x(x), y(y), gCost(gCost), hCost(hCost), parent(parent){
            fCost = gCost+hCost;
        }

};

bool isValid(int x, int y, vector<vector<int>> &grid){
    return (x>=0 && y>=0 && x<grid.size() && y<grid[0].size() && grid[x][y] == 0);
}

double heuristic(int x1, int y1, int x2, int y2){
    return (sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)));
}

vector<pair<int,int>> aStar(vector<vector<int>> &grid, pair<int, int> start, pair<int, int> end){


    int row = grid.size();
    int col = grid[0].size();

    vector<pair<int,int>> directions = {
        {-1,0}, {1,0}, {0,-1}, {0, 1}, {-1,-1}, {1, 1}, {-1,1}, {1, -1}
    };

    vector<vector<double>> gCostMap(row, vector<double>(col, INFINITY));

    auto comparator = [](const Node &a, const Node &b){
        return a.fCost > b.fCost;
    };

    priority_queue<Node, vector<Node>, decltype(comparator)> openset(comparator);

    set<pair<int,int>> closedset;

    Node *startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, end.first, end.second));
    openset.push(*startNode);
    gCostMap[start.first][start.second] = 0;   

    while(!openset.empty()){
        Node curr = openset.top();
        openset.pop();

        

        if(curr.x == end.first && curr.y == end.second){
            vector<pair<int,int>> path;
            Node *temp = &curr; 
            while(temp){
                path.emplace_back(temp->x, temp->y); 
                temp = temp->parent;   
            }
            reverse(path.begin(), path.end());
            return path;
        }

        closedset.insert({curr.x, curr.y});

        for(const auto &dir : directions){
            int dx = dir.first;
            int dy = dir.second;

            int nx = curr.x + dx;
            int ny = curr.y + dy;

            if(isValid(nx, ny, grid) && closedset.find({nx,ny}) == closedset.end()){
                double newgCost = curr.gCost + heuristic(curr.x, curr.y, nx, ny);
                if(newgCost < gCostMap[nx][ny]){
                    double newhCost = heuristic(nx, ny, end.first, end.second);
                    gCostMap[nx][ny] = newgCost;
                    
                    Node *neighbour = new Node(nx, ny, newgCost, newhCost, new Node(curr.x, curr.y, curr.gCost, curr.hCost, curr.parent));
                    openset.push(*neighbour);
                }
            }
        }



    }

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


