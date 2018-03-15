#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

long long get_fibonacci_partial_sum_naive(long long to, long long from) {

    long long previous = 0, current  = 1 , sum = 0;

    //Base case:
    if (to < 2)
        return to;

    for (long long i = 1; i <= to ; ++i) {

        if( i >= from ){
            sum += current;
        }

        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        //cout << previous << " " << current << endl;
    }
    return sum % 10;
}

long long get_fibonacci_partial_sum_better(long long to, long long from) {

    //For 'd' = 10, 'l' = 60; Use an appropriate (d,l) pair.
    //'d' should be a positive power of 10 for ease of implementation.
    int d = 10 , l = 60;

    //Normalize 'to' and 'from'
    to += 2; from += 1;
    to %= l; from %= l;

    int curr = 1, prev = 0;
    int result = 0;

    //Edge cases:
    if (to < 2)
        result = to;
    if (from == 1)
        result -= 1;

    //After normalization 'to' may become smaller than 'from'.
    for( int i =2 ; i <= to || i <= from ; ++i ){

        //cout << curr << " ";
        int temp = curr%d;
        curr = (prev + temp)%d;
        prev = temp%d;

        if( i == from )
            result -= curr;

        if (i == to)
            result+=curr;
    }
    return (result < 0)? result + 10 : result;
}

void testing_solution(){
    srand(time(0));
    while (true){
        long long n = rand()%90 + 1, m = rand()%n;

        long long naive = get_fibonacci_partial_sum_naive(n,m);
        long long better = get_fibonacci_partial_sum_better(n,m);

        cout <<  naive <<  " " << better << endl;

        if(naive != better){
            cout << "Testcase Failed. " << n << " " << m << endl;
            break;
        }
    }
}

int main() {
    long long n = 0, m = 0;
    std::cin >> m >> n;
    std::cout << get_fibonacci_partial_sum_better(n,m);
    //testing_solution();
}

