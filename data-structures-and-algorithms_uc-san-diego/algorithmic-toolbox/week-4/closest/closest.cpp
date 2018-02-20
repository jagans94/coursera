#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

#define DOUBLE_MAX 1000000000000000000

using namespace std;

struct Point{
    int x=0,y=0;
};

typedef vector<Point> Points;

double distance(const Point &A, const Point &B){
    return sqrt(pow((A.x - B.x),2) + pow((A.y - B.y),2));
}

double minimal_distance_brute_force(const Points &points){
    double min_dist = DOUBLE_MAX;
    for(int i=0;i<points.size();++i){
        for(int j = i+1;j<=points.size();++j){
            min_dist = min(min_dist, distance(points[i], points[j]));
        }
    }
    return min_dist;
}

double closest_pair_split(Points &points, double min_dist){

    size_t center = points.size()/2;
    int strip_center_x = points[center].x;
    Points strip;
    for(int i = 0; i <= points.size(); ++i){
        if(abs(strip_center_x - points[i].x) <= min_dist){
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(),strip.end(),[](const Point &a, const Point &b) { return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y); });

    double best_dist = min_dist;

    for(int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < min(i + 8, int(strip.size())); ++j) {
            best_dist = min(best_dist, distance(strip[i], strip[j]));
        }
    }
    return best_dist;
}

double closest_pair(Points &points){
    //  Base Case:
    if(points.size() <= 3){
        return minimal_distance_brute_force(points);
    }

    //  Splitting the array and computing the min_dist of the individual splits
    size_t mid = points.size()/2;

    Points p_l (points.begin(),points.begin()+mid);
    Points p_r (points.begin() + mid, points.end());

    double min_dist_left_right = min(closest_pair(p_l),closest_pair(p_r));

    // Computing the min_dist across the split
    double min_dist_split = closest_pair_split(points,min_dist_left_right);

    return min(min_dist_left_right,min_dist_split);
}

int main() {

    int n, x, y;;
    cin >> n;

    Points points(n,Point{0,0});
    for(int i=0;i<n;++i) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end(),[](const Point &a, const Point &b) { return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x); });

    cout << fixed << setprecision(6) << closest_pair(points) << "\n";
}

