#include "base_class_services.hpp"
#include "memory/heap_allocator.hpp"

namespace JUTIL
{

    // Default class allocator.
    HeapAllocator BaseClassServices::allocator_;

    /*
     * Get default allocator interface.
     */
    AllocatorInterface* BaseClassServices::get_default_allocator( void )
    {
        return static_cast<AllocatorInterface>(&allocator_);
    }

}
