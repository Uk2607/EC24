#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

vector<vector<int>> read_data(string filePath) {

    ifstream file(filePath);

    vector<vector<int>>grid;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return grid;
    }

    string sentence;
    while (getline(file, sentence)) {
        vector<int>t;
        for(char c: sentence)
            (c=='.')?t.push_back(0):t.push_back(1);
        grid.push_back(t);
    }
    file.close();
    return grid;
}

int getMin(vector<vector<int>>&grid, int x, int y, int r, int c) {
    int mn = INT_MAX;
    vector<int>d = {1,0,-1,0,1};
    for(int i=0;i<4;i++)// {1,0}, {0,-1}, {-1,0}, {0,1}
        if(x+i>=0 && x+i<r && y+i+1>=0 && y+i+1<c)
            mn = min(mn, grid[x+i][y+i+1]);
    return mn;
}

int part_1(vector<vector<int>>grid) {
    int cnt = 0, r = grid.size(), c = grid[0].size();
    vector<vector<int>>t = grid;
    bool hasChange;
    do
    {
        hasChange = false;
        for(int i=0;i<r;i++) {
            for(int j=0;j<c;j++) {
                if(grid[i][j]==0) continue;
                int n_val = getMin(grid, i, j, r, c)+1;
                if(n_val != grid[i][j]) {
                    grid[i][j] = n_val;
                    hasChange = true;
                }
            }
        }
        grid = t;
    } while (hasChange);
    
    cout<<"\n";
    for(vector<int>v: grid) {
        for(int x: v) {
            cout<<x<<" ";
            cnt+=x;
        }
        cout<<"\n";
    }
    return cnt;
}

int main() {

    vector<vector<int>>ip = read_data("ex");
    cout<<"PART 1 :: "<<part_1(ip)<<"\n";
    return 0;
}