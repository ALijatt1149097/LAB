#include<iostream>
using namespace std;

struct Node{
	char letter;
	Node* next;
	
};

int main(){
	char a[4];
	cout<<"\nLinked List\n"<<endl;
	cout<<"Enter a String of 4 characters: "<<endl;
	for(int i =0;i<4;i++){
		cin>>a[i];
	}	
	Node *Node1 = new Node();
	Node *Node2 = new Node();
	Node *Node3 = new Node();
	Node *Node4 = new Node();
	
	Node1->next = Node2;
	Node2->next = Node3;
	Node3->next = Node4;
	Node4->next = NULL;
	
	Node1->letter = a[0];
	Node2->letter = a[1];
	Node3->letter = a[2];
	Node4->letter = a[3];
	
	Node* head = Node1;
	
	Node* temp = Node1;
	int i = 1;
	while(temp != NULL){
		cout<<"Character "<<i<<" is: "<<temp->letter<<endl;
		temp = temp->next;
		i++;
	}
	cout<<"\nEND OF LIST\n"<<endl;
	return 0;
}