#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BWT(string text){
    string res;
    int n = text.size();
    text+=text;
    vector<string> cyclic_texts;
    for(int i=0;i<n;++i){
        cyclic_texts.push_back(text.substr(i,n));
    }

    sort(cyclic_texts.begin(),cyclic_texts.end());

    for(auto &text:cyclic_texts)
        res.push_back(text.back());

    return res;
}

int main() {
    string text;
    cin >> text;
    cout << BWT(text) << endl;
    return 0;
}
