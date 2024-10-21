#include<iostream>
#include<cstdlib>
using namespace std;

main()
{
    int P, G,a,b,x,y,ka, kb;
    cout<<"Enter the value of P : ";
    cin>>P;
    cout<<"Enter the value of G : ";
    cin>>G;

    a = (rand() % 100);
    cout<<"\nPrivate Key for Alice : "<<a<<endl;
    b = (rand() % 100);
    cout<<"Private Key for Bob : "<<b<<endl;

    x = G^a%P;
    y = G^b%P;

    cout<<"\nKeys Generated !!"<<endl;
    cout<<"Keys Exchanged !!!"<<endl;

    ka = y^a%P;
    kb = x^b%P;

    cout<<"Secret Key Generated !!!"<<endl;
    if(ka==kb)
    {
        cout<<"\nGenerated Secret Keys are symmetric"<<endl;
    }
    else
    {
        cout<<"\nGenerated Secret Keys are not Symmetric"<<endl;
    }

    cout<<"\nGenerated Secret Key for Alice : "<<ka<<endl;
    cout<<"Generated Secret Key For Bob : "<<kb<<endl;
}
