//Description: Demonstrating simple Structured Programming Methodology part 1

//Task:
//  Excersize 5 with a class. We will be using class functions rather than functions and
//      class member variables instead of local variables to main. We will be adopting
//      our helper option function into our as a private member. Same applies for our enum.
//      This will couple our original procedures with our class object 

//Tools to be used and learnt: 
//  class: member functions, member variables, and encapsulation of data (scope).


#include <iostream>
#include <string>

//Simple class to manage user data.
class User {
private:
    enum {
        NAME,
        DESCRIPTION,
        FAVORITE,
        EXIT,
        SIZE
    };
    //Simple function to display and prompt users for procedure to take.
    int option() {
        std::string str;//Temporary string variable used for multiple purposes.
        std::cout << "\nName:            " << name;
        std::cout << "\nDescription:     " << description;
        std::cout << "\nFavorite Color:  " << favorite;
        std::cout << "\n\nEnter your choice on what to do:"
            << "\n\t1) Change Name\n\t2) Change Description"
            << "\n\t3) Change Favorite Color\n\t4) Exit Program\nChoice: ";
        std::getline(std::cin, str);
        return std::stoi(str) - 1;//Throwable from std::stoi().
    }
public:
    //Public memebers of User. In modern c++ getters and setters are stated to be Idiomatic and
    //  generally signs of poor design. Personally, I believe there are exceptions where they
    //  should be used, example: virtual functions and pure virtual class'. However for demonstrations, 
    //  public members will be used in this case as well as setters (Intentional poor coupling with IO).
    std::string name,
                description,
                favorite;
    User(){}//Empty constructor
    User(const std::string &name, const std::string &description, const std::string &favorite) :
        name(name), description(description), favorite(favorite){}
    void setName() {
        std::cout << "\nEnter new name: ";
        std::getline(std::cin, name);
    }
    void setDescription() {
        std::cout << "\nEnter new description: ";
        std::getline(std::cin, description);
    }
    void setFavorite() {
        std::cout << "\nEnter new favorite color: ";
        std::getline(std::cin, favorite);
    }
    bool run() {
        try {
            int index = option();
            switch (index) {
            case NAME:
                setName();
                break;
            case DESCRIPTION:
                setDescription();
                break;
            case FAVORITE:
                setFavorite();
                break;
            case EXIT:
                std::cout << "Exiting Application";
                return false;
            default:
                std::cout << "\nInvalid number!\n";
                return true;
            }
        }
        catch (...) {
            std::cout << "Invalid choice";
        }
        return true;
    }
};


int main() {
    User user;//Declare our user
    std::cout << "Welcome to the console Data entry application\n";
    while (user.run()) {}//Could end with semicolon, but supposedly this helps readability.
    return 0;//Not necessary but illustrating that main function will return an int; pregenerated
    //  by compiler if not present on main function.
}