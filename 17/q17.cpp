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

int findParent(int node, vector<int>parent) {
    if(parent[node] == -1) return node;
    return findParent(parent[node], parent);
}

void unionSets(vector<int>& parent, int u, int v) {
    int pu = findParent(u, parent), pv = findParent(v, parent);
    parent[pu] = pv;
}

vector<pair<int,pair<int,int>>> kruskal(vector<pair<int,pair<int,int>>> edges, vector<pair<int,int>> pos) {
    // Kruskal Algorithm
    int n = pos.size();
    sort(edges.begin(), edges.end());
    vector<int> parent(n, -1);
    vector<pair<int,pair<int,int>>> mst;

    for(auto edge: edges) {
        int u = edge.second.first, v = edge.second.second;
        int pu = findParent(u, parent), pv = findParent(v, parent);
        if(pu != pv) {
            mst.push_back(edge);
            unionSets(parent, pu, pv);
        }
    }

    return mst;
}

void part_1n2(vector<string>arr) {
    vector<pair<int,int>> pos;
    int H = arr.size(), W = arr[0].size();
    for(int i=0;i<H;i++) for(int j=0;j<W;j++) if(arr[i][j] == '*') pos.push_back({i,j});
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<pos.size();i++)
        for(int j=i+1;j<pos.size();j++) {
            int dist = abs(pos[i].first-pos[j].first) + abs(pos[i].second-pos[j].second);
            edges.push_back({dist, {i,j}});
        }
    // MST: Kruskal for sparse graph and Prims for dense graph
    vector<pair<int,pair<int,int>>> mst = kruskal(edges, pos);

    int res = pos.size();
    for(int i=0;i<mst.size();i++) res+=mst[i].first;

    cout<<"PART 1 :: "<<res<<"\n";
}

void part_3(vector<string>arr) {
    cout<<"PART 3 :: "<<arr.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    
    string folder_path = "17/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1n2(ip);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_1n2(ip);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1n2(ip);
        ip = read_data(folder_path+"02.in");
        part_1n2(ip);
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    }
    return 0;
}
