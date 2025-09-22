#include <iostream>
using namespace std;    

int swap ( int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}       
int main() {
    int x,y;
    int *ptr1 = &x;
    int *ptr2 = &y; 
    *ptr1 = 42;
    *ptr2 = 21;
    swap(ptr1,ptr2);
    cout<<"the value of x after swapping is "<<x<<endl;
    
    cout<<"the value of y after swapping is "<<y<<endl;

    return 0;}