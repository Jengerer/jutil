#ifndef BASE_ALLOCATOR_HPP
#define BASE_ALLOCATOR_HPP

#include "base/jutil_base.hpp"
#include "memory/allocation_manager.hpp"
#include <stdlib.h>
#include <new.h>

namespace JUTIL
{

    /*
     * Generic allocator class for objects & heap memory.
     */
    class __declspec(dllexport) BaseAllocator
    {

    public:

        // Memory management functions.
        template <class Type> static bool allocate( Type** output );
        template <class Type> static bool allocate_array( Type** output, size_t elements );
        template <class Type> static bool reallocate_array( Type** output, size_t elements );
        template <class Type> static void release( Type* address );
        template <class Type> static void safe_release( Type** memory );
        template <class Type> static void destroy( Type* address );
        template <class Type> static void safe_destroy( Type** memory );

    };

    /*
     * Allocate space for a single object.
     */
    template <class Type>
    bool BaseAllocator::allocate( Type** output )
    {
        // Just allocate enough space for one.
        void* allocation = malloc( sizeof(Type) );
        if (allocation == nullptr) {
            return false;
        }

#if defined( _DEBUG )
        AllocationManager* allocation_manager = AllocationManager::get_instance();
        if (allocation_manager != nullptr) {
            allocation_manager->on_allocate( allocation, sizeof(Type) );
        }
#endif

        *output = static_cast<Type*>(allocation);
        return true;
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
        if (allocation == nullptr) {
            return false;
        }

#if defined( _DEBUG )
        AllocationManager* allocation_manager = AllocationManager::get_instance();
        if (allocation_manager != nullptr) {
            allocation_manager->on_allocate( allocation, size );
        }
#endif

        *output = allocation;
        return true;
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
        if (allocation == nullptr) {
            return false;
        }

#if defined( _DEBUG )
        AllocationManager* allocation_manager = AllocationManager::get_instance();
        if (allocation_manager != nullptr) {
            allocation_manager->on_reallocate( *output, allocation, size );
        }
#endif

        *output = allocation;
        return true;
    }

    /*
     * Free allocated memory.
     */
    template <class Type>
    void BaseAllocator::release( Type* address )
    {
#if defined( _DEBUG )
        AllocationManager* allocation_manager = AllocationManager::get_instance();
        if (allocation_manager != nullptr) {
            allocation_manager->on_release( address );
        }
#endif

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
#if defined( _DEBUG )
        AllocationManager* allocation_manager = AllocationManager::get_instance();
        if (allocation_manager != nullptr) {
            allocation_manager->on_release( address );
        }
#endif

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
