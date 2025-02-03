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
    int cLayers = sqrt(ip), res;
    if(cLayers*cLayers == ip){
        res = 0;
        return;
    }
    int missing_stones = pow(cLayers+1, 2)-ip;
    int pWidth = (cLayers+1)*2-1;
    res = missing_stones*pWidth;
    cout<<"PART 1 :: "<<res<<"\n";
}

void part_2(ll mul) {
    int mod = 1111, layer = 1, thickness = 1;
    ll stones = 1LL, totalStones = 20240000LL;
    while(stones<totalStones) {
        thickness = (thickness*mul)%mod;
        layer++;
        stones += (2*layer-1)*thickness;
    }
    ll missing_stones = stones-totalStones, pWidth = layer*2-1, res = missing_stones*pWidth;
    cout<<"PART 2 :: "<<res<<"\n";
}

void part_3(int mul) {
    int mod = 10, layer = 1, thickness = 1;
    ll stones = 1LL, totalStones = 202400000LL;
    while(stones<totalStones) {
        thickness = ((thickness*mul)%mod)+mod;
        layer++;
        stones += (2*layer-1)*thickness;
    }
    ll missing_stones = stones-totalStones, pWidth = layer*2-1, res = missing_stones*pWidth;
    cout<<"PART 3 :: "<<missing_stones<<"\n";
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
        part_2(stoll(ip));
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_3(stoi(ip));
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1(stoi(ip));
        ip = read_data(folder_path+"02.in");
        part_2(stoll(ip));
        ip = read_data(folder_path+"03.in");
        part_3(stoi(ip));
        break;
    }
    return 0;
}
