//Ryan Huang
//CISP430
//Hanoi
#include <iostream>
using namespace std;

void tower(int disks, char src, char aux, char dest);

int count = 0;

int main(){
	int disks;
	cout<<"Enter number of disks: ";
	cin>>disks;
	tower(disks, 'A', 'B', 'C');
}

void tower(int disks, char src, char aux, char dest){
	if (disks==1){   //No Recursion
		count++;
   	cout<<count<<") move plate "<<src<<" to "<<dest<<endl;
   }else{   
		tower(disks-1, src, dest, aux);
		count++;
      cout<<count<<") move plate "<<src<<" to "<<dest<<endl;
      tower(disks-1, aux, src, dest);               
	}
}




