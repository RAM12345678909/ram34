#include<iostream>
using namespace std;


string encrypt(string text, int shift)
{
    string encrypted_text = "";
    for(int i=0;i<text.length();i++)
    {
        if(isupper(text[i]))
            encrypted_text += char(int(text[i] + shift - 65) % 26 + 65);
        else if (islower(text[i]))
            encrypted_text += char(int(text[i] + shift - 97) % 26 + 97);
        else
            encrypted_text += " ";
    }
    return encrypted_text;
}

string decrypt(string text, int shift)
{
    string encrypted_text = "";
    for(int i=0;i<text.length();i++)
    {
        if(isupper(text[i]))
            encrypted_text += char(int(text[i] - shift - 65 + 26) % 26 + 65);
        else if (islower(text[i]))
            encrypted_text += char(int(text[i] - shift - 97 + 26) % 26 + 97);
        else
            encrypted_text += " ";
    }
    return encrypted_text;
}
main()
{
    string text, encrypted_text;
    int shift;

    /*cout<<"Enter text to encrypt : ";
    cin>>text;

    cout<<"Enter shift key : ";
    cin>>shift;

    cout<<"Encrypted text : "<<encrypt(text, shift)<<endl;
    cout<<"Decrypted Text : "<<decrypt(encrypt(text, shift), shift)<<endl;*/

    int c, a, x, y;

    while(c != 3)
    {
        cout<<"\n Enter your Choice : "<<endl;
        cout<<" 1. Encryption \n 2. Decryption \n 3. Exit"<<endl;
        cout<<" :> ";
        cin>>c;

        cout<<"\n Enter your Choice : "<<endl;
        cout<<" 1. Symmetric  \n 2. Asymmetric \n 3. Exit"<<endl;
        cout<<" :> ";
        cin>>x;

        cout<<"\n Enter Algorithm Type : "<<endl;
        cout<<" 1. Ceaser Cipher \n 2. Row-Column Transposition \n 3. Polyalphabetic Cipher \n 4. Exit "<<endl;
        cout<<" :> ";
        cin>>a;

        cout<<"\n Enter Algorithm Type : "<<endl;
        cout<<" 1. Diffie Hellman \n"<<endl;
        cout<<" :> ";
        cin>>y;

        switch(a)
        {
        case 1:
            {
                if(c==1)
                {
                    cout<<"Enter text to encrypt : ";
                    cin>>text;
                    cout<<"Enter shift key : ";
                    cin>>shift;
                    encrypted_text = encrypt(text, shift);
                    cout<<"Encrypted text : "<<encrypted_text<<endl;
                }
                else
                {
                    cout<<"Decrypted Text : "<<decrypt(encrypted_text, shift)<<endl;
                }
                break;
            }
        case 2:
            {
                int rct;
                cout<<"\n Enter Transposition Type : "<<endl;
                cout<<" 1. Row Transposition \n 2. Column Transposition \n 3. Both \n 4. Exit"<<endl;
                cout<<" :> ";
                cin>>rct;

                switch(rct)
                {
                case 1:
                    {
                        break;
                    }
                case 2:
                    {
                        break;
                    }
                case 3:
                    {
                        break;
                    }
                default:
                    {
                        break;
                    }
                }
                break;
            }
            default :
            {
                break;
            }
        }
    }
}
