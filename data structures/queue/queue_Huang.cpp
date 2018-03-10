//Ryan Huang
//CISP430
//Queue

#include <iostream>
#include <fstream>
using namespace std;

ifstream in;
ofstream out;

struct node{
	int data;
	struct node* next;
};
typedef struct node node;

void enqueue(node*&, node*&, int);
int dequeue(node*&, node*&);
void build(node*&, node*&);
void processQueue(node*&, node*&);
void printList(node*);


int main(){
	int number;
	node *front, *rear;
	front = rear = NULL;
	build(front, rear);
	cout<<"Original Queue:"<<endl;
	printList(front);
	processQueue(front, rear);
	cout<<"New Queue:"<<endl;
	printList(front);
}

//remove negative numbers from the queue
void processQueue(node*& front, node*& rear){
	int temp;
	node* first = NULL;
	node* current = front;
	while (current!=first){
		temp=dequeue(front, rear);
		current=front;
		if (temp>=0){
			enqueue(front, rear, temp);
			if (!first){
				first = rear;
			}
		}
	}
}

//build the queue
void build(node*& front, node*& rear){
	in.open("input.txt");
	int num;
	while (in.good()){
		in>>num;
		enqueue(front, rear, num);
	}
	in.close();
}

//queue an int after the last element of the queue
void enqueue(node*& front, node*& rear, int item){
	node *newNode = new node;
	newNode->data=item;
	newNode->next=NULL;
	if (rear){
		rear->next=newNode;
		rear = newNode;
	}
	else{
		front = rear = newNode;
	}
}

//return the first element of the queue
int dequeue(node *&front, node *&rear){
	int number;
	node *temp;
	if (front){
		number=front->data;
		temp=front;
		front=front->next;
		delete temp;
		return number;
	}
	if (!front){
		rear = NULL;
	}
}

//Traverse and print the list
void printList(node* current){
	while ( current != NULL ) {
   	cout<<current->data<<endl;
   	current=current->next;
	}
	cout<<endl;
}
