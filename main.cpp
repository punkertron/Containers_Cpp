#include <iostream>

#include "stack.hpp"
#include "vector.hpp"

void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}


int main()
{
    /*
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
    */

    ft::vector<int> v;
    ft::vector<char> v2;
    ft::vector<int> v3(4);
    ft::vector<int> v4(15, 10);

    for (int i = 0; i < v4.size(); ++i)
        std::cout << v4[i] << ' ';
    std::cout << std::endl;

    std::cout << v.empty() << std::endl;
    std::cout << v4.empty() << std::endl;
    std::cout << v.max_size() << std::endl;
    std::cout << v2.max_size() << std::endl;

    try
    {
        v.at(0) = 1;
    }
    catch(const std::out_of_range &e)
    {
        std::cerr << e.what() << '\n';
    }

    v4[0] = 1111;
    v4.at(14) = 2222;

    std::cout << v4.front() << std::endl;
    std::cout << v4.back() << std::endl;
    std::cout << v4.capacity() << std::endl;

    pointer_func(v4.data(), v4.size());

    if (!(v4.data()))
        std::cout << "Invalid data" << std::endl;

    auto ptr = v4.data();
    std::cout << *ptr << std::endl;

    v4.reserve(100);
    std::cout << "capacity = " << v4.capacity() << std::endl;
    v4.reserve(10000);
    std::cout << v4.capacity() << std::endl;
    pointer_func(v4.data(), v4.size());

    ft::vector<int> v5(std::move(v4));
    pointer_func(v4.data(), v4.size());
    pointer_func(v5.data(), v5.size());

    v = std::move(v5);
    v = std::move(v);
    pointer_func(v5.data(), v5.size());
    pointer_func(v.data(), v.size());

    ft::vector<int> v6;

    for (int i = 0; i < 11; ++i)
    {
        v6.push_back(i);
        std::cout << "size = " << v6.size() << " | capacity = " << v6.capacity() << std::endl;
    }

    return 0;
}
