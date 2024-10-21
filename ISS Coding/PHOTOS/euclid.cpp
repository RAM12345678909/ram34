#include <iostream>

int euclideanGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int num1, num2;
    std::cout << "Enter two numbers to find their GCD: ";
    std::cin >> num1 >> num2;

    int gcd = euclideanGCD(num1, num2);

    std::cout << "GCD of " << num1 << " and " << num2 << " is " << gcd << std::endl;

    return 0;
}
