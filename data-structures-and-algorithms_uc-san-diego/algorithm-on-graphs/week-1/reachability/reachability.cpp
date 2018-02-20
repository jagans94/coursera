#include <iostream>
#include <vector>

using namespace std;

void reach(const vector<vector<int> > &adj,vector<bool> &visited, int x, int y) {
    visited[x] = true;
    //cout << x << " " << y << '\n';
    if(visited[y])
        return;

    for(int i=0;i<adj[x].size();++i) {
        if (!visited[adj[x][i]]) {
            reach(adj, visited, adj[x][i], y);
        }
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<bool> visited(n, false);
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }

    int x, y;
    cin >> x >> y;

    /*
    //cout << endl;
    for (int i = 0; i < adj.size(); ++i) {
        //cout << i << " -> ";
        for (int j = 0; j < adj[i].size(); ++j) {
            //cout << adj[i][j] << " ";
        }
        //cout << '\n';
    }
     */

    reach(adj, visited, x - 1, y - 1);
    cout << (visited[y - 1] ? 1 : 0);
}

