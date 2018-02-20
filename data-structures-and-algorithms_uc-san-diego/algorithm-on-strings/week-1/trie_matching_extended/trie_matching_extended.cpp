#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef vector<string> vs;
typedef vector<int> vi;
typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(const vs & patterns) {
    size_t size = 0;
    for(auto &pattern:patterns) size += pattern.size();

    trie t(size); int j = 1;

    for(auto & pattern:patterns){
        int current_node = 0;
        for(auto & ch:pattern){
            if(t[current_node].find(ch) == t[current_node].end())
                t[current_node].emplace(ch,j++);
            current_node = t[current_node][ch];
        }
    }
    return t;
}

vector <int> solve (const string &text, int n, const vs &patterns) {
    vector <int> result;
    trie t = build_trie(patterns);
    for(int i=0;i<text.size();++i){
        int current_node = 0, j = i;
        char symbol = text[i];
        while(true){
            if(t[current_node].find('$') != t[current_node].end()){
                result.push_back(i); break;
            }
            if(t[current_node].find(symbol) != t[current_node].end()){
                current_node = t[current_node][symbol];
                symbol = text[++j];
            } else break;
        }
    }
    return result;
}

int main () {
    string text ; cin >> text;
    size_t n; cin >> n;

    vs patterns (n);
    for (int i = 0; i < n; i++) {
        cin >> patterns[i];
        patterns[i].push_back('$');
    }

    vi ans;
    ans = solve (text, n, patterns);

    for (int i = 0; i < (int) ans.size (); i++) {
        cout << ans[i];
        if (i + 1 < (int) ans.size ()) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}

