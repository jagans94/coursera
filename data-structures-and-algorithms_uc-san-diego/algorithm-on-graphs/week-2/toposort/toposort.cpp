#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

typedef vector<int> vi;
typedef list<int> li;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

void explore(const vvi &adj,vb &visited, li &order, int x) {
    visited[x] = true;
    for(int i=0;i<adj[x].size();++i) {
        if (!visited[adj[x][i]]) {
            explore(adj, visited,order, adj[x][i]);
        }
    }
    order.push_front(x+1);
}

void dfs(vvi &adj, vb &visited, li &order,int n) {
    for(int i=0;i<n;++i){
        if(!visited[i]){
            explore(adj, visited, order, i);
        }
    }
}

li toposort(vvi adj, size_t n) {
    vb visited(n, false);
    list<int> order;
    dfs(adj,visited,order,n);
    return order;
}

int main() {
    size_t n, m;
    cin >> n >> m;
    vvi adj(n, vi());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    li order = toposort(adj, n);
    for (const auto &each:order) {
        cout << each << " ";
    }
}

