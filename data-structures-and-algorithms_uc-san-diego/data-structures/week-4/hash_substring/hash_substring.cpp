#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

const ll p = 1000000007, x = 263;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    cin >> data.pattern >> data.text;
    return data;
}

/*
Data read_input_from_file(){
    ifstream input("06");
    Data data;
    input >> data.pattern >> data.text;
    return data;
}
 */

void print_occurrences(const vi & output) {
    for (int i = 0; i < output.size(); ++i)
        cout << output[i] << " ";
    cout << "\n";
}

ll polyHash(string s){
    ll hash = 0;
    for(int i=s.size()-1;i>=0;--i)
        hash = (hash * x + s[i]) % p;
    return hash;
}

/// Pre-processing
vll precomputeHashes(const string &txt, const string &ptrn){
    size_t l = txt.size()- ptrn.size();
    vll hash_table(l+1);
    hash_table[l] = polyHash(txt.substr(l));

    ll y=1;
    for(int j=1;j<=ptrn.size();j++)
        y = (y*x)%p;

    for (int i=l-1;i>=0;i--)
        hash_table[i] = ((hash_table[i+1]*x + txt[i] - txt[i+ptrn.size()]*y)%p + p) % p;

    return hash_table;
}

/// Rabin-Karp
vi get_occurrences(const Data& input) {
    const string& ptrn = input.pattern, txt = input.text;
    vi ans;
    ll ptrn_hash = polyHash(ptrn);

    vll hash_table = precomputeHashes(txt,ptrn);
    for (int i = 0; i <= txt.size() - ptrn.size(); ++i) {
        if (ptrn_hash == hash_table[i] && txt.compare(i,ptrn.size(),ptrn) == 0)
            ans.push_back(i);
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}

