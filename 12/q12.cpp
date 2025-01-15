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
    arr.pop_back();
    file.close();
    return arr;
}

void part_1(vector<string>arr) {
    int r = arr.size(), c = arr[0].length(), res = 0;
    vector<pair<int,int>>target;
    vector<pair<char, pair<int,int>>>players;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) {
            if(arr[i][j]=='T') target.push_back({i, j}); 
            else if(arr[i][j]!='.') players.push_back({arr[i][j], {i, j}});
        }
    for(pair<int,int>t: target) {
        int dist = 0, idx = 0;
        for(auto [c, p]: players) {
            int diff  = (t.second-p.second) - (t.first-p.first);
            if(diff%3==0) {
                int x = (c -'A' + 1) * ((t.second - p.second) - (t.first - p.first))/3;
                cout<<c<<": "<<x<<"\n";
                res += x;
				break;
            }
        }
    }
    cout<<"PART 1 :: "<<res<<"\n";
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
    
    string folder_path = "12/";
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
