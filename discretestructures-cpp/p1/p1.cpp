/*Author:  Hunter Esler
 *  *Course:  CSCI 3080
 *   *Lab number: Lab 1
 *    *Purpose: This lab will take the user's name as input and output it by
 *    		Saying Hello!
 *    		 *Due date: Jan 25, 2018
 *    		 */

//Includes
#include <iostream>

using namespace std;

//Required Main function
int main()
{
	//Allocate a string for 100 characters max
	string name;
	//Ask User for name and take input
	cout << "Please input your name: ";
	getline(cin, name);

	//Tell the user hello!
	cout << "Hello " << name << "!\n";

	//end program
	return 0;

}




