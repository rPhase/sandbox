//Ryan Huang
//CISP430
//Quick Sort Radix Sort

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

ifstream in;

struct node{
	int data;
	struct node* next;
};
typedef struct node node;

//Number of elements in the array, maximum of 10 elements
int SIZE = 0;

//Function Prototypes
int clean();
int readFile(int a[]);
void print(int a[]);
int findLargest(int a[]);
int countDigits(int);
void process(int a[]);
//Quicksort
void quickSort(int a[], int start, int end);
int partition(int a[], int first, int last);
//Stack
void setNull(node* top[]);
void push(node*&, int);
int pop(node*&);
void printList(node*);
void printStacks(node**);
//Radix
void radix(int a[]);

int main(){
	int array[10];
	SIZE=readFile(array);
	cout<<"SIZE:"<<SIZE<<endl;
	cout<<endl<<"Original:"<<endl;
	print(array);
	quickSort(array, 0, SIZE-1);
	cout<<endl<<"Quicksort(Descending):"<<endl;
	print(array);
	process(array);
	cout<<endl<<"Add 5:"<<endl;
	print(array);
	radix(array);
	cout<<endl<<"Radix Sort(Descending):"<<endl;
	print(array);
}

//============================================================================================
//Radix
void radix(int a[]){
	int M=10;
	int N=1;
	int MAX=a[findLargest(a)];
	int temp, count;
	node *top[10];
	setNull(top);
	
	while (N<MAX){
		for (int i=SIZE-1;i>=0;i--){
			temp=a[i]%M;
			temp = temp/N;
			push(top[temp], a[i]);
		}
		count=0;
		for (int i=9; i>=0; i--){
			while (top[i]){
				a[count]=pop(top[i]);
				count++;			
			}
		}
		M=M*10;
		N=N*10;
	}
}

//============================================================================================
//Stack
//Stack is used instead of queue for descending order
void setNull(node* top[]){
	for (int i=0;i<10;i++){
		top[i]=NULL;
	}
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
	}
	else{
		number=-1;
	}
	return number;
}


//Traverse and print the list
void printList(node* current){
	while ( current != NULL ) {
   	cout<<current->data<<" ";
   	current=current->next;
	}
	cout<<endl;
}
void printStacks(node* top[]){
	for (int i=0;i<10;i++){
		cout<<i<<":";
		printList(top[i]);
	}
}

//============================================================================================

//Add additional digits
void process(int a[]){
	int index_large, digit_large, digit_curr, diff;
	index_large=findLargest(a);
	digit_large=countDigits(a[index_large]);
	
	for (int i=0;i<SIZE;i++){
		if (i!=index_large){
			digit_curr=countDigits(a[i]);
			if (digit_curr<digit_large){
				diff = digit_large-digit_curr;
				//cout<<a[i]<<" is smaller than "<<a[index_large]<<" by "<<diff<<endl;
				for (int j=0; j<diff; j++){
					a[i]=a[i]*10;
					a[i]=a[i]+5;
				}
			}
		}
	}
}

//Find and return the index of the largest number
int findLargest(int a[]){
	int indexLargest=0;
	for (int i=1; i<SIZE; i++){
		if (a[i]>a[indexLargest]){
			indexLargest=i;
		}
	}
	return indexLargest;
}

//Return number of digits
int countDigits(int num){
	int count;
	if (num!=0){
		count=countDigits(num/10) + 1;
	}
	else{
		count=0;
	}
	return count;	
}

void print(int a[]){
	for (int i=0;i<SIZE;i++){
		cout<<a[i]<<" ";
	}
	cout<<endl;	
}

//============================================================================================
//Quick Sort
void quickSort(int a[], int start, int end){
    int pIndex;

    //if start= end, we have only one item. No sorting in needed. 
    //if start > end, then there is nothing to process
    if (start>=end)                          
 return;   
                   
    pIndex=partition(a,start,end);  //pIndex is used for partioning
	 quickSort(a, start, pIndex-1);  //To the left of the pivot
    quickSort(a, pIndex+1, end);    //To the right of the pivot
}

int partition(int a[], int first, int last){
    int pivot=last, lower=first, upper=last-1; 
   
    while (lower<=upper){            //While they don't cross over
	  //check the left handside against the pivot.
        while (a[lower]>=a[pivot] && lower<=upper)
            lower++;
        if (lower>upper)               //If cross over. pass is done.            
	        break;
        
        swap (a[lower],a[pivot]);      //swap the pivot
        pivot=lower;                   //identify new pivot location       
        lower++;               
	  
	  //Check the right hand side against the pivot. 
        while (a[upper]<=a[pivot] && upper>=lower)  
            upper--; 
        if (upper<lower)               //If cross over, pass done
           break;
        
        swap (a[upper],a[pivot]);      //swap the pivot
        pivot=upper;                   //identify new pivot location
        upper--;                                      
             
    }
    return pivot;
}

//============================================================================================

int readFile(int a[]){
	in.open("input.txt");
	int i = 0;
	while (clean() && in.good()){
		in>>a[i];
		i++;
	}
	in.close();
   return i;
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


