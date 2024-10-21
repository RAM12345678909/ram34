#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Caesar Cipher
//Encryption
string enCaesarCipher(string text, int k_shift) {
    string res = "";
    for(int i = 0; i < text.length(); i++) {
        if(isupper(text[i])) {
            res += char(int(text[i] + k_shift - 65) % 26 + 65);
        } else if(islower(text[i])) {
            res += char(int(text[i] + k_shift - 97) % 26 + 97);
        } else {
            res += text[i];
        }
    }
    return res;
}

//Decryption
string deCaesarCipher(string text, int k_shift) {
    return enCaesarCipher(text, 26 - k_shift); // Decryption is just the reverse of encryption
}

//Main Function for Ceasar Cipher
void ceasarCipher() {
    string text, enText;
    int k_shift, choice3;

    cout << "Enter you text" << endl;
    cin.ignore();
    getline(cin, text);

    cout << "Enter the shift value" << endl;
    cin >> k_shift;

    enText = enCaesarCipher(text, k_shift);
    cout << "Encrypted Text: " << enText << endl;

    do {
        cout << " *** Sub Menu *** " << endl;
        cout << "1. Decrypt the encrypted text" << endl;
        cout << "2. Decrypt a new text" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice" << endl;
        cin >> choice3;

        switch(choice3) {
            case 1:
                cout << "Decrypted Text: " << deCaesarCipher(enText, k_shift) << endl;
                break;
            case 2:
                cout << "Enter the text to decrypt :" << endl;
                cin.ignore();
                getline(cin, text);
                cout << "Decrypted Text: " << deCaesarCipher(text, k_shift) << endl;
                break;
            case 3:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid Choice" << endl;
        }
    } while(choice3 != 3);
}

// Transpositional Matrix
//Row Transposition
vector<vector<char>>formMatrixRow(const string& text){
    vector<vector<char>> matrix;
    vector<char>row;
    for (char ch: text)
    {
        if(ch == ' ')
        {
            matrix.push_back(row);
            row.clear();
        }
        else{
            row.push_back(ch);
        }
    }
    matrix.push_back(row);
    return matrix;
}

void printMatrix(const vector<vector<char>>& matrix){
    for (const auto& row:matrix) {
        for (char ch : row) {
            cout<< ch << " ";
        }
        cout<<endl;
    }
}

int findLongestWordLength(const vector<vector<char>>& matrix) {
    int maxLength = 0;
    for (const auto& row : matrix) {
        maxLength = max(maxLength, static_cast<int>(row.size()));
    }
    return maxLength;
}

// Fill empty spaces with special characters
void fillMatrix(vector<vector<char>>& matrix, int maxLength) {
    for (auto& row : matrix) {
        while (row.size() < maxLength) {
            row.push_back('*');
        }
    }
}

// Shifting.... characters
void shiftMatrix(vector<vector<char>>& matrix, int shiftValue) {
    for (auto& row : matrix) {
        std::rotate(row.rbegin(), row.rbegin() + (shiftValue % row.size()), row.rend());
    }
}

void rowTransposition()
{
    string text;
    cout << "Enter the text: ";
    cin.ignore();
    getline(cin, text);

    auto matrix = formMatrixRow(text);
    int maxLength = findLongestWordLength(matrix);
    fillMatrix(matrix, maxLength);

    cout << "Matrix with filled characters:\n";
    printMatrix(matrix);

    int k_shift;
    cout << "Enter shift value: ";
    cin >> k_shift;

    shiftMatrix(matrix, k_shift);
    cout << "Shifted Matrix:\n";
    printMatrix(matrix);
}

