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
    int clapIdx = 0;
    string res = "";
    for(int r = 0;r<10;r++) {
        if(cols[clapIdx].empty()) continue;

        int clapper = cols[clapIdx].front();
        cols[clapIdx].erase(cols[clapIdx].begin()); // Shift operation

        int targetColumnIdx = (clapIdx + 1) % cols.size();
        std::vector<int>& targetColumn = cols[targetColumnIdx];

        int moves = (clapper % (targetColumn.size() * 2)) - 1;
        moves = abs(moves);
        if (moves > targetColumn.size()) {
            moves = (targetColumn.size() * 2) - moves;
        }

        // Insert clapper into the target column
        targetColumn.insert(targetColumn.begin() + moves, clapper);
        clapIdx = (clapIdx + 1) % cols.size();
    }

    // Prepare the answer
    for (const auto& col : cols) if (!col.empty()) res += to_string(col[0]);
    cout<<"PART 1:: "<<res<<"\n";
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

    string folder_path = "05/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part1(ip);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part2(ip);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part3(ip);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part1(ip);
        ip = read_data(folder_path+"02.in");
        part2(ip);
        ip = read_data(folder_path+"03.in");
        part3(ip);
        break;
    }
    return 0;
}