#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

vector<vector<int>> read_data(string filePath) {

    ifstream file(filePath);

    vector<vector<int>>grid;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return grid;
    }

    string sentence;
    while (getline(file, sentence)) {
        vector<int>t;
        for(char c: sentence)
            (c=='.')?t.push_back(0):t.push_back(1);
        grid.push_back(t);
    }
    file.close();
    return grid;
}

void solve(vector<vector<int>>grid, int part) {
    
}

int main() {
    int part = 1;
    cout<<"Enter question part: ";
    cin>>part;
    vector<vector<int>>ip;

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