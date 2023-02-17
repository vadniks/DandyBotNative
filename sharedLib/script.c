
#include <stdio.h>
#include "script.h"

char hasCollectedCoin = 0;

/**
 * Just an example
 */
char script(unsigned row, unsigned column, unsigned level, unsigned rows, unsigned columns, char* objects) {
#if 0
    printf("%u %u %u %u %u\n", row, column, level, rows, columns);
    for (unsigned r = 0, c = 0; r < rows; r++) {
        for (c = 0; c < columns; printf("%c", objects[r * columns + c++]));
        printf("\n");
    }
#endif

    if (level > 0) return PASS;

    char right = column + 1 < columns ? objects[row * columns + column + 1] : NOTHING;
    if (!hasCollectedCoin && right == EMPTY) return RIGHT;
    if (right >= COIN_MIN && right <= COIN_MIN) {
        hasCollectedCoin = 1;
        return RIGHT;
    }

    char down = row + 1 < rows ? objects[(row + 1) * columns + column] : NOTHING;
    if (down == EMPTY || (down >= COIN_MIN && down <= COIN_MIN)) return DOWN;

    return PASS;
}
