#include <iostream>
#include <cstdlib>
using namespace std;

long long get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_better(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
    }

    return current;
}


void test_solution(){

    int i = 0;
    while (true){
        int x = rand() % 100;

        long long naive = get_fibonacci_last_digit_naive(x);
        int better = get_fibonacci_last_digit_better(x);

        std::cout << naive << " " << better << "\n";

        if(naive != better) {
            cout<<"X = "<< x <<endl;
            cout<<"I = "<< i <<endl;
            break;
        }
        else
            ++i;

        if (i == 100)
            break;
    }
}


int main() {
    int n;
    std::cin >> n;
    std::cout << get_fibonacci_last_digit_better(n);
    //test_solution();
}
