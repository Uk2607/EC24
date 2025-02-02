#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<string>
using namespace std;

#define ll long long
#define ull unsigned long long

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
        vector<int>& targetColumn = cols[targetColumnIdx];

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
    int clapIdx = 0;
    map<string, int> count;
    ll r = 1, res = 0;
    while(true) {
        if(cols[clapIdx].empty()) continue;

        int clapper = cols[clapIdx].front();
        cols[clapIdx].erase(cols[clapIdx].begin()); // Shift operation

        int targetColumnIdx = (clapIdx + 1) % cols.size();
        vector<int>& targetColumn = cols[targetColumnIdx];

        int moves = (clapper % (targetColumn.size() * 2)) - 1;
        moves = abs(moves);
        if (moves > targetColumn.size()) {
            moves = (targetColumn.size() * 2) - moves;
        }

        // Insert clapper into the target column
        targetColumn.insert(targetColumn.begin() + moves, clapper);
        clapIdx = (clapIdx + 1) % cols.size();

        // Prepare the result
        string result;
        for (const auto& col : cols) {
            if (!col.empty()) {
                result += to_string(col[0]); // Get the first element of each column
            }
        }
        count[result]++;

        // Check if the result has appeared 2024 times
        if (count[result] == 2024) {
            res = r * stoll(result); // Calculate the answer
            break;
        }
        r++;
    }
    cout<<"PART 2:: "<<res<<"\n";
}

void part3(vector<vector<int>>cols) {
    int clapIdx = 0;
    string res;
    map<string, int> mp;
    vector<int> topArr(cols.size(), 0);
    while(true) {
        if(cols[clapIdx].empty()) continue;

        int clapper = cols[clapIdx].front();
        cols[clapIdx].erase(cols[clapIdx].begin()); // Shift operation

        int targetColumnIdx = (clapIdx + 1) % cols.size();
        vector<int>& targetColumn = cols[targetColumnIdx];

        int moves = (clapper % (targetColumn.size() * 2)) - 1;
        moves = abs(moves);
        if (moves > targetColumn.size()) {
            moves = (targetColumn.size() * 2) - moves;
        }

        // Insert clapper into the target column
        targetColumn.insert(targetColumn.begin() + moves, clapper);
        clapIdx = (clapIdx + 1) % cols.size();

        // Prepare the result
        string result;
        for (const auto& col : cols) {
            if (!col.empty())
                result += to_string(col[0]); // Get the first element of each column
            result += "|";
        }
        mp[result]++;

        if(mp[result]>2024) break;

        // Calculate the top values
        vector<int> top(cols.size(), 0); // Initialize top with 0s
        for (int i = 0; i < cols.size(); ++i)
            if (!cols[i].empty())
                top[i] = cols[i][0]; // Get the first element of each column

        // Compare top with topArr
        for (int i = 0; i < top.size(); ++i) {
            if (top[i] > topArr[i]) {
                topArr = top; // Update topArr if top is greater
                break; // No need to check further
            } else if (top[i] < topArr[i]) {
                break; // No need to check further
            }
        }
    }
    for(int x: topArr) res += to_string(x);
    cout<<"PART 3:: "<<res<<"\n";
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