#include <iostream>
#include <stack>
#include <vector>
#include <set>

//Make the function that will validate the count of the brackets and
//if each opens bracket will have the close bracket (like () or (((())))) -
//the validation must be true, in other way (like (( or )( or ()()))) - must be false.

template<class T, class C = typename std::stack<T>::container_type>
class hackedStack : public std::stack<T, C>
{
public:
    // just fun fact: we can expose the protected members to public with using keyword
    using std::stack<T,C>::c; // actually the real container used
};

void investigateStackConstructor()
{
    std::stack<int, std::vector<int>> vectorStack {};
    std::stack<int, std::set<int>> customizedStack {}; // here we can use any container that provides back(), push_back(), pop_back()

    std::stack<int> stackExample {}; // but std::deque is optimal for us - performance as in vector, but without realloc
    hackedStack<int> hackedStackExample {}; // lets hack the stack!

    // Oh....
//    std::stack<std::string> booksPillar {
//        "Stroustrup",
//        "Meyers"
//    };

    std::cout << typeid (hackedStackExample.c).name() << std::endl; // here you will see the mangled name

    hackedStackExample.push(187);
    hackedStackExample.push(190);

    for (const auto& hackedValue : hackedStackExample.c) { // hehe
        std::cout << hackedValue << std::endl;
    }
}

void investigateOperations() {
    std::stack<std::string> booksPillar;

    booksPillar.push("Effective Modern C++"); // add element, O(1)
    booksPillar.push("The C++ programming language");
    booksPillar.emplace("Effective STL"); // the same

// Stack layout:
//    |                            |
//    |        Effective STL       |
//    |____________________________|
//    |                            |
//    |The C++ programming language|
//    |____________________________|
//    |                            |
//    |     Effective Modern C++   |
//    |____________________________|
    std::cout << "Books pillar is empty: " << booksPillar.empty() << std::endl
              << "It's size is: " << booksPillar.size() << std::endl;

    std::cout << booksPillar.top() << std::endl; // top element, the last added, O(1)

    booksPillar.pop(); // remove last added element, O(1)
    std::cout << booksPillar.top() << std::endl;

    // Underflow example:
    std::cout << "Size: " << booksPillar.size() << std::endl;
    if (booksPillar.empty()) { // Crash is avoidable
        // do nothing
    } else {
        booksPillar.pop();
        booksPillar.pop();
        booksPillar.pop(); // Crash
    }

};

int main()
{
    investigateStackConstructor();
    investigateOperations();
    return 0;
}
