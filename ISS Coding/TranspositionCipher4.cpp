#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


string rowTranspositionEncrypt(string plaintext, int numRows) {
    string ciphertext;
    int len = plaintext.length();

    int numCols = (len + numRows - 1) / numRows;

    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows && index < len; row++) {
            grid[row][col] = plaintext[index++];
        }
    }

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            ciphertext += grid[row][col];
        }
    }

    return ciphertext;
}

string rowTranspositionDecrypt(string ciphertext, int numRows) {
    string plaintext;
    int len = ciphertext.length();

    int numCols = (len + numRows - 1) / numRows;

    vector<vector<char>> grid(numRows, vector<char>(numCols, ' '));

    int index = 0;
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols && index < len; col++) {
            grid[row][col] = ciphertext[index++];
        }
    }

    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {
            plaintext += grid[row][col];
        }
    }

    return plaintext;
}

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


string encryptRowColumnTransposition(const string& plaintext, const string& key) {
    int keyLength = key.length();
    int numRows = (plaintext.length() + keyLength - 1) / keyLength;

    vector<vector<char>> matrix(numRows, vector<char>(keyLength, ' '));

    int index = 0;
    for (int col = 0; col < keyLength; ++col) {
        for (int row = 0; row < numRows; ++row) {
            if (index < plaintext.length()) {
                matrix[row][col] = plaintext[index++];
            }
        }
    }

    string ciphertext;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < keyLength; ++col) {
            if (matrix[row][col] != ' ') {
                ciphertext += matrix[row][col];
            }
        }
    }

    return ciphertext;
}

// Function to perform row-column transposition decryption
string decryptRowColumnTransposition(const string& ciphertext, const string& key) {
    int keyLength = key.length();
    int numRows = (ciphertext.length() + keyLength - 1) / keyLength;

    vector<vector<char>> matrix(numRows, vector<char>(keyLength, ' '));

    int index = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < keyLength; ++col) {
            if (index < ciphertext.length()) {
                matrix[row][col] = ciphertext[index++];
            }
        }
    }

    string plaintext;
    for (int col = 0; col < keyLength; ++col) {
        for (int row = 0; row < numRows; ++row) {
            if (matrix[row][col] != ' ') {
                plaintext += matrix[row][col];
            }
        }
    }

    return plaintext;
}

int main() {
    int choice;
    string text,plaintext,key, ciphertext, decryptedText;

    cout << "Choose a transposition technique:" << endl;
    cout << "1. Row Transposition" << endl;
    cout << "2. Column Transposition" << endl;
    cout << "3. Row-Column Transposition" << endl;

    cin >> choice;

    switch (choice) {
    case 1:{

            cout << "Enter text to encrypt: ";
            cin.ignore();
            getline(cin, text);

            cout << "Enter the number of rows: ";
            int numRows;
            cin >> numRows;

            string encryptedText = rowTranspositionEncrypt(text, numRows);
            cout << "Encrypted text: " << encryptedText << endl;

            string decryptedText = rowTranspositionDecrypt(encryptedText, numRows);
            cout << "Decrypted text: " << decryptedText << endl;
            break;
    }
    case 2: {

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
        break;
    }

    case 3:{

    cout << "Enter the text to encrypt: ";
    cin>>plaintext;

    cout << "Enter the key (a permutation of numbers or characters representing the column order): ";
    cin>>key;

    // Encryption
    ciphertext = encryptRowColumnTransposition(plaintext, key);
    cout << "Encrypted text: " << ciphertext << endl;

    // Decryption
    decryptedText = decryptRowColumnTransposition(ciphertext, key);
    cout << "Decrypted text: " << decryptedText << endl;
    break;
    }


        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    return 0;
}
