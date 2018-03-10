//Ryan Huang
//CISP430
//Recursion Commas
#include <iostream>
using namespace std;

void recursiveComma(long);

int main(){
	long input;
	cout<<"Input a number: ";
	cin>>input;
	cout<<"Output:";
	recursiveComma(input);
}

//Print a number with commas if needed. Can be negative. Must be within 10 digits.
void recursiveComma(long number){
	long result;
	if (number<0){
		number=number*-1;
		cout<<"-";
	}
	if (number<1000){
		cout<<number;
	}
	else{
		recursiveComma(number/1000);
		cout<<",";
		result=number%1000;
		if (result<100){
			cout<<"0";
			if (result<10){
				cout<<"0";
			}
			cout<<result;
		}
		else{
			cout<<result;	
		}
	}
}
