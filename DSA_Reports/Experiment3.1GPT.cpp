#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    // Create head node with value 10
    Node* head = new Node{10, nullptr};
    Node* tail = head; // keep a tail pointer to append efficiently

    // Append n nodes with value 20
    for (int i = 0; i < n; ++i) {
        Node* node = new Node{20, nullptr};
        tail->next = node;
        tail = node;
    }

    // Print the list
    Node* ptr = head;
    while (ptr != nullptr) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;

    // Optional: free memory
    ptr = head;
    while (ptr != nullptr) {
        Node* tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }

    return 0;
}
