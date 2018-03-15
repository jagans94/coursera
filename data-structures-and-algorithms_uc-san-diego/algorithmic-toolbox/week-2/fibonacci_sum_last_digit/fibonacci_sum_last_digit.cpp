#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current;
    }

    return sum % 10;
}

long long fibonacci_sum_better(long long n) {

    //For 'm' = 10, 'l' = 60; Use an appropriate (m,l) pair.
    //'m' should be a positive power of 10 for ease of implementation.
    int m = 10 , l = 60;
    n += 2;
    n %= l;

    int curr = 1, prev = 0;

    if (n < 2)
        return (n == 0)? 9 : 0;

    for(int i=2; i<=n ;++i){

        //Debugging
        //cout << curr << " ";

        int temp = curr%m;
        curr = (prev + temp)%m;
        prev = temp%m;
    }
    //cout << endl;

    return curr ? curr - 1 : 9;
}

void testing_solution(){
    srand(time(0));
    while (true){
        long long n = rand()%90 + 1;

        long long naive = fibonacci_sum_naive(n);
        long long better = fibonacci_sum_better(n);

        cout <<  naive <<  " " <<  better << endl;

        if(naive != better){
            cout << "Testcase Failed. " << n ;
            break;
        }
    }
}

int main() {
    long long n = 0;
    std::cin >> n;
    std::cout << fibonacci_sum_better(n);
    //testing_solution();
}
