#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <stack>
#include <string>
#include <vector>

#include "doctest.h"
#include "list.hpp"
#include "stack.hpp"
#include "unique_ptr.hpp"
#include "vector.hpp"

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

template <typename T>
struct Compare
{
    bool operator()(const T& a, const T& b) const
    {
        return a > b;
    }
};

void test_bla()
{
    std::unique_ptr<int> p;
}

TEST_SUITE("vector")
{
    TEST_CASE("vectors: push_back, Element access, Capacity")
    {
        ft::vector<int> v;
        std::vector<int> v_stl;

        CHECK(v.size() == v_stl.size());

        SUBCASE("push_back, size and []")
        {
            v.push_back(100);
            v_stl.push_back(100);

            CHECK(v.size() == v_stl.size());
            CHECK(v[0] == v_stl[0]);

            for (int i = -50; i < 60; ++i)
            {
                v.push_back(i);
                v_stl.push_back(i);
                CHECK(v.size() == v_stl.size());
            }

            for (std::size_t i = 0; i < v_stl.size(); ++i)
            {
                CHECK(v[i] == v_stl[i]);
            }
        }

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(-1000, 1000);

        for (int i = 0; i < 101; ++i)
        {
            int x = dist(rng);
            v.push_back(x);
            v_stl.push_back(x);
        }

        SUBCASE("at, front, back, data")
        {
            CHECK(v.at(0) == v_stl.at(0));
            CHECK(v.at(3) == v_stl.at(3));
            CHECK(v.at(43) == v_stl.at(43));

            CHECK(v.front() == v_stl.front());
            CHECK(v.back() == v_stl.back());
            CHECK(*v.data() == *v_stl.data());  // first value
        }

        SUBCASE("capacity: empty, reserve, capacity, shrink_to_fit")
        // max_size ????????
        {
            CHECK_FALSE(v.empty());
            CHECK(v.capacity() >= v.size());

            v.reserve(1000);
            CHECK(v.capacity() >= 1000);
            v.reserve(2000);
            CHECK(v.capacity() >= 2000);

            v.shrink_to_fit();
            CHECK(v.size() == v.capacity());

            // check the data remain the same
            for (std::size_t i = 0; i < v_stl.size(); ++i)
                CHECK(v[i] == v_stl[i]);
        }
    }

    TEST_CASE("vectors: Modifiers")
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

        ft::vector<unsigned char> v;
        std::vector<unsigned char> v_stl;

        SUBCASE("insert initializer_list")
        {
            v.insert(v.begin(), {});
            v_stl.insert(v_stl.begin(), {});
            CHECK(v.size() == v_stl.size());

            unsigned char a = dist(rng), b = dist(rng), c = dist(rng);
            unsigned char d1 = *(v.insert(v.begin(), {a, b, c}));
            unsigned char d2 = *(v_stl.insert(v_stl.begin(), {a, b, c}));
            for (int i = 0; i < 3; ++i)
                CHECK(v[i] == v_stl[i]);
            CHECK(d1 == d2);
        }

        SUBCASE("insert(cit pos, size_type count, const T& value)")
        {
            v.insert(v.begin(), 0, 'a');
            CHECK(v.size() == 0);
            CHECK_THROWS_AS(v.at(0), std::out_of_range);

            unsigned char a = dist(rng);

            v.insert(v.begin(), 11, a);
            v_stl.insert(v_stl.begin(), 11, a);

            CHECK(v.size() == v_stl.size());
            for (std::size_t i = 0; i < v_stl.size(); ++i)
                CHECK(v[i] == v_stl[i]);

            unsigned char d1 = *(v.insert(--v.end(), 11, 'b'));
            unsigned char d2 = *(v_stl.insert(--v_stl.end(), 11, 'b'));

            CHECK(v.size() == v_stl.size());
            for (std::size_t i = 0; i < v_stl.size(); ++i)
                CHECK(v[i] == v_stl[i]);
            CHECK(d1 == d2);
        }

        SUBCASE("insert(const_iterator pos, T&& value)")
        {
            unsigned char d1 = *(v.insert(v.begin(), 67));
            unsigned char d2 = *(v_stl.insert(v_stl.begin(), 67));

            CHECK(d1 == d2);
            CHECK(v[0] == v_stl[0]);

            d1 = *(v.insert(v.end(), 87));
            d2 = *(v_stl.insert(v_stl.end(), 87));
            CHECK(d1 == d2);
            CHECK(v[1] == v_stl[1]);
        }

        SUBCASE("insert(const_iterator pos, const T& value)")
        {
            for (int i = 0; i < 10; ++i)
            {
                v.insert(v.begin(), static_cast<const unsigned char&>(i));  // FIXME: only with static_cast???
                v_stl.insert(v_stl.begin(), i);
            }
            unsigned char c = 78;
            v.insert(++v.begin(), c);
            v_stl.insert(++v_stl.begin(), c);

            for (std::size_t i = 0; i < v_stl.size(); ++i)
                CHECK(v[i] == v_stl[i]);
        }

        SUBCASE("insert(const_iterator pos, const_iterator first, const_iterator last) AND clear")
        {
            ft::vector<unsigned char> v2;
            v2.insert(v2.begin(), {'a', 'b', 'c', 'd', 'e'});

            std::vector<unsigned char> v_stl2 = {'a', 'b', 'c', 'd', 'e'};

            v.insert(v.begin(), v2.begin(), v2.end());
            v_stl.insert(v_stl.begin(), v_stl2.begin(), v_stl2.end());

            for (std::size_t i = 0; i < v_stl.size(); ++i)
                CHECK(v[i] == v_stl[i]);
        }

        SUBCASE("clear")
        {
            v.insert(v.begin(), {'a', 'b', 'c', 'd'});
            std::size_t cap1 = v.capacity();

            v.clear();
            CHECK(v.size() == 0);
            CHECK(v.capacity() == cap1);
            v.clear();
            CHECK(v.size() == 0);
            CHECK(v.capacity() == cap1);
        }

        SUBCASE("erase, pop_back, resize")
        {
            unsigned char a = dist(rng), b = dist(rng), c = dist(rng);
            v.insert(v.begin(), {a, b, c, a, b, c, 'a', 'b', 'c'});
            v_stl.insert(v_stl.begin(), {a, b, c, a, b, c, 'a', 'b', 'c'});

            auto f = [&v, &v_stl]()
            {
                REQUIRE(v.size() == v_stl.size());
                INFO("current iteration of loop:");
                for (std::size_t i = 0; i < v_stl.size(); ++i)
                {
                    CAPTURE(i);
                    CHECK(v[i] == v_stl[i]);
                }
            };

            CHECK((v.end() == v.erase(v.end(), v.end())));  // FIXME: without () doesn't work
            f();

            v.erase(--v.end(), v.end());
            v_stl.erase(--v_stl.end(), v_stl.end());
            f();

            CHECK((v.erase(++v.begin(), --v.end()) == ++v.begin()));
            v_stl.erase(++v_stl.begin(), --v_stl.end());
            f();

            v.insert(v.end(), {a, b, c, a, b, c, 'a', 'b', 'c'});
            v_stl.insert(v_stl.end(), {a, b, c, a, b, c, 'a', 'b', 'c'});

            CHECK((v.erase(++ ++v.begin()) == ++ ++v.begin()));
            v_stl.erase(++ ++v_stl.begin());
            f();

            CHECK((v.erase(v.cend()) == v.cend()));
            f();

            CHECK((v.erase(v.cbegin()) == v.begin()));
            v_stl.erase(v_stl.begin());
            f();

            v.pop_back();
            v_stl.pop_back();
            f();

            v.resize(1);
            v_stl.resize(1);
            f();

            v.resize(10);
            v_stl.resize(10);
            f();

            v.resize(30, 'a');
            v_stl.resize(30, 'a');
            f();
        }

        CHECK(v.size() == v_stl.size());
    }

}  // TEST_SUITE("vector")

