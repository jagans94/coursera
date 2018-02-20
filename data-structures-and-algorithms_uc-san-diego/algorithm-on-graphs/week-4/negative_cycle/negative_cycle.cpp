#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ll posinf = numeric_limits<ll>::max()/100;
int negative_cycle(vvll &adj, vvll &cost){
    size_t n = adj.size();
    vll distance(n,posinf);  distance[0] = 0;

    bool improvements;
    ///  B-F Algorithm with k (<= V-1) iterations
    for(int k=0;k<n-1;++k) {
        improvements = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < adj[i].size(); ++j) {
                /// The distance[i] != posinf is a really important condition for correct evaluation
                if(distance[i] != posinf && distance[adj[i][j]] > distance[i] + cost[i][j]){
                    improvements = true;
                    distance[adj[i][j]] = distance[i] + cost[i][j];
                }
            }
        }
        if(!improvements)
            return 0;
    }

    ///  B-F Algorithm Vth iteration
    for(int i=0;i<n;++i){
        for (int j = 0; j < adj[i].size(); ++j) {
            /// The distance[i] != posinf is a really important condition for correct evaluation
            if(distance[i] != posinf && distance[adj[i][j]] > distance[i] + cost[i][j]){
                return 1;
            }
        }
    }
}

int main() {

    size_t n, m;
    cin >> n >> m;
    vvll adj(n, vll());
    vvll cost(n, vll());
    for (int i = 0; i < m; i++) {
        ll x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cout << negative_cycle(adj, cost);
}
