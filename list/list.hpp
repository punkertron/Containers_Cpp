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
    using value_type      = T;
    using allocator_type  = Allocator;
    using pointer         = typename std::allocator_traits<allocator_type>::pointer;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;

    list() { ptr = new BaseNode; }

    ~list()
    {
        clear();
        delete ptr;
    }

    void clear()
    {
        BaseNode* tmp;
        BaseNode* save_ptr = ptr;
        ptr                = ptr->next;
        while (m_size)
        {
            tmp = ptr;
            ptr = ptr->next;
            deallocateNode(tmp);
            --m_size;
        }
        ptr = save_ptr;
    }

    void push_back(const T& value)
    {
        Node* newNode = allocateNode(value);
        if (m_size)
        {
            newNode->prev   = ptr->prev;
            newNode->next   = ptr;
            ptr->prev->next = newNode;
            ptr->prev       = newNode;
        }
        else
        {
            ptr->next     = newNode;
            newNode->next = ptr;
            newNode->prev = ptr;
            ptr->prev     = newNode;
        }
        ++m_size;
    }

    void push_back(T&& value)
    {
        Node* newNode = allocateNode(std::move(value));
        if (m_size)
        {
            newNode->prev   = ptr->prev;
            newNode->next   = ptr;
            ptr->prev->next = newNode;
            ptr->prev       = newNode;
        }
        else
        {
            ptr->next     = newNode;
            newNode->next = ptr;
            newNode->prev = ptr;
            ptr->prev     = newNode;
        }
        ++m_size;
    }

    void push_front(const T& value)
    {
        Node* newNode = allocateNode(value);
        if (m_size)
        {
            newNode->prev       = ptr;
            newNode->next       = ptr->next;
            ptr->next           = newNode;
            newNode->next->prev = newNode;
        }
        else
        {
            ptr->next     = newNode;
            newNode->next = ptr;
            newNode->prev = ptr;
            ptr->prev     = newNode;
        }
        ++m_size;
    }

    void push_front(T&& value)
    {
        Node* newNode = allocateNode(std::move(value));
        if (m_size)
        {
            newNode->prev       = ptr;
            newNode->next       = ptr->next;
            ptr->next           = newNode;
            newNode->next->prev = newNode;
        }
        else
        {
            ptr->next     = newNode;
            newNode->next = ptr;
            newNode->prev = ptr;
            ptr->prev     = newNode;
        }
        ++m_size;
    }

    void print_all()
    {
        BaseNode* tmp = ptr;
        size_type i   = m_size;

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
    using node_allocator_type = typename std::allocator_traits<allocator_type>::template rebind_alloc<Node>;

    struct BaseNode
    {
        BaseNode* prev = nullptr;
        BaseNode* next = nullptr;
    };

    struct Node : BaseNode
    {
        value_type data;

        Node(const value_type& value) : data(value) {}
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

    Node* allocateNode(value_type&& value)
    {
        Node* newNode = std::allocator_traits<node_allocator_type>::allocate(m_alloc, 1);
        std::allocator_traits<node_allocator_type>::construct(m_alloc, newNode, std::move(value));
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
        // using value_type        = typename std::iterator_traits<iterator_type>::value_type;
        using difference_type = typename std::iterator_traits<iterator_type>::difference_type;

        list_iterator(BaseNode* current) : current(current) {}

        operator list_iterator<true>() const { return list_iterator<true>(current); }

        list_iterator& operator--()
        {
            current = current->prev;
            return *this;
        }

        list_iterator operator--(int)
        {
            list_iterator tmp = current;
            current           = current->prev;
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
            current           = current->next;
            return tmp;
        }

        reference operator*() const { return static_cast<Node*>(current)->data; }

        bool operator==(const list_iterator& other) { return current == other.current; }

        bool operator!=(const list_iterator& other) { return !(operator==(other)); }

       private:
        BaseNode* current;

        friend class list;
    };

    using iterator               = list_iterator<false>;
    using const_iterator         = list_iterator<true>;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() { return iterator(ptr->next); }

    const_iterator cbegin() const { return const_iterator(ptr->next); }

    iterator end() { return iterator(ptr); }

    const_iterator cend() const { return const_iterator(ptr); }

    reverse_iterator rbegin() { return reverse_iterator(ptr); }

    const_reverse_iterator crbegin() const { return const_reverse_iterator(ptr); }

    reverse_iterator rend() { return reverse_iterator(ptr->next); }

    const_reverse_iterator crend() const { return const_reverse_iterator(ptr->next); }

    size_type size() const { return m_size; }

    void pop_back()
    {
        BaseNode* tmp = ptr->prev;
        if (m_size == 1)
        {
            ptr->prev = nullptr;
            ptr->next = nullptr;
        }
        else
        {
            ptr->prev       = ptr->prev->prev;
            ptr->prev->next = ptr;
        }
        deallocateNode(tmp);
        --m_size;
    }

    iterator insert(const_iterator pos, size_type count, const T& value)
    {
        BaseNode* tmp         = ptr;
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
                    newNode->prev     = before_node->prev;
                    newNode->next     = before_node;
                    ptr->next         = newNode;
                    before_node->prev = newNode;
                    before_node       = newNode;  // Update before_node to the current inserted node
                }
                else
                {
                    ptr->next     = newNode;
                    newNode->next = ptr;
                    ptr->prev     = newNode;
                }
                ++m_size;
            }
            return begin();  // Return iterator to the first inserted element
        }

        for (size_type i = 0; i < count; ++i)
        {
            Node* newNode           = allocateNode(value);
            newNode->prev           = before_node->prev;
            newNode->next           = before_node;
            before_node->prev->next = newNode;
            before_node->prev       = newNode;
            before_node             = newNode;  // Update before_node to the current inserted node
            ++m_size;
        }
        return iterator(before_node);
    }

    reference front() { return *begin(); }

    const_reference front() const { return *cbegin(); }

    reference back() { return *(--end()); }

    const_reference back() const { return *(--end()); }

    bool empty() const noexcept { return !m_size; }

    void pop_front()
    {
        BaseNode* del         = ptr->next;
        ptr->next->next->prev = ptr;
        ptr->next             = ptr->next->next;
        deallocateNode(del);
        --m_size;
    }

    // don't have capacity
    void resize(size_type count)
    {
        (void)count;
        return;
    }

    void resize(size_type count, const value_type& value)
    {
        (void)count;
        (void)value;
        return;
    }

    // SORT - merge sort

    template <class Compare>
    void sort(Compare comp)
    {
        ptr->next     = merge_sort(ptr->next, comp);
        BaseNode *tmp = ptr->next, *prev = ptr;
        while (tmp->next && tmp->next != ptr)
        {
            tmp->prev  = prev;
            prev->next = tmp;
            prev       = prev->next;
            tmp        = tmp->next;
        }
        ptr->prev = tmp;
        tmp->next = ptr;
    }

    void sort() { sort(std::less<value_type>()); }

    // https://www.alphacodingskills.com/ds/notes/circular-doubly-linked-list-reverse-the-list.php
    void reverse() noexcept
    {
        // 1. If head is not null create three nodes
        //   prevNode - pointing to head,
        //   tempNode - pointing to head,
        //   curNode - pointing to next of head

        if (ptr != NULL)
        {
            BaseNode* prevNode = ptr;
            BaseNode* tempNode = ptr;
            BaseNode* curNode  = ptr->next;

            // 2. assign next and previous of prevNode
            //    as itself to make the first node as last
            //    node of the reversed list
            prevNode->next = prevNode;
            prevNode->prev = prevNode;

            while (curNode != ptr)
            {
                // 3. While the curNode is not head adjust links
                //    (unlink curNode and link it to the reversed list
                //    from front and modify curNode and prevNode)
                tempNode = curNode->next;

                curNode->next  = prevNode;
                prevNode->prev = curNode;
                ptr->next      = curNode;
                curNode->prev  = ptr;

                prevNode = curNode;
                curNode  = tempNode;
            }

            // 4. Make prevNode (last node) as head ---- MODIFIED
            ptr->prev = prevNode;
        }
    }

    template <class Compare>
    void merge(list& other, Compare comp)
    {
        m_size += other.size();
        ptr->next     = merge(ptr->next, other.ptr->next, ptr, other.ptr, comp, true);
        BaseNode *tmp = ptr->next, *prev = ptr;
        while (tmp->next && tmp->next != ptr)
        {
            tmp->prev  = prev;
            prev->next = tmp;
            prev       = prev->next;
            tmp        = tmp->next;
        }
        ptr->prev = tmp;
        tmp->next = ptr;
    }

    void merge(list& other) { merge(other, std::less<value_type>()); }

    iterator erase(const_iterator first, const_iterator last)
    {
        BaseNode *tf = first.current, *tl = last.current;
        if (first == last)
            return iterator(tf);

        BaseNode *saveBegin = tf->prev, *tmp;
        while (tf != tl)
        {
            tmp = tf->next;
            deallocateNode(tf);
            --m_size;
            tf = tmp;
        }
        tl->prev        = saveBegin;
        saveBegin->next = tl;
        return iterator(tl);
    }

    iterator erase(const_iterator pos)
    {
        iterator second((++pos).current);
        return erase(--pos, second);
    }

   private:
    void deallocateNode(BaseNode* node)
    {
        Node* del = static_cast<Node*>(node);
        std::allocator_traits<node_allocator_type>::destroy(m_alloc, del);
        std::allocator_traits<node_allocator_type>::deallocate(m_alloc, del, 1);
    }

    template <class Compare>
    BaseNode* merge(BaseNode* left, BaseNode* right, BaseNode* end_left, BaseNode* end_right, Compare comp,
                    bool create_new = false)
    {
        BaseNode res;
        BaseNode* tmp = &res;

        while (left && right && left != end_left && right != end_right)
        {
            if (comp(static_cast<Node*>(left)->data, static_cast<Node*>(right)->data))
            {
                tmp->next = left;
                left      = left->next;
            }
            else
            {
                if (create_new)
                {
                    Node* newNode = allocateNode(static_cast<Node*>(right)->data);
                    tmp->next     = newNode;
                }
                else
                    tmp->next = right;
                right = right->next;
            }
            tmp = tmp->next;
        }

        if (left && left != end_left && left->next != end_left)
            tmp->next = left;
        else
            tmp->next = right;
        return res.next;
    }

    BaseNode* get_mid(BaseNode* p)
    {
        BaseNode *slow = p, *fast = p->next;
        while (fast && fast != ptr && fast->next && fast->next != ptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    template <class Compare>
    BaseNode* merge_sort(BaseNode* begin_list, Compare comp)
    {
        if (!begin_list || begin_list == ptr || !(begin_list->next) || begin_list->next == ptr)
            return begin_list;
        BaseNode* left  = begin_list;
        BaseNode* right = get_mid(begin_list);

        BaseNode* tmp = right->next;
        right->next   = nullptr;
        right         = tmp;
        left          = merge_sort(left, comp);
        right         = merge_sort(right, comp);
        return merge(left, right, ptr, ptr, comp);
    }

};  // class list

}  // namespace ft

#endif