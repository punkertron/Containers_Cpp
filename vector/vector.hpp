#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>
#include <utility>

#include "vector_iterator.hpp"

namespace ft
{
template <class T, class Allocator = std::allocator<T> >
class vector
{
   public:
    using AllocTraits = std::allocator_traits<Allocator>;

    using value_type      = T;
    using allocator_type  = Allocator;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    // using pointer                   = T*;
    // using const_pointer             = const T*;
    using pointer       = typename AllocTraits::pointer;
    using const_pointer = typename AllocTraits::const_pointer;

    // using iterator                  = vec_iterator<vector<value_type, allocator_type> >;
    // using const_iterator            = vec_iterator<vector<const value_type, allocator_type> >;

    using iterator               = vec_iterator<pointer>;
    using const_iterator         = vec_iterator<const_pointer>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    ~vector()
    {
        while (m_size--)
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        // m_alloc.destroy(m_arr + m_size);
        AllocTraits::deallocate(m_alloc, m_arr, m_capacity);
        // m_alloc.deallocate(m_arr, m_capacity);
    }

    vector()
    {
        m_arr      = nullptr;
        m_capacity = 0;
        m_size     = 0;
    }

    vector(size_type count, const T& value, const Allocator& alloc = Allocator()) : m_alloc(std::move(alloc))
    {
        pointer p = AllocTraits::allocate(m_alloc, count * 2);
        // value_type* p = m_alloc.allocate(count * 2);
        pointer q = p;
        while (q != p + count)
            AllocTraits::construct(m_alloc, q++, value);
        // m_alloc.construct(q++, value);
        m_arr      = p;
        m_size     = count;
        m_capacity = 2 * count;
    }

    explicit vector(size_type count, const Allocator& alloc = Allocator()) : m_alloc(std::move(alloc))
    {
        pointer p = AllocTraits::allocate(m_alloc, count * 2);
        // value_type* p = m_alloc.allocate(count * 2);
        pointer q = p;
        value_type t;
        while (q != p + count)
            AllocTraits::construct(m_alloc, q++, t);
        // m_alloc.construct(q++, t);
        m_arr      = p;
        m_size     = count;
        m_capacity = 2 * count;
    }

