#include<iostream>
using namespace std;

int euler(int n){

    int count=n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            count =count -count/i;

            while(n%i==0){
                n=n/i;
            }
        }
    }

    if(n>1){
        count=count-count/n;
    }

}

int main(){
    int n;
    cout<<"Enter the Number:"<<endl;
    cin>>n;
    cout<<euler(n)<<endl;
}
