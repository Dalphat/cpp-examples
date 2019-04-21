//Description: Demonstrating simple Procedural Programming Methodology part 5

//Task:
//  Excersize 4 with functions and a struct.

//Tools to be used and learnt: 
//  Pointers, functions and structs

#include <iostream>
#include <string>

//Simple struct to manage user data.
struct User {
    std::string name,
                description,
                favorite;
};

//Simple function to display and prompt users for procedure to take.
int option(User *user) {
    std::string str;//Temporary string variable used for multiple purposes.
    std::cout << "\nName:            " << user->name;
    std::cout << "\nDescription:     " << user->description;
    std::cout << "\nFavorite Color:  " << user->favorite;
    std::cout << "\n\nEnter your choice on what to do:"
        << "\n\t1) Change Name\n\t2) Change Description"
        << "\n\t3) Change Favorite Color\n\t4) Exit Program\nChoice: ";
    std::getline(std::cin, str);
    return std::stoi(str) - 1;//Throwable from std::stoi().
}

int main() {
    enum {
        NAME,
        DESCRIPTION,
        FAVORITE,
        EXIT,
        SIZE
    };
    User user;//Declare our user

    std::cout << "Welcome to the console Data entry application\n";

    bool running = true;//Running condition variable.
    while (running) {
        try {
            int index = option(&user);//Amphersand pass' the address as an argument to the function.
            std::string *user_member_ptr;//Pointer to string.
            std::string str;//Separated to not confuse new coders and possibly for readability.
            switch (index) {
            case NAME:
                str = "\nEnter new name: ";
                user_member_ptr = &user.name;
                break;
            case DESCRIPTION:
                str = "\nEnter new description: ";
                user_member_ptr = &user.description;
                break;
            case FAVORITE:
                str = "\nEnter new favorite Color: ";
                user_member_ptr = &user.favorite;
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
            *user_member_ptr = str;//Set the value being pointed at to value of str.
        }
        catch (...) {
            std::cout << "Invalid choice";
        }
    }

    return 0;
}