TEST_SUITE("uniqie_ptr")
{
    template <typename T>
    struct D
    {
        int number      = 5;
        int number2     = 10;
        std::string abc = "abc!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        void operator()(T* ptr)
        {
            delete ptr;
        }
    };

    TEST_CASE("basics")
    {
        ft::unique_ptr<int> p(new int(5));
        std::unique_ptr<int> p_stl(new int(5));
        CHECK(sizeof(p) == sizeof(p_stl));

        ft::unique_ptr<int, D<int>> p2(new int(5));
        std::unique_ptr<int, D<int>> p2_stl(new int(5));
        CHECK(sizeof(p2) == sizeof(p2_stl));
    }

    struct test_struct
    {
        int i         = 42;
        double pi     = 3.14;
        float f       = 4.0f;
        const char* s = "Hello, world!";

        friend bool operator==(const test_struct& a, const test_struct& b);
    };

    bool operator==(const test_struct& a, const test_struct& b)
    {
        return a.i == b.i && (std::abs(a.pi - b.pi) < 1.0 / 10000000) && (std::abs(a.f - b.f) < 1.0 / 10000000) &&
               (std::strcmp(a.s, b.s) == 0);
    }

    TEST_CASE("Observers")
    {
        test_struct* ptr     = new test_struct();
        test_struct* ptr_stl = new test_struct();

        ft::unique_ptr<test_struct> p(ptr);
        std::unique_ptr<test_struct> p_stl(ptr_stl);

        CHECK(sizeof(p) == sizeof(p_stl));
        CHECK(p.get()->i == p_stl.get()->i);
        CHECK(p.get()->pi == doctest::Approx(3.14));
        CHECK(p.get()->f == doctest::Approx(4.0f));
        CHECK(std::strcmp(p.get()->s, "Hello, world!") == 0);

        CHECK_FALSE(!p);
        ft::unique_ptr<float> pf;
        CHECK_FALSE(pf);

        test_struct t;
        CHECK(*p == t);

        t.f = 5.0f;
        CHECK_FALSE(*p == t);

        // TODO: add Modifiers
    }

}  // TEST_SUITE("uniqie_ptr")

