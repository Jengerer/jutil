#ifndef ALLOCATOR_INTERFACE_H
#define ALLOCATOR_INTERFACE_H

namespace JUTIL
{

    /*
     * Interface for managing allocated memory.
     */
    class AllocatorInterface
    {

    public:

        // Start and clean-up.
        virtual bool initialize( void ) = 0;
        virtual void shut_down( void ) = 0;    

        // Memory management.
        virtual void* allocate( size_t size ) = 0;
        virtual void free( void* address ) = 0;
        
    };

}

#endif // ALLOCATOR_INTERFACE_H

