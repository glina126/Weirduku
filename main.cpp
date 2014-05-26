#include "Square_Matrix.h"
#include <iostream>
#include<time.h>
using namespace std;

/*
ASIGMENT 
Your program asks user to input integer number N. 

Then program creates square grid of size N by N and fills 
it randomly with a numbers from 1 to N in such a way that 
the same number is never seen twice in the same row or the 
same column (obviously, each number will be seen in a grid multiple times).

Your program got to show different random solutions for the problem. 
In other words, if I execute your program few times with a same input
parameter, each time I should see different (but still correct) answer.
Your algorithm MUST use recursion OR backtracking OR both. Please
state what you are trying to use in the comments in the beginning of 
the program.

Memory for the grid to be filled should be allocated dynamically. 
If you want to, you can use YOUR (only your own) class and include
files created in a previous homework assignment. In this case dont
forget to include header and cpp-file together with your assignment submission.

*/

// global variables
int size = 0;

Square_Matrix matrix;


int main()
{
	while(1)
	{
		cout<<"Enter -99 to Quit or Enter Matrix Size: ";
		cin>> size;

		if(size == -99)
		{
			cout<<"Good Bye"<<endl;
			break;
		}
		while(size <= 0)
		{
			size = NULL;
			cout<<"Size has to be greater than 0, enter size: ";
			cin>>size;
		}
		if(size > 20)
		{
			cout<<"\nPlease note that due to size restrictions of the console,\nthe matrix might not appear properly "<<endl;
			system("pause");
		}
		cout<<"\nGreat! Generating matrix" <<endl <<endl;

		// allocate an empty matrix filled with 0's 
		// 0's will be a good way to tell if we should compare it or not
		matrix.Set_Size(size);

		// now fill it with 0's
		for(int i = 0; i < size; i++)
		{
			for(int b = 0; b < size; b++)
			{
				matrix.Set_Elem(0,i,b);
			}
		}

		// change the random seed
		srand(time(NULL));
		// do the generating magic here
		matrix.GenerateMatrix();
		cout<<endl;
	}

	system("pause");
	return 0;
}