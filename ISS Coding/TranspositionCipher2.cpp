#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to perform column transposition encryption
string encryptColumnTransposition(const string& plaintext, const vector<int>& key) {
    int numRows = (plaintext.length() + key.size() - 1) / key.size();
    int numCols = key.size();

    vector<vector<char>> matrix(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int col : key) {
        for (int row = 0; row < numRows; ++row) {
            if (index < plaintext.length()) {
                matrix[row][col] = plaintext[index++];
            }
        }
    }

    string ciphertext;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (matrix[row][col] != ' ') {
                ciphertext += matrix[row][col];
            }
        }
    }

    return ciphertext;
}

// Function to perform column transposition decryption
string decryptColumnTransposition(const string& ciphertext, const vector<int>& key) {
    int numRows = (ciphertext.length() + key.size() - 1) / key.size();
    int numCols = key.size();

    vector<vector<char>> matrix(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int col = 0; col < numCols; ++col) {
        for (int row = 0; row < numRows; ++row) {
            if (index < ciphertext.length()) {
                matrix[row][col] = ciphertext[index++];
            }
        }
    }

    string plaintext;
    for (int row = 0; row < numRows; ++row) {
        for (int col : key) {
            if (matrix[row][col] != ' ') {
                plaintext += matrix[row][col];
            }
        }
    }

    return plaintext;
}

int main() {
    string plaintext, ciphertext, decryptedText;
    vector<int> key;

    cout << "Enter the text to encrypt (without spaces): ";
    cin >> plaintext;

    cout << "Enter the key (a permutation of numbers representing the column order): ";
    for (int i = 0; i < plaintext.length(); ++i) {
        int col;
        cin >> col;
        key.push_back(col % plaintext.length()); // Ensure key is within bounds
    }

    // Encryption
    ciphertext = encryptColumnTransposition(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decryption
    decryptedText = decryptColumnTransposition(ciphertext, key);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
