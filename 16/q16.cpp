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

pair<vector<int>, vector<vector<string>>> read_data(string filePath) {

    ifstream file(filePath);
    vector<int> lever;
    vector<vector<string>> wheel;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return {lever, wheel};
    }
    bool flag = false;
    while(getline(file, line)) {
        if(line.length() == 0) { flag = true; continue; }
        if(flag) {
            if(wheel.size() == 0)
                for(int i=0;i<line.length();i+=4) wheel.push_back({line.substr(i, 3)});
            else
                for(int i=0;i<line.length();i+=4) {
                    string s = line.substr(i, 3);
                    if(s!= "   ") wheel[i/4].push_back(s);
                }
        } else {
            stringstream ss(line);
            string token;
            while(getline(ss, token, ',')) {
                lever.push_back(stoi(token));
            }
        }
    }
    file.close();
    return {lever, wheel};
}

void print(vector<int>lever, vector<vector<string>>wheel) {
    cout<<"LEVER :: ";
    for(int i: lever) cout<<i<<" ";
    cout<<"\n";
    int idx = 1;
    cout<<"WHEEL :: \n";
    for(vector<string> v: wheel) {
        cout<<idx++<<": ";
        for(string s: v) cout<<s<<" ";
        cout<<"\n";
    }
}

void part_1(vector<int>lever, vector<vector<string>>wheel) {
    int t = 0;
    string res;
    vector<int>idx(lever.size(), 0);
    while(t<100) {
        for(int i=0;i<wheel.size();i++) idx[i] = (idx[i]+lever[i])%wheel[i].size();
        t++;

        res = "";
        for(int i=0;i<wheel.size();i++) res += (wheel[i][idx[i]]+" ");
    }
    cout<<"PART 1 :: "<<res<<"\n";
}

void part_2(vector<int>lever, vector<vector<string>>wheel) {
    long long pull_limit = 202420242024LL, coins = 0LL, t = 0LL;
    vector<int>idx(lever.size(), 0), pre;
    set<string>seen_idx_pattern;
    vector<string>order;
    while(t<pull_limit) {
        for(int i=0;i<wheel.size();i++) idx[i] = (idx[i]+lever[i])%wheel[i].size();

        map<char, int>f;
        string slot = "", idx_str = "";
        for(int i=0;i<wheel.size();i++) {
            char left_eye = wheel[i][idx[i]][0];
            char mouth = wheel[i][idx[i]][1];
            char right_eye = wheel[i][idx[i]][2];
            f[left_eye]++;
            f[right_eye]++;
            slot += wheel[i][idx[i]];
            idx_str += (to_string(idx[i])+' ');
        }

        if(seen_idx_pattern.find(idx_str) == seen_idx_pattern.end()) {
            seen_idx_pattern.insert(idx_str);
            order.push_back(slot);
        } else break;
        t++;

        for(auto it: f)
            coins += (it.second-2>0)?it.second-2:0;
        pre.push_back(coins);
    }
    coins *= (pull_limit/t);
    if(pull_limit%t) coins += pre[pull_limit%t-1];
    cout<<"PART 2 :: "<<coins<<"\n";
}

void part_3(vector<int>lever, vector<vector<string>>wheel) {
    cout<<"PART 3 :: "<<" "<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    pair<vector<int>, vector<vector<string>>> ip;
    
    string folder_path = "16/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(ip.first, ip.second);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_2(ip.first, ip.second);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(ip.first, ip.second);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1(ip.first, ip.second);
        ip = read_data(folder_path+"02.in");
        part_2(ip.first, ip.second);
        ip = read_data(folder_path+"03.in");
        part_3(ip.first, ip.second);
        break;
    }
    return 0;
}
