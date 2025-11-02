#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class list{//class start 
    Node* head;
    Node* tail;
    public:
    list() : head(nullptr), tail(nullptr) {}

    void isempty(){//isempty start 
        if (head== NULL && tail == NULL){
            cout<<"List is empty"<<endl;
        }
        else {
            cout<<"List is Not empty :" <<endl;
        }
        //isempty end
    }
    void append(int val){//append Start

        Node* temp1 = head;
        Node* temp2 = tail; //temp pointers to be used in insertion 
        Node* prev = NULL;


        Node * newNode = new Node (val);
        //the new Node has been created with the value so in all the next cases just update the pointers


        //Case: 1 - empty list 
        if(isempty()){
            head= tail= newNode;
        }

        //Case: 2 - If only one node is present 
        else if (head == tail){
            newNode-> prev = head;
            head-> next = newNode;
            tail = newNode;
        }

        //Case: 3 - if more than one Node is present 
        else {
            tail-> next = newNode;
            newNode->prev = tail;
            tail = newNode;
            }
    //append end
    }

    void display(){//diplay start 
        //Case: 1 - empty list 
        if(isempty())
        return;

        // Case: 2 - list Not empty 
        else {
            Node* temp = head;
            while (temp!= NULL)
            {
                cout<<temp->data<<endl<<"->";
                temp = temp -> next;
            }
        }
    //display end 
    }

    

//class end 
};