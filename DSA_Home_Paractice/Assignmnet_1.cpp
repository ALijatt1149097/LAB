#include <iostream>
using namespace std;

int main() {
    int Ali[6] = {10, 20, 30, 40, 50};

    cout << "Array before insertion: ";
    for (int i = 0; i < 5; i++) {
        cout << Ali[i] << " ";
    }
    cout << endl;

    for (int i = 5; i > 2; i--) {
        Ali[i] = Ali[i - 1];
    }

    Ali[2] = 15;

    cout << "Array after inserting 15 at index 2: ";
    for (int i = 0; i < 6; i++) {
        cout << Ali[i] << " ";
    }
    cout << endl;

    return 0;
}
