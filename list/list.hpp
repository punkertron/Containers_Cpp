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
    using reference         = value_type&;
    using const_reference   = const value_type&;


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
        using reference         = std::conditional_t<IsConst, const value_type&, value_type&>;
        using pointer           = std::conditional_t<IsConst, const value_type*, value_type*>;
        using iterator_type     = BaseNode*;
        using iterator_category = typename std::iterator_traits<iterator_type>::iterator_category;
        using value_type        = typename std::iterator_traits<iterator_type>::value_type;
        using difference_type   = typename std::iterator_traits<iterator_type>::difference_type;

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
            current = current->prev;
            return tmp;
        }

        list_iterator& operator++()
        {
            current = current->next;
            return *this;
        }

        list_iterator operator++(int)
        {
            list_iterator tmp = current;
            current = current->next;
            return tmp;
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

        friend class list;
    };

    using iterator                  = list_iterator<false>;
    using const_iterator            = list_iterator<true>;
    using reverse_iterator          = std::reverse_iterator<iterator>;
    using const_reverse_iterator    = std::reverse_iterator<const_iterator>;


    iterator begin()
    {
        return iterator(ptr->next);
    }

    const_iterator cbegin() const
    {
        return const_iterator(ptr->next);
    }

    iterator end()
    {
        return iterator(ptr);
    }

    const_iterator cend() const
    {
        return const_iterator(ptr);
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(ptr);
    }

    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(ptr);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(ptr->next);
    }

    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(ptr->next);
    }

    size_type size() const
    {
        return m_size;
    }

    void pop_back()
    {
        BaseNode *tmp = ptr->prev;
        if (m_size == 1)
        {
            ptr->prev = nullptr;
            ptr->next = nullptr;
        }
        else
        {
            ptr->prev = ptr->prev->prev;
            ptr->prev->next = ptr;
        }
        deallocateNode(tmp);
        --m_size;
    }

    iterator insert( const_iterator pos, size_type count, const T& value )
    {
        BaseNode* tmp = ptr;
        BaseNode* before_node = pos.current;

        while (tmp->next != before_node)
            tmp = tmp->next;

        if (m_size == 0 || before_node == ptr->next)
        {
            for (size_type i = 0; i < count; ++i)
            {
                Node* newNode = allocateNode(value);
                if (m_size)
                {
                    newNode->prev = before_node->prev;
                    newNode->next = before_node;
                    ptr->next = newNode;
                    before_node->prev = newNode;
                    before_node = newNode; // Update before_node to the current inserted node
                }
                else
                {
                    ptr->next = newNode;
                    newNode->next = ptr;
                    ptr->prev = newNode;
                }
                ++m_size;
            }
            return begin(); // Return iterator to the first inserted element
        }
        
        for (size_type i = 0; i < count; ++i)
        {
            Node* newNode = allocateNode(value);
            newNode->prev = before_node->prev;
            newNode->next = before_node;
            before_node->prev->next = newNode;
            before_node->prev = newNode;
            before_node = newNode; // Update before_node to the current inserted node
            ++m_size;
        }
        return iterator(before_node);
    }

    reference front()
    {
        return *begin();
    }

    const_reference front() const
    {
        return *cbegin();
    }

    reference back()
    {
        return *(--end());
    }

    const_reference back() const
    {
        return *(--end());
    }

    bool empty() const noexcept
    {
        return !m_size;
    }

    void pop_front()
    {
        BaseNode *del = ptr->next;
        ptr->next->next->prev = ptr;
        ptr->next = ptr->next->next;
        deallocateNode(del);
        --m_size;
    }

    // don't have capacity
    void resize( size_type count )
    {
        (void) count;
        return ;
    }

    void resize( size_type count, const value_type& value )
    {
        (void) count;
        (void) value;
        return ;
    }


    // SORT - merge sort
    
    template< class Compare >
    void sort( Compare comp )
    {
        ptr->next = merge_sort(ptr->next, comp);
        BaseNode *tmp = ptr->next, *prev = ptr;
        while (tmp->next && tmp->next != ptr)
        {
            tmp->prev = prev;
            prev->next = tmp;
            prev = prev->next;
            tmp = tmp->next;
        }
        ptr->prev = tmp;
        tmp->next = ptr;

    }

    void sort()
    {
        sort(std::less<int>());
    }

private:
    void deallocateNode(BaseNode *node)
    {
        Node* del = static_cast<Node*>(node);
        std::allocator_traits<node_allocator_type>::destroy(m_alloc, del);
        std::allocator_traits<node_allocator_type>::deallocate(m_alloc, del, 1);
    }

    template< class Compare >
    BaseNode* merge(BaseNode* left, BaseNode* right, Compare comp)
    {
        BaseNode res;
        BaseNode* tmp = &res;

        while (left && right && left != ptr && right != ptr)
        {
            // if (comp.operator<(static_cast<Node*>(left)->data, static_cast<Node*>(right)->data))
            if (comp(static_cast<Node*>(left)->data, static_cast<Node*>(right)->data))
            {
                tmp->next = left;
                left = left->next;
            }
            else
            {
                tmp->next = right;
                right = right->next;
            }
            tmp = tmp->next;
        }

        if (left && left != ptr && left->next != ptr)
            tmp->next = left;
        else
            tmp->next = right;
        return res.next;
    }

    BaseNode *get_mid(BaseNode* p)
    {
        BaseNode *slow = p, *fast = p->next;
        while (fast && fast != ptr && fast->next && fast->next != ptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    template< class Compare >
    BaseNode* merge_sort(BaseNode* begin_list, Compare comp)
    {
        if (!begin_list || begin_list == ptr || !(begin_list->next) || begin_list->next == ptr)
            return begin_list;
        BaseNode* left = begin_list;
        BaseNode* right = get_mid(begin_list);
        
        BaseNode* tmp = right->next;
        right->next = nullptr;
        right = tmp;
        left = merge_sort(left, comp);
        right = merge_sort(right, comp);
        return merge(left, right, comp);
    }

}; // class list


} // namespace ft

#endif