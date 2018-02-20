#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::cin;
using std::cout;

long long MaxPairwiseProduct(const vector<int>& numbers) {
  int mx1 = -3, mx2 = -1, mx1_idx = -2, mx2_idx = -1;
  int n = numbers.size();

  for (int i = 0; i < n; ++i){
  	if (mx1 < numbers[i])
  	{
  		mx1 = numbers[i];
  		mx1_idx = i;
  	}
  }
  
  for (int i = 0; i < n; ++i){
  	if (mx2 < numbers[i] && i != mx1_idx)
  	{
  		mx2 = numbers[i];
  		mx2_idx = i;
  	}
  }
  
  return (long long) mx1*mx2;
}

int main() {
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    cout << MaxPairwiseProduct(numbers) << "\n";
    return 0;
}
