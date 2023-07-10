#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <stdexcept>

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
    //using iterator          = 
    // ADD ITERATORS

    ~vector()
    {
        while (m_size--)
            m_alloc.destroy(m_arr + m_size);
        m_alloc.deallocate(m_arr, m_capacity);
    }

    vector()
    {
        m_arr = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    vector( size_type count, const T& value, const Allocator& alloc = Allocator())
    {
        value_type* p = m_alloc.allocate(count * 2);
        value_type* q = p;
        while (q != p + count)
            m_alloc.construct(q++, value);
        m_arr = p;
        m_size = count;
        m_capacity = 2 * count;
    }

    explicit vector( size_type count, const Allocator& alloc = Allocator() ):
        m_alloc(alloc)
    {
        value_type* p = m_alloc.allocate(count * 2);
        value_type* q = p;
        value_type t;
        while (q != p + count)
            m_alloc.construct(q++, t);
        m_arr = p;
        m_size = count;
        m_capacity = 2 * count;
    }



    // Element access
    reference at( size_type pos )
    {
        if (pos < 0 || pos >= m_size)
            throw std::out_of_range("pos not in range of this vector");
        return m_arr[pos];
    }

    const_reference at( size_type pos ) const
    {
        if (pos < 0 || pos >= m_size)
            throw std::out_of_range("pos not in range of this vector");
        return m_arr[pos];
    }

    reference operator[]( size_type pos )
    {
        return m_arr[pos];
    }

    const_reference operator[]( size_type pos ) const
    {
        return m_arr[pos];
    }

    reference front()
    {
        return m_arr[0];
    }

    const_reference front() const
    {
        return m_arr[0];
    }

    reference back()
    {
        return m_arr[m_size - 1];
    }

    const_reference back() const
    {
        return m_arr[m_size - 1];
    }

    T* data() noexcept
    {
        return m_arr;
    }

    const T* data() const noexcept
    {
        return m_arr;;
    }


    void push_back(const value_type &val)
    {
        
    }

    // Capacity
    bool empty() const noexcept
    {
        return !m_size;
    }

    size_type size() const noexcept
    {
        return m_size;
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<difference_type>::max();
    }

    size_type capacity() const noexcept
    {
        return m_capacity;
    }

private:
    value_type* m_arr;
    size_type m_capacity;
    size_type m_size;
    allocator_type m_alloc;
};


} // namespace ft


#endif