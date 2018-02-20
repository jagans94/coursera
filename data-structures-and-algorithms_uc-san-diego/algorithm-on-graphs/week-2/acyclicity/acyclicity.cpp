#include <iostream>
#include <vector>

using namespace std;

typedef vector<bool> vb;
typedef vector<vector<int>> vvi;

bool reach(const vvi &adj,vb &visited,vb &rec_stack , int x) {
    bool isCycle = false;
    visited[x] = true; rec_stack[x] = true;

    for(int i=0;i<adj[x].size();++i) {

        if(rec_stack[adj[x][i]]){
            //cout << "back edge: (" << x+1 << "," << adj[x][i] + 1 << ")" << '\n';
            return true;
        }

        if (!visited[adj[x][i]]) {
            isCycle = reach(adj, visited, rec_stack, adj[x][i]);
        }

        if(isCycle)
            break;
    }
    rec_stack[x] = false;
    return isCycle;
}

int acyclic(vvi &adj,vb &visited, int n) {
    int res = 0;
    for(int i=0;i<n;++i){
        vb rec_stack (n, false);
        if(!visited[i]){
            res = reach(adj, visited, rec_stack, i) ? 1 : 0;
            if(res == 1) break;
        }
    }
    return res;
}


int main() {
    size_t n, m;
    std::cin >> n >> m;
    vvi adj(n, vector<int>());
    vb visited (n,false);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj,visited,n);
}

