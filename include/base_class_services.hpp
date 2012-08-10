#ifndef BASE_CLASS_SERVICES_HPP
#define BASE_CLASS_SERVICES_HPP

#include "base_services_interface.hpp"
#include "memory/heap_allocator.hpp"

namespace JUTIL
{

    /*
     * Services for objects of base class.
     */
    class BaseClassServices : public BaseServicesInterface
    {

        public:

            // Default allocator getter.
            static AllocatorInterface* get_default_allocator( void );

        private:

            static HeapAllocator allocator_;
            
    };

}

#endif // BASE_CLASS_SERVICES_HPP
