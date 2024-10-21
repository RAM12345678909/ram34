#include <iostream>
#include <string>
#include <cmath>
using namespace std;
string round_keys[16];
string pt;

string convertDecimalToBinary(int decimal)
{
string binary;
while(decimal != 0) {
binary = (decimal % 2 == 0 ? "0" : "1") + binary;
decimal = decimal/2;
}
while(binary.length() < 4){
binary = "0" + binary;
}
return binary;
}


int convertBinaryToDecimal(string binary)
{
int decimal = 0;
int counter = 0;
int size = binary.length();
for(int i = size-1; i >= 0; i--)
{
if(binary[i] == '1'){
decimal += pow(2, counter);
}
counter++;
}
return decimal;
}


string shift_left_once(string key_chunk){
string shifted="";
for(int i = 1; i < 28; i++){
shifted += key_chunk[i];
}
shifted += key_chunk[0];
return shifted;
}

string shift_left_twice(string key_chunk){
string shifted="";
for(int i = 0; i < 2; i++){
for(int j = 1; j < 28; j++){
shifted += key_chunk[j];
}
shifted += key_chunk[0];
key_chunk= shifted;
shifted ="";
}
return key_chunk;
}

string Xor(string a, string b){
string result = "";
int size = b.size();
for(int i = 0; i < size; i++){
if(a[i] != b[i]){
result += "1";
}
else{
result += "0";
}
}
return result;
}


void generate_keys(string key){
int pc1[56] = {
57,49,41,33,25,17,9,
1,58,50,42,34,26,18,
10,2,59,51,43,35,27,
19,11,3,60,52,44,36,
63,55,47,39,31,23,15,
7,62,54,46,38,30,22,
14,6,61,53,45,37,29,
21,13,5,28,20,12,4
};

int pc2[48] = {
14,17,11,24,1,5,
3,28,15,6,21,10,
23,19,12,4,26,8,
16,7,27,20,13,2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32
};


string perm_key ="";

for(int i = 0; i < 56; i++){
perm_key+= key[pc1[i]-1];
}

string left= perm_key.substr(0, 28);
string right= perm_key.substr(28, 56);

for(int i=0; i<16; i++){
if(i == 0 || i == 1 || i==8 || i==15 ){
left= shift_left_once(left);
right= shift_left_once(right);
}
else{
left= shift_left_twice(left);
right= shift_left_twice(right);
}

cout<<"Right Key:"<<right<<" "<<"Left Key:"<<left<<endl;

string combined_key = left + right;

string round_key = "";
for(int i = 0; i < 48; i++){
round_key += combined_key[pc2[i]-1];
}
round_keys[i] = round_key;

}

}

string DES(){
int initial_permutation[64] = {
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7
};

int expansion_table[48] = {
32,1,2,3,4,5,4,5,
6,7,8,9,8,9,10,11,
12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,
22,23,24,25,24,25,26,27,
28,29,28,29,30,31,32,1
};

int substition_boxes[64]={

13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11

};

int permutation_tab[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};
int inverse_permutation[64]= {
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};

string perm = "";
for(int i = 0; i < 64; i++){
perm += pt[initial_permutation[i]-1];
}
string left = perm.substr(0, 32);
string right = perm.substr(32, 64);
for(int i=0; i<16; i++) {
string right_expanded = "";
for(int i = 0; i < 48; i++) {
right_expanded += right[expansion_table[i]-1];
};
string xored = Xor(round_keys[i], right_expanded);
string res = "";
for(int i=0;i<8; i++){
string row1= xored.substr(i*6,1) + xored.substr(i*6 + 5,1);
int row = convertBinaryToDecimal(row1);
string col1 = xored.substr(i*6 + 1,1) + xored.substr(i*6 + 2,1) + xored.substr(i*6 + 3,1) + xored.substr(i*6 + 4,1);;
int col = convertBinaryToDecimal(col1);
int val = substition_boxes[i];
res += convertDecimalToBinary(val);
}
string perm2 ="";
for(int i = 0; i < 32; i++){
perm2 += res[permutation_tab[i]-1];
}
xored = Xor(perm2, left);
left = xored;
if(i < 15){
string temp = right;
right = xored;
left = temp;
}
}
string combined_text = left + right;
string ciphertext ="";
for(int i = 0; i < 64; i++){
ciphertext+= combined_text[inverse_permutation[i]-1];
}
return ciphertext;
}

int main(){
string key;
cout<<"Enter Key:"<<endl;
cin>>key;
cout<<"Enter Data:"<<endl;
cin>>pt;
generate_keys(key);
string ct= DES();
cout<<"Ciphertext: "<<ct<<endl;
}
