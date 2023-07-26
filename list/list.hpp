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
    using pointer           = typename allocator_traits<Allocator>::pointer;
    using const_pointer     = typename allocator_traits<Allocator>::const_pointer;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;


    list(): list(Allocator()) {};

private:
    ;

};

} // namespace ft

#endif // LIST_HPP