#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

namespace JUTIL
{

    /*
     * Heap allocator class.
     */
    class HeapAllocator
    {

    public:

        virtual void* allocate( size_t size );
        virtual void free( void* address );

    };

}

#endif // HEAP_ALLOCATOR_H
