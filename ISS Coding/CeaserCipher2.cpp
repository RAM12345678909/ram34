#include<iostream>
using namespace std;

//Encrypt Function
string encrypt(string text, int shift)
{
    string result = "";

    for (char c : text)
        {
        if (isalpha(c))
        {
            char base = islower(c) ? 'a' : 'A';
            result += (c - base + shift) % 26 + base;
        }
        else
        {
            result += c;
        }
    }
    return result;
}

///Decrypt Function
string decrypt(string text, int shift)
{
    return encrypt(text, 26 - shift);
}

int main(){
string plaintext;
int shift;

cout << "Enter the text to encrypt: "<<endl ;
cin>>plaintext;

cout << "Enter shift value: "<<endl;
cin >> shift;

string ciphertext = encrypt(plaintext, shift);
cout << "Encrypted text: " << ciphertext << endl;

string decryptedText = decrypt(ciphertext, shift);
cout << "Decrypted text: " << decryptedText << endl;

}
