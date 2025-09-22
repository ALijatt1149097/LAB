#include<iostream>
using namespace std;

struct Node{
	int data;
	Node* next;
};

int main(){
	cout<<"\nLinked List\n"<<endl;
	Node *first = new Node();
	Node *second = new Node();
	Node *third = new Node();
	
	first->data=1;
	first->next = second;
	
	second->data=2;
	second->next=third;
	third->data=4;
	third->next=NULL;
	
	Node *head = first;
	Node *temp = new Node();
	
	temp = first;
	int i = 1;
	while(temp != NULL){
		cout<<"Data of Node "<<i<<": "<<temp->data<<endl;
		cout<<"Address of Next Node: "<<temp->next<<endl;
		temp = temp->next;
		i++;
	}
	
}