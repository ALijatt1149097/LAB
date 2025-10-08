#include<iostream>
using namespace std:

struct Node {
int data:
Node* next;

Node(int a){
    data=a;
    next=NULL;

}

class list {
Node* head;
public;
list(){
    head=NULL;
}

int isempty(){
    if(head==NULL)
    return 1:
    else return 0:
}

int isfull(){
    node* newNode= new node;
    if (newNode == NULL)
    return 1;
    else reurn 0;}

Node* search (int key){
    if (isempty())
    return NULL;
    Node* temp = head;
    while (temp!= NULL)
    {
        if(temp->data==key)
        return temp;
        temp = temp->next;
        else return NULL;
    }
}
void append(int x){
    Node* new Node =- new Node;
    newNode->data = x;
    newNode->next = NULL;
    if (isempty){
        head=newNode;
        return;
    }
    else {
        Node*temp = head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void insertatpos(int pos, int a)
{
    if (isempty())
    {
        cout<<"list is empty";
        return;
    }
    Node* newNode = new Node;
    newNode->data = a;
    if (pos == 0)
    {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* temp = head;
    for (int i =0;i<pos -1 &&temp !=NULL;i++)
    {
        temp = temp->next;
    }
    if(temp == NULL)
    {
        cout<<"position out of range";
        delete newNode;
        return;
    }
    else {
        newNode->next = temp->next;
        temp->next = newNode;
    }
}
void insertbefore(int pos,int a)
{
    if (isempty()|| pos<=0)
    {
        cout<<"list is empty or insertion is not possible before zero position";
        return;
    }
    Node* newNode = new Node;
    newNode->data = a;
    else if (pos>=1){
        insertatpos(pos-1,a);
        return;
    }void insertbeforeoccuranceofavalue(int val, int a)
{
    if (isempty())
    {
        cout<<"list is empty";
        return;
    }
    Node* newNode = new Node;
    newNode->data = a;
    Node* temp= head;
    Node* p= NULL;
    while (temp!= NULL && temp->data != val)
    { p= temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout<<"value not found";
        delete newNode;
        return;
    }
    if (temp == head)
    {
        newNode->next = head;
        head = newNode;
        return;
    }
    else {
        newNode->next = temp;
        p->next = newNode;
    }
}
void insertaftereveryevenvaluednode(int a){
    if(isenpty()){
        cout<<"list is empty";
        return;
    }
    Node* newNode = new Node; 
    newNode->data = a;
    Node* temp = head;
    while (temp!= NULL){
        if(temp->data %2 !=0){
        node* newNode = new Node;
        newNode->data = a;
        newNode->next = temp->next;
        temp->next = newNode;        
        }
        temp = temp->next;
    }
}

void insertafterevryknodes(int k,int a)
{
    if (isempty() || k<=0){
        cout<<"list is empty or invalid k";
        return;
    }
  Node* temp = head;
  while (temp!= NULL){
    for (int i=1;i<k && temp!= NULL;i++){
        temp = temp->next;
    }
    if (temp == NULL)
    return;
    Node* newNode = new Node;
    newNode->data = a;
    newNode->next = temp->next;
    temp->next = newNode;
    temp = newNode->next; //IMPORTANT Cocept here
}
}

void buildalistdynamicallyfromarray(int arr[],int size){
    for(int i=0;i<size;i++){
        append(arr[i]);
}
}
void sortedinsert(int a){
    Node* newNode = new Node;
    newNode->data = a;
    newNode->next = NULL;
    if (isempty() || head->data >= a){
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* temp = head;
    Node* p = NULL;
    while (temp!=NULL && temp->data<a){
        p= temp;
        temp = temp->next;
    }
    if (temp == NULL){
        append(a);
        return;
    }
    else {
        newNode->next = temp;
        p->next = newNode;
    }
}

void insertmultiplenoes until-1(int a){

    if (a == -1)
    return;
    append(a);
    int x;
    cout<<"enter next no or -1 to stop";
    cin>>x;
    insertmultiplenoes until-1(x);
}

void insertbetweentwonodesiftheirsum>a (int a){
    Noed* newNode = new Node;
    newNode->data = a;  
    newNode->next = NULL;
    if (isempty() || head->next == NULL){
        append(a);
        return;
    }
    else {
        Node* temp = head;
        while (temp->next != NULL){
            if (temp->data + temp->next->data > a){
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }
            temp = temp->next;
        }
        append(a);
        return;
    }

void insertatsecondlastposition(int a){
    Node* newNode = new Node;
    newNode->data = a;
    newNode->next = NULL;
    if (isempty() || head->next == NULL){
        append(a);
        return;
    }
    Node* temp = head;
    Node* p = NULL;
    while (temp->next != NULL){
        p=temp;
        temp = temp->next;

    }
    newNode->next = temp;
    p->next = newNode;
    }
void builtbyalternatingnode(){
    cout<<"Enter vakue of node or -1 to stop";
    int x; 
    cin>>x;
    int count =1;
    while (x != -1){
        if (count %2 !=0){
            insertatpos(0,x);
        }
        else {
            append(x);
        }
        count++;
        builtbyalternatingnode();
        return;
    }
}

void sortedinsertinacircularlinkedlist(int a){ //important concept
    Node* newNode = new Node;
    newNode->data = a;
    newNode->next = NULL;
    if (isempty()){ //list is empty
        head = newNode;
        newNode->next = head;
        return;
    }
    if (head->data >= a){ //insertion before head
        Node* temp = head;
        while (temp->next != head){
            temp = temp->next;
        }
        newNode->next = head;
        head = newNode;
        temp->next = head;
        return;
    }
    Node* temp = head;
    while (temp->next != head && temp->next->data < a){ //insertion in between or at end
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}
    
void insertaftereveryoddvaluednode(int a){
    if (isempty()){
        cout<<"list is empty";
        return;
    }
    Node* temp = head;
    while (temp!= NULL){
        if (temp->data %2 !=0){
        node* newNode = new Node;
        newNode->data = a;
        newNode->next = temp->next;
        temp->next = newNode;        
        }
        temp = temp->next; //to make sure we move to next node
    }
}


void insertbeforeverynode>a(int a){
    if (isempty()){ //list is empty
        cout<<"list is empty";
        return;
    }
    Node* newNode = new Node;
    newNode->data = a;
    if (head->data > a){//insertion before head
        newNode->next = head;
        head = newNode;
    }
    Node* temp = head;
    Node* p = NULL;
    while (temp!= NULL){//insertion in between or at end
        if (temp->data > a){
            Node* newNode = new Node;
            newNode->data = a;
            newNode->next = temp;
            p->next = newNode;
        }
        p= temp;
        temp = temp->next; //to make sure we move to next node
    }
}

void insertamarkernodeafterthevlauesdivisblebym(int m, int a;){
   
    if (isempty()){ //list is empty 
        cout<<"list os empty";
            }
    if(m==0){

        cout<<"M canoot be zero"<<endl;
    }
    else {
        Node*temp= head;
        while(temp!=NULL)
        {
            if (temp->data%m == 0){
                  Node* newNode= new Node;
                  newNode->data = a;
                newNode->next = temp->next;
                temp->next = newNode;
                            }
            temp=temp->next
        }
    }
}







void display(){
    if (isempty()){
        cout<<"list is empty";
        return;
    }
    Node* temp = head;
    while (temp!= NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}


//cclass
}
