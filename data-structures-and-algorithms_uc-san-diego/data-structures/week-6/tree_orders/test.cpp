#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main(){
	vector<int> result;
	result.emplace_back(10);
	auto it = result.end()-1;
	cout << *it;
	return 0;
}