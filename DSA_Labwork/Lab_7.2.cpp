#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int v = 0) : data(v), next(NULL) {}
};

class CLL {
public:
    Node* head;
    Node* tail;

    CLL() : head(NULL), tail(NULL) {}

    // Insert at beginning (head)
    void insertAtHead(int val) {
        Node* n = new Node(val);

        // Empty list
        if (head == NULL) {
            head = tail = n;
            n->next = head;   // circular link
            return;
        }

        // Non-empty
        n->next = head;
        head = n;
        tail->next = head;    // Circularr lnk 
    }

    // Insert at end using ----tail----- pointer
    void append(int val) {
        Node* n = new Node(val);

        // Empty list
        if (head == NULL) {
            head = tail = n;
            n->next = head;   // circular link to itself
            return;
        }

        // Non-empty
        n->next = head;       
        tail->next = n;       
        tail = n;             
    }

    // Display 
    void display() {
        if (head == NULL) {
            cout << "List is empty\n";
            return;
        }

        Node* temp = head;
        do {
            cout << temp->data << "->";
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

    // Delete Node of given value
    void deleteNode(int val) {
        if (head == NULL) {               // Case 1: list is empty
            return;
        }

             // Case 2: deleting head
        if (head->data == val) {
            // 2a: only one node
            if (head == tail) {
                delete head;
                head = tail = NULL;
                return;
            }

            // 2b: multiple nodes
            Node* d = head;
            head = head->next;               
            tail->next = head;              
            delete d;
            return;
        }

        // Case 3: find value othet than head 
        Node* prev= head;
        Node* curr  = head->next;

        // search until we loop back to head or find the value
        while (curr != head && curr->data != val) {
            prev = curr;
            curr = curr->next;
        }

        // 3A: value not found
        if (curr == head) {
            cout << "value not found" << endl;
            return;
        }

        // unlink the node
        prev->next = curr->next;

        // Update tail if we deleted the last node
        if (curr == tail) {
            tail = prev;
        }

        delete curr;
    }
};

int main() {
    CLL list;

    // Insert at head
    list.insertAtHead(30);
    list.insertAtHead(20);
    list.insertAtHead(10);

    // Insert at tail
    list.append(40);
    list.append(50);

    cout << "List: ";
    list.display();            // 10 20 30 40 50

    list.deleteNode(10);       // delete head
    cout << "After deleting 10: ";
    list.display();            // 20 30 40 50

    list.deleteNode(50);       // delete tail
    cout << "After deleting 50: ";
    list.display();            // 20 30 40

    list.deleteNode(999);      // value not found
    cout << "After trying to delete 999: ";
    list.display();            // 20 30 40

    return 0;
}
