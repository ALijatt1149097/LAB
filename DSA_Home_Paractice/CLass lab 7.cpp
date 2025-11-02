#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Function to insert a node at the end of circular linked list
void insertEnd(Node** head, int data) {
    Node* newNode = new Node();
    newNode->data = data;

    // If the list is empty
    if (*head == nullptr) {
        newNode->next = newNode; // Point to itself
        *head = newNode;
        return;
    }

    // Otherwise, find the last node
    Node* temp = *head;
    while (temp->next != *head)
        temp = temp->next;

    // Insert new node after last node
    temp->next = newNode;
    newNode->next = *head;
}

// Function to display the circular linked list
void display(Node* head) {
    if (head == nullptr)
        return;

    Node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);
    cout << endl;
}

// Driver code
int main() {
    Node* head = nullptr;

    insertEnd(&head, 10);
    insertEnd(&head, 20);
    insertEnd(&head, 30);
    insertEnd(&head, 40);

    cout << "Circular Linked List: ";
    display(head);

    return 0;
}
