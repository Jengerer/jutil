#include "base_class.hpp"

namespace JUTIL
{

    /*
     * Base class initialization.
     */
    bool BaseClass::initialize( void )
    {
		// Nothing yet, maybe be able to remove.
		return true;
    }

    /*
     * Base class clean-up.
     */
    void BaseClass::shut_down()
    {
        // Nothing yet, may be able to remove.
    }

    /* 
     * Over-written new single-allocation operator.
     */
    void* BaseClass::operator new( size_t size, AllocatorInterface* allocator )
    {
        return allocator->allocate( size );
    }

    /*
     * Over-written single de-allocation operator.
     */
    void BaseClass::operator delete( void* address, AllocatorInterface* allocator )
    {
        return allocator->free( address );
    }

}
