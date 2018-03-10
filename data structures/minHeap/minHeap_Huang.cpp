//Ryan Huang
//CISP430
//Heap

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
using namespace std;

ifstream in;
ofstream out;

#define MAX 8
int SIZE = MAX;
int array[MAX+1];

/*
==========================================================================================================
*/

//Function Prototypes
int clean();
void processFile();
void siftUp(int);
void siftDown(int);
void deleteNode(int);
void print();
void printLevel();
int min(int A, int B);

/*
==========================================================================================================
*/

//Main Function
int main(){
	cout<<"Initial heap"<<endl<<endl;
	processFile();
	print();
	printLevel();
	cout<<"Delete from heap"<<endl<<endl;
	deleteNode(5);
}


/*
==========================================================================================================
*/

//Functions

void print(){
	for (int i=1; i<SIZE+1; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl<<endl;
}

void printLevel(){
	int level = 0;
	int nodePerLevel=1;
	int totalNodes = 1;
	cout<<"Level "<<level<<": ";
	for (int i=1; i<SIZE+1; i++){
		cout<<array[i]<<" ";
		if (i==totalNodes){
			level++;
			nodePerLevel = nodePerLevel*2;
			totalNodes = totalNodes + nodePerLevel;
			if (i<SIZE){
				cout<<endl<<"Level "<<level<<": ";
			}
			
		}
	}
	cout<<endl<<endl;
}

//After the item has been inserted at the end, call this function
void siftUp(int nodeIndex) {
	//figure out parent index
	int parentIndex = nodeIndex/2;
	//if parent is bigger, then swap and siftUp parentindex 
	if (array[parentIndex] > array[nodeIndex]){
		int temp = array[parentIndex];
		array[parentIndex]=array[nodeIndex];
		array[nodeIndex]=temp;
		if (parentIndex>0){	//if not root, siftup
			siftUp(parentIndex);
		}
	}
}

//First remove item from beginning, then move last item to the root 
//position and finally call this function
void siftDown(int parent) {
	// figure out which child is bigger
	int leftIndex = 2*parent;
	int rightIndex = 2*parent+1;
	int smallest;
   if (rightIndex >= SIZE){
   	if (leftIndex >= SIZE){
   		return;
   	}
   	smallest = leftIndex;
   }
   else{
   	smallest=min(leftIndex,rightIndex);
   }
   
   // if the parent is > smallest child, then swap and siftDown on the 
   // index of the smallest child
   if (array[parent]>array[smallest]){
   	int temp = array[parent];
   	array[parent]=array[smallest];
   	array[smallest]=temp;
   	siftDown(smallest);
   }
}

//Delete items
void deleteNode(int itemsToDel){
	for (int i=1; i<itemsToDel+1; i++){
		array[1]=array[SIZE];
		SIZE--;
		siftDown(1);
		printLevel();
	}
}

//Process the file
void processFile(){
	in.open("input.txt");
	int key;
	//Start at index 1
	int i=1;
	while (clean() && in.good()){
		in>>key;
		//Insert nodes
		array[i]=key;
		siftUp(i);
		i++;
	}
	in.close();
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

//Return the min index
int min(int A, int B){
	if (array[A]>array[B]){
		return B;
	}
	else{
		return A;
	}
}

