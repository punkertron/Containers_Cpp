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
    
    stack() = default;
    explicit stack( const Container& cont ): c(cont) { }
    explicit stack( Container&& cont ): c(std::move(cont)) { }
    stack(const stack &s): c(s.c) { }
    stack(stack &&s): c(std::move(s.c)) { }

    ~stack() = default;

    stack& operator=( const stack& other )
    {
        c = other.c;
        return *this;
    }

    stack& operator=(stack &&s)
    {
        c = std::move(s.c);
        return *this;
    }

    //Element access
    reference top()
    {
        return c.back();
    }
    
    const_reference top() const
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
    
    void push( value_type&& value )
    {
        c.push_back(std::move(value));
    }

    template< class... Args >
    void emplace( Args&&... args )
    {
        c.emplace_back(std::forward<Args>(args)...);
    }

    void pop()
    {
        c.pop_back();
    }
    
    void swap( stack& other ) //noexcept(/* see below */);
    {
        std::swap(c, other.c);
    }

    template <class U, class F>
    inline friend bool operator<(stack<U, F> &x, stack<U, F> &y);

    template <class U, class F>
    inline friend bool operator==(stack<U, F> &x, stack<U, F> &y);

}; // class stack

template <class U, class F>
inline bool operator<(stack<U, F> &x, stack<U, F> &y)
{
    return x.c < y.c;
}

//based on operator<
template <class U, class F>
inline bool operator<=(stack<U, F> &x, stack<U, F> &y)
{
    return !(y < x);
}

//based on operator<
template <class U, class F>
inline bool operator>=(stack<U, F> &x, stack<U, F> &y)
{
    return !(x < y);
}

//based on operator<
template <class U, class F>
inline bool operator>(stack<U, F> &x, stack<U, F> &y)
{
    return y < x;
}

template <class U, class F>
inline bool operator==(stack<U, F> &x, stack<U, F> &y)
{
    return x.c == y.c;
}

//based on operator==
template <class U, class F>
inline bool operator!=(stack<U, F> &x, stack<U, F> &y)
{
    return !(x == y);
}

} //namespace ft

#endif // STACK_HPP