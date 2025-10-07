#include <iostream>
using namespace std;    

struct Node {
    int data;
    Node *next;
};
class List {
    Node *head;
public:
    List() { head = NULL; }
    int isempty(){
        if (head == NULL)
            return 1;
        else
            return 0;
    }
    void append(int a){
        if (isempty()){
            Node *temp = new Node;
            temp->data = a;
            temp->next = NULL;
            head = temp;
        }
        else{
            Node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;
            Node *newnode = new Node;
            newnode->data = a;
            newnode->next = NULL;
            temp->next = newnode;
        }
    }
    void insertat(int pos, int val){
        if(isempty() || pos == 0){
            Node *temp = new Node;
            temp->data = val;
            temp->next = head;
            head = temp;
        }
        else{
            Node *temp = head;
            for (int i = 0; i < pos - 1 && temp->next != NULL; i++)
                temp = temp->next;
            Node *newnode = new Node;
            newnode->data = val;
            newnode->next = temp->next;
            temp->next = newnode;
        }
    }
    Node* search(int x){
        if(isempty())
            return NULL;
        else{
            Node *temp = head;
            while(temp != NULL){
                if(temp->data == x)
                    return temp;
                temp = temp->next;
            }
            return NULL;
          }
        }
    int deletelastnode(){   
        if (isempty())
            return 0;
        else if (head->next == NULL){
            int x = head->data;
            delete head;
            head = NULL;
            return x;
        }
        else{
            Node *temp = head;
            while (temp->next->next != NULL)
                temp = temp->next;
            int x = temp->next->data;
            delete temp->next;
            temp->next = NULL;
            return x;
        }
    }
    int deleteanynode(int x){
        Node *n = search(x);
        if (n == NULL)
            return 0;
            else{
                Node *temp = head;
                while (temp->next != n && temp->next != NULL)
                    temp = temp->next;
                if (temp->next == NULL)
                    return 0;
                temp->next = n->next;
                delete n;
                return 1;
            }
        }
    int countNodes(int v){
        int c = 0;
        Node *temp = head;
        while (temp != NULL){
            if (temp->data == v)
                c++;
            temp = temp->next;
        }
        return c;
    }
    void deleteconsec(int pos) {
    if (isempty() || pos < 0)
        return;

    Node* temp = head;
    Node* prev = NULL;

    for (int i = 0; i < pos && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;


    if (pos == 0) {
        Node* nextNode = temp->next;
        delete temp;
        if (nextNode != NULL) {
            head = nextNode->next;
            delete nextNode;
        } else {
            head = NULL;
        }
        return;
    }
    Node* nextNode = temp->next;
    if (nextNode == NULL) {
        prev->next = NULL;
        delete temp;
    }
    else {
        prev->next = nextNode->next;
        delete temp;
        delete nextNode;
    }
}

    int isfull(){
        Node *temp = new Node;
        if (temp == NULL)
            return 1;
        else{
            delete temp;
            return 0;
        }
    }
    void display(){
        Node *temp = head;
        while (temp != NULL){
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main(){
    List l;
    l.append(10);
    cout << "Linked List: ";
    l.display();
    l.append(20);
    cout << "Linked List: ";
    l.display();
    l.append(982);
    cout << "Linked List: ";
    l.display();
    l.append(30);
    cout << "Linked List: ";
    l.display();
    l.append(99);
    cout << "Linked List: ";
    l.display();
    l.append(220);
    cout << "Linked List: ";
    l.display();
    cout << "Linked List: ";
    l.display();
    cout << "Count nodes till 20: " << l.countNodes(30) << endl;
    cout << "Count nodes 220: " << l.countNodes(220) << endl;
    l.deleteconsec(0);
    cout << "After deleting consecutive nodes from position 0: ";
    l.display();
    l.deleteconsec(1);
    cout << "After deleting consecutive nodes from position 1: ";
    l.display();
    return 0;
}
