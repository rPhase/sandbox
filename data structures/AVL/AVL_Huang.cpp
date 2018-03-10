//Ryan Huang
//CISP430
//AVL

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

ifstream in;
ofstream out;

//Binary Tree
struct BinaryTree{
	int item;
	int height;
	struct BinaryTree* left;
	struct BinaryTree* right;
};
typedef struct BinaryTree BinaryTree;

//Queue
struct node{
	BinaryTree* nodePtr;
	struct node* next;
};
typedef struct node node;

/*
==========================================================================================================
*/

//Function Prototypes
int clean();
void processFile(BinaryTree*&);
BinaryTree* newNode(int);
BinaryTree* insert_correct(BinaryTree*, int);

BinaryTree* rebalance(BinaryTree*);
BinaryTree* leftRotate(BinaryTree*);
BinaryTree* rightRotate(BinaryTree*);

int max(int, int);
int height(BinaryTree*);
int getBalance(BinaryTree*);

//Depth First Traversal
void preOrder(BinaryTree *root);
void inOrder(BinaryTree *root);
void postOrder(BinaryTree *root);

//Print Level
void printLevel(BinaryTree*);
void enqueue(node*&, node*&, BinaryTree*);
BinaryTree* dequeue(node*&, node*&);

/*
==========================================================================================================
*/

//Main Function
int main(){
	BinaryTree *root = NULL;
	processFile(root);
	out.open("output.txt");
	cout<<"preOrder:"<<endl<<"\t";
	out<<"preOrder:"<<endl<<"\t";
	preOrder(root);
	cout<<endl<<"inOrder:"<<endl<<"\t";
	out<<endl<<"inOrder:"<<endl<<"\t";
	inOrder(root);
	cout<<endl<<"postOrder:"<<endl<<"\t";
	out<<endl<<"postOrder:"<<endl<<"\t";
	postOrder(root);
	cout<<endl<<"printLevel:"<<endl;
	out<<endl<<"printLevel:"<<endl;
	printLevel(root);
	out.close();
}


/*
==========================================================================================================
*/

//Functions

//Print Level
void printLevel(BinaryTree *root){
	if (!root){
		cout<<"Empty"<<endl;
		return;
	}
	node *front, *rear;
	front = rear = NULL;
	int curNode = 1;
	int nextNode = 0;
	int level = 0;
	BinaryTree *temp;
	enqueue(front, rear, root);
	cout<<"Level "<<level<<": ";
	out<<"Level "<<level<<": ";
	while (curNode!=0){
		temp=dequeue(front, rear);
		cout<<temp->item<<"("<<temp->height<<","<<getBalance(temp)<<")"<<" ";
		out<<temp->item<<"("<<temp->height<<","<<getBalance(temp)<<")"<<" ";
		curNode--;
		if (temp->left){
			enqueue(front, rear, temp->left);
			nextNode++;
		}
		if (temp->right){
			enqueue(front, rear, temp->right);
			nextNode++;
		}
		if (curNode==0){
			curNode=nextNode;
			nextNode=0;
			cout<<endl;
			out<<endl;
			if (curNode!=0){
				level++;
				cout<<"Level "<<level<<": ";
				out<<"Level "<<level<<": ";
			}
		}
	}
}


//Process the file
void processFile(BinaryTree*& root){
	in.open("input.txt");
	char A[10];
	int key;
	while (clean() && in.good()){
		in>>A;
		//Insert nodes
		root=insert_correct(root, atoi(A));
	}
	in.close();
}

//Left Rotation
BinaryTree* leftRotate(BinaryTree *x){
	cout<<"Left Rotation on "<<x->item<<endl;
	BinaryTree *y = x->right;
	BinaryTree *temp = y->left;
	//Swap
	y->left = x;
	x->right = temp;
	//Update height
	x->height = max(height(x->left),height(x->right))+1;
	y->height = max(height(y->left),height(y->right))+1;
	return y;
}

//Right Rotation
BinaryTree* rightRotate(BinaryTree *y){
	cout<<"Right Rotation on "<<y->item<<endl;
	BinaryTree *x = y->left;
	BinaryTree *temp = x->right;
	//Swap
	x->right = y;
	y->left = temp;
	//Update height
	y->height = max(height(y->left),height(y->right))+1;
	x->height = max(height(x->left),height(x->right))+1;	
	return x;
}

//Rebalance
BinaryTree* rebalance(BinaryTree *node){
	node->height=max(height(node->left), height(node->right)) + 1;
	int balance = getBalance(node); //left - right
	
	//Rotation based on balance
	//Right Heavy
	if (balance < -1){
		//Right Child Left Heavy
		if (getBalance(node->right)>0){ 
			node->right=rightRotate(node->right);
		}
		return leftRotate(node);
	}
	//Left Heavy
	if (balance > 1){
		//Left Child right Heavy
		if (getBalance(node->left)<0){
			node->left=leftRotate(node->left);
		}
		return rightRotate(node);
	}
	return node;
}

//Insert
//non-tail recursive algorithm because of rebalance
BinaryTree* insert_correct(BinaryTree* leaf, int item) { 
	if (leaf == NULL) {// Insertion place found.
		return (newNode(item));
	}
	else if (item < leaf->item){
		leaf->left  = insert_correct(leaf->left, item); 
	}    
	else{
		leaf->right = insert_correct(leaf->right, item);
	}
	leaf=rebalance(leaf);
	return(leaf); 
}

//New Node
BinaryTree* newNode(int value){
	BinaryTree *node = new BinaryTree;
	node->item=value;
	node->height=0;
	node->left=NULL;
	node->right=NULL;
	return (node);
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

//Depth-First traversal
// A utility function to print preorder traversal of the tree.
void preOrder(BinaryTree *root){
    if(root != NULL){
        printf("%d ", root->item);
        out<<root->item<<" ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// A utility function to print inorder traversal of the tree.
void inOrder(BinaryTree *root){
    if(root != NULL){
        inOrder (root->left);
        printf("%d ", root->item);
        out<<root->item<<" ";
        inOrder (root->right);
    }
}

// A utility function to print postorder traversal of the tree.
void postOrder(BinaryTree *root){
    if(root != NULL){
        postOrder (root->left);
        postOrder (root->right);
        printf("%d ", root->item);
        out<<root->item<<" ";
    }
}

//queue an int after the last element of the queue
void enqueue(node*& front, node*& rear, BinaryTree* leaf){
	node *newNode = new node;
	newNode->nodePtr=leaf;
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
BinaryTree* dequeue(node *&front, node *&rear){
	BinaryTree* leaf;
	node *temp;
	if (front){
		leaf=front->nodePtr;
		temp=front;
		front=front->next;
		delete temp;
	}
	if (!front){
		rear = NULL;
	}
	return leaf;
}

//Return the max of two int
int max(int A, int B){
	if (A>B){
		return A;
	}
	else{
		return B;
	}
}
//Return height of tree
int height(BinaryTree* node){
	if (node){
		return node->height;
	}
	else{
		return -1;
	}
}
//Get balance factor
int getBalance(BinaryTree* node){
	if (node){
		return height(node->left) - height(node->right);
	}
	else{
		return -1;
	}
}

