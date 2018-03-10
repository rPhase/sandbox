//Ryan Huang
//CISP430
//CircularList

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
void printList(nodeList*, nodeList*);
void printListRev(nodeList*, nodeList*);
void build(nodeList*&, nodeList*&);
nodeList* addList(nodeList*&, char data[]);
void outputList(nodeList*, nodeList*);
void deleteNodes(nodeList*&, nodeList*&, int);
void deleteNode(nodeList*&, nodeList*&);

int main(){
	int nodesToDelete = 0;
	nodeList *head, *tail;
   in.open("input.txt");   
   build(head, tail);


	cout<<"Print list of names:"<<endl;
	printList(head, tail);
	cout<<"Reverse Print:"<<endl;
	printListRev(head, tail);
	in.close();
	
	cout<<"Enter a number of nodes to delete: ";
	cin>>nodesToDelete;
	
	cout<<"Deleting "<<nodesToDelete<<" nodes..."<<endl;
	
	deleteNodes(head, tail, nodesToDelete);
	
	cout<<endl<<"Print:"<<endl;
	printList(head, tail);
	cout<<"Reverse Print:"<<endl;
	printListRev(head, tail);
	
	out.open("output.txt");
	outputList(head, tail);
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

void build(nodeList*& first, nodeList*& last){
	nodeList dummy;
	dummy.prev = NULL;
	dummy.next = NULL;
	nodeList* tail = &dummy;
	
	char A[20];
	while (clean() && in.good()){
		in>>A;
		tail = addList(tail, A);
	}
	dummy.next->prev = tail;
	tail->next = dummy.next;
	first = dummy.next;
	last = tail;
	
}

nodeList* addList(nodeList*& tail, char data[]){
	nodeList* newNode = new nodeList;
	strcpy(newNode->data, data);
	newNode->prev = tail;
	newNode->next = NULL;
	tail->next = newNode;
	return tail->next;
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
void printList(nodeList* first, nodeList* last){
	if (first != NULL){
		do{
			cout<< first->data<<endl;
			first = first->next;
		}while (first != last->next);
		cout<<endl;
	}
	else{
		cout<<"Empty List"<<endl;
	}
}

//print starting from the tail
void printListRev(nodeList* first, nodeList* last){
	if (last != NULL){
		do{
			cout<< last->data<<endl;
			last = last->prev;
		}while (last != first->prev);
		cout<<endl;
	}
	else{
		cout<<"Empty List"<<endl;
	}
}

void outputList(nodeList* first, nodeList* last){
	if (first != NULL){
		do{
			out<< first->data<<endl;
			first = first->next;
		}while (first != last->next);
	}
	else{
		out<<"Empty List"<<endl;
	}
}

//Delete a single node
void deleteNode(nodeList*& first, nodeList*& last){
	nodeList *temp;
	cout<<"Deleting "<<first->data<<endl;
		if (first == last){
			temp=first;
			delete temp;
			first=NULL;
			last=NULL;
		}
		else{
			temp = first;
			first = first->next;
			delete temp;
		}
}

//Traverse and call deleteNode
void deleteNodes(nodeList*& first, nodeList*& last, int num){
	for (int count=0; count<num; count++){
		deleteNode(first, last);
	}
}

