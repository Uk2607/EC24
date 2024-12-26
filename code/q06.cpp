#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
using namespace std;

map<string, vector<string>> read_data(string filePath) {

    ifstream file(filePath);

    map<string, vector<string>>mp;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return mp;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        bool isParent = true;
        string s, src, child;
        vector<string>children;
        while(getline(ss, s, ':')) {
            if(isParent) {
                src = s;
                isParent = false;
            } else {
                stringstream ch(s);
                while(getline(ch, child, ','))
                    children.push_back(child);
            }
        }
        mp[src] = children;
    }

    file.close();
    return mp;
}

void print(map<string, vector<string>>mp) {
    for(auto it: mp) {
        cout<<it.first<<":";
        for(string s: it.second) cout<<s<<" ";
        cout<<"\n";
    }
}

void dfs(string u, map<string, vector<string>>&mp, vector<string>&path, map<int, vector<vector<string>>>&path_dict) {
    if(u == "@") {
        path_dict[path.size()].push_back(path);
        return;
    }
    for(string v: mp[u]) {
        path.push_back(v);
        dfs(v, mp, path, path_dict);
        path.pop_back();
    }
}

void part1n2(map<string, vector<string>>&mp, int part) {
    string res = "";
    string root = "RR";
    vector<string>path = {root};
    map<int, vector<vector<string>>>path_dict;
    dfs(root, mp, path, path_dict);
    for(auto it: path_dict) {
        // cout<<it.first<<":"<<"\n";
        // for(vector<string>path: it.second) {
        //     for(string node: path) cout<<node<<"->";
        //     cout<<"\n";
        // }
        if(it.second.size()==1)
        for(string node: it.second[0]) {
            if(part==1) res += node;
            else if(part==2) res += node[0];
        }
    }
    cout<<"PART "<<part<<":: "<<res<<"\n";
}

void part3(map<string, vector<string>>mp) {
    string res = "TODO using bfs to limit the dfs";
    string node = "RR";
    queue<string>q;
    q.push(node);
    while(!q.empty()) {
        ;
    }
    cout<<"PART 3:: "<<res<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    map<string, vector<string>>mp;

    string folder_path = "input/06/";
    switch (part)
    {
    case 1:
        mp = read_data(folder_path+"part_01.in");
        part1n2(mp, part);
        break;
    case 2:
        mp = read_data(folder_path+"part_02.in");
        part1n2(mp, part);
        break;
    case 3:
        mp = read_data(folder_path+"part_03.in");
        part3(mp);
        break;
    default:
        mp = read_data(folder_path+"part_01.in");
        part1n2(mp, 1);
        mp = read_data(folder_path+"part_02.in");
        part1n2(mp, 2);
        mp = read_data(folder_path+"part_03.in");
        part3(mp);
        break;
    }
    return 0;
}
