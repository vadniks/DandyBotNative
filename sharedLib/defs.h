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

#pragma once

/** object ids */
extern char NOTHING;
extern char EMPTY;
extern char BLOCK;
extern char COIN_MIN;
extern char COIN_MAX;
extern char ENEMY_MIN;
extern char ENEMY_MAX;
extern char PLAYER;

/** action ids */
extern char UP;
extern char LEFT;
extern char DOWN;
extern char RIGHT;
extern char PASS;

/** Converts row and column coordinates to index of an object */
unsigned coordsToIndex(unsigned row, unsigned columns, unsigned column);

/** Checks whether the given object is a coin */
int isCoin(char object);

/** Checks whether the given object is an enemy */
int isEnemy(char object);
