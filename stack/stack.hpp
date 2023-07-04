#ifndef STACK_HPP
#define STACK_HPP

#include <deque>

namespace ft {
                                    //REPLACE IN THE FUTURE
template <class T, class Container = std::deque<T> > class stack
{
public:
    typedef typename Container::value_type		value_type;
    typedef typename Container::reference		reference;
    typedef typename Container::const_reference	const_reference;
    typedef typename Container::size_type		size_type;
    typedef	         Container			        container_type;

protected:
    container_type c;

public:
    
    stack(): c() { }

    ~stack() { }

    stack(const stack &s): c(s.c) { }

    stack(stack &&s): c(std::move(s.c)) { }

    stack& operator=(stack &&s)
    {
        c = std::move(s.c);
        return *this;
    }

    //Element access
    const value_type& top() const
    {
        return c.back();
    }

    value_type& top()
    {
        return c.back();
    }
    
    //Capacity
    bool empty() const
    {
        return c.empty();
    }

    size_type size() const
    {
        return c.size();
    }

    //Modifiers
    void push(const value_type& val)
    {
        c.push_back(val);
    }
    //void push( value_type&& value );

    //template< class... Args >
    //void emplace( Args&&... args );

    void pop()
    {
        c.pop_back();
    }
    //void swap( stack& other ) noexcept(/* see below */);

};

} //namespace ft

#endif //STACK_HPP