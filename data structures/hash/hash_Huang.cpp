//Ryan Huang
//CISP430
//Hash

#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

ifstream in;

#define SIZE 10
int collision = 0;

/*
==========================================================================================================
*/

//Function Prototypes
int clean();
void processFile(int*, bool*);
void print(bool*);
void print(int*);
void setStatus(bool*, bool);
void insert(int*, bool*, int);
int modulo(int);
int dblHash(int, int);
int linearProbe(bool*, int);
void search(int*, int);
void linearSearch(int*, int, int);

/*
==========================================================================================================
*/

//Main Function
int main(){
	int table[SIZE] = {0};
	bool tableStatus[SIZE] = {false};	//Parallel array to track filled slots, 1 means filled.
	int input;
	processFile(table, tableStatus);
	
	while(input!=-1){	//input -1 to exit loop
		cout<<"Enter a value to search (input -1 to exit loop):";
		cin>>input;
		search(table, input);
	}
}


/*
==========================================================================================================
*/

//Functions

//Print status
void print(bool *array){
	for (int i=0; i<SIZE; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl<<endl;
}

//print array
void print(int *array){
	for (int i=0; i<SIZE; i++){
		cout<<array[i]<<" ";
	}
	cout<<endl<<endl;
}

//Set the entire array to true or false
void setStatus(bool *array, bool option){
	for (int i=0;i<SIZE;i++){
		array[i]=option;
	}
}

//Search
void search(int *table, int input){
	int index = modulo(input);
	if (table[index]==input){
		cout<<"Found "<<input<<" at index "<<index<<endl;
	}
	else{
		index = dblHash(input, index);
		if (table[index]==input){
			cout<<"Found "<<input<<" at index "<<index<<endl;
		}
		else{
			linearSearch(table, index, input);
		}
	}
}

//linear probe search
void linearSearch(int *table, int index, int input){
	int i = index;
	do{
		if (i==SIZE-1){
			i=0;
		}
		else{
			i++;
		}
	}	
	while (table[i]!=input&&i!=index);
	if (i==index){
		cout<<"Not Found."<<endl;
	}
	else{
		cout<<"Found "<<input<<" at index "<<i<<endl;
	}

}

//Insert
void insert(int* table, bool *status, int item){
	int index = modulo(item);
	if (status[index]==true){
		collision++;
		index = dblHash(item, index);
		if (status[index]==true){
			collision++;
			index = linearProbe(status, index);
		}
	}
	table[index]=item;
	status[index]=true;
}

//modulo-division hashing
int modulo(int item){
	return (item%(SIZE-1))+1;
}

//double hashing
int dblHash(int item, int key){
	if (key==0){
		key++;
	}
	return (key-(item%key));
}


//Linear Probe
int linearProbe(bool *status, int key){
	int i = key;
	if (i==SIZE-1){
		i=0;
	}
	else{
		i++;
	}
	while(i!=key && status[i]==true){
		collision++;
		i++;
		if (i==SIZE-1){
			i=0;
		}
	}
	return i;
}

//Process the file
void processFile(int *table, bool *status){
	in.open("input.txt");
	int item;

	while (clean() && in.good()){
		in>>item;
		//Insert nodes
		cout<<"Inserting "<<item<<endl;;
		insert(table, status, item);
		cout<<"Collisions:"<<collision<<endl;
		print(table);
		print(status);
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



