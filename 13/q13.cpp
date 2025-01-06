#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
using namespace std;

#define ll long long
#define ull unsigned long long

vector<string> read_data(string filePath) {

    ifstream file(filePath);
    vector<string> arr;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }
    while(getline(file, line)) {
        arr.push_back(line);
    }
    file.close();
    return arr;
}

vector<pair<int,int>>dir = {{0,1}, {1,0}, {0,-1}, {-1,0}};

bool isInside(int x, int y, int H, int W) { return x>=0 && x<H && y>=0 && y<W; }

int cyclicDiff(int a, int b) {
    return min(abs(a-b), 10-abs(a-b));
}

// Dijkstra's algorithm
int min_path(vector<string>&grid, int H, int W, pair<int,int>me, pair<int,int>to) {
    vector<vector<bool>>vis(H, vector<bool>(W, false));
    vector<vector<int>>dist(H, vector<int>(W, INT_MAX));
    set<pair<int,pair<int, int>>>st;
    st.insert({0, me});
    dist[me.first][me.second] = 0;
    while(!st.empty()) {
        me = st.begin()->second;
        st.erase(st.begin());
        for(pair<int,int>d:dir) {
            int nx = me.first+d.first, ny = me.second+d.second;
            if(isInside(nx, ny, H, W) && grid[nx][ny]!='#' && !vis[nx][ny]) {
                int new_dist = dist[me.first][me.second] + cyclicDiff((grid[nx][ny]-'0'), (grid[me.first][me.second]-'0')) + 1;
                if(new_dist < dist[nx][ny]) {
                    if(dist[nx][ny] != INT_MAX) st.erase({dist[nx][ny], {nx, ny}});
                    dist[nx][ny] = new_dist;
                    st.insert({dist[nx][ny], {nx, ny}});
                }
            }
        }
    }
    return dist[to.first][to.second];
}

void part_1n2(vector<string>arr, int part) {
    int H = arr.size(), W = arr[0].length();
    pair<int,int>me, to;
    for(int i=0;i<H;i++)
        for(int j=0;j<W;j++)
            if(arr[i][j] == 'S') { me = {i, j}; arr[i][j] = '0'; }
            else if(arr[i][j] == 'E') { to = {i, j}; arr[i][j] = '0'; }
    
    int res = min_path(arr, H, W, me, to);
    if(part == 1) cout<<"PART 1 :: "<<res<<"\n"; // 143
    else cout<<"PART 2 :: "<<res<<"\n"; // 662
}

void part_3(vector<string>arr) {
    int H = arr.size(), W = arr[0].length();
    vector<pair<int,int>>src;
    pair<int,int>to;
    for(int i=0;i<H;i++)
        for(int j=0;j<W;j++)
            if(arr[i][j] == 'S') { src.push_back({i, j}); arr[i][j] = '0'; }
            else if(arr[i][j] == 'E') { to = {i, j}; arr[i][j] = '0'; }
    
    int res = INT_MAX, idx = 0;
    for(pair<int, int>me: src) {
        res = min(res, min_path(arr, H, W, me, to));
    }
    cout<<"PART 3 :: "<<res<<"\n"; // 529
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    
    string folder_path = "13/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1n2(ip, 1);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_1n2(ip, 2);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1n2(ip, 1);
        ip = read_data(folder_path+"02.in");
        part_1n2(ip, 2);
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    }
    return 0;
}
