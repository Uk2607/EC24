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

vector<string> read_data(string filePath) {

    ifstream file(filePath);
    vector<string> arr;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }
    while(getline(file, line)) {
        arr.push_back(line);
    }
    file.close();
    return arr;
}

const int NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3;

const vector<vector<tuple<int, int, int>>> MOVES = {
    {{0, -1, WEST}, {-1, 0, NORTH}, {0, 1, EAST}},  // NORTH
    {{-1, 0, NORTH}, {0, 1, EAST}, {1, 0, SOUTH}}, // EAST
    {{0, 1, EAST}, {1, 0, SOUTH}, {0, -1, WEST}},  // SOUTH
    {{1, 0, SOUTH}, {0, -1, WEST}, {-1, 0, NORTH}}  // WEST
};

const unordered_map<char, int> ALTITUDE_CHANGE = {
    {'+', 1}, {'.', -1}, {'-', -2}, {'S', -1}, {'A', -1}, {'B', -1}, {'C', -1}
};

const string CHECK_POINTS = "ABC";

long long ff(int r, int c, int d, int p = 0) {
    return (static_cast<long long>(r) << 28) | (static_cast<long long>(c) << 16) | (static_cast<long long>(d) << 4) | p;
}

tuple<int, int, int, int> fr(long long x) {
    int r = x >> 28;
    int c = (x >> 16) & 0xFFF;
    int d = (x >> 4) & 0xF;
    int p = x & 0xF;
    return make_tuple(r, c, d, p);
}

void part_1(vector<string>grid) {
    int n = grid.size();
    int m = grid[0].size();
    int rs = 0, cs = 0;

    // Find the starting position 'S'
    for (int c = 0; c < m; ++c) {
        if (grid[0][c] == 'S') {
            cs = c;
            break;
        }
    }
    unordered_map<long long, int> s; // states
    for (int d = 0; d < 4; ++d) {
        s[ff(rs, cs, d)] = 1000;
    }

    for (int iteration = 0; iteration < 100; ++iteration) {
        unordered_map<long long, int> sn;
        for (const auto& [x, alt] : s) {
            int r, c, d, p;
            tie(r, c, d, p) = fr(x);
            for (const auto& [dr, dc, dn] : MOVES[d]) {
                int rn = r + dr;
                int cn = c + dc;
                if (rn >= 0 && rn < n && cn >= 0 && cn < m && (grid[rn][cn] == '.' || grid[rn][cn] == '-' || grid[rn][cn] == '+')) {
                    int altn = alt + ALTITUDE_CHANGE.at(grid[rn][cn]);
                    long long newState = ff(rn, cn, dn);
                    if (sn.find(newState) != sn.end()) {
                        sn[newState] = max(sn[newState], altn);
                    } else {
                        sn[newState] = altn;
                    }
                }
            }
        }
        s = sn;
    }

    int res = 0;
    for (const auto& [key, value] : s) {
        res = max(res, value);
    }

    cout<<"PART 1 :: "<<res<<"\n";
}

void part_2(vector<string>arr) {
    cout<<"PART 2 :: "<<arr.size()<<"\n";
}

void part_3(vector<string>arr) {
    cout<<"PART 3 :: "<<arr.size()<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    
    string folder_path = "20/";
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
