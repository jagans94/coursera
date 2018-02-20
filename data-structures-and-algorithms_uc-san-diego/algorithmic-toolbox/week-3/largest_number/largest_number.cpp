#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool sort_function(string &a, string &b){
    return(stoi(a+b) > stoi(b+a));
}

string largest_number(vector<string> a) {
    //  Just for lulz, you can test your own sort method in here.
    sort(a.begin(),a.end(),sort_function);

    std::stringstream ret;
    for (size_t i = 0; i < a.size(); i++) {
        ret << a[i];
    }
    string result;
    ret >> result;
    return result;
}

int main() {
    int n;
    std::cin >> n;
    vector<string> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    std::cout << largest_number(a);

}

