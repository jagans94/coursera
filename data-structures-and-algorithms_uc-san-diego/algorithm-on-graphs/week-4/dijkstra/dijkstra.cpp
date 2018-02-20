#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>
#include <algorithm>

using namespace std;

struct Node{
    int key, dist;
    Node(int k, int d):key(k),dist(d){};
};

typedef vector<vector<int>> vvi;
typedef vector<int> vi;
typedef greater<int> gi;
typedef vector<Node> vN;

class mycomparison
{
    bool reverse;
public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const Node& lhs, const Node &rhs) const
    {
        if (reverse) return (lhs.dist>rhs.dist);
        else return (lhs.dist<rhs.dist);
    }
};

int distance(vvi &adj, vvi &cost, int s, int t) {
    size_t n = adj.size();
    vN shortestPaths (n,Node(-1,numeric_limits<int>::max()));
    for(int i=0;i<n;++i)
        shortestPaths[i] = Node{i,numeric_limits<int>::max()};
    shortestPaths[s].dist = 0;

    priority_queue<int, vN, mycomparison> pQ(mycomparison(true)); pQ.push(shortestPaths[s]);
    while(!pQ.empty()) {
        Node u = pQ.top(); pQ.pop();
        if(u.key == t){
            return u.dist;
        }
        for(int i=0;i<adj[u.key].size();++i){
            if(shortestPaths[adj[u.key][i]].dist > shortestPaths[u.key].dist + cost[u.key][i]){
                shortestPaths[adj[u.key][i]].dist = shortestPaths[u.key].dist + cost[u.key][i];
                pQ.emplace(shortestPaths[adj[u.key][i]]);
            }
        }
    }
    return -1;
}

int main() {

    int n, m;
    cin >> n >> m;
    vvi adj(n, vi());
    vvi cost(n, vi());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    int s, t;
    cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}