// int main()
// {

// //     ft::stack<int> i;
// //     i.push(190);
// //     std::cout << i.top() << std::endl;
// //     i.push(80);
// //     std::cout << i.top() << std::endl;
// //     i.top() = 100;
// //     std::cout << i.top() << std::endl;
// //     if (!i.empty())
// //         std::cout << "H\n" << i.size() << std::endl;
// //     i.pop();
// //     std::cout << i.top() << '|' << i.size() << std::endl;

// //     std::cout << "i = " << i.top() << std::endl;

// //     ft::stack<int> k(std::move(i));

// //     std::cout << "k = " << k.top() << std::endl;

// //     ft::stack<int> p;

// //     p = std::move(k);
// //    //std::cout << "k = " << k.top() << std::endl;
// //     std::cout << "p = " << p.top() << std::endl;
// //     ft::stack<int> b;
// //     b.push(42);
// //     b.push(21);
// //     b.push(19);
// //     std::cout << "b size = " << b.size() << "\np size = " << p.size() << std::endl;
// //     b.swap(p);
// //     std::cout << "b size = " << b.size() << "\np size = " << p.size() << std::endl;

// //     ft::stack<int> test1, test2;
// //     test1.push(21);
// //     test2.push(42);
// //     test1.push(100);
// //     if (test1 < test2)
// //         std::cout << "test1 < test" << std::endl;
// //     if (test2 > test1)
// //         std::cout << "test2 > test1" << std::endl;

// //     if (test1 == test2)
// //         std::cout << "test1 == test" << std::endl;
// //     if (test1 != test2)
// //         std::cout << "test1 != test" << std::endl;

// //     test1.pop();
// //     test1.pop();
// //     test1.push(42);
// //     if (test1 == test2)
// //         std::cout << "test1 == test" << std::endl;
// //     if (test1 != test2)
// //         std::cout << "test1 != test" << std::endl;

// ///////////////////////////////////////
// // VECTOR
// ///////////////////////////////////////