vector<vector<char>> formMatrixColumn(const string& text) {
    vector<vector<char>> matrix;
    vector<string> words;

    size_t start = 0, end;
    while ((end = text.find(' ', start)) != string::npos) {
        words.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    words.push_back(text.substr(start));

    size_t maxLength = 0;
    for (const auto& word : words) {
        maxLength = max(maxLength, word.length());
    }

    matrix.resize(maxLength, vector<char>(words.size(), '*'));
    for (size_t i = 0; i < words.size(); ++i) {
        for (size_t j = 0; j < words[i].size(); ++j) {
            matrix[j][i] = words[i][j];
        }
    }

    return matrix;
}

void printMatrixColumn(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

void shiftColumn(vector<vector<char>>& matrix, int col, int k_shift) {
    if (matrix.empty()) return;
    size_t rows = matrix.size();
    std::rotate(matrix.begin(), matrix.begin() + ((rows - k_shift) % rows), matrix.end());
}

void columnTransposition() {
    string text;
    cout << "Enter the text: ";
    cin.ignore();
    getline(cin, text);

    auto matrix = formMatrixColumn(text);
    cout << "Matrix:\n";
    printMatrixColumn(matrix);

    int k_shift;
    cout << "Enter the shift value: ";
    cin >> k_shift;

    for (size_t i = 0; i < matrix[0].size(); ++i) {
        shiftColumn(matrix, i, k_shift);
    }

    cout << "Matrix after column-wise shifting:\n";
    printMatrixColumn(matrix);
}

void displayMatrix(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char ch : row) {
            cout << ch << " ";
        }
        cout << endl;
    }
}

void shiftMatrixRow1(vector<vector<char>>& matrix, int k_shift) {
    for (auto& row : matrix) {
        rotate(row.rbegin(), row.rbegin() + k_shift % row.size(), row.rend());
    }
}

void convertToColumnMatrix(vector<vector<char>>& matrix) {
    if (matrix.empty()) return;

    vector<vector<char>> columnMatrix(matrix[0].size(), vector<char>(matrix.size(), '*'));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            columnMatrix[j][i] = matrix[i][j];
        }
    }
    matrix = move(columnMatrix);
}

void shiftMatrixColumn1(vector<vector<char>>& matrix, int k_shift) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();

    for (int col = 0; col < numCols; ++col) {
        for (int step = 0; step < k_shift % numRows; ++step) {
            char temp = matrix[numRows - 1][col];
            for (int row = numRows - 1; row > 0; --row) {
                matrix[row][col] = matrix[row - 1][col];
            }
            matrix[0][col] = temp;
        }
    }
}

void rowColumnTransposition() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    string text;
    cout << "Enter the text: ";
    getline(cin, text);

    // Find the longest word length
    size_t maxLen = 0;
    string word;
    istringstream stream(text);
    while (stream >> word) {
        maxLen = max(maxLen, word.length());
    }

    // Build the matrix
    vector<vector<char>> matrix;
    istringstream textStream(text);
    while (textStream >> word) {
        vector<char> row(word.begin(), word.end());
        row.resize(maxLen, '*'); // Pad with '*' if needed
        matrix.push_back(row);
    }

    // Display original matrix
    cout << "Original Matrix:\n";
    displayMatrix(matrix);

    // Row Transposition
    int shiftRow;
    cout << "Enter the row shift value: ";
    cin >> shiftRow;
    shiftMatrixRow1(matrix, shiftRow);

    // Display matrix after row transposition
    cout << "Matrix after Row Transposition:\n";
    displayMatrix(matrix);

    // Convert to Column Matrix and Display
    convertToColumnMatrix(matrix);
    cout << "Matrix after converting to Column Matrix:\n";
    displayMatrix(matrix);

    // Column Transposition
    int shiftColumn;
    cout << "Enter the column shift value: ";
    cin >> shiftColumn;
    shiftMatrixColumn1(matrix, shiftColumn);

    // Display final matrix after row and column transposition
    cout << "Final Matrix after Row and Column Transposition:\n";
    displayMatrix(matrix);
}

void transpositionalMatrix() {
    int choice;
    do {
        cout << "Sub-Menu" << endl;
        cout << "1. Row" << endl;
        cout << "2. Column" << endl;
        cout << "3. Row + Column" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                rowTransposition();
                break;
            }
            case 2: {
                columnTransposition();
                break;
            }
            case 3: {
                rowColumnTransposition();
                break;
            }
            case 4:
                cout << "Exiting" << endl;
                break;
            default:
                cout << "Invalid Option. Please choose a correct option from 1 to 4" << endl;
        }
    }while(choice != 4);
}

