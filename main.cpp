#include <containers/hash_map.hpp>
#include <string/string.hpp>
#include <string/string_hasher.hpp>
#include <stdio.h>

int main( void )
{
    JUTIL::HashMap<unsigned int, i, const char*, JUTIL::StringHasher> map;
    JUTIL::HashMap<unsigned int, i, const char*, JUTIL::StringHasher>::Iterator iterator;
    for (int i = 0; i < 10; i++) {
        JUTIL::StringBuilder builder;
        builder.write("So goes the number %d...", i);
        map.insert( &builder, "And there it is...\n" );
    }

    for (iterator = map.begin(); iterator.has_next(); iterator.next()) {
        printf("%s.\n", iterator.get_value());
    }
    system("pause");
    return 0;
}