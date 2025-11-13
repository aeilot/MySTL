#include <iostream>
#include <string>
#include "LinkedList.h" // Include the corrected header

int main() {
    std::cout << "--- Test 1: Default Ctor and push_back ---" << std::endl;
    DS::LinkedList<std::string> list1;
    list1.print(); // Test print on empty
    list1.push_back("Hello");
    list1.push_back("World");
    list1.push_back("!");
    list1.print();
    // Expected: List (size 3): [0:Hello] -> [1:World] -> [2:!] -> nullptr

    std::cout << "\n--- Test 2: Initializer List Ctor ---" << std::endl;
    DS::LinkedList<int> list2 = {10, 20, 30, 40, 50};
    list2.print();
    // Expected: List (size 5): [0:10] -> [1:20] -> [2:30] -> [3:40] -> [4:50] -> nullptr

    std::cout << "\n--- Test 3: find() ---" << std::endl;
    std::cout << "Find 30: " << (list2.find(30) ? "true" : "false") << std::endl;
    // Expected: Find 30: true
    std::cout << "Find 99: " << (list2.find(99) ? "true" : "false") << std::endl;
    // Expected: Find 99: false

    std::cout << "\n--- Test 4: removeAt(id) ---" << std::endl;
    list2.print(); // Before removal

    std::cout << "Removing id 2 (data 30)..." << std::endl;
    list2.removeAt(2);
    list2.print();
    // Expected: List (size 4): [0:10] -> [1:20] -> [3:40] -> [4:50] -> nullptr

    std::cout << "Removing id 0 (data 10, head)..." << std::endl;
    list2.removeAt(0);
    list2.print();
    // Expected: List (size 3): [1:20] -> [3:40] -> [4:50] -> nullptr

    std::cout << "Removing id 4 (data 50, tail)..." << std::endl;
    list2.removeAt(4);
    list2.print();
    // Expected: List (size 2): [1:20] -> [3:40] -> nullptr

    std::cout << "Removing id 99 (not found)..." << std::endl;
    list2.removeAt(99);
    list2.print();
    // Expected: List (size 2): [1:20] -> [3:40] -> nullptr

    std::cout << "\n--- Test 5: Single-element Ctor ---" << std::endl;
    DS::LinkedList<double> list3(3.14);
    list3.print();
    // Expected: List (size 1): [0:3.14] -> nullptr
    list3.push_back(6.28);
    list3.print();
    // Expected: List (size 2): [0:3.14] -> [1:6.28] -> nullptr

    return 0;
}