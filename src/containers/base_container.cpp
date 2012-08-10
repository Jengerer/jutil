#include "containers/base_container.hpp"

namespace JUTIL
{

    /*
     * Base container constructor.
     */
    BaseContainer::BaseContainer( AllocatorInterface* allocator )
    {
        set_allocator( allocator );
    }

    /*
     * Base container destructor.
     */
    BaseContainer::~BaseContainer( void )
    {
        //allocator_->shut_down();
    }

    /*
     * Setting new container object allocator.
     * Allocator must have been initialized before setting; no error
     * checking is done here.
     */
    void BaseContainer::set_allocator( AllocatorInterface* allocator )
    {
        allocator_ = allocator;
    } 

    /*
     * Get current allocator.
     */
    AllocatorInterface* BaseContainer::get_allocator( void ) const
    {
        return allocator_;
    }
}
