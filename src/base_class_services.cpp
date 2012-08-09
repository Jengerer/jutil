#include "base_class_services.hpp"
#include "memory/heap_allocator.hpp"

namespace JUTIL
{

    // Default allocator interface pointer.
    AllocatorInterface* BaseClassServices::allocator_ = nullptr;

    /*
     * Base class services initialization.
     */
    bool BaseClassServices::initialize( void )
    {
        // Create default allocator.
        HeapAllocator* allocator = new HeapAllocator();
        if (allocator != nullptr) {
            allocator_ = static_cast<AllocatorInterface*>(allocator);
            return allocator_->initialize();
        }
        return false;
    }


    /*
     * Base class service destruction.
     */
    void BaseClassServices::shut_down( void )
    {
        // Destroy allocator.
        if (allocator_ != nullptr) {
            allocator_->shut_down();
            allocator_ = nullptr;
        }
    }


    /*
     * Get default allocator interface.
     */
    AllocatorInterface* BaseClassServices::get_default_allocator( void )
    {
        return allocator_;
    }

}
