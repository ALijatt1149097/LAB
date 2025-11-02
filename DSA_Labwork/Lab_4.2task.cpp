#include <iostream>
using namespace std;


struct Node {
    int data;
    string name;
    Node* next;
};



int main() {
  int n,data,data2,a;
  string b,c,d,e;
  Node* Head=NULL;
  Node* SL = new Node();
  Head=SL;
  cout <<"Enter the Name of Head Node: "<<endl;
  cin>>b;
  SL->name=b;
  cout<<"Enter the data of Head Node:"<<endl;
  cin>>a;
  SL->data=a;
  SL->next=NULL;
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


Node* temp = Head;
while(temp != NULL){
    cout<<temp->name<<"->";
    temp = temp->next;
}
cout<<"NULL"<<endl;
temp = Head;
while(temp != NULL){
    cout<<temp->data<<"->";
    temp = temp->next;
}
cout<<"NULL"<<endl;
cout<<"Enter the name to search: "<<endl;
cin>>e;
temp = Head;
for (int i=1; temp != NULL; i++){
    if(temp->name == e){
        cout<<"Data Found "<<e<<" at "<<i<<" Marks: "<<temp->data<<endl;
        break;
    }
    else {
        cout<<"Data Not Found "<<e<<" at "<<i<<" Marks: "<<temp->data<<endl;
    }
    temp = temp->next;

}

    cout<<"Enter the position: "<<endl;
    cin>>n;
    if(n == 1){
        //Insertion at beginning funciton
    Node* temp = new Node();
    temp->data=10;
    temp->next = Head;
    Head= temp;
    }else{
        int check = 1;
    temp = Head;
    while(temp->next != NULL && check < n){
        temp = temp->next;
        check++;
    }
    Node* newnode = new Node();
    newnode->data = 20;
    newnode->next = NULL;
    temp->next = newnode;
}
cout<<"After Insertion at Middle: "<<endl;
temp = Head;
while(temp != NULL){
    cout<<temp->data<<"->";
    temp = temp->next;
}
cout<<"NULL"<<endl;


return 0;
}