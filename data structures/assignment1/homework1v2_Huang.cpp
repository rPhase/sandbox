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
	char data[10];
	struct nodeScore* next;
};
typedef struct nodeScore nodeScore;

/*
==========================================================================================================
*/

//Function Prototypes
int clean();
void processFile(nodeStudent*&, nodeStudent*&);
void addStudent(nodeStudent*&, nodeStudent*&, char name[]);
void printList(nodeStudent*);
void printListRev(nodeStudent*);
nodeScore* processScores();
void addScore(nodeScore*&, char score[]);
void printScores(nodeScore*);
void deleteStudent(nodeStudent*&, nodeStudent*&, char name[]);
void deleteScore(nodeScore*&);
nodeStudent* search(nodeStudent *, char name[]);
void deleteScores(nodeScore*&);
void outputFile(nodeStudent*, nodeStudent*);
void outputScores(nodeScore*);

/*
==========================================================================================================
*/

//Main Function
int main(){
	nodeStudent *head, *tail = NULL;
	processFile(head, tail);
	cout<<"Ascending Order:"<<endl;
	printList(head);
	cout<<endl<<"=================================================================="<<endl;
	cout<<endl<<"Descending Order:"<<endl;
	printListRev(tail);
	outputFile(head, tail);
}


/*
==========================================================================================================
*/

//Functions

//Process the file, create a list, and call functions as needed.
void processFile(nodeStudent*& head, nodeStudent*& tail){
	in.open("input.txt");
	char A[20];
	while (clean() && in.good()){
		in>>A;
		if (strcmp(A, "delete")==0){
			//call delete
			in>>A;
			deleteStudent(head, tail, A);
		}
		else{
			//create nodes
			addStudent(head, tail, A);
		}
	}
	in.close();
}

//Output the file
void outputFile(nodeStudent* head, nodeStudent* tail){
	out.open("output.txt");
	while ( head != NULL ) {
   	out<< head->firstName<<" ";
   	outputScores(head->scorePtr);
   	head=head->next;
	}
	out<<"=================================================================="<<endl;
	while ( tail != NULL ) {
   	out<< tail->firstName<<" ";
   	outputScores(tail->scorePtr);
   	tail=tail->prev;
	}
	out.close();
}

//Delete Students
//If student is found, delete the node, also call delete for scores. Otherwise do nothing.
void deleteStudent(nodeStudent*& head, nodeStudent*& tail, char name[]){
	nodeStudent *current;
	current = search(head, name);
	if (current){
		if (current==head){
			if (current!=tail){
				head=head->next;
				head->prev=NULL;
			}
		}
		else if (current==tail){
			tail=tail->prev;
			tail->next=NULL;
		}
		else{
			current->prev->next=current->next;
			current->next->prev=current->prev;
		}
		deleteScores(current->scorePtr);
		delete current;
	}
	else{
		cout<<"Not found."<<endl;
	}
}

//Search for student, return NULL if not found
nodeStudent* search(nodeStudent *head, char name[]){
	while (head != NULL){
		if (strcmp(head->firstName, name)==0){
			break;
		}
		else{
			head=head->next;
		}
	}
	return head;	
}

//Delete Scores
void deleteScores(nodeScore*& score){
	nodeScore *temp, *current;
	current = score;
	while (current != NULL){
		temp=current;
		current=current->next;
		delete temp;
	}
}

//Add Students
//Will create a new list or insert node into the list in sorted order
void addStudent(nodeStudent*& origin, nodeStudent*& current, char name[]){
	nodeStudent* newNode = new nodeStudent;
	nodeStudent* head = origin;
	strcpy(newNode->firstName, name);
	newNode->scorePtr = processScores();
	
	//If nothing in the list, set newNode as the first element in the list
	if (!current){
		newNode->next=NULL;
		current=newNode;
		origin=current;
	}
	else{	//The list is not empty
			//Check if new node goes before or after first node of the list
		if (strcmp(head->firstName, name)>0){
			//Insert new node before first node and set current
			newNode->next = head;
			newNode->prev = NULL;
			origin->prev=newNode;
			origin = newNode;
		}
		else{	//new node will go after the first node
				//Check if new node goes before or after next node
			while((strcmp(head->firstName, name)<0)&&!(head->next==NULL)){
				head=head->next;
			}
			if (head->next==NULL){	//If current node is the last, insert new node as the last node
				newNode->prev = head;
				newNode->next = NULL;
				head->next = newNode;
				current = newNode;
			}
			else{
				//Insert new node in middle
				newNode->prev = head->prev;
				newNode->next = head;
				head->prev->next = newNode;
				head->prev = newNode;
			}
		}
	}	
}

//Read the scores into a list, stop when "end" is reached
nodeScore* processScores(){
	nodeScore dummy;
	nodeScore* tail = &dummy;
	char score[10];
	in >> score;
	while (in.good()&&strcmp(score, "end")!=0){
		addScore(tail, score);
		in >> score;
	}
	return dummy.next;
}

//Add score as the next node
void addScore(nodeScore*& tail, char score[]){
	nodeScore* newNode = new nodeScore;
	strcpy(newNode->data, score);
	newNode->next = NULL;
	tail->next = newNode;
	tail = newNode;
}

//Print the list
void printList(nodeStudent* current){
	while ( current != NULL ) {
   	cout<< current->firstName<<" ";
   	printScores(current->scorePtr);
   	current=current->next;
	}
}

//Print the list in reverse
void printListRev(nodeStudent* current){
	while ( current != NULL ) {
   	cout<< current->firstName<<" ";
   	printScores(current->scorePtr);
   	current=current->prev;
	}
}

//Print the scores
void printScores(nodeScore* current){
	while ( current != NULL ) {
   	cout<< current->data<<" ";
   	current=current->next;
	}
	cout<<endl;
}

//Output the scores
void outputScores(nodeScore* current){
	while ( current != NULL ) {
   	out<< current->data<<" ";
   	current=current->next;
	}
	out<<endl;
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
