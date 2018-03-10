//Ryan Huang
//CISP430
//Homework 1 

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;
ofstream out;

//Doubly linked list containing first names of students
//and pointer to their scores
struct nodeStudent{
	char firstName[20];
	struct nodeStudent* prev;
	struct nodeStudent* next;
	struct nodeScore* scorePtr;
};
typedef struct nodeStudent nodeStudent;

//Single linked list containing scores
struct nodeScore{
	char data[20];
	struct nodeScore* next;
};
typedef struct nodeScore nodeScore;

//Function Prototypes
int clean();
void processFile(nodeStudent*&, nodeStudent*&);
void addStudent(nodeStudent*&, nodeStudent*&, char name[]);
void printList(nodeStudent*);
void printListRev(nodeStudent*);

//Main Function
int main(){
	nodeStudent *head, *tail = NULL;
	processFile(head, tail);
	cout<<"Main current:"<<head->firstName<<endl;
	cout<<"Main tail:"<<tail->firstName<<endl;
	printList(head);
	printListRev(tail);
//	char A[] = "John";
//	char B[] = "Jack";
//	cout<<"Result:"<<strcmp(A, B)<<endl;
//	
//	if (strcmp(A, B)<0){
//		//negative
//		cout<<B<<" goes after "<<A<<endl;
//	}
//	else{
//		//positive
//		cout<<B<<" goes before "<<A<<endl;
//	}
	
}

//Functions

//Process the file, using a dummy node, create a list and call functions as needed.
void processFile(nodeStudent*& head, nodeStudent*& tail){
	nodeStudent dummy;
	dummy.next=NULL;
	dummy.prev=NULL;
	nodeStudent *origin = &dummy;
	nodeStudent *current = NULL;
	in.open("input.txt");
	char A[20];
	while (clean() && in.good()){
		in>>A;
		if (strcmp(A, "delete")==0){
			//call delete
			cout<<"Delete Called"<<endl;
		}
		else{
			//create nodes
			cout<<"Create nodes"<<endl;
			addStudent(origin, current, A);
		}
	}
	head = dummy.next;
	tail = current;
	in.close();
}

//Add Students
void addStudent(nodeStudent*& origin, nodeStudent*& current, char name[]){
	nodeStudent* newNode = new nodeStudent;
	nodeStudent* head = origin->next;
	strcpy(newNode->firstName, name);
	
	if (!current){
		cout<<"List is empty. Creating first node..."<<endl;
		newNode->next=NULL;
		current=newNode;
		origin->next=current;
	}
	else{
		cout<<"List is not empty..."<<endl;
		cout<<"head:"<<head->firstName<<endl;
		printList(head);
		if (strcmp(head->firstName, name)>0){
			//go before
			cout<<name<<" goes before "<<head->firstName<<endl;
			newNode->next = head;
			newNode->prev = NULL;
			origin->next->prev=newNode;
			origin->next = newNode;
		}
		else{
			//go after
			//cout<<"head:"<<head->firstName<<endl;
			while((strcmp(head->firstName, name)<0)&&!(head->next==NULL)){
				cout<<name<<" less than "<<head->firstName<<endl;
				head=head->next;
			}
			//cout<<name<<" goes after "<<head->firstName<<endl;
			if (head->next==NULL){
				cout<<"next is null. we are at the end"<<endl;
				cout<<name<<" goes after "<<head->firstName<<endl;
				cout<<"current:"<<head->firstName<<endl;
				newNode->prev = head;
				newNode->next = NULL;
				head->next = newNode;
				current = newNode;
				//cout<<"current:"<<current->firstName<<endl;
			}
			else{
				//Insert in middle
				cout<<"next is not null. we are in the middle"<<endl;
				cout<<"current head:"<<head->firstName<<endl;
				cout<<"name:"<<name<<endl;
				newNode->prev = head->prev;
				newNode->next = head;
				head->prev->next = newNode;
				head->prev = newNode;
			}
			
		}
	}	
}

//Print the list
void printList(nodeStudent* current){
	cout<< "print: "<<endl;
	while ( current != NULL ) {
   	cout<< current->firstName<<endl;
   	current=current->next;
	}
	cout<<endl;
}

void printListRev(nodeStudent* current){
	while ( current != NULL ) {
   	cout<< current->firstName<<endl;
   	current=current->prev;
	}
	cout<<endl;
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
