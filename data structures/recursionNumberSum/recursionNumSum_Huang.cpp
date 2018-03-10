//Ryan Huang
//CISP430
//Recursion Number Sum
#include <iostream>
using namespace std;

int recursiveSum(int number);

int main(){
	int input, sum;
	cout<<"Input a 4 digit number: ";
	cin>>input;
	sum=recursiveSum(input);
	cout<<"The sum of "<<input<<" is "<<sum<<endl;

}

int recursiveSum(int number){
	int result;
	if (number!=0){
		result=number%10+recursiveSum(number/10);
	}
	else{
		result=0;
	}
	return result;
}
