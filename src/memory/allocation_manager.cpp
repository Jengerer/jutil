#include "memory/allocation_manager.hpp"
#include <stdio.h>
#include <stdlib.h>

namespace JUTIL
{

    // Static members.
    AllocationNode* AllocationManager::root_ = nullptr;
    int AllocationManager::allocation_num_ = 0;

    /*
     * Mark address as allocated.
     */
    void AllocationManager::set_allocated( const void* address, size_t size )
    {
        AllocationNode* node = (AllocationNode*)malloc( sizeof(AllocationNode) );
        if (node == nullptr) {
            return;
        }

        // Fill out node.
        node->allocation.allocation_num = allocation_num_;
        node->allocation.address = address;
        node->allocation.size = size;
        allocation_num_++;

        // Update current root.
        if (root_ != nullptr) {
            root_->prev = node;
        } 

        // Add to list.
        node->next = root_;
        node->prev = nullptr;
        root_ = node;
    }


    /*
     * Update currently existing allocation.
     */
    void AllocationManager::update_allocated( const void* address, const void* new_address, size_t new_size )
    {
        AllocationNode* node = find_node( address );
        if (node != nullptr) {
            Allocation* allocation = &node->allocation;
            allocation->address = new_address;
            allocation->size = new_size;
        }
    }


    /*
     * Mark address as freed.
     */
    void AllocationManager::set_freed( const void* address )
    {
        // Find node by address.
        AllocationNode* node = find_node( address );
        if (node != nullptr) {
            // Update next and previous.
            if (node->next != nullptr) {
                node->next->prev = node->prev;
            }
            if (node->prev != nullptr) {
                node->prev->next = node->next;
            }

            // Update root.
            if (node == root_) {
                root_ = node->next;
            }
            free( node );
        }
    }


    /*
     * Dump allocation information.
     */
    void AllocationManager::dump( const char* filename )
    {
        // TODO: Use file wrapper class later.
        FILE* file;
        errno_t error = fopen_s( &file, filename, "w" );
        if (error == 0) {
            // Dump all allocations.
            AllocationNode* node = root_;
            while (node != nullptr) {
                Allocation* allocation = &node->allocation;
                fprintf_s(
                    file,
                    "NUMBER: %u\r\n" \
                    "ADDRESS: 0x%x\r\n" \
                    "SIZE: %u\r\n" \
                    "ASCII:\r\n" \
                    "======\r\n",
                    allocation->allocation_num,
                    allocation->address,
                    allocation->size );
                for (size_t i = 0; i < allocation->size; i++) {
                    fprintf_s( file, "%c", *((char*)allocation->address + i) );
                }
                fprintf_s( file, "\r\n\r\n" );
                node = node->next;
            }

            // Finish dump.
            fclose( file );
        }
    }

    /*
     * Find memory allocation node by address.
     */
    AllocationNode* AllocationManager::find_node( const void* address )
    {
        AllocationNode* node = root_;
        while (node != nullptr) {
            if (node->allocation.address == address) {
                return node;
            }
            node = node->next;
        }
        
        // Not found.
        return nullptr;
    }

}