    vector(const vector& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_alloc(other.m_alloc)
    {
        pointer p   = AllocTraits::allocate(m_alloc, m_capacity);
        size_type i = 0;
        while (i < m_size)
        {
            AllocTraits::construct(m_alloc, p + i, *(other.m_arr + i));
            ++i;
        }
        m_arr = p;
    }

    vector(vector&& other) :
        m_arr(other.m_arr), m_size(other.m_size), m_capacity(other.m_capacity), m_alloc(std::move(other.m_alloc))
    {
        other.m_arr      = nullptr;
        other.m_size     = 0;
        other.m_capacity = 0;
    }

    vector(std::initializer_list<T> init, const Allocator& alloc = Allocator()) :
        m_size(0), m_capacity(sizeof(init)), m_alloc(alloc)
    {
        m_arr = AllocTraits::allocate(m_alloc, m_capacity);

        for (auto i : init)
            push_back(i);
    }

    vector& operator=(vector&& other)
    {
        if (this == &other)
            return *this;

        while (m_size--)
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        AllocTraits::deallocate(m_alloc, m_arr, m_capacity);

        m_arr            = other.m_arr;
        m_size           = other.m_size;
        m_capacity       = other.m_capacity;
        m_alloc          = std::move(other.m_alloc);
        other.m_arr      = nullptr;
        other.m_size     = 0;
        other.m_capacity = 0;
        return *this;
    }

    void assign(size_type count, const T& value)
    {
        size_type i = 0;

        while (i < m_size && i < count)
        {
            *(m_arr + i) = value;
            ++i;
        }
        while (i < count)
        {
            push_back(value);
            ++i;
        }
    }

    // should implement all iterators?
    // template< class InputIt >
    void assign(iterator first, iterator last)
    {
        clear();

        while (first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    void assign(std::initializer_list<T> ilist)
    {
        clear();

        for (auto i : ilist)
            push_back(i);
    }

    allocator_type get_allocator() const noexcept
    {
        return m_alloc;
    }

    // Element access
    reference at(size_type pos)
    {
        if (pos >= m_size)
            throw std::out_of_range("pos not in range of this vector");
        return m_arr[pos];
    }

    const_reference at(size_type pos) const
    {
        if (pos >= m_size)
            throw std::out_of_range("pos not in range of this vector");
        return m_arr[pos];
    }

    reference operator[](size_type pos)
    {
        return m_arr[pos];
    }

    const_reference operator[](size_type pos) const
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
        return m_arr;
        ;
    }

    // Iterators
    iterator begin()
    {
        return iterator(m_arr);
    }

    const_iterator cbegin() const noexcept
    {
        return const_iterator(m_arr);
    }

    iterator end()
    {
        return iterator(m_arr + m_size);
    }

    const_iterator cend() const noexcept
    {
        return const_iterator(m_arr + m_size);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(m_arr);
    }

    const_reverse_iterator rcbegin() const noexcept
    {
        return const_reverse_iterator(m_arr);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(m_arr + m_size);
    }

    const_reverse_iterator rcend() const noexcept
    {
        return const_reverse_iterator(m_arr + m_size);
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

    void reserve(size_type new_cap)
    {
        if (m_capacity > new_cap)
            return;
        if (new_cap > max_size())
            throw std::length_error("new_cap > max_size()");

        pointer newarr = AllocTraits::allocate(m_alloc, new_cap);

        for (size_type i = 0; i < m_size; ++i)
        {
            AllocTraits::construct(m_alloc, newarr + i, std::move(*(m_arr + i)));
        }
        AllocTraits::deallocate(m_alloc, m_arr, m_capacity);
        // m_alloc.deallocate(m_arr, m_capacity);
        m_arr      = newarr;
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
            m_arr      = newarr;
            m_capacity = m_size;
        }
    }

    // Modifiers
    void clear() noexcept
    {
        while (m_size--)
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        m_size = 0;
    }

    iterator insert(const_iterator pos, size_type count, const T& value)
    {
        size_type i;
        if (m_size == 0)
            i = 0;
        else
            i = &(*pos) - m_arr;
        if (m_capacity == 0)
            reserve(10);
        if (m_size + count > m_capacity)
            reserve(m_capacity * 2);
        if (count > 0)
        {
            for (size_type j = m_size + count - 1; j >= i + count; --j)
                AllocTraits::construct(m_alloc, m_arr + j, std::move(*(m_arr + j - count)));
            m_size += count;
            while (count)
            {
                AllocTraits::construct(m_alloc, m_arr + i + count - 1, value);
                --count;
            }
        }
        pos = m_arr + i;
        return pos;
    }

    iterator insert(const_iterator pos, const T& value)
    {
        return insert(pos, 1, value);
    }

    iterator insert(const_iterator pos, T&& value)
    {
        size_type i = pos - m_arr;
        if (m_capacity == 0)
            reserve(10);
        if (m_size == m_capacity)
            reserve(m_capacity * 2);
        if (m_size > 0)
        {
            for (size_type j = m_size - 1; j >= i; --j)
                AllocTraits::construct(m_alloc, m_arr + j, std::move(*(m_arr + j)));
            AllocTraits::construct(m_alloc, m_arr + i, std::move(value));
        }
        else
        {
            AllocTraits::construct(m_alloc, m_arr, std::move(value));
        }
        ++m_size;
        pos = m_arr + i;
        return pos;
    }

    iterator insert(const_iterator pos, const_iterator first, const_iterator last)
    {
        size_type i = pos - m_arr;
        while (first != last)
        {
            pos = insert(pos, 1, *first);
            ++pos;
            ++first;
        }
        return m_arr + i;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist)
    {
        size_type i = pos - m_arr;
        for (auto i : ilist)
        {
            pos = insert(pos, 1, i);
            ++pos;
        }
        return m_arr + i;
    }

    iterator erase(const_iterator pos)
    {
        if (pos == end())
            return pos;
        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        if (first == end() || first == last)
            return last;
        size_type to_erase = last - first;
        size_type i        = first - m_arr;

        bool last_is_end = last == end();
        size_type to_move;
        if (!last_is_end)
            to_move = end() - last;

        while (first != last)
        {
            AllocTraits::destroy(m_alloc, &(*first));
            ++first;
        }
        m_size -= to_erase;

        if (last == end() + to_erase)
            return end();

        if (!last_is_end)
        {
            size_type j = 0;

            while (j != to_move)
            {
                AllocTraits::construct(m_alloc, m_arr + i + j, std::move(*(m_arr + i + to_erase + j)));
                ++j;
            }
        }
        return m_arr + i;
    }

    void push_back(const value_type& val)
    {
        insert(end(), 1, val);

        // if (m_capacity == 0)
        //     reserve(10);
        // if (m_size == m_capacity)
        //     reserve(m_capacity * 2);
        // AllocTraits::construct(m_alloc, m_arr + m_size, val);
        // ++m_size;
    }

    void push_back(value_type&& val)
    {
        insert(end(), std::move(val));

        /*
        if (m_capacity == 0)
            reserve(10);
        if (m_size == m_capacity)
            reserve(m_capacity * 2);
        AllocTraits::construct(m_alloc, m_arr + m_size, std::move(val));
        ++m_size;
        */
    }

    void pop_back()
    {
        --m_size;
        AllocTraits::destroy(m_alloc, m_arr + m_size);
    }

    void resize(size_type count, const value_type& value)
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

    void resize(size_type count)
    {
        // value_type t;
        // resize(count, t);

        while (count < m_size)
        {
            --m_size;
            AllocTraits::destroy(m_alloc, m_arr + m_size);
        }
        while (count > m_size)
        {
            push_back(value_type());
        }
    }

    void swap(vector& other)
    {
        ;
    }

   private:
    value_type* m_arr;
    size_type m_capacity;
    size_type m_size;
    allocator_type m_alloc;
};

template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
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

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
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

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return operator<(rhs, lhs);
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return !operator<(lhs, rhs);
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
    return !operator>(lhs, rhs);
}

}  // namespace ft

#endif  // VECTOR_HPP