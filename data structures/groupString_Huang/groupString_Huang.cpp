//Ryan Huang
//CISP430
//Group 1 Strings

#include <iostream>
#include <fstream>
using namespace std;

//Place these at the global level
ifstream in("input.txt");		//input.txt is the file that we read from
ofstream out("output.txt");	//output.txt is the file that we write into

//This function looks ahead to get rid of all extra characters, such as new lines, spaces, tabs  
//and single line comments.


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


void stringCopy(char *A, char *B);
bool stringCompare(char *A, char *B);
void stringConcatenation (char *A, char *B);
int stringPosition(char *A, char B);
int stringLength(char *A);


int main(){
   //char from[10], to[10];
   //double distance;
	
	int size =10;
	
	char A[size];
	char B[size];
	char C[size];
	char D[size];
	char E[size];
	char F[size];
	char G[size];
	char H[size];
	char I[size];
	
	
	/*
   // can use in.good() to check if for end of file   
    while (clean() && in.good()){
        in >>from>> to >> distance;
       out<<from<<"  "<<to<<"  "<< distance <<endl;
    }
    */
    

   while (clean() && in.good()){
		in >> A >> B >> C >> D >> E >> F >> G >> H >> I;
	}
   
	 
   cout<<"A is " << A << endl;
	cout<<"B is " << B << endl;
	cout<<"C is " << C << endl;
   cout<<"D is " << D << endl;
	cout<<"E is " << E << endl;
	cout<<"F is " << F << endl;
   cout<<"G is " << G << endl;
	cout<<"H is " << H << endl;
	cout<<"I is " << I << endl;
	cout<<endl<<endl;
	
	//String Copy
	stringCopy(A, B);
	cout<<"String Copy B to A"<<endl;
	cout<<"A is " << A << endl;
	cout<<"B is " << B << endl;
	cout<<endl<<endl;
	
	//String Compare
	cout<<"Compare C to D"<<endl;
	if (stringCompare(C, D)){
		cout<<"TRUE"<<endl;
	}
	else{
		cout<<"FALSE"<<endl;
	}
	cout<<"C is " << C << endl;
   cout<<"D is " << D << endl;
	cout<<endl<<endl;
	
	//String Concatenation
	cout<<"Combine E and F"<<endl;
	stringConcatenation(E,F);
	cout<<"E is " << E << endl;
	cout<<"F is " << F << endl;
	cout<<endl<<endl;
		
	//String Position (Zero index)
	cout<<"Location of H in G (zero index):"<<stringPosition(G, *H)<<endl;
	cout<<"G is " << G << endl;
	cout<<"H is " << H << endl;
	cout<<endl<<endl;
		
	//String Length
	cout<< "Length of I:" << stringLength(I)<<endl;
	cout<<"I is " << I << endl;
	cout<<endl<<endl;


	out<<A<<" "<<B<<endl<<C<<" "<<D<<endl<<E<<" "<<F<<endl<<G<<" "<<H<<endl<<I;

	//Remember to close
	in.close();
   out.close();    
   
   cin.get();
}

//Replace contents of string A with contents of string B
void stringCopy(char *A, char *B){
	while (*B != '\0'){
		*A = *B;
		A++;
		B++;
	}	
	//Terminate with null char
	*A='\0';
}

//Compare A and B, return 1 if strings are exactly the same, 0 if not
bool stringCompare(char *A, char *B){
	while (*A != '\0'){
		if (*A == *B){
			A++;
			B++;
		}
		else{
			return false;
		}
	}
	
	if (*A=='\0' && *B=='\0'){
		return true;
	}
	else{
		return false;
	}
}

//Append B to the end of A
void stringConcatenation (char *A, char *B){
	while (*A != '\0'){
		A++;
	}
	while (*B != '\0'){
		*A = *B;
		A++;
		B++;
	}
	//Terminate with null char
	*A='\0';
}

//return position of first occurrence of character, return -1 if not found
int stringPosition(char *A, char B){
	int num = 0;
	while (*A != '\0'){
		if (*A==B){
			return num;
		}
		A++;
		num++;
	}
	//Reached null character without finding character
	return -1;
}

//shift all characters to the right by one and store length of string in position 0
int stringLength(char *A){
	int len = 0;
	char *copy, temp;
	copy = A;	
	
	while (*copy != '\0'){
		copy++;
		len++;
	}
	
	for (int i=len; i >= 0; i--){
		temp=*(A+i);
		*(A+i+1)=temp;
	}
	//0 starts at 48
	*A=len+48;
	return ((int)*A)-48;
}










