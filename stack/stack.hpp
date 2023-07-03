#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

namespace ft {

template <class T, class Container = std::deque<T> > class stack
{
public:
    typedef typename Container::value_type		value_type;
    //typedef typename Container::reference		reference;
    //typedef typename Container::const_reference	const_reference;
    typedef size_t		size_type;
    typedef	         Container			        container_type;

protected:
    container_type c;

public:
    void push(const value_type& val)
    {
        c.push_back(val);
    }


    const value_type& top() const
    {
        return c.back();
    }
    value_type& top()
    {
        return c.back();
    }
};

} //namespace ft

#endif