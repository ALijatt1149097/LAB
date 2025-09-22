#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
  int n,data,data2,a;
  Node* Head=NULL;
  Node* SL = new Node();
  Head=SL;
  cout<<"Enter the data of Head Node:"<<endl;
  cin>>a;
  SL->data=a;
  SL->next=NULL;
  cout<<"Enter the number of Nodes: "<<endl;
  cin>>n;
  for(int i=1;i<=n;i++){
    cout<<"Enter the Data of node current and next:"<<endl;
    cin>>data>>data2;
    Node* p = new Node();
        if(Head->next == NULL){
      Head->next = p;
    }
    p->data = data;
    p->next = NULL;
    SL->next=p;
    SL = new Node();
    SL->data=data2;
    p->next = SL;

  }


Node* temp = Head;
while(temp != NULL){
    cout<<temp->data<<"->";
    temp = temp->next;
}
cout<<"NULL"<<endl;
return 0;
}