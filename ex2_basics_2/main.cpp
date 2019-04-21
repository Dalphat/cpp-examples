//Description: Demonstrating simple Procedural Programming Methodology part 2

//Task:
//	Ask the user to select one of the three colors to print.

//Tools to the used and learnt:
//	Conditional branching with "if statements" and "switch statements"

#include <iostream>
#include <string>

int main() {
	//Constant string literals, our results to the users choice.
	const char *red   = "red",
			   *green = "green",
			   *blue  = "blue";

	std::string choice;
	const char *color = 0;

	std::cout << "Choose a color:";
	std::cout << "\n1) " << red << "\n2) " << green << "\n3) " << blue << "\nChoice: ";
	std::cin >> choice;

	if (choice == "1" || choice == red) {
		color = red;
	}else if (choice == "2" || choice == green) {
		color = green;
	}else if (choice == "3" || choice == blue) {
		color = blue;
	}
	else {
		std::cout << "Invalid choice.\n";
	}

	if (color != 0) {
		std::cout << "The color you selected was: " << color << ".\nNow ending program.\n";
	}

	std::cin.clear();
	std::cin.ignore(256, '\n');
	std::cout << "\nPress enter/return to exit application ";
	std::getline(std::cin, choice);

	return 0;
}