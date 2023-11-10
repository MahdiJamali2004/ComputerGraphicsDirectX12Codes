

#include <iostream>
#include <iomanip>
using namespace std;

int** sumMatrixes(int a[][4], int b[][4]);

int** subtractionMatrixes(int a[][4], int b[][4]);

int** multiMatrixes(int a[][4], int b[][4]);

void printMatrixes(int a[][4]);
void printMatrixes(int **a);

int main()

{


	int a[4][4] = { {3,2,2,2},{1,2,2}, {3,2,3},{2,3,2,1} };
	int b[4][4] = { {1,1,2,2},{1,2}, {2,2,3},{2,3} };
	cout << "matrix A is : " << endl << endl ;
	printMatrixes(a);
	cout << "-----------------------------" << endl;
	cout << "matrix B is : " << endl << endl;
	printMatrixes(b);
	cout << "-----------------------------" << endl;
	cout << " the sum of Matrixes is : " << endl << endl;
	printMatrixes(sumMatrixes(a, b));
	cout << "-----------------------------" << endl;
	cout << " the subtraction of Matrixes is : " << endl << endl;
	printMatrixes(subtractionMatrixes(a, b));
	cout << "-----------------------------" << endl;
	cout << " the multi of Matrixes is : " << endl << endl;
	printMatrixes(multiMatrixes(a, b));
 cout << "-----------------------------" << endl;
	
	
}

int** sumMatrixes(int a[][4], int b[][4])
{

	int** result ;
	result = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		result[i] = new int[4];
		for (int j = 0; j< 4; j++)
		{
			result[i][j] = a[i][j] + b[i][j];
		}
	}

	return result;
}
int** subtractionMatrixes(int a[][4], int b[][4])
{

	int** result;
	result = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		result[i] = new int[4];
		for (int j = 0; j < 4; j++)
		{
			result[i][j] = a[i][j] - b[i][j];
		}
	}

	return result;
}
int** multiMatrixes(int a[][4], int b[][4])
{

	int** result;
	result = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		result[i] = new int[4];
		for (int j = 0; j < 4; j++)
		{
			int sum = 0;
			for (int k = 0; k < 4; k++)
			{
				sum += a[i][k] * b[k][j];
			}
			result[i][j] = sum;
		}
	}

	return result;
}
void printMatrixes(int a[][4])
{
	for (int i = 0; i < 4; i++)
	{
		cout << ' ';
		cout << left << setw(3) << setfill(' ') << '|';
		
		for (int j = 0; j < 4; j++) 
		{
			cout << left << setw(3) << setfill(' ') << a[i][j];
		}
		cout << left << setw(3) << setfill(' ') << '|';
		cout << endl;
		cout << endl;
	}
}
void printMatrixes(int** a)
{
	for (int i = 0; i < 4; i++)
	{
		cout << ' ';
		cout << left << setw(3) << setfill(' ') << '|';

		for (int j = 0; j < 4; j++)
		{
			cout << left << setw(3) << setfill(' ') << a[i][j];
		}
		cout << left << setw(3) << setfill(' ') << '|';
		cout << endl;
		cout << endl;
	}
}
