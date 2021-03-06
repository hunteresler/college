/*Author:  Hunter Esler
 *  *Course:  CSCI 3080
 *   *Lab number: Lab 2
 *    *Purpose: This lab will take 2 matrices as input and A S or M as input to output a resulting matrix.
 *    		 *Due date: Jan 25, 2018
 *    		 */

//Includes
#include <iostream>

using namespace std;

//Add 2 matrices together, parameters: firstx, firsty, secondx, secondy, first matrix, second matrix. Returns success
bool addMatrix(int, int, int, int, int[10][10], int[10][10]);

//Subtract 2 matrices, parameters: firstx, firsty, secondx, secondy, first matrix, second matrix. Returns success
bool subMatrix(int, int, int, int, int[10][10], int[10][10]);

//Multiply 2 matrices together, parameters: firstx, firsty, secondx, secondy, first matrix, second matrix. Returns success
bool multMatrix(int, int, int, int, int[10][10], int[10][10]);
//Required Main function
int main()
{
	//Incrementing variables for loops
	int i, j, k;

	//Dimensions of first matrix, x is rows, y is columns
	int fx, fy;
	//Dimensions of second matrix, x is rows, y is columns
	int sx, sy;
	
	//Matrices, max 10x10
	int first[10][10];
	int second[10][10];
	
	//Add/Subtract/Multiply - A/S/M
	char operation;

	//Matrix A row and column size input from user
	cout << "input the row size and col size of A\n";
	cin >> fx >> fy;

	//Matrix A inputs from user
	cout << "input mstrix A\n";
	for (i = 0; i < fx; i++) {
		for (j = 0; j < fy; j++) {
			cin >> first[i][j];
		}
	}

	
	//Matrix B row and column size input from user
	cout << "input the row size and col size of B\n";
	cin >> sx >> sy;

	//Matrix A inputs from user
	cout << "input mstrix B\n";
	for (i = 0; i < sx; i++) {
		for (j = 0; j < sy; j++) {
			cin >> second[i][j];
		}
	}

	//Add/Subtract/Multiply input
	cout << "Choose your operation: A for add,  S for subtract, M for multiply\n";
	cin >> operation;

	switch(operation) {
		case 'A':
			if (addMatrix(fx, fy, sx, sy, first, second))
				return 0;
			else
				return -1;;
			break;
		case 'S':
			if (subMatrix(fx, fy, sx, sy, first, second))
				return 0;
			else
				return -1;
			break;
		case 'M':
			if (multMatrix(fx, fy, sx, sy, first, second))
				return 0;
			else
				return -1;
			break;
		default:
			cout << "Not valid input\n";
			return -1;
	}
	//end program
	return 0;

}



bool addMatrix(int fx, int fy, int sx, int sy, int first[10][10], int second[10][10]) {
	//Counter variables
	int i, j;
	
	//Check if dimensions are the same
	if (fx != sx || fy != sy) {
		cout << "dimensions are not compatible.\n";
		return false;
	}

	cout << "The answer is:\n";
		
	for (i = 0; i < fx; i++) {
		for (j = 0; j < fy; j++) {
			cout << (first[i][j] + second[i][j]) << " ";
		}
		cout << "\n";
	}

	return true;
}
bool subMatrix(int fx, int fy, int sx, int sy, int first[10][10], int second[10][10]) {

	//Counter variables
	int i, j;
	
	//Check if dimensions are the same
	if (fx != sx || fy != sy) {
		cout << "dimensions are not compatible.\n";
		return false;
	}

	cout << "The answer is:\n";
		
	for (i = 0; i < fx; i++) {
		for (j = 0; j < fy; j++) {
			cout << (first[i][j] - second[i][j]) << " ";
		}
		cout << "\n";
	}


	return true;
}
bool multMatrix(int fx, int fy, int sx, int sy, int first[10][10], int second[10][10]) {
	
	//Counter variables
	int i, j, k, l, m;
	//Output dimensions
	int outputx, outputy;
	
	//Check if dimensions are correct
	if (fy != sx) {
		cout << "dimensions are not compatible.\n";
		return false;
	}

	outputx = fx;
	outputy = sy;

	cout << "The answer is:\n";
	//Dot product of matrices and outputting		
	for (i = 0; i < outputx; i++) {
		for (j = 0; j < outputy; j++) {
			m = 0;
			for (k = 0; k < fy; k++) {
				m = m + (first[i][k] * second[k][j]);
			}
			cout << m << " ";
		}
		cout << "\n";
	}


	return true;
}

