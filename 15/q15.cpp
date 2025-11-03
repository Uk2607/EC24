#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<assert.h>
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

vector<pair<int,int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool isInside(pair<int,int>&p, int H, int W) {
    return p.first>=0 && p.first<H && p.second>=0 && p.second<W;
}

int get_min_path(vector<string>&arr, pair<int,int>&me, int H, int W) {
    vector<vector<bool>>vis(H, vector<bool>(W, false));
    queue<pair<int,int>>q;
    int len = 0;
    q.push(me);
    while(!q.empty()) {
        int sz = q.size();
        while(sz--) {
            auto p = q.front();
            q.pop();
            if(arr[p.first][p.second] != '.' && arr[p.first][p.second] != '#' && arr[p.first][p.second] != '~') return 2*len;
            for(pair<int,int> d: dirs) {
                pair<int,int>new_p = {p.first+d.first, p.second+d.second};
                if(isInside(new_p, H, W) && arr[new_p.first][new_p.second] != '#' && !vis[new_p.first][new_p.second]) {
                    vis[new_p.first][new_p.second] = true;
                    q.push(new_p);
                }
            }
        }
        len++;
    }
    return -1;
}

void part_1(vector<string>arr) {
    pair<int,int>me;
    int H = arr.size(), W = arr[0].length();
    for(int j=0;j<W;j++) if(arr[0][j] == '.') { me = {0, j}; break; }
    int min_path = get_min_path(arr, me, H, W);
    cout<<"PART 1 :: "<<min_path<<"\n"; // 196
}

void part_2n3(vector<string>grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    int start_row = 0, start_col = -1;
    for(int j=0;j<cols;j++) if(grid[0][j] == '.') { start_col = j; break; }
    map<char, int> fruit_to_bit; // Map to store fruit type -> bit index

    // Find the starting position '$' and identify all unique fruit types
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != '.' && grid[i][j] != '#' && grid[i][j] != '~') {
                // This is a fruit
                if (fruit_to_bit.find(grid[i][j]) == fruit_to_bit.end()) {
                    // New fruit type found, assign it the next available bit
                    fruit_to_bit[grid[i][j]] = fruit_to_bit.size();
                }
            }
        }
    }

    if (start_row == -1) {
        assert(false); // No starting point found
    }

    int num_fruit_types = fruit_to_bit.size();
    if (num_fruit_types == 0) {
        // No fruits to collect, just need to be at start.
        assert(false); 
    }

    int all_fruits_mask = (1 << num_fruit_types) - 1; // e.g., 3 fruits -> 111 (binary) -> 7
    int num_states = (1 << num_fruit_types); // e.g., 3 fruits -> 2^3 = 8 states

    // 3D distance array: dist[row][col][mask]
    // Stores the shortest distance to (row, col) having collected fruits in 'mask'
    // Initialize all distances to -1 (unvisited)
    vector<vector<vector<int>>> dist(rows, vector<vector<int>>(cols, vector<int>(num_states, -1)));

    // Queue for BFS: stores {row, col, mask}
    queue<tuple<int, int, int>> q;

    // Start BFS from the starting position with mask 0 (no fruits)
    q.push({start_row, start_col, 0});
    dist[start_row][start_col][0] = 0;

    // Direction vectors for 4-directional movement (up, down, left, right)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c, mask] = q.front();
        q.pop();

        int d = dist[r][c][mask];

        // Check if we are at the start with all fruits
        // Note: The BFS will continue to find shorter paths if they exist,
        // but we'll read the final answer from dist[start_row][start_col][all_fruits_mask]
        // after the BFS is complete.

        // Explore neighbors
        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // Check if the new position is valid (within bounds and not a wall)
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || grid[nr][nc] == '#' || grid[nr][nc] == '~') {
                continue;
            }

            // Calculate the new mask based on the cell we are moving to
            int new_mask = mask;
            char cell = grid[nr][nc];

            // Check if the cell is one of our identified fruits
            if (fruit_to_bit.count(cell)) {
                int fruit_bit = fruit_to_bit[cell];
                new_mask |= (1 << fruit_bit); // Set the corresponding bit
            }

            // If this state (nr, nc, new_mask) has not been visited,
            // update its distance and add it to the queue.
            if (dist[nr][nc][new_mask] == -1) {
                dist[nr][nc][new_mask] = d + 1;
                q.push({nr, nc, new_mask});
            }
        }
    }

    // The final answer is the shortest distance to the start cell
    // with all fruits collected
    cout<<"PART X :: "<<dist[start_row][start_col][all_fruits_mask]<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    vector<string> ip;
    
    string folder_path = "15/";
    switch (part)
    {
    case 1:
        ip = read_data(folder_path+"01.in");
        part_1(ip);
        break;
    case 2:
        ip = read_data(folder_path+"02.in");
        part_2n3(ip);
        break;
    case 3:
        ip = read_data(folder_path+"03.in");
        part_2n3(ip);
        break;
    default:
        ip = read_data(folder_path+"01.in");
        part_1(ip);
        ip = read_data(folder_path+"02.in");
        part_2n3(ip);
        ip = read_data(folder_path+"03.in");
        part_2n3(ip);
        break;
    }
    return 0;
}
