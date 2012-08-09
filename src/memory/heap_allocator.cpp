#include "memory/heap_allocator.hpp"
#include "memory/allocation_manager.hpp"
#include <stdlib.h>

namespace JUTIL
{

    /*
     * Heap allocation function.
     */
    void* HeapAllocator::allocate( size_t size )
    {
        void* memory = malloc( size );

#if defined( _DEBUG )
        if (memory != nullptr) {
            AllocationManager::set_allocated( memory, size );
        }
#endif

        return memory;
    }


    /*
     * Heap free function.
     */
    void HeapAllocator::free( void* memory )
    {
        // Free from heap.
        ::free( memory );
        AllocationManager::set_freed( memory );
    }

}
