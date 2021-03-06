#ifndef BASE_SERVICES_HPP
#define BASE_SERVICES_HPP

#include "memory/heap_allocator.hpp"

namespace JUTIL
{

	/*
	 * Services for objects of base class.
	 */
	class BaseServices
	{

		public:

			// Default allocator getter.
			static AllocatorInterface* get_default_allocator( void );

		private:

			static HeapAllocator allocator_;
			
	};

}

#endif // BASE_SERVICES_HPP
