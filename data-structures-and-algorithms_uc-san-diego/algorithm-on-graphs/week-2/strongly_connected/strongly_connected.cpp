#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

typedef list<pair<int,int>> lpii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

int tick = 0;

void explore(const vvi &adj,vb &visited, lpii &order, int x) {
    visited[x] = true; ++tick;
    for(int i=0;i<adj[x].size();++i) {
        if (!visited[adj[x][i]]) {
            explore(adj, visited,order, adj[x][i]);
        }
    }
    order.push_front(make_pair(x+1,++tick)); // push node_index & post-visit val
}

void dfs(vvi &adj, lpii &order ,size_t n) {
    vb visited (n,false);
    for(int i=0;i<n;++i){
        if(!visited[i]){
            explore(adj, visited, order, i);
        }
    }
}

int number_of_strongly_connected_components(vvi &adj, vvi &r_adj, size_t n) {
    lpii order;
    dfs(r_adj,order,n);

    //for(const auto &each:order)
    //    cout << setw(5) << each.first << setw(5) << each.second << '\n';

    int no_of_scc = 0; vb visited (n,false);
    for(auto it = order.begin(); it != order.end(); ++it){
        if(!visited[it->first-1]) {
            ++no_of_scc;
            explore(adj, visited, order, it->first-1);
        }
    }
    return no_of_scc;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vvi adj(n, vi());
    vvi r_adj(n, vi());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        r_adj[y-1].push_back(x-1);
    }
    cout << number_of_strongly_connected_components(adj,r_adj,n);
}
