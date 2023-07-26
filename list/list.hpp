#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

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


    list(): list(Allocator()) {};

    explicit list( const Allocator& alloc ): alloc(alloc)
    {
        ;
    }

    explicit list( size_type count, const T& value = T(), const Allocator& alloc = Allocator()): alloc(alloc)
    {
        ;
    }

    list( value_type val )
    {
        m_n->next = new Node(val);
    }

private:
    struct BaseNode
    {
        BaseNode* prev = nullptr;
        BaseNode* next = nullptr;
    };

    struct Node : BaseNode
    {
        value_type value;
        Node(value_type val = value_type(), Node *prev = nullptr, Node *next = nullptr):
            value(val)
        {
            this->prev = prev; BaseNode::next(next);
        }
    };

    Allocator alloc;
    BaseNode *m_b;
    Node *m_n;
    size_type m_size;

};

} // namespace ft

#endif // LIST_HPP