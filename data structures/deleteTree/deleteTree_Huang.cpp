//Ryan Huang
//CISP430
//Delete Tree

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
bool searchNoRecursion(BinaryTree*, int);
void deleteNode(BinaryTree*&, int);
BinaryTree* remove(BinaryTree*, int);

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
		cout<<temp->item<<" ";
		out<<temp->item<<" ";
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
		if (strcmp(A, "delete")==0){
			//call delete
			in>>A;
			key=atoi(A);
			if (searchNoRecursion(root, key)){
				//deleteNode(root, key);
				root=remove(root, key);
			}
			else{
				root=insert_correct(root, key);
			}
		}
		else{
			//Insert nodes
			root=insert_correct(root, atoi(A));
			
		}
	}
	in.close();
}

//Insert
//It travels down until it gets to the bottom of the tree, creates node and 
//then goes back up to connect it to the tree
BinaryTree* insert_correct(BinaryTree* leaf, int item) { 
  if (leaf == NULL) {// Insertion place found.
		leaf = newNode(item);
  } else if (item <= leaf->item) 
        leaf->left  = insert_correct(leaf->left, item); 
    else 
        leaf->right = insert_correct(leaf->right, item);
  return(leaf); 
}

//New Node
BinaryTree* newNode(int value){
	BinaryTree *node = new BinaryTree;
	node->item=value;
	node->left=NULL;
	node->right=NULL;
	return (node);
}

//Remove
BinaryTree* remove(BinaryTree* root, int item){
	BinaryTree *temp = NULL;
	if (root==NULL){
		return root;
	}
	if (item == root->item){
		if (root->left==NULL){
			temp=root->right;
			delete root;
			return temp;
		}
		else if (root->right==NULL){
			temp=root->left;
			delete root;
			return temp;
		}
		else{
			temp=root->right;
			while (temp->left!=NULL){
				temp=temp->left;
			}
			root->item=temp->item;
			root->right=remove(root->right, temp->item);
		}
	}
	else if(item<root->item){
		root->left=remove(root->left, item);
	}
	else if(item>root->item){
		root->right=remove(root->right, item);
	}
	return root;
}


//Delete
void deleteNode(BinaryTree*& root, int item){
	bool found=false;
	BinaryTree *parent, *leaf, *temp;
	leaf=root;	

	while (leaf!=NULL && !found){
		if (item==leaf->item){
      	found=true;
		}
		else if (item < leaf->item){
			parent=leaf;
			leaf=leaf->left; 
		}      	
      else{
      	parent=leaf;
      	leaf=leaf->right;
      }
   }
   
	//One or no children
   if (leaf->left==NULL){
   	if (parent->left==leaf){
   		parent->left=leaf->right;
   	}
   	else{
   		parent->right=leaf->right;
   	}
   	delete leaf;
   }
   else if (leaf->right==NULL){
   	if (parent->left==leaf){
   		parent->left=leaf->left;
   	}
   	else{
   		parent->right=leaf->left;
   	}
   	delete leaf;
   }
   //Two Children
   else{
   	int num;
   	cout<<"Two children"<<endl;
   	temp=leaf->right;
		while (temp->left!=NULL){
   		temp = temp->left;
   	}
   	num=temp->item;
   	deleteNode(root, num);
   	leaf->item=num;

   }
}

//Search
bool searchNoRecursion(BinaryTree *leaf, int item){
	bool found=false;
    //use a while loop and not recursion. Leaf is being changed
    //each and every time to point to the left or right, going down
    //the tree.
	while (leaf!=NULL && !found){
		if (item==leaf->item){
      	found=true;
		}
		else if (item < leaf->item){
			leaf=leaf->left; //replaces recursion
		}      	
      else{
      	leaf=leaf->right;
      }
         
    }
    return found;
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


