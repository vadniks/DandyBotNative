
#include <stdio.h>
#include "script.h"

/**
 * Just an example
 */
char script(unsigned row, unsigned column, unsigned level, char* objectIds, unsigned rows, unsigned columns) {
//    printf("%u %u %u\n|", row, column, level);
//    for (unsigned i = 0; i < 4; printf("%c, ", objectIds[i++]));
//    printf("|\n");

//    if ((level == 0 && column + 1 < columns && objectIds[3] == EMPTY) || (objectIds[3] >= COIN_MIN && objectIds[3] <= COIN_MAX))
//        return RIGHT;

    if (level == 0) {
        if (column < 23) return RIGHT;
        else return DOWN;
    }
    if (level == 1) {
        if (row > 1) return UP;
        else return RIGHT;
    }

    return PASS;
}
