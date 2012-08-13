#ifndef ALLOCATOR_INTERFACE_HPP
#define ALLOCATOR_INTERFACE_HPP

namespace JUTIL
{

    /*
     * Interface for managing allocated memory.
     */
    class AllocatorInterface
    {

    public:

        // Cleaning up.
        virtual void shut_down( void ) = 0;    

        // Memory management.
        virtual void* allocate( size_t size ) = 0;
        virtual void* reallocate( void* address, size_t size ) = 0;
        virtual void free( void* address ) = 0;
        
    };

}

#endif // ALLOCATOR_INTERFACE_HPP
