#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<assert.h>
using namespace std;

map<char, vector<char>> read_data(string filePath) {

    ifstream file(filePath);

    map<char, vector<char>>mp;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return mp;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string s;
        char src;
        bool isParent = true;
        vector<char>operation;
        while(getline(ss, s, ':')) {
            if(isParent) {
                src = s[0];
                isParent = false;
            } else {
                string op;
                stringstream ops(s);
                while(getline(ops, op, ','))
                    operation.push_back(op[0]);
            }
        }
        mp[src] = operation;
    }
    file.close();
    return mp;
}

void print(map<char, vector<char>>mp) {
    for(auto [src, ops]: mp) {
        cout<<src<<":";
        for(char c:ops) cout<<c<<" ";
        cout<<"\n";
    }
}

bool compare(const pair<char, int>& a, const pair<char, int>& b) {
    if(a.second == b.second) return a.first<b.first;
    return a.second > b.second; // Sort in descending order
}

string get_standings(map<char, pair<int, int>>&score) {
    string res = "";
    vector<pair<char, int>>standing;
    for(auto it: score) standing.push_back({it.first, it.second.second});
    sort(standing.begin(), standing.end(), compare);
    for(pair<char, int>p: standing) res += p.first;
    return res;
}

void part1(map<char, vector<char>>mp) {
    int t = 0;
    map<char, pair<int, int>>score;
    for(auto it: mp) score[it.first] = {10, 0};
    while(t<10) {
        for(auto it: mp) {
            char src = it.first;
            char op = it.second[t%it.second.size()];
            if(op == '+') {
                score[src].first += 1;
            } else if(op == '-') {
                if(score[src].first>0) score[src].first-=1;
            }
            score[src].second += score[src].first;
        }
        ++t;
    }
    string res = get_standings(score);
    cout<<"PART 1:: "<<res<<"\n";
    assert(res=="KBAICEFJD");
}

void part2(map<char, vector<char>>mp) {
    const string RACETRACK = "-=++=-==++=++=-=+=-=+=+=--=-=++=-==++=-+=-=+=-=+=+=++=-+==++=++=-=-=---=++==--+++==++=+=--==++==+++=++=+++=--=+=-=+=-+=-+=-+-=+=-=+=-+++=+==++++==---=+=+=-=";
    map<char, pair<int, int>>score;
    for(auto it: mp) score[it.first] = {10, 0};
    int loop = 0, idx = 0;
    while(loop<10) {
        for(int t=0;t<RACETRACK.length();t++) {
            for(auto it: mp) {
                char src = it.first;
                char track_op = RACETRACK[t], op = track_op;
                if(track_op == '=') op = it.second[idx%it.second.size()];
                if(op == '+') {
                    score[src].first += 1;
                } else if(op == '-') {
                    if(score[src].first>0) score[src].first-=1;
                }
                score[src].second += score[src].first;
            }
            idx++;
        }
        loop++;
        cout<<loop<<":\n";
        for(auto it: score) cout<<it.first<<": "<<it.second.second<<"\n";
    }
    string res = get_standings(score);
    cout<<"PART 2:: "<<res<<"\n";
    assert(res=="FKBDECIHJ");
}

void part3(map<char, vector<char>>mp) {
    string first_row = "TODO";
    cout<<"PART 3:: "<<first_row<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    map<char, vector<char>>ip;

    string folder_path = "07/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part1(ip);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part2(ip);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part3(ip);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part1(ip);
        ip = read_data(folder_path+"02.in");
        part2(ip);
        ip = read_data(folder_path+"03.in");
        part3(ip);
        break;
    }
    return 0;
}
