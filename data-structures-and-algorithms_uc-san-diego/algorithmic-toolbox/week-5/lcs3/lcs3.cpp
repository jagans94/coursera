#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;

int lcs3(vi &a, vi &b, vi &c) {
    size_t l = a.size(), m = b.size(), n = c.size();
    vvvi ss(l+1,vvi(m+1,vi(n+1)));
    for(int i=1;i<=l;++i){
        for(int j=1;j<=m;++j){
            for(int k=1;k<=n;++k) {
                /// A total of seven possible conditions occur; they are:
                /// a) All of them match (1), b) None of them match(3) and c) Only two of them match(3)
                /// The only condition for forward evaluation is when all 3 sequences have a match.
                if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1]) {
                    ss[i][j][k] = ss[i - 1][j - 1][k - 1] + 1;
                }
                /// The other six conditions can be evaluated as follows (just like w/ 2 sequences):
                ss[i][j][k] = max({ss[i][j][k], ss[i-1][j][k], ss[i][j-1][k], ss[i][j][k-1],
                                   ss[i-1][j-1][k], ss[i][j-1][k-1], ss[i-1][j][k-1]});
            }
        }
    }
    return ss[l][m][n];
}

int main() {
    size_t an; cin >> an;
    vi a(an);
    for (size_t i = 0; i < an; i++) {
        cin >> a[i];
    }

    size_t bn; cin >> bn;
    vi b(bn);
    for (size_t i = 0; i < bn; i++) {
        cin >> b[i];
    }

    size_t cn; cin >> cn;
    vi c(cn);
    for (size_t i = 0; i < cn; i++) {
        cin >> c[i];
    }

    cout << lcs3(a, b, c) << endl;
}

