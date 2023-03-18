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

#include "defs.h"

char NOTHING = -1;
char EMPTY = ' ';
char BLOCK = '#';
char COIN_MIN = '1';
char COIN_MAX = '9';
char ENEMY_MIN = 'a';
char ENEMY_MAX = 'f';
char PLAYER = '!';

char UP = 87;
char LEFT = 65;
char DOWN = 83;
char RIGHT = 68;
char PASS = -1;

unsigned coordsToIndex(unsigned row, unsigned columns, unsigned column)
{ return row * columns + column; }

int isCoin(char object) { return object >= COIN_MIN && object <= COIN_MIN; }
int isEnemy(char object) { return object >= ENEMY_MIN && object <= ENEMY_MIN; }
