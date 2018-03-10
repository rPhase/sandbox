//Ryan Huang
//CISP430
//SplitMerge

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;
ofstream out;

struct nodeList{
	char name[20];
	struct nodeList* next;
};
typedef struct nodeList nodeList;

int clean();
void printList(nodeList*);
nodeList* build();
nodeList* buildTwo();
nodeList* addList(nodeList*&, char data[]);
int listLength(nodeList*);
nodeList* splitList(nodeList*&);
void mergeList(nodeList*&, nodeList*&);
void outputList(nodeList* current);

int main(){
	nodeList *myList, *myList2, *myList3, *myList4;
   in.open("inputSplit.txt");   
	out.open("outputSplit.txt");
	
	myList=build();
	cout<<"Before Split:"<<endl;
	cout<<"myList:"<<endl;
	printList(myList);
	myList2=splitList(myList);
	
	cout<<"After Split:"<<endl;
	cout<<"myList:"<<endl;
	printList(myList);
	outputList(myList);
	cout<<"myList2:"<<endl;
	printList(myList2);
	outputList(myList2);

	in.close();
	in.clear();
	out.close();
	out.clear();
	
	in.open("inputMerge.txt");  
	out.open("output.merge");
	
	myList3=buildTwo();
	myList4=splitList(myList3);
	cout<<"Before Merge:"<<endl;
	cout<<"myList3:"<<endl;
	printList(myList3);
	cout<<"myList4:"<<endl;
	printList(myList4);
	mergeList(myList3, myList4);
	
	cout<<"After Merge:"<<endl;
	cout<<"myList3:"<<endl;
	printList(myList3);
	cout<<"myList4:"<<endl;
	printList(myList4);
	
	outputList(myList3);
	
	in.close();
	out.close();
}

//Build the first List taking in which contain first names
nodeList* build(){
	nodeList dummy;
	dummy.next = NULL;
	nodeList* tail = &dummy;
	
	char A[20];
	while (clean() && in.good()){
		in>>A;
		tail = addList(tail->next, A);
	}
   return (dummy.next);
}

//Build a list which contains 5 cities
//Some cities have a space so entire line is fed (ex. San Francisco) 
nodeList* buildTwo(){
	nodeList dummy;
	dummy.next = NULL;
	nodeList* tail = &dummy;
	
	char A[20];
	while (clean() && in.good()){
		in.getline(A, 20);
		tail = addList(tail->next, A);
	}
   return (dummy.next);
}

nodeList* addList(nodeList*& tailNext, char data[]){
	nodeList* newNode = new nodeList;
	strcpy(newNode->name, data);
	newNode->next = NULL;
	tailNext = newNode;
	return tailNext;
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


void printList(nodeList* current){
	while ( current != NULL ) {
   	cout<< current->name<<endl;
   	current=current->next;
	}
	cout<<endl;
}

int listLength(nodeList* current){
	int count = 0;
	while ( current != NULL ) {
   	count++;
   	current=current->next;
	}
	return count;
}

//Split the even list in half
nodeList* splitList(nodeList*& head){
	nodeList* current = head;
	nodeList* newHead;
	int length = listLength(head);
	length= length/2;
	for (; length>1; length--){
		head=head->next;
	}
	newHead=head->next;
	head->next = NULL;
	head = current;
	
	return newHead;	
}

//Append second to end of first
void mergeList(nodeList*& first, nodeList*& second){
	nodeList* current = first;
	while ( first->next != NULL ) {
   	first=first->next;
	}
	first->next=second;
	first=current;
	second=NULL;
}

void outputList(nodeList* current){
	while ( current != NULL ) {
   	out<< current->name<<endl;
   	current=current->next;
	}
}
