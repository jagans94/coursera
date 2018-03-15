#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using  namespace std;

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}
/*
 * This method can be implemented without using an array, but will require another
 * loop to calculate the fibonacci number separately.
 *
 * Fibonacci numbers have a useful property;
 * When you perform modulo operation on the fibonacci series, the values repeat themselves
 * at certain intervals called the pisano period. The period always begins with 0,1.
 * Interestingly, even the remainders of the fibonacci series follow the fibonacci pattern, while
 * only being limited to values lesser than that of the divisor.
 *
 * Reference: Numberphile
 */
long long get_fibonacci_huge_better(long long n, long long m) {

    if (n < 2)
        return n;

    //The min value of 'l' is equal to 3, i.e. the pisano period of Fn mod m, when m = 2;
    long long l = 3;

    vector<long long> fib_huge = {0,1};

    //The interval 'l' can exceed 'n' in cases where n is small.
    for(long long i=2; /*No exit condition*/ ;++i){

        //Calculating Fi
        fib_huge.push_back((fib_huge[i-1] + fib_huge[i-2])%m);

        //Debugging
        //cout << fib_huge[i] << " ";

        //Calculating interval L
        if(fib_huge[i] == 1 && fib_huge[i-1] == 0){
            // l = i-2 + 1 (1 is added for 0 adjusting).
            l = i-1; break;
        }
    }

    //cout << endl;
    //cout << l << endl;

    n %= l;

    return fib_huge[n]%m;
}

long long get_fibonacci_huge_better_2(long long n, long long m) {

    if (n < 2)
        return n;

    //The min value of 'l' is equal to 3, i.e. the pisano period of Fn mod m, when m = 2;
    long long l = 3;

    long long prev = 0, curr = 1;

    //The interval 'l' can exceed 'n' in cases where n is small.
    for(long long i=2; /*No exit condition*/ ;++i){

        //Calculating Fn remainder
        long long temp = curr%m;
        curr = (temp + prev)%m;
        prev = temp %m;

        //Debugging
        //cout << curr << " ";

        //Calculating interval L
        if(curr == 1 && prev == 0){
            // l = i-2 + 1 (1 is added for 0 adjusting).
            l = i-1; break;
        }
    }

    //cout << endl;
    //cout << l << endl;

    n %= l;

    //Calculating new Fn remainder
    if (n < 2)
        return n;

    // The iteration range for i is from 2 to n (inclusive).
    for (int i = 2; i <= n; ++i) {
        long long temp = curr%m;
        curr = (temp + prev)%m;
        prev = temp %m;
    }

    return curr;
}


    void testing_solution(){
        srand(time(0));
        while (true){
            long long m = rand()%100000 + 2 , n = rand()%10000000000 + 1;

            long long naive = get_fibonacci_huge_naive(n,m);
            long long better = get_fibonacci_huge_better(n,m);
            long long better2 = get_fibonacci_huge_better_2(n,m);

            cout <<  better <<  " " << better2 << endl;

            if(better2 != better){
                cout << "Testcase Failed. " << n << " " << m;
                break;
            }
        }
    }

int main() {
    long long n, m;
    std::cin >> n >> m;
    //cout << get_fibonacci_huge_better(n, m);
    cout << get_fibonacci_huge_better_2(n, m);
    //testing_solution();
}
