#include <iostream>
using namespace std;


int swap (int &x, int &y )
{
    int temp = x;
    x = y;
    y = temp;
    return 0;
}
int main () {
    int a, b ; 
    cout<<"Enter the two Values"<<endl;
    cin>>a>>b;
    swap (a,b);
    cout<<"After swapping the numbers are "<<a<<" and "<<b<<endl;
    return 0;
}