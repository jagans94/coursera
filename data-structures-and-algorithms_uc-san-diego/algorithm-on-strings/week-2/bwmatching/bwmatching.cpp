#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void PreprocessBWT(const string& bwt, map<char,int>& first_occ, map<char, vector<int> >& count_occ){

    /// Count Occurences
    for(auto &ch:bwt){
        int count = 0;
        if(count_occ.find(ch) == count_occ.end()){
            count_occ[ch].emplace_back(0);
            for(int i=0;i<bwt.size();++i){
                if(ch == bwt[i])
                    count++;
                count_occ[ch].emplace_back(count);
            }
        }
    }

    string first = bwt; sort(first.begin(),first.end());

    //// First Occurences
    int pos=0;
    while(pos != first.size()){
        char ch = first[pos];
        if(first_occ.find(ch) == first_occ.end())
            first_occ[ch] = pos;
        pos += count_occ.find(ch)->second.back();
    }
/*
    for(auto &occ:first_occ){
        cout << occ.first <<  "->" << occ.second << '\n';
    }

    cout << '\n';

    for(auto &occ_c:count_occ){
        cout << occ_c.first << " -> { ";
        for(auto &occ_c_sec:occ_c.second){
            cout << occ_c_sec << " ";
        }
        cout <<"}" << endl;
    }
    */
}

int CountOccurrences(const string& pattern, const string& bwt, map<char, int> first_occ, map<char, vector<int> > count_occ){
    int top = 0, bottom = bwt.size() - 1;
    int i = pattern.size() - 1;

    while(top <= bottom){
        if(i != -1) {
            char symbol = pattern[i--];
            if (bwt.find(symbol) != string::npos) {
                top = first_occ[symbol] + count_occ[symbol][top];
                bottom = first_occ[symbol] + count_occ[symbol][bottom + 1] - 1;
                //cout << top << " " << bottom << '\n';
            } else
                return 0;
        }
        else
            return bottom - top + 1;
    }
    return 0;
}

int main() {
    string bwt; cin >> bwt;

    map<char, int> first_occ; map<char, vector<int> > count_occ;
    PreprocessBWT(bwt, first_occ, count_occ);

    int pattern_count;
    cin >> pattern_count;
    for (int pi = 0; pi < pattern_count; ++pi) {
        string pattern;
        cin >> pattern;
        int occ_count = CountOccurrences(pattern, bwt,first_occ,count_occ);
        printf("%d ", occ_count);
    }
    printf("\n");
    return 0;
}