//     // ft::vector<int> v;
//     // ft::vector<char> v2;
//     // ft::vector<int> v3(4);
//     // ft::vector<int> v4(15, 10);

//     // for (int i = 0; i < v4.size(); ++i)
//     //     std::cout << v4[i] << ' ';
//     // std::cout << std::endl;

//     // std::cout << v.empty() << std::endl;
//     // std::cout << v4.empty() << std::endl;
//     // std::cout << v.max_size() << std::endl;
//     // std::cout << v2.max_size() << std::endl;

//     // try
//     // {
//     //     v.at(0) = 1;
//     // }
//     // catch(const std::out_of_range &e)
//     // {
//     //     std::cerr << e.what() << '\n';
//     // }

//     // v4[0] = 1111;
//     // v4.at(14) = 2222;

//     // std::cout << v4.front() << std::endl;
//     // std::cout << v4.back() << std::endl;
//     // std::cout << v4.capacity() << std::endl;

//     // pointer_func(v4.data(), v4.size());

//     // if (!(v4.data()))
//     //     std::cout << "Invalid data" << std::endl;

//     // auto ptr = v4.data();
//     // std::cout << *ptr << std::endl;

//     // v4.reserve(100);
//     // std::cout << "capacity = " << v4.capacity() << std::endl;
//     // v4.reserve(10000);
//     // std::cout << v4.capacity() << std::endl;
//     // pointer_func(v4.data(), v4.size());

//     // ft::vector<int> v5(std::move(v4));
//     // pointer_func(v4.data(), v4.size());
//     // pointer_func(v5.data(), v5.size());

//     // v = std::move(v5);
//     // v = std::move(v);
//     // pointer_func(v5.data(), v5.size());
//     // pointer_func(v.data(), v.size());

//     // ft::vector<int> v6;

//     // for (int i = 0; i < 21; ++i)
//     // {
//     //     v6.push_back(i);
//     //     std::cout << "size = " << v6.size() << " | capacity = " << v6.capacity() << std::endl;
//     // }

//     // std::cout << v6.size() << std::endl;
//     // v6.clear();
//     // std::cout << v6.size() << std::endl;
//     // std::cout << v6.capacity() << std::endl;

//     // pointer_func(v.data(), v.size());
//     // std::cout << v.size() << std::endl;
//     // std::cout << v.capacity() << std::endl;
//     // v.resize(14);
//     // pointer_func(v.data(), v.size());
//     // std::cout << v.size() << std::endl;
//     // std::cout << v.capacity() << std::endl;
//     // v.resize(16);
//     // pointer_func(v.data(), v.size());
//     // std::cout << v.size() << std::endl;
//     // std::cout << v.capacity() << std::endl;

//     // v.shrink_to_fit();
//     // pointer_func(v.data(), v.size());
//     // std::cout << v.size() << std::endl;
//     // std::cout << v.capacity() << std::endl;

//     // std::cout << (v == v6) << std::endl;
//     // ft::vector<int> v7(v);
//     // pointer_func(v7.data(), v7.size());
//     // std::cout << (v == v7) << std::endl;
//     // std::cout << *v.begin() << " " << *v7.begin() << std::endl;

//     // ft::vector<double> v8, v9;
//     // for (int i = 0; i < 6; ++i)
//     // {
//     //     v8.push_back(i / 3.0);
//     //     v9.push_back(i / 3.0);
//     // }
//     // std::cout << "(v8 < v9) = " << (v8 < v9) << std::endl;
//     // v9.push_back(19);
//     // std::cout << "(v8 < v9 after push_back) = " << (v8 < v9) << std::endl;
//     // v9.pop_back();
//     // v9.pop_back();
//     // std::cout << "(v9 after 2 pop_back < v8) = " << (v9 < v8) << std::endl;
//     // std::cout << (v9 <= v8) << std::endl;
//     // std::cout << (v9 > v8) << std::endl;
//     // v8.pop_back();
//     // v8.pop_back();
//     // std::cout << (v9 > v8) << std::endl;
//     // std::cout << (v9 >= v8) << std::endl;

