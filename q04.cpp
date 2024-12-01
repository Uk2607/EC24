#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

vector<int> read_data(string filePath) {

    ifstream file(filePath);

    vector<int>arr;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }

    string line;
    while (getline(file, line))
        arr.push_back(stoi(line));
    file.close();
    return arr;
}

void part1n2(vector<int>&arr, int part) {
    int mn = INT_MAX;
    for(int x: arr) mn = min(mn, x);
    int cnt = 0;
    for(int x: arr) cnt += (x-mn);
    cout<<"PART "<<part<<":: "<<cnt<<"\n";
}

void part3(vector<int>&arr) {
    long long int cnt, res = LLONG_MAX;
    for(int x: arr) {
        cnt = 0;
        for(int y: arr)
            cnt+=abs(y-x);
        res = min(res, cnt);
    }
    cout<<"PART 3:: "<<res<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<int>ip;

    string folder_path = "input/04/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"part_01.in");
        part1n2(ip, part);
        break;
    case 2:
        ip = read_data(folder_path+"part_02.in");
        part1n2(ip, part);
        break;
    case 3:
        ip = read_data(folder_path+"part_03.in");
        part3(ip);
        break;
    default:
        ip = read_data(folder_path+"part_01.in");
        part1n2(ip, 1);
        ip = read_data(folder_path+"part_02.in");
        part1n2(ip, 2);
        ip = read_data(folder_path+"part_03.in");
        part3(ip);
        break;
    }
    return 0;
}