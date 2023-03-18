/*
 * Copyright (C) 2023 Vad Nik (https://github.com/vadniks)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

//#define IS_DEBUG

#if defined(IS_DEBUG)
#  include <stdio.h>
#endif

#include "script.h"

char hasCollectedCoin = 0;

/**
 * Just an example
 */
char script(unsigned row, unsigned column, unsigned level,
            unsigned rows, unsigned columns, const char* objects) {

#if defined(IS_DEBUG)
    printf("%u %u %u %u %u\n", row, column, level, rows, columns);
    for (unsigned r = 0, c = 0; r < rows; r++) {
        for (c = 0; c < columns; printf("%c", objects[r * columns + c++]));
        printf("\n");
    }
#endif

    if (level > 0) return PASS;

    char right = column + 1 < columns ? objects[coordsToIndex(row, columns, column + 1)] : NOTHING;
    if (!hasCollectedCoin && right == EMPTY) return RIGHT;
    if (right >= COIN_MIN && right <= COIN_MIN) {
        hasCollectedCoin = 1;
        return RIGHT;
    }

    char down = row + 1 < rows ? objects[coordsToIndex((row + 1), columns, column)] : NOTHING;
    if (down == EMPTY || (down >= COIN_MIN && down <= COIN_MIN)) return DOWN;

    return PASS;
}
