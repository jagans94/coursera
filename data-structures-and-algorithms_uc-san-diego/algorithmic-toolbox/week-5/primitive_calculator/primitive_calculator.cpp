#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1000000000
using namespace std;

vector<int> optimal_sequence(int n) {
    vector<int> min_ops(n+1,MAX), sequence;
    min_ops[0] = 0;

    //Here we use DP to construct an array of "minimum no of operations" required to construct the number 'n'.
    for(int i=1;i<=n;++i){
        min_ops[i] = min_ops[i-1]+1;
        if(i%2 == 0){
            min_ops[i] = min(min_ops[i/2] + 1, min_ops[i]);
        }
        if(i%3 == 0) {
            min_ops[i] = min(min_ops[i / 3] + 1, min_ops[i]);
        }
    }

    //  The order by which we perform reconstruction is reversed i.e. div by 3, div by 2 and then sub with 1,
    //  because while constructing the array of 'minimum no. of operations' we started with ops add 1,
    //  mult by  2 and mult by 3 in that order. Therefore, by reversing the order of operations, we obtain
    //  the intended array which was the basis of computation of "min no. of ops" array required.

    //  Performing the operations in any other order may give you a different but comparable result. But for
    //  sake of uniformity, we'll stick to the below.

    while(n>0){
        sequence.push_back(n);

        if(min_ops[n] == min_ops[n/3] + 1 && n%3 == 0){
            n/=3;
        }
        else if(min_ops[n] == min_ops[n/2] + 1 && n%2 == 0){
            n/=2;
        }
        else if(min_ops[n] == min_ops[n-1] + 1){
            n-=1;
        }
    }

    reverse(sequence.begin(),sequence.end());

    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    cout << sequence.size() - 1 << endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        cout << sequence[i] << " ";
    }
}

