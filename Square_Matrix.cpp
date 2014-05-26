#include "Square_Matrix.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;


Square_Matrix::Square_Matrix() : size(0)
{
	// constructor - initialize values to 0
	size = 0;
	matrix = 0;
}

Square_Matrix::Square_Matrix(Square_Matrix& S_M_Object)
{
	// copy constuctor
	size = S_M_Object.Get_Size();
	if (size != 0)
	{
		matrix = new int*[size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new int[size];
		}

		// Copy the elements
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = S_M_Object.Get_Elem(i, j);
			}
		}
	}
}

Square_Matrix::~Square_Matrix()
{
	// destructor
	// release the allocated memory
	
	if (size > 0)
	{
		for (int d = 0; d < size; d++)
		{
			delete[] matrix[d];
		}
		delete[] matrix;

		size = 0;
	}
}


// functions
void Square_Matrix::Set_Size(int new_size)
{
	// allocate new memory and delete old if a new matrix
	if (size != 0)
	{
		// we have memory to delete
		for (int i = 0; i < size; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		size = 0;
	}

	// now create a new matrix
	matrix = 0; // just in case 

	matrix = new int *[new_size];
	for (int i = 0; i < new_size; i++)
	{
		matrix[i] = new int[new_size];
	}
	size = new_size;
}

int Square_Matrix::Get_Size()
{
	return size;
}

void Square_Matrix::Set_Elem(int number, int row, int column)
{
	matrix[row][column] = number;
}

int Square_Matrix::Get_Elem(int row, int column)
{
	return matrix[row][column];
}

bool Square_Matrix::operator==(Square_Matrix & object)
{
	if (size == object.Get_Size())
	{
		for (int i = 0; i < size; i++)
		{
			for (int b = 0; b < size; b++)
			{
				if (matrix[i][b] != object.Get_Elem(i, b))
				{
					return 0;
				}
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

 Square_Matrix Square_Matrix::operator+(Square_Matrix& object) 
{
	Square_Matrix sum;
	sum.Set_Size(size);
	object.Get_Size();
	for (int i = 0; i < size; i++)
	{
		for (int b = 0; b < size; b++)
		{
			sum.Set_Elem((matrix[i][b] + object.Get_Elem(i, b)),i, b);
		}
	}
	return sum;
}

 Square_Matrix& Square_Matrix::operator =(Square_Matrix& object)
 {
	 if (this == &object)
	 {
		 return *this;
	 }
	 else
	 {		 
		 
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				matrix[i][j] = object.Get_Elem(i, j);
			}
		}
		 return *this; 
	}
 }



// generator functions
void Square_Matrix::GenerateMatrix()
{
	printed = true;
	
	// generate RANDOM matrix of size "size"
	// assign numbers to a "list"
	int *list;
    list = new int [size + 1];

	// variable to store a random number
	int random_num;

	// now we are ready to generate the first row of numbers 
	// please note that the first row does not have to be checked against anything
	for(int row = 0; row < size; row++)
	{
		for(int i = 0; i < size; i++)
			list[i] = i+1;
		list[size] = 0;
		// now we have a list from 1 to size
		// we will use this list for filling in random variables	

		for(int column = 0; column < size; column++)
		{
			// get a random value from 1 to size - column
			random_num = rand() % (size - column); 

			// assign the new value to the matrix row row and column column
			matrix[row][column] = list[random_num];

			// now we have to move all the content of the list to the left most 
			// extreme of the value taken out. 
			for(int b = random_num; b < size; b++)
			{
				// copy content 
				list[b] = list[b+1];
			}

			// this system takes a random number from the list created before.
			// this way we cannot choose duplicates and random happens only once per loop
		}
	}

	// once all the rows are randomized, we have to "sort" them in a way that corresponds to the following rules:
	// check if the value corresponds to any other matrix[0 to row][column] value
	// if it doesnt, then we can assign it
	// if we have no more steps to go, backtrack
	// sorting will be accomplished using swapping 

	// create a check list of size size
	bool * check_list;
	check_list = new bool[size];

	// we start checking with row 1. we increment row at step 6 if we did not touch the swap function
	int row = 1;
	while (row < (size-1))
	{
		// we have to zero out the check_list before reusing it
		for (int i = 0; i < size; i++)
			check_list[i] = 0;

		// we start with column 0 and go all the way to column size
		// we increment column when we finish checking against all combinations of [0 to row-1][column]
		for (int column = 0; column < size; column++)
		{
			// we are at [row][column]. we have to check [row][column] against [0 to row][column]
			// r stands for the row that we are checking against
			for (int r = 0; r < row ; r++)
			{
				// if this is true, we can stop the loop and write 1 to check_list[column];
				//note: check_list[column] start with all values at 0 every time we run a new row check
				if (matrix[row][column] == matrix[r][column])
				{
					// we have a match, we need to swap this value
					check_list[column] = 1;
					// also, since we have a match we do not increment row.
				}
			}
			if (!printed)
			{
				// plase enable this if you want to generate a very large matrix 
				// although its not necessary, its nice to see the progress.
				// also, please note that I have tested with high numbers and relatively good running times. 
				// I came up with another algorithm for finding any size of a matrix with a Big 0 of n. 
				// but this needed backtracking or recursion, thus i did not include it. I would gladly
				// demonstrate it though. 

				//cout << "Progress Status, working on row " << row + 1 << " out of " << size << endl;
				printed = true;
			}

		}
		// we finished checking against all the values and now we have a populated check_list
		// now we can do the magic of swapping values and finding a new home for them.
		// if we swapped anything, we do not increment the row value
		// if we did not swap anything then we move on to the next row
		//cout<<"calling the Check The List function"<<endl;
		if (Check_The_List(check_list, row) == false)
		{
			row++;
			printed = false;
		}
		
	}
	Fill_In_Last(row);

	delete [] list;
	delete [] check_list;
	

	// sorted
	cout<<endl<<"Random Matrix"<<endl;
	for(int row = 0; row < size; row++)
	{
		for (int column = 0; column < size; column++)
		{
			if (size < 10)
			{
				cout << matrix[row][column] << " ";
			}
			else
			{
				if (matrix[row][column] > 9)
					cout << matrix[row][column] << "  ";
				else
					cout << matrix[row][column] << "   ";
			}
		}
		cout<<endl;
	}
}

// this function will return us a boolian
// if the boolian is TRUE then we should NOT increment row.
bool Square_Matrix::Check_The_List(bool * list, int row)
{
	// take the list and go through trying to find 1's
	// if no 1's are found then return false
	// if a 1 is found, call the swap function and return true

	// stores the amount of 1's in the list
    int amount = 0;
	// stores the first 1's position in the matrix
	int position = 0;

	//static int old_position; 
	//static int incrementation;

	for (int i = 0; i < size; i++)
	{
		// we have to go through the list and grab the first 1 we find. 
		// then we have to swap it with another 1 if possible, but before we do we 
		// have to make sure it can go there. if it cant, then we have to take the
		// next 1, if no 1's are avaliable then we have to swap it with a 0.
		if (list[i] == 1)
		{
			// we have a 1. increment 
			amount++;

		}
	}

	for (int i = 0; i < size; i++)
	{
		if (list[i] == 1)
		{
			// we have a 1. note its position
			position = i;
			break;

		}
	}

	// if position_i is > to old_position_i
	// then we need to backtrack and try swapping with another value.
	// if it is == we are ok, just swap the next element
	// if its less than the old one, we made progress and are going in the right direction
	// backtracking at its best.

	if (incrementation >= size)
	{
		// clear the old postion
		old_amount = 0;
		// clear the old_position 
		old_position = 0;
		// clear the incrementation
		incrementation = 0;
		return true;
	}

	if (amount == 0)
	{
		// this row is sorted.
		// clear the old postion
		old_amount = 0;
		// clear the old_position 
		old_position = 0;
		// clear the incrementation
		incrementation = 0;

		return false;
	}

	if (old_amount == 0)
	{
		// we never swapped this row yet. 
		// this is the first swap of the row. 
		Swap(position, incrementation, row);
		old_position = position;
		old_amount = amount;
		incrementation++;
		return true;
	}

	if (old_amount < amount)
	{
		// we need to backtrack since the old amount was less than the new one. 
		// but, if incrementation is bigger than size, then we have to backtrack even more.
		Swap(old_position, (incrementation - 1), row);
		return true;
		
	}
	if (old_amount == amount)
	{
		// do we need to backtrack? 
		Swap(position, incrementation, row);
		old_position = position;
		old_amount = amount;
		incrementation++;
		return true;
	}
	if (old_amount > amount)
	{
		// we made progress
		// start as if we never touched the row
		// clear the old postion
		old_amount = 0;
		// clear the old_position 
		old_position = 0;
		// clear the incrementation
		incrementation = 0;
		return true;
	}

	return true;
}

void Square_Matrix::Swap(int first, int second, int row)
{
	int temp = matrix[row][first];
	matrix[row][first] = matrix[row][second];
	matrix[row][second] = temp;
}

void Square_Matrix::Fill_In_Last(int row)
{
	int * list;
	list = new int[size];

	// populate a list with numbers from 1 to size
	for (int i = 0; i < size; i++)
	{
		list[i] = i+1;
	}

	for (int column = 0; column < size; column++)
	{
		for (int i = 0; i < (size-1); i++)
		{
			// the values that are present, will be set to 0
			list[(matrix[i][column]) - 1] = 0;			
		}

		for (int i = 0; i < size; i++)
		{
			// now look for the value that was left in the loop and assign it to the matrix[row][column]
 			if (list[i] != 0)
			{
				matrix[row][column] = list[i];
				break;
			}
		}

		//assign the number to the corresponding list spot
		for (int i = 0; i < size; i++)
		{
			list[i] = i + 1;
		}
	}
	delete[] list;
}
