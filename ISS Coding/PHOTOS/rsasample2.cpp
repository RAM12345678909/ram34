// Take p = 53, q = 59
// Message = ATHARVA

#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
using namespace std;

// Function for calculating GCD
int gcd(int a, int b) {
    int remainder;
    int flag = 0;

    while (flag == 0) {
        if (a != 0 && b != 0) {     // Checking if a or b is 0 or not
            remainder = a % b;      // Calculate the remainder

            a = b;
            b = remainder;
        } else {
            if (a == 0) {           // If a is 0 then return b
                flag = 1;
                return b;
            } else if (b == 0) {    // If b is 0 then return b
                flag = 1;
                return a;
            }
        }
    }
}

// Function for calculating power
long long int power(long long int base, long long int exponent, long long int modulus) {
    if (exponent == 0)              // If exponent is 0 then return 1
        return 1;
    else if (exponent % 2 == 0)     // If modulus is 0 then use this formula
        return power((base * base) % modulus, exponent / 2, modulus) % modulus;
    else                            // Else use this
        return (base * power((base * base) % modulus, (exponent - 1) / 2, modulus)) % modulus;
}

int main() {
    double p, q, n, phin, d, e = 0, k = 2;
    string message;
    int asciiValue = 0, messageLength, i = 0;

    cout << "Enter the value of p: ";
    cin >> p;                               // Get the value of p

    cout << "Enter the value of q: ";
    cin >> q;                               // Get the value of q

    n = p * q;                              // Calculating the value of n

    cout << "\nValue of n: " << n;

    phin = (p - 1) * (q - 1);               // Calculating phi(n) using formula

    cout << "\nValue of phi(n): " << phin;

    for (i = 2; i < (int)phin; i++) {       // Lopp for identifying the value of e
        if (gcd(i, (int)phin) == 1)
        {
            e = i;
            break;
        }
    }

    cout <<"\nValue of e: " << e;

    d = ((k * phin) + 1) / e;           // Calculating the value of d

    cout << "\nValue of d: " << d;

    cout << "\n\nEnter message: ";
    cin >> message;                     // User input for taking message

    messageLength = message.length();   // Calculating message length

    int ascii[messageLength];

    cout << "\nASCII Values:";
    i = 0;
    for (char ch : message) {          // Getting ASCII value of characters in message
        asciiValue = (int)ch;

        ascii[i] = asciiValue;
        cout << "\n" << ascii[i];
        i++;
    }

    long long int encryptedMessage[messageLength];

    for (i = 0; i < message.length(); i++) {
        encryptedMessage[i] = power(ascii[i], e, n);            // Encrypting the message
    }

    cout << "\n\nEncrypted message: ";
    for (i = 0; i< message.length(); i++) {
        cout << "\n" << encryptedMessage[i];
    }

    cout << "\n\nDecrypted message: ";
    for (i = 0; i < message.length(); i++) {
        cout << (char)power(encryptedMessage[i], d, n);        // Decrypting the message
    }
}
