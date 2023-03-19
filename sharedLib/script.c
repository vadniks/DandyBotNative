/*
 * Copyright (c) 2021 Peter Sovietov (https://github.com/true-grue)
 *
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

#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include "script.h"

#define ARGUMENTS unsigned row, unsigned column, unsigned level, \
    unsigned rows, unsigned columns, const char* objects

#define LOG_FRAMES

#if defined(LOG_FRAMES)
void logFrames(ARGUMENTS);
#endif

char hasCollectedCoin = 0;

/** Just an example */
__attribute__((unused)) char script(ARGUMENTS) {

#if defined(LOG_FRAMES)
    logFrames(row, column, level, rows, columns, objects);
#endif

    if (level > 0) return PASS;

    char right = column + 1 < columns ? objects[coordsToIndex(row, columns, column + 1)] : NOTHING;
    if (!hasCollectedCoin && right == EMPTY) return RIGHT;
    if (isCoin(right)) {
        hasCollectedCoin = 1;
        return RIGHT;
    }

    char down = row + 1 < rows ? objects[coordsToIndex((row + 1), columns, column)] : NOTHING;
    if (down == EMPTY || isCoin(down)) return DOWN;

    return PASS;
}

#if defined(LOG_FRAMES)

#include <stdio.h>
#include <stdlib.h>

/**
 * Prints each game frame in a TUI manner,
 * meaning the previous frame will be overwritten
 * with the next one at the same position
 */
void logFrames(ARGUMENTS) {
    rewind(stdout);
    system("clear");
    printf("%u %u %u %u %u\n", row, column, level, rows, columns);
    for (unsigned r = 0, c; r < rows; r++) {
        for (c = 0; c < columns; printf("%c", objects[coordsToIndex(r, columns, c++)]));
        printf("\n");
    }
    fflush(stdout);
}

#endif
