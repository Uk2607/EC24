#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<set>
#include<assert.h>
using namespace std;

#define ll long long
#define ull unsigned long long

vector<vector<string>> read_data(string filePath) {
    ifstream file(filePath);
    vector<vector<string>> arr;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }
    vector<vector<string>>row_grid;
    bool flag = false;
    while(getline(file, line)) {
        if(line.length()==0) {
            for(vector<string>grid: row_grid)
                arr.push_back(grid);
            row_grid.clear();
            flag = false;
            continue;
        }
        stringstream ss(line);
        string row;
        int idx = 0;
        while(getline(ss, row, ' ')) {
            if(!flag) row_grid.push_back({row});
            else row_grid[idx].push_back(row);
            idx++;
        }
        flag = true;
    }
    for(vector<string>grid: row_grid)
        arr.push_back(grid);
    file.close();
    return arr;
}

void print(vector<string>&grid) {
    cout<<"\n";
    for(string row: grid) cout<<row<<"\n";
    cout<<"\n";
}

string solve(vector<string>arr) {
    string res = "";
    int n = arr.size();
    for(int i=2;i<n-2;i++) {
        for(int j=2;j<n-2;j++) {
            set<char>col, row;
            for(int k=0;k<n;k++) {
                if(arr[i][k]!='.') row.insert(arr[i][k]);
                if(arr[k][j]!='.') col.insert(arr[k][j]);
            }
            set<char>common;
            set_intersection(row.begin(), row.end(), col.begin(), col.end(), inserter(common, common.begin()));
            arr[i][j] = *next(common.begin(), 0);
            res+=arr[i][j];
        }
    }
    return res;
}

void part_1(vector<string>arr) {
    string res = solve(arr);
    assert(res=="PWMZTSHNDGCKQFLB");
    cout<<"PART 1 :: "<<res<<"\n";
}

// R:7 X C:15 = 105 Grids
void part_2(vector<vector<string>>arr) {
    ll res = 0;
    for(vector<string>grid: arr) {
        string s = solve(grid);
        ll x = 0;
        for(int i=0;i<s.length();i++) {
            x += ((s[i]-'A'+1)*(i+1));
        }
        res+=x;
    }
    assert(res==199666);
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
    
    string folder_path = "10/";
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
