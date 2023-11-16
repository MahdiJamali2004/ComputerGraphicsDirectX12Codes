
#include <iostream>
#include <iomanip>
using namespace std;

int** taranahde(int a[][4]);
int determinan4(int a[][4], int size);
int determinan3(int** a, int size);
void makoosMatrix(int a[][4]);
void printMatrixes(int a[][4]);
void printMatrixes(int** a);
int main()
{
	
	int b[4][4] = { {1,1,1,0},{1,2,1,3}, {2,2,3},{2,3} };
	cout << "we use matrix below to show functions you can change parameters of it : " << endl;
	printMatrixes(b);
	cout << endl;
	cout << "-----------------------------";
	cout << endl;
	cout << "The DeterminanMatrix below is : " << determinan4(b, 4) << endl << endl;
	printMatrixes(b);
	cout << endl;
	cout << "-----------------------------";
	cout << endl;
	cout << "The MakoosMatrix below is : " << endl;
	printMatrixes(b);
	cout << '1' << '/' << determinan4(b, 4) << '*' << endl ;   //ماتریس معکوس کامل نوشته شده ولی برای زیبایی به صورت روبه رو نمایش داده شده 
	printMatrixes(b);
	cout << endl;
	cout << "-----------------------------";
	cout << endl;
	cout << "matrix Taranahde is :  " << endl;
	printMatrixes(taranahde(b));

	
	
	

	
}

int** taranahde(int a[][4])
{
	int** result;
	result = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		result[i] = new int[4];
		for (int j = 0; j < 4; j++) {
			result[i][j] = a[j][i];
		}
	}
	return result;
}
int determinan3(int** a, int size)
{
	int sum = 0;
	int column = 0;
	int index = 0;
	int** helper;
	helper = new int* [size - 1];
	for (int j = 0; j < size - 1; j++)
		helper[j] = new int[size - 1];
	for (int i = 0; i < size; i++)
	{
		int row = 0;
	
		for (int j = 0; j < size -1 ; j++)
		{
			row++;
		
			for (int k = 0; k < size ; k++)
			{
				if (i == column)
				{
					column++;
					
				}
				else
				{
				
					helper[j][index++] = a[row][column++];
					
				}
			}
			column = 0;
			index = 0;




		}



		if (i % 2 == 0)
		{
			sum += a[0][i] * ((helper[0][0] * helper[1][1]) - (helper[0][1] * helper[1][0]));
		}
		else
		{
			sum += -a[0][i] * ((helper[0][0] * helper[1][1]) - (helper[0][1] * helper[1][0]));
		}
	}
	return sum;
}
void makoosMatrix(int a[][4])
{
	double determinan =  1/determinan4(a, 4);
	for (int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4 ; j++)
		{
			a[i][j] *= determinan;
		}
	}
}
int determinan4(int a[][4], int size)
{
	int sum = 0;
	int column = 0;
	int index = 0;
	int** helper;;
	helper = new int* [size - 1];
	for (int j = 0; j < size - 1; j++)
		helper[j] = new int[size - 1];
	
	
	
		
	
		for (int i = 0; i < size; i++)
		{
			int row = 0;

			for (int j = 0; j < size - 1; j++)
			{
				row++;

				for (int k = 0; k < size; k++)
				{
					if (i == column)
					{
						column++;

					}
					else
					{
						
						helper[j][index++] = a[row][column++];
						
					}
				}
				column = 0;
				index = 0;




			}

			if (i%2 == 0)
			{
				sum += a[0][i] * determinan3(helper, 3);
				
			}
			else 
			{
				sum += -a[0][i] * determinan3(helper, 3);
				
			}

			
			
		}
	
	return sum;
	
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
