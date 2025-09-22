#include <iostream>
using namespace std;

int main() {
int x;
int *ptr = &x;
*ptr = 42; 
cout<<"the value of x is "<<x<<endl;    
cout<<"the address of x is "<<&x<<endl;
cout << "the value of ptr is "<<*ptr<<endl;
cout << "the address of ptr is "<<ptr<<endl;
*ptr = *ptr + 1;
cout<<" the value of x after the increment is "<< x<<endl;
cout << "the value of ptr after the increment is "<<*ptr<<endl;
return 0;
}