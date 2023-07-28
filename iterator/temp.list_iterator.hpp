#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include <type_traits>

namespace ft
{

struct BaseNode
{
    BaseNode* next = nullptr;
    BaseNode* prev = nullptr;
};

template <typename T>
struct ListNode : public BaseNode
{
    T data;
    ListNode(const T& value) : data(value)
    {}

    ListNode(const T& value, const ListNode<T>* next, const ListNode<T>* prev):
        data(value)
    {
        this->next = next;
        this->prev = prev;
    }
};

// template <typename T>
// struct ListNode
// {
//     T data;
//     ListNode* next;
//     ListNode* prev;

//     ListNode(const T& value) : data(value), next(nullptr), prev(nullptr) {}
// };

template <class T, bool IsConst = false>
struct list_iterator
{
   private:
    // ListNode<T>* current;
    BaseNode* current;
    BaseNode* tail;

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

    list_iterator(BaseNode* current, BaseNode* tail):
        current(current), tail(tail)
    {
    }

    
    operator list_iterator<value_type, true>() const { return list_iterator<value_type, true>(current); }

    explicit list_iterator(ListNode<T>* current, ListNode<T>* tail):
        current(current), tail(tail)
    {}

    //    explicit list_iterator(ListNode<T>* node, ListNode<T>* tail) : current(node), m_tail(tail) {}

    reference operator*() const
    {
        return static_cast<ListNode<T>*>(current)->data;
    }

    bool operator==(const list_iterator& other) const { return current == other.current; }

    bool operator!=(const list_iterator& other) const { return !(*this == other); }

    list_iterator& operator++()
    {
        current = current->next;
        return *this;
    }

    list_iterator& operator--()
    {
        if (!current)
            current = tail->prev;
        else
            current = current->prev;
        return *this;
    }
};

}  // namespace ft

#endif  // LIST_ITERATOR_HPP