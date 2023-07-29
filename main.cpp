#include <iostream>
#include <string>

#include "stack.hpp"
#include "vector.hpp"
#include "list.hpp"

void pointer_func(const int* p, std::size_t size)
{
    std::cout << "data = ";
    for (std::size_t i = 0; i < size; ++i)
        std::cout << p[i] << ' ';
    std::cout << '\n';
}


class A
{
private:
    A();

public:
    A(const std::string& s)
    {
        std::cerr << "From A const. : " << s << std::endl;
    }
};

int main()
{

//     ft::stack<int> i;
//     i.push(190);
//     std::cout << i.top() << std::endl;
//     i.push(80);
//     std::cout << i.top() << std::endl;
//     i.top() = 100;
//     std::cout << i.top() << std::endl;
//     if (!i.empty())
//         std::cout << "H\n" << i.size() << std::endl;
//     i.pop();
//     std::cout << i.top() << '|' << i.size() << std::endl;

    
//     std::cout << "i = " << i.top() << std::endl;
    
//     ft::stack<int> k(std::move(i));

//     std::cout << "k = " << k.top() << std::endl;

//     ft::stack<int> p;

//     p = std::move(k);
//    //std::cout << "k = " << k.top() << std::endl;
//     std::cout << "p = " << p.top() << std::endl;
//     ft::stack<int> b;
//     b.push(42);
//     b.push(21);
//     b.push(19);
//     std::cout << "b size = " << b.size() << "\np size = " << p.size() << std::endl;
//     b.swap(p);
//     std::cout << "b size = " << b.size() << "\np size = " << p.size() << std::endl;

    
//     ft::stack<int> test1, test2;
//     test1.push(21);
//     test2.push(42);
//     test1.push(100);
//     if (test1 < test2)
//         std::cout << "test1 < test" << std::endl;
//     if (test2 > test1)
//         std::cout << "test2 > test1" << std::endl;

//     if (test1 == test2)
//         std::cout << "test1 == test" << std::endl;
//     if (test1 != test2)
//         std::cout << "test1 != test" << std::endl;
    
//     test1.pop();
//     test1.pop();
//     test1.push(42);
//     if (test1 == test2)
//         std::cout << "test1 == test" << std::endl;
//     if (test1 != test2)
//         std::cout << "test1 != test" << std::endl;



///////////////////////////////////////
// VECTOR
///////////////////////////////////////

    // ft::vector<int> v;
    // ft::vector<char> v2;
    // ft::vector<int> v3(4);
    // ft::vector<int> v4(15, 10);

    // for (int i = 0; i < v4.size(); ++i)
    //     std::cout << v4[i] << ' ';
    // std::cout << std::endl;

    // std::cout << v.empty() << std::endl;
    // std::cout << v4.empty() << std::endl;
    // std::cout << v.max_size() << std::endl;
    // std::cout << v2.max_size() << std::endl;

    // try
    // {
    //     v.at(0) = 1;
    // }
    // catch(const std::out_of_range &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    // v4[0] = 1111;
    // v4.at(14) = 2222;

    // std::cout << v4.front() << std::endl;
    // std::cout << v4.back() << std::endl;
    // std::cout << v4.capacity() << std::endl;

    // pointer_func(v4.data(), v4.size());

    // if (!(v4.data()))
    //     std::cout << "Invalid data" << std::endl;

    // auto ptr = v4.data();
    // std::cout << *ptr << std::endl;

    // v4.reserve(100);
    // std::cout << "capacity = " << v4.capacity() << std::endl;
    // v4.reserve(10000);
    // std::cout << v4.capacity() << std::endl;
    // pointer_func(v4.data(), v4.size());

    // ft::vector<int> v5(std::move(v4));
    // pointer_func(v4.data(), v4.size());
    // pointer_func(v5.data(), v5.size());

    // v = std::move(v5);
    // v = std::move(v);
    // pointer_func(v5.data(), v5.size());
    // pointer_func(v.data(), v.size());

    // ft::vector<int> v6;

    // for (int i = 0; i < 21; ++i)
    // {
    //     v6.push_back(i);
    //     std::cout << "size = " << v6.size() << " | capacity = " << v6.capacity() << std::endl;
    // }

    // std::cout << v6.size() << std::endl;
    // v6.clear();
    // std::cout << v6.size() << std::endl;
    // std::cout << v6.capacity() << std::endl;

    // pointer_func(v.data(), v.size());
    // std::cout << v.size() << std::endl;
    // std::cout << v.capacity() << std::endl;
    // v.resize(14);
    // pointer_func(v.data(), v.size());
    // std::cout << v.size() << std::endl;
    // std::cout << v.capacity() << std::endl;
    // v.resize(16);
    // pointer_func(v.data(), v.size());
    // std::cout << v.size() << std::endl;
    // std::cout << v.capacity() << std::endl;

    // v.shrink_to_fit();
    // pointer_func(v.data(), v.size());
    // std::cout << v.size() << std::endl;
    // std::cout << v.capacity() << std::endl;


    // std::cout << (v == v6) << std::endl;
    // ft::vector<int> v7(v);
    // pointer_func(v7.data(), v7.size());
    // std::cout << (v == v7) << std::endl;
    // std::cout << *v.begin() << " " << *v7.begin() << std::endl;

    // ft::vector<double> v8, v9;
    // for (int i = 0; i < 6; ++i)
    // {
    //     v8.push_back(i / 3.0);
    //     v9.push_back(i / 3.0);
    // }
    // std::cout << "(v8 < v9) = " << (v8 < v9) << std::endl;
    // v9.push_back(19);
    // std::cout << "(v8 < v9 after push_back) = " << (v8 < v9) << std::endl;
    // v9.pop_back();
    // v9.pop_back();
    // std::cout << "(v9 after 2 pop_back < v8) = " << (v9 < v8) << std::endl;
    // std::cout << (v9 <= v8) << std::endl;
    // std::cout << (v9 > v8) << std::endl;
    // v8.pop_back();
    // v8.pop_back();
    // std::cout << (v9 > v8) << std::endl;
    // std::cout << (v9 >= v8) << std::endl;

    // v9[0] = 123;

    // std::cout << *(v9.begin()) << std::endl;

    // std::cout << std::endl << "using range loop" << std::endl;
    // for (auto it : v9)
    //     std::cout << it << ' ';
    // std::cout << std::endl;
    // std::cout << std::endl << "using iterators loop" << std::endl;
    // for (ft::vector<double>::iterator it = v9.begin(), end = v9.end(); it != end; ++it)
    //     std::cout << *it << ' ';
    // std::cout << std::endl;

    // std::cout << std::endl << "using const iterators loop" << std::endl;
    // for (ft::vector<double>::const_iterator it = v9.cbegin(), end = v9.cend(); it != end; ++it)
    //     std::cout << *it << ' ';
    // std::cout << std::endl;

    // auto const_it = v9.cbegin();
    // auto non_const_it = v9.begin();

    // *non_const_it = 5;

    // const_it += 2;
    // std::cout << *const_it << std::endl;

    // auto test_it1 = ++v9.begin();
    // auto test_it2 = v9.begin();

    // std::cout << (test_it1 > test_it2) << std::endl;
    // std::cout << (test_it1 >= test_it2) << std::endl;
    // std::cout << (test_it1 < test_it2) << std::endl;
    // std::cout << (test_it1 <= test_it2) << std::endl;
    // ++test_it2;
    // std::cout << (test_it1 <= test_it2) << std::endl;
    // ++test_it2;
    // std::cout << (test_it1 < test_it2) << std::endl;
    // std::cout << (test_it1 <= test_it2) << std::endl;

    // ft::vector<double>::reverse_iterator rit = v9.rbegin();

    // //std::cout << *rit << std::endl; //ILLEGAL
    // rit -= 1;
    // std::cout << *rit << std::endl;
    // rit -= 1;
    // std::cout << *rit << std::endl;

    // ft::vector<std::string> v10 = {"abc", "hello", "foo", "bar"};

    // for (auto it : v10)
    //     std::cout << it << ' ';
    // std::cout << std::endl;

    // ft::vector<int> v11 {1, 2};
    // v11.assign(10, 0);
    // for (auto i : v11)
    //     std::cout << i << ' ';
    // std::cout << std::endl;

    // ft::vector<int> v12{1, 2, 3, 4, 5};
    // v11.assign(v12.begin(), v12.end());

    // for (auto i : v11)
    //     std::cout << i << ' ';
    // std::cout << std::endl;

    // v11.assign({-1, -2, -3, -4, -5, -6, -7, -8});
    // for (auto i : v11)
    //     std::cout << i << ' ';
    // std::cout << std::endl;


    // ft::vector<int> v13 = {0, 1, 2, 3, 4, 5, 6};
    // std::cout << "Before insert" << std::endl;
    // for (auto i : v13)
    //     std::cout << i << ' ';
    // std::cout << "\nAfter Insert" << std::endl;
    // v13.insert(++(++v13.begin()), 2, -1);
    // v13.push_back(42);
    // for (auto i : v13)
    //     std::cout << i << ' ';
    // std::cout << std::endl;

    // ft::vector<std::string> v14 = {"foo", "bar", "hello", "world"};
    // std::cout << "Before insert" << std::endl;
    // for (auto i : v14)
    //     std::cout << i << ' ';
    // std::cout << "\nAfter Insert" << std::endl;
    // v14.insert(++(++v14.begin()), 2, "bla-bla");
    // v14.push_back("OOPS");
    // for (auto i : v14)
    //     std::cout << i << ' ';
    // std::cout << std::endl;

    // std::string temp("TEMP_STRING");

    // v14.insert(v14.end(), std::move(temp));
    // for (auto i : v14)
    //     std::cout << i << ' ';
    // std::cout << std::endl;


    // ft::vector<std::string> v15 {"NUM_1", "NUM_2", "NUM_3"};
    // v14.insert(v14.end(), v15.begin(), v15.end());
    // std::cout << *((v14.insert(++v14.begin(), {"ABC","BOOO","BAR", "FUN"}))) << std::endl;

    // for (auto i : v14)
    //     std::cout << i << ' ';
    // std::cout << std::endl;


    // auto it_1 = v14.begin();
    // auto it_2 = ++v14.cbegin();
    
    // // std::cout << *it_1 << std::endl;
    // it_1 = it_2;
    // // std::cout << *it_1 << std::endl;
    // it_2 = it_1;

    // ft::vector<int>::iterator reg_it(it_2);

    // std::cout << "v14.size() = " << v14.size() << std::endl;
    // std::cout << *v14.erase(++v14.begin(), ++++++v14.begin()) << std::endl;
    // for (auto i : v14)
    //     std::cout << i << ' ';
    // std::cout << std::endl;
    // std::cout << "v14.size() = " << v14.size() << std::endl;

    // v14.erase(--v14.end());
    // for (auto i : v14)
    //     std::cout << i << ' ';
    // std::cout << std::endl;


///////////////////////////////////////
// LIST
///////////////////////////////////////

    ft::list<int> l;
    l.push_back(455);
    l.push_back(-100);
    l.push_back(22222);
    l.push_back(42);

    for (auto it = l.begin(); it != l.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
    std::cout << "size = " << l.size() << std::endl;

    l.pop_back();
    for (auto it = l.begin(); it != l.end(); ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;
    std::cout << "size = " << l.size() << std::endl;

    l.push_back(21);

    
    for (auto it = l.cbegin(), end = l.cend(); it != end; ++it)
        std::cout << *it << ' ';
    std::cout << std::endl;

    ft::list<int>::const_iterator cit = l.cbegin();
    ft::list<int>::iterator it = ++++l.begin();
    ft::list<int>::iterator it2 = --l.end();
    std::cout << *it2 << std::endl;
    std::cout << *it << std::endl;


    std::cout << *cit << std::endl;
    cit = it;
    std::cout << *cit << std::endl;
    cit = --cit;
    std::cout << *cit << std::endl;
    cit = --l.cend();
    std::cout << *cit << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << *cit-- << std::endl;
    std::cout << *cit << std::endl;

    auto it3 = ++++l.rbegin();
    std::cout << *it3 << std::endl;

    l.print_all();
    auto it4 = l.insert(l.end(), 2, 0);
    l.print_all();

    std::cout << *(--it4) << std::endl;

    ft::list<A> l2;

    return 0;
}
