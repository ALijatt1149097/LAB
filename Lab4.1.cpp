// insertion deldetion and traversal in singly linked list
#include <iostream>
using namespace std;



struct Node {
    int data;
    string name;
    Node* next;
};




//traversal to a particular position
void TraversaltoPt(Node *head, int position){
    Node *Temp = new Node();
    Temp = head;
    if(Temp->next == NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    else {
    for(int i =1; i<position; i++){
        if (Temp->next !=NULL)
        Temp = Temp->next;
        else 
        cout<<"end of list reached"<<endl;
        return;
    }
    }
    cout<<"Value at position "<<position<<" is: "<<Temp->data<<"namea at poistion is"<<Temp->name<< endl;
}




//insert at begin
void insertAtBegin(Node *head, int Value, string name)
{
Node *temp = new Node();
temp->data = Value;
temp->next = head;
temp->name = name;
head = temp;
}




//insert at end
void InsertAtEnd(Node * head, int Value, string name){
    Node *temp = new Node();
    temp = head;
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->data = Value;
    temp->name = name;
    temp->next = NULL;  
}


//insert at middle
void insertatMiddle(Node *head, int Value, int position, string name){
    Node *temp = new Node();
    temp = head;
    Node *newNode = new Node();
    newNode->data = Value;
    newNode->name = name;
    for(int i=1; i<position-1; i++){
        if(temp->next != NULL)
        temp = temp->next;
        else {
            cout<<"End of list reached"<<endl;
            return;
        }
    }
    newNode->next = temp->next;
    temp->next = newNode;
}


//serching the linke list 

void SearchLL(Node *head, string fdata){
    Node *temp = new Node();
    temp = head;
    while(temp != NULL){
        if(temp->name == fdata){
            cout<<"Data found: "<<fdata<<endl;
            return;
        }
        temp = temp->next;
    }
    cout<<"Data not found: "<<fdata<<endl;
}

//deledtion of a particular nide

void deleteNode(Node *head, int Value, string name){
    Node *temp = new Node();
    temp = head;
    for (int i = 1; i < Value; i++) {

        temp = temp->next;
        if (temp == NULL) {
            cout << "Position is greater than the number of nodes in the list." << endl;
            return;
        }
    }   
    delete temp;
    cout<<"Node deleted at position: "<<Value<<endl;
    cout<<"list after deletion: "<<endl;
    Node* t = head; 
    while(t != NULL){
        cout<<t->data<<"->"<<t->name<<"->";
        t = t->next;
    }
    cout<<"NULL"<<endl;
}

int main() {
  int n,data,data2,a;
  string b,c,d,s;
  Node* Head=NULL;
  Node* SL = new Node();
  Head=SL;
  cout<<"Enter the data of Head Node:"<<endl;
  cin>>a;
  SL->data=a;
  cin>>b;
  SL->name=b;
  SL->next=NULL;




  //making linked list of n nodes using for loop
  cout<<"Enter the number of Nodes: "<<endl;
  cin>>n;
  for(int i=1;i<=n;i++){
    cout<<"Enter the Data of node current and next:"<<endl;
    cin>>data>>data2;
    cout<<"Enter the current name and next name: "<<endl;
    cin>>c>>d;  
    Node* p = new Node();
        if(Head->next == NULL){
      Head->next = p;
    }
    p->data = data;
    p->name=c;
    p->next = NULL;
    SL->next=p;
    SL = new Node();
    SL->data=data2;
    SL->name=d;
    p->next = SL;

  }


// traversal and cout
Node* temp = Head;
while(temp != NULL){
    cout<<temp->data<<"->"<<temp->name<<"->";
    temp = temp->next;
}
cout<<"NULL"<<endl;

//function calling

TraversaltoPt(Head, 3);
insertAtBegin(Head, 5  , "Abid"); 
InsertAtEnd(Head, 10, "Ali");
insertatMiddle(Head, 7, 2, "Sara");
SearchLL(Head, "Abid");
deleteNode(Head, 3, "Ali");


return 0;
}