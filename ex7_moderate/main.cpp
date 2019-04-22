//Description: Demonstrating simple Structured Programming Methodology part 2

//Task:
//  Simple excersize using templates and class.
//  This program provides a template class with the capacity of 3 type 'T' data.
//      It demonstrates the use of operator overload with the plus operator.
//      It demonstrates the use of friend with the output stream object.

//Tools to be used and learnt:
//  template, operator overload, friend, and stream processing (ostream).

#include <iostream>
#include <string>

template<class T>
class Data {
public:
    T a, b, c;
    Data(T a, T b, T c) : a(a), b(b), c(c) {}
    Data(const Data<T> &data) {
        a = data.a;
        b = data.b;
        c = data.c;
    }
    friend std::ostream &operator<<(std::ostream &stream, const Data<T> &data) {
        stream << data.a << ' ' << data.b << ' ' << data.c;
        return stream;
    }
    void operator=(const Data<T> &data) {
        a = data.a;
        b = data.b;
        c = data.c;
    }
    Data<T> operator+(const Data<T> &data) {//Returns by value, expensive (copy expense: 2)
        Data<T> result(*this);//Copying self using constructor.
        result += data;
        return result;//Returning by value sinse result is only local to this scope.
    }
    Data<T> operator+(const T &value) {//Returns by value, expensive (copy expense: 2)
        Data<T> copy(*this);//Copying self using constructor.
        copy += value;
        return copy;//Returning by value sinse result is only local to this scope.
    }
    void operator+=(const Data<T> &data) {
        a += data.a;
        b += data.b;
        c += data.c;
    }
    void operator+=(const T &value) {
        a += value;
        b += value;
        c += value;
    }
};

void end();//Helper function for test: prompts user to press enter/return before program ends.

template<class T>
void print(const Data<T> data[], int size);//Helper function for test: print all data from one data.

int main() {
    //Data<int> data[]{ { 1,2,3 }, { 4,5,6 }, { 7,8,9 } };
    Data<std::string> data[]{ { "1","2","3" }, { "4","5","6" }, { "7","8","9" } };
    std::cout << "Original Numbers: \n";
    print(data, 3);
    std::cout << "Adding integer value '2' to numbers.\n";
    for (int i = 0; i < 3; ++i) {
        //data[i] = data[i] + 2;
        data[i] = data[i] + "2";
    }
    std::cout << "Resulting Numbers: \n";
    print(data, 3);
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
template<class T>
void print(const Data<T> data[], int size) {
    for (int i = 0; i < 3; ++i) {
        std::cout << data[i] << '\n';
    }
}