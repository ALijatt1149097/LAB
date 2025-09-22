#include <iostream>
#include <string>
using namespace std;

int main() {
    string a;
    cout << "Enter a string: ";
    getline(cin, a);
    string *ptr = &a;
    int n = (*ptr).length();
    for (int i = 0; i < n / 2; i++) {
        char temp = (*ptr)[n - 1 - i];
        (*ptr)[n - 1 - i] = (*ptr)[i];
        (*ptr)[i] = temp;
    }
    cout << "Reversed string: " << *ptr << endl;
    return 0;
}
