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

        test_struct* test1 = new test_struct();
        test_struct* test2 = new test_struct();
        test_struct* test3 = new test_struct();
        test_struct* test4 = new test_struct();

        struct D<test_struct> del_struct;
        std::unique_ptr<test_struct, D<test_struct>> bla(test1, del_struct);

        ft::unique_ptr<test_struct, D<test_struct>> p_bla(test2, del_struct);
        ft::unique_ptr<test_struct, D<test_struct>> p_bla_2(test3, D<test_struct>());

        struct D<test_struct> del_struct2;
        ft::unique_ptr<test_struct, D<test_struct>> p_bla_3(test4, std::move(del_struct2));

        // ft::unique_ptr<test_struct> p_bla_4(std::move(p_bla));

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

TEST_SUITE("stack")
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-1000, 1000);

    TEST_CASE("stack basics")
    {
        ft::stack<int> s;
        std::stack<int> s_stl;

        SUBCASE("Capacity")
        {
            CHECK(s.size() == s_stl.size());
            CHECK(s.empty());

            s.push(5);
            s_stl.push(5);
            CHECK(s.size() == s_stl.size());
            CHECK_FALSE(s.empty());

            s.pop();
            s_stl.pop();
        }

        SUBCASE("Modifieres")
        {
            for (int i = 0; i < 15; ++i)
            {
                int x = dist(rng);
                s.push(x);
                s_stl.push(x);
            }

            // INFO("current iteration of loop:");
            for (std::size_t i = 0; i < 15; ++i)
            {
                // CAPTURE(i);
                CHECK(s.top() == s_stl.top());
                s.pop();
                s_stl.pop();
            }
        }
        CHECK(s.empty());
        CHECK(s.size() == s_stl.size());
    }

    TEST_CASE("Operators")
    {
        ft::stack<int> s;
        ft::stack<int> s2;
        for (int i = 0; i < 15; ++i)
        {
            int x = dist(rng);
            s.push(x);
            s2.push(x);
        }

        CHECK(s == s2);
        CHECK_FALSE(s != s2);
        CHECK_FALSE(s < s2);
        CHECK(s <= s2);
        CHECK_FALSE(s > s2);
        CHECK(s >= s2);

        s2.push(20);

        CHECK_FALSE(s == s2);
        CHECK(s != s2);
        CHECK(s < s2);
        CHECK(s <= s2);
        CHECK_FALSE(s > s2);
        CHECK_FALSE(s >= s2);

        s2.pop();

        CHECK(s == s2);
        CHECK_FALSE(s != s2);
        CHECK_FALSE(s < s2);
        CHECK(s <= s2);
        CHECK_FALSE(s > s2);
        CHECK(s >= s2);

        s2.pop();

        CHECK_FALSE(s == s2);
        CHECK(s != s2);
        CHECK_FALSE(s < s2);
        CHECK_FALSE(s <= s2);
        CHECK(s > s2);
        CHECK(s >= s2);

        ft::stack<int> s3;

        CHECK_FALSE(s == s3);
        CHECK(s != s3);
        CHECK_FALSE(s < s3);
        CHECK_FALSE(s <= s3);
        CHECK(s > s3);
        CHECK(s >= s3);
    }

}  // TEST_SUITE("stack")

TEST_SUITE("List")
{
    // struct custom_string
    // {
    //     char *str;

    //     custom_string(char* s)
    //     {
    //         str = new char[std::strlen(s) + 1]();
    //         std::strcpy(str, s);
    //         str[std::strlen(s)] = '\0';
    //     }
    // };

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 10);


    void check_list_data(ft::list<std::string>& l, std::list<std::string>& l_stl)
    {
        REQUIRE(l.size() == l_stl.size());
        auto sit = l_stl.cbegin(), end = l_stl.cend();
        auto it = l.cbegin();
        while (sit != end)
        {
            REQUIRE(*it == *sit);
            // std::cerr << *it << std::endl;
            // std::cerr << *sit << std::endl;
            ++sit;
            ++it;
        }
        CHECK(l.size() == l_stl.size());
        CHECK(l.back() == l_stl.back());
        CHECK(l.front() == l_stl.front());
    };

    TEST_CASE("basics: capacity, element access")
    {
        ft::list<std::string> l;
        std::list<std::string> l_stl;

        CHECK(l.empty());

        l.push_back("string");
        l_stl.push_back("string");
        CHECK_FALSE(l.empty());

        CHECK(l.size() == l_stl.size());
        CHECK(l.back() == l_stl.back());
        CHECK(l.front() == l_stl.front());

        l.pop_back();
        l_stl.pop_back();

        CHECK(l.size() == l_stl.size());

        for (int i = 0; i < 15; ++i)
        {
            int n = dist(rng);
            int r = dist(rng);
            std::string s(n + 1, 65 + r * 2);
            // std::cerr << "char = " << (char)(65 + r * 2) << ". string = " << s << std::endl;
            std::string s2(n + 1, 80 + r);
            std::string s3(s2);

            l.push_back(s);
            l_stl.push_back(s);
            l.push_back(std::move(s2));  // FIXME: mode doesn't work?
            l_stl.push_back(std::move(s3));
        }

        check_list_data(l, l_stl);
    }

    TEST_CASE("Operations")
    {
        ft::list<std::string> l;
        std::list<std::string> l_stl;
        for (int i = 0; i < 15; ++i)
        {
            int n = dist(rng);
            int r = dist(rng);
            std::string s(n + 1, 65 + r * 2);
            std::string s2(n + 1, 80 + r);
            std::string s3(s2);

            l.push_back(s);
            l_stl.push_back(s);
            l.push_back(std::move(s2));  // FIXME: mode doesn't work?
            l_stl.push_back(std::move(s3));
        }

        check_list_data(l, l_stl);

        l.sort();
        l_stl.sort();

        check_list_data(l, l_stl);

        // std::cerr << l.back().size() << std::endl;
        // std::cerr << l_stl.back().size() << std::endl;

        l.reverse();
        l_stl.reverse();

        check_list_data(l, l_stl);
        
        // ft::list<std::string> l2;
        // l2.push_back("123");
        // l2.push_back("TTT");
        // l2.push_back("FF");
        // l2.push_back("GGG");
        // l2.push_back("g46Fgqq");

        // std::list<std::string> l2_stl;
        // l2_stl.push_back("123");
        // l2_stl.push_back("TTT");
        // l2_stl.push_back("FF");
        // l2_stl.push_back("GGG");
        // l2_stl.push_back("g46Fgqq");

        // l.merge(l2);
        // l_stl.merge(l2_stl);
        // check_list_data(l, l_stl);

        l.pop_front();
        l.pop_front();
        l_stl.pop_front();
        l_stl.pop_front();

        check_list_data(l, l_stl);

        // l.sort();
        // l_stl.sort();

        // check_list_data(l, l_stl);
    }

}  // TEST_SUITE("List")
