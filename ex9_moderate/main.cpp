//Description: Demonstrating simple Structured Programming Methodology part 4

//Task: Now that we've gotten experience with making our own dynamic array (doubly linked list),
//      we will be instead using the pre built containers provided by the c++
//      standard library.

//Tools to be used and learnt:
//      Array:  Fixed sized contiguous memory. Similar to primitive arrays but
//              provides us with useful functions.
//      Vector: Dynamically sized contiguous memory similar to array but enables resizing at some expense.
//		List:   Like vector but has cheaper reads and writes, however memory is not contiguous.
//				Linked list vs Vector comparison from SO: https://stackoverflow.com/a/2209564
//              Unordered Maps are fast at reading but are unordered.

#include <iostream>
#include <string>
#include <array>//Statically Sized Array
#include <vector>//Dynamically Sized Array
#include <list>//Dynamically Sized Array (Fast but not contiguous)
#include <iterator>//For Standard Advance with our list
#include <unordered_map>

template<class T>
void print(T var) {
	for (auto a : var)
		std::cout << a << ' ';
    std::cout << "\n\n";
}

template<class T1, class T2>
void print(std::unordered_map<T1, T2> map) {
    for (auto pair : map)
        std::cout << pair.first << ' ' << pair.second << '\n';
    std::cout << '\n';
}

int main() {
	std::array<int, 10> arr{ 0 };
	arr[2] = 1;//Changed third element to an integer value of 1.
	print(arr);

	std::vector<int> vec(10,0);
	vec[5] = 2;//Changed fifth element to an integer value of 2.
	vec.push_back(5);//Add an element to the end of the vector; value 5.
	print(vec);

	std::list<int> list(10, 0);
	auto it = list.begin();
	std::advance(it, 7);//Shift our iterator "it" 7 units right
	*it = 3;//Set value at iterator to 3
	print(list);

    std::unordered_map<int, std::string> map;
    map[0] = "Hello World";
    map[1] = "Good Bye";
    print(map);

	std::cout << "Press any enter to continue: ";
	std::string buffer;
	std::getline(std::cin, buffer);

	return 0;
}
