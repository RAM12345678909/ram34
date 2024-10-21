#include <iostream>

int eulerTotient(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int main() {
    int n;
    std::cout << "Enter a number to compute Euler's Totient function: ";
    std::cin >> n;

    int phi = eulerTotient(n);

    std::cout << "Euler's Totient function of " << n << " is " << phi << " (phi(" << n << "))" << std::endl;

    return 0;
}
