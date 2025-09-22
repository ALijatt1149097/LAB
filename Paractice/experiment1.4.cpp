#include <iostream>
using namespace std;

int main ()
{

    cout<<"enter the number of elements"<<endl;
    int n;
    cin >> n;
    int *x = new int[n];
    int sum = 0;
    for (int i=0; i<n; i++)
    {
        cout<<"enter the "<<i<<" value"<<endl;
        cin >>x[i];
        sum = sum + x[i];
    }
cout<<"the sum is "<<sum<<endl; 
    int Avg = sum / n;
cout<< "the average is "<<Avg<<endl;
    return 0;
}