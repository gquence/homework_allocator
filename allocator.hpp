#pragma once

#include <iostream>
#include <map>

namespace my_alloc{ 

template<class T, int C = 10>
class my_allocator
{
public:
    using value_type = T;
private:
    value_type* m_memoryPool = nullptr;
    size_t      m_allocated_to_user = 0;

public:
    my_allocator() noexcept {};
    template<class U>
    my_allocator(const my_allocator<U> &rhv) noexcept {
        m_memoryPool = rhv.m_memoryPool;
        rhv.m_memoryPool = nullptr;
        m_allocated_to_user = rhv.m_allocated_to_user;
        rhv.m_allocated_to_user = 0;
    }
    value_type *allocate(std::size_t n) {
        if (m_memoryPool == nullptr) {
            m_memoryPool = static_cast<value_type *>(::operator new(C * sizeof(value_type)));
        }
        if (m_allocated_to_user + n > C) {
            throw std::bad_alloc();
        }
        auto *targetPtr = m_memoryPool +m_allocated_to_user;
        m_allocated_to_user += n;
        return targetPtr;
    };
    void deallocate(value_type *, std::size_t )
    {};
    ~my_allocator() {
        if (m_memoryPool) {
            ::operator delete(m_memoryPool);
        }
    };

    template< class U >
    struct rebind
    {
        typedef my_allocator<U> other;
    };
    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;
};

template <class K, class V>
using map = std::map<K, V, std::less<K>, my_allocator<std::pair<const K, V>>>;
}
