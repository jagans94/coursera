#include <iostream>
#include <vector>

using namespace std;

int binary_search(const vector<int> &a, int x) {
    int left = 0, right = (int)a.size();
    while(left <= right){
        int mid = (left + right)/2;
        if(a[mid] == x) return mid;
        else if (a[mid] > x) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int linear_search(const vector<int> &a, int x) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] == x) return i;
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n,0);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int m;
    std::cin >> m;
    vector<int> b(m,0);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    for (const auto &each : b){
        std::cout << binary_search(a,each) << " ";
    }
}

