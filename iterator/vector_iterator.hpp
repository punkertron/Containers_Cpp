#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>
#include <type_traits>

namespace ft {

template <class T>
struct vec_iterator
{
public:

    using iterator_category = std::random_access_iterator_tag;
    using value_type        = typename T::value_type;;
    using difference_type   = typename T::difference_type;
    using pointer           = typename T::pointer;
    using reference         = typename T::reference;

    using size_type         = typename T::size_type;
    using const_pointer     = typename T::const_pointer;
    using const_reference   = typename T::const_reference;

    vec_iterator(pointer ptr): m_ptr(ptr)
    {
        ;
    }

    vec_iterator& operator=(const vec_iterator& other)
    {
        m_ptr = other.m_ptr;
        return *this;
    }

    vec_iterator& operator++()
    {
        ++m_ptr;
        return *this;
    }

    vec_iterator operator++(int)
    {
        vec_iterator it = *this;
        ++(*this);
        return it;
    }

    vec_iterator& operator--()
    {
        --m_ptr;
        return *this;
    }

    vec_iterator operator--(int)
    {
        vec_iterator it = *this;
        --(*this);
        return it;
    }

    vec_iterator& operator+(size_type n)
    {
        m_ptr += n;
        return *this;
    }

    // vec_iterator& operator-(size_type n)
    // {
    //     m_ptr -= n;
    //     return *this;
    // }

    vec_iterator& operator+=(size_type n)
    {
        m_ptr += n;
        return *this;
    }

    vec_iterator& operator-=(size_type n)
    {
        m_ptr -= n;
        return *this;
    }

    pointer operator->()
    {
        return m_ptr;
    }

    reference operator*()
    {
        return *m_ptr;
    }

    reference operator[](size_type pos)
    {
        return *(m_ptr + pos);
    }

    const_pointer operator->() const
    {
        return m_ptr;
    }

    const_reference operator*() const
    {
        return *m_ptr;
    }

    const_reference operator[](size_type pos) const
    {
        return *(m_ptr + pos);
    }

    bool operator<(const vec_iterator& other)
    {
        return m_ptr < other.m_ptr;
    }

    bool operator>(const vec_iterator& other)
    {
        return other.m_ptr < m_ptr;
    }

    bool operator<=(const vec_iterator& other)
    {
        return !(m_ptr > other.m_ptr);
    }

    bool operator>=(const vec_iterator& other)
    {
        return !(m_ptr < other.m_ptr);
    }

    bool operator==(const vec_iterator& other)
    {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const vec_iterator& other)
    {
        return !operator==(other);
    }

    size_type operator-(const vec_iterator& other)
    {
        return m_ptr - other.m_ptr;
    }

private:
    pointer m_ptr;
};


} // namespace ft

#endif // VECTOR_ITERATOR_HPP