//     // v9[0] = 123;

//     // std::cout << *(v9.begin()) << std::endl;

//     // std::cout << std::endl << "using range loop" << std::endl;
//     // for (auto it : v9)
//     //     std::cout << it << ' ';
//     // std::cout << std::endl;
//     // std::cout << std::endl << "using iterators loop" << std::endl;
//     // for (ft::vector<double>::iterator it = v9.begin(), end = v9.end(); it != end; ++it)
//     //     std::cout << *it << ' ';
//     // std::cout << std::endl;

//     // std::cout << std::endl << "using const iterators loop" << std::endl;
//     // for (ft::vector<double>::const_iterator it = v9.cbegin(), end = v9.cend(); it != end; ++it)
//     //     std::cout << *it << ' ';
//     // std::cout << std::endl;

//     // auto const_it = v9.cbegin();
//     // auto non_const_it = v9.begin();

//     // *non_const_it = 5;

//     // const_it += 2;
//     // std::cout << *const_it << std::endl;

//     // auto test_it1 = ++v9.begin();
//     // auto test_it2 = v9.begin();

//     // std::cout << (test_it1 > test_it2) << std::endl;
//     // std::cout << (test_it1 >= test_it2) << std::endl;
//     // std::cout << (test_it1 < test_it2) << std::endl;
//     // std::cout << (test_it1 <= test_it2) << std::endl;
//     // ++test_it2;
//     // std::cout << (test_it1 <= test_it2) << std::endl;
//     // ++test_it2;
//     // std::cout << (test_it1 < test_it2) << std::endl;
//     // std::cout << (test_it1 <= test_it2) << std::endl;

//     // ft::vector<double>::reverse_iterator rit = v9.rbegin();

//     // //std::cout << *rit << std::endl; //ILLEGAL
//     // rit -= 1;
//     // std::cout << *rit << std::endl;
//     // rit -= 1;
//     // std::cout << *rit << std::endl;

//     // ft::vector<std::string> v10 = {"abc", "hello", "foo", "bar"};

//     // for (auto it : v10)
//     //     std::cout << it << ' ';
//     // std::cout << std::endl;

//     // ft::vector<int> v11 {1, 2};
//     // v11.assign(10, 0);
//     // for (auto i : v11)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // ft::vector<int> v12{1, 2, 3, 4, 5};
//     // v11.assign(v12.begin(), v12.end());

//     // for (auto i : v11)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // v11.assign({-1, -2, -3, -4, -5, -6, -7, -8});
//     // for (auto i : v11)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // ft::vector<int> v13 = {0, 1, 2, 3, 4, 5, 6};
//     // std::cout << "Before insert" << std::endl;
//     // for (auto i : v13)
//     //     std::cout << i << ' ';
//     // std::cout << "\nAfter Insert" << std::endl;
//     // v13.insert(++(++v13.begin()), 2, -1);
//     // v13.push_back(42);
//     // for (auto i : v13)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // ft::vector<std::string> v14 = {"foo", "bar", "hello", "world"};
//     // std::cout << "Before insert" << std::endl;
//     // for (auto i : v14)
//     //     std::cout << i << ' ';
//     // std::cout << "\nAfter Insert" << std::endl;
//     // v14.insert(++(++v14.begin()), 2, "bla-bla");
//     // v14.push_back("OOPS");
//     // for (auto i : v14)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // std::string temp("TEMP_STRING");

//     // v14.insert(v14.end(), std::move(temp));
//     // for (auto i : v14)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // ft::vector<std::string> v15 {"NUM_1", "NUM_2", "NUM_3"};
//     // v14.insert(v14.end(), v15.begin(), v15.end());
//     // std::cout << *((v14.insert(++v14.begin(), {"ABC","BOOO","BAR", "FUN"}))) << std::endl;

//     // for (auto i : v14)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

//     // auto it_1 = v14.begin();
//     // auto it_2 = ++v14.cbegin();

