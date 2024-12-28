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

map<char, vector<char>> read_data(string filePath) {

    ifstream file(filePath);
    map<char, vector<char>> mp;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return mp;
    }
    while(getline(file, line)) {
        for(int i=2;i<line.length();i+=2) mp[line[0]].push_back(line[i]);
    }
    file.close();
    return mp;
}

void part_1(map<char, vector<char>>mp, int target_day) {
    queue<char>q;
    q.push('A');
    int d = 1;
    while(d<=target_day) {
        d++;
        int n = q.size();
        // cout<<d<<":: ";
        while(n--) {
            char u = q.front();
            q.pop();
            // cout<<u<<"->[ ";
            for(char v: mp[u]) {
                // cout<<v<<" ";
                q.push(v);
            }
            // cout<<"] ";
        }
        // cout<<"\n";
    }
    cout<<"PART 1 :: "<<q.size()<<"\n";
}

void part_2(map<char, vector<char>>mp) {
    cout<<"PART 2 :: "<<mp.size()<<"\n";
}

void part_3(map<char, vector<char>>mp) {
    cout<<"PART 3 :: "<<mp.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    map<char, vector<char>> ip;
    
    string folder_path = "11/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(ip, 4);
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
        part_1(ip, 4);
        ip = read_data(folder_path+"02.in");
        part_2(ip);
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    }
    return 0;
}
