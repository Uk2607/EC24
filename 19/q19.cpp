#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<cassert>
using namespace std;

#define ll long long
#define ull unsigned long long

pair<string, vector<string>> read_data(string filePath) {

    ifstream file(filePath);
    vector<string> arr;

    string ins, line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return {ins, arr};
    }
    bool flag = false;
    while(getline(file, line)) {
        if(line.length() == 0) {flag = true; continue;}
        if(flag) arr.push_back(line);
        else ins = line;
    }
    file.close();
    return {ins, arr};
}

void rotate(vector<string>&arr, pair<int, int>pivot, char dir, int H, int W) {
   int x = pivot.first, y = pivot.second;
    if(dir == 'R') { // Rotate the neighbours of pivot to right
        int temp = arr[x-1][y-1];
        arr[x-1][y-1] = arr[x][y-1];
        arr[x][y-1] = arr[x+1][y-1];
        arr[x+1][y-1] = arr[x+1][y];
        arr[x+1][y] = arr[x+1][y+1];
        arr[x+1][y+1] = arr[x][y+1];
        arr[x][y+1] = arr[x-1][y+1];
        arr[x-1][y+1] = arr[x-1][y];
        arr[x-1][y] = temp;
    } else { // Rotate the neighbours of pivot to left
        int temp = arr[x-1][y-1];
        arr[x-1][y-1] = arr[x-1][y];
        arr[x-1][y] = arr[x-1][y+1];
        arr[x-1][y+1] = arr[x][y+1];
        arr[x][y+1] = arr[x+1][y+1];
        arr[x+1][y+1] = arr[x+1][y];
        arr[x+1][y] = arr[x+1][y-1];
        arr[x+1][y-1] = arr[x][y-1];
        arr[x][y-1] = temp;
    }
}

void part_1(string ins, vector<string>arr) {
    int H = arr.size(), W = arr[0].size(), n = ins.length(), idx = 0;
    for(int i=1;i<H-1;i++) {
        for(int j=1;j<W-1;j++) {
            rotate(arr, {i, j}, ins[idx], H, W);
            idx = (idx+1)%n;
        }
    }
    string res = "";
    bool flag = false;
    for(int i=0;i<H;i++) {
        for(int j=0;j<W;j++) {
            if(arr[i][j] == '>') flag = true;
            else if(arr[i][j] == '<') flag = false;
            else if(flag) res += arr[i][j];
        }
    }
    cout<<"PART 1 :: "<<res<<"\n";
}

void part_2(string ins, vector<string>arr) {
    cout<<"PART 2 :: "<<arr.size()<<"\n";
}

void part_3(string ins, vector<string>arr) {
    cout<<"PART 3 :: "<<arr.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    pair<string, vector<string>> ip;
    
    string folder_path = "19/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(ip.first, ip.second);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_2(ip.first, ip.second);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(ip.first, ip.second);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1(ip.first, ip.second);
        ip = read_data(folder_path+"02.in");
        part_2(ip.first, ip.second);
        ip = read_data(folder_path+"03.in");
        part_3(ip.first, ip.second);
        break;
    }
    return 0;
}
