#ifndef __BUFFER_ALLOCATOR_H__
#define __BUFFER_ALLOCATOR_H__

#include <utility>
#include <set>
#include <new>

namespace allocator_lib
{

using std::size_t;
using std::pair;
using std::make_pair;
using std::set;
using std::bad_alloc;

template <typename element_type> class buffer_allocator
{
public:
    typedef element_type* ptr;
    typedef element_type const * const const_ptr_to_const;
    typedef const element_type& const_ref;

    explicit buffer_allocator(const size_t capacity_);
    ~buffer_allocator();

    ptr new_element();
    void delete_element(const_ptr_to_const element_);

    void construct(ptr address_, const_ref element_) const;
    void destroy(ptr address_) const;

private:
    typedef pair<void*, size_t> free_space_descriptor;

    void* m_buffer;
    size_t m_size;
    size_t m_capacity;
    set<free_space_descriptor> m_free_space;

    buffer_allocator();
    buffer_allocator(const buffer_allocator&);
    void operator=(const buffer_allocator&);
}; 

template <typename element_type>
buffer_allocator<element_type>::buffer_allocator(const size_t capacity_)
{

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

}

#endif /* __BUFFER_ALLOCATOR_H__*/