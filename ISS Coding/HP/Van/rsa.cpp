#include<iostream>
#include<cmath>
#include<cstdlib>
#include <algorithm>
using namespace std;

main()
{
    int p, q, n, phiofn, e, d, k;
    string original_text, decrypted_text;
    double msg;
    k = 2;
    p = 3;
    q = 7;

    n = p*q;
    phiofn = (p-1)*(q-1);

    for(int i=2;i<phiofn;i++)
    {
        if((__gcd(i, phiofn)) == 1)
        {
            e=i;
            break;
        }
    }
    //cout<<"E : "<<e<<endl;
    d = (k*phiofn+1)/e;
    //cout<<"N : "<<n<<endl;
    //cout<<"D : "<<d<<endl;
    //cout<<"Phi Of N : "<<phiofn<<endl;

    /*cout<<"Enter number : ";
    cin>>msg;

    double c = pow(msg, e);
    c = fmod(c,n);
    cout<<"C : "<<c<<endl;

    double m = pow(c,d);
    m = fmod(m, n);
    cout<<"M : "<<m<<endl;*/
    cout<<"Enter Text to Encode : ";
    cin>>original_text;
    int rsa[original_text.length()], decrypted[original_text.length()];
    for(int i=0;i<original_text.length();i++)
    {
        int a = int(original_text[i]);

        if (a >= 65 && a <= 90) // uppercase letters
            a = a - 65;
        else if (a >= 97 && a <= 122) // lowercase letters
            a = a - 97;
        else // invalid input
        {
            cout << "Invalid input. Only alphabetic characters are allowed." << endl;
            exit(1);
        }
        //cout<<"A : "<<a<<endl;
        int b = pow(a, e);
        //cout<<"B : "<<b<<endl;
        rsa[i] = fmod(b,n);
        //cout<<"B%N : "<<b%n<<endl;
    }

    for(int i=0;i<original_text.length();i++)
    {
        cout<<rsa[i]<<endl;
    }

    for(int i=0;i<original_text.length();i++)
    {
        int a = pow(rsa[i], d);
        a = fmod(a,n);
        a = a+65;
        //int b = fmod(a,n);
        decrypted_text += char(a);
    }
    cout<<"Decrypted Text : "<<decrypted_text<<endl;
}
