#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

// Function to calculate the modular exponentiation (x^y mod m)
long long mod_pow(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to calculate the greatest common divisor (gcd) of two numbers
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to perform RSA key generation
void generateKeys(long long& e, long long& d, long long& n) {
    // In practice, choose larger prime numbers for p and q
    long long p = 61;
    long long q = 53;

    n = p * q;
    long long phi = (p - 1) * (q - 1);

    // Choose e randomly within a certain range
    srand(static_cast<unsigned>(time(0)));
    do {
        e = rand() % (phi - 2) + 2; // Random e between 2 and phi-1
    } while (gcd(e, phi) != 1);

    // Calculate d, the modular multiplicative inverse of e (d * e % phi = 1)
    d = 0;
    while ((d * e) % phi != 1) {
        d++;
    }

    std::cout << "Public Key (e, n): (" << e << ", " << n << ")" << std::endl;
    std::cout << "Private Key (d, n): (" << d << ", " << n << ")" << std::endl;
}

// Function to encrypt a message using RSA
std::vector<long long> encrypt(const std::string& message, long long e, long long n) {
    std::vector<long long> ciphertext;

    std::cout << "Encrypting message:" << std::endl;
    for (char c : message) {
        long long asciiValue = static_cast<long long>(c);
        std::cout << "Character: " << c << " ASCII: " << asciiValue;

        long long encryptedChar = mod_pow(asciiValue, e, n);
        std::cout << " Encrypted: " << encryptedChar << std::endl;

        ciphertext.push_back(encryptedChar);
    }

    return ciphertext;
}

// Function to decrypt a ciphertext using RSA
std::string decrypt(const std::vector<long long>& ciphertext, long long d, long long n) {
    std::string decryptedMessage;

    std::cout << "\nDecrypting ciphertext:" << std::endl;
    for (long long encryptedChar : ciphertext) {
        std::cout << "Ciphertext: " << encryptedChar;

        long long decryptedValue = mod_pow(encryptedChar, d, n);
        char decryptedChar = static_cast<char>(decryptedValue);

        std::cout << " Decrypted ASCII: " << decryptedValue << " Decrypted Character: " << decryptedChar << std::endl;

        decryptedMessage += decryptedChar;
    }

    return decryptedMessage;
}

int main() {
    // Get input string
    std::string input;
    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    // Generate RSA keys
    long long e, d, n;
    generateKeys(e, d, n);

    // Encrypt the message
    std::vector<long long> ciphertext = encrypt(input, e, n);

    // Decrypt the ciphertext
    std::string decryptedMessage = decrypt(ciphertext, d, n);

    // Display results
    std::cout << "\nOriginal message: " << input << std::endl;
    std::cout << "Encrypted ciphertext: ";
    for (long long encryptedChar : ciphertext) {
        std::cout << encryptedChar << " ";
    }
    std::cout << std::endl;
    std::cout << "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}
