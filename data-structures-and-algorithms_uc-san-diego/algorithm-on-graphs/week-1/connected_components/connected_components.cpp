#include <iostream>
#include <vector>

using namespace std;

void reach(const vector<vector<int> > &adj,vector<bool> &visited, int x) {
    visited[x] = true;
    for(int i=0;i<adj[x].size();++i) {
        if (!visited[adj[x][i]]) {
            reach(adj, visited, adj[x][i]);
        }
    }
}

int number_of_components(vector<vector<int> > &adj,vector<bool> &visited, int n) {
    int res = 0;
    for(int i=0;i<n;++i){
        if(!visited[i]){
            reach(adj, visited, i);
            ++res;
        }
    }
    return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
    vector<bool> visited (n,false);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj,visited,n);
}