//     // // std::cout << *it_1 << std::endl;
//     // it_1 = it_2;
//     // // std::cout << *it_1 << std::endl;
//     // it_2 = it_1;

//     // ft::vector<int>::iterator reg_it(it_2);

//     // std::cout << "v14.size() = " << v14.size() << std::endl;
//     // std::cout << *v14.erase(++v14.begin(), ++++++v14.begin()) << std::endl;
//     // for (auto i : v14)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;
//     // std::cout << "v14.size() = " << v14.size() << std::endl;

//     // v14.erase(--v14.end());
//     // for (auto i : v14)
//     //     std::cout << i << ' ';
//     // std::cout << std::endl;

// ///////////////////////////////////////
// // LIST
// ///////////////////////////////////////

//     ft::list<int> l;
//     l.push_back(455);
//     l.push_back(-100);
//     l.push_back(22222);
//     l.push_back(42);

//     for (auto it = l.begin(); it != l.end(); ++it)
//         std::cout << *it << ' ';
//     std::cout << std::endl;
//     std::cout << "size = " << l.size() << std::endl;

//     l.pop_back();
//     for (auto it = l.begin(); it != l.end(); ++it)
//         std::cout << *it << ' ';
//     std::cout << std::endl;
//     std::cout << "size = " << l.size() << std::endl;

//     l.push_back(21);

//     for (auto it = l.cbegin(), end = l.cend(); it != end; ++it)
//         std::cout << *it << ' ';
//     std::cout << std::endl;

//     ft::list<int>::const_iterator cit = l.cbegin();
//     ft::list<int>::iterator it = ++++l.begin();
//     ft::list<int>::iterator it2 = --l.end();
//     std::cout << *it2 << std::endl;
//     std::cout << *it << std::endl;

//     std::cout << *cit << std::endl;
//     cit = it;
//     std::cout << *cit << std::endl;
//     cit = --cit;
//     std::cout << *cit << std::endl;
//     cit = --l.cend();
//     std::cout << *cit << std::endl;
//     std::cout << "-------------" << std::endl;
//     std::cout << *cit-- << std::endl;
//     std::cout << *cit << std::endl;

//     auto it3 = ++++l.rbegin();
//     std::cout << *it3 << std::endl;

//     l.print_all();
//     auto it4 = l.insert(l.end(), 2, 0);
//     l.print_all();

//     std::cout << *(--it4) << std::endl;

//     std::cout << "front: " <<  l.front() << std::endl;
//     const int& i = l.front();
//     l.pop_front();
//     std::cout << "front: " <<  l.front() << std::endl;

//     std::cout << "back: " <<  l.back() << std::endl;
//     l.push_back(150);
//     std::cout << "back: " <<  l.back() << std::endl;

//     ft::list<A> l2;
//     std::cout << "empty(): " << l.empty() << " and " << l2.empty() << std::endl;

//     l.push_back(-42);
//     std::cout << "before sort: " << std::endl;
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl << "After sort using custom comparator: " << std::endl;

//     l.sort(Compare<int>());

//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl << "After sort using default comparator: " << std::endl;

//     l.sort();
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl;

//     ft::list<int> l3;
//     l3.push_back(-111);
//     l3.push_back(0);
//     l3.push_back(12);
//     l3.push_back(56);

//     l.merge(l3);

//     std::cerr << "Before reverse()" << std::endl;
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl;

//     l.reverse();

//     std::cerr << "After reverse()" << std::endl;
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl;

//     l.push_front(-1);
//     l.push_front(-2);
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl;

//     ft::list<std::string> l4;
//     std::string temp1("Hello");
//     std::string temp2("World");
//     l4.push_front(std::move(temp1));
//     l4.push_front(std::move(temp2));

//     for (auto s : l4)
//         std::cout << s << ' ';
//     std::cout << std::endl;

//     // l.insert(l.begin(), 1, 1);
//     l.erase(l.begin(), ++++++l.begin());
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl;
//     l.erase(l.begin());
//     for (auto i : l)
//         std::cout << i << ' ';
//     std::cout << std::endl;

//     return 0;
// }
