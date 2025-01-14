#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<cassert>
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

bool isInside(pair<int,int>p, int H, int W) {
    return p.first>=0 && p.first<H && p.second>=0 && p.second<W;
}

int bfs(vector<string>arr, int H, int W, vector<pair<int,int>>src, set<pair<int,int>>&st) {
    vector<vector<bool>>vis(H, vector<bool>(W, false));
    queue<pair<int,int>>q;
    for(pair<int,int> s:src) {
        q.push(s);
        vis[s.first][s.second] = true;
    }
    int depth = 0;
    while(!q.empty()) {
        int n = q.size();
        while(n--) {
            pair<int,int>cur = q.front();
            q.pop();
            if(st.find(cur) != st.end()) st.erase(cur);
            for(pair<int,int> d:dir) {
                pair<int,int>newPos = {cur.first+d.first, cur.second+d.second};
                if(isInside(newPos, H, W) && arr[newPos.first][newPos.second]!='#' && !vis[newPos.first][newPos.second]) {
                    q.push(newPos);
                    vis[newPos.first][newPos.second] = true;
                }
            }
        }
        if(st.empty()) break;
        depth++;
    }
    return depth;
}

void part_1(vector<string>arr) {
    set<pair<int,int>>st;
    int H = arr.size(), W = arr[0].size();
    for(int i=0;i<H;i++) for(int j=0;j<W;j++) if(arr[i][j] == 'P') st.insert({i,j});
    int depth = bfs(arr, H, W, {{1, 0}}, st);
    cout<<"PART 1 :: "<<depth<<"\n";
}

void part_2(vector<string>arr) {
    set<pair<int,int>>st;
    int H = arr.size(), W = arr[0].size();
    for(int i=0;i<H;i++) for(int j=0;j<W;j++) if(arr[i][j] == 'P') st.insert({i,j});
    int depth = bfs(arr, H, W, {{1, 0}, {H-2, W-1}}, st);
    cout<<"PART 2 :: "<<depth<<"\n";
}

void part_3(vector<string>arr) {
    cout<<"PART 3 :: "<<arr.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    
    string folder_path = "18/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(ip);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_2(ip);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1(ip);
        ip = read_data(folder_path+"02.in");
        part_2(ip);
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    }
    return 0;
}
