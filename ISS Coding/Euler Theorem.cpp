#include<iostream>
#include<math.h>
#include<string>
using namespace std;

int gcd(int num1,int num2){
    int gcd;
for(int i=1;i<=num1;i++){
    if(num1%i==0 && num2%i==0){
        gcd=i;
    }
 }
 return gcd;
}

int main(){

int p,q;

cout<<"Enter 1st Prime Number:"<<endl;
cin>>p;

cout<<"Enter 2nd Prime Number:"<<endl;
cin>>q;

int n=p*q;
int fiofn=(p-1)*(q-1);

cout<<"Fi of N:"<<fiofn<<endl;

int e,i=2;

while(gcd(i,fiofn)!=1){
    i++;
}
e=i;

int k = 2;
double d = (1 + (k * fiofn)) / e;

string me;
cout<<"Enter the Message:"<<endl;
cin>>me;
double msg = me.length();

printf("Message data = %lf", msg);

double c = pow(msg, e);
c = fmod(c, n);
printf("\nEncrypted data = %lf", c);

double m = pow(c, d);
m = fmod(m, n);
printf("\nOriginal Message Sent = %lf", m);

}
