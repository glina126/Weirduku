#ifndef SQAREMATRIX
#define SQAREMATRIX

class Square_Matrix{
private:
	int **matrix;
	int size;
	int old_amount;
	int old_position;
	int incrementation;
	bool printed;
public:
	// default constructor
	Square_Matrix();
	// copy constructor
	Square_Matrix(Square_Matrix& S_M_Object);
	// destructor
	~Square_Matrix();
	// functions:
	void Set_Size(int);
	int Get_Size();
	void Set_Elem(int, int, int);
	int Get_Elem(int, int);
	// overload functions
	bool operator==( Square_Matrix &);
	Square_Matrix operator+(Square_Matrix &);
	Square_Matrix& operator =(Square_Matrix &);
	// generator functions
	void GenerateMatrix();
	bool Check_The_List(bool * list, int row);
	void Swap(int,int,int);
	void Fill_In_Last(int);
};
#endif