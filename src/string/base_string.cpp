#include "string/base_string.hpp"

namespace JUTIL
{

    /*
     * Generic string destructor.
     */
    BaseString::~BaseString( void )
    {
        // Nothing to clean yet.
    }

    /*
     * Get string length.
     */
    unsigned int BaseString::get_length( void ) const
    {
        return length_;
    }

    /*
     * Set stored string length.
     */
    void BaseString::set_length( unsigned int length )
    {
        length_ = length;
    }

}
