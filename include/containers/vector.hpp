#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "containers/base_container.hpp"
#include "memory/base_allocator.hpp"

namespace JUTIL
{

    // Vector push expansion factors.
    const unsigned int PUSH_EXPAND_NUMERATOR = 3;
    const unsigned int PUSH_EXPAND_DENOMINATOR = 2;

    /*
     * Vector class that acts as a resizable array.
     */
    template <class Type>
    class __declspec(dllexport) Vector : public BaseContainer<Type>
    {

        typedef BaseContainer<Type> BaseClass;

    public:

        Vector( void );
        ~Vector( void );

        // Element management.
        Type& get( size_t i );
        const Type& get( size_t i ) const;
        void set( size_t i, const Type& element );
        bool contains( const Type& element ) const;
        bool erase( size_t i );
        bool remove( const Type& element );
        bool push( const Type& element );

        // Buffer management.
        bool set_length( size_t length );
        void clear( void );
        Type* get_buffer( void );
        const Type* get_buffer( void ) const;

    private:

        // Local buffer management.
        bool set_buffer_size( size_t length );

    private:

        Type* array_;
        size_t buffer_size_;

    };

    /*
     * Vector constructor.
     */
    template <class Type>
    Vector<Type>::Vector( void )
    {
        array_ = nullptr;
        buffer_size_ = 0;
    }

    /*
     * Vector destructor.
     */
    template <class Type>
    Vector<Type>::~Vector( void )
    {
        clear();
    }

    /*
     * Non-constant reference getter for index.
     * Assumes valid index and array not nullptr.
     */
    template <class Type>
    Type& Vector<Type>::get( size_t i )
    {
        return array_[i];
    }

    /*
     * Gets element at index (constant reference).
     * Assumes valid index and array not nullptr.
     */
    template <class Type>
    const Type& Vector<Type>::get( size_t i ) const
    {
        return array_[i];
    }

    /*
     * Set element in array.
     */
    template <class Type>
    void Vector<Type>::set( size_t i, const Type& element )
    {
        array_[i] = element;
    }

    /*
     * Checks whether an element exists in the array.
     */
    template <class Type>
    bool Vector<Type>::contains( const Type& element ) const
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
     * Remove an element from the array by index.
     * Assumes valid index.
     */
    template <class Type>
    bool Vector<Type>::erase( size_t i )
    {
        // Shift left
        size_t length = get_length();
        memmove( array_ + i, array_ + i + 1, (length - i - 1) * sizeof(Type) );

        // TODO: If we're shrinking the array, we don't care if it fails; make set_length pass if
        // failed to realloc when shrinking.
        if (!set_length( length - 1 )) {
            return false;
        }

        return true;
    }

    /*
     * Remove an element from the array.
     * Returns true if the element was found, false otherwise.
     */
    template <class Type>
    bool Vector<Type>::remove( const Type& element )
    {
        // Skip empty.
        if (get_length() == 0) {
            return false;
        }

        // Find element index.
        size_t i;
        size_t length = get_length();
        for (i = 0; i < length; ++i) {
            if (element == array_[i]) {
                break;
            }
        }

        // Check if found.
        if (i != length) {
            return erase( i );
        }

        return false;
    }

    /*
     * Add an element to the end of the vector.
     */
    template <class Type>
    bool Vector<Type>::push( const Type& element )
    {
        // Check if array needs to be expanded.
        size_t length = get_length();
        if (buffer_size_ == length) {
            unsigned int new_length = (length + 1) * PUSH_EXPAND_NUMERATOR / PUSH_EXPAND_DENOMINATOR;
            if (!set_buffer_size( new_length )) {
                return false;
            }
        }

        // Add to end.
        set( length, element );
        set_length( length + 1 );
        return true;
    }

    /*
     * Set new array size.
     * Always matches buffer to length, so is destructive.
     */
    template <class Type>
    bool Vector<Type>::set_length( size_t length )
    {
        // Allocate if needed.
        if (!set_buffer_size( length )) {
            return false;
        }

        // Set base length.
        BaseClass::set_length( length );
        return true;
    }

    /*
     * Clear array elements.
     */
    template <class Type>
    void Vector<Type>::clear( void )
    {
        set_length( 0 );
    }

    /*
     * Get reference to buffer to pass as C-style array.
     */
    template <class Type>
    Type* Vector<Type>::get_buffer( void )
    {
        return array_;
    }

    /*
     * Get reference to constant buffer to pass as C-style array.
     */
    template <class Type>
    const Type* Vector<Type>::get_buffer( void ) const
    {
        return array_;
    }

    /*
     * Set number of elements in array.
     * Returns true if reallocation succeeded, false otherwise.
     */
    template <class Type>
    bool Vector<Type>::set_buffer_size( size_t length )
    {
        // Check if emptying.
        if (length == 0) {
            // Check if already emptied.
            if (buffer_size_ != 0) {
                free( array_ );
                buffer_size_ = 0;
            }

            return true;
        }

        // Attempt sizing.
        bool result;
        if (buffer_size_ == 0) {
            result = BaseAllocator::allocate_array( &array_, length );
        }
        else {
            result = BaseAllocator::reallocate_array( &array_, length );
        }

        // Check successful resize.
        if (!result) {
            return false;
        }

        buffer_size_ = length;
        return true;
    }

}

#endif // VECTOR_HPP
