#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>

using namespace std;

// GCD function
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Check if number is prime or not
bool isPrime(int num) {
    if (num <= 1) {
        return false;
    }

    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

// Power function
int power(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent & 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}

int main() {
    srand(time(0));

    cout << "Enter prime number p: ";
    int p;
    cin >> p;

    cout << "Enter prime number q: ";
    int q;
    cin >> q;

    cout << "Step 1:" << endl;
    cout << "Prime Number p: " << p << endl;
    cout << "Prime Number q: " << q << endl;
    cout << endl;
    cout << "Step 2:" << endl;

    int n = p * q;
    cout << "Modulus of Encryption and Decryption: " << n << endl;
    cout << endl;
    cout << "Step 3: " << endl;

    int phiN = (p - 1) * (q - 1);
    int e = 0;

    cout << "Enter value for e (should be coprime with phiN): ";
    cin >> e;

    // Check if e is coprime with phiN using gcd
    while (gcd(e, phiN) != 1) {
        cout << "Entered value for e is not coprime with phiN. Enter a different value for e: ";
        cin >> e;
    }

    cout << "Value of e: " << e << endl;
    cout << endl;

    cout << "Step 4:" << endl;
    cout << "Public Key <e, n>: "<< "<" << e << ", " << n << ">" << endl;
    cout << endl;

    cin.ignore(); // Clear the newline character from the input buffer

    string m;
    cout << "Enter plain text message (m) less than (n): ";
    getline(cin, m); // Enter a string value

    string encrypted;

    // Iterate each character in message
    cout << "Encrypted Text of (m): " << endl;
    for (char c : m) {
        std::cout << c << ": " << static_cast<int>(c) << "\n";
        int encryptedChar = power(static_cast<int>(c), e, n);
        encrypted += to_string(encryptedChar) + " ";
    }

    cout << "Step 6:" << endl;

    int d = 0;

    // Check if e and phiN are coprime
    if (gcd(e, phiN) != 1) {
        cout << "Error: e and phiN are not coprime. Private key generation failed." << endl;
    } else {
        // Find the modular multiplicative inverse of e modulo phiN
        for (int i = 2; i < phiN; i++) {
            if ((e * i) % phiN == 1) {
                d = i;
                break;
            }
        }

        cout << "Private Key <d, n>: " << "<" << d << ", " << n << ">" << endl;
        cout << endl;
    }

    cout << "Step 7:" << endl;

    string decrypted;
    stringstream ss(encrypted); // Create a stream of encrypted values
    string temp;

    // For each encrypted character get the value and convert back to character
    while (getline(ss, temp, ' ')) {
        if (!temp.empty()) {
            int encryptedChar = stoi(temp);
            int decryptedChar = power(encryptedChar, d, n);
            cout << "Decrypted Char (Ascii): " << decryptedChar << endl;
            decrypted += static_cast<char>(decryptedChar);
        }
    }

    cout << "Decrypted Message: " << decrypted << endl;

    return 0;
}
