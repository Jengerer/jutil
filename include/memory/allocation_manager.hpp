#ifndef ALLOCATION_MANAGER_HPP
#define ALLOCATION_MANAGER_HPP

#include "base/jutil_base.hpp"
#include <boost/thread/mutex.hpp>

namespace JUTIL
{

    /*
     * Allocation list data structure.
     */
    struct Allocation
    {
        // Allocation information.
        size_t num;
        void* address;
        size_t size;

        // List structure.
        struct Allocation* prev;
        struct Allocation* next;
    };

    /*
     * Class for tracking allocations, reallocations, and frees on heap.
     */
    class AllocationManager
    {

    public:

        // Private constructor and destructor.
        AllocationManager( void );
        ~AllocationManager( void );

        // Allocation debugging.
        void set_debug_break( size_t allocation_num );
        void dump_leaks( const char* filename );

        // Allocation tracking.
        void on_allocate( void* address, size_t size );
        void on_reallocate( void* address, void* new_address, size_t new_size );
        void on_release( void* address );

    public:

        // Singleton instance creation.
        static AllocationManager* get_instance( void );
        static void shut_down( void );

    private:

        // Find structure for existing allocations.
        struct Allocation* find_allocation( void* address );

    private:

        static AllocationManager* instance_;

    private:

        struct Allocation* root_;
        size_t allocation_num_;
        size_t break_allocation_;

		// Allocation logging mutex.
		boost::mutex allocation_mutex_;

    };

}

#endif // ALLOCATION_MANAGER_HPP
