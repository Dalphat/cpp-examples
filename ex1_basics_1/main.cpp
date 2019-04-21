//Description: Demonstrating simple Procedural Programming Methodology part 1

//Tools to be used and learnt: 
//	Comments and variables.

// This is a single-lined comment
/* This is a multi-lined comment.*/

//Icluding input and output from the standard library.
#include <iostream>//Needs to be included before use of cout, cin; string is included.

//The following line is the "Global main function" and the starting point of our application:
int main() {
	//Declare our local variables before usage:
	std::string name,			//The users name
				description;	//The users description
	int favorite;				//The users favorite number
	//Other primitive types: https://www.geeksforgeeks.org/c-data-types/

	//Using standard's output member cout to display data to console:
	std::cout << "Welcome user, please enter your name: ";//Our data is a string literal.
	//Using standard's input member cin to acqurie data from console.
	std::cin >> name;//Our data is a string variable.
	
	//Console output with multiple arguments, one being our "name" variable.
	std::cout << "Hello " << name << "! what can you tell us about yourself?\nDescription: ";

	//Default return value for our main function.
	return 0;//No longer necessary after c99, automatically added.
	//Where value 0 is a sucessful exit.
}