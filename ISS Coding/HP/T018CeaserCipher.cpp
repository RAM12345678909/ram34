#include <iostream>
#include <string>

std::string encryptCaesar(const std::string& message, int shift) {
    std::string result = message;

    for (char& ch : result) {
        if (std::isalpha(ch)) {
            char base = (std::isupper(ch)) ? 'A' : 'a';
            ch = (ch - base + shift) % 26 + base;
        }
    }

    return result;
}

int main() {
    std::string message;
    int shift;

    std::cout << "Enter the message: ";
    std::getline(std::cin, message);

    std::cout << "Enter the shift value: ";
    std::cin >> shift;

    std::string encryptedMessage = encryptCaesar(message, shift);

    std::cout << "Encrypted message: " << encryptedMessage << std::endl;

    return 0;
}
