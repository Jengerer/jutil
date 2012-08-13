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

        // Memory management.
        bool reserve( size_t elements );

    protected:

        void set_allocator( AllocatorInterface* allocator );
        AllocatorInterface* get_allocator( void ) const;

    private:

        Allocator allocator_;

    };

    /*
     * Base container constructor.
     */
    template <class Type, class Allocator>
    BaseContainer<Type, Allocator>::BaseContainer( AllocatorInterface* allocator )
    {
        set_allocator( allocator );
    }

    /*
     * Base container destructor.
     */
    template <class Type, class Allocator>
    BaseContainer<Type, Allocator>::~BaseContainer( void )
    {
    }

    /*
     * Setting new container object allocator.
     * Allocator must have been initialized before setting; no error
     * checking is done here.
     */
    template <class Type, class Allocator>
    void BaseContainer<Type, Allocator>::set_allocator( AllocatorInterface* allocator )
    {
        allocator_ = allocator;
    } 

    /*
     * Get current allocator.
     */
    template <class Type, class Allocator>
    AllocatorInterface* BaseContainer<Type, Allocator>::get_allocator( void ) const
    {
        return allocator_;
    }

}

#endif // BASE_CONTAINER_HPP
