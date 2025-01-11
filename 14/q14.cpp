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

struct Pos {
    int x, y, z;
    bool operator<(const Pos &p) const {
        if(x == p.x) {
            if(y == p.y) return z<p.z;
            return y<p.y;
        }
        return x<p.x;
    }
};

vector<vector<string>> read_data(string filePath) {

    ifstream file(filePath);
    vector<vector<string>> arr;

    string line, ins;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }
    while(getline(file, line)) {
        stringstream ss(line);
        vector<string>t;
        while(getline(ss, ins, ',')) t.push_back(ins);
        arr.push_back(t);
    }
    file.close();
    return arr;
}

void part_1(vector<string>arr) {
    int maxH = 0, h = 0;
    for(string s: arr) {
        if(s[0] == 'U') h += stoi(s.substr(1));
        else if(s[0] == 'D')h -= stoi(s.substr(1));
        maxH = max(maxH, h);
    }
    cout<<"PART 1 :: "<<maxH<<"\n"; // 150
}

void part_2(vector<vector<string>>arr) {
    set<Pos>st;
    for(vector<string> path: arr) {
        Pos p = {0, 0, 0};
        for(string ins: path) {
            char dir = ins[0];
            int steps = stoi(ins.substr(1));
            for(int t = 0; t<steps; t++) {
                if(dir == 'U') --p.y;
                else if(dir == 'D') ++p.y;
                else if(dir == 'L') --p.x;
                else if(dir == 'R') ++p.x;
                else if(dir == 'F') ++p.z;
                else  --p.z;
                st.insert(p);
            }
        }
    }
    int res = 0;
    cout<<st.size()<<"\n";
    cout<<"PART 2 :: "<<res<<"\n";
}

void part_3(vector<vector<string>>arr) {
    cout<<"PART 3 :: "<<arr.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<vector<string>> ip;
    
    string folder_path = "14/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(ip[0]);
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
        part_1(ip[0]);
        ip = read_data(folder_path+"02.in");
        part_2(ip);
        ip = read_data(folder_path+"03.in");
        part_3(ip);
        break;
    }
    return 0;
}
