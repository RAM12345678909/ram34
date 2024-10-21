#include<iostream>
using namespace std;


string encryption(string text,int key){
    string result;

    for(char c:text ){
        if(isalpha(c)){
            char base= islower(c)?'a':'A';
            result+=(c-base+key)%26+base;
        }
        else{
            result+=c;
        }
    }

    return result;

}

string decryption(string text,int key){
    return encryption(text,26-key);
}

int main(){

string input_text;
int key,user_input;

cout<<"****Menu****"<<endl;
cout<<"1.Encryption"<<endl;
cout<<"2.Decryption"<<endl;
cin>>user_input;

cout<<"Enter the Text:"<<endl;
cin>>input_text;

cout<<"Enter the Key:"<<endl;
cin>>key;

switch(user_input){

case 1:
        cout<<"Encrypted Text: "<<encryption(input_text,key)<<endl;
        break;

case 2:
        cout<<"Decryption Text:"<<decryption(input_text,key)<<endl;
        break;

default:
        cout<<"Invalid Input"<<endl;
        break;

}

return 0;
}
