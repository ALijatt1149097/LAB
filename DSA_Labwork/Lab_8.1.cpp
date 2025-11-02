#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int d) : data(d), next(nullptr), prev(nullptr) {}
};

class DList {
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    void insertAtBeginning(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        if (head!=NULL) {
            head->prev = newNode;
        } else {
            head=tail = newNode;
        }
        head = newNode;
    }

    int countNodes() {
        int count = 0;
        Node* temp = tail;
        while (temp!=NULL) {
            count++;
            temp = temp->prev;
        }
        return count;
    }

    Node* reverseList() {
        Node* curr = head;
        Node* prev= NULL;
        Node*next = NULL;
        do {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }while (curr!= NULL);
        head = prev;
        return head;
    }

    void print() {
        Node* temp = head;
        while (temp!= NULL) {
            cout << temp->data <<"->";
            temp = temp->next;
        }
        cout << '\n';
    }
};

int main() {
    DList a;
    a.insertAtBeginning(10);
    a.insertAtBeginning(20);
    a.insertAtBeginning(30);
    a.insertAtBeginning(40);
    a.insertAtBeginning(50);

    cout << "Original: ";
    a.print();

    int x = a.countNodes();
    cout << "Number of nodes = " << x << '\n';

    a.reverseList();
    cout << "Reversed: ";
    a.print();

    return 0;
}
