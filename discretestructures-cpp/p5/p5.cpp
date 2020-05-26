/*Author:  Hunter Esler
 *  *Course:  CSCI 3080
 *   *Lab number: Lab 5
 *    *Purpose: This lab will take a graph in left-middle-right child array representation, and output different traversals through the graph
 *    		 *Due date: April 24, 2018
 *    		 */

//Max number of rows in array... increase if needed
#define max_rows 40

#include <iostream>

//Recursive traversals with cur being the current node index being worked on
void preorder(const int cur);
void postorder(const int cur);
void inorder(const int cur);

//array pointer representation, 3 to represent left, middle, and right child
int apr[max_rows][3];

int main()
{
	//blah
	int i,j,k,index;
	
	//number of nodes
	int num_nodes;

	//Current row
	int c_row[3];

	//Did we make one before? This is for comma logic
	bool didone;
	
	//Input
	std::cout<<"Please input the number of nodes (max " << max_rows << "): ";
	std::cin >> num_nodes;
	std::cout << std::endl << "Please input the left-middle-right child array representation of the graph: \n";

	//Read in apr
	for (i = 0; i < num_nodes; i++)
	{
		std::cin >> apr[i][0];
		std::cin >> apr[i][1];
		std::cin >> apr[i][2];
	}	

	//Output preorder
	std::cout << "The preorder traversal is:\n  ";
	preorder(0);
	std::cout << "\n";
	//Output inorder
	std::cout << "The inorder traversal is:\n  ";
	inorder(0);
	std::cout << "\n";
	//Output postorder
	std::cout << "The postorder traversal is:\n  ";
	postorder(0);
	std::cout << "\n";
	return 1;
}

//Outputs the preorder traversal of apr
void preorder(const int cur) {

	std::cout << (cur+1) << " ";
	int left = apr[cur][0], middle = apr[cur][1], right = apr[cur][2];

	if (left > 0)
		preorder(left-1);
	if (middle > 0)
		preorder(middle-1);
	if (right > 0)
		preorder(right-1);
}

//Outputs the inorder traversal of apr
void inorder(const int cur) {


	int left = apr[cur][0], middle = apr[cur][1], right = apr[cur][2];

	if (left > 0)
		inorder(left-1);

	std::cout << (cur+1) << " ";

	if (middle > 0)
		inorder(middle-1);
	if (right > 0)
		inorder(right-1);


}

//Outputs the postorder of apr
void postorder(const int cur) {

	int left = apr[cur][0], middle = apr[cur][1], right = apr[cur][2];

	if (left > 0)
		postorder(left-1);
	if (middle > 0)
		postorder(middle-1);
	if (right > 0)
		postorder(right-1);
	
	std::cout << (cur+1) << " ";

}
