#include "memory/base_allocator.hpp"

namespace JUTIL
{

    /*
     * Base allocator constructor.
     */
    BaseAllocator::BaseAllocator( void )
    {
        // Do nothing.
    }

    /*
     * Base allocator destructor.
     */
    BaseAllocator::~BaseAllocator( void )
    {
        // You do nothing! You lose! Good day, sir!
    }

    /*
     * Base allocator clean-up.
     */
    void BaseAllocator::shut_down( void )
    {
        // Ain't even a thang.
    }

}
