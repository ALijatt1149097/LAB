
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    // ----- Step 1: Create initial list of 3 nodes -----
    Node* head = new Node{10, nullptr};
    head->next = new Node{20, nullptr};
    head->next->next = new Node{30, nullptr};

    cout << "Initial list: ";
    for (Node* t = head; t != nullptr; t = t->next)
        cout << t->data << " -> ";
    cout << "NULL\n";

    // ----- Step 2: Insert at the beginning -----
    Node* newNodeBeg = new Node{5, nullptr};
    newNodeBeg->next = head;
    head = newNodeBeg;

    cout << "After inserting 5 at beginning: ";
    for (Node* t = head; t != nullptr; t = t->next)
        cout << t->data << " -> ";
    cout << "NULL\n";

    // ----- Step 3: Insert at the end -----
    Node* newNodeEnd = new Node{40, nullptr};
    Node* temp = head;
    while (temp->next != nullptr) {      // move to the last node
        temp = temp->next;
    }
    temp->next = newNodeEnd;

    cout << "After inserting 40 at end: ";
    for (Node* t = head; t != nullptr; t = t->next)
        cout << t->data << " -> ";
    cout << "NULL\n";

    // ----- Step 4: Insert at a specific index (0-based) -----
    int index = 2;   // change as needed
    int value = 15;

    Node* cur = head;
    for (int i = 0; cur != nullptr && i < index - 1; i++) {
        cur = cur->next;
    }

    if (cur == nullptr) {
        cout << "Index out of range!\n";
    } else {
        Node* newNodeMid = new Node{value, nullptr};
        newNodeMid->next = cur->next;
        cur->next = newNodeMid;
    }

    cout << "After inserting 15 at index 2: ";
    for (Node* t = head; t != nullptr; t = t->next)
        cout << t->data << " -> ";
    cout << "NULL\n";
    }

    return 0;
}
