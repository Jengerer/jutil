#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#include "memory/base_allocator.hpp"

namespace JUTIL
{

    /*
     * Heap allocator class.
     */
    class HeapAllocator : public BaseAllocator
    {

    public:

        virtual void* allocate( size_t size );
        virtual void free( void* address );

    };

}

#endif // HEAP_ALLOCATOR_H
