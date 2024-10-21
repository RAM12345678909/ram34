#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string transposeRows(string text, int rows, int cols) {
 string transposedText = "";
 for (int col = 0; col < cols; ++col) {
 for (int row = 0; row < rows; ++row) {
 transposedText += text[row * cols + col];
 }
 }
 return transposedText;
}
string transposeColumns(string text, int rows, int cols) {
 string transposedText = "";
 for (int row = 0; row < rows; ++row) {
 for (int col = 0; col < cols; ++col) {
 transposedText += text[row + col * rows];
 }
 }
 return transposedText;
}

string transposeBoth(string text, int rows, int cols) {
 string transposedText = transposeRows(text, rows, cols);
 return transposeColumns(transposedText, cols, rows);
}

int main(){

 int choice;
 string text;
 int shift;

cout << "Enter the text to transpose: ";
 getline(cin, text);
 int transposeChoice;
 int rows, cols;
 cout << "Choose transpose method:\n";
 cout << "1. Transpose with Rows\n";
 cout << "2. Transpose with Columns\n";
 cout << "3. Transpose with Both Rows and Columns\n";
 cout << "Enter your choice: ";
 cin >> transposeChoice;
 cin.ignore();
 switch (transposeChoice) {
 case 1:
 cout << "Enter the number of rows: ";
 cin >> rows;
 cout << "Enter the number of columns: ";
 cin >> cols;
 text = transposeRows(text, rows, cols);
 cout << "Transposed text with rows: " << text << endl;
 break;
 case 2:
 cout << "Enter the number of rows: ";
 cin >> rows;
 cout << "Enter the number of columns: ";
 cin >> cols;
 text = transposeColumns(text, rows, cols);
 cout << "Transposed text with columns: " << text << endl;
 break;
 case 3:
 cout << "Enter the number of rows: ";
 cin >> rows;
 cout << "Enter the number of columns: ";
 cin >> cols;
 text = transposeBoth(text, rows, cols);
 cout << "Transposed text with both rows and columns: " << text << endl;
 break;
 default:
 cout << "Invalid choice. Please enter a valid option.\n";
 }


}
