#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string encrypt(string plaintext, int numRows) {
    int numCols = (plaintext.length() + numRows - 1) / numRows;

    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {
            if (index < plaintext.length()) {
                grid[row][col] = plaintext[index];
                index++;
            }
        }
    }

    string ciphertext = "";
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            ciphertext += grid[row][col];
        }
    }

    return ciphertext;
}

string decrypt(string ciphertext, int numRows) {
    int numCols = (ciphertext.length() + numRows - 1) / numRows;

    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (index < ciphertext.length()) {
                grid[row][col] = ciphertext[index];
                index++;
            }
        }
    }

    string decryptedText = "";
    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {
            decryptedText += grid[row][col];
        }
    }

    return decryptedText;
}

int main() {
    string plaintext, ciphertext, decryptedText;
    int numRows;

    cout << "Enter the text to encrypt: ";
    getline(cin, plaintext);

    cout << "Enter the number of rows: ";
    cin >> numRows;

    ciphertext = encrypt(plaintext, numRows);
    cout << "Encrypted text: " << ciphertext << endl;

    decryptedText = decrypt(ciphertext, numRows);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
