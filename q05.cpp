#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

vector<vector<int>> read_data(string filePath) {

    ifstream file(filePath);

    vector<vector<int>>arr;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }

    string line;
    while (getline(file, line)) {
        vector<int>t;
        stringstream ss(line);
        string x;
        while(getline(ss, x, ' ')) t.push_back(stoi(x));
        arr.push_back(t);
    }
    file.close();
    return arr;
}

void part1(vector<vector<int>>&arr) {
    long long int res = LLONG_MAX;
    for(vector<int>v: arr) {
        for(int x: v) {
            cout<<x<<" ";
        }
        cout<<"\n";
    }
    cout<<"PART 1:: "<<res<<"\n";
}

void part2(vector<vector<int>>&arr) {
    long long int res = LLONG_MAX;
    cout<<"PART 2:: "<<res<<"\n";
}

void part3(vector<vector<int>>&arr) {
    long long int res = LLONG_MAX;
    cout<<"PART 3:: "<<res<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<vector<int>>ip;

    string folder_path = "input/05/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"part_01.in");
        part1(ip);
        break;
    case 2:
        ip = read_data(folder_path+"part_02.in");
        part2(ip);
        break;
    case 3:
        ip = read_data(folder_path+"part_03.in");
        part3(ip);
        break;
    default:
        ip = read_data(folder_path+"part_01.in");
        part1(ip);
        ip = read_data(folder_path+"part_02.in");
        part2(ip);
        ip = read_data(folder_path+"part_03.in");
        part3(ip);
        break;
    }
    return 0;
}