void diffieHellman()
{
    int p, g, a, b;
    cout << "Enter a prime number (p): ";
    cin >> p;
    cout << "Enter a primitive root of p (g): ";
    cin >> g;
    cout << "Enter a secret key for Alice (a): ";
    cin >> a;
    cout << "Enter a secret key for Bob (b): ";
    cin >> b;

    int A = 1, B = 1;
    for (int i = 0; i < a; i++)
        {
            A = (A * g) % p;
        }
    cout<<"Value of x is "<<A<<endl;
    for (int i = 0; i < b; i++)
        {
            B = (B * g) % p;
        }
    cout<<"Value of y is "<<B<<endl;

    int secret_key_A = 1, secret_key_B = 1;

    for (int i = 0; i < a; i++)
        {
            secret_key_A = (secret_key_A * B) % p;
        }
    for (int i = 0; i < b; i++)
        {
            secret_key_B = (secret_key_B * A) % p;
        }
    cout << "Alice's secret key: " << secret_key_A << endl;
    cout << "Bob's secret key: " << secret_key_B << endl;
}

// Function to encrypt a string using a polyalphabetic cipher
string polyalphabeticEncrypt(const string& plaintext, const string& key) {
    string ciphertext;
    int keyLength = key.length();

    for (size_t i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            char baseChar = isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar = key[i % keyLength];

            // Calculate key shift (starting from 1)
            int keyShift = (toupper(keyChar) - 'A' + 1);

            // Encrypt character
            char encryptedChar = baseChar + (plaintext[i] - baseChar + keyShift) % 26;
            ciphertext += encryptedChar;

            int letterPosition = toupper(plaintext[i]) - 'A' + 1;
            cout << "Value of " << plaintext[i] << ": " << letterPosition << ", ";
            cout << "Key value: " << keyShift << ", ";
            cout << "Encrypted value: " << (encryptedChar - baseChar + 1) % 26 << endl;
        } else {
            ciphertext += plaintext[i];
        }
    }

    return ciphertext;
}

string polyalphabeticDecrypt(const string& ciphertext, const string& key) {
    string plaintext;
    int keyLength = key.length();

    for (size_t i = 0; i < ciphertext.length(); i++) {
        if (isalpha(ciphertext[i])) {
            char baseChar = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyChar = key[i % keyLength];

            // Calculate key shift (starting from 1)
            int keyShift = (toupper(keyChar) - 'A' + 1);

            // Decrypt character
            char decryptedChar = baseChar + (ciphertext[i] - baseChar - keyShift + 26) % 26;
            plaintext += decryptedChar;
        } else {
            plaintext += ciphertext[i];
        }
    }

    return plaintext;
}

int main() {
    int choice1,choice2,choice3;
    do{
        cout<<"1. Symmetric "<<endl;
        cout<<"2. Asymmetric "<<endl;
        cout<<"3. Exit"<<endl;
        cin>> choice2;

        switch(choice2)
        {
        case 1:
            {
                do {
                    cout << "1. Ceasor Cipher" << endl;
                    cout << "2. Transpositional Matrix" << endl;
                    cout << "3. Polyalphabetic " <<endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice1;

                    switch(choice1) {
                        case 1:
                            ceasarCipher();
                            break;
                        case 2:
                            transpositionalMatrix();
                            break;
                        case 3:
                            {
                                string text, key, encrypted, decrypted;

                                // Clear input buffer
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Enter the text: ";
                                getline(cin, text);

                                cout << "Enter the key: ";
                                getline(cin, key);

                                encrypted = polyalphabeticEncrypt(text, key);
                                cout << "Encrypted Text: " << encrypted << endl;

                                decrypted = polyalphabeticDecrypt(encrypted, key);
                                cout << "Decrypted Text: " << decrypted << endl;

                                break;
                            }
                        case 4:
                            cout << "Exiting" << endl;
                            break;
                        default:
                            cout << "Invalid Option. Please select a valid option from 1 to 3" << endl;
                    }
            } while(choice1 != 4);
            break;
         }
       case 2:
           {
               do{
                cout<<"1. Diffie hellman"<<endl;
                cout<<"2. Exit"<<endl;
                cout<<"Enter your choice"<<endl;
                cin>>choice3;

                switch(choice3)
                {
                    case 1:
                        diffieHellman();
                        break;
                    case 2:
                            cout << "Exiting to Asymmetric menu" << endl;
                            break;
                    default:
                            cout << "Invalid Option. Please select a valid option from 1 to 2" << endl;
                    }
                } while (choice3 != 2);
                break; // Break to exit the inner loop and go back to the Asymmetric menu
            }
        case 3:
            {
            cout<<"Exiting"<<endl;
            break;
        default:
                cout << "Invalid Option. Please select a valid option from 1 to 3";
            }
        }
    }while(choice2!=3);
}
