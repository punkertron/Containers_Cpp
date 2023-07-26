#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <type_traits>

namespace ft
{

template <typename T>
struct ListNode
{
    T data;
    ListNode* next;
    ListNode* prev;

    ListNode(const T& value):
        data(value), next(nullptr), prev(nullptr)
    {
    }
};


template <class T>
struct list_iterator
{
private:
    ListNode<T>* current;

public:
    explicit list_iterator(ListNode<T>* node):
        current(node)
    {
    }

    T& operator*() const
    {
        return current->data;
    }

    bool operator==(const list_iterator& other) const
    {
        return current == other.current;
    }

    bool operator!=(const list_iterator& other) const
    {
        return !(*this == other);
    }

    list_iterator operator++()
    {
        current = current->next;
        return *this;
    }
};
    
} // namespace ft


#endif // LIST_ITERATOR_HPP