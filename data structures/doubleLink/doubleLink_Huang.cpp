//Ryan Huang
//CISP430
//DoubleLink

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;
ofstream out;

struct nodeList{
	char data[20];
	struct nodeList* prev;
	struct nodeList* next;
};
typedef struct nodeList nodeList;

int clean();
void printList(nodeList*);
void printListRev(nodeList*);
nodeList* build();
nodeList* addList(nodeList*&, char data[]);
void outputList(nodeList* current);
nodeList* returnTail(nodeList* head);
void deleteFromHead(nodeList*&, int);
void deleteFromTail(nodeList*&, nodeList*&, int);

int main(){
	int first, second = 0;
	nodeList *head, *tail;
   in.open("input.txt");   
	head=build();
	tail=returnTail(head);
	
	cout<<"myList:"<<endl;
	printList(head);
	printListRev(tail);
	in.close();
	
	cout<<"Which item to delete from the beginning? ";
	cin>>first;
	
	deleteFromHead(head, first);
	printList(head);
	
	cout<<"Which item to delete from end? ";
	cin>>second;

	deleteFromTail(head, tail, second);
	printList(head);
	
	out.open("output.txt");
	outputList(head);
	out.close();
}

nodeList* build(){
	nodeList dummy;
	dummy.prev = NULL;
	dummy.next = NULL;
	nodeList* tail = &dummy;
	
	char A[20];
	while (clean() && in.good()){
		in>>A;
		tail = addList(tail, A);
	}
	dummy.next->prev = NULL; //Make sure prev in first element is NULL
   return (dummy.next);
}


nodeList* addList(nodeList*& tail, char data[]){
	nodeList* newNode = new nodeList;
	strcpy(newNode->data, data);
	newNode->prev = tail;
	newNode->next = NULL;
	tail->next = newNode;
	return tail->next;
}

//Traverse through list and return tail
nodeList* returnTail(nodeList* head){
	while ( head->next != NULL ) {
   	head=head->next;
	}
	return head;
}

//Clean function supplied in first group assignment
int clean(){
      string comments;  //store the comments in this variable
       while (in.peek()=='\n' || in.peek()=='/' || in.peek()==' ' || in.peek()=='\t'){
           if (in.peek()=='/' )
              getline(in, comments);  //read the entire line because it is a comment
           else
              in.get();    //eat the newline, space and tab characters
      }
      return 1;
}

//print starting from head
void printList(nodeList* current){
	while ( current != NULL ) {
   	cout<< current->data<<endl;
   	current=current->next;
	}
	cout<<endl;
}

//print starting from the tail
void printListRev(nodeList* current){

	while ( current != NULL ) {
   	cout<< current->data<<endl;
   	current=current->prev;
	}
	cout<<endl;
}

void outputList(nodeList* current){
	while ( current != NULL ) {
   	out<< current->data<<" ";
   	current=current->next;
	}
}


void deleteFromHead(nodeList*& head, int pos){
	nodeList *temp, *current;
	current = head;
	for (int num=1; num<pos; num++){
		head = head->next;
	}	
	if (head->prev==NULL){		//If deleting the first element of the list
		current=head->next;
	}
	else if (head->next==NULL){	//If deleting the last element of the list
		head->prev->next=NULL;
	}
	else{										//If deleting from the middle
		head->prev->next=head->next;
		head->next->prev=head->prev;
	}
	temp = head;
	head = current;
	delete temp;
	
}

void deleteFromTail(nodeList*& head, nodeList*& tail, int pos){
	nodeList *temp, *current;
	current = tail;
	for (int num=1; num<pos; num++){
		tail = tail->prev;
	}
	
	if (tail->next==NULL){		//If deleting the last element of the list
		tail->prev->next=NULL;
	}
	else if (tail->prev==NULL){	//If deleting the first element of the list
		tail->next->prev=NULL;
		head = tail->next;
	}
	else{										//If deleting from the middle
		tail->prev->next=tail->next;
		tail->next->prev=tail->prev;
	}
	temp = tail;
	tail = current;
	delete temp;
	
}
