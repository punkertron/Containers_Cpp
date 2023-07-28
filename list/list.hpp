#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

namespace ft
{

template <class T, class Allocator = std::allocator<T>>
class list
{
public:


    using value_type        = T;
    using allocator_type    = Allocator;
    using pointer           = typename std::allocator_traits<allocator_type>::pointer;
    using size_type         = std::size_t;
   

    list()
    {
        ptr = new BaseNode;
    }

    ~list()
    {
        BaseNode *tmp;
        BaseNode *save_ptr = ptr;
        ptr = ptr->next;
        while (m_size)
        {
            tmp = ptr;
            ptr = ptr->next;
            deallocateNode(tmp);
            --m_size;
        }
        delete save_ptr;
    }

    void push_back(const T& value)
    {
        Node* newNode = allocateNode(value);
        if (m_size)
        {
            newNode->prev = ptr->prev;
            newNode->next = ptr;
            ptr->prev->next = newNode;
            ptr->prev = newNode;
        }
        else
        {
            ptr->next = newNode;
            newNode->next = ptr;
            ptr->prev = newNode;
        }
        ++m_size;
    }

    void print_all()
    {
        BaseNode *tmp = ptr;
        size_type i = m_size;

        while (i)
        {
            tmp = tmp->next;
            std::cerr << static_cast<Node*>(tmp)->data << ' ';
            --i;
        }
        std::cerr << std::endl;
    }



private:

    struct Node;
    using node_allocator_type =
        typename std::allocator_traits<allocator_type>::template rebind_alloc<Node>;

    struct BaseNode
    {
        BaseNode *prev = nullptr;
        BaseNode *next = nullptr;
    };

    struct Node : BaseNode
    {
        value_type data;

        Node(const value_type& value): data(value) {}
    };

    BaseNode* ptr;
    node_allocator_type m_alloc;
    size_type m_size = 0;

    Node* allocateNode(const value_type& value)
    {
        Node* newNode = std::allocator_traits<node_allocator_type>::allocate(m_alloc, 1);
        std::allocator_traits<node_allocator_type>::construct(m_alloc, newNode, value);
        return newNode;
    }

public:
    template <bool IsConst = false>
    struct list_iterator
    {
    public:
        using reference = std::conditional_t<IsConst, const value_type&, value_type&>;

        list_iterator(BaseNode* current):
            current(current)
        {
        }

        operator list_iterator<true>() const
        {
            return list_iterator<true>(current);
        }

        list_iterator& operator--()
        {
            current = current->prev;
            return *this;
        }

        list_iterator operator--(int)
        {
            list_iterator tmp = current;
            --current;
            return tmp;
        }

        list_iterator& operator++()
        {
            current = current->next;
            return *this;
        }

        reference operator*() const
        {
            return static_cast<Node*>(current)->data;
        }

        bool operator==(const list_iterator& other)
        {
            return current == other.current;
        }

        bool operator!=(const list_iterator &other)
        {
            return !(operator==(other));
        }

    private:
        BaseNode* current;
    };

    using iterator = list_iterator<false>;
    using const_iterator = list_iterator<true>;


    iterator begin()
    {
        return iterator(ptr->next);
    }

    iterator end()
    {
        return iterator(ptr);
    }

    const_iterator cbegin()
    {
        return const_iterator(ptr->next);
    }

    const_iterator cend()
    {
        return const_iterator(ptr);
    }

    size_type size() const
    {
        return m_size;
    }

private:
    void deallocateNode(BaseNode *node)
    {
        Node* del = static_cast<Node*>(node);
        std::allocator_traits<node_allocator_type>::destroy(m_alloc, del);
        std::allocator_traits<node_allocator_type>::deallocate(m_alloc, del, 1);
    }


}; // class list


} // namespace ft

#endif