#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

#include "list_iterator.hpp"

namespace ft
{

template <class T, class Allocator = std::allocator<T>>
class list
{
   public:
    using value_type = T;
    using allocator_type =
        typename std::allocator_traits<Allocator>::template rebind_alloc<ListNode<value_type>>;  // Allocator;
    using pointer         = typename std::allocator_traits<allocator_type>::pointer;
    using const_pointer   = typename std::allocator_traits<allocator_type>::const_pointer;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using iterator       = list_iterator<value_type>;
    using const_iterator = list_iterator<value_type, true>;

    ~list()
    {
        while (m_head)
        {
            BaseNode* tmp = m_head;
            m_head                    = m_head->next;
            deallocateNode(tmp);
        }
    }

    list() : list(Allocator()){};

    explicit list(const Allocator& alloc) : m_alloc(alloc), m_head(nullptr), m_tail(nullptr) { ; }

    // explicit list( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): alloc(alloc)
    // {
    //     ;
    // }

    void push_back(const T& value)
    {
        ListNode<value_type>* newNode = allocateNode(value);
        
        
        newNode->prev = m_tail->prev;
        newNode->next = m_tail;

        m_tail->prev->next = newNode;
        m_tail->prev = newNode;
        ++m_size;

        
        // if (m_tail)
        // {
        //     m_tail->next  = newNode;
        //     newNode->prev = m_tail;
        //     m_tail        = newNode;
        // }
        // else
        // {
        //     m_head = m_tail = newNode;
        // }
        // ++m_size;
    }

    void pop_back()
    {
        ListNode<value_type>* tmp = m_tail;
        m_tail                    = m_tail->prev;
        if (m_tail)
            m_tail->next = nullptr;
        else
            m_head = nullptr;
        deallocateNode(tmp);
        --m_size;
    }

    iterator begin() { return iterator(m_head, m_tail); }

    iterator end() { return iterator(m_tail, m_tail); }

    const_iterator cbegin() { return const_iterator(m_head); }

    const_iterator cend() { return const_iterator(nullptr); }

    size_type size() const noexcept { return m_size; }

   private:
    BaseNode* m_head;
    BaseNode* m_tail;
    size_type m_size = 0;
    allocator_type m_alloc;

    ListNode<value_type>* allocateNode(const value_type& value)
    {
        ListNode<value_type>* newNode = std::allocator_traits<allocator_type>::allocate(m_alloc, 1);
        std::allocator_traits<allocator_type>::construct(m_alloc, newNode, value);
        return newNode;
    }

    void deallocateNode(BaseNode* node)
    {
        ListNode<value_type>* del = static_cast<ListNode<value_type>*>(node);
        std::allocator_traits<allocator_type>::destroy(m_alloc, del);
        std::allocator_traits<allocator_type>::deallocate(m_alloc, del, 1);
    }
};

}  // namespace ft

#endif  // LIST_HPP