#include <iostream>
using namespace std;

//defining struct node with 3 things name, grades, marks and next pointer
struct Node{
string name;
char grades;
int marks;
Node* next; 
};


//update the marks in linked list
void updatemarks(Node *head, string nameto, int newMarks) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp == nullptr) return; // position is not in the list
        if (temp->name == nameto) {
            temp->marks = newMarks;
            return;
        }
        temp = temp->next;
    }

}
//insert node at any position

void insertNodeatposition (Node*& head, string name, char grades, int marks, int position) {
    Node *p1 = new Node();
    p1->name = name;
    p1->grades = grades;
    p1->marks = marks;
    p1->next = nullptr;

    if(position ==1){
        head = p1;
        return;
    }
    else{
        Node* temp = head;
        for(int i=1; i<position-1; i++){
            temp = temp->next;
        }
        p1->next = temp->next;
        temp->next = p1;
    }
    
}

// diplay list 
void display(Node * head) {
Node *temp = head;
while (temp!=nullptr)   {

cout<<temp->name<<":"<<temp->grades<<","<<temp->marks<<",";

temp = temp->next;

}}

//insert at end 
void insertatEnd(Node *head, string name1, int grades, int marks) {
    Node* temp= head;
    while (temp)
    {
        if (temp->next == nullptr) {
            temp->next = new Node();
            temp->next->name = name1;
            temp->next->grades = grades;
            temp->next->marks = marks;
            temp->next->next = nullptr;
            return;
        }
        temp = temp->next;  
    }

}
//delete node at any position
void deleteNode(Node*& head, int position) {
    // empty list
    if (head == nullptr) return; 

if (position==1){
    Node* temp = head;
    head = head->next;
    delete temp;
}
else{//deletion by middle position
    Node* prev = head;
    for(int i=1; i<position-1; i++){
        prev = prev->next;
    }
    Node* nodeToDelete = new Node();
    for(int i=1; i<position; i++){
        nodeToDelete = nodeToDelete->next;
    }
    if (nodeToDelete != nullptr) {
        prev->next = nodeToDelete->next;
        delete nodeToDelete;
    }




}
}
//deletion by roll number 
void deletebyrollnumber(Node* head, int rollnumber13)
{
    Node* temp= new Node;
    temp = head;

}
// search by choice od catgory 
void searchbyctgy(Node* head, int choice, string searchdata)
{
//search by choice use switch 

} 

//search by name or marks or grades 
void searchanydatainNode(Node* head, string key) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->name == key || to_string(temp->marks) == key || to_string(temp->grades) == key) {
            cout << "Found: " << temp->name << ", " << temp->grades << ", " << temp->marks << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Not Found" << endl;
}
int main (){
    Node*p = new Node();
    p->name = "Ali";
    p->grades = 'A';
    p->marks = 90;
    p->next = nullptr;

    Node*q = new Node();
    q->name = "Abid";
    q->grades = 'B';
    q->marks = 80;
    q->next = nullptr;
    p->next = q;

    Node* head = new Node();
    head = p;

// using insert function to insert node at any position
    insertNodeatposition(head, "Ahmed", 'C', 70, 2);
    insertNodeatposition(head,"Basit",'B',77,3);

    //serach by name data oe marks 
  

    //serach by  option 
    int choice;
    cout << "Search by (1) Name (2) Grades (3) Marks: ";
    cin >> choice;  
    cout << "enter the name or data you want to search: ";
    string key;
    cin >> key;
    searchanydatainNode(head, key);
    cout << "Enter the name of the student you want to update: ";
    string nametoup;
    cin >> nametoup;
    int upmarks;
    cin >> upmarks;
    updatemarks(head, nametoup, upmarks);

    cout<<"name grade and marks of student to be inserted at the end";
    string name12,name13;
    cin>>name12;    
    char grade12,garde13;
    cin>>grade12;
    int marks12,marks13;
    cin>>marks12;
    updatemarks(head,name12,marks12);
    display(head);
    insertatEnd(head,name12,grade12,marks12);
    cout<<"enterthe name garde marks at the beining ";
    cin>>name13,garde13,marks13;
    insertNodeatposition(head,name13,garde13,marks13,1);

    display(head);
    return 0;
}