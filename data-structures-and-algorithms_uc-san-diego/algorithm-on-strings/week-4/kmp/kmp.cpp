#include <iostream>
#include <vector>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

vector<int> compute_prefix(const string &pattern){
    vector<int> prefix(pattern.size(),0);
    int border = 0;
    for(int i=1;i<pattern.size();++i){
        while(border > 0 && pattern[i] != pattern[border])
            border = prefix[border-1];

        if(pattern[i] == pattern[border])
            border++;
        else
            border = 0;
        prefix[i] = border;
    }
    return prefix;
}

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where
// the pattern starts in the text.
vector<int> find_pattern(const string& pattern, const string& text) {
    vector<int> result;
    string S = pattern + '$' + text;
    vector<int> prefix = compute_prefix(S);

    /*
    for(auto &each:prefix)
        cout << each << " ";
    cout << '\n';
     */

    for(int i = pattern.size() + 1; i < S.size(); ++i)
        if(prefix[i] == pattern.size())
            result.push_back(i-2*pattern.size());

    return result;
}

int main() {
    string pattern, text;
    cin >> pattern;
    cin >> text;
    vector<int> result = find_pattern(pattern, text);
    for (int i = 0; i < result.size(); ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}



