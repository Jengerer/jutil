#include <containers/map.hpp>
#include <stdio.h>

int main( void )
{
    JUTIL::Map<int, int> map;
    JUTIL::Map<int, int>::Iterator iterator;
    for (int i = 0; i < 10; i++) {
        map.insert(i, i+1);
    }

    for (iterator = map.begin(); iterator.has_next(); iterator.next()) {
        printf("%d maps to %d.\n", iterator.get_key(), iterator.get_value());
    }
    system("pause");
    return 0;
}