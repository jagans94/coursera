#include <iostream>

using  namespace std;

int get_change(int m) {
    int numOfCoins = 0 , q = 0;

    if(m>=10){
        numOfCoins = m / 10;
        m %= 10;
    }

    if(m>=5){
        ++numOfCoins;
        m -= 5;
    }

    numOfCoins += m;

    return numOfCoins;
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
