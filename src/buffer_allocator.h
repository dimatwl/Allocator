#ifndef __BUFFER_ALLOCATOR_H__
#define __BUFFER_ALLOCATOR_H__

namespace allocator_lib
{

using std::size_t;

template <typename element_type> class buffer_allocator
{
public:
    typedef element_type* pointer;
    typedef element_type const * const const_pointer_to_const;

    buffer_allocator(const size_t capacity_);
    pointer new_element();
    void delete_element(const_pointer_to_const element_);
}; 

}

#endif /* __BUFFER_ALLOCATOR_H__*/