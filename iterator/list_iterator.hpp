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

    ListNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <class T, bool IsConst = false>
struct list_iterator
{
   private:
    ListNode<T>* current;

   public:
    using value_type = T;
    using reference  = std::conditional_t<IsConst, const value_type&, value_type&>;
    using pointer    = std::conditional_t<IsConst, const value_type*, value_type*>;

    // template <bool B = IsConst, typename std::enable_if_t<!B, int>::type = 0>
    // list_iterator(const list_iterator<value_type, true>& other) : current(other.current) {}

    // template <bool B = IsConst, std::enable_if_t<B, int> = 0>
    //     list_iterator& operator=(const list_iterator& other) {
    //         if (this != &other) {
    //             current = other.current;
    //         }
    //         return *this;
    //     }

    operator list_iterator<value_type, true>() const { return list_iterator<value_type, true>(current); }

    explicit list_iterator(ListNode<T>* node) : current(node) {}

    //    explicit list_iterator(ListNode<T>* node, ListNode<T>* tail) : current(node), m_tail(tail) {}

    reference operator*() const { return current->data; }

    bool operator==(const list_iterator& other) const { return current == other.current; }

    bool operator!=(const list_iterator& other) const { return !(*this == other); }

    list_iterator& operator++()
    {
        current = current->next;
        return *this;
    }

    list_iterator& operator--()
    {
        current = current->prev;
        return *this;
    }
};

}  // namespace ft

#endif  // LIST_ITERATOR_HPP