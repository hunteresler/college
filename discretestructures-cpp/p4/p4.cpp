/*Author:  Hunter Esler
 *  *Course:  CSCI 3080
 *   *Lab number: Lab 4
 *    *Purpose: This lab will take in an input matrix as an array pointer representation, and output the properties of that matrix
 *    		 *Due date: April 12, 2018
 *    		 */
#include <iostream>

int main()
{
	int i,j,k,index;
	//array pointer representation
	int apr[20][2];
	
	//matrix, max 20x20
	int matrix[20][20];

	//number of nodes
	int num_nodes;
	//number of rows to read in for apr
	int num_rows;

	//Current row
	int c_row[2];

	//Did we make one before? This is for comma logic
	bool didone;
	//Is this row isolated?
	bool isolated;

	std::cout<<"Please input the numner of nodes: ";
	std::cin >> num_nodes;
	std::cout << std::endl << "Please input number of rows in the matrix: ";
	std::cin >> num_rows;
	std::cout << std::endl << "Please input the array-pointer representation of the graph: \n";

	//Read in apr
	for (i = 0; i < num_rows; i++)
	{
		std::cin >> apr[i][0];
		std::cin >> apr[i][1];
	}

	
	//Transfer apr to matrix
	for (i = 0; i < num_nodes; i++)
	{
		for (j = 0; j < num_nodes; j++)
		{
			matrix[i][j] = 0;
		}
		c_row[0] = apr[i][0];
		c_row[1] = apr[i][1];
		while (c_row[1] != 0)
		{
			index = c_row[1]-1;
			c_row[0] = apr[index][0];
			c_row[1] = apr[index][1];
			matrix[i][c_row[0]-1] = 1;
		}

	}

	//Print matrix
	std::cout << std::endl << "The adjacency matrix is:\n\n";

	for (i = 0; i < num_nodes; i++)
	{
		for (j = 0; j < num_nodes; j++)
		{
			std::cout << matrix[i][j] << " ";

		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	//Find isolated nodes
	std::cout << "The isolated nodes are: ";

	didone = false;
	for (i = 0; i < num_nodes; i++)
	{
		isolated = true;
		for (j = 0; j < num_nodes; j++)
		{
			if (matrix[i][j]==1)//Found a 1, not isolated
				isolated=false;
		}
		if (isolated)//Print that it's isolated
		{
			if (didone)
				std::cout << ", ";
			std::cout << (i+1);
			didone = true;
		}
	}

	//Print degrees of nodes
	std::cout << std::endl;
	std::cout << "The degree of each node (in the form of node/degree) is:\n";


	for (i = 0; i < num_nodes; i++)
	{
		k = 0;
		for (j = 0; j < num_nodes; j++)
		{
			if (matrix[i][j]==1)
			{
				k += 1;
				//Node is connected to itself, it has 2 connection points instead of 1
				if (i==j)
					k+=1;
			}
		}
		std::cout << (i+1) << "/" << k << std::endl;
	}

	//Print adjacent nodes
	std::cout << "The nodes adjacent to each node (in the form node: list of adjacent nodes) is:\n";
	for (i = 0; i < num_nodes; i++)
	{
		std::cout << (i+1) << ": ";
		didone = false;
		for (j = 0; j < num_nodes; j++)
		{
			if (matrix[i][j]==1)
			{
				if (didone)
					std::cout << ", ";
				didone = true;
				std::cout << (j+1);
			}
		}
		std::cout << std::endl;
	}

	return 1;
}

