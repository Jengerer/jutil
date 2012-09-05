#include <containers/hash_map.hpp>
#include <string/base_string.hpp>
#include <string/string.hpp>
#include <string/constant_string.hpp>
#include <string/string_hasher.hpp>
#include <stdio.h>

int main( void )
{
    JUTIL::HashMap<unsigned int, JUTIL::BaseString, int, JUTIL::StringHasher> map;
    JUTIL::HashMap<unsigned int, JUTIL::BaseString, int, JUTIL::StringHasher>::Iterator iterator;
    for (int i = 0; i < 10; i++) {
        JUTIL::StringBuilder builder;
        builder.write("Number %d", i);
        map.insert( JUTIL::String(&builder), i );
    }

    int x;
    if (map.get( JUTIL::ConstantString("Number 9"), &x )) {
        printf( "%d\n", x );
    }
    system("pause");
    return 0;
}