#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
Node* head = nullptr;
int main() {
    cout << "\nLinked List\n" << endl;

    //  initial list
    Node* first  = new Node();
    Node* second = new Node();
    Node* third  = new Node();

    first->data = 1;     first->next = second;
    second->data = 2;    second->next = third;
    third->data = 3;     third->next = nullptr;
    head = first;
    // insertion at beginning
    {
        Node* newnode = new Node();
        newnode->data = 10;
        newnode->next = head;
        head = newnode;  
    }
    // insertion at end
    {
        Node* newNode = new Node();
        newNode->data = 35;
        newNode->next = nullptr;

        Node* temp1 = head;
        while (temp1->next != nullptr) {
            temp1 = temp1->next;
        }
        temp1->next = newNode; 
    }
    // insertion at index
    {
        int index = 2; 
        int value = 15;
        Node* cur = head;
        for (int i = 0; cur != nullptr && i < index - 1; ++i) {
            cur = cur->next;
        }
            Node* n = new Node();
            n->data = value;
            n->next = cur->next;
            cur->next = n;
    }
    // print linked list
    {
        Node* temp = head;
        int i = 1;
        while (temp != nullptr) {
            cout << "Data of Node " << i << ": " << temp->data << endl;
            cout << "Address of Next Node: " << temp->next << endl;
            temp = temp->next;
            ++i;
        }
    }
    return 0;
}