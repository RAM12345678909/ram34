#include<iostream>
using namespace std;

 int main(){

 int num1, num2, gcd;

 cout<<"Enter the number1:"<<endl;
 cin>>num1;

 cout<<"Enter the number2:"<<endl;
 cin>>num2;

 for(int i=1;i<=num1;i++){
    if(num1%i==0 && num2%i==0){
        gcd=i;
    }
 }

 cout<<"GCD of "<<num1<<" and "<<num2<<" is "<<gcd<<endl;

 }
