#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <stdexcept>
#include <utility>

#include "vector_iterator.hpp"

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
    
    using iterator          = vec_iterator<vector<value_type, allocator_type> >;
    using const_iterator    = vec_iterator<vector<const value_type, allocator_type> >;

    using AllocTraits       = std::allocator_traits<Allocator>;

    ~vector()
    {
        while (m_size--)
            AllocTraits::destroy(m_alloc, m_arr + m_size);
            //m_alloc.destroy(m_arr + m_size);
        AllocTraits::deallocate(m_alloc, m_arr, m_capacity);
        //m_alloc.deallocate(m_arr, m_capacity);
    }

    vector()
    {
        m_arr = nullptr;
        m_capacity = 0;
        m_size = 0;
    }

    vector( size_type count, const T& value, const Allocator& alloc = Allocator()):
        m_alloc(std::move(alloc))
    {
        pointer p = AllocTraits::allocate(m_alloc, count * 2);
        //value_type* p = m_alloc.allocate(count * 2);
        pointer q = p;
        while (q != p + count)
            AllocTraits::construct(m_alloc, q++, value);
            //m_alloc.construct(q++, value);
        m_arr = p;
        m_size = count;
        m_capacity = 2 * count;
    }

    explicit vector( size_type count, const Allocator& alloc = Allocator() ):
        m_alloc(std::move(alloc))
    {
        pointer p = AllocTraits::allocate(m_alloc, count * 2);
        //value_type* p = m_alloc.allocate(count * 2);
        pointer q = p;
        value_type t;
        while (q != p + count)
            AllocTraits::construct(m_alloc, q++, t);
            //m_alloc.construct(q++, t);
        m_arr = p;
        m_size = count;
        m_capacity = 2 * count;
    }

    vector( const vector& other ):
        m_size(other.m_size), m_capacity(other.m_capacity), m_alloc(other.m_alloc)
    {
        pointer p = AllocTraits::allocate(m_alloc, m_capacity);
        size_type i = 0;
        while (i < m_size)
        {
            AllocTraits::construct(m_alloc, p + i, *(other.m_arr + i));
            ++i;
        }
        m_arr = p;
    }

    vector(vector&& other):
        m_arr(other.m_arr), m_size(other.m_size), m_capacity(other.m_capacity),
        m_alloc(std::move(other.m_alloc))
    {
        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    vector& operator=(vector&& other)
    {
        if (this == &other)
            return *this;

        while (m_size--)
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        AllocTraits::deallocate(m_alloc, m_arr, m_capacity);
        
        m_arr = other.m_arr;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_alloc = std::move(other.m_alloc);
        other.m_arr = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        return *this;
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
        if (m_capacity == 0)
            reserve(10);
        if (m_size == m_capacity)
            reserve(m_capacity * 2);
        AllocTraits::construct(m_alloc, m_arr + m_size, val);
        ++m_size;
    }

    void push_back(value_type &&val)
    {
        if (m_capacity == 0)
            reserve(10);
        if (m_size == m_capacity)
            reserve(m_capacity * 2);
        AllocTraits::construct(m_alloc, m_arr + m_size, std::move(val));
        ++m_size;
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

    void reserve( size_type new_cap )
    {
        if (m_capacity > new_cap)
            return ;
        if (new_cap > max_size())
            throw std::length_error ("new_cap > max_size()");
        
        pointer newarr = AllocTraits::allocate(m_alloc, new_cap);

        for (size_type i = 0; i < m_size; ++i)
        {
            AllocTraits::construct(m_alloc, newarr + i, std::move(*(m_arr + i)));
        }
        AllocTraits::deallocate(m_alloc, m_arr, m_capacity);
        //m_alloc.deallocate(m_arr, m_capacity);
        m_arr = newarr;
        m_capacity = new_cap;
    }

    size_type capacity() const noexcept
    {
        return m_capacity;
    }

    void shrink_to_fit()
    {
        if (m_capacity > m_size)
        {
            pointer newarr = AllocTraits::allocate(m_alloc, m_size);
            for (size_type i = 0; i < m_size; ++i)
            {
                AllocTraits::construct(m_alloc, newarr + i, std::move(*(m_arr + i)));
            }
            AllocTraits::deallocate(m_alloc, m_arr, m_capacity);
            m_arr = newarr;
            m_capacity = m_size;
        }
    }



    // Modifiers
    void clear() noexcept
    {
        std::cout << m_size << std::endl;
        while (m_size--)
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        m_size = 0;
    }

    void pop_back()
    {
        --m_size;
        AllocTraits::destroy(m_alloc, m_arr + m_size);
    }

    void resize( size_type count, const value_type& value )
    {
        while (count < m_size)
        {
            --m_size;
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        }
        while (count > m_size)
        {
            push_back(value);
        }
    }

    void resize( size_type count )
    {
        value_type t;
        resize(count, t);
    }


    iterator begin()
    {
        return iterator(m_arr);
    }

    iterator end()
    {
        return iterator(m_arr + m_size);
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(m_arr);
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(m_arr + m_size);
    }


private:
    value_type* m_arr;
    size_type m_capacity;
    size_type m_size;
    allocator_type m_alloc;
};

template< class T, class Alloc >
bool operator==( const vector<T, Alloc>& lhs,
                 const vector<T, Alloc>& rhs )
{
    typename vector<T, Alloc>::size_type i = 0, lhs_n = lhs.size(), rhs_n = rhs.size();

    if (lhs_n != rhs_n)
        return false;
    while (i < lhs_n && i < rhs_n)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
        ++i;
    }
    return true;
}

template< class T, class Alloc >
bool operator<( const vector<T, Alloc>& lhs,
                const vector<T, Alloc>& rhs )
{
    typename vector<T, Alloc>::size_type i = 0, lhs_n = lhs.size(), rhs_n = rhs.size();
    
    while (i < lhs_n && i < rhs_n)
    {
        if (lhs[i] < rhs[i])
        {
            return true;
        }
        ++i;
    }
    if (lhs_n < rhs_n)
        return true;
    return false;
}

template< class T, class Alloc >
bool operator>( const vector<T, Alloc>& lhs,
                const vector<T, Alloc>& rhs )
{
    return operator<(rhs, lhs);
}

template< class T, class Alloc >
bool operator>=( const vector<T, Alloc>& lhs,
                 const vector<T, Alloc>& rhs )
{
    return operator<(rhs, lhs) || operator==(rhs, lhs);
}

template< class T, class Alloc >
bool operator<=( const vector<T, Alloc>& lhs,
                 const vector<T, Alloc>& rhs )
{
    return operator<(lhs, rhs) || operator==(lhs, rhs);
}


} // namespace ft


#endif // VECTOR_HPP