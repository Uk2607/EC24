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

vector<pair<int,int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool isInside(pair<int,int>&p, int H, int W) {
    return p.first>=0 && p.first<H && p.second>=0 && p.second<W;
}

int get_min_path(vector<string>&arr, pair<int,int>&me, int H, int W, char &c) {
    vector<vector<bool>>vis(H, vector<bool>(W, false));
    queue<pair<int,int>>q;
    int len = 0;
    q.push(me);
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            auto p = q.front();
            q.pop();
            if(arr[p.first][p.second] != '.' && arr[p.first][p.second] != '#' && arr[p.first][p.second] != '~') {
                me = p;
                c = arr[p.first][p.second];
                return len;
            }
            for(pair<int,int> d: dirs) {
                pair<int,int>new_p = {p.first+d.first, p.second+d.second};
                if(isInside(new_p, H, W) && arr[new_p.first][new_p.second] != '#' && !vis[new_p.first][new_p.second]) {
                    vis[new_p.first][new_p.second] = true;
                    q.push(new_p);
                }
            }
        }
        len++;
    }
    return -1;
}

void part_1n2(vector<string>arr, int part) {
    pair<int,int>me, pos;
    int H = arr.size(), W = arr[0].length();
    for(int j=0;j<W;j++) if(arr[0][j] == '.') { me = {0, j}; arr[0][j] = '.'; break; }
    map<char, vector<pair<int,int>>>targets;
    for(int i=1;i<H;i++) {
        for(int j=0;j<W;j++) {
            if(arr[i][j] != '.' && arr[i][j] != '#' && arr[i][j] != '~')
                targets[arr[i][j]].push_back({i, j});
        }
    }
    int min_path = 0;
    pos = me;
    char t;
    while(!targets.empty()) {
        min_path += get_min_path(arr, pos, H, W, t);
        for(pair<int,int> p: targets[t]) {
            arr[p.first][p.second] = '.';
        }
        targets.erase(t);
    }
    arr[me.first][me.second] = '@';
    min_path += get_min_path(arr, pos, H, W, t);

    if(part == 1) cout<<"PART 1 :: "<<min_path<<"\n"; // 196
    else cout<<"PART 2 :: "<<min_path<<"\n"; // 568
}

void part_3(vector<string>arr) {
    cout<<"PART 3 :: "<<arr.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    
    string folder_path = "15/";
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
