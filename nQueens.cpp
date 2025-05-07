#include<bits/stdc++.h>
using namespace std; 

void addSolution(vector<vector<int>>& board ,vector<vector<string>>& ans, int n){
    vector<string>  temp;
    string r = "";

    for(int  i = 0; i<n; i++){
        r = "";
        for(int j = 0; j<n; j++){
            if(board[i][j] == 1){
                r.push_back('1');
            }
            else{
                r.push_back('0');
            }
        }
        temp.push_back(r);
    }

    ans.push_back(temp);
}

bool isSafe(int row, int col, vector<vector<int>>& board, int n){
    int x = row;
    int y = col;

    while(x>=0 && y>=0){
        if(board[x][y] == 1){
            return false;
        }
        x--;
        y--;
    }

    x=row;
    y=col;

    while(x<n && y>=0){
        if(board[x][y] == 1){
            return false;
        }

        x++;
        y--;
    }

    x=row;
    y=col;

    while(y>=0){
        if(board[x][y] == 1){
            return false;
        }

        y--;
    }

    x=row;
    y=col;

    while(x>=0){
        if(board[x][y] == 1){
            return false;
        }
        x--;
    }

    return true;

}

void solve(int col,vector<vector<int>>& board ,vector<vector<string>>& ans, int n){
    if(col == n){
        addSolution(board, ans, n);
        return;
    }

    for(int row = 0; row<n; row++){
        if(isSafe(row, col, board, n)){
            board[row][col] = 1;
            solve(col+1, board, ans, n);
            board[row][col] = 0;
        }
    }
}

vector<vector<string>> nQueens(int N){
    vector<vector<string>> ans;
    vector<vector<int>> board(N, vector<int>(N,0));
    

    solve(0, board, ans, N);
    return ans;
}


int main(){
    int n;
    cout<<"Enter N: \n";
    cin>>n;

    vector<vector<string>> ans = nQueens(n);

    if(ans.size() == 0){
        cout<<"No arrangements possible for n = "<<n<<endl;
    }


    for(auto x:ans){
        for(auto y:x){
            cout<<y<<endl;
        }
        cout<<"---------------------------------------------------------------------------------\n";
    }
    
    return 0;
}