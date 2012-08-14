#ifndef BASE_SERVICES_INTERFACE_HPP
#define BASE_SERVICES_INTERFACE_HPP

#include "memory/allocator_interface.hpp"

namespace JUTIL
{

    /*
     * Base services for all library objects.
     */
    class BaseServicesInterface
    {

    public:

        virtual AllocatorInterface* get_default_allocator( void );

    };

}

#endif // BASE_SERVICES_INTERFACE_HPP
