#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

long long lcm_naive(int a, int b) {
    for (long l = 1; l <= (long long) a * b; ++l)
        if (l % a == 0 && l % b == 0)
            return l;

    return (long long) a * b;
}

long long gcd_efficient(long long a, long long b){

    if(b == 0)
        return a;

    a %= b;
    return gcd_efficient(b,a);
}

long long lcm_efficient(long long a, long long b) {
    return (a * b)/gcd_efficient(a,b);
}

void test_solution(){

    srand(time(0));
    while(true){


        long long a = rand()%100 + 1, b = rand()%101 + 7;

        long long naive = lcm_naive(a, b);
        long long better = lcm_efficient(a,b);

        if(naive != better)
            break;

        std::cout << naive << " " << better << '\n';
        cout << "OK" << '\n';
    }
}

int main() {

    /* Though both 'a' and 'b' are smaller than a signed 32 bit integer data type, for values of 'a' & 'b' ,i.e. say nearing 2e31,
     * their product becomes larger than 32 bits. Assigning the product to a 64 bit (or higher) integer data types still results
     * in an overflow. The reason being, when 'a' and 'b' are multiplied, their product is stored in 'a', before being moved to the assigned 64 bit
     * (or higher) integer variable. But, since 'a' can accommodate only 32 bits, doing so results in an overflow.
     *
     * To solve this problem, you need only intialize the variables with larger integer data type.
     *
     */

    long long a, b;
    std::cin >> a >> b;
    //std::cout << lcm_naive(a, b) << std::endl;
    std::cout << lcm_efficient(a, b);
    //test_solution();
    return 0;
}
