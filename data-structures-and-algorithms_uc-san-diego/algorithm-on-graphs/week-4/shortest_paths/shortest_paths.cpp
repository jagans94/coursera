#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;

ll posinf = numeric_limits<ll>::max()/100, neginf = numeric_limits<ll>::min()/100;

void shortest_paths(vvll &adj, vvll &cost, vll &distance) {
    size_t n = adj.size(); vll prev(n,-1);
    ///  B-F Algorithm with k (<= V-1) iterations
    for(int k=0;k<n-1;++k) {
        bool improvements = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < adj[i].size(); ++j) {
                /// The distance[i] != posinf is a really important condition for correct evaluation
                if(distance[i] != posinf && distance[adj[i][j]] > distance[i] + cost[i][j]){
                    improvements = true;
                    prev[adj[i][j]] = i;
                    distance[adj[i][j]] = distance[i] + cost[i][j];
                }
            }
        }
        if(!improvements)
            return;
    }

    ///  B-F Algorithm Vth iteration
    vll nS;
    for(int i=0;i<n;++i){
        for (int j = 0; j < adj[i].size(); ++j) {
            /// The distance[i] != posinf is a really important condition for correct evaluation
            if(distance[i] != posinf && distance[adj[i][j]] > distance[i] + cost[i][j]){
                prev[adj[i][j]] = i;
                nS.push_back(adj[i][j]);
            }
        }
    }

    /// Debugging
    /*
    for(const auto &each:nS){
        cout << each + 1<< " ";
    }
    cout << '\n';

    for(int i=0;i<n;++i){
        cout << prev[i] + 1<< " ";
    }
    cout << '\n';

    cout << "Works?\n";
    */


    /// Infinite Arbitrage Algorithm using DFS
    vb visited(n,false);
    while(!nS.empty()){
        ll u = nS.back(); nS.pop_back();
        if(visited[u])
            continue;

        distance[u] = neginf; visited[u] = true;
        for(int i=0;i<adj[u].size();++i){
            if(!visited[adj[u][i]]){
                nS.push_back(adj[u][i]);
            }
        }
    }
}

int main() {
    size_t n, m, s;
    cin >> n >> m;
    vvll adj(n, vll());
    vvll cost(n, vll());

    for (int i = 0; i < m; i++) {
        ll x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    cin >> s; s--;

    vll distance(n, posinf); distance[s] = 0;
    shortest_paths(adj, cost, distance);

    for(const auto &each:distance){
        if(each == posinf)
            cout << "*\n";
        else if(each == neginf)
            cout << "-\n";
        else
            cout << each << '\n';
    }
}

