#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using std::map;
using std::vector;
using std::string;

using namespace std;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
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

int main() {
    size_t n;
    std::cin >> n;
    vector<string> patterns;
    for (size_t i = 0; i < n; i++) {
        string s;
        std::cin >> s;
        patterns.push_back(s);
    }

    trie t = build_trie(patterns);

    for (size_t i = 0; i < t.size(); ++i) {
        for (const auto & j : t[i]) {
            std::cout << i << "->" << j.second << ":" << j.first << "\n";
        }
    }

    return 0;
}
