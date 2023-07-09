#include <iostream>

#include "stack.hpp"
#include "vector.hpp"

int main()
{
    ft::stack<int> i;
    i.push(190);
    std::cout << i.top() << std::endl;
    i.push(80);
    std::cout << i.top() << std::endl;
    i.top() = 100;
    std::cout << i.top() << std::endl;
    if (!i.empty())
        std::cout << "H\n" << i.size() << std::endl;
    i.pop();
    std::cout << i.top() << '|' << i.size() << std::endl;

    
    std::cout << "i = " << i.top() << std::endl;
    
    ft::stack<int> k(std::move(i));

    std::cout << "k = " << k.top() << std::endl;

    ft::stack<int> p;

    p = std::move(k);
   //std::cout << "k = " << k.top() << std::endl;
    std::cout << "p = " << p.top() << std::endl;
    ft::stack<int> b;
    b.push(42);
    b.push(21);
    b.push(19);
    std::cout << "b size = " << b.size() << "\np size = " << p.size() << std::endl;
    b.swap(p);
    std::cout << "b size = " << b.size() << "\np size = " << p.size() << std::endl;

    
    ft::stack<int> test1, test2;
    test1.push(21);
    test2.push(42);
    test1.push(100);
    if (test1 < test2)
        std::cout << "test1 < test" << std::endl;
    if (test2 > test1)
        std::cout << "test2 > test1" << std::endl;

    if (test1 == test2)
        std::cout << "test1 == test" << std::endl;
    if (test1 != test2)
        std::cout << "test1 != test" << std::endl;
    
    test1.pop();
    test1.pop();
    test1.push(42);
    if (test1 == test2)
        std::cout << "test1 == test" << std::endl;
    if (test1 != test2)
        std::cout << "test1 != test" << std::endl;

    return 0;
}
