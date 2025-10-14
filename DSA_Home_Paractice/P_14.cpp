    #include <iostream>
    using namespace std;

    struct Node{
        int data;
        Node* next;
    };

    class list{
        Node* head;
        Node* tail;
        public:
        
        list(){
            head = NULL;
        }


    int isempty(){
        if (head==NULL)
        return 1;
        else 
        return 0;
    }


   void append(int a) {
        Node* newNode = new Node;
        newNode->data = a;
        newNode->next = nullptr;

        if (isempty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }


    void display(){
        Node*temp = head;
        while (temp!=NULL)
        {
            cout<<temp->data<<"->";
            temp = temp->next;
        }
    }

    int isfull(){
    Node* newNode= new Node;
    if (newNode==NULL){
    cout<<"list is Full";
    return 1;}
    else 
    { cout<< "list is not Full";
    return 0;
    }
    }

    void insertatpos(int pos, int a){
        Node* newNode = new Node;
        newNode-> data = a;

        if (isempty()|| pos<=0)
        cout<<"list is empty";

        else if (pos==1)
        {
            newNode->next= head;
            head = newNode;
        }
        else {
            Node* temp = head;
        for (int i=0;temp!= NULL && i<pos-1;i++)
        {
            if (temp == NULL){
                cout <<"Position not found";
                return;
            }
            else {
                newNode->next = temp->next;
                temp->next= newNode;
            }
        }
        }
    }

void insertsublistatposition(int pos, list &a, list &b){
    if (b.isempty()) {
        cout << "sublist is empty\n";
        return;
    }
    if (pos <= 0) {
        cout << "position is undefined\n";
        return;
    }

    // Case 1: A is empty OR insert at head (pos == 1)
    if (a.isempty() || pos == 1) {
        b.tail->next = a.head;   // attach old A to B's tail
        a.head = b.head;         // new A head is B's head
        if (a.tail == nullptr)   // if A was empty, tail becomes B's tail
            a.tail = b.tail;

        // clear B (ownership transferred)
        b.head = b.tail = nullptr;

        cout << "After inserting sublist at position " << pos << ":\n";
        a.display();
        cout << endl;
        return;
    }

    // Case 2: insert somewhere after head
    Node* temp = a.head;
    for (int i = 1; temp != nullptr && i < pos - 1; ++i)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "position not found\n";
        return;
    }

    // Splice B after temp
    b.tail->next = temp->next;
    temp->next = b.head;

    // Tail maintenance
    if (a.tail == temp)
        a.tail = b.tail;

    // clear B (ownership transferred)
    b.head = b.tail = nullptr;

    cout << "After inserting sublist at position " << pos << ":\n";
    a.display();
    cout << endl;
}

int countnodes(){
    if(isempty()){
    return 0;}
  else {
    Node* temp=head;
    int count=0;
    while (temp!= NULL)
    {count++;
        temp= temp->next;
    }
    return count;}
}

Node* middlenode(){
    if(isempty())
    {cout<<"list is empty:\n";
        return NULL;}
    else {
    Node* temp= head;
    int x = countnodes()/2;
    for (int i =0;i<x;i++){
        temp= temp->next;
    }
    return temp;}
}

void insertatmiddle(int a){
    if(isempty()){
        cout<<"listisempty";
        return;
    }
    else
    {
        Node*temp = head;
        Node*newNode = new Node;
        newNode->data = a;
        int mid = countnodes()/2;
        for(int i=0;i <mid-1;i++)
        {
            temp=temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}


Node* search(x);
{
    if(isempty())
    return NULL;
    else 
    {
        Node* temp= head;
        while (temp!= NULL && temp->data !=x){
            temp= temp->next;
        }
        if (temp==NULL)
        {
            cout<<"Not Found";
        }
        else 
        return temp;
    }
}



void deleteAllGreaterthanx(int x) {
    Node* temp = head;
    Node* prev = NULL;

    // remove from start if needed
    while (head != NULL && head->data > x) {
        temp = head;
        head = head->next;
        delete temp;
    }

    temp = head;
    while (temp != NULL) {
        if (temp->next != NULL && temp->next->data > x) {
            Node* del = temp->next;
            temp->next = temp->next->next;
            delete del;
        } else {
            temp = temp->next;
        }
    }
}

void deleteSecondOfPairs() {
    // if list is empty or has only one node, do nothing
    if (head == NULL || head->next == NULL) {
        cout << "List is too short to delete pairs." << endl;
        return;
    }

    Node* temp = head;

    while (temp != NULL && temp->next != NULL) {
        Node* del = temp->next;      // second node of the pair
        temp->next = del->next;      // skip the deleted node
        delete del;                  // free memory
        temp = temp->next;           // move to the next pair
    }
}












    };

    int main (){
        list a,b;
        a.append(1);
        a.append(2);
        a.append(3);
        a.append(4);
        a.append(5);
        a.display();
        cout<<endl;
        a.insertatpos(2,66);
        a.display();
        cout<<endl;
        a.insertatpos(1,11);
        a.display();
        cout<<endl;
        b.append(6);
        b.append(7);
        b.append(8);
        b.append(9);
        b.display();
        cout<<endl;
        a.insertsublistatposition(2,a,b);
        int x=a.countnodes();
        cout<<x<<endl;
        b.display();
        cout<<endl;
        int z=b.countnodes();
        cout<<z<<endl;
        Node* n= a.middlenode();
        cout<<n->data<<endl;
        a.append(5);
        a.insertatmiddle(222);
        a.display();
        cout<<endl;

       


    }