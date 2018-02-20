#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>


using namespace std;

struct Point{
    int x=0,y=0;
    int index = -1;
    Point(int f_x, int f_y):x(f_x),y(f_y){}
};

struct Edge{
    Point u = Point(0,0),v = Point(0,0);
    double weight=0.0;
    Edge(Point u, Point v, double weight):u(u),v(v),weight(weight){}
};

typedef vector<Point> vP;
typedef vector<Edge> vE;

struct DisjointSetsElement {
    int parent_idx = -1, rank = 0;
    explicit DisjointSetsElement(int parent = -1, int rank = 0): parent_idx(parent), rank(rank){}
};

struct DisjointSets {
    long long size;
    vector <DisjointSetsElement> sets;

    explicit DisjointSets(long long size): size(size), sets(size){
        for (int i = 0; i < size; i++){
            sets[i].parent_idx = i;
        }
    }

    int find(int index) {
        if(sets[index].parent_idx != index){
            sets[index].parent_idx = find(sets[index].parent_idx);
        }
        return sets[index].parent_idx;
    }

    void merge(int A, int B) {
        int A_root = find(A);
        int B_root = find(B);

        if (A_root == B_root)
            return;

        if (sets[A_root].rank > sets[B_root].rank) {
            sets[B_root].parent_idx = A_root;
        } else {
            sets[A_root].parent_idx = B_root;
            if (sets[A_root].rank == sets[B_root].rank)
                ++sets[A_root].rank;
        }
    }
};

double dist( Point &a, Point &b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

bool sort_edges( Edge &a, Edge &b){
    return a.weight < b.weight;
}

vE calculateEdges( vP &points){
    size_t n = points.size();
    vE edges;
    for(int i=0;i<n;++i){
        for(int j=i+1;j<n;++j){
            Point a = points[i], b = points[j];
            edges.emplace_back(Edge(a,b,dist(a,b)));
        }
    }
    sort(edges.begin(),edges.end(),sort_edges);
    return edges;
}

double clustering( vP &points,int k) {
    /// n = no. of trees in the forest at any given time
    size_t n = points.size();
    DisjointSets forest(n);
    vE sortedEdgeList = calculateEdges(points);
    /// i.e. if every point has been consolidated into a single tree then we break out as there is no need to
    /// add anymore edges. Though if k >= 2 then this shouldn't be triggered at all.
    for(int i=0;i<sortedEdgeList.size() && n > 1;++i){
        Edge u_v = sortedEdgeList[i];
        if(forest.find(u_v.u.index)!= forest.find(u_v.v.index)){
            if(n == k)
                return u_v.weight;
            forest.merge(u_v.u.index, u_v.v.index);
            --n;
        }
    }
    return 0;
}

int main() {
    size_t n; cin >> n;
    vP points(n,Point(0,0));
    for (size_t i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].index = i;
    }
    int k; cin >> k;
    cout << setprecision(10) << clustering(points,k) << endl;
}

