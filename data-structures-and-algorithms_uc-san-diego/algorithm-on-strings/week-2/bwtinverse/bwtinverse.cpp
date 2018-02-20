#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct char_map{
    char ch = ' ';
    int index = -1;
    char_map(char c, int n):ch(c),index(n){}
};

bool sort_func(char_map &a, char_map&b){
    if(a.ch == b.ch)
        return a.index < b.index;
    return a.ch < b.ch;
}

vector<char_map> build_bwt_map(const string &bwt){
    vector<char_map> b;
    for(int i=0;i<bwt.size();++i){
        b.emplace_back(char_map(bwt[i],i));
    }
    sort(b.begin(),b.end(),sort_func);
    return b;
}

string InverseBWT(const string& bwt) {
    string text;
    vector<char_map> bwt_map = build_bwt_map(bwt);

    int i=0;
    do{
        i = bwt_map[i].index;
        text.push_back(bwt_map[i].ch);
    }while(bwt_map[i].ch != '$');

    return text;
}

int main() {
    string bwt;
    cin >> bwt;
    cout << InverseBWT(bwt) << endl;
    return 0;
}

