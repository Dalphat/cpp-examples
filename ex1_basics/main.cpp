//Description: Demonstrating simple Procedural Programming Methodology part 1

//Task:
//	Prompt the user for his or her name, description, favorite number and print it.

//Tools to be used and learnt: 
//	Comments and variables.

// This is a single-lined comment
/* This is a multi-lined comment.*/

//Icluding input and output from the standard library.
#include <iostream>//Needs to be included before use of cout, cin.
#include <string>//Needs to be include for string operation.

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
	//	Note: '\n' is the escape character for newline.
	std::cout << "Hello " << name << "!\nWhat can you tell us about yourself?\nDescription: ";
	std::cin.clear();//Clears error in cin, if any.
	std::cin.ignore(256, '\n');//Ignores up to 256 characters in the console input buffer.
	std::getline(std::cin,description);//Clear and Ignore needed.
	//We should not mix IO operators.

	//Lastly, ask the user for his or her favorite number.
	std::cout << "Quite interesting. Do you have a favorite number?\nNumber: ";
	std::cin >> favorite;

	//If the console input state is fine, we've recieved valid inputs (maybe):
	if (std::cin.good()) {
		std::cout << "\nAh, so let's check out your data:\nName: " << name
				  << "\nDescription: " << description
				  << "\nFavorite Number: " << favorite;

	}

	//The following will wait for the to press enter/return before exiting.
	std::cin.clear();//Clears error in cin, if any.
	std::cin.ignore(256, '\n');//Ignores up to 256 characters in the console input buffer.
	std::cout << "\nPress enter/return to exit application ";//Prompt user for input.
	std::string buffer;//Temporary String to capture the exit input.
	std::getline(std::cin, buffer);//Acquire input before exiting.

	//Default return value for our main function.
	return 0;//No longer necessary after c99, automatically added.
	//Where value 0 is a sucessful exit.
}