#include "base_allocator.hpp"

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
     * Base initialization.
     */
    bool BaseAllocator::initialize( void )
    {
        // So much nothing.
        return true;
    }

    /*
     * Base allocator clean-up.
     */
    void BaseAllocator::shut_down( void )
    {
        delete this;
    }

}