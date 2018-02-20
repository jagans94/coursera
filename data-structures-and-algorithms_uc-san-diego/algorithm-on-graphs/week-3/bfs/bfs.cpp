#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

int modified_bfs(vvi &adj, int s, int t, size_t n) {
    vi dist (n,-1); dist[s] = 0;
    queue<int> Q; Q.push(s);
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i=0;i<adj[u].size();++i){
            if(dist[adj[u][i]] < 0){
                dist[adj[u][i]] = dist[u] + 1;
                Q.push(adj[u][i]);
            }
            if(adj[u][i] == t)
                return dist[t];
        }
    }
    return -1;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vvi adj(n, vi());
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    cout << modified_bfs(adj, s, t, n);
}

