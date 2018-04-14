#include "memory/allocation_manager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <new.h>

namespace JUTIL
{

	// Allocation manager instance.
	AllocationManager* AllocationManager::instance_ = nullptr;

	/*
	 * Allocation manager constructor.
	 */
	AllocationManager::AllocationManager( void ) :
		root_( nullptr ),
		allocation_num_( 1 ),
		break_allocation_( 0 ),
		allocation_mutex_()

	{
	}

	/*
	 * Allocation manager destructor.
	 */
	AllocationManager::~AllocationManager( void )
	{
		// Clear allocations.
		while (root_ != nullptr) {
			on_release( root_->address );
		}
	}

	/*
	 * Set point to break on.
	 */
	void AllocationManager::set_debug_break( size_t allocation_num )
	{
		break_allocation_ = allocation_num;
	}

	/*
	 * Dump leaks to file.
	 */
	void AllocationManager::dump_leaks( const char* filename )
	{
		// Open file.
		FILE* file;
		errno_t error = fopen_s( &file, filename, "w" );
		if (error != 0) {
			return;
		}

		// Write all leaks to file.
		struct Allocation* allocation = root_;
		while (allocation != nullptr) {
			fprintf( file, "===========\n" );
			fprintf( file, "ALLOCATION: #%u\n", allocation->num );
			fprintf( file, "ADDRESS:    &0x%08p\n", allocation->address );
			fprintf( file, "SIZE:       %u\n", allocation->size );

			// Dump data.
			fprintf( file, "HEX DUMP:   " );
			size_t i;
			const char* buffer = static_cast<const char*>(allocation->address);
			for (i = 0; i < allocation->size; ++i) {
				fprintf( file, "%02x ", buffer[i] );
			}
			fprintf( file, "\n" );

			// Dump ASCII.
			fprintf( file, "ASCII DUMP: " );
			for (i = 0; i < allocation->size; ++i) {
				fprintf( file, "%c", buffer[i] );
			}
			fprintf( file, "\n===========\n\n" );
			
			allocation = allocation->next;
		}

		// Close file.
		fclose( file );
	}

	/*
	 * Track allocation from heap.
	 */
	void AllocationManager::on_allocate( void* address, size_t size )
	{
		// Acquire mutex.
		allocation_mutex_.lock();

		// Break on allocation.
		if (allocation_num_ == break_allocation_) {
			JUTIL::JUTILBase::debug_assert( false );
		}

		// Create struct for tracking.
		struct Allocation* allocation = static_cast<struct Allocation*>(malloc( sizeof(struct Allocation) ));
		if (allocation == nullptr) {
			return;
		}

		// Set up and add to head.
		allocation->num = allocation_num_;
		allocation->address = address;
		allocation->size = size;
		allocation->prev = nullptr;
		allocation->next = root_;
	
		// Update root if any.
		if (root_ != nullptr) {
			root_->prev = allocation;
		}
		root_ = allocation;
		allocation_num_++;

		// Release mutex.
		allocation_mutex_.unlock();
	}

	/*
	 * Move existing allocation.
	 */
	void AllocationManager::on_reallocate( void* address, void* new_address, size_t new_size )
	{
		// Acquire mutex.
		allocation_mutex_.lock();

		// Find allocation.
		struct Allocation* allocation = find_allocation( address );
		JUTIL::JUTILBase::debug_assert( allocation != nullptr );
		if (allocation == nullptr) {
			return;
		}

		// Update address and size.
		allocation->address = new_address;
		allocation->size = new_size;

		// Release mutex.
		allocation_mutex_.unlock();
	}

	/*
	 * Remove allocation.
	 */
	void AllocationManager::on_release( void* address )
	{
		// Acquire mutex.
		allocation_mutex_.lock();

		// Find allocation.
		struct Allocation* allocation = find_allocation( address );
		JUTIL::JUTILBase::debug_assert( allocation != nullptr );
		if (allocation == nullptr) {
			return;
		}

		// Update previous and next.
		if (allocation->prev != nullptr) {
			allocation->prev->next = allocation->next;
		}
		if (allocation->next != nullptr) {
			allocation->next->prev = allocation->prev;
		}

		// Check for root case.
		if (address == root_->address) {
			root_ = allocation->next;
		}

		// Delete allocation.
		free( allocation );

		// Release mutex.
		allocation_mutex_.unlock();
	}

	/*
	 * Allocation manager singleton instance function.
	 */
	AllocationManager* AllocationManager::get_instance( void )
	{
		// Create if not created yet.
		if (instance_ == nullptr) {
			instance_ = static_cast<AllocationManager*>(malloc( sizeof(AllocationManager) ));
			JUTIL::JUTILBase::debug_assert( instance_ != nullptr );
			if (instance_ == nullptr) {
				return nullptr;
			}

			instance_ = new (instance_) AllocationManager();
		}

		return instance_;
	}

	/*
	 * Allocation manager singleton instance destruction.
	 */
	void AllocationManager::shut_down( void )
	{
		delete instance_;
	}

	/*
	 * Find allocation by address.
	 */
	struct Allocation* AllocationManager::find_allocation( void* address )
	{
		// Search for matching address.
		struct Allocation* allocation = root_;
		while (allocation != nullptr) {
			if (allocation->address == address) {
				break;
			}
			allocation = allocation->next;
		}

		return allocation;
	}

}