#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

#define ll long long
#define ull unsigned long long

vector<int> read_data(string filePath) {

    ifstream file(filePath);
    vector<int> arr;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }
    while(getline(file, line)) {
        arr.push_back(stoi(line));
    }
    file.close();
    return arr;
}

int knapsack(vector<int>&options, int target) {
    int limit=target+1;
    vector<int>dp(limit, limit);
    dp[0] = 0;
    for(int i=0;i<=target;i++) {
        for(int j=0;j<options.size();j++) {
            if(options[j]<=i) {
                dp[i] = min(dp[i], dp[i-options[j]]+1);
            }
        }
    }
    return dp[target];
}

void part_1(vector<int>arr) {
    vector<int>validStamps = {1, 3, 5, 10};
    int res = 0;
    for(int x: arr)
        res+=knapsack(validStamps, x);
    cout<<"PART 1 :: "<<res<<"\n";
}

void part_2(vector<int>arr) {
    vector<int>validStamps = {1, 3, 5, 10, 15, 16, 20, 24, 25, 30};
    int res = 0;
    for(int x: arr)
        res+=knapsack(validStamps, x);
    cout<<"PART 2 :: "<<res<<"\n";
}

void part_3(vector<int>arr) {
    // TODO: fix
    vector<int>validStamps = {1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101};
    int res = 0, idx = 0;
    for(int T: arr) {
        cout<<idx++<<": "<<T<<" ";
        int lmn = INT_MAX, rmn = INT_MAX;
        for(int y=(T/2)-50;y<=T/2;y++) {
            int x = T-y;
            int l = knapsack(validStamps, y);
            int r = knapsack(validStamps, x);
            lmn = min(lmn, l);
            rmn = min(rmn, r);
        }
        cout<<lmn<<", "<<rmn<<"\n";
        res += (lmn+rmn);
        // res += knapsack(validStamps, T);
    }
    cout<<"PART 3 :: "<<res<<"\n"; // 1 _ _ _ _ _ != 148844
}
// x>y
// x+y=T;
// x-y<=100

// (1) --> x<=50+(T/2)
// (2) --> y>=(T/2)-50

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<int> ip;
    
    string folder_path = "09/";
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
