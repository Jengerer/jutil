#ifndef BASE_CONTAINER_HPP
#define BASE_CONTAINER_HPP

#include "base_class.hpp"
#include "memory/allocator_interface.hpp"

namespace JUTIL
{

    /*
     * Generic container class with common container functions.
     */
    class BaseContainer : public BaseClass
    {

    public:

        BaseContainer( AllocatorInterface* allocator = BaseClassServices::get_default_allocator() );
        virtual ~BaseContainer( void );

    protected:

        void set_allocator( AllocatorInterface* allocator );
        AllocatorInterface* get_allocator( void ) const;

    private:

        
        AllocatorInterface* allocator_;

    };

}

#endif // BASE_CONTAINER_HPP
