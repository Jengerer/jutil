#ifndef BASE_ALLOCATOR_H
#define BASE_ALLOCATOR_H

#include "allocator_interface.hpp"

namespace JUTIL
{

    /*
     * Generic allocator starter class.
     */
    class BaseAllocator : public AllocatorInterface
    {

    public:

        BaseAllocator( void );

        // Allocator initialize and shut down.
        virtual bool initialize( void );
        virtual void shut_down( void );

    protected:

        virtual ~BaseAllocator( void );

    };

}

#endif // BASE_ALLOCATOR_H
