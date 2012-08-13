#ifndef BASE_CONTAINER_HPP
#define BASE_CONTAINER_HPP

#include "base_class.hpp"
#include "memory/allocator_interface.hpp"

namespace JUTIL
{

    /*
     * Generic container class with common container functions.
     * This base class is just for the base set of functions; an inheriting
     * class should NOT be referred to or deleted by a BaseContainer* pointer,
     * since there is no virtual destructor.
     */
    template <class Type, class Allocator>
    class BaseContainer : public BaseClass
    {

    public:

        BaseContainer( void );
        ~BaseContainer( void );

        // Memory allocation management.
        inline size_t get_length( void ) const { return length_; };

    protected:

        // Setting number of valid elements in container.
        inline void set_length( size_t length ) { length_ = length; };

        // Get interface for allocating elements.
        AllocatorInterface* get_allocator( void ) const;

    private:

        // Number of valid slots in container.
        size_t length_;

        // Allocator interface.
        Allocator allocator_;

    };

    /*
     * Base container constructor.
     */
    template <class Type, class Allocator>
    BaseContainer<Type, Allocator>::BaseContainer( void )
    {
    }

    /*
     * Base container destructor.
     */
    template <class Type, class Allocator>
    BaseContainer<Type, Allocator>::~BaseContainer( void )
    {
        allocator_.shut_down();
    }

    /*
     * Get current allocator.
     */
    template <class Type, class Allocator>
    AllocatorInterface* BaseContainer<Type, Allocator>::get_allocator( void ) const
    {
        return static_cast<AllocatorInterface*>(&allocator_);
    }

}

#endif // BASE_CONTAINER_HPP
