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

int get_min_path(vector<string>&arr, pair<int,int>&me, int H, int W) {
    vector<vector<bool>>vis(H, vector<bool>(W, false));
    queue<pair<int,int>>q;
    int len = 0;
    q.push(me);
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            auto p = q.front();
            q.pop();
            if(arr[p.first][p.second] == 'H') return 2*len;
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
    return len*2;
}

void part_1(vector<string>arr) {
    pair<int,int>me;
    int H = arr.size(), W = arr[0].length();
    for(int j=0;j<W;j++) if(arr[0][j] == '.') { me = {0, j}; break; }
    int min_path = get_min_path(arr, me, H, W);
    cout<<"PART 1 :: "<<min_path<<"\n"; // 196
}

void part_2(vector<string>arr) {
    cout<<"PART 2 :: "<<arr.size()<<"\n";
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
