#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <type_traits>

namespace ft
{

template <class T>
struct vec_iterator
{
   public:
    using iterator_type     = T;
    using iterator_category = typename std::iterator_traits<iterator_type>::iterator_category;
    using value_type        = typename std::iterator_traits<iterator_type>::value_type;
    using difference_type   = typename std::iterator_traits<iterator_type>::difference_type;
    using pointer           = typename std::iterator_traits<iterator_type>::pointer;
    using reference         = typename std::iterator_traits<iterator_type>::reference;
    using size_type         = std::size_t;

    vec_iterator(pointer ptr) : m_ptr(ptr) { ; }

    template <class U>
    vec_iterator(const vec_iterator<U>& other)
    {
        m_ptr = (pointer)other.m_ptr;
    }

    vec_iterator(const vec_iterator& other) { m_ptr = other.m_ptr; }

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

    vec_iterator& operator-(size_type n)
    {
        m_ptr -= n;
        return *this;
    }

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

    pointer operator->() { return m_ptr; }

    reference operator*() { return *m_ptr; }

    reference operator[](size_type pos) { return *(m_ptr + pos); }

    bool operator<(const vec_iterator& other) { return m_ptr < other.m_ptr; }

    bool operator>(const vec_iterator& other) { return other.m_ptr < m_ptr; }

    bool operator<=(const vec_iterator& other) { return !(m_ptr > other.m_ptr); }

    bool operator>=(const vec_iterator& other) { return !(m_ptr < other.m_ptr); }

    bool operator==(const vec_iterator& other) { return m_ptr == other.m_ptr; }

    bool operator!=(const vec_iterator& other) { return !operator==(other); }

    size_type operator-(const vec_iterator& other) { return m_ptr - other.m_ptr; }

   private:
    pointer m_ptr;

    template <class U>
    friend class vec_iterator;
};

}  // namespace ft

#endif  // VECTOR_ITERATOR_HPP