#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#include <memory>
#include <type_traits>

namespace ft
{

template <class T, class D = std::default_delete<T> >
class unique_ptr
{
   public:
    using element_type = T;
    using deleter_type = D;
    using pointer      = element_type*;  // TODO: std::remove_reference<D>::type::pointer;

   private:
    pointer m_ptr = nullptr;
    [[no_unique_address]] deleter_type m_deleter;  // FIXME: [[no_unique_address]] is a C++20 feature.
                                                   // TODO: We should use compressed_pair?

   public:
    constexpr unique_ptr() noexcept = default;
    constexpr unique_ptr(std::nullptr_t) noexcept : unique_ptr()
    {
    }

    explicit unique_ptr(pointer ptr) : m_ptr(ptr)
    {
    }

    unique_ptr(unique_ptr&& other) noexcept : m_ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    // unique_ptr( pointer p, /* see below */ d1 ) noexcept;

    // template<typename U, typename E,
    // std::enable_if_t<std::is_convertible_v<U*, T*>, bool> = false,
    // std::enable_if_t<std::is_reference_v<deleter_type> && std::is_same_v<E, deleter_type>,
    //                  bool> = false>
    // unique_ptr( unique_ptr<U, E>&& other ) noexcept:
    //     m_ptr(other.release()), m_deleter(other.m_deleter)
    // {
    // }

    unique_ptr(const unique_ptr& /*other*/)            = delete;
    unique_ptr& operator=(const unique_ptr& /*other*/) = delete;

    ~unique_ptr()
    {
        if (get())
        {
            get_deleter()(m_ptr);
            m_ptr = nullptr;
        }
    }

    // Modifiers

    pointer release() noexcept
    {
        pointer res = get();
        m_ptr       = nullptr;
        return res;
    }

    void reset(pointer ptr = pointer()) noexcept
    {
        pointer old_ptr = m_ptr;
        m_ptr           = ptr;
        if (old_ptr)
            get_deleter()(old_ptr);
    }

    void swap(unique_ptr& other) noexcept
    {
        std::swap(m_ptr, other.m_ptr);
        std::swap(m_deleter, other.m_deleter);
    }

    // Observers

    pointer get() const noexcept
    {
        return m_ptr;
    }

    deleter_type& get_deleter() noexcept
    {
        return m_deleter;
    }

    const deleter_type& get_deleter() const noexcept
    {
        return m_deleter;
    }

    explicit operator bool() const noexcept
    {
        return get() != nullptr;
    }

    typename std::add_lvalue_reference<T>::type operator*() const noexcept(noexcept(*std::declval<pointer>()))
    {
        return *get();
    }

    pointer operator->() const noexcept
    {
        return get();
    }
};

template <class T, class... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace ft

#endif  // UNIQUE_PTR_HPP