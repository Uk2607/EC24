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

int getMin(vector<vector<int>>&grid, int x, int y, int r, int c, int part) {
    int mn = INT_MAX;
    vector<pair<int,int>>dir = {{1,0}, {0, -1},{-1,0},{0, 1}};
    if(part == 3) {
        dir.push_back({1, 1});
        dir.push_back({1, -1});
        dir.push_back({-1, -1});
        dir.push_back({-1, 1});
    }
    for(pair<int,int>p: dir) {
        int dx = x+p.first, dy = y+p.second;
        if(dx>=0 && dx<r && dy>=0 && dy<c)
            mn = min(mn, grid[dx][dy]);
    }
    return mn;
}

void solve(vector<vector<int>>grid, int part) {
    int cnt = 0, r = grid.size(), c = grid[0].size();
    vector<vector<int>>t = grid;
    bool hasChange;
    do
    {
        hasChange = false;
        for(int i=0;i<r;i++) {
            for(int j=0;j<c;j++) {
                if(grid[i][j]==0) continue;
                int n_val = getMin(grid, i, j, r, c, part)+1;
                if(n_val != grid[i][j]) {
                    t[i][j] = n_val;
                    hasChange = true;
                }
            }
        }
        grid = t;
    } while (hasChange);
    for(vector<int>v: grid) for(int x: v) cnt += x;
    cout<<"PART "<<part<<" :: "<<cnt<<"\n";
}

int main() {
    int part = 3;
    // cout<<"Enter question part: ";
    // cin>>part;
    vector<vector<int>>ip;
    switch (part)
    {
    case 1:
        ip = read_data("input/03/part_01.in");
        solve(ip, 1);
        break;
    case 2:
        ip = read_data("input/03/part_02.in");
        solve(ip, 2);
        break;
    case 3:
        ip = read_data("input/03/part_03.in"); // 11725 X but 1 _ _ _ _
        solve(ip, 3);
        break;
    default:
        ip = read_data("input/03/part_01.in");
        solve(ip, 1);
        ip = read_data("input/03/part_02.in");
        solve(ip, 2);
        ip = read_data("input/03/part_03.in");
        solve(ip, 3);
        break;
    }
    return 0;
}