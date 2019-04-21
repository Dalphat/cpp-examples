//Description: Demonstrating simple Procedural Programming Methodology part 4

//Task:
//  Application prompts the user to select one of the three colors using an integer.
//  If integer is 

//Tools to be used and learnt: 
//  Enumerators, switch, and functions

#include <iostream>
#include <string>

int main() {
    enum {
        NAME,
        DESCRIPTION,
        FAVORITE,
        EXIT,
        SIZE
    };
    std::string data[SIZE];

    std::cout << "Welcome to the console Data entry application\n";
    bool running = true;//Running condition variable.
    while (running) {
        std::string str;//Temporary string variable used for multiple purposes.
        std::cout << "\nName:            " << data[NAME];
        std::cout << "\nDescription:     " << data[DESCRIPTION];
        std::cout << "\nFavorite Color:  " << data[FAVORITE];
        std::cout << "\n\nEnter your choice on what to do:"
                  << "\n\t1) Change Name\n\t2) Change Description"
                  << "\n\t3) Change Favorite Color\n\t4) Exit Program\nChoice: ";
        std::getline(std::cin, str);
        try {
            int index = std::stoi(str) - 1;
            switch (index) {
            case NAME:
                str = "\nEnter new name: ";
                break;
            case DESCRIPTION:
                str = "\nEnter new description: ";
                break;
            case FAVORITE:
                str = "\nEnter new favorite Color: ";
                break;
            case EXIT:
                std::cout << "Exiting Application";
                running = false;
                continue;
            default:
                std::cout << "\nInvalid number!\n";
                continue;
            }
            std::cout << str;
            std::getline(std::cin, str);
            data[index] = str;
        }
        catch (...) {//Catching all exceptions for logging.
            std::cout << "\nInvalid choice!\n";
        }

    }
    //Handle enter press before exit:
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cout << "\nPress enter/return to exit application ";
    std::string buffer;
    std::getline(std::cin, buffer);
}