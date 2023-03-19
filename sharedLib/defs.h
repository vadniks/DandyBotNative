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

#pragma once

#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

/** object ids */
extern const char NOTHING;
extern const char EMPTY;
extern const char BLOCK;
extern const char COIN_MIN;
extern const char COIN_MAX;
extern const char ENEMY_MIN;
extern const char ENEMY_MAX;
extern const char PLAYER;

/** action ids */
extern const char UP;
extern const char LEFT;
extern const char DOWN;
extern const char RIGHT;
extern const char PASS;

/** Converts row and column coordinates to index of an object */
unsigned coordsToIndex(unsigned row, unsigned columns, unsigned column);

/** Checks whether the given object is a coin */
int isCoin(char object);

/** Checks whether the given object is an enemy */
int isEnemy(char object);
