#include <iostream>

#include "stack.hpp"

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

    return 0;
}
