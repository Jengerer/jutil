#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "containers/base_container.hpp"

namespace JUTIL
{

    /*
     * Vector class that acts as a resizable array.
     */
    template <class Type>
    class Vector : public BaseContainer<Type>
    {

        typedef BaseContainer<Type> BaseClass;

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
        bool set_buffer_size( size_t length );
        bool push( const Type& element );

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
     * Non-const array operator.
     * Assumes valid index and array not nullptr.
     */
    template <class Type>
    Type& Vector<Type>::operator[]( size_t i )
    {
        return array_[i];
    }

    /*
     * Const array operator.
     * Assumes valid index and array not nullptr.
     */
    template <class Type>
    const Type& Vector<Type>::operator[]( size_t i ) const
    {
        return array_[i];
    }

    /*
     * Checks whether an element exists in the array.
     */
    template <class Type>
    bool Vector<Type>::has_element( const Type& element ) const
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
    template <class Type>
    bool Vector<Type>::remove( const Type& element )
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
    template <class Type>
    void Vector<Type>::clear( void )
    {
        free( array_ );
    }

    /*
     * Set number of elements in array.
     * Returns true if reallocation succeeded, false otherwise.
     */
    template <class Type>
    bool Vector<Type>::set_buffer_size( size_t length )
    {
        // Check if emptying.
        if (size == 0) {
            free( array_ );
            size_ = 0;
            return true;
        }

        // Attempt sizing.
        Type* new_array;
        size_t real_size = length * sizeof(Type);
        if (size_ == 0) {
            new_array = (Type*)malloc( real_size );
        }
        else {
            new_array = (Type*)realloc( array_, real_size );
        }

        // Check successful resize.
        if (new_array == nullptr) {
            return false;
        }

        array_ = new_array;
        buffer_size_ = size;
        return true;
    }

}

#endif // VECTOR_HPP
