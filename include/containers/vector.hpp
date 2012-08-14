#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "containers/base_container.hpp"

namespace JUTIL
{

    /*
     * Vector class that acts as a resizable array.
     */
    template <class Type, class Allocator>
    class Vector : public BaseContainer<Type, Allocator>
    {

        typedef BaseContainer<Type, Allocator> BaseClass;

    public:

        Vector( void );
        ~Vector( void );

        // Array retrieval.
        Type& operator[]( size_t i );
        const Type& operator[]( size_t i ) const;

        // Array operations/getters.
        bool has_element( const Type& element ) const;
        bool remove( const Type& element );
        void clear( void );

    private:

        Type* array_;
        size_t buffer_size_;

    };

    /*
     * Vector constructor.
     */
    template <class Type, class Allocator>
    Vector<Type, Allocator>::Vector( void )
    {
        array_ = nullptr;
        buffer_size_ = 0;
    }

    /*
     * Vector destructor.
     */
    template <class Type, class Allocator>
    Vector<Type, Allocator>::~Vector( void )
    {
        clear();
    }

    /*
     * Non-const array operator.
     * Assumes valid index and array not nullptr.
     */
    template <class Type, class Allocator>
    Type& Vector<Type, Allocator>::operator[]( size_t i )
    {
        return array_[i];
    }

    /*
     * Const array operator.
     * Assumes valid index and array not nullptr.
     */
    template <class Type, class Allocator>
    const Type& Vector<Type, Allocator>::operator[]( size_t i ) const
    {
        return array_[i];
    }

    /*
     * Checks whether an element exists in the array.
     */
    template <class Type, class Allocator>
    bool Vector<Type, Allocator>::has_element( const Type& element ) const
    {
        size_t i;
        for (i = 0; i < get_length(); ++i) {
            if (element == array_[i]) {
                return true;
            }
        }

        return false;
    }

    /*
     * Remove an element from the array.
     * Returns true if the element was found, false otherwise.
     */
    template <class Type, class Allocator>
    bool Vector<Type, Allocator>::remove( const Type& element )
    {
        // Skip empty.
        if (size_ == 0) {
            return false;
        }

        // Find element index.
        size_t i;
        for (i = 0; i < size_; ++i) {
            if (element == array_[i]) {
                break;
            }
        }

        // Check if found.
        if (i != size_) {
            // Shift left
            memmove( array_ + i, array_ + i + 1, (size_ - i - 1) * sizeof(Type) ); 
            set_size( size_ - 1 );
            return true;
        }

        return false;
    }

    /*
     * Clear array elements.
     */
    template <class Type, class Allocator>
    void Vector<Type, Allocator>::clear( void )
    {
        AllocatorInterface* allocator = get_allocator();
        allocator->free( array_ );
    }

    /*
     * Set number of elements in array.
     * Returns true if reallocation succeeded, false otherwise.
     */
    template <class Type, class Allocator>
    bool Vector<Type, Allocator>::reserve( size_t length )
    {
        // Check if emptying.
        AllocatorInterface* allocator = get_interface();
        if (size == 0) {
            allocator->free( array_ );
            size_ = 0;
            return true;
        }

        // Attempt sizing.
        Type* new_array;
        size_t real_size = length * sizeof(Type);
        if (size_ == 0) {
            new_array = (Type*)allocator->allocate( real_size );
        }
        else {
            new_array = (Type*)allocator->reallocate( real_size );
        }

        // Check successful resize.
        if (new_array == nullptr) {
            return false;
        }

        array_ = new_array;
        size_ = size;
        return true;
    }

}

#endif // VECTOR_HPP
