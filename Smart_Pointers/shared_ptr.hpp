#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <iostream>

namespace ft
{
template <typename T>
class shared_ptr
{
   public:
    using element_type = T;

   private:
    std::size_t* m_cnt;
    element_type* m_ptr;

   public:
    shared_ptr(element_type* ptr) : m_cnt(new std::size_t(1)), m_ptr(ptr)
    {
    }

    shared_ptr(const shared_ptr& other) noexcept : m_cnt(other.m_cnt), m_ptr(other.m_ptr)
    {
        ++*m_cnt;
    }

    shared_ptr(shared_ptr&& other) noexcept : m_cnt(other.m_cnt), m_ptr(other.m_ptr)
    {
        // std::cerr << "Here" << std::endl;
        other.m_cnt = nullptr;
        other.m_ptr = nullptr;
    }

    ~shared_ptr()
    {
        if (m_cnt && --*m_cnt == 0)
        {
            delete m_ptr;
            delete m_cnt;
        }
    }
};

}  // namespace ft

#endif  // SHARED_PTR_HPP