#include <iostream>
#include <string>
#include <cmath>

using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int gcdEuclid(int a, int b) {
    int res = (a > b) ? b : a;
    while (res > 0) {
        if (a % res == 0 && b % res == 0)
            break;
        res--;
    }
    return res;
}

// Function for modular exponentiation
long long modPow(long long base, long long exponent, long long modulus) {
    long long result = 1;
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
    // Step 1: Generate two prime numbers
    int prime_number1, prime_number2;
    do {
        cout << "Enter two prime numbers: ";
        cin >> prime_number1 >> prime_number2;
        if (!isPrime(prime_number1) || !isPrime(prime_number2)) {
            cout << "Both numbers must be prime. Please try again.\n";
        }
    } while (!isPrime(prime_number1) || !isPrime(prime_number2));

    // Step 2: Calculate n and pi_n
    int n = prime_number1 * prime_number2;
    int pi_n = (prime_number1 - 1) * (prime_number2 - 1);

    // Step 3: Choose e (usually a small prime relative to pi_n)
    int e = 2; // Initialize e to a suitable value.
    while (e < pi_n) {
        if (gcdEuclid(e, pi_n) == 1) {
            break;
        }
        e++;
    }

    // Step 4: Calculate d (private key)
    int k = 2;
    int d = 1;
    while ((k * pi_n + 1) % e != 0) {
        k++;
    }
    d = (k * pi_n + 1) / e;

    // Display public and private keys
    cout << "Public Key (n, e): (" << n << ", " << e << ")\n";
    cout << "Private Key (n, d): (" << n << ", " << d << ")\n";

    // Take input string from user
    string input;
    cout << "Enter a string in uppercase letters: ";
    cin.ignore();
    getline(cin, input);

    // Encrypt each character
    cout << "Encrypted values: ";
    for (char c : input) {
        int asciiVal = static_cast<int>(c);
        // Apply RSA encryption formula
        long long encryptedVal = modPow(asciiVal, e, n);
        cout << encryptedVal << " ";
    }
    cout << endl;

    // Decrypt each character
    cout << "Decrypted values: ";
    for (char c : input) {
        int asciiVal = static_cast<int>(c);
        // Apply RSA decryption formula
        long long decryptedVal = modPow(asciiVal, d, n);
        cout << decryptedVal << " ";
    }
    cout << endl;

    return 0;
}
