
/*Author:  Hunter Esler
 *  *Course:  CSCI 3080
 *   *Lab number: ola6
 *    *Purpose: This lab will take input from cin, and go through each state to see if it is recognized as a*b*ab
 *    		 *Due date: April 30, 2018
 *    		 */



#include <iostream>

//a is 0, b is 1 etc---assuming lower case
//Format is {state, input, output, stateprime}
int lookup[5][4] = {
	{0, 0, 0, 0},//See an a? output 0, go to state 0
	{0, 1, 1, 1},//see a b? output 1, go to state 1
	{1, 1, 0, 1},//see a b, output 0, go to 1
	{1, 0, 0, 2},//see an a, output 0, go to 2
	{2, 1, 1, 3}//better see a b, output 1	
};


int main()
{
	int i;//Iterator
	char a;//Input char from cin.get
	bool done = false;//Not done
	bool found;//We found a matching state already
	int input;//Converted char to integer
	int cur_state = 0;//Our current state

	//By default, we don't recognize
	std::cout << "0";
	while (!done)
	{
		found = false;
		//Get the next input char and convert it to int - 'a' (to make a 0)
		std::cin.get(a);
		input = a - 'a';

		//Most likely a newline, break out
		if (input < 0)
		{
			break;
		}
		
		//Look inside our lookup
		for (i = 0; i < 5; i++)
		{
			//This array has our state, and our input
			if (!found && lookup[i][0] == cur_state && lookup[i][1] == input) {
				std::cout << lookup[i][2];
				cur_state = lookup[i][3];
				found = true;
			}
		}

		if (!found)//rule not found, not recognized.
		{
			std::cout << "0";
			break;
		}
		
	}

	return 1;
}
