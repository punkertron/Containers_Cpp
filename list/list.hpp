#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>
#include "list_iterator.hpp"

namespace ft {

template<class T, class Allocator = std::allocator<T>>
class list
{
public:
    using value_type        = T;
    using allocator_type    = Allocator;
    using pointer           = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer     = typename std::allocator_traits<Allocator>::const_pointer;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    using iterator          = list_iterator<value_type>;

    ~list()
    {
        ;
    }

    // list(): list(Allocator()) {};

    // explicit list( const Allocator& alloc ): alloc(alloc)
    // {
    //     ;
    // }

    // explicit list( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): alloc(alloc)
    // {
    //     ;
    // }

    void push_back( const T& value )
    {
        ListNode<T>* newNode = new ListNode<value_type>(value);
        if (tail)
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else
        {
            head = tail = newNode;
        }
        ++m_size;
    }

    iterator begin()
    {
        return iterator(head);
    }

    iterator end()
    {
        return iterator(nullptr);
    }

    size_type size() const noexcept
    {
        return m_size;
    }

private:
    Allocator alloc;
    ListNode<value_type>* head;
    ListNode<value_type>* tail;
    size_type m_size = 0;

};

} // namespace ft

#endif // LIST_HPP