//Ryan Huang
//CISP430
//Expressions

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;

//Queue containing a single char
struct qChar{
	char data;
	struct qChar* next;
};
typedef struct qChar qChar;

//Stack containing int
struct stackInt{
	int data;
	struct stackInt* next;
};
typedef struct stackInt stackInt;

//Stack containing char
struct stackChar{
	char data;
	struct stackChar* next;
};
typedef struct stackChar stackChar;

//Processing Prototypes
void readFile(stackChar*&, qChar*&, qChar*&);
int precedence(char);
void processOperator(stackChar*&, qChar*&, qChar*&, char);
void process(stackInt*&, int);
int evaluate(qChar*&, qChar*&);

//Stack function prototypes
void push(stackInt*&, int);
int pop(stackInt*&);
void push(stackChar*&, char);
char pop(stackChar*&);

//Queue function prototypes
void enqueue(qChar*&, qChar*&, char);
char dequeue(qChar*&, qChar*&);

//Print
void print(qChar*);
void print(stackInt*);
void printHex(int);



int main(){
	int number;
	char ch;
	stackInt *head = NULL;
	stackChar *top = NULL;
	qChar *front, *rear;
	front = rear = NULL;
	
	cout<<"Infix: ";
	readFile(top, front, rear);
	cout<<endl;
	cout<<"Postfix: ";
	print(front);
	number=evaluate(front, rear);
	cout<<number<<endl;
	process(head, number);
	cout<<"Hexadecimal: ";
	while (head!=NULL){
		printHex(pop(head));
	}
	cin.get();
}

//Evaluate the postfix equation
int evaluate(qChar*& front, qChar*& rear){
	stackInt *top = NULL;
	char ch;
	int A, B;
	while (front){
		ch = dequeue(front, rear);
		switch (ch){
		case '+':
			B = pop(top);
			A = pop(top);
			push(top, (A+B));
			break;
		case '-':
			B = pop(top);
			A = pop(top);
			push(top, (A-B));
			break;
		case '*':
			B = pop(top);
			A = pop(top);
			push(top, (A*B));
			break;
		case '/':
			B = pop(top);
			A = pop(top);
			push(top, (A/B));
			break;
		//Everything else assumed to be operands and pushed on to stack
		default:
			push(top, (int)(ch-'0'));
		}
	}
	return pop(top);
}

void print(qChar* current){
	while ( current != NULL ) {
   	cout<<current->data;
   	current=current->next;
	}
	cout<<endl;
}

void print(stackInt* current){
	while ( current != NULL ) {
   	cout<<current->data;
   	current=current->next;
	}
	cout<<endl;
}

void readFile(stackChar*& top, qChar*& front, qChar*& rear){
	char temp, ch;
	in.open("input.txt");
	while (in.good()){
		ch = in.get();
		if (ch != -1){	//Display the infix
			cout<<ch;
		}
		switch (ch){
		case 10:		//If new line
		case ' ':	//If space, don't do anything
			break;
		case -1:		//in.get() seems to return -1 when it hits the null terminator
			while (top!=NULL){
				temp=pop(top);
				enqueue(front, rear, temp);
			}
			break;
		//Check for Parenthesis
		case '(':	//Push open parenthesis on stack
			push(top, ch);
			break;
		case ')':	//pop and enqueue everything up to open parenthesis,
			while (top->data!='('){
				temp = pop(top);
				enqueue(front, rear, temp);
			}
			temp = pop(top);
			break;
		//Check for operators
		case '+':
		case '-':
		case '*':
		case '/':
			if (!top){ //Stack Empty, push on stack
				push(top, ch);
			}
			else{	//Stack not empty
				processOperator(top, front, rear, ch);
			}
			break;
		//Everything else assumed to be numbers
		default:	
			enqueue(front, rear, ch);
		}
	}
	in.close();
}

//Process the operators
void processOperator(stackChar*& top, qChar*& front, qChar*& rear, char ch){
	char result;
	int A = precedence(ch);	//Current
	int B = precedence(top->data);	//top of stack
	if (A<B){	//If current A is higher precedence
		push(top, ch);
	}
	else{
		while (A>=B&&top){	//If Current A is lower or equal
			result=pop(top);
			enqueue(front, rear, result);
			if (top){
				B = precedence(top->data);
			}
		}
		push(top, ch);
	}
}

//returns the precedence of the operators. Lower means higher precedence
int precedence(char ch){
	switch (ch){
	case '(':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 0;
	}
}

//Print hex numbers
void printHex(int number){
	switch (number){
	case 10:
		cout<<"A";
		break;
	case 11:
		cout<<"B";
		break;
	case 12:
		cout<<"C";
		break;
	case 13:
		cout<<"D";
		break;
	case 14:
		cout<<"E";
		break;
	case 15:
		cout<<"F";
		break;
	default:
		cout<<number;
	}
}

//Convert the integer into binary and push on stack
void process(stackInt*& top, int item){
	int result;
	while (item!=0){
		result = item%16;
		push(top, result);
		item=(item/16);
	}
}

//Push an char onto stack
void push(stackChar*& top, char item){
	stackChar *newNode = new stackChar;
	newNode->data = item;
	newNode->next=top;
	top=newNode;
}

//Pop an int off the stack, returns -1 if empty
char pop(stackChar *&top){
	stackChar *temp;
	char ch;
	if (top){
		ch=top->data;
		temp=top;
		top=top->next;
		delete temp;
		return ch;
	}
}

//Push an int onto stack
void push(stackInt*& top, int item){
	stackInt *newNode = new stackInt;
	newNode->data = item;
	newNode->next=top;
	top=newNode;
}

//Pop an int off the stack, returns -1 if empty
int pop(stackInt *&top){
	stackInt *temp;
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

//queue a char after the last element of the queue
void enqueue(qChar*& front, qChar*& rear, char item){
	qChar *newNode = new qChar;
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
char dequeue(qChar *&front, qChar *&rear){
	char ch;
	qChar *temp;
	if (front){
		ch=front->data;
		temp=front;
		front=front->next;
		delete temp;
		return ch;
	}
	if (!front){
		rear = NULL;
	}
}

