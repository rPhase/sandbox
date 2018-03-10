//Ryan Huang
//CISP430
//Expression Tree

#include <iostream>
#include <string.h>
using namespace std;

struct tree{
	char item;
	struct tree *left;
	struct tree *right;
};
typedef struct tree tree;

//each element of the stack is a tree
struct stackTree{
	struct tree *item;
	struct stackTree *next;
};
typedef struct stackTree stackTree;

//Function Prototypes
tree *newTree(char);
int eval(int, int, char);
int postOrder(tree*);	
bool isOp(char);
void push(stackTree*&, tree*);
tree* pop(stackTree*&);
stackTree* process(char[]);
void printStack(stackTree*);
void printTree(tree *);
	
//Main function
int main(){
	char input[20];
	stackTree *top = NULL;
	cout<<"Input a postfix expression: ";
	cin>>input;
	top = process(input);
	cout<<"Evaluation: "<<postOrder(top->item)<<endl;
	printStack(top);
}

//Create a new tree
tree* newTree(char item){
	tree *newNode = new tree;
	newNode->item = item;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

//Process the input
stackTree* process(char input[]){
	tree *T1, *T2;
	stackTree *top = NULL;
	int i = 0;
	while (input[i] != '\0'){
		//Check if number
		if (!isOp(input[i])){
			T1 = newTree(input[i]);
			push(top, T1);
		}
		else{ //NOT a number
			T2 = newTree(input[i]);
			T2->right = pop(top);
			T2->left = pop(top);
			push(top, T2);
		}
		i++;
	}
	return top;
}

//Evaluate the tree
int postOrder(tree *leaf){
	int result;
	
	if (leaf==NULL) return 0;
	int left = postOrder(leaf->left);
	int right = postOrder(leaf->right);
	if (isOp(leaf->item)){
		return (eval(left, right, leaf->item));
	}
	else{
		return ((leaf->item)-'0');
	}
}

//Evaluate the expression
int eval(int left, int right, char op){
	int result = 0;
	switch (op){
		case '+':
			result = (left + right);
			break;
		case '-':
			result = (left - right);
			break;
		case '*':
			result = (left * right);
			break;
		case '/':
			result = (left / right);
			break;
	}
	return result;
}

//Return true if char is a operator
bool isOp(char A){
	bool Op = true;
	if (A>='0'&&A<='9'){
		Op = false;
	}
	return Op;
}

void printTree(tree *leaf){
	if (isOp(leaf->item)){
		cout<<"(";
	}
	if (leaf->left){
		printTree(leaf->left);
	}
	cout<<leaf->item;
	if (leaf->right){
		printTree(leaf->right);
	}
	if (isOp(leaf->item)){
		cout<<")";
	}
}

void printStack(stackTree *top){
	while (top){
		printTree(top->item);
		top=top->next;
	}
}

tree* pop(stackTree *&top){
	stackTree *temp;
	tree *leaf = NULL;
	if (top){
		leaf=top->item;
		temp=top;
		top=top->next;
		delete temp;
	}
	return leaf;
}

void push(stackTree*& top, tree *item){
	stackTree *newNode = new stackTree;
	newNode->item = item;
	newNode->next=top;
	top=newNode;
}

