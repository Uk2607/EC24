#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

#define ll long long
#define ull unsigned long long

string read_data(string filePath) {

    ifstream file(filePath);
    vector<string> arr;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return line;
    }
    getline(file, line);
    file.close();
    return line;
}

void part_1(int ip) {
    cout<<"PART 1 :: "<<ip<<"\n";
}

void part_2(int ip) {
    cout<<"PART 2 :: "<<ip<<"\n";
}

void part_3(int ip) {
    cout<<"PART 3 :: "<<ip<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    string ip, folder_path = "08/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(stoi(ip));
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_2(stoi(ip));
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(stoi(ip));
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1(stoi(ip));
        ip = read_data(folder_path+"02.in");
        part_2(stoi(ip));
        ip = read_data(folder_path+"03.in");
        part_3(stoi(ip));
        break;
    }
    return 0;
}
