#ifndef BASE_CLASS_SERVICES_HPP
#define BASE_CLASS_SERVICES_HPP

#include "memory/allocator_interface.hpp"

namespace JUTIL
{

    /*
     * Services for objects of base class.
     */
    class BaseClassServices
    {

        public:

            // Static initialization.
            static bool initialize( void );
            static void shut_down( void );

            // Default allocator getter.
            static AllocatorInterface* get_default_allocator( void );

        private:

            static AllocatorInterface* allocator_;
            
    };

}

#endif // BASE_CLASS_SERVICES_HPP
