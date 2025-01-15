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

void part_1(string ins, vector<string>arr) {
    cout<<"PART 1 :: "<<arr.size()<<"\n";
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
