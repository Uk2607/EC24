#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

pair<vector<string>, vector<string> > read_data(string filePath) {

    ifstream file(filePath);

    vector<string>words;
    vector<string>inscription;

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return make_pair(words, inscription);
    }

    string sen, word;
    int line_cnt = 0;
    while (getline(file, sen)) {
        if(line_cnt == 0) {
            stringstream ss(sen.substr(6));
            while(getline(ss, word, ',')) words.push_back(word);
        }
        else if(line_cnt > 1)inscription.push_back(sen);
        ++line_cnt;
    }
    file.close();
    return make_pair(words, inscription);
}

void part_1(vector<string>&words, string&inscription) {
    int cnt = 0;
    for(string word: words)
        for(int i=0;i<=inscription.length()-word.length();i++)
            if(inscription.substr(i, word.length())==word) ++cnt;
    cout<<"PART 1 :: "<<cnt<<"\n";
}

void part_2(vector<string>&words, vector<string>&inscription) {
    int cnt = 0;
    for(string ins: inscription) {
        vector<bool>used(ins.length(), false);
        for(string word: words) {
            string rev = word;
            reverse(rev.begin(), rev.end());
            for(int i=0;i<=ins.length()-word.length();i++)
                if(ins.substr(i, word.length())==word || ins.substr(i, word.length())==rev) {
                    int k=0;
                    while(k<word.length()) {
                        used[i+k] = true;
                        ++k;
                    }
                }
        }
        for(bool b: used) if(b) ++cnt;
    }
    cout<<"PART 2 :: "<<cnt<<"\n";
}

void part_3(vector<string>&words, vector<string>&inscription) {
    int cnt = 0;
    vector<vector<bool> >vis;
    for(string ins: inscription) {
        vector<bool>used(ins.length(), false);
        for(string word: words) {
            string rev = word;
            reverse(rev.begin(), rev.end());
            string new_ins = ins + ins.substr(0, word.length()-1);
            for(int i=0;i<=new_ins.length()-word.length();i++) {
                if(new_ins.substr(i, word.length())==word || new_ins.substr(i, word.length())==rev) {
                    int k=0;
                    while(k<word.length()) {
                        used[(i+k)%ins.size()] = true;
                        ++k;
                    }
                }
            }
        }
        vis.push_back(used);
    }

    // Rotate
    vector<string>new_inscription(inscription[0].size());
    for(int i=0;i<inscription.size();i++)
        for(int j=0;j<inscription[i].size();j++)
            new_inscription[j]+=inscription[i][j];
    int r = vis.size(), c = vis[0].size();
    vector<vector<bool>>new_vis(c, vector<bool>(r, false));
    for(int i=0;i<r;i++) for(int j=0;j<c;j++) new_vis[j][i] = vis[i][j];

    int idx = 0;
    for(string ins: new_inscription) {
        vector<bool>used = new_vis[idx];
        for(string word: words) {
            string rev = word;
            if(ins.length()<word.length()) continue;
            reverse(rev.begin(), rev.end());
            for(int i=0;i<=ins.length()-word.length();i++) {
                cout<<word<<"::"<<ins.substr(i, word.length())<<"\n";
                if(ins.substr(i, word.length())==word || ins.substr(i, word.length())==rev) {
                    int k=0;
                    while(k<word.length()) {
                        used[(i+k)%ins.size()] = true;
                        ++k;
                    }
                }
            }
        }
        for(bool b: used) if(b) ++cnt;
        new_vis[idx++] = used;
    }

    for(int i=0;i<r;i++) for(int j=0;j<c;j++) vis[i][j] = new_vis[j][i];

    cout<<"PART 3 :: "<<cnt<<"\n";
}

int main() {
    int part;
    cout<<"Enter question part: ";
    cin>>part;
    pair<vector<string>, vector<string>>p;
    switch (part)
    {
    case 1:
        p = read_data("input/02/part_01.in");
        part_1(p.first, p.second[0]);
        break;
    case 2:
        p = read_data("input/02/part_02.in");
        part_2(p.first, p.second);
        break;
    case 3:
        p = read_data("input/02/part_03.in");
        part_3(p.first, p.second);
        break;
    default:
        p = read_data("input/02/part_01.in");
        part_1(p.first, p.second[0]);
        p = read_data("input/02/part_02.in");
        part_2(p.first, p.second);
        p = read_data("input/02/part_03.in");
        part_3(p.first, p.second);
        break;
    }
    return 0;
}