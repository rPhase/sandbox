//Ryan Huang
//CISP430
//Stacks

#include <iostream>
using namespace std;

struct node{
	int data;
	struct node* next;
};
typedef struct node node;

int process(node*&, int);
void push(node*&, int);
int pop(node*&);

int main(){
	int input, number, size ;
	node* top = NULL;
	
	cout<<"Input an integer to convert into binary: ";
	cin>>input;
	
	size = process(top, input);

	cout<<"size:"<<size<<endl;
	
	for (int i=0;i<size;i++){
		number = pop(top);
		cout<<number;
	}
	cout<<endl;
}

//Convert the integer into binary and push on stack
int process(node*& top, int item){
	int result;
	int size = 0;
	while (item!=0){
		result = item%2;
		push(top, result);
		item=(item/2);
		size++;
	}
	return size;
}

//Push an int onto stack
void push(node*& top, int item){
	node *newNode = new node;
	newNode->data = item;
	newNode->next=top;
	top=newNode;
}

//Pop an int off the stack, returns -1 if empty
int pop(node *&top){
	node *temp;
	int number;
	if (top){
		number=top->data;
		temp=top;
		top=top->next;
		delete temp;
		return number;
	}
	else{
		return (-1);
	}
}

