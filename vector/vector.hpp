#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{
template <class T, class Allocator = std::allocator<T> >
class vector
{


public:
    using value_type        = T;
    using allocator_type    = Allocator;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using pointer           = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer     = typename std::allocator_traits<Allocator>::const_pointer;
    // ADD ITERATORS


    vector()
    {
        //allocator_type = std::allocator<value_type>;
    }

    void push_back(const value_type &val)
    {
        
    }

private:
    value_type* arr;
    size_type capacity;
    size_type size;
};


} // namespace ft


#endif