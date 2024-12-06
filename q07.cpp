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

    vector<vector<int>>cols(arr[0].size());
    for(int i=0;i<arr.size(); i++)
        for(int j=0;j<arr[0].size(); j++)
            cols[j].push_back(arr[i][j]);

    file.close();
    return cols;
}

void print(vector<vector<int>>&cols) {
    for(vector<int>v: cols) {
        for(int x: v) cout<<x<<" ";
        cout<<"\n";
    }
}

void part1(vector<vector<int>>cols) {
    string first_row = "TODO";
    print(cols);
    cout<<"PART 1:: "<<first_row<<"\n";
}

void part2(vector<vector<int>>cols) {
    string first_row = "TODO";
    cout<<"PART 2:: "<<first_row<<"\n";
}

void part3(vector<vector<int>>cols) {
    string first_row = "TODO";
    cout<<"PART 3:: "<<first_row<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<vector<int>>ip;

    string folder_path = "input/07/";
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
