
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

double get_optimal_value(double capacity, vector<int> weights, vector<int> values) {

    double value = 0.0;
    int n = values.size();

    vector<double> valueByWeights (n,0);
    unordered_map<double,int> indexMap;

    for(int i = 0; i < n; ++i){
        valueByWeights[i] = double(values[i])/weights[i];
        indexMap[valueByWeights[i]] = i;
    }

    sort(valueByWeights.begin(), valueByWeights.end());

    while(n > 0){
        double w = min(double(weights[indexMap[valueByWeights[n-1]]]),capacity);
        //cout << w <<'\n';
        value += w*valueByWeights[n-1];
        //cout << value <<'\n';
        capacity -= w;
        //cout << capacity <<'\n';
        if(capacity == 0){
            break;
        }
        n--;
    }

    return value;
}

int main() {
    int n;
    double capacity;
    std::cin >> n >> capacity;
    vector<int> values(n,0);
    vector<int> weights(n,0);
    for (int i = 0; i < n; i++) {
        std::cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}

