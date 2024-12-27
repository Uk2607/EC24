#include<iostream>
#include<fstream>
#include<vector>
#include<string>
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
    file.close();
    return arr;
}

void part_1(vector<string>arr) {
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
    
    string folder_path = "10/";
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
