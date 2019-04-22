//Description: Demonstrating simple Procedural Programming Methodology part 1

//Task:
//	Prompt the user for his or her name, description, favorite number and print it.
//  Very bloated with comments to help give awareness to fellow developers.
//      Ideally the first commented statement will explain the following codes behavior.
//      Comments following the initial comment may go into details about possible new components
//      and can be ignored but is advised to at least skim over.
//  There are Extra Comments below the main function that futher explains possible questions.

//Tools to be used and learnt: 
//	Comments and variables.

//  Learning about singled line Comments:
//      These comments are considered single-lined comments.
//      They are only valid for the line and only after the usage of two consecutive forwards slashes.

/*  Learning about multiple line Comments:
        These comments are considered multi-line and starts with an initial forward slash followed by
            asterisk and ends with an asterisk followed by forward slash.
        All lines written between the two tags will be considered comments and will not directly effect
            the flow of your application in any way.
*/

//  Learning about Inclusion of headers/frameworks/libraries:
//  The following are inclusions from the c++ standard library.
//      We will be using "iostream" for inputing and outputing as streams to the console.
#include <iostream> //IO stream is needed for our usage of standard's cout and cin.
#include <string>   //String will be needed to use string operations. Although string is also provided
                    //  by IO stream, you are given a large variety of functionality with strings when
                    //  including the actual library.

//  Learning about Namespaces: std also known as the standard c++ library.
//      Intentionally displayed for illustrations but commented because our applications will
//          not be using global namespaces. If anything, you can use namespaces within limited
//          scopes to not create ambiguity with other users of your application. 
//using namespace std;

//The following line is the "Global main function" and the starting point of our application:
//  It is required for most if not all standard c++ applications on hosted machines.
int main() {
	//This is our variable declarations. They are memory reserved by our application
    //  for usage within our application. In this case, they are local to our main function
    //  and by default will only be available within this and any sub scopes.
	std::string name,			//Our string variable representing the users name
				description;	//Our string variable representing the users description
                                //  Comma allows us to continue adding variables of the same type.

	int favorite;				//Here we have an integer for the users favorite number
	//Other primitive types can be learnt about here: https://www.geeksforgeeks.org/c-data-types/


	//We will be using the standard's output stream called cout to display a string to the console.
    //  In this example, the const string literal on the "right hand side" (short for "rhs")
    //  is the string we are printing to the user. The operator<< is provided by stream objects
    //  and used by cout to print to the console.
	std::cout << "Welcome user, please enter your name: ";//Semi colon ends a statement.

	//For console input processing, we will be using the standard's cin.
    //  Just like cout, cin is a stream object and uses the operator>> to acquire input.
    //  In the example, we will be assigning our input to the "name" variable.
	std::cin >> name;//Our data is a string variable and will stop reading after whitespace or return/enter.
	
	//Next we will be printing multiple output to the console by appending the operator<<
    //  after each of our arguments-to-be-printed followed by more arguments and repeating until done. 
	//	Note: '\n' is the an ascii escape "single-character" for newline.
    //      More can be found here: https://en.cppreference.com/w/cpp/language/escape
	std::cout << "Hello " << name << "!\nWhat can you tell us about yourself?\nDescription: ";

    //We will be using standard's getline to acquire strings not delimited by white space character.
    //  To do this, we need to clear console input of any errors (only require if you are mixing 
    //      standard's console input with standard's getline.
	std::cin.clear();//Clears error in cin, if any.

    //After clearing the errors, we will be ignoring characters in the buffer.
    //  This can generate undefined behaviors and not recommended but we the developers know that
    //  We will be taking in console input prior to this and will have a remaining return key in buffer.
    //  In this case, we will be ignoring up to 256 characters or after the first newline character is extracted.
	std::cin.ignore(256, '\n');//Ignores up to 256 characters in the console input buffer.

    //Now we are ready to use standards getline. If you do not mix standard's input streams, you would just
    //  normally call this directly without clearing or ignoring.
	std::getline(std::cin,description);

	//Lastly, ask the user for his or her favorite number.
	std::cout << "Quite interesting. Do you have a favorite number?\nNumber: ";
	std::cin >> favorite;

	//If the console input state is fine, we've recieved valid inputs (maybe):
	if (std::cin.good()) {
        //The following line prints to the console like usually, but illustrates usage of continuing code
        //  on newlines. In this case, the operator<< as the first argument on the next indicates that it is
        //  a part of the previous line and works to help make code possibly readable.
        //  You can have operators at the end of a line and it would do the same rather that at the beginning of
        //  the next line, but I have chosen this style to nicely align code with operators (shorten).
		std::cout << "\nAh, so let's check out your data:\nName: " << name
				  << "\nDescription: " << description
				  << "\nFavorite Number: " << favorite;
    }
    else {
        //This is our else scope, if the if-statement is false, we shall process procedures within here.
        std::cout << "\nInvalid data, processing canceled.";
    }

    //Note: The remaining code of the application not relevant to our demonstration, but can be further explained
    //  below our main function in the EXTRA Notes section. Only breif descriptions will be provided hereafter.


	//The following will wait for an "enter or return" key from console before exiting.
	std::cin.clear();//As earlier, this will clear any errors if any in the console input stream.
	std::cin.ignore(256, '\n');//Repeat: Ignores up to 256 characters in the console input buffer.

    //Inform the user that "enter or return" in the input buffer is necessary to properly terminate this application
	std::cout << "\nPress enter/return to exit application ";
	std::string buffer;//A temporary string to capture input
	std::getline(std::cin, buffer);//Capture input from console input stream; delimited by newline.

	return 0;//Always displayed by me, but unnecessary: Explained in EXTRA Notes.
}

//EXTRA Notes:

    //  Escape Character: There are other escape characters including ANSI, that which may not be
    //      supported on certain Operating systems. As of 2019, of the Windows 10 supports ANSI characters.
    //      Older windows OS still do not support ANSI escape characters, so keep that in mind if
    //      you are intending to release applications for such platforms.

    //  Return Zero: Not necessary in the main function after C99 but I will always be providing it
    //      to clearly illustrate that main is a function and does expect a return type integer.
    //      This is now automatically generated automatically by default with modern compilers.

    //  Mixing Standards IO operations: Avoid mixing standard IO operations, in particularly the input object,
    //      to avoid possible undefined behavior and unnecessary calls to clears and ignore from the console input 
    //      stream object.

    //  Namespaces: You should never add "using namespace"(s) to any applications unless you are for certain
    //      that there are no ambiguity between current and future resources. If anything, you can add
    //      "using namespace" within narrowed scopes, such as your specified function, to only limit
    //      the namespace usage to your functions. I do not recommend Global usages of namespaces for any reason. 

