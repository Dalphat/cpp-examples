//Description: Demonstrating simple Structured Programming Methodology part 3

//Task: Building a simple structure using knowledge from our previous example excersizes
//      We will be demonstrating a simple dynamic array by using the doubly linked list implementation.
//      Doubly Link List will handle range exception.

//Our Doubly Linked List interface object (A class that manages the behavior of our Nodes)
//  Our DLL will support simple functions: #push_back(T), #pop_bck(), #insert(int, T), and #erase(int).
//  Where integer values are the indices. (Since we do not allow access of nodes, we will not be manipulating by iter).
//  We will also override the operator[] to further familiarize/associate this interface with arrays.

#include <iostream>
#include <sstream>
#include <string>

template<class T>
class LinkedList {
private:
    //Our Node object: (POD) Plain Old Data
    //  Managed by the DLL, and contains the data requested by the user.
    //  Provides a value variable of type T
    //  Provides two pointer to acknowledge previous and next nodes that are possibly linked.
    template<class T1>//'U' is of a type, but must not be 'T' to avoid shadowing template.
    struct Node {
        T1 value;
        Node *prev,
             *next;
    };
    std::stringstream ss;
    std::string out_of_range(int index) {
        ss.str(std::string());//Clear the ss if an error occurs.
        std::size_t size_v = size();
        ss << "\n\n\tError\tOut of Range:" 
           << "\tAccess of element [" << index << "] where size " << size_v << '\n';
        return ss.str();
    }
    //Our node will not be public exposed to the user, this will help prevent accidental memory leakage.
    Node<T> *head;
public:
    LinkedList() : head(0){}
    LinkedList(T value) : head(new Node<T>{ value,0,0 }) {}

    //Destructor to free our nodes when our linked list object leaves scope.
    //All data managed by us will no longer be available after destructor is called, with exceptions
    //  of memory not managed by our linked list, example: if our linked list is of type pointer
    //  we would only manage pointers to address' of data rather than the actual data.
    ~LinkedList() {
        Node<T> *curr = head;
        while (curr) {//Repeats while curr is not null or 0
            //Link the previous and next node together, so we can delete the current node.

            //Our pointer to the previous node from currently focused node:
            Node<T> *prev = curr->prev;
            //Our pointer to the next node from currently focused node:
            Node<T> *next = curr->next;


            //We shall reassociate the "previous' next" with the current node's "next" node.
            if (prev) //If prev is not null or 0
                prev->next = next;//Null is fine.

            //We shall reassociate the "next's previous" with the current node's "previous" node.
            if (next) //If prev is not null or 0
                next->prev = prev;//Null is fine.

            //Now we can free this Node.
            delete curr;

            //And to ensure all nodes are freed, we will try previous and next nodes to ensure all nodes are freed.
            //  Our destructor will free previous' first then nexts.
            if (prev)
                curr = prev;//Set current to previous, until there are no more previous nodes of non 0 value.
            else if (next)
                curr = next;//Set current to next, until there are no more next nodes of non 0 value.
            else
                curr = 0;//No more linked nodes, set current to null(0) to exit loop.
        }
    }
    T operator[](int index) {
        Node<T> *curr = head;
        //Shift the current node by "index" amount. Current will be null(0) if out of bounds.
        for (int i = 0; i < index && curr; ++i)
            curr = curr->next;
        if (curr)
            return curr->value;
        throw std::out_of_range(out_of_range(index));
        //Throw out of range error.
    }
    void push_back(T value) {
        Node<T> *curr = head;
        if (head) {
            //GOTO the last node
            while (curr->next)
                curr = curr->next;
            if (curr) {
                //Create a new last node and connect it to the second last node.
                curr->next = new Node<T>{ value, curr, 0 };
            }
        }
        else {
            //No nodes found, create a new "head" node.
            head = new Node<T>{ value, 0, 0 };
        }
    }
    void pop_back() {
        Node<T> *curr = head;
        //Free the last available node on the list
        if (curr) {
            //GOTO the last node
            while (curr->next)
                curr = curr->next;
            //Set a pointer to second last node.
            Node<T> *prev = curr->prev;
            //Delete last node.
            delete curr;
            //Update second last node to be the last node there was a previous node.
            if(prev)
                prev->next = 0;
        }
        //No throw on empty list.
    }
    void insert(int index, T value) {
        if (head) {
            Node<T> *curr = head;
            //Setting current node to expected position.
            for (int i = 0; i < index && curr; ++i)
                curr = curr->next;
            //Inserting new Node between previous and current.
            if (curr) {
                Node<T> *next = curr,
                        *prev = curr->prev;
                curr = new Node<T>{ value, prev, next };
                if(prev)
                    prev->next = curr;
                if(next)
                    next->prev = curr;
            }
        }
        else {
            throw std::out_of_range(out_of_range(index));
        }
    }
    void erase(int index) {
        if (head) {
            Node<T> *curr = head;
            //Setting current node to expected index.
            for (int i = 0; i < index && curr; ++i)
                curr = curr->next;
            if (curr) {
                Node<T> *prev = curr->prev,
                        *next = curr->next;
                delete curr;
                if (prev)
                    prev->next = next;
                if (next)
                    next->prev = prev;
            }
        }
        else {
            throw std::out_of_range(out_of_range(index));
        }
    }
    std::size_t size() {
        std::size_t size = 0;
        Node<T> *curr = head;
        while (curr) {
            curr = curr->next;
            ++size;
        }
        return size;
    }
};

//Prototype function:
void end();

int main() {
    //Declare our linked list:
    //  Initializing with curly braces will prevents compiler from accidentally "Narrowing Conversion"
    //  This will also avoid "Most vexing parse": https://en.wikipedia.org/wiki/Most_vexing_parse
    LinkedList<int> list;
    try {
        for (int i = 0; i < 10; ++i)
            list.push_back(i);
        for (std::size_t i = 0; i < list.size(); ++i)
            std::cout << list[i] << ' ';
        std::cout << '\n';
        while (list.size() > 5)
            list.erase(5);
        for (std::size_t i = 0; i < list.size(); ++i)
            std::cout << list[i] << ' ';

        //std::cout << list[5] << '\n';//Example of out of range exception.
    }
    catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }
    end();
    return 0;
}
void end() {
    //Handle enter press before exit:
    //std::cin.clear();//Only necessary if input was used
    //std::cin.ignore(256, '\n');//Only necessary if input was used
    std::cout << "\nPress enter/return to exit application ";
    std::string buffer;
    std::getline(std::cin, buffer);
}

/*
    Note:
        Memory Leak:

            This program was checked with Valgrind to ensure no memory is leaked.

            Memory leak can have an impact of applications and should be freed when application finishes.

            OS will automatically free used memory on termination of applications but it is good practice to do
            so ourselves. Also, Sub-Systems may not necessarily free memory on termination of the application 
            hence why the program should be manually freed.

            Our example does so with class destructors: Are manually allocated data will be freed when 
            destructor is called.

        Out of Range:
            
*/