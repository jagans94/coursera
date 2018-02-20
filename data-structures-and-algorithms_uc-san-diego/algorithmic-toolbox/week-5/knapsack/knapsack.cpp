#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int optimal_weight(int W, const vector<int> &w) {
    size_t n = w.size();
    vector<vector<int>> weight_by_item (W+1,vector<int> (n+1,0));

    for(int j=1;j<n+1;++j){
        for(int i=1;i<W+1;++i){
            weight_by_item[i][j] =
                    i >= w[j - 1] ? max(weight_by_item[i - w[j - 1]][j - 1] + w[j - 1], weight_by_item[i][j - 1])
                                 : weight_by_item[i][j - 1];
        }
    }
    /*
    for(int i=0;i<W+1;++i) {
        for (int j = 0; j < n + 1; ++j) {
            cout << setw(4) << weight_by_item[i][j];
        }
        cout << '\n';
    }
    cout << endl;
    */

    return weight_by_item[W][n];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n,0);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cout << optimal_weight(W, w) << '\n';
}

