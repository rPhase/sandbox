//Ryan Huang
//CISP430
//Sort Array
#include <iostream>
using namespace std;

//Size of the two dimensional array defined
#define ROW 5
#define COL 4

void display(int array[][COL]);
void funcA(int array[][COL]);
void funcB(int array[][COL]);
void funcC(int array[][COL]);
void search(int array[][COL], int);

void bubble(int array[][COL], int, int);
void selection(int array[][COL], int, int);
void insertion(int array[][COL], int);

int main(){
	int array[ROW][COL] = {	{5, 3, 2, 16},
									{9, 8, 10, 17},
									{4, 7, 11, 18},
									{2, 5, 9, 12},
									{7, 9, 4, 10}};
									
	int number;
							
	cout<<"Print Array"<<endl;
	display(array);
	funcA(array);
	display(array);
	funcB(array);
	display(array);
	funcC(array);
	display(array);
	
	cout<<"Enter a number to search for in the 5th row: ";
	cin>>number;
	search(array, number);

}

//search for a number in the 5th row and display the column that contains the number
void search(int array[][COL], int num){
	bool found = false;
	int pos;
	for (int i=0; i<COL; i++){
		if (array[4][i]==num){
			found=true;
			pos = i;
			i=COL;
		}
	}
	if (found){
		cout<<"Found: "<<array[4][pos]<<" in POS: "<<pos<<endl;
		for (int R=0; R<ROW; R++){
			cout<<array[R][pos]<<endl;
		}
	}
	else{
		cout<<"Not Found"<<endl;
	}
}

//Display the two dimensional array
void display(int array[][COL]){
	for (int R=0; R<ROW; R++){
		for (int C=0; C<COL; C++){
			cout<<array[R][C]<<" ";
		}
		cout<<endl;
	}
}

//Function A, Bubble Sort on 1st column, ascending
void funcA(int array[][COL]){
	cout<<"Function A (Bubble Sort, Ascending)"<<endl;
	int limit = ROW - 1;
	bubble(array, limit, 0);
}

void bubble(int array[][COL], int limit, int pos){
	int temp, index;
	//Determine number of passes
	for (;limit > 0; limit--){
		for (index = 0; index<limit; index++){
			//Change relation operator to < for descending order
			if (array[index][pos]>array[index+1][pos]){
				//Swap array elements
				for (int C=0; C<COL; C++){
					temp = array[index][C];
					array[index][C]=array[index+1][C];
					array[index+1][C]=temp;
				}
			}
		}
	}
	
	
}
//Function B, Selection sort on 2nd column, descending
void funcB(int array[][COL]){
	cout<<"Function B (Selection Sort, Descending)"<<endl;
	int limit = ROW - 1;
	selection(array, limit, 1);
}
void selection(int array[][COL], int limit, int pos){
	int temp, index_largest, index;
	//Determine number of passes
	for (;limit >0; limit--){
		index_largest=0;
		//determine number of caparisons for each pass
		for (index = 1; index<=limit; index++){
			//< for descending order
			if (array[index][pos]<array[index_largest][pos]){
				index_largest=index;
			}
		}
		//Swap array elements
		if (limit !=index_largest){
			for (int C=0; C<COL; C++){
				temp=array[limit][C];
				array[limit][C]=array[index_largest][C];
				array[index_largest][C]=temp;
			}
			
		}
	}
}
//Function C, insertion sort 5th row, ascending
void funcC(int array[][COL]){
	cout<<"Function C (Insertion Sort, Ascending)"<<endl;
	insertion(array, 4);
}
void insertion(int array[][COL], int pos){
	int i, j, temp;
	for (i = 1; i < COL; i++){
		for (j=i; j>0 && array[pos][j]<array[pos][j-1];j--){
			for (int R = 0; R<ROW; R++){
				temp = array[R][j];
				array[R][j]=array[R][j-1];
				array[R][j-1]=temp;
			}
		}
	}
}




