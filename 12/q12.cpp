#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<tuple>
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
    arr.pop_back();
    file.close();
    return arr;
}

vector<pair<int,int>> read_data3(string filePath) {

    ifstream file(filePath);
    vector<pair<int,int>> arr;

    string line;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return arr;
    }
    while(getline(file, line)) {
        stringstream ss(line);
        int x, y;
        ss>>x>>y;
        arr.push_back({x, y});
    }
    file.close();
    return arr;
}

void part_1n2(vector<string>arr) {
    int r = arr.size(), c = arr[0].length(), res = 0;
    vector<pair<pair<int,int>, int>>target;
    vector<pair<char, pair<int,int>>>players;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) {
            if(arr[i][j]=='T') target.push_back({{i, j}, 1});
            else if(arr[i][j]=='H') target.push_back({{i, j}, 2});
            else if(arr[i][j]!='.') players.push_back({arr[i][j], {i, j}});
        }
    for(auto [t, m]: target) {
        int dist = 0, idx = 0;
        for(auto [c, p]: players) {
            int diff  = (t.second-p.second) - (t.first-p.first);
            if(diff%3==0) {
                int x = (c -'A' + 1) * m * diff/3;
                res += x;
				break;
            }
        }
    }
    cout<<"PART 1 :: "<<res<<"\n";
}

tuple<int, int, int, int, int> calc_hit(pair<int,int>t, pair<int,int>p, int m) {
    auto [rt, ct] = t;
    auto [rs, cs] = p;
    int t_delay = 0;
    if ((ct - cs) & 1) {
        t_delay = 1;
        rt -= 1;
        ct -= 1;
    }

    int delta = ct - cs;
    int t_hit = delta / 2;
    int r_hit = rt - delta / 2;
    int c_hit = ct - delta / 2;
    int dr = r_hit - rs;
    int dc = c_hit - cs;

    if (r_hit < 0) {
        return make_tuple(-1, -1, -1, -1, -1); // None equivalent
    }
    if (dc < dr) {
        return make_tuple(-1, -1, -1, -1, -1); // None equivalent
    }

    // hit in phase 1
    int p_hit = dr;
    if (dr == dc) {
        return make_tuple(t_delay + t_hit, r_hit, c_hit, p_hit, m);
    }

    // hit in phase 2
    p_hit = dr;
    if (p_hit < dc && dc <= 2 * p_hit) {
        return make_tuple(t_delay + t_hit, r_hit, c_hit, p_hit, m);
    }

    // hit in phase 3
    p_hit = (dr + t_hit) / 3;
    int r = (dr + t_hit) % 3;
    if (r == 0) {
        return make_tuple(t_delay + t_hit, r_hit, c_hit, p_hit, m);
    }

    return make_tuple(-1, -1, -1, -1, -1); // None equivalent
}

void part_3(vector<pair<int,int>>targets) {
    int res = 0;
    vector<pair<pair<int,int>,int>>players = {{{0, 0}, 1}, {{0, 1}, 2}, {{0, 2}, 3}};
    for(pair<int,int>t: targets) {
        vector<tuple<int, int, int, int, int>> hits;
        for(auto [p, m]: players) {
            auto hit = calc_hit(t, p, m);
            if (get<0>(hit) != -1) { // Check if hit is not None
                hits.push_back(hit);
            }
        }
        if (!hits.empty()) {
            int highest = numeric_limits<int>::min();
            for (const auto& h : hits) {
                highest = max(highest, get<1>(h));
            }

            vector<tuple<int, int, int, int, int>> hits_highest;
            for (const auto& h : hits) {
                if (get<1>(h) == highest) {
                    hits_highest.push_back(h);
                }
            }

            int min_product = numeric_limits<int>::max();
            for (const auto& h : hits_highest) {
                min_product = min(min_product, get<3>(h) * get<4>(h));
            }
            res += min_product;
        }
    }
    cout<<"PART 3 :: "<<res<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    vector<pair<int,int>> ip3;
    
    string folder_path = "12/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1n2(ip);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_1n2(ip);
        break;
    case 3:
        ip3 = read_data3(folder_path+"03.in");
        part_3(ip3);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1n2(ip);
        ip = read_data(folder_path+"02.in");
        part_1n2(ip);
        ip3 = read_data3(folder_path+"03.in");
        part_3(ip3);
        break;
    }
    return 0;
}
