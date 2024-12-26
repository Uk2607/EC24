#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

string read_data(string filePath) {

    ifstream file(filePath);
    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return "";
    }

    getline(file, line);
    file.close();
    return line;
}

void part_1(vector<int>&power, string str) {
    int cost = 0;
    for(char c: str) cost+=power[c-'A'];
    cout<<"PART 1 :: "<<cost<<"\n";
}

void part_2(vector<int>&power,  string str) {
    int cost = 0, n = str.length();
    for(int i=0;i<n;i+=2) {
        cost += (power[str[i]-'A']+power[str[i+1]-'A']);
        if(str[i]!='x' && str[i+1]!='x') cost += 2;
    }
    cout<<"PART 2 :: "<<cost<<"\n";
}

void part_3(vector<int>&power,  string str) {
    int cost = 0, n = str.length();
    for(int i=0;i<n;i+=3) {
        cost += (power[str[i]-'A']+power[str[i+1]-'A']+power[str[i+2]-'A']);
        int cnt_x = (str[i] == 'x' ? 1:0) + (str[i+1] == 'x' ? 1:0) + (str[i+2] == 'x' ? 1:0);
        if(cnt_x == 0) cost+=6; // Triplets
        else if(cnt_x == 1) cost+=2; // Pair
    }
    cout<<"PART 3 :: "<<cost<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<int>ememyPower(26, 0);
    ememyPower[1] = 1; // B
    ememyPower[2] = 3; // C
    ememyPower[3] = 5; // D
    string input;
    
    string folder_path = "01/";
    switch (part)
    {
    case 1:
        input = read_data(folder_path+"01.in");
        part_1(ememyPower, input);
        break;
    case 2:
        input = read_data(folder_path+"02.in");
        part_2(ememyPower, input);
        break;
    case 3:
        input = read_data(folder_path+"03.in");
        part_3(ememyPower, input);
        break;
    default:
        input = read_data(folder_path+"01.in");
        part_1(ememyPower, input);
        input = read_data(folder_path+"02.in");
        part_2(ememyPower, input);
        input = read_data(folder_path+"03.in");
        part_3(ememyPower, input);
        break;
    }
    return 0;
}