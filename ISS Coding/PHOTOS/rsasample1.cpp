#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Function to calculate GCD
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Function to calculate modular exponentiation
long long int power(long long int base, long long int exponent, long long int modulus) {
    long long int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

int main() {
    long long int p, q, n, phin, d, e = 0;
    string message;

    // Input p and q
    cout << "Enter the value of p: ";
    cin >> p;

    cout << "Enter the value of q: ";
    cin >> q;

    // Calculate n and phi(n)
    n = p * q;
    phin = (p - 1) * (q - 1);

    // Find e such that gcd(e, phi(n)) = 1
    for (int i = 2; i < phin; i++) {
        if (gcd(i, phin) == 1) {
            e = i;
            break;
        }
    }

    // Calculate d as the modular inverse of e modulo phi(n)
    for (int i = 1; i < phin; i++) {
        if ((i * e) % phin == 1) {
            d = i;
            break;
        }
    }

    // Display public and private keys
    cout << "\nPublic Key (e, n): (" << e << ", " << n << ")";
    cout << "\nPrivate Key (d, n): (" << d << ", " << n << ")";

    // Input message
    cin.ignore(); // Clear the input buffer
    cout << "\nEnter message: ";
    getline(cin, message);

    // Encrypt message
    string decrypt=message;
    cout << "\nEncrypted message: ";
    for (char ch : message) {
        long long int encryptedChar = power(ch, e, n);
        cout << encryptedChar << " ";
    }

    // Decrypt message
    cout << "\nDecrypted message: ";
    for (char ch : message) {
        long long int decryptedChar = power(ch, d, n);
    }
        cout << decrypt;

    return 0;
}
