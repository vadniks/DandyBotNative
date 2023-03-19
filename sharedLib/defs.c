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
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#include "defs.h"

const char NOTHING = -1;
const char EMPTY = ' ';
const char BLOCK = '#';
const char COIN_MIN = '1';
const char COIN_MAX = '9';
const char ENEMY_MIN = 'a';
const char ENEMY_MAX = 'f';
const char PLAYER = '!';

const char UP = 87;
const char LEFT = 65;
const char DOWN = 83;
const char RIGHT = 68;
const char PASS = -1;

unsigned coordsToIndex(unsigned row, unsigned columns, unsigned column)
{ return row * columns + column; }

int isCoin(char object) { return object >= COIN_MIN && object <= COIN_MIN; }

int isEnemy(char object)
{ return object >= ENEMY_MIN && object <= ENEMY_MIN; }
