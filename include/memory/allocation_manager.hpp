#ifndef ALLOCATION_MANAGER_HPP
#define ALLOCATION_MANAGER_HPP

namespace JUTIL
{

    /*
     * Struct to represent an allocation.
     */
    struct Allocation
    {
        size_t allocation_num;
        const void* address;
        size_t size;
    };

    /*
     * Allocation manager list struct.
     */
    struct AllocationNode
    {
        Allocation allocation;
        AllocationNode* next;
    };

    /*
     * Tracks and manages allocations across objects of base class.
     */
    class AllocationManager
    { 

    public:

        // Allocation tracking functions.
        static void set_allocated( const void* address, size_t size );
        static void set_freed( const void* address );

        // Allocation logging.
        static void dump( const char* filename );
        static void clear( void );

    private:

        static AllocationNode* root_;
        static int allocation_num_;

    };

}

#endif // ALLOCATION_MANAGER_HPP
