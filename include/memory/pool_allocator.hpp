#ifndef POOL_ALLOCATOR_HPP
#define POOL_ALLOCATOR_HPP

#include "memory/base_allocator.hpp"
#include "memory/heap_allocator.hpp"

namespace JUTIL
{

    /*
     * Allocator that supplies resources of equal size.
     */
    template <class Type>
    class PoolAllocator : public BaseAllocator
    {

    public:

        PoolAllocator( void );
        ~PoolAllocator( void );

        // Clean up pool.
        virtual void shut_down( void );

        // Allocator interface functions.
        virtual void* allocate( size_t size );
        virtual void* reallocate( void* address, size_t size );
        virtual void free( void* address );

    private:

        // Extend the pool for more elements.
        void* extend( void );

        // Getting locations.
        void* get_allocation_by_index( size_t index );
        static void* get_next_allocation( void* pool_address );

    private:

        // Heap allocator for pool expansion.
        HeapAllocator sub_allocator_;

        // Next available spot in pool.
        size_t next_;

        // Buffer space.
        void* buffer_;
        size_t buffer_length_;

        // Statics for allocation.
        static const size_t EXTEND_NUMERATOR = 3;
        static const size_t EXTEND_DENOMINATOR = 2;
        static const size_t ELEMENT_SIZE = (sizeof(Type) > sizeof(size_t) ? sizeof(Type) : sizeof(size_t));

    };

    /*
     * Pool allocator constructor.
     */
    template <class Type>
    PoolAllocator<Type>::PoolAllocator( void )
    {
        next_ = nullptr;
        buffer_ = nullptr;
        buffer_length_ = 0;
    }

    /*
     * Pool allocator destructor.
     */
    template <class Type>
    PoolAllocator<Type>::~PoolAllocator( void )
    {
    }

    /*
     * Clean up pool allocator.
     */
    template <class Type>
    void PoolAllocator<Type>::shut_down( void )
    {
        sub_allocator_.shut_down();
    }

    /*
     * Allocate element(s) from the pool.
     */
    template <class Type>
    void* PoolAllocator<Type>::allocate( size_t size )
    {
        // Make sure we're allocating multiples.
        JUTILBase::debug_assert( size == sizeof(Type) );

        // Check if next is valid.
        if (next_ != nullptr) {
            void* temp = next_;
            next_ = get_next_allocation( temp );
            return temp;
        }

        // Get more room.
        size_t old_length = buffer_length_;
        void* newest = extend();
        if (newest == nullptr) {
            return nullptr;
        }

        // Update next.
        next_ = get_next_allocation( newest );
        return newest;
    }

    /*
     * Reallocation for pool allocator.
     */
    template <class Type>
    void* PoolAllocator<Type>::reallocate( void* address, size_t size )
    {
        JUTILBase::debug_assert( size == sizeof(Type) );

        // Should only be allocating singles; may as well return the same.
        return address;
    }

    /*
     * Free from pool allocator.
     */
    template <class Type>
    void PoolAllocator<Type>::free( void* address )
    {
    }

    /*
     * Extend pool to accomodate more elements.
     */
    template <class Type>
    size_t PoolAllocator<Type>::extend( void )
    {   
        // Get new length.
        size_t old_length = buffer_length_;
        size_t new_length = (old_length + 1) * EXTEND_NUMERATOR / EXTEND_DENOMINATOR;

        // Resize buffer.
        void* new_buffer = nullptr;
        size_t new_size = new_length * ELEMENT_SIZE;
        if (buffer_length_ == 0) {
            new_buffer = sub_allocator_.allocate( new_size );
        }
        else {
            new_buffer = sub_allocator_.reallocate( buffer_, new_size );
        }

        // Check if valid extension.
        if (new_buffer == nullptr) {
            return nullptr;
        }
        buffer_ = new_buffer;
        buffer_length_ = new_length;

        // Update next pointers.
        size_t last_index = next_;
        for (size_t i = old_length; i < new_length; i++) {
            void** current = reinterpret_cast<void**>(get_allocation_by_index( i ));
            *current = last;
            last = current;
        }

        next_ = get_allocation_by_index( new_length - 1 );
        return next_;
    }

    /*
     * Get next element from given element.
     */
    template <class Type>
    void* PoolAllocator<Type>::get_allocation_by_index( size_t index )
    {
        // Get value at address as integer.
        size_t offset = index * ELEMENT_SIZE;
        return reinterpret_cast<void*>(reinterpret_cast<char*>(buffer_) + offset);
    }
    
    /*
     * Get next element from given element.
     */
    template <class Type>
    void* PoolAllocator<Type>::get_next_allocation( void* pool_address )
    {
        // Get value at address as integer.
        size_t* next_ptr = reinterpret_cast<size_t*>(pool_address);
        return get_allocation_by_index( *next_ptr );
    }

}

#endif // POOL_ALLOCATOR_HPP
