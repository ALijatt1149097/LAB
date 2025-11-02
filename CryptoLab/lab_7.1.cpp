#include <iostream>
#include <bitset>
#include <string>
using namespace std;

// Function to perform polynomial addition in GF(2^n) ~ XOR operation
unsigned int gf_add(unsigned int a, unsigned int b) {
    return a ^ b;// returns the value of A xor B 
}

// Function to display polynomial representation
void display_polynomial(unsigned int poly, int degree)// to display the polynomial/ given binary number in the human readable from 
 {
    bool firstTerm = true; // to determine if it is the first term or not so that we can ensure proper formatting

    for (int i = degree; i >= 0; i--)// loop from the highest degree to the lowest 
     {
        if (poly & (1 << i))// if the polynomail exists and the power of each polynomial variable is greater than one 
         {
            if (!firstTerm) // if its not the first term we need to addd a plus sign before the term 
            {
                cout << " + ";
            }
            if (i == 0) { // if the power is zero just print 1
                cout << "1";
            } else if (i == 1) {  // if the power is one just print x
                cout << "x";
            } else { //if the power is more than 1 than print x^i where i is the power of the variable 
                cout << "x^" << i;
            }
            firstTerm = false; //change the firstterm bool to falsse aafter the first value is printec
        }
    }

    if (firstTerm)  //if it sthe first term than print 0;
     {
        cout << "0";
    }
}

int main() {
    // GF(2^4) polynomials
    unsigned int a = 0b1011;   // x^3 + x + 1 -----4 bit ----  here 0b represents that the following number is a binary : likewise 0x represents the following number is a hex 
    unsigned int b = 0b1101;   // x^3 + x^2 + 1

    // GF(2^8) polynomials
    unsigned int c = 0b101010001; // x^7 + x^6 + x^4 + 1-----8 bit ----  here 0b represents that the following number is a binary : likewise 0x represents the following number is a hex 
    unsigned int d = 0b10110001;  // x^7 + x^5 + x^3 + 1

    // Addition in GF(2^4)
    int sum_GF4 = gf_add(a, b); //will return the value of A xor B (a and b are predeclared 4 bit binary ) and stores the result in sum_GF4

    // Display results for GF(2^4)
    cout << "Polynomial a in GF(2^4): ";
    display_polynomial(a, 3); // will display the polynomial representation of a (which is 4 bit binary ) with degree 3
    cout << "  (Binary: " << bitset<4>(a) << ")\n"; // will display the binary representation of a using bitset of size 4

    cout << "Polynomial b in GF(2^4): ";
    display_polynomial(b, 3);// will display the polynomial representation of b (which is 4 bit binary ) with degree 3
    cout << "  (Binary: " << bitset<4>(b) << ")\n";// will display the binary representation of b using bitset of size 4


    cout << "Sum in GF(2^4): ";
    display_polynomial(sum_GF4, 3);// will display the polynomial representation of sum_GF4 (which is 4 bit binary having the value of A xor B ) with degree 3
    cout << "  (Binary: " << bitset<4>(sum_GF4) << ")\n\n";// will display the binary representation of sum_GF4 using bitset of size 4

    // Addition in GF(2^8)
    int sum_GF8 = gf_add(c, d);//will return the value of C xor D (c and d are predeclared 8 bit binary ) and stores the result in sum_GF8

    // Display results for GF(2^8)
    cout << "Polynomial c in GF(2^8): ";
    display_polynomial(c, 7);// will display the polynomial representation of c (which is 8 bit binary ) with degree 7
    cout << "  (Binary: " << bitset<8>(c) << ")\n";// will display the binary representation of c using bitset of size 8

    cout << "Polynomial d in GF(2^8): ";
    display_polynomial(d, 7);// will display the polynomial representation of d (which is 8 bit binary ) with degree 7
    cout << "  (Binary: " << bitset<8>(d) << ")\n";// will display the binary representation of d using bitset of size 8

    cout << "Sum in GF(2^8): ";
    display_polynomial(sum_GF8, 7);// will display the polynomial representation of sum_GF8 (which is 8 bit binary having the value of C xor D ) with degree 7
    cout << "  (Binary: " << bitset<8>(sum_GF8) << ")\n\n";// will display the binary representation of sum_GF8 using bitset of size 8

    cout << "=== Code Execution Successful ===" << endl;
    return 0;
}
