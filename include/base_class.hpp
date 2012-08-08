#ifndef BASE_CLASS_HPP
#define BASE_CLASS_HPP

#include "memory/allocator_interface.hpp"

namespace JUTIL
{

    /*
     * Base class for all JUTIL objects.
     */
    class BaseClass
    {

    public:

        // Allocator services.
        static bool initialize( void );
        static void shut_down( void );

        // Allocation operators.
        void* operator new( size_t size );
        void* operator new[]( size_t size );
        void operator delete( void* address );
        void operator delete[]( void* address );

    private:

        static AllocatorInterface* allocator_;

    };

}

#endif // BASE_CLASS_HPP
