#include<iostream>
using namespace std;

struct Node{
	int number;
	Node* next;
	
};

int main(){
	cout<<"\n\n====================Linked List=====================\n"<<endl;
	
	Node *first = new Node();
	Node *second = new Node();
	Node *third = new Node();
	Node *fourth = new Node();
	Node *fifth = new Node();
	
	cout<<"\n\n====================ORIGINAL LIST=====================\n"<<endl;
	
	first->next=second;
	second->next=third;
	third->next=fourth;
	fourth->next=fifth;
	fifth->next=NULL;
	
	first->number=1;
	second->number=2;
	third->number=3;
	fourth->number=4;
	fifth->number=5;
	
	
	Node* head = first;
	Node* temp = first;
	int i = 1;
	while(temp!=NULL){
		cout<<"Data of Node "<<i<<" is: "<<temp->number<<endl;
		temp = temp->next;
		i++;
	}
	
	cout<<"\nSPLITTED LIST"<<endl;
	Node* Node1 = first;
	Node* Node2 = second;
	Node* Node3 = third;
	Node* Node4 = fourth;
	Node* Node5 = fifth;
	
	Node1->next=Node3;
	Node2->next=Node4;
	Node3->next=Node5;
	Node4->next=NULL;
	Node5->next=NULL;	
	
	Node* head1 = Node1;
	Node* head2 = Node2;
	Node* temp1 = Node1;
	Node* temp2 = Node2;
	cout<<"\nLIST 1"<<endl;	
	int j = 1;
	while(temp1!= NULL){
		cout<<"Data of Node "<<j<<" is: "<<temp1->number<<endl;
		temp1 = temp1->next;
		j++;
	}
	cout<<"LIST 2"<<endl;
	int k = 1;
	while(temp2!= NULL){
		cout<<"Data of Node "<<k<<" is: "<<temp2->number<<endl;
		temp2 = temp2->next;
		k++;
	}
	cout<<"\nEND OF LIST\n"<<endl;
	return 0;
}