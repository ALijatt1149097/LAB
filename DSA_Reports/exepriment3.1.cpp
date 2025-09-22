#include <iostream>
using namespace std;

struct Node {
        int data;
        Node* next;
    };

int main ()
{
int n;
cout<<"Enter the number of nodes: ";
cin>>n;

Node *head = new Node;
Node *SL = new Node();
SL->data = 10;
SL->next = NULL;
head = SL;

    for (int i=0; i<n; i++)
    {
    Node *ptr = new Node;
    ptr->data = 20;
    if (head->next == NULL)
    {
    ptr->next = NULL;
    head->next = ptr;
    }
    else 
    {

        Node *SL = new Node();
        SL->data = 30;
        SL->next = NULL;
        ptr->next = SL;

        Node *ptr2 = new Node();
        ptr2->data = 40;
        ptr2->next = NULL;
        SL->next = ptr;
    }
    }
    return 0;
}