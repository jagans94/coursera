#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

enum Color
{
    WHITE,
    BLACK
};

int bipartite(vvi &adj, size_t n) {
    int s = 0;
    vi color (n,BLACK); color[s] = WHITE;
    vi dist (n,-1); dist[s] = 0;
    queue<int> Q; Q.push(s);
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i=0;i<adj[u].size();++i){

            if(dist[adj[u][i]] < 0){
                dist[adj[u][i]] = dist[u] + 1;
                // An edge will have the same color at both end, only if they have both been discovered already.
                // The color is changed only once per vertex. The rest is pretty obvious.
                color[adj[u][i]] = (color[u] == WHITE)? BLACK : WHITE;
                Q.push(adj[u][i]);
            }

            if(color[adj[u][i]] == color[u]){
                return 0;
            }
        }
    }
    return 1;
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
    cout << bipartite(adj, n);
}


