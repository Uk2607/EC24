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
    int res = 0, t = 0;
    string sres = "";
    vector<int>idx(lever.size(), 0);
    while(t<100) {
        sres = "";
        for(int i=0;i<wheel.size();i++) idx[i] = (idx[i]+lever[i])%wheel[i].size();
        t++;

        vector<string> slot;
        for(int i=0;i<wheel.size();i++) slot.push_back(wheel[i][idx[i]]);

        // map<char, int>f;
        for(string s: slot) {
            // for(char c: s) f[c]++;
            sres += (s+" ");
        }
        // for(auto it: f)
        //     res += (it.second-2>0)?it.second-2:0;
    }
    cout<<"PART 1 :: "<<sres<<"\n";
}

void part_2(vector<int>lever, vector<vector<string>>wheel) {
    cout<<"PART 2 :: "<<" "<<"\n";
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
