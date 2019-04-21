//Description: Demonstrating simple Procedural Programming Methodology part 3

//Task:
//  Make a command driven application that will terminate when requested by user or after 256
//      numbers have been inserted.
//  Use a string to validate entry and error check.
//  Use Try and Catch to determine if an exception occurred.

//Tools to be used and learnt: 
//  Loops and primitive Array

#include <iostream>
#include <string>

int main() {

    const static int max = 256;
    int numbers[max];
    int count = 0;
    std::string input;//String variable to be parse for actual input.

    std::cout << "Welcome User\nPlease enter numbers until you are statisfied (max = 256)." <<
        "\nWe will sort the number and display them afterwards, thank you.\n";
    for (int i = 0, number; i < max; ++i) {
        std::cout << "\nEnter an integer for number[" << i << "] or type \"quit\" when done.\nInput: ";
        std::cin >> input;
        if (input == "quit")
            break;
        try {
            number = std::stoi(input);
            numbers[count++] = number;
        }catch (std::exception &e) {
            std::cout << "\nInvalid input, try again";
        }
    }

    //Simple Bubble Sort:
    for (int i = 0; i < count; ++i) {//Go through every item
        for (int j = i + 1; j < count; ++j) {//Go through every number after 'i'
            if (numbers[i] > numbers[j]) {//Compare the value at index 'i' to value at index 'j'.
                //True, we need to swap the numbers now.
                int number = numbers[i];//Backup the number at index 'i' to temporary variable "number".
                numbers[i] = numbers[j];//Assign the number at index 'i' to be the same as the number at index 'j'.
                numbers[j] = number;//Assign the number at index 'j' to be the same value as the variable "number".
            }
        }
    }

    //Print the numbers:
    if (count > 0) {
        std::cout << "\nThe sorted numbers are: {\n\t";
        for (int i = 0; i < count; ++i) {
            if (!(i % 8) && i)
                std::cout << "\n\t";
            std::cout << numbers[i] << ' ';
        }
        std::cout << "\n}\n";
    }

    //Handle enter press before exit:
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cout << "\nPress enter/return to exit application ";
    std::string buffer;
    std::getline(std::cin, buffer);

    return 0;
}