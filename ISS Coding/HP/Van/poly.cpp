#include <iostream>
#include <string>

using namespace std;

string encrypt(string text, string key) {
    string encrypted = "";
    int keyLength = key.length();

    for (int i = 0; i < text.length(); ++i) {
        char plainChar = text[i];
        char keyChar = key[i % keyLength];

        if (isalpha(plainChar)) {
            char base = isupper(plainChar) ? 'A' : 'a';
            char encryptedChar = ((plainChar - base) + (keyChar - 'A')) % 26 + base;
            encrypted += encryptedChar;
        } else {
            encrypted += plainChar;
        }
    }

    return encrypted;
}

string decrypt(string text, string key) {
    string decrypted = "";
    int keyLength = key.length();

    for (int i = 0; i < text.length(); ++i) {
        char cipherChar = text[i];
        char keyChar = key[i % keyLength];

        if (isalpha(cipherChar)) {
            char base = isupper(cipherChar) ? 'A' : 'a';
            char decryptedChar = ((cipherChar - base) - (keyChar - 'A') + 26) % 26 + base;
            decrypted += decryptedChar;
        } else {
            decrypted += cipherChar;
        }
    }

    return decrypted;
}

int main() {

    string ptext, key;

    cout<<"enter text : ";
    cin>>ptext;
    cout<<"enter key : ";
    cin>>key;

   /* string ptext = "Hello";
    string key = "KEY";*/

    string encryptedText = encrypt(ptext, key);
    string decryptedText = decrypt(encryptedText, key);

    cout << "\nOriginal Text: " << ptext << endl;
    cout << "Key: " << key << endl;
    cout << "Encrypted Text: " << encryptedText << endl;
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
