#include "base/jutil_base.hpp"
#include <assert.h>

namespace JUTIL
{

	/*
	 * Debug assertion function.
	 */
	void JUTILBase::debug_assert( bool condition )
	{
#if defined( _DEBUG )
		if (!condition) {
			__asm { int 3 }
		}
#endif
	}

}