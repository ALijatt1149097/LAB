#include <iostream>
using namespace std;

int main() {
    int arr[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    cout << "Array before deletion: ";
    for (int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    for (int i = 4; i < 9; i++) {
        arr[i] = arr[i + 1];
    }

    cout << "Array after deleting element at index 4: ";
    for (int i = 0; i < 9; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
