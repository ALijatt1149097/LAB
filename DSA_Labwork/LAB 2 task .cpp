#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
};
void iAB(Node*& head, int value) {
    Node* newNode = new Node;   
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}
void iAE(Node*& head, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    Node* temp = head;
        while (temp->next) {       
            temp = temp->next;
        }
        temp->next = newNode;}
        
void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->data << endl;
        temp = temp->next;
    }
}
int main() {
    Node* head = nullptr;

    Node* first  = new Node;
    Node* second = new Node;
    Node* third  = new Node;

    first->data = 1;  first->next = second;
    second->data = 2; second->next = third;
    third->data = 3;  third->next = nullptr;
    head = first;
    iAB(head, 10);
    iAB(head, 20);
    iAE(head, 30);
    printList(head);
    return 0;
}