#ifndef __BUFFER_ALLOCATOR_H__
#define __BUFFER_ALLOCATOR_H__

#include <utility>
#include <set>
#include <new>
#include <memory>

namespace allocator_lib
{

using std::size_t;
using std::pair;
using std::make_pair;
using std::set;
using std::bad_alloc;
using std::unique_ptr;

template <typename element_type> class buffer_allocator
{
public:
    typedef element_type* ptr;
    typedef element_type const * const const_ptr_to_const;
    typedef const element_type& const_ref;

    //bad_alloc can be thrown here.
    explicit buffer_allocator(const size_t capacity_);
    ~buffer_allocator();

    ptr new_element();
    void delete_element(const_ptr_to_const element_);

    void construct(ptr address_, const_ref element_) const;
    void destroy(ptr address_) const;

private:
    typedef pair<ptr, size_t> free_space_descriptor;

    unique_ptr<element_type> m_buffer;
    size_t m_size;
    size_t m_capacity;
    set<free_space_descriptor> m_free_space;

    buffer_allocator();
    buffer_allocator(const buffer_allocator&);
    void operator=(const buffer_allocator&);
}; 

template <typename element_type>
buffer_allocator<element_type>::buffer_allocator(const size_t capacity_):
    m_buffer(static_cast<ptr>(::operator new(capacity_ * sizeof(element_type)))),
    m_size(0), 
    m_capacity(capacity_),
    m_free_space()
{
    m_free_space.insert(make_pair(m_buffer.get(), capacity_));
}

template <typename element_type>
buffer_allocator<element_type>::~buffer_allocator()
{
}

template <typename element_type>
void buffer_allocator<element_type>::construct(ptr address_, const_ref element_) const
{
    new(address_) element_type(element_);
}

template <typename element_type>
void buffer_allocator<element_type>::destroy(ptr address_) const
{
    address_->~element_type();
}

template <typename element_type>
typename buffer_allocator<element_type>::ptr buffer_allocator<element_type>::new_element()
{
    ptr allocated_memory_address = 0;
    if (!m_free_space.empty())
    {
        auto free_position_iter = m_free_space.begin();
        if (free_position_iter->second > 1)
        {
            allocated_memory_address = free_position_iter->first;
            auto descriptor = *free_position_iter;
            m_free_space.erase(free_position_iter);
            descriptor.first++;
            descriptor.second--;
            m_free_space.insert(descriptor);
        }
        else
        {
            allocated_memory_address = free_position_iter->first;
            m_free_space.erase(free_position_iter);
        }
    }
    return allocated_memory_address;
}

template <typename element_type>
void buffer_allocator<element_type>::delete_element(const_ptr_to_const element_)
{

}

}

#endif /* __BUFFER_ALLOCATOR_H__*/