#ifndef BASE_ALLOCATOR_HPP
#define BASE_ALLOCATOR_HPP

#include "base/jutil_base.hpp"
#include <stdlib.h>
#include <new.h>

namespace JUTIL
{

    /*
     * Generic allocator class for objects & heap memory.
     */
    class BaseAllocator
    {

    public:

        // Single object allocation.
        template <class Type>
        static bool allocate( Type** output );

        // Array allocation.
        template <class Type>
        static bool allocate_array( Type** output, size_t elements );

        // Array reallocation.
        template <class Type>
        static bool reallocate_array( Type** output, size_t elements );

        // Memory freeing functions.
        template <class Type>
        static void release( Type* address );

        // Free after checking handle.
        template <class Type>
        static void safe_release( Type** memory );

        // Destroying function.
        template <class Type>
        static void destroy( Type* address );

        // Destroy after checking handle.
        template <class Type>
        static void safe_destroy( Type** memory );

    };

    /*
     * Allocate space for a single object.
     */
    template <class Type>
    bool BaseAllocator::allocate( Type** output )
    {
        // Just allocate enough space for one.
        Type* allocation = (Type*)malloc( sizeof(Type) );
        if (allocation != nullptr) {
            *output = allocation;
            return true;
        }
        
        return false;
    }

    /*
     * Allocate an array for an object type.
     */
    template <class Type>
    bool BaseAllocator::allocate_array( Type** output, size_t elements )
    {
        // Allocate chunk for array.
        unsigned int size = elements * sizeof(Type);
        Type* allocation = (Type*)malloc( size );
        if (allocation != nullptr) {
            *output = allocation;
            return true;
        }
        
        return false;
    }

    /*
     * Reallocate an array for an object type.
     */
    template <class Type>
    bool BaseAllocator::reallocate_array( Type** output, size_t elements )
    {
        // Allocate chunk for array.
        unsigned int size = elements * sizeof(Type);
        Type* allocation = (Type*)realloc( *output, size );
        if (allocation != nullptr) {
            *output = allocation;
            return true;
        }
        
        return false;
    }

    /*
     * Free allocated memory.
     */
    template <class Type>
    void BaseAllocator::release( Type* address )
    {
        free( address );
    }

    /*
     * Free allocated memory if not already freed.
     */
    template <class Type>
    void BaseAllocator::safe_release( Type** memory )
    {
        Type* address = *memory;
        if (address != nullptr) {
            release( address );
            *memory = nullptr;
        }
    }

    /*
     * Delete object and free memory.
     */
    template <class Type>
    void BaseAllocator::destroy( Type* address )
    {
        delete address;
    }

    /*
     * Delete object and free memory if not already released.
     */
    template <class Type>
    void BaseAllocator::safe_destroy( Type** memory )
    {
        Type* address = *memory;
        if (address != nullptr) {
            destroy( address );
            *memory = nullptr;
        }
    }

}

#endif // BASE_ALLOCATOR_HPP