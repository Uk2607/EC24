#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<assert.h>
using namespace std;

#define ll long long
#define ull unsigned long long

map<string, vector<string>> read_data(string filePath) {

    ifstream file(filePath);
    map<string, vector<string>> mp;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return mp;
    }
    while(getline(file, line)) {
        stringstream ss(line);
        string node, src;
        bool flag = false;
        while(getline(ss, node, ':')) {
            if(!flag) {
                src = node;
                mp[node] = {};
                flag = true;
            } else {
                stringstream arr(node);
                string v;
                while(getline(arr, v, ',')) mp[src].push_back(v);
            }
        }
    }
    file.close();
    return mp;
}

ll solve(map<string, vector<string>>&mp, string src, int target_day) {
    map<string, ll>dp;
    dp[src] = 1;
    int d = 1;
    while(d<=target_day) {
        map<string, ll>new_dp;
        for(auto [u, cnt]: dp) {
            for(string v: mp[u]) new_dp[v]+=cnt;
        }
        dp = new_dp;
        d++;
    }
    ll res = 0;
    for(auto [u, x]: dp) res+=x;
    return res;
}

void part_1n2(map<string, vector<string>>mp, string src, int target_day, int part=1) {
    ll res = solve(mp, src, target_day);
    if(part==1) assert(res==39LL);
    if(part==2) assert(res==312384LL);
    cout<<"PART "<<part<<" :: "<<res<<"\n";
}

void part_3(map<string, vector<string>>mp, int target_day) {
    ll mx = LLONG_MIN, mn = LLONG_MAX, idx=0;
    for(auto it: mp) {
        ll x = solve(mp, it.first, target_day);
        mx = max(mx, x);
        mn = min(mn, x);
    }
    assert(mx-mn == 1274520320218LL);
    cout<<"PART 3 :: "<<mx-mn<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    map<string, vector<string>> mp;
    
    string folder_path = "11/";
    switch (part)
    {
    case 1:
        mp = read_data(folder_path+"01.in");
        part_1n2(mp, "A", 4, 1);
        break;
    case 2:
        mp = read_data(folder_path+"02.in");
        part_1n2(mp, "Z", 10, 2);
        break;
    case 3:
        mp = read_data(folder_path+"03.in");
        part_3(mp, 20);
        break;
    default:
        mp = read_data(folder_path+"01.in");
        part_1n2(mp, "A", 4, 1);
        mp = read_data(folder_path+"02.in");
        part_1n2(mp, "Z", 10, 2);
        mp = read_data(folder_path+"03.in");
        part_3(mp, 20);
        break;
    }
    return 0;
}
