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

void solve(vector<int>arr, int part) {
    
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
        solve(ip, part);
        break;
    case 2:
        ip = read_data(folder_path+"part_02.in");
        solve(ip, part);
        break;
    case 3:
        ip = read_data(folder_path+"part_03.in");
        solve(ip, part);
        break;
    default:
        ip = read_data(folder_path+"part_01.in");
        solve(ip, 1);
        ip = read_data(folder_path+"part_02.in");
        solve(ip, 2);
        ip = read_data(folder_path+"part_03.in");
        solve(ip, 3);
        break;
    }
    return 0;
}