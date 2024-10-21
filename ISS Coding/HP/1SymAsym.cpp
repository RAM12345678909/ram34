#include<conio.h>
#include<stdio.h>
#include<vector>
#include<iostream>
#include<math.h>
using namespace std;

string encryptedText(string plainText, int shiftValue) {
    string cipherText;
    char base, encryptedChar;

    // Getting word one by one from text
    for (char ch : plainText) {
        // Checking if text is character
        if (isalpha(ch)) {
            // Checking if character is lowercase or uppercase
            base = (isupper(ch)) ? 'A' : 'a';

            // Applying formula for encryption
            encryptedChar = ((ch - base + shiftValue) % 26) + base;

            cipherText += encryptedChar;
        } else {
            cipherText += ch;
        }
    }

    return cipherText;
}

string vigenereEncrypt(string plaintext, string key) {
    string encryptedText = "";
    for (size_t i = 0; i < plaintext.length(); ++i) {
        char plainChar = plaintext[i];
        char keyChar = key[i % key.length()];

        if (isalpha(plainChar)) {
            char base = isupper(plainChar) ? 'A' : 'a';
            char encryptedChar = ((plainChar - base + keyChar - 'A') % 26) + base;
            encryptedText += encryptedChar;
        } else {
            encryptedText += plainChar; // Keep non-alphabetic characters unchanged
        }
    }
    return encryptedText;
}

string vigenereDecrypt(string ciphertext, string key) {
    string decryptedText = "";
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char cipherChar = ciphertext[i];
        char keyChar = key[i % key.length()];

        if (isalpha(cipherChar)) {
            char base = isupper(cipherChar) ? 'A' : 'a';
            char decryptedChar = ((cipherChar - base - (keyChar - 'A') + 26) % 26) + base;
            decryptedText += decryptedChar;
        } else {
            decryptedText += cipherChar; // Keep non-alphabetic characters unchanged
        }
    }
    return decryptedText;
}

string encrypt(string message, int rows, int cols) {
    // Determine the number of padding characters needed
    int extraChars = rows * cols - message.length();
    if (extraChars > 0) {
        message.append(extraChars, ' ');
    }

    // Create the matrix
    vector<vector<char>> matrix(rows, vector<char>(cols));
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = message[index++];
        }
    }

    // Print the matrix
    cout << "Original matrix: " << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Transpose the matrix
    vector<vector<char>> transposed(cols, vector<char>(rows));
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            transposed[i][j] = matrix[j][i];
        }
    }

    // Print the transposed matrix
    cout << "Transposed matrix: " << endl;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }

    // Read the cipher message from the transposed matrix
    string cipherMessage;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            cipherMessage.push_back(transposed[i][j]);
        }
    }

    return cipherMessage;
}

string decrypt(string cipherMessage, int rows, int cols) {
    // Determine the number of padding characters
    int extraChars = rows * cols - cipherMessage.length();
    if (extraChars > 0) {
        cipherMessage.append(extraChars, ' ');
    }

    // Create the matrix
    vector<vector<char>> matrix(cols, vector<char>(rows));
    int index = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            matrix[i][j] = cipherMessage[index++];
        }
    }

    // Transpose the matrix
    vector<vector<char>> transposed(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transposed[i][j] = matrix[j][i];
        }
    }

    // Read the original message from the transposed matrix
    string originalMessage;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            originalMessage.push_back(transposed[i][j]);
        }
    }

    return originalMessage;
}

int main()
{
    int s,in,out;

    cout<<"1. Symmetric Key Algorithms"<<endl;
    cout<<"2. Asymmetric Key Algorithms"<<endl;
    cin>>s;

    if(s==1)
    {
        cout<<"1. Caeser Cipher"<<endl;
        cout<<"2. Polyalphabetic Cipher"<<endl;
        cout<<"3. Row/Column Transposition"<<endl;
        cin>>in;

        if(in==1)
        {
            string plainText, cipherText;
            int shiftValue;

            cout << "Enter the plain text: ";
            cin >> plainText;

            cout << "Enter shift value: ";
            cin >> shiftValue;

            cipherText = encryptedText(plainText, shiftValue);

            cout << "Encrypted text: " << cipherText;
        }

        else if(in==2)
        {
            string message = "HELLO";
            string key = "KEY";

            string encryptedMessage = vigenereEncrypt(message, key);
            cout << "Encrypted message: " << encryptedMessage << endl;

            string decryptedMessage = vigenereDecrypt(encryptedMessage, key);
            cout << "Decrypted message: " << decryptedMessage << endl;

            return 0;
        }
        else
        {
            string message = "HELLO WORLD";
            int rows = 4;
            int cols = 3;

            cout << "Original message: " << message << endl;

            string cipherMessage = encrypt(message, rows, cols);
            cout << "Cipher message: " << cipherMessage << endl;

            string originalMessage = decrypt(cipherMessage, rows, cols);
            cout << "Decrypted message: " << originalMessage << endl;

            return 0;
        }
    }
    else if(s==2)
    {
        int a;
        cout<<"Diffie Hellman Key Exchange"<<endl;
        cout<<"Do you want to continue, Further is sample output"<<endl;
        cin>>a;
        if(a==1)
        {
        long long int g=3;
        long long int N=17;
        long long int a=15, b=13;
        long long int pa,pb,an,pn, FA1,FB1,anf,pnf;

        cout<<"Private key of Alice = "<<a<<endl;
        cout<<"Private key of Bob = "<<b<<endl;
        cout<<"Generator value = "<<g<<endl;

        pa = (long long int)pow(g,a);
        pb = (long long int)pow(g,b);

        an = pa % N;
        pn = pb % N;

        cout<<"Alice (Ga) = "<<an<<endl;
        cout<<"Bob (Gb) = "<<pn<<endl;

        FA1 = (long long int)pow(pn,a);
        FB1 = (long long int)pow(an,b);

        cout<<"After exchange the value of ALICE = "<<pn<<endl;
        cout<<"After exchange the value of ALICE = "<<an<<endl;

        anf= FA1 % N;
        pnf= FB1 % N;

        cout<<"Alice final output = "<<anf<<endl;
        cout<<"Bob final output = "<<pnf<<endl;
        }
        else
        {
            cout<<"Succesfully exited Diffie hellman"<<endl;
        }

    }
}
