#ifndef BASE_CONTAINER_HPP
#define BASE_CONTAINER_HPP

#include "base/jutil_base.hpp"

namespace JUTIL
{

    /*
     * Generic container class with common container functions.
     * This base class is just for the base set of functions; an inheriting
     * class should NOT be referred to or deleted by a BaseContainer* pointer,
     * since there is no virtual destructor.
     */
    template <class Type>
    class BaseContainer
    {

    public:

        BaseContainer( void );
        ~BaseContainer( void );

        // Memory allocation management.
        inline size_t get_length( void ) const { return length_; };

    protected:

        // Setting number of valid elements in container.
        inline void set_length( size_t length ) { length_ = length; };

    private:

        // Number of valid slots in container.
        size_t length_;

    };

    /*
     * Base container constructor.
     */
    template <class Type>
    BaseContainer<Type>::BaseContainer( void )
    {
        set_length( 0 );
    }

    /*
     * Base container destructor.
     */
    template <class Type>
    BaseContainer<Type>::~BaseContainer( void )
    {
        // Should be empty on removal.
        JUTILBase::debug_assert( length_ == 0 );
    }

}

#endif // BASE_CONTAINER_HPP
