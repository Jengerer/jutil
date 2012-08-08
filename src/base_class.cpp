#include "base_class.hpp"
#include "memory/heap_allocator.hpp"
#include <new.h>

namespace JUTIL
{

    // Default allocation interface.
    AllocatorInterface* BaseClass::allocator_ = nullptr;

    /*
     * Base class initialization.
     */
    bool BaseClass::initialize( void )
    {
        HeapAllocator* allocator = new HeapAllocator();
        if (allocator == nullptr) {
            return false;
        }
        
        allocator_ = allocator;
        return allocator_->initialize();
    }

    /*
     * Base class clean-up.
     */
    void BaseClass::shut_down()
    {
        allocator_->shut_down();
    }

    /* 
     * Over-written new single-allocation operator.
     */
    void* BaseClass::operator new( size_t size )
    {
        return allocator_->allocate( size );
    }

    /*
     * Over-written single de-allocation operator.
     */
    void BaseClass::operator delete( void* address )
    {
        return allocator_->free( address );
    